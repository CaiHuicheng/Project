#include "include\game.h"
#include "include\resource_manager.h"
#include "include\sprite_renderer.h"
#include "include\game_object.h"
#include "include\ball_object.h"
#include "include\particle_generator.h"

SpriteRenderer *Renderer;
GameObject *Player;
BallObject *Ball;
ParticleGenerator *Particles;

Game::Game(GLint width, GLint height):State(GAME_ACTIVE), Keys(), Width(width), Height(height) 
{

}
Game::~Game()
{
	delete Renderer;
	delete Player;
	delete Ball;
	delete Particles;
}

//初始化
void Game::Init()
{
	//加载着色器
	ResourceManager::LoadShader("GLSL/game.vs", "GLSL/game.fs",nullptr,"sprite");
	ResourceManager::LoadShader("GLSL/particle.vs", "GLSL/particle.frag", nullptr, "particle");
	//配置着色器
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("particle").SetMatrix4("projection", projection);
	//加载纹理
	ResourceManager::LoadTexture("images/background.jpg", GL_FALSE, "background");
	ResourceManager::LoadTexture("images/awesomeface.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("images/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("images/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture("images/paddle.png", GL_TRUE, "paddle");
	ResourceManager::LoadTexture("images/particle.png", GL_TRUE, "particle");
	//设置纹理控制器
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	Particles = new ParticleGenerator(ResourceManager::GetShader("particle"),ResourceManager::GetTexture("particle"),500);
	//加载Level
	GameLevel level_1; level_1.Load("levels/1.lvl", this->Width, this->Height*0.5);
	GameLevel level_2; level_1.Load("levels/2.lvl", this->Width, this->Height*0.5);
	GameLevel level_3; level_1.Load("levels/3.lvl", this->Width, this->Height*0.5);
	GameLevel level_4; level_1.Load("levels/4.lvl", this->Width, this->Height*0.5);
	this->Levels.push_back(level_1);
	this->Levels.push_back(level_2);
	this->Levels.push_back(level_3);
	this->Levels.push_back(level_4);
	this->Level = 0;
	/*初始化游戏对象*/
	//初始化paddle
	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
	//初始化ball
	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,ResourceManager::GetTexture("face"));

}

//更新
void Game::Update(GLfloat dt)
{
	//更新对象
	Ball->Move(dt, this->Width);
	//检测碰撞
	this->DoCollisions();
	//更新粒子
	Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2));
	//检测下边界，判断是否死亡重新开始
	if (Ball->Position.y >= this->Height) 
	{
		this->ResetLevel();
		this->ResetPlayer();
	}
}

//输入处理
void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		GLfloat velocity = PLAYER_VELOCITY * dt;
		// 移动玩家挡板
		if (this->Keys[GLFW_KEY_LEFT]||this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0)
			{
				Player->Position.x -= velocity;
				if (Ball->Stuck)
					Ball->Position.x -= velocity;
			}
		}
		if (this->Keys[GLFW_KEY_RIGHT] || this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
			{
				Player->Position.x += velocity;
				if (Ball->Stuck)
					Ball->Position.x += velocity;
			}
		}
		if (this->Keys[GLFW_KEY_ENTER])
			Ball->Stuck = false;
	}
}

//渲染
void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		// Draw background
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		// Draw level
		this->Levels[this->Level].Draw(*Renderer);
		// Draw player
		Player->Draw(*Renderer);
		// Draw particles   
		Particles->Draw();
		// Draw ball
		Ball->Draw(*Renderer);
	}
}

void Game::ResetLevel()
{
	if (this->Level == 0)
		this->Levels[0].Load("levels/1.lvl", this->Width, this->Height * 0.5f);
	else if (this->Level == 2)
		this->Levels[1].Load("levels/2.lvl", this->Width, this->Height * 0.5f);
	else if (this->Level == 1)
		this->Levels[2].Load("levels/3.lvl", this->Width, this->Height * 0.5f);
	else if (this->Level == 3)
		this->Levels[3].Load("levels/4.lvl", this->Width, this->Height * 0.5f);
}

void Game::ResetPlayer()
{
	// Reset player/ball stats
	Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);
}


Direction VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),  // 上
		glm::vec2(1.0f, 0.0f),  // 右
		glm::vec2(0.0f, -1.0f), // 下
		glm::vec2(-1.0f, 0.0f)  // 左
	};
	GLfloat max = 0.0f;
	GLuint best_match = -1;
	for (GLuint i = 0; i < 4; i++)
	{
		GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}

//AABB碰撞检测
GLboolean CheckCollision(GameObject &one, GameObject &two)
{
// x轴方向碰撞？
bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
two.Position.x + two.Size.x >= one.Position.x;
// y轴方向碰撞？
bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
two.Position.y + two.Size.y >= one.Position.y;
// 只有两个轴向都有碰撞时才碰撞
return collisionX && collisionY;
}

//圆形碰撞外形 碰撞检测
Collision CheckCollision(BallObject &one, GameObject &two) // AABB - Circle collision
{
	// 获取圆的中心 
	glm::vec2 center(one.Position + one.Radius);
	// 计算AABB的信息（中心、半边长）
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(
		two.Position.x + aabb_half_extents.x,
		two.Position.y + aabb_half_extents.y
	);
	// 获取两个中心的差矢量
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// AABB_center加上clamped这样就得到了碰撞箱上距离圆最近的点closest
	glm::vec2 closest = aabb_center + clamped;
	// 获得圆心center和最近点closest的矢量并判断是否 length <= radius
	difference = closest - center;
	if (glm::length(difference) <= one.Radius)
		return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
	else
		return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
}


void Game::DoCollisions()
{
	for (GameObject &box : this->Levels[this->Level].Bricks)
	{
		if (!box.Destroyed)
		{
			Collision collision = CheckCollision(*Ball, box);
			if (std::get<0>(collision)) // 如果collision 是 true
			{
				// 如果砖块不是实心就销毁砖块
				if (!box.IsSolid)
					box.Destroyed = GL_TRUE;
				// 碰撞处理
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (dir == LEFT || dir == RIGHT) // 水平方向碰撞
				{
					Ball->Velocity.x = -Ball->Velocity.x; // 反转水平速度
														  // 重定位
					GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
					if (dir == LEFT)
						Ball->Position.x += penetration; // 将球右移
					else
						Ball->Position.x -= penetration; // 将球左移
				}
				else // 垂直方向碰撞
				{
					Ball->Velocity.y = -Ball->Velocity.y; // 反转垂直速度
														  // 重定位
					GLfloat penetration = Ball->Radius - std::abs(diff_vector.y);
					if (dir == UP)
						Ball->Position.y -= penetration; // 将球上移
					else
						Ball->Position.y += penetration; // 将球下移
				}
			}
		}
		//检查玩家paddle的碰撞（除非卡住）
		Collision result = CheckCollision(*Ball, *Player);
		if (!Ball->Stuck && std::get<0>(result))
		{
			// 检查它击中paddle的地点，并根据它击中paddle的地点更改速度
			GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
			GLfloat distance = (Ball->Position.x + Ball->Radius) - centerBoard;
			GLfloat percentage = distance / (Player->Size.x / 2);
			// 相应地移动
			GLfloat strength = 2.0f;
			glm::vec2 oldVelocity = Ball->Velocity;
			Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
			//Ball->Velocity.y = -Ball->Velocity.y;
			Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity); // Keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)															// Fix sticky paddle
			Ball->Velocity.y = -1 * abs(Ball->Velocity.y);
		}
	}
}

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

//��ʼ��
void Game::Init()
{
	//������ɫ��
	ResourceManager::LoadShader("GLSL/game.vs", "GLSL/game.fs",nullptr,"sprite");
	ResourceManager::LoadShader("GLSL/particle.vs", "GLSL/particle.frag", nullptr, "particle");
	//������ɫ��
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("particle").SetMatrix4("projection", projection);
	//��������
	ResourceManager::LoadTexture("images/background.jpg", GL_FALSE, "background");
	ResourceManager::LoadTexture("images/awesomeface.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("images/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("images/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture("images/paddle.png", GL_TRUE, "paddle");
	ResourceManager::LoadTexture("images/particle.png", GL_TRUE, "particle");
	//�������������
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	Particles = new ParticleGenerator(ResourceManager::GetShader("particle"),ResourceManager::GetTexture("particle"),500);
	//����Level
	GameLevel level_1; level_1.Load("levels/1.lvl", this->Width, this->Height*0.5);
	GameLevel level_2; level_1.Load("levels/2.lvl", this->Width, this->Height*0.5);
	GameLevel level_3; level_1.Load("levels/3.lvl", this->Width, this->Height*0.5);
	GameLevel level_4; level_1.Load("levels/4.lvl", this->Width, this->Height*0.5);
	this->Levels.push_back(level_1);
	this->Levels.push_back(level_2);
	this->Levels.push_back(level_3);
	this->Levels.push_back(level_4);
	this->Level = 0;
	/*��ʼ����Ϸ����*/
	//��ʼ��paddle
	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
	//��ʼ��ball
	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,ResourceManager::GetTexture("face"));

}

//����
void Game::Update(GLfloat dt)
{
	//���¶���
	Ball->Move(dt, this->Width);
	//�����ײ
	this->DoCollisions();
	//��������
	Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2));
	//����±߽磬�ж��Ƿ��������¿�ʼ
	if (Ball->Position.y >= this->Height) 
	{
		this->ResetLevel();
		this->ResetPlayer();
	}
}

//���봦��
void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		GLfloat velocity = PLAYER_VELOCITY * dt;
		// �ƶ���ҵ���
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

//��Ⱦ
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
		glm::vec2(0.0f, 1.0f),  // ��
		glm::vec2(1.0f, 0.0f),  // ��
		glm::vec2(0.0f, -1.0f), // ��
		glm::vec2(-1.0f, 0.0f)  // ��
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

//AABB��ײ���
GLboolean CheckCollision(GameObject &one, GameObject &two)
{
// x�᷽����ײ��
bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
two.Position.x + two.Size.x >= one.Position.x;
// y�᷽����ײ��
bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
two.Position.y + two.Size.y >= one.Position.y;
// ֻ��������������ײʱ����ײ
return collisionX && collisionY;
}

//Բ����ײ���� ��ײ���
Collision CheckCollision(BallObject &one, GameObject &two) // AABB - Circle collision
{
	// ��ȡԲ������ 
	glm::vec2 center(one.Position + one.Radius);
	// ����AABB����Ϣ�����ġ���߳���
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(
		two.Position.x + aabb_half_extents.x,
		two.Position.y + aabb_half_extents.y
	);
	// ��ȡ�������ĵĲ�ʸ��
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// AABB_center����clamped�����͵õ�����ײ���Ͼ���Բ����ĵ�closest
	glm::vec2 closest = aabb_center + clamped;
	// ���Բ��center�������closest��ʸ�����ж��Ƿ� length <= radius
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
			if (std::get<0>(collision)) // ���collision �� true
			{
				// ���ש�鲻��ʵ�ľ�����ש��
				if (!box.IsSolid)
					box.Destroyed = GL_TRUE;
				// ��ײ����
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (dir == LEFT || dir == RIGHT) // ˮƽ������ײ
				{
					Ball->Velocity.x = -Ball->Velocity.x; // ��תˮƽ�ٶ�
														  // �ض�λ
					GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
					if (dir == LEFT)
						Ball->Position.x += penetration; // ��������
					else
						Ball->Position.x -= penetration; // ��������
				}
				else // ��ֱ������ײ
				{
					Ball->Velocity.y = -Ball->Velocity.y; // ��ת��ֱ�ٶ�
														  // �ض�λ
					GLfloat penetration = Ball->Radius - std::abs(diff_vector.y);
					if (dir == UP)
						Ball->Position.y -= penetration; // ��������
					else
						Ball->Position.y += penetration; // ��������
				}
			}
		}
		//������paddle����ײ�����ǿ�ס��
		Collision result = CheckCollision(*Ball, *Player);
		if (!Ball->Stuck && std::get<0>(result))
		{
			// ���������paddle�ĵص㣬������������paddle�ĵص�����ٶ�
			GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
			GLfloat distance = (Ball->Position.x + Ball->Radius) - centerBoard;
			GLfloat percentage = distance / (Player->Size.x / 2);
			// ��Ӧ���ƶ�
			GLfloat strength = 2.0f;
			glm::vec2 oldVelocity = Ball->Velocity;
			Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
			//Ball->Velocity.y = -Ball->Velocity.y;
			Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity); // Keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)															// Fix sticky paddle
			Ball->Velocity.y = -1 * abs(Ball->Velocity.y);
		}
	}
}

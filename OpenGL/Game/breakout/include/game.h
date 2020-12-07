#ifndef GAME_H
#define GAME_H
#include<vector>
#include<tuple>
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include"game_level.h"
#include "ball_object.h"


//游戏状态
enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

//运动方向矢量
enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

// 玩家paddle的初始大小
const glm::vec2 PLAYER_SIZE(100, 20);
// 玩家paddle的初始速度
const GLfloat PLAYER_VELOCITY(500.0f);
// 初始化球的速度
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// 球的半径
const GLfloat BALL_RADIUS = 12.5f;

//碰撞的函数中获取的信息
typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

//游戏类
class Game
{
public:
	GameState State;
	GLboolean Keys[1024];
	GLint Width, Height;
	//关卡
	std::vector<GameLevel> Levels;
	GLuint Level;
	Game(GLint width, GLint Height);
	~Game();
	//初始化
	void Init();
	//处理输入
	void ProcessInput(GLfloat dt);
	//更新
	void Update(GLfloat dt);
	//渲染
	void Render();
	//AABB检测碰撞
	void DoCollisions();
	//死后初始化
	void ResetLevel();
	void ResetPlayer();
};

#endif
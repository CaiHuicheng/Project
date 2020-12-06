#ifndef GAME_H
#define GAME_H

#include<GL\glew.h>
#include<GLFW\glfw3.h>


//游戏状态
enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

//游戏类
class Game
{
public:
	GameState State;
	GLboolean Keys[1024];
	GLint Width, Height;
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
};

#endif
#ifndef GAME_H
#define GAME_H

#include<GL\glew.h>
#include<GLFW\glfw3.h>


//��Ϸ״̬
enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

//��Ϸ��
class Game
{
public:
	GameState State;
	GLboolean Keys[1024];
	GLint Width, Height;
	Game(GLint width, GLint Height);
	~Game();
	//��ʼ��
	void Init();
	//��������
	void ProcessInput(GLfloat dt);
	//����
	void Update(GLfloat dt);
	//��Ⱦ
	void Render();
};

#endif
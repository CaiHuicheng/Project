#ifndef GAME_H
#define GAME_H
#include<vector>
#include<tuple>
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include"game_level.h"
#include "ball_object.h"


//��Ϸ״̬
enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

//�˶�����ʸ��
enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

// ���paddle�ĳ�ʼ��С
const glm::vec2 PLAYER_SIZE(100, 20);
// ���paddle�ĳ�ʼ�ٶ�
const GLfloat PLAYER_VELOCITY(500.0f);
// ��ʼ������ٶ�
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// ��İ뾶
const GLfloat BALL_RADIUS = 12.5f;

//��ײ�ĺ����л�ȡ����Ϣ
typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

//��Ϸ��
class Game
{
public:
	GameState State;
	GLboolean Keys[1024];
	GLint Width, Height;
	//�ؿ�
	std::vector<GameLevel> Levels;
	GLuint Level;
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
	//AABB�����ײ
	void DoCollisions();
	//�����ʼ��
	void ResetLevel();
	void ResetPlayer();
};

#endif
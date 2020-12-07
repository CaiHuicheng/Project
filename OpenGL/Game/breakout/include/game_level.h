#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>

#include <GL/glew.h>
#include <glm.hpp>

#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"


/*
��Ϸ����������д�����Ϊͻ�Ƽ����һ���֣�
�������ܣ���Ӳ���̼���/��Ⱦ����
*/
class GameLevel
{
public:
	// �ؿ�״̬
	std::vector<GameObject> Bricks;
	// ���캯��
	GameLevel() { }
	// ���عؿ��ļ�
	void Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
	// ��Ⱦ�ؿ�
	void Draw(SpriteRenderer &renderer);
	// ���ؿ������Ƿ�����ɣ����з�ʵ����Ƭ�������٣�
	GLboolean IsCompleted();
private:
	// ��ʼ��
	void init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};

#endif
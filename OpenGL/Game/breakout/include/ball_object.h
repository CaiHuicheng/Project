#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include <GL/glew.h>
#include <glm.hpp>

#include "gameTexture.h"
#include "sprite_renderer.h"
#include "game_object.h"

class BallObject : public GameObject
{
public:
	// ��״̬	
	GLfloat   Radius;
	GLboolean Stuck;
	// ���캯��
	BallObject();
	BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);
	// �ƶ���ʹ���ڴ��ڷ�Χ�ڱ���Լ�����ײ���Ե���⣩������������
	glm::vec2 Move(GLfloat dt, GLuint window_width);
	// ʹ�ø���λ�ú��ٶȽ�������Ϊԭʼ״̬
	void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif

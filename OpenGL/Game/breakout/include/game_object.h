#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <glm.hpp>

#include "gameTexture.h"
#include "sprite_renderer.h"


/*
���ڱ����뵥����ص�����״̬����������

��Ϸ����ʵ�塣��Ϸ�е�ÿ�����������Ҫ

��Ϸ��������������С״̬��
*/
class GameObject
{
public:
	// ״̬
	glm::vec2   Position, Size, Velocity;
	glm::vec3   Color;
	GLfloat     Rotation;
	GLboolean   IsSolid;
	GLboolean   Destroyed;
	// ��ɫ��״̬
	Texture2D   Sprite;
	// ����
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	// ��Ⱦ
	virtual void Draw(SpriteRenderer &renderer);
};

#endif
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <glm.hpp>

#include "gameTexture.h"
#include "sprite_renderer.h"


/*
用于保持与单个相关的所有状态的容器对象

游戏对象实体。游戏中的每个对象可能需要

游戏对象中描述的最小状态。
*/
class GameObject
{
public:
	// 状态
	glm::vec2   Position, Size, Velocity;
	glm::vec3   Color;
	GLfloat     Rotation;
	GLboolean   IsSolid;
	GLboolean   Destroyed;
	// 着色器状态
	Texture2D   Sprite;
	// 构造
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	// 渲染
	virtual void Draw(SpriteRenderer &renderer);
};

#endif
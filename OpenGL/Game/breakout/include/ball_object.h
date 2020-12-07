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
	// 球状态	
	GLfloat   Radius;
	GLboolean Stuck;
	// 构造函数
	BallObject();
	BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);
	// 移动球，使球在窗口范围内保持约束（底部边缘除外），返回球坐标
	glm::vec2 Move(GLfloat dt, GLuint window_width);
	// 使用给定位置和速度将球重置为原始状态
	void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif

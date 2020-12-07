#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>

#include <GL/glew.h>
#include <glm.hpp>

#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"


/*
游戏级别持有所有磁贴作为突破级别的一部分，
主机功能，从硬磁盘加载/渲染级别。
*/
class GameLevel
{
public:
	// 关卡状态
	std::vector<GameObject> Bricks;
	// 构造函数
	GameLevel() { }
	// 加载关卡文件
	void Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
	// 渲染关卡
	void Draw(SpriteRenderer &renderer);
	// 检查关卡加载是否已完成（所有非实体切片都已销毁）
	GLboolean IsCompleted();
private:
	// 初始化
	void init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};

#endif
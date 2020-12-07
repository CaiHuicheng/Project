#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GL\glew.h>
#include <glm.hpp>
#include<gtc/matrix_transform.hpp>

#include"gameShader.h"
#include"gameTexture.h"


class SpriteRenderer {
public:
	SpriteRenderer(Shader &shapes);
	~SpriteRenderer();
	void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
	Shader shader;
	GLuint quadVAO;
	void initRenderData();
};

#endif // !SPRITE_RENDERER_H

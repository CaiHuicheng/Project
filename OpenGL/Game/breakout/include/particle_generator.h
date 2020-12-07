#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include <vector>

#include <GL/glew.h>
#include <glm.hpp>

#include "gameShader.h"
#include "gameTexture.h"
#include "game_object.h"


// ��ʾ�������Ӽ���״̬
struct Particle {
	glm::vec2 Position, Velocity;
	glm::vec4 Color;
	GLfloat Life;

	Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};


/*
�����������䵱������������Ⱦ����

����ͨ���������ɺ͸������Ӻ�ɱ��

�����ڸ�����ʱ������
*/
class ParticleGenerator
{
public:
	// ����
	ParticleGenerator(Shader shader, Texture2D texture, GLuint amount);
	// ˢ����������
	void Update(GLfloat dt, GameObject &object, GLuint newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	// ��Ⱦ��������
	void Draw();
private:
	// ״̬
	std::vector<Particle> particles;
	GLuint amount;
	// ��ɫ��״̬
	Shader shader;
	Texture2D texture;
	GLuint VAO;
	// ��ʼ���������Ͷ�������
	void init();
	// ���ص�ǰδʹ�õĵ�һ���������� Life <= 0.0f or 0 ���û�����ӵ�ǰ���ڷǻ״̬
	GLuint firstUnusedParticle();
	// ��������
	void respawnParticle(Particle &particle, GameObject &object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};

#endif

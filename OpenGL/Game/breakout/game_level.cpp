#include "include\game_level.h"

#include <fstream>
#include <sstream>


void GameLevel::Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight)
{
	// ��������
	this->Bricks.clear();
	// ���عؿ��ļ�
	GLuint tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> tileData;
	if (fstream)
	{
		while (std::getline(fstream, line)) // ��ȡһ��
		{
			std::istringstream sstream(line);
			std::vector<GLuint> row;
			while (sstream >> tileCode) // ���ո�����Ķ�ÿ������
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
			this->init(tileData, levelWidth, levelHeight);
	}
}

void GameLevel::Draw(SpriteRenderer &renderer)
{
	for (GameObject &tile : this->Bricks)
		if (!tile.Destroyed)
			tile.Draw(renderer);
}

GLboolean GameLevel::IsCompleted()
{
	for (GameObject &tile : this->Bricks)
		if (!tile.IsSolid && !tile.Destroyed)
			return GL_FALSE;
	return GL_TRUE;
}

void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight)
{
	// ����size
	GLuint height = tileData.size();
	GLuint width = tileData[0].size(); // ��ע�⣬���ǿ����� {0} ������ʸ������Ϊֻ���ڸ߶�> 0 ʱ
	GLfloat unit_width = levelWidth / static_cast<GLfloat>(width), unit_height = levelHeight / height;
	// ��tileDataΪ������ʼ������		
	for (GLuint y = 0; y < height; ++y)
	{
		for (GLuint x = 0; x < width; ++x)
		{
			// ���level �� ��ļ���
			if (tileData[y][x] == 1) // ����
			{
				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				GameObject obj(pos, size, ResourceManager::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
				obj.IsSolid = GL_TRUE;
				this->Bricks.push_back(obj);
			}
			else if (tileData[y][x] > 1)	// �ǹ���;���ڸ��ݼ�������ȷ������ɫ

			{
				glm::vec3 color = glm::vec3(1.0f); // ��ɫ
				if (tileData[y][x] == 2)
					color = glm::vec3(0.2f, 0.6f, 1.0f);
				else if (tileData[y][x] == 3)
					color = glm::vec3(0.0f, 0.7f, 0.0f);
				else if (tileData[y][x] == 4)
					color = glm::vec3(0.8f, 0.8f, 0.4f);
				else if (tileData[y][x] == 5)
					color = glm::vec3(1.0f, 0.5f, 0.0f);

				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				this->Bricks.push_back(GameObject(pos, size, ResourceManager::GetTexture("block"), color));
			}
		}
	}
}
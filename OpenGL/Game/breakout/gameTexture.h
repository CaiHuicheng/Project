#ifndef GAMETEXTURE_H
#define GAMETEXTURE_H

#include<GL/glew.h>


class Texture2D
{
public:
	//������������ ID����������������������ô˲�������
	GLuint ID;
	/*����ͼ��ߴ�
	  ����ͼ��Ŀ�Ⱥ͸߶ȣ�������Ϊ��λ��*/
	GLuint Width, Height;
	/*
	�����ʽ
	�������ĸ�ʽ
	����ͼ��ĸ�ʽ
	*/
	GLuint Internal_Format;
	GLuint Image_Format;
	/*
	��������
	S ���ϵĻ���ģʽ
	T ���ϵĻ���ģʽ
	*/
	GLuint Wrap_S;
	GLuint Wrap_T;
	/*
	ɸѡģʽ
	���������������Ļ<
	����������غ���Ļ���أ���>
	*/
	GLuint Filter_Min;
	GLuint Filter_Max;
	//���캯��������Ĭ������ģʽ��
	Texture2D();
	//��ͼ��������������
	void Generate(GLuint width, GLuint height, unsigned char* data);
	//�������Ϊ��ǰ�GL_TEXTURE_2D�������
	void Bind() const;
};

#endif // !GAMETEXTRUE_H

#ifndef GAMETEXTURE_H
#define GAMETEXTURE_H

#include<GL/glew.h>


class Texture2D
{
public:
	//保存纹理对象的 ID，用于所有纹理操作以引用此部分纹理
	GLuint ID;
	/*纹理图像尺寸
	  加载图像的宽度和高度（以像素为单位）*/
	GLuint Width, Height;
	/*
	纹理格式
	纹理对象的格式
	加载图像的格式
	*/
	GLuint Internal_Format;
	GLuint Image_Format;
	/*
	纹理配置
	S 轴上的环绕模式
	T 轴上的环绕模式
	*/
	GLuint Wrap_S;
	GLuint Wrap_T;
	/*
	筛选模式
	如果纹理像素与屏幕<
	如果纹理像素和屏幕像素，则>
	*/
	GLuint Filter_Min;
	GLuint Filter_Max;
	//构造函数（设置默认纹理模式）
	Texture2D();
	//从图像数据生成纹理
	void Generate(GLuint width, GLuint height, unsigned char* data);
	//将纹理绑定为当前活动GL_TEXTURE_2D纹理对象
	void Bind() const;
};

#endif // !GAMETEXTRUE_H

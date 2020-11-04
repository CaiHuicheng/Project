/******************************************************************
���ܣ�ʶ������״̬��صĺ���
˵����
******************************************************************/


/****************************** �ж��۾�״̬ ************************************************
���ܣ�ͨ��ģ���ۺ����۵�˼���ж��۾���״̬
���룺
	double MinEyeballRectShape���۾���������ĳ����
	double MinEyeballBlackPixelRate���۾�������������ص���ռ�ı���
	double MinEyeballBeta���۾�����1/2�����ɫ���ص�ռ�ܺ����ص�ı���
�����
	�������������պϵ�״̬0��������1���պ�

˵����
	1. ���������������ֵ���Լ��趨��
	2. ����Ľ����������ֵ��Ҫ����
	3. Ϊ��תӲ�����㣬�ӿ������ٶȣ�����������תΪ���������㡣
********************************************************************************************/
#include<opencv2/imgproc.hpp>

int getEyeState(double MinEyeballRectShape, double MinEyeballBlackPixelRate, double MinEyeballBeta)
{
	int eyeState;
	int funcResult;
	int shapeFuzzyLv, pixelFuzzyLv, betaFuzzyLv;	// ����������Ӧ��ģ�������ֵ

	// �ж��۾���������ĳ���ȵ�ģ������
	shapeFuzzyLv = 0;
	if( (MinEyeballRectShape >= 0) && (MinEyeballRectShape <= 0.8) )
		shapeFuzzyLv = 0;
	else if( MinEyeballRectShape <= 1.2 )
		shapeFuzzyLv = 2;
	else if( MinEyeballRectShape <= 1.5 )
		shapeFuzzyLv = 6;
	else if( MinEyeballRectShape <= 2.5 )
		shapeFuzzyLv = 8;
	else if( MinEyeballRectShape <= 3 )
		shapeFuzzyLv = 6;
	else
		shapeFuzzyLv = 0;

	// �ж��۾�������������ص���ռ������ģ������
	pixelFuzzyLv = 0;
	if( (MinEyeballBlackPixelRate >= 0) && (MinEyeballBlackPixelRate <= 0.4) )
		pixelFuzzyLv = 0;
	else if( MinEyeballBlackPixelRate <= 0.50 )
		pixelFuzzyLv = 2;
	else if( MinEyeballBlackPixelRate <= 0.60 )
		pixelFuzzyLv = 6;
	else if( MinEyeballBlackPixelRate <= 1 )
		pixelFuzzyLv = 8;

	// �ж��۾�����1/2�����ɫ���ص�ռ�ܺ����ص�ı�����ģ������
	betaFuzzyLv = 0;
	if( (MinEyeballBeta >= 0) && (MinEyeballBeta <= 0.3) )
		betaFuzzyLv = 0;
	else if( MinEyeballBeta <= 0.45 )
		betaFuzzyLv = 2;
	else if( MinEyeballBeta <= 0.6 )
		betaFuzzyLv = 6;
	else if( MinEyeballBeta <= 1 )
		betaFuzzyLv = 8;

	// ģ�����ۺ���
	eyeState = 1;		// Ĭ���Ǳ��۵�
	funcResult = 2 * shapeFuzzyLv + 4 * pixelFuzzyLv + 4 * betaFuzzyLv;
	if( funcResult >= 58 )
		eyeState = 0;

	return eyeState;
}


int FuzPatternRecoEyeState(double MinEyeballRectShape, double MinEyeballBlackPixelRate, double MinEyeballBeta)
{
	int eyeState;
	double openEyeFunResult, closeEyeFunResult;
	double R, alpha, beta;	// ����������Ӧ��ģ�������ֵ

	/*************** ��������ʱ�������ģ������ֵ֮�� ******************/
	////////////////R
	R = 0;
	if( (MinEyeballRectShape < 0.5) && (MinEyeballRectShape >= 3) )
		R = 0;
	else if( (MinEyeballRectShape >= 0.5) && (MinEyeballRectShape < 1.5) )
		R = MinEyeballRectShape - 0.5;
	else if( (MinEyeballRectShape >= 1.5) && (MinEyeballRectShape < 2.5) )
		R = 1;
	else if( MinEyeballRectShape < 3 )
		R = (3 - MinEyeballRectShape) / 0.5;

	////////////////alpha
	alpha = 0;
	if( MinEyeballBlackPixelRate < 0.4 )
		alpha = 0;
	else if( MinEyeballBlackPixelRate <= 0.6 )
		alpha = (MinEyeballBlackPixelRate - 0.4) / 0.2;
	else
		alpha = 1;

	////////////////beta
	beta = 0;
	if( MinEyeballBeta < 0.3 )
		beta = 0;
	else if( MinEyeballBeta <= 0.6 )
		beta = (MinEyeballBeta - 0.3) / 0.3;
	else
		beta = 1;

	// ��������ģ������ֵ֮��
	openEyeFunResult = R + alpha + beta;

	/*************** �������ʱ�������ģ������ֵ֮�� ******************/
	////////////////R
	R = 0;
	if( MinEyeballRectShape < 0.8 )
		R = 1;
	else if( MinEyeballRectShape <= 1.5 )
		R = (2.5 - MinEyeballRectShape) / 0.7;
	else if( MinEyeballRectShape < 2.5 )
		R = 0;
	else 
		R = 1;

	// ��������ģ������ֵ֮��
	closeEyeFunResult = R + (1 - alpha) + (1 - beta);

	
	if( openEyeFunResult >= closeEyeFunResult )
		eyeState = 0;
	else
		eyeState = 1;
	
	printf("openEyeFunResult:%f\tcloseEyeFunResult:%f\n", openEyeFunResult, closeEyeFunResult);

	return eyeState;
}


/****************************** �ж��۾�״̬ ************************************************
���ܣ�ͳ��lMinEyeballImg�е�1/2�����ں����صı���
���룺
	int* vertProject����ֱͶӰ���
	CvRect* eyeRect����С�ۿ�������
	int width����ֱͶӰ���еĳ���
	int eyeCol����С�ۿ��к�Ĥ���������ڵ�����
	int MinEyeballBlackPixel����С�ۿ��еĺ�����������
�����
	double MinEyeballBeta���۾�����1/2�����ɫ���ص�ռ�ܺ����ص�ı���

˵����
********************************************************************************************/

double calMiddleAreaBlackPixRate(int* vertProject, CvRect* eyeRect, int width, int height, int eyeCol, int MinEyeballBlackPixel)
{
	// ����
	int temp, temp1, count, i;
	double MinEyeballBeta;
	temp1 = 0;				// �м�1/2����İ����ظ���
	temp = 0;				// �м�1/2����ĺ����ظ���
	count = 0;				// ��ʱ����
	MinEyeballBeta = 0;	// ��ʼ���м�1/2����ĺ����صı���
	if( width >= 8 ){
		temp = eyeCol - eyeRect->x;// ��С�ۿ��ĺ�Ĥ���ĵ����ڵ���
		// ����if else �Ǳ����Դ���
		if( width / 2 > temp ){
			// ��ֹ��߽�Խ������
			count = temp + width / 4;
			temp1 = temp - width / 4;
			if( temp1 < 0 )
				i = 0;
			else
				i = temp1;
		}
		else{
			// ��ֹ�ұ߽�Խ������
			i = temp - width / 4;
			temp1 = temp + width / 4;
			if( temp1 < width )
				count = temp1;
			else
				count = width;
		}
		temp1 = 0;
		temp = 0;
		for( ; i < count; i ++ )
			temp1 += *(vertProject + i);
		temp1 /= 255;
		temp = height * (width / 2) - temp1;								// �м�1/2����ĺ����ظ���
		MinEyeballBeta = (double)temp / (double)MinEyeballBlackPixel;		// �м�1/2����ĺ�����ռ���к����صı���
	}
	else{
		MinEyeballBeta = 0;
	}

	return MinEyeballBeta;
}

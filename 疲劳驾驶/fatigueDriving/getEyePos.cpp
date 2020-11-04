/************************************************************
���ܣ��ҳ��������޶������ڵ���͵��λ��
���룺
	int* project:  ����
	int size: ���еĳ���
	int region: �м�����ķ�Χ
�����
	����int���λ��, ����ʱ����-1
˵����
	1. û�п�����ͬͶӰֵ���ǲ�ͬindex�������ô������
	2. �ɿ��Ǽ���ԭͼ�����������ͷ����Ƭ��ͼ���Ӱ�죡��
************************************************************/

#include<opencv2/imgproc.hpp>
#include <stdlib.h>


typedef struct
{
	int data;
	int index; 
}projectArr;

// qsort�ĺ�������
int cmpInc( const void *a ,const void *b)
{
	return (*(projectArr *)a).data - (*(projectArr *)b).data;
}


int getEyePos(int* project, int size, int region)
{
	// ����
	projectArr* projectStruct = NULL;
	projectArr* projectTemp = NULL;
	int i, j, pos, sizeTemp, temp;

	// ����projectStruct�ڴ�ռ�
	projectStruct = (projectArr*)malloc(size * sizeof(projectArr));
	projectTemp = (projectArr*)malloc(sizeof(projectArr));

	// ��ʼ���ڴ�ռ�
	for(i = 0; i < size; i ++){
		(projectStruct + i)->data  = *(project + i);
		(projectStruct + i)->index  = i;
	}

	// ��project��С�����������
	//qsort(projectStruct, size, sizeof(*project), cmpInc);
	for(i = 0; i <= size - 2; i ++){
		for( j = 0; j < size - i - 1; j ++ ){
			if( (projectStruct + j)->data > (projectStruct + j + 1)->data ){
				*projectTemp = *(projectStruct + j);
				*(projectStruct + j) = *(projectStruct + j + 1);
				*(projectStruct + j + 1) = *projectTemp;
			}
		}
	}

	// Ѱ���м��������Сֵ����λ��
	sizeTemp = size / 2;
	temp = 0;
	for( i = 0; i < size; i ++ ){
		temp = (projectStruct+i)->index;
		if( (temp > sizeTemp - region) && (temp < sizeTemp + region) ){
			pos = (projectStruct + i)->index;
			// ��ָֹ��Խ�����λ��Ԫ�س��ָ���
			if( pos < 0)
				return -1;
			break;
		}
		else{
			// ��ֹ�������в����ڷ���������Ԫ��
			if( i == size - 1 )
				return -1;
		}
	}

	//free(projectStruct);
	free(projectTemp);
	return pos;
}


/************************************************************
���ܣ���������ͶӰͼ�е���͵㣬�Ӷ�����üë�ĺ���
���룺
	int* horiProject: ���е�ָ��
	int width:  ���еĿ��
	int height: ���еĸ߶�
	int threshold���ָ�üë����ֵ�����
�����
	�����ҵ�����͵���λ�ã����Ϊint���ͣ���üë���۾��ķָ���
˵����
		1. ����üëʱ���Ե���eyeBrowThreshold������ȥ����Ч��
		2. ͬʱ���Ե�������������ֵ�Ĵ���count������Ч����
************************************************************/

int removeEyebrow(int* horiProject, int width, int height, int threshold)
{
	//  ����
	int temp, temp1, count, flag, i;
	int eyeRow;
	int eyeBrowThreshold;

	// ��λ����λ��
	eyeBrowThreshold = (width - threshold) * 255;			// Ϊ�˷�ֹ�޷������۾���üë����������ʵ�������ֵ

	// ����üë����
	temp = 100000000;
	temp1 = 0;
	count = 0;
	flag = 0;										// ��ʾ��ǰ������λ���ڵ�һ����͹�֮ǰ
	eyeRow = 0;
	for(i = 0; i < height; i = i + 3){
		count ++;
		// �൱�ڵ����˲�
		temp1 = *(horiProject + i) + *(horiProject + i + 1) + *(horiProject + i + 2);
		if( (temp1 < temp) & (flag == 0) ){
			temp = temp1;
			eyeRow = i;
			count = 0;
		}
		if (count >= 3 || i >= height - 2){
			flag = 1;
			break;
		}
	}

	// ������һ�������۾���üë�ָ���ֵ�ĵ�
	count = 0;
	for( i = eyeRow; i < height; i ++ ){
		if( *(horiProject + i) > eyeBrowThreshold){
			eyeRow = i;
			count ++;
			if( count >= 3 ){				// count: ͳ�ƹ��ж����������е�ͶӰֵ������ֵ��
				eyeRow = i;
				break;
			}
		}
		else
			count = 0;
	}

	// ��ֹû��üë��ɾ�۾���������ɸ���ʵ��������������
	if( eyeRow >= height / 2 )
		eyeRow = 0;

	return eyeRow;
}

/************************************************************
���ܣ��ض����ܺ������������۵����Ĵ��¼����ۿ�������
���룺
	CvRect* eyeRect: �ۿ����������ָ��
	int width:  ���еĿ��
	int height: ���еĸ߶�
	int EyeCol����Ĥ�������ڵ���λ��
	int EyeRow����Ĥ�������ڵ���λ��
�����
	��ָ��ķ�ʽ�����ۿ��Ĵ�������eyeRect
************************************************************/

void calEyeSocketRegion(CvRect* eyeRect, int width, int height, int EyeCol, int EyeRow)
{
	// ����
	int temp, temp1;
	temp = EyeCol - width / 4;
	temp1 = EyeRow - height / 4;
	if( (temp < 0) && (temp1 < 0) ){
		eyeRect->x = 0;
		eyeRect->width = width / 2 + temp;
		eyeRect->y = 0;
		eyeRect->height = height / 2 + temp1;
	}
	else if( (temp < 0) && (temp1 > 0) ){
		eyeRect->x = 0;
		eyeRect->width = width / 2 + temp;
		eyeRect->y = temp1;
		eyeRect->height = height / 2;
	}
	else if( (temp > 0) && (temp1 < 0) ){
		eyeRect->x = temp;
		eyeRect->width = width / 2;
		eyeRect->y = 0;
		eyeRect->height = height / 2 + temp1;
	}
	else if( (temp > 0) && (temp1 > 0) ){
		eyeRect->x = temp;
		eyeRect->width = width / 2;
		eyeRect->y = temp1;
		eyeRect->height = height / 2;
	}
}

/************************************************************
���ܣ��ض����ܺ���������������С�ľ�������
���룺
	CvRect* eyeRect: ������С�ľ��������ָ��
	int* horiProject
	int* vertProject
	int width:  ���еĿ��
	int height: ���еĸ߶�
	int horiThreshold��ˮƽ�������ֵ
	int vertThreshold����ֱ�������ֵ
�����
	ͨ��ָ�뷵��CvRect* eyeRect: ������С�ľ��������ָ��
************************************************************/

void getEyeMinRect(CvRect* eyeRect, int* horiProject, int* vertProject, int width, int height, int horiThreshold=5, int vertThreshold=3)
{
	// ����
	int temp, temp1, i;

	temp1 = (width - horiThreshold) * 255;
	for(i = 0; i < height; i ++){
		if( *(horiProject + i) < temp1 ){
			eyeRect->y = i;
			break;
		}
	}
	temp = i;				// ��¼eyeRectTemp.y��λ��
	//printf("eyeRectTemp->y: %d\n", eyeRect->y);

	if( temp != height ){	
	// temp != HEIGHT: ��ֹû�з���*(subhoriProject + i) < temp1������λ�ã����temp != HEIGHT��һ��������������λ�ô���
		for(i = height-1; i >= 0; i --){
			if( *(horiProject + i) < temp1 ){
				temp = i;
				break;
			}
		}
		if( temp == eyeRect->y )
			eyeRect->height = 1;
		else
			eyeRect->height = temp - eyeRect->y;
	}
	else{
		eyeRect->height = 1;
	}
	//printf("eyeRectTemp.height: %d\n", eyeRect->height);
	
	temp1 = (height - vertThreshold) * 255;
	for( i = 0; i < width; i ++ ){
		if( *(vertProject + i) < temp1 ){
			eyeRect->x = i;
			break;
		}
	}
	temp = i;			// ��¼eyeRectTemp.x��λ��
	//printf("eyeRectTemp.x: %d\n", eyeRect->x);

	if( temp != width ){
		for(i = width-1; i >= 0; i --){
			if( *(vertProject + i) < temp1 ){
				temp = i;
				break;
			}
		}
		// ��ֹ���Ϊ0����ʾͼ��ʱ����
		if( temp == eyeRect->x )
			eyeRect->width = 1;
		else
			eyeRect->width = temp - eyeRect->x;
	}
	else{
		eyeRect->width = 1;
	}
	//printf("eyeRectTemp.width: %d\n", eyeRect->width);
}

/*************************************************
���ܣ��ض����ܺ������������۾��պ�״̬���Ƿ��⵽����
					  �жϼ�ʻ״̬��������ƣ�ͣ�
���룺
	int eyeCloseNum�����������۾���״̬���ܴ���
	int maxEyeCloseDuration�����������۾������պϵ�������
	int failFaceNum����������δ��⵽�������ܴ���
	int maxFailFaceDuration��������������δ��⵽������������
˵����
**************************************************/
#include <stdio.h>

int eyeCloseNumTab[] = {2,2,4,6,9,14,20,29,39,50,61,72,80,86,91,94,96,98,98,99,99,100,100,100,100,100,100,100,100,100, 100};
int eyeCloseDurationTab[] = {2, 4, 9, 18, 32, 50, 68, 82, 91, 95, 98, 99, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
int failFaceDurationTab[] = {2, 6, 14, 29, 50, 71, 86, 94, 98, 99, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

int recoFatigueState(int thresh, int eyeCloseNum, int maxEyeCloseDuration, int failFaceNum, int maxFailFaceDuration)
{
	int eyeCloseValue;				// �۾��պϴ����Ĺ���ֵ
	int eyeCloseDurationValue;		// �۾������պϴ����Ĺ���ֵ
	int failFaceValue;				// δ��⵽�������ܴ����Ĺ���ֵ
	int failFaceDurationValue;		// ����δ��⵽�����Ĺ���ֵ
	int compreValue;				// �ۺϹ���ֵ

	// �������ĸ�ָ��Ĺ���ֵ
	eyeCloseValue = eyeCloseNumTab[eyeCloseNum];
	eyeCloseDurationValue = eyeCloseDurationTab[maxEyeCloseDuration];
	failFaceValue = eyeCloseNumTab[failFaceNum];
	failFaceDurationValue = failFaceDurationTab[maxFailFaceDuration];
	// �ۺϹ���ֵ
	compreValue = eyeCloseValue + eyeCloseDurationValue + failFaceValue + failFaceDurationValue;

	printf("\neyeCloseValue: %d\n", eyeCloseValue);
	printf("eyeCloseDurationValue: %d\n", eyeCloseDurationValue);
	printf("failFaceValue: %d\n", failFaceValue);
	printf("failFaceDurationValue: %d\n", failFaceDurationValue);
	printf("compreValue: %d\n\n", compreValue);

	return (compreValue >= thresh) ? 1 : 0;
}

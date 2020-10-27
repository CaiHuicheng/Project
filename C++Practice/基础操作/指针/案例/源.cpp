#include<iostream>
using namespace std;

void bubbleSort(int * arr ,int len) {
	for (int  i = 0; i < len; i++)
	{
		for (int j = 0; j < len - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}

	}
}

void printArray(int * arr, int len) {
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << endl;
	}
}

int main() {
	int arr[10] = { 4,3,18,29,40,56,71,2,10,1 };
	int len = sizeof(arr) / sizeof(arr[0]);

	bubbleSort(arr, len);
	printArray(arr, len);
	system("pause");
	return 0;
}
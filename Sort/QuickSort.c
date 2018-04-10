#include <stdio.h>

void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int Partition(int *data, int left, int right)
{
	int first = left; //처음 left 자리를 기억하고 있는다.
	int pivot = data[first];

	while (1)
	{
		while (data[left] <= pivot && left < right) //pivot보다 큰 값을 찾으면 정지
			left++;
		while (data[right] > pivot && left <= right)//pivot보다 작거나 같은 값을 찾으면 정지
			right--;

		if (left < right) //left보다 right가 큰 경우(L 홀드와 R 홀드를 찾았다) 스왑
			Swap(&data[left], &data[right]);
		else
			break;
	}

	Swap(&data[first], &data[right]); //pivot의 자리를 찾아 스왑해준다.

	return right;
}

void QuickSort(int *data, int left, int right)
{
	if (left < right)
	{
		int index = Partition(data, left, right);
		QuickSort(data, left, index - 1);
		QuickSort(data, index + 1, right);
	}
}

int main()
{
	int data[10] = { 5,1,3,11,2,9,4,30,7,6 };
	int len = sizeof(data) / sizeof(data[0]);

	for (int i = 0; i<len; i++)
	{
		printf("%d ", data[i]);
	}
	printf("\n");

	QuickSort(data, 0, len - 1);

	for (int i = 0; i<len; i++)
	{
		printf("%d ", data[i]);
	}
	printf("\n");

	return 0;
}
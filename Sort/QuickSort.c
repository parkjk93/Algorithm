#include <stdio.h>

void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int Partition(int *data, int left, int right)
{
	int first = left; //ó�� left �ڸ��� ����ϰ� �ִ´�.
	int pivot = data[first];

	while (1)
	{
		while (data[left] <= pivot && left < right) //pivot���� ū ���� ã���� ����
			left++;
		while (data[right] > pivot && left <= right)//pivot���� �۰ų� ���� ���� ã���� ����
			right--;

		if (left < right) //left���� right�� ū ���(L Ȧ��� R Ȧ�带 ã�Ҵ�) ����
			Swap(&data[left], &data[right]);
		else
			break;
	}

	Swap(&data[first], &data[right]); //pivot�� �ڸ��� ã�� �������ش�.

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
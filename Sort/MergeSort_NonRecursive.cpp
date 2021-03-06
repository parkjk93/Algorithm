#include <queue>
#include <iostream>

#define SIZE 100

using namespace std;

int* Merge(int *ldata, int llength, int *rdata, int rlength)
{
	int* temp = new int[llength + rlength + 1];
	temp[0] = llength + rlength;

	int l = 1;
	int r = 1;
	int t = 1;

	while ((ldata[0] != 0) || (rdata[0] != 0))
	{
		if (ldata[0] == 0)
		{
			temp[t] = rdata[r];
			t++;
			r++;
			rdata[0] -= 1;
		}
		else if (rdata[0] == 0)
		{
			temp[t] = ldata[l];
			t++;
			l++;
			ldata[0] -=1;
		}
		else
		{
			if (ldata[l] < rdata[r])
			{
				temp[t] = ldata[l];
				t++;
				l++;
				ldata[0] -= 1;
			}
			else
			{
				temp[t] = rdata[r];
				t++;
				r++;
				rdata[0] -= 1;
			}
		}
	}

	return temp;
}

int main()
{
	queue<int*> Queue;

	//Init Queue
	for (int i=0 ; i<SIZE ; i++)
	{
		int *a = new int[2];
		a[0] = 1;
		a[1] = SIZE-i;
		Queue.push(a);
	}

	while (Queue.size() != 1)
	{
		cout << "left : ";
		for (int i=1 ; i<Queue.front()[0]+1 ; i++)
		{
			 cout << Queue.front()[i] << " ";
		}
		cout << endl;

		int Llength = Queue.front()[0];
		int *Ldata = Queue.front();

		Queue.pop(); cout << "right : ";
		for (int i = 1; i<Queue.front()[0]+1; i++)
		{
			cout << Queue.front()[i] << " ";
		}
		cout << endl;

		int Rlength = Queue.front()[0];
		int *Rdata = Queue.front();
		Queue.pop();

		Queue.push(Merge(Ldata, Llength, Rdata, Rlength));
	}
	
	cout << endl << "SORTED DATA" << endl;
	for (int j=1 ; j<Queue.front()[0]+1 ; j++)
	{
		cout << Queue.front()[j] << " ";
	}
	cout << endl;
	
    return 0;
}
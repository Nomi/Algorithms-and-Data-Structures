#include <iostream>
#include <stdlib.h>
#include <list>
#include <iterator>

using namespace std;

void printarr(int size, int A[], int seperatingind=-1);
void heapify(int[], int, int);
void arrayswap(int[], int i, int j);
void buildheap(int, int[]);

int main()
{
	int A[] = { 2, 4, 1, 3, 5, 7, 6 };
	int size = sizeof(A) / sizeof(int);		//could have used sizeof(A[0]) if data type was to be changed
	if (size > 100)
	{
		cout << "Maximum size for array is 100. Maximum size exceeded. Exiting.";
		return -1;
	}



	cout << "The array given as input is:   " << endl;;
	printarr(size, A);
	buildheap(size, A);

	cout << endl << endl;

	cout << "Initially, heap looks like:    "<<endl;
	printarr(size, A);

	cout << endl << endl;

	for (int i = size - 1; i >= 1; i--)
	{
		arrayswap(A, i, 0);
		heapify(A, i, 0);
		cout << "After deleting, we have:      " << endl;
		printarr(size, A, i - 1);
	}

	cout <<endl<< endl;

	cout << "Finally, we have:     "<<endl;
	printarr(size, A);

	return 0;
}




//Function definitions start:











void printarr(int size, int A[], int separatingind)
{
	cout << '[';

	for (int i = 0; i < size; i++)
	{
		cout << A[i];

		if (i + 1 < size)
		{
			if (separatingind != i)
			{
				cout << ", ";
			}
			else
			{
				cout << '|';
			}
		}
	}
	cout << "]" << endl;
}

void heapify(int A[], int size, int maxindex)
{
	int currentindex;

	do
	{
		currentindex = maxindex;
		int maxvalue = A[maxindex];

		if (currentindex * 2 + 1 < size)
		{
			int currentvalue = A[currentindex * 2 + 1];

			if (currentvalue > maxvalue)
			{
				maxindex = currentindex * 2 + 1;
				maxvalue = currentvalue;
			}
		}

		if (currentindex * 2 + 2 < size)
		{
			int currentvalue = A[currentindex * 2 + 2];

			if (currentvalue > maxvalue)
			{
				maxindex = currentindex * 2 + 2;
				maxvalue = currentvalue;
			}
		}

		if (currentindex != maxindex)
			arrayswap(A, currentindex, maxindex);

	} while (currentindex != maxindex);
}


void arrayswap(int A[], int i, int j)
{
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

void buildheap(int size, int A[])
{
	for (auto i = size / 2; i >= 0; i--)
	{
		heapify(A, size, i);
	}
}
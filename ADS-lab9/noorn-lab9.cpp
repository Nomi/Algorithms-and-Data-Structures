#include <iostream>
#include <stdlib.h>
#include <list>
#include <iterator>

using namespace std;



list<int>::iterator nthelementoflist(list<int>* list, int n) //nth element starting from n=0;
{
	auto nitr = list->begin();
	advance(nitr, n);
	return nitr;
}

void printArray(int*,int);

void swap(int*, int*);

void quickSort(int*, int, int);

int partition(int*, int, int);


int main(void)
{
	int input[] = {5, 1, 4, 8, 9, 3, 7, 6, 2}; const int size = 9; //C++17 Doesn't support old methods of finding size.
	cout << "Input List: ";
	printArray(input,size);

//	int size = *(&input + 1) - input;
	quickSort(input, 0, (size - 1));

	cout << "Final list: ";
	printArray(input,size);
	cout << endl;
	return 0;
}






void printArray(int* arr, int size)
{
//	int size = *(&arr + 1) - arr;

	for (int i = 0; i < size; i++)
	{
		if (i != 0) 
			cout << ',';
		cout << arr[i];
		if (i == (size - 1)) 
			cout << '.' << endl;
	}
	cout << endl;
}


void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void quickSort(int* toSort, int p, int r)
{
	while(p<r)
	{
		
		int index = partition(toSort, p, r);
		quickSort(toSort, p+1, index);
		cout << endl;
		printArray(toSort, r - p + 1);
		cout << endl;
		p = (index + 1);
	}
}


int partition(int* toSort, int p, int r)
{
	int pivot = toSort[p];
	int i = (p - 1); 
	for (int j = p; j <= r; j++)
	{
		if (toSort[j] < pivot)//BUG: && j!=i+1 ??
		{
			i++;
			swap(&(toSort[i]), &toSort[j]);
		}
	}
	i += 1;
	swap(&toSort[i], &toSort[r]);
	return i;
}
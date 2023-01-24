#include <iostream>
#include <stdlib.h>
#include <list>
#include <iterator>

using namespace std;

/* My ideas:
i=0 i++ {} a[i]>a[i+gap] => Swap 
|Note: Only while a[i+gap] exists|, gap=floor(gap/2)
if gap=0, use insertion sort. index can be replaced to work with list.
*/


void shellsort(list<int>*, int[],int);
list<int>::iterator nthelementoflist(list<int>* list, int n) //nth element starting from n=0;
{
	auto nitr = list->begin();
	advance(nitr, n);
	return nitr;
}


void printlist(list<int> list)
{
	for (auto i : list) 
	{
		std::cout << i << ", ";
	}
	cout << endl;
}



int main(void)
{
	list<int> wow1; list<int> wow2;
	wow1.emplace_back(4);
	wow1.emplace_back(1);
	wow1.emplace_back(7);
	wow1.emplace_back(3);
	wow1.emplace_back(9);
	wow1.emplace_back(2);
	wow1.emplace_back(5);
	wow2.emplace_back(4);
	wow2.emplace_back(1);
	wow2.emplace_back(7);
	wow2.emplace_back(3);
	wow2.emplace_back(9);
	wow2.emplace_back(2);
	wow2.emplace_back(5);
	int h1[] = { 4,3,1 }; int h2[] = { 2,1 };
	cout << "Input List: ";
	printlist(wow1);
	shellsort(&wow1, h1,3);
	shellsort(&wow2, h2,2);
	cout << endl;
	return 0;
}



//find a formula for number of sublists .



void shellsort(list<int>* toSort, int interval[], int arrsize)
{
	cout << "Array of intervals is: [";
	for (int i = 0; i < arrsize; i++)
	{
		//if (i>sizeof(interval)/sizeof(interval[0])+1)
		//{
		//	break;
		//}
		cout << interval[i]<<',';
	}
	cout << "]" << endl;
	cout << "Initial List: ";
	printlist(*(toSort));
	for (int h = 0; h < arrsize; h++)		//!= NULL???
	{
		int gap = interval[h];
		//for (int i = 0; i<toSort->size(); i++) //we start from 1 because nothing is to the left of i)
		//{
			int i = 0;//comment this line if the above part is uncommented
			int intitial_i = i;
			//if (i != 0 && i % (intitial_i + gap) == 0)
			//{
			//	continue;
			//}
			for (int j = i+gap; j<toSort->size(); j=j+gap)
			{
				if (*(nthelementoflist(toSort,i)) < *(nthelementoflist(toSort, j)))
				{
					auto it1 = nthelementoflist(toSort, i); auto it2 = nthelementoflist(toSort, j);
					swap(*it1,*it2);
				}
				i++;//comment this line if the above part is uncommented
			}
		//}
			if(gap)
			{ 
				cout << "after " << interval[h] << "-th sort: ";
				printlist(*(toSort));
			}
	}



}
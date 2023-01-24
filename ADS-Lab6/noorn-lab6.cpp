#include <iostream> 
#include <list> 
#include <iterator> 
using namespace std;



void printPairs(int, list<int>, list<int>);

int main(void)
{
    int n;
    list <int> a;
    list <int> b;


    //example data begins.

    n = 4;

    a.emplace_back(9);
    a.emplace_back(6);
    a.emplace_back(7);
    a.emplace_back(8);

    b.emplace_back(4);
    b.emplace_back(5);
    b.emplace_back(6);

    //example data ends.

    printPairs(n, a, b);
    return 0;

}


void printPairs(int n, list<int> a, list<int> b)
{
    cout << "The pairs are: ";
    bool firstRun = true;
    list <int> ::iterator it1 = a.begin();
    list <int> ::iterator it2 = b.begin();
    for (; it1 != a.end(); it1++)
    {
        while (it2 != b.end())
        {
            if (*it1 - *it2 == n)
            {
                if (firstRun)
                {
                    cout << '(' << *it1 << ',' << *it2 << ')';
                    firstRun = false;
                    it2++;
                    continue;
                }
                cout << ", (" << *it1 << ',' << *it2 << ')';
            }
            it2++;
        }
        it2 = b.begin();
    }
    if (firstRun) //if this triggers, it means no such pair was found
    {
        cout << "No such pairs exist";
    }
    cout << '.' << endl;
}
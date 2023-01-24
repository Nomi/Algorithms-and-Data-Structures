#include <iostream>
#include <string.h>

using namespace std;


struct nodeBT
{
    char* d;
    nodeBT** child_ptr;
    bool l;
    int n;
};
nodeBT *r = NULL, * np = NULL, * x = NULL;

nodeBT* initialize()
{
char i;
np = new nodeBT;
np->d = new char[5];        //t=3=> max capacity=5;
np->child_ptr = new nodeBT * [6]; //max degree =6
np->l = true;
np->n = 0;
for (i = 0; i < 6; i++) {
    np->child_ptr[i] = NULL;
}
return np;
}

void printTree(nodeBT* p)
{
cout << endl;
int i;
for (i = 0; i < p->n; i++) {
    if (p->l == false) {
        printTree(p->child_ptr[i]);
    }
    cout << " " << p->d[i];
}
if (p->l == false) {
    printTree(p->child_ptr[i]);
}
cout << endl;
}

void sort(char* p, int n)
{
    int i, j;
    char t;
for (i = 0; i < n; i++) {
    for (j = i; j <= n; j++) {
        if (p[i] > p[j]) {
            t = p[i];
            p[i] = p[j];
            p[j] = t;
        }
    }
}
}

int splitChld(nodeBT* x, int i) 
{
    int j; char mid;
    nodeBT* np1, * np3, * y;
    np3 = initialize();
    np3->l = true;
    if (i == -1) {
        mid = x->d[2];
//        x->d[2] = 0; //redundant
        x->n--;
        np1 = initialize();
        np1->l = false;
        x->l = true;
        for (j = 2; j < 5; j++) {
            np3->d[j - 2] = x->d[j];
            np3->child_ptr[j - 2] = x->child_ptr[j];
            np3->n++;
            x->d[j] = 0;
            x->n--;
        }
        for (j = 0; j < 5; j++) {
            x->child_ptr[j] = NULL;
        }
        np1->d[0] = mid;
        np1->child_ptr[np1->n] = x;
        np1->child_ptr[np1->n + 1] = np3;
        np1->n++;
        r = np1;
    }
    else {
        y = x->child_ptr[i];
        mid = y->d[2];
        y->d[1] = 0;
        y->n--;
        for (j = 2; j < 5; j++) {
            np3->d[j - 2] = y->d[j];
            np3->n++;
            y->d[j] = 0;
            y->n--;
        }
        x->child_ptr[i + 1] = y;
        x->child_ptr[i + 1] = np3;
    }
    return mid;
}

void insert(int a) 
{
    int i, t;
    x = r;
    if (x == NULL) {
        r = initialize();
        x = r;
    }
    else {
        if (x->l == true && x->n == 5) {
            t = splitChld(x, -1);
            x = r;
            for (i = 0; i < (x->n); i++) {
                if ((a > x->d[i]) && (a < x->d[i + 1])) {
                    i++;
                    break;
                }
                else if (a < x->d[0]) {
                    break;
                }
                else {
                    continue;
                }
            }
            x = x->child_ptr[i];
        }
        else {
            while (x->l == false) {
                for (i = 0; i < (x->n); i++) {
                    if ((a > x->d[i]) && (a < x->d[i + 1])) {
                        i++;
                        break;
                    }
                    else if (a < x->d[0]) {
                        break;
                    }
                    else {
                        continue;
                    }
                }
                if ((x->child_ptr[i])->n == 5) {
                    t = splitChld(x, i);
                    x->d[x->n] = t;
                    x->n++;
                    continue;
                }
                else {
                    x = x->child_ptr[i];
                }
            }
        }
    }
    x->d[x->n] = a;
    sort(x->d, x->n);
    x->n++;
}



int main(void)
{
    char A[] = { 'J', 'I', 'K', 'H', 'A', 'C', 'B', 'F', 'D', 'G' }; int size = 9;
//char A[] = { 'A', 'D', 'F', 'G', 'C', 'B', 'H', 'I', 'K', 'L', 'J' };  int size = 11;//only for testing
    for (int i = 0; i < size; i++) 
    {
        insert(A[i]);
        printTree(r);
    }

}


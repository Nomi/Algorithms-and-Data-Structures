#include <iostream>
//using namespace std;


struct element
{
    int number;
    struct element* next;
};

class stack
{
public:
    element* head;
    stack();
    ~stack() {};
    void push(int n);
    void pop();
    void print();
};

stack::stack()
{
    head = NULL;
}

void stack::print()
{
    element* temp;
    temp = head;
    std::cout << std::endl;
    std::cout << "The stack is:" << std::endl;
    while (temp)
    {
        std::cout << temp->number << std::endl;
        temp=temp->next;
    }
    std::cout <<std::endl << std::endl;
}

void stack::push(int n)
{
    element* newelem = new element;
    newelem->number = n;
    newelem->next = head;
    if (!head)
    {
        newelem->next = NULL;
    }
    head = newelem;
    std::cout << "After the operation:";
    this->print();
}

void stack::pop()
{
    if (!head)
    {
        std::cout << "The stack is already empty." << std::endl;
    }
    else 
    {
        element* temp;
        temp = head;

        if (head->next)
        {
            head = head->next;
            std::cout << "After the operation:";
        }
        else
        {
            head = NULL;
        }
        temp->next = NULL;
        temp->number = 0;
        delete temp;
        this->print();
    }


}
int main(void)
{
    stack moistack;
    moistack.push(6);
    moistack.pop();
    moistack.pop();
    moistack.push(5);
    moistack.push(4);
    moistack.pop();
    moistack.push(5);
    moistack.pop();
}
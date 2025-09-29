#include<iostream>
#include "DataStructure.h"

using namespace std;

int main()
{
    Singly <int> sobj ;

    sobj.InsertFirst(10);
    sobj.InsertLast(20);
    sobj.InsertAtPos(111,2);
    sobj.Display();

    Doubly <char> cobj ;  

    cobj.InsertFirst('a');
    cobj.InsertLast('c');
    cobj.InsertAtPos('b',2);
    cobj.Display();

    Queuee <int> qobj ;

    qobj.EnQueue(10);
    qobj.EnQueue(20);
    qobj.EnQueue(30);

    qobj.Display();

    cout<<"\n";

    Stack <int> ssobj ;

    ssobj.Push(10);
    ssobj.Push(20);
    ssobj.Push(30);

    ssobj.Display();

    return 0 ;
}
#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include<iostream>
using namespace std ;

template <class T>
struct node                             
{
    T data ;                          
    struct node *next ;                 
};

template<class T>
class Singly
{
    public:
        struct node<T>* head ;                   
        T iCountNode ;                   

        Singly();                               // constructor
        int CountNode();                        // Count the elements of LL
        void InsertFirst(T iNo);              // Insert the node at starting of LL
        void InsertLast(T iNo);               // Insert the node at Last of LL
        void InsertAtPos(T iNo , int iPos);   // Insert the node at the position
        void DeleteFirst();                     // Delete the first node of LL
        void DeleteLast();                      // delete the last node of LL
        void DeleteAtPos(int iPos);             // delete the node from the position
        void Display();                         // Display the data of LL 
        void DeleteAllNode();                   // Delete All nodes
};

template<class T>
Singly<T> :: Singly()                   
{
    head = NULL ;
    iCountNode = 0 ;
}

template<class T>
int Singly<T> :: CountNode()                             // Count the elements of LL
{
    return iCountNode ;
}

template<class T>
void Singly<T> :: InsertFirst(T iNo)            // Insert the node at starting of LL
{
    struct node<T>* newn = NULL ;             // new node 

    newn = new (struct node<T>);                // Dynamic memory allocation for new node

    newn->data = iNo ;
    newn->next = NULL ;

    if(head == NULL)               // if LL is empty
    {
        head = newn ;
    }
    else                            // if LL contain more than 1 node 
    {
        newn->next = head ;
        head = newn ;
    }
    iCountNode++ ;
}

template<class T>
void Singly<T> :: InsertLast(T iNo)                 // Insert the node at Last of LL
{
    struct node<T>* newn = NULL ;             // new node 
    struct node<T>* temp = NULL ;             // temp for travelling the node

    newn = new (struct node <T>);                // Dynamic memory allocation for new node

    newn->data = iNo ;
    newn->next = NULL ;

    if(head == NULL)               // if LL is empty
    {
        head = newn ;
    }
    else                            // if LL contain more than 1 node 
    {
        temp = head ;

        while(temp->next != NULL)
        {
            temp = temp -> next ;
        }
        temp->next = newn ;
    }
    iCountNode++ ;
}

template<class T>
void Singly<T> :: InsertAtPos(T iNo , int iPos)                 // Insert the node at the position
{
    if((iPos < 1) || iPos > (iCountNode+1))
    {
        cout<<"Invalid Position !!! \n";
        return;
    }
    else if(iPos == 1)                               // position is 1
    {
        InsertFirst(iNo);
    }
    else if(iPos == iCountNode+1)                   // position is 2
    {
        InsertLast(iNo);
    }
    else                                        // other position
    {
        int iCnt = 0 ;

        struct node<T>* temp = NULL ;
        struct node<T>* newn = NULL ;

        newn = new (struct node <T>) ;

        newn->data = iNo ;
        newn->next = NULL ;

        temp = head ;

        for(iCnt = 1 ; iCnt < iPos-1 ; iCnt++)
        {
            temp = temp -> next ;
        }
        newn->next = temp->next ;
        temp->next = newn ;

        iCountNode++ ;
    }       
}

template<class T>
void Singly<T> :: DeleteFirst()                           // Delete the first node of LL
{
    struct node<T>* target = NULL ;                 // target for storing the delete node into it

    if(head == NULL)                   // if LL is empty
    {
        cout<<"LL is empty!! \n";
        return  ;
    }
    else if(head->next == NULL)         // if LL contain 1 node only
    {
        delete head ;
        head = NULL ;
    }
    else                                // if LL contain more than 1 node
    {
        target = head ;

        head = head->next ;
        delete target ;
    }
    iCountNode-- ;                  
}

template<class T>
void Singly<T> :: DeleteLast()                            // delete the last node of LL
{
    struct node<T>* temp = NULL ;
    struct node<T>* target = NULL ;                 // for storing the delete node into it

    if(head == NULL)                   // if LL is empty
    {
        cout<<"LL is empty!! \n";
        return ;
    }
    else if(head->next == NULL)         // if LL contain 1 node only
    {
        delete head ;
        head = NULL ;
    }
    else                                // if LL contain more than 1 node
    {
        temp = head ;

        while(temp->next->next != NULL)
        {
            temp = temp->next ;
        }
        target = temp->next ;
        temp->next = NULL ;
        delete target ;
    }
    iCountNode-- ; 
}

template<class T>
void Singly<T> :: DeleteAtPos(int iPos)              // delete the node from the position
{
    int iCnt = 0 ;

    struct node<T>* temp = NULL ;
    struct node<T>* target = NULL ;

    if((iPos < 1) || iPos > (iCountNode+1))  
    {
        cout<<"Invalid Position !!! \n";
        return;
    }

    if(iPos == 1)                       // if position is 1
    {
        DeleteFirst();
    }
    else if(iPos == iCountNode+1)           // if position is last
    {
        DeleteLast();
    }
    else                                // Other position
    {
        temp = head ;

        for(iCnt = 1 ; iCnt < iPos-1 ; iCnt++)
        {
            temp = temp -> next ;
        }
        target = temp->next ;
        temp->next = target->next ;
        delete target ;
        
        iCountNode-- ;
    }       
} 

template<class T>
void Singly<T> :: Display()                          // Display the data of LL 
{
    struct node<T>* temp = NULL ;                 // temp for travelling the node

    temp = head ;

    while(temp != NULL)
    {
        cout<<"| "<<temp->data<<" |->";
        temp = temp->next ;
    }
    cout<<" NULL\n";
}     

template<class T>
void Singly<T> :: DeleteAllNode()
{
    struct node<T>* temp = head;
    while (temp != NULL)
    {
        struct node<T>* next = temp->next;
        delete temp;
        temp = next;
    }
    head = NULL;
    iCountNode = 0;
}

template<class T>
struct node1
{
    T data ;
    struct node1* prev ;
    struct node1* next ;
};

template<class T>
class Doubly
{
    public:
        struct node1<T>* head ;
        T iCountNode ;

        Doubly();
        T CountNode();
        void InsertFirst(T iNo);
        void InsertLast(T iNo);
        void DeleteFirst();
        void DeleteLast();
        void InsertAtPos(T iNo , int iPos);
        void DeleteAtPos(int iPos);
        void DeleteAllNode();
        void Display();
};

template<class T>
Doubly<T> :: Doubly()
{
    head = NULL ;
    iCountNode = 0 ;
}

template<class T>
T Doubly<T> :: CountNode()
{
    return iCountNode ;
}

template<class T>
void Doubly<T> :: InsertFirst(T iNo)
{
    struct node1<T>* newn = NULL ;

    newn = new (struct node1 <T>) ;

    newn->data = iNo ;
    newn->next = NULL ;
    newn->prev = NULL ;

    if(head == NULL)
    {
        head = newn ;
    }
    else 
    {
        newn->next = head ;
        head->prev = newn ;
        head = newn ;
    }

    iCountNode++ ;
}

template<class T>
void Doubly<T> :: InsertLast(T iNo)
{
    struct node1<T>* newn = NULL ;

    newn = new (struct node1<T>) ;

    newn->data = iNo ;
    newn->next = NULL ;
    newn->prev = NULL ;

    if(head == NULL)
    {
        head = newn ;
    }
    else 
    {
        struct node1<T>* temp = NULL ;

        temp = head ;

        while(temp->next != NULL)
        {
            temp = temp->next ;
        }
        newn->prev = temp ;
        temp->next = newn ;
    }
    iCountNode++ ;
}

template<class T>
void Doubly<T> :: DeleteFirst()
{
    if(head == NULL)
    {
        cout<<"Linked List is empty !";
        return ;
    }
    else if(head->next == NULL)
    {
        delete (head);
        head = NULL ;
    }
    else
    {
        struct node1<T>* target = NULL ;

        target = head->next->prev ;
        head->next->prev = NULL ;
        head = head->next ;

        delete (target);
    }
    iCountNode-- ;
}

template<class T>
void Doubly<T> :: DeleteLast()
{
    if(head == NULL)
    {
        cout<<"Linked List is empty !";
        return ;
    }
    else if(head->next == NULL)
    {
        delete (head);
        head = NULL ;
    }
    else
    {
        struct node1<T>* target = NULL ;
        struct node1<T>* temp = NULL ;

        temp = head ;

        while(temp->next->next != NULL)
        {
            temp = temp->next ;
        }

        target = temp->next ;
        delete (target);

        temp->next = NULL ;
    }
    iCountNode-- ;
}

template<class T>
void Doubly<T> :: InsertAtPos(T iNo , int iPos)
{
    if(iPos < 1 || iPos > iCountNode+1)
    {
        cout<<"Invalid Position !!\n";
        return ;
    }
    else if(iPos == 1)
    {
        InsertFirst(iNo);
    }
    else if(iPos == iCountNode+1)
    {
        InsertLast(iNo);
    }
    else
    {
        struct node1<T>* newn = NULL ;
        struct node1<T>* temp = NULL ;

        int iCnt = 0 ;

        temp = head ;

        newn = new (struct node1<T>) ;
        
        newn->data = iNo ;
        newn->next = NULL ;
        newn->prev = NULL ;

        for(iCnt = 1 ; iCnt < iPos-1 ; iCnt++)
        {
            temp = temp->next ;
        }
        newn->next = temp->next ;
        newn->prev = temp ;
        temp->next->prev = newn ;
        temp->next = newn ;

        iCountNode++ ;
    }
}

template<class T>
void Doubly<T> :: DeleteAtPos(int iPos)
{
    if(iPos < 1 || iPos > iCountNode)
    {
        cout<<"Invalid Position !!\n";
        return ;
    }
    else if(iPos == 1)
    {
        DeleteFirst();
    }
    else if(iPos == iCountNode)
    {
        DeleteLast();
    }
    else
    {
        struct node1<T>* temp = NULL ;
        struct node1<T>* target = NULL ;

        int iCnt = 0 ;

        temp = head ;

        for(iCnt = 1 ; iCnt < iPos-1 ; iCnt++)
        {
            temp = temp->next ;
        }
        target = temp->next ;
        temp->next = target->next ;
        target->next->prev = temp->next ;
        

        delete target ;

        iCountNode-- ;
    }
}

template<class T>
void Doubly<T> :: DeleteAllNode()
{
    struct node1<T>* temp = NULL ;
    struct node1<T>* next = NULL ;

    temp = head;
    while (temp != NULL)
    {
        next = temp->next;
        delete temp;
        temp = next;
    }
    head = NULL;
    iCountNode = 0;
}

template<class T>
void Doubly<T> :: Display()
{
    struct node1<T>* temp = NULL ;
    temp = head ;

    cout<<"NULL<=>";
    while(temp != NULL)
    {
        cout<<"|"<<temp->data<<"|<=>";
        temp = temp->next ;
    }
    cout<<"NULL\n";
}

template<class T>
struct node2 
{
    T data ;
    struct node2* next ;
};

template<class T>
class Singly_Circular
{
    public:
        struct node2<T>* head ;
        struct node2<T>* tail ;
        T iCountNode ;

        Singly_Circular();
        T CountNode();
        void Display();
        void InsertFirst(T iNo);
        void InsertLast(T iNo);
        void DeleteFirst();
        void DeleteLast();
        void InsertAtPos(T iNo , int iPos);
        void DeleteAtPos(int iPos);
        void DeleteAllNode();
};

template<class T>
Singly_Circular<T> :: Singly_Circular()
{
    head = NULL ;
    tail = NULL ;
    iCountNode = 0 ;
}

template<class T>
T Singly_Circular <T> :: CountNode()
{
    return iCountNode ;
}

template<class T>
void Singly_Circular <T> :: Display()
{
    if(head == NULL || tail == NULL)
    {
        cout<<"LL is empty !!\n";
        return ;
    }

    struct node2<T>* temp = NULL ;
    temp = head ;

    do
    {
        cout<<"|"<<temp->data<<"|->";
        temp = temp->next ;
    }
    while(temp != (tail->next));

    cout<<"NULL\n";
}

template<class T>
void Singly_Circular <T> :: InsertFirst(T iNo)
{
    struct node2<T>* newn = NULL ;

    newn = new (struct node2<T>) ;

    newn->data = iNo ;
    newn->next = NULL ;

    if(head == NULL && tail == NULL)
    {
        head = newn ;
        tail = newn ;
    }
    else
    {
        newn->next = head ;
        head = newn ;
    }
    tail->next = head ;
    iCountNode++ ;
}

template<class T>
void Singly_Circular <T> :: InsertLast(T iNo)
{
    struct node2<T>* newn = NULL ;

    newn = new (struct node2<T>) ;

    newn->data = iNo ;
    newn->next = NULL ;

    if(head == NULL && tail == NULL)
    {
        head = newn ;
        tail = newn ;
    }
    else
    {
        tail->next = newn ;
        tail = newn ;
    }
    tail->next = head ;
    iCountNode++ ;
}

template<class T>
void Singly_Circular <T> :: DeleteFirst()
{
    if(head == NULL && tail == NULL)
    {
        cout<<"LL is already empty\n";
        return ;
    }
    else if(head == tail)
    {
        delete head;

        head = NULL ;
        tail = NULL ;
    }
    else
    {
        head = head->next ;
        delete (tail->next);

        tail->next = head ;
    }    
    iCountNode-- ;
}

template<class T>
void Singly_Circular <T> :: DeleteLast()
{
    if(head == NULL && tail == NULL)
    {
        cout<<"LL is already empty\n";
        return ;
    }
    else if(head == tail)
    {
        delete head;

        head = NULL ;
        tail = NULL ;
    }
    else
    {
        struct node2<T>* temp = NULL ;
        struct node2<T>* target = NULL ;

        temp = head ;

        while(temp->next != tail)
        {
            temp = temp->next ;
        }
        delete (temp->next);
        tail = temp ;

        tail->next = head ;
    }
    iCountNode-- ;
}

template<class T>
void Singly_Circular <T> :: InsertAtPos(T iNo , int iPos)
{
    if(iPos < 1 || iPos > iCountNode+1)
    {
        cout<<"Invalid Position !!\n";
        return ;
    }
    else if(iPos == 1)
    {
        InsertFirst(iNo);
    }
    else if(iPos == iCountNode+1)
    {
        InsertLast(iNo);
    }
    else
    {
        struct node2<T>* temp = NULL ;
        struct node2<T>* newn = NULL ;
        int i = 0 ;

        newn = new (struct node2<T>) ;

        newn->data = iNo ;
        newn->next = NULL ;

        temp = head ;

        for(i = 1 ; i < iPos-1 ; i++)
        {
            temp = temp->next ;
        }
        newn->next = temp->next ;
        temp->next = newn ;

        iCountNode++ ;
    }
}

template<class T>
void Singly_Circular <T> :: DeleteAtPos(int iPos)
{
    if(iPos < 1 || iPos > iCountNode)
    {
        cout<<"Invalid Position !!\n";
        return ;
    }
    else if(iPos == 1)
    {
        DeleteFirst();
    }
    else if(iPos == iCountNode)
    {
        DeleteLast();
    }
    else
    {
        struct node2<T>* temp = NULL ;
        struct node2<T>* target = NULL ;
        int i = 0 ;

        temp = head ;

        for(i = 1 ; i < iPos-1 ; i++)
        {
            temp = temp->next ;
        }
        target = temp->next ;
        temp->next = temp->next->next ;
        delete (target) ;

        iCountNode-- ;
    }
}

template<class T>
void Singly_Circular <T> :: DeleteAllNode()
{
    if(head == NULL) return;

    struct node2<T>* temp = head;
    struct node2<T>* next = NULL;

    do
    {
        next = temp->next;
        delete temp;
        temp = next;
    }
    while(temp != head);

    head = NULL;
    tail = NULL;
    iCountNode = 0;
}   

template <class T>
struct node3
{
    T data ;
    struct node3* next ;
    struct node3* prev ;
};

template <class T>
class Doubly_Circular
{
    public:
        struct node3<T>* head ;
        struct node3<T>* tail ;
        T iCountNode ;

        Doubly_Circular();

        T CountNode();
        void Display();
        void InsertFirst(T iNo);
        void InsertLast(T iNo);
        void DeleteFirst();
        void DeleteLast();
        void InsertAtPos(T iNo , int iPos);
        void DeleteAtPos(int iPos);
        void DeleteAllNode();
 
};

template <class T>
Doubly_Circular <T> :: Doubly_Circular()
{
    head = NULL ;
    tail = NULL ;
    iCountNode = 0 ;
}

template <class T>
T Doubly_Circular<T> :: CountNode()
{
    return iCountNode ;
}

template <class T>
void Doubly_Circular<T> :: Display()
{
    if(head == NULL && tail == NULL)
    {
        cout<<"LL is Already Empty \n";
        return ;
    }

    struct node3<T>* temp = NULL ;
    temp = head ;
    
    cout<<"<=>";
    do
    {
        cout<<"|"<<temp->data<<"|<=>";
        temp = temp->next ;
    }
    while(temp != head);
    cout<<"\n";
}

template <class T>
void Doubly_Circular <T> :: InsertFirst(T iNo)
{
    struct node3<T>* newn = NULL ;

    newn = new (struct node3<T>) ;

    newn->data = iNo ;
    newn->next = NULL ;
    newn->prev = NULL ;

    if(head == NULL && tail == NULL)
    {
        head = newn ;
        tail = newn ;
    }
    else
    {
        newn->next = head ;
        head->prev = newn ;
        head = newn ;
    }
    tail->next = head ;
    head->prev = tail ;

    iCountNode++ ;
}

template <class T>
void Doubly_Circular <T> :: InsertLast(T iNo)
{
    struct node3<T>* newn = NULL ;

    newn = new (struct node3<T>) ;

    newn->data = iNo ;
    newn->next = NULL ;
    newn->prev = NULL ;

    if(head == NULL && tail == NULL)
    {
        head = newn ;
        tail = newn ;
    }
    else
    { 
        newn->prev = tail ;
        tail->next = newn ;
        tail = newn ;
    }
    tail->next = head ;
    head->prev = tail ;

    iCountNode++ ;
}

template <class T>
void Doubly_Circular <T> :: DeleteFirst()
{
    if(head == NULL && tail == NULL)
    {
        cout<<"LL is empty unable to delete first element\n";
        return ;
    }
    else if(head == tail)
    {
        delete head ;

        head = NULL ;
        tail = NULL ;
    }
    else
    {
        head = head->next ;

        delete (tail->next) ;

        tail->next = head ;
        head->prev = tail ;
    }
    iCountNode-- ;
}

template <class T>
void Doubly_Circular <T> :: DeleteLast()
{
    if(head == NULL && tail == NULL)
    {
        cout<<"LL is empty unable to delete first element\n";
        return ;
    }
    else if(head == tail)
    {
        delete head ;

        head = NULL ;
        tail = NULL ;
    }
    else
    {
        tail = tail->prev ;
        delete (tail->next) ;

        tail->next = head ;
        head->prev = tail ;
    }
    iCountNode-- ;
}

template <class T>
void Doubly_Circular <T> :: InsertAtPos(T iNo , int iPos)
{
    if(iPos < 1 || iPos > iCountNode+1)
    {
        cout<<"Invalid Position !!\n";
        return ;
    }
    else if(iPos == 1)
    {
        InsertFirst(iNo);
    }
    else if(iPos == iCountNode+1)
    {
        InsertLast(iNo);
    }
    else
    {
        int iCnt = 0 ;

        struct node3<T>* temp = NULL ;
        struct node3<T>* newn = NULL ;

        newn = new (struct node3<T>) ;

        newn->data = iNo ;
        newn->next = NULL ;
        newn->prev = NULL ;

        temp = head ;

        for(iCnt = 1 ; iCnt < iPos-1 ; iCnt++)
        {
            temp = temp->next ;
        }
        newn->next = temp->next ;
        temp->next->prev = newn ;
        newn->prev = temp->next ;
        temp->next = newn ;

        iCountNode++ ;
    }
}

template <class T>
void Doubly_Circular <T> :: DeleteAtPos(int iPos)
{
    if(iPos < 1 || iPos > iCountNode)
    {
        cout<<"Invalid Position !!\n";
        return ;
    }
    else if(iPos == 1)
    {
        DeleteFirst();
    }
    else if(iPos == iCountNode)
    {
        DeleteLast();
    }
    else
    {
        int iCnt = 0 ;

        struct node3<T>* temp = NULL ;
        struct node3<T>* target = NULL ;

        temp = head ;

        for(iCnt = 1 ; iCnt < iPos-1 ; iCnt++)
        {
            temp = temp->next ;
        }

        target = temp->next;
        temp->next = temp->next->next;
        temp->next->prev = temp;
        delete target;

        iCountNode-- ;
    }
}

template <class T>
void Doubly_Circular <T> :: DeleteAllNode()
{
    if(head == NULL)
    return;

    struct node3<T>* temp = head;
    struct node3<T>* next = NULL;

    do
    {
        next = temp->next;
        delete temp;
        temp = next;
    }
    while(temp != head);

    head = NULL;
    tail = NULL;
    iCountNode = 0;
}  

template <class T>
struct nodeQ 
{
    T data ;
    struct nodeQ* next ;
};

template <class T>
class Queuee
{
    public:
        T iCountNode ;
        struct nodeQ<T>* head ;

        Queuee();

        T CountNode();
        void Display();
        void EnQueue(T iNo);
        T DeQueue();
};

template <class T>
Queuee <T> :: Queuee()
{
    iCountNode = 0 ;
    head = NULL ;
}

template <class T>
T Queuee <T> :: CountNode()
{
    return iCountNode ;
}

template <class T>
void Queuee <T> :: Display()
{
    struct nodeQ<T>* temp = NULL ;

    temp = head ;

    while(temp != NULL)
    {
        cout<<"| "<<temp->data<<" |<-";
        temp = temp->next ;
    }
    cout<<"NULL\n";
}

template <class T>
void Queuee <T> :: EnQueue(T iNo)
{
    struct nodeQ<T>* newn = NULL ;

    newn = new (struct nodeQ<T>) ;

    newn->data = iNo ;
    newn->next = NULL ;

    if(head == NULL)
    {
        head = newn ;
    }
    else
    {
        struct nodeQ<T>* temp = NULL ;

        temp = head ;

        while(temp->next != NULL)
        {
            temp = temp->next ;
        }
        temp->next = newn ;
    }
    iCountNode++ ;
}

template <class T>
T Queuee <T> :: DeQueue()
{
    struct nodeQ<T>* target = NULL ; 
    int no = -1 ;

    if(head == NULL)
    {
        cout<<"Queue is empty , Unable to Delete element !!";
        return -1 ;
    }
    else if(head->next == NULL)
    {
        no = head->data ;

        target = head ;

        delete target;
        head = NULL ;
    }
    else
    {
        no = head->data ;

        target = head ;
        head = head->next ;

        delete target ;
    }

    iCountNode-- ;

    return no ;
}

template <class T>
struct nodeS
{
    T data ;
    struct nodeS* next ;
};

template <class T>
class Stack
{
    public:
        struct nodeS<T>* head ;
        T iCountNode ;

        Stack();

        T CountNode();
        void Display();
        void Push(T iNo);
        T Pop();
};

template <class T>
Stack <T> :: Stack()
{
    head = NULL ;
    iCountNode = 0 ;
}

template <class T>
T Stack <T> :: CountNode()
{
    return iCountNode ;
}

template <class T>
void Stack <T> :: Display()
{
    if(head == NULL)
    {
        cout<<"Stack is empty !!\n";
        return ;
    }
    struct nodeS<T>* temp = NULL ;
    temp = head ;

    while(temp != NULL)
    {
        cout<<"| "<<temp->data<<" |\n";
        temp = temp->next ;
    }
}

template <class T>
void Stack <T> :: Push(T iNo)
{
    struct nodeS<T>* newn = NULL ;

    newn = new (struct nodeS<T>);

    newn->next = NULL ;
    newn->data = iNo ;

    if(head == NULL)
    {
        head = newn ;
    }
    else
    {
        newn->next = head ;
        head = newn ;
    }
    iCountNode++ ;
}

template <class T>
T Stack <T> :: Pop()
{
    T no = -1 ;

    struct nodeS<T>* target = NULL ;

    if(head == NULL)
    {
        cout<<"Stack is already empty ! enable to delete element !!\n";
        return -1 ;
    }
    else if(head->next == NULL)
    {
        target = head ;

        no = head->data ;

        delete target ;

        head = NULL ;
    }
    else
    {  
        no = head->data ;

        target = head ;

        head = head->next ;

        delete target ;
    }
    iCountNode-- ;

    return no ;
}

#endif
#pragma once
//#include <iostream>
//#include <tchar.h>
//#include <windows.h>
//#include <math.h>
//#include "GL/glut.h"
//#include "globals.h"
//#include "cRenderClass.h"
//
//
//// TODO: reference additional headers your program requires here
//#include <vector>
//using std::vector;
//
//#include "NA_Boid.h"
//#include "NA_common_includes.h"
//#include "NA_LinkedListNode.h"
//#include "NA_MathsLib.h"
//#include "NA_Matrix.h"
//#include "NA_Queue.h"
//#include "NA_Return.h"
//#include "NA_Stack.h"
//#include "NA_Timer.h"
//#include "NA_Vector.h"
#include "NA_LinkedListNode.h"
template <class _template>class NA_Stack 
{
public:
	~NA_Stack(void);
	NA_Stack();
	void push(_template);
	_template pop(void);
	_template peak(void);
	bool isEmpty(void);
	unsigned int getSize(void);
private:
	unsigned int size;
	NA_LinkedListNode<_template>* stack;
};

template <class _template> unsigned int NA_Stack<_template>::getSize(void)
{
	return size;
}


template <class _template>NA_Stack<_template>::NA_Stack(void)
{
	stack=NULL;//stack starts as empty
	size = 0;
}

template <class _template>NA_Stack<_template>::~NA_Stack(void)
{
	while(!isEmpty())//if there are items on the stack then we need to empty it
	{
		NA_LinkedListNode<_template>* _stack = stack; //we will need to delete this later
    stack = stack->next;//move the 2nd item to the top of the stack
    _stack->next = NULL; //disconnect bottom of node from stack
    delete _stack; //delete the removed node
    size--;
	}
	stack=NULL;
	size=0;
}

template <class _template>bool NA_Stack<_template>::isEmpty(void)
{ 
	if (size==0)//if the pointer is null then the stack is empty
        return true;
	else
		return false;
}

template <class _template>void NA_Stack<_template>::push(_template x)
{
	NA_LinkedListNode<_template>* temp = new NA_LinkedListNode<_template>();//create a new node to store the pushed value
	temp->value = x;//put the value in the node
	temp->next = stack;//attach the stack to the bottom
	stack = temp;//set the stack head to the top
	size++;
}

 template <class _template>_template NA_Stack<_template>::pop(void)
{
	_template returnVar = stack->value; //get value from stack
	NA_LinkedListNode<_template>* _stack = stack; //we will need to delete this later
	stack = stack->next;//move the 2nd item to the top of the stack
	_stack->next = NULL; //disconnect bottom of node from stack
	delete _stack; //delete the removed node
	size--;
	return returnVar; //return wanted value
}

 template <class _template>_template NA_Stack<_template>::peak(void)
{
	return stack->value;
}
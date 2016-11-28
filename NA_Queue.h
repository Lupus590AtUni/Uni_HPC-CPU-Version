#pragma once
#include "NA_LinkedListNode.h"
template <class _template> class NA_Queue
{
public:
	NA_Queue(void);
	~NA_Queue(void);
	void enqueue(_template);
	_template dequeue(void);
	_template peak(void);
	bool isEmpty(void);
	unsigned int getSize();
private:
	unsigned int size;
	NA_LinkedListNode<_template>* queueHead;
	NA_LinkedListNode<_template>* queueTail;//more work to maintain a pointer to the end of the queue
							  //but it means that we don't have to loop to get to the end of it when we want to add something
};

template <class _template> unsigned int NA_Queue<_template>::getSize(void)
{
	return size;
}

template <class _template>NA_Queue<_template>::NA_Queue(void)
{
	//queue starts as empty
	queueHead=NULL;
	queueTail=NULL;
	size = 0;
}

template <class _template>NA_Queue<_template>::~NA_Queue(void)
{
	while(!isEmpty())//if there are items on the stack then we need to empty it
	{
		NA_LinkedListNode<_template>* _queue = queueHead; //we will need to delete this later
    queueHead = queueHead->next;//move the 2nd item to the front of the queue
    _queue->next = NULL; //disconnect bottom of node from queue
    delete _queue; //delete the removed node
    size--;
	}
	queueHead=NULL;
	queueTail=NULL;
	size=0;
}

template <class _template>bool NA_Queue<_template>::isEmpty(void)
{ 
	if (size==0)//if the pointer is null then the stack is empty
        return true;
	else
		return false;
}

template <class _template> void NA_Queue<_template>::enqueue(_template x)
{
	NA_LinkedListNode<_template>* temp = new NA_LinkedListNode<_template>();//create a new node to store the added value
	temp->value = x;//put the value in the node
	if(size==0)//queue is empty go to front of queue (and set back) else go to back of queue
	{
		queueHead = temp;
		queueTail = temp;
	}
	else
	{
		queueTail->next = temp;//set the last node to the new node
		queueTail = temp;//set the tail to the last node
	}
	size++;
}

template <class _template> _template NA_Queue<_template>::dequeue(void)
{
	_template returnVar = queueHead->value; //get value from queue
	NA_LinkedListNode<_template>* _queue = queueHead; //we will need to delete this later
	queueHead = queueHead->next;//move the 2nd item to the front of the queue
	_queue->next = NULL; //disconnect bottom of node from queue
	delete _queue; //delete the removed node
	size--;
	return returnVar; //return wanted value
}

template <class _template>_template NA_Queue<_template>::peak(void)
{
	return queueHead->value;
}
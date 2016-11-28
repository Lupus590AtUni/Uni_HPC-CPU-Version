#pragma once
template <class _template> class NA_LinkedListNode //http://www.cprogramming.com/tutorial/templates.html
{
public:

	NA_LinkedListNode(void);
	~NA_LinkedListNode(void);

	//could be private but that would just mean gets and sets
	_template value;
	NA_LinkedListNode* next;
};

template <class _template>NA_LinkedListNode<_template>::NA_LinkedListNode(void)
{
	next = NULL;
}


template <class _template>NA_LinkedListNode<_template>::~NA_LinkedListNode(void)
{
	//posible memory leak if value is a pointer to dynamic memory
	next=NULL;
}

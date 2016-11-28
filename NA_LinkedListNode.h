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

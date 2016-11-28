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
#include <string>
using std::string;
template<class _template> class NA_Return//this should be a struct (can I template a struct? do I need to, things could define their own return struct)
{

public:
	NA_Return(void);
	~NA_Return(void);

//private: //these probably should be private, but public removes function overhead
	bool success; //if true then value is useful else value is junk
	_template value;
	string reason; //a string where code can put failure details

};

template <class _template>NA_Return<_template>::NA_Return(void)
{
  success = false;
}


template <class _template>NA_Return<_template>::~NA_Return(void)
{
}

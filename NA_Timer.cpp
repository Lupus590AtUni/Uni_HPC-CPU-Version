
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
#include "NA_Timer.h"
#include <time.h>



NA_Timer::NA_Timer(double d)
{
	duration = d;
	start = time(NULL);
}

NA_Timer::~NA_Timer(void)
{
}

void NA_Timer::setDuration(double d)
{
	duration = d;
}

bool NA_Timer::hasElapsed()
{
	if(duration < difftime(time(NULL),start))
		return true;
	//else
	return false;
}

void NA_Timer::restart()
{
	start = time(NULL);
}

void NA_Timer::wait()
{
	while (!hasElapsed())
	{
		//should probably tell the os that we are waiting
	}
}

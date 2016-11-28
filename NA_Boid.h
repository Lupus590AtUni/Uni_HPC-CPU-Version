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

#include "NA_Vector.h"

class NA_Boid
{
public:
	//should be private, but lazy
	NA_Vector position;
	NA_Vector currentVelocity;
	NA_Vector newVelocity;

	NA_Boid();
	void update();
	void postUpdate();//keeps all boids using same data
	//NA_Vector getVelocity();
	//NA_Vector getposition();
	void draw();
};


//adapted from 1st year maths assignment (lecturer: Gordan Dickers)
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

class NA_Vector
{
public:

	//construct
	NA_Vector(float x=0.0f, float y=0.0f, float z=0.0f, float w=0.0f);
	NA_Vector(const NA_Vector &copy);
	void scale(float s);
	void add(NA_Vector & v1);
	void normalise(void);
	float dist(NA_Vector & v1);
	float dot(NA_Vector & v1);
	float length();
	static NA_Vector twoPointsIntoVector(NA_Vector & startPoint, NA_Vector & endPoint);

	//were private, but gets and sets slowdown realtime systems (such as games)
	float x;
	float y;
	float z;
	float w;
};
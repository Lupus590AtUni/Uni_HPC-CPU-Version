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

class NA_Vector;
class NA_Matrix
{
public:

	enum types { identity = 0, translate, rotateX, rotateY, rotateZ, scale, shearX, shearY, shearZ};

	float matrix[4][4];//was private but gets and sets slow things down

	~NA_Matrix(void);
  
	NA_Matrix(types type = types::identity, float x=0, float y=0, float z=0);

	void correctW();
	NA_Matrix transpose();//inverse
	NA_Matrix matrixXmatrix(NA_Matrix);//TODO make operand version
	NA_Vector matrixXvector(NA_Vector);//TODO make operand version
};


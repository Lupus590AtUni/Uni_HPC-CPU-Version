#pragma once
#include "stdafx.h"

class NA_Vector;
class NA_Matrix
{
public:

  static enum types { identity = 0, translate, rotateX, rotateY, rotateZ, scale, shearX, shearY, shearZ};

	float matrix[4][4];//was private but gets and sets slow things down

	~NA_Matrix(void);
  
	NA_Matrix(types type = types::identity, float x=0, float y=0, float z=0);

	void correctW();
	NA_Matrix transpose();//inverse
	NA_Matrix matrixXmatrix(NA_Matrix);//TODO make operand version
	NA_Vector matrixXvector(NA_Vector);//TODO make operand version
};


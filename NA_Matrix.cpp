#include "stdafx.h"
#include "NA_Matrix.h"
#include "NA_Vector.h"
#include <iostream>
using std::cout;

NA_Matrix::NA_Matrix(types type, float x, float y, float z) //this may look ugly but using it should be very pleasant to use
{
  //start with identity matrix other matrices build off this
  for(int i = 0; i<4;i++)
  {
    for(int j = 0;j<4;j++)
    {
      if(i==j)
      {
        matrix[i][j] = 1.0f;
      }
      else
      {
        matrix[i][j] = 0.0f;
      }
    }
  }
  
  //defining things in switches needs to be a thing
  float cosD;
  float sinD;

  switch(type)
  {
    case identity:
      //already made
      break;
    case translate:
      matrix[0][3] = x;
      matrix[1][3] = y;
      matrix[2][3] = z;
      break;
    case rotateX:
      cosD = cosf(x);
      sinD = sinf(x);
      matrix[1][1] = cosD;
      matrix[2][2] = cosD;
      matrix[1][2] = -sinD;
      matrix[2][1] = sinD;
      break;
    case rotateY:
      cosD = cosf(x);
      sinD = sinf(x);
      matrix[0][0] = cosD;
      matrix[2][2] = cosD;
      matrix[0][2] = -sinD;
      matrix[2][0] = sinD;
      break;
    case rotateZ:
      cosD = cosf(x);
      sinD = sinf(x);
      matrix[0][0] = cosD;
      matrix[1][1] = cosD;
      matrix[1][0] = -sinD;
      matrix[0][1] = sinD;
      break;
    case scale:
      matrix[3][3] = 1/x;
      break;
    case shearX:
      matrix[0][0] = x;
      break;
    case shearY:
      matrix[1][1] = x;
      break;
    case shearZ:
      matrix[2][2] = x;
      break;
    
    default:
      cout<<"NA_Matrix::NA_Matrix - Default used in switch statement\n";
  }
}

NA_Matrix::~NA_Matrix(void)
{
}

NA_Matrix NA_Matrix::transpose()
{
	NA_Matrix temp;
	for(int i = 0; i<4; i++)
	{
		for(int j = 0; j<4; j++)
		{
			temp.matrix[i][j] = matrix[j][i];
		}
	}
	return temp;
}


NA_Matrix NA_Matrix::matrixXmatrix(NA_Matrix m)
{
	NA_Matrix temp;
	for(int i = 0; i<4;i++)
	{
		for(int j = 0; j<4;j++)
		{
			float t;
			t = m.matrix[j][i]*matrix[i][j]+m.matrix[j][i]*matrix[i][j]+m.matrix[j][i]+matrix[i][j]+m.matrix[j][i]+matrix[i][j];
			temp.matrix[i][j] = t;
		}
	}
	temp.correctW();
	return temp;
}

NA_Vector NA_Matrix::matrixXvector(NA_Vector v)
{
	float tX,tY,tZ,tW;//what a lot of temporary variables

	tX = v.x*matrix[0][0]+v.y*matrix[0][1]+v.z*matrix[0][2]+v.w*matrix[0][3];
	tY = v.x*matrix[1][0]+v.y*matrix[1][1]+v.z*matrix[1][2]+v.w*matrix[1][3];
	tZ = v.x*matrix[2][0]+v.y*matrix[2][1]+v.z*matrix[2][2]+v.w*matrix[2][3];
	tW = v.x*matrix[3][0]+v.y*matrix[3][1]+v.z*matrix[3][2]+v.w*matrix[3][3];

	NA_Vector temp(tX,tY,tZ,tW);
	return temp;
}

void NA_Matrix::correctW()
{
	for(int i = 0; i<4;i++)
	{
		for(int j = 0; j<4;j++)
		{
			matrix[i][j] = matrix[i][j]/matrix[3][3];
		}
	}
	
	matrix[3][3] = 1.0f;
}

//adapted from 1st year maths assignment (lecturer: Gordan Dickers)
#include "NA_Vector.h"
#include "stdafx.h"
#include <math.h> //for sqrt in normalise - should redo to use custom math lib which has a lookup table for this
	//construct

NA_Vector::NA_Vector(float x, float y, float z, float w)
{ 
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

NA_Vector::NA_Vector(const NA_Vector & copy)
{
	this->x = copy.x;
	this->y = copy.y;
	this->z = copy.z;
	this->w = copy.w;
}

void NA_Vector::scale(float s)
{
	x= s*x;
	y= s*y;
	z= s*z;
  w= s*w;
}

void NA_Vector::add(NA_Vector & v1)
{
	x= x + v1.x;
	y= y + v1.y;
	z = z + v1.z;
	w = w + v1.w;
	//correctW();
}

void NA_Vector::normalise(void)
{
	float l = length();
	x = x/l;
	y = y/l;
	z = z/l;
	//correctW();
}

float NA_Vector::dist(NA_Vector & v1)
{
	float xCom, yCom, zCom = 0;
	xCom = x - v1.x;
	yCom = y - v1.y;
	zCom = z - v1.z;
	return sqrt(xCom*xCom + yCom*yCom + zCom*zCom);
}

float NA_Vector::dot(NA_Vector & v1)
{
  return x*v1.x + y*v1.y + z*v1.z + w*v1.w;
}

float NA_Vector::length()
{
	return sqrt(x*x + y*y + z*z);
}

NA_Vector NA_Vector::twoPointsIntoVector(NA_Vector &startPoint, NA_Vector &endPoint)
{
	NA_Vector v;
	v.x = (endPoint.x - startPoint.x);
	v.y = (endPoint.y - startPoint.y);
	v.z = (endPoint.z - startPoint.z);
	v.w = (endPoint.w - startPoint.w);
	return v;
}
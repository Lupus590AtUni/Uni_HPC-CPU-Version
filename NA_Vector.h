//adapted from 1st year maths assignment (lecturer: Gordan Dickers)
#pragma once

class NA_Vector
{
public:

	//construct
	NA_Vector(float x=0.0f, float y=0.0f, float z=0.0f, float w=0.0f);
	NA_Vector(const NA_Vector &copy);
	void Scale(float s);
	void Add(NA_Vector & v1);
	void normalise(void);
	float dist(NA_Vector & v1);
	float dot(NA_Vector & v1);
	static NA_Vector twoPointsIntoVector(NA_Vector & startPoint, NA_Vector & endPoint);

	//were private, but gets and sets slowdown realtime systems (such as games)
	float x;
	float y;
	float z;
	float w;
};
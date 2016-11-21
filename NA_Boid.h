#pragma once

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


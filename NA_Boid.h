#pragma once

#include "NA_Vector.h"

class NA_Boid
{
private:
	NA_Vector position;
	NA_Vector currentVelocity;
	NA_Vector newVelocity;
public:
	NA_Boid();
	void update();
	void postUpdate();//keeps all boids using same data
	NA_Vector getVelocity();
	NA_Vector getposition();
};


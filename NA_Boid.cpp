#include "NA_Boid.h"
#include "stdafx.h"

NA_Boid::NA_Boid()
{

}

void NA_Boid::update()
{
	//TODO: find naigboors

	//TODO: alignment

	//TODO: cohesion

	//TODO: separation

}

void NA_Boid::postUpdate()
{
	currentVelocity = newVelocity;
	newVelocity = NA_Vector();
}

NA_Vector NA_Boid::getVelocity()
{
	NA_Vector temp(this->currentVelocity);
	return temp;
}

NA_Vector NA_Boid::getposition()
{
	NA_Vector temp(this->position);
	return temp;
}

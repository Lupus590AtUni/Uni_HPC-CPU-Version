#include "NA_Boid.h"
#include "stdafx.h"

NA_Boid::NA_Boid()
{

}

void NA_Boid::update()
{
	extern vector<NA_Boid> boidList;
	//TODO: find naigboors
	//boidList

	//TODO: alignment

	//TODO: cohesion

	//TODO: separation

}

void NA_Boid::postUpdate()
{
	currentVelocity = newVelocity;
	newVelocity = NA_Vector();
}

/*NA_Vector NA_Boid::getVelocity()
{
	NA_Vector temp(this->currentVelocity);
	return temp;
}

NA_Vector NA_Boid::getposition()
{
	NA_Vector temp(this->position);
	return temp;
}*/

void NA_Boid::draw()
{
	extern cRenderClass graphics;


	//draw body
	graphics.setColour(1, 1, 1);
	graphics.setPointSize(6);
	graphics.drawPixel(position.x,position.y);

	//draw 'nose'
	graphics.setColour(1, 0, 0);
	graphics.setPointSize(2);
	NA_Vector noseOffset = currentVelocity;
	noseOffset.normalise();
	graphics.drawPixel(position.x+(noseOffset.x*5.0f), position.y+(noseOffset.y*5.0f));

	

}

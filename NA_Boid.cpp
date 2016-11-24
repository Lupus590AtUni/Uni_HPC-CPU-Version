#include "NA_Boid.h"
#include "stdafx.h"

NA_Boid::NA_Boid()
{

}

void NA_Boid::update()
{
	extern vector<NA_Boid> boidList;
	//TODO: find nearby boids and only consider them



	/*
	//alignment - align self to average heading
	//calc sum velocity
	NA_Vector sumVelocity;
	for (int i = 0; i < BOID_MAX; i++)
	{
		sumVelocity.x = boidList[i].currentVelocity.x + sumVelocity.x;
		sumVelocity.y = boidList[i].currentVelocity.y + sumVelocity.y;
	}
	//convert to average
	sumVelocity.x = sumVelocity.x / (BOID_MAX);
	sumVelocity.y = sumVelocity.y / (BOID_MAX);

	newVelocity = sumVelocity; //TODO: maybe should change this gradually
	*/





	//cohesion - move towards average position
	//calc sum position
	NA_Vector sumPosition;
	for (int i = 0; i < BOID_MAX; i++)
	{
		sumPosition.x = boidList[i].position.x + position.x;
		sumPosition.y = boidList[i].position.y + position.y;
	}
	//convert to average
	sumPosition.x = sumPosition.x / (BOID_MAX);
	sumPosition.y = sumPosition.y / (BOID_MAX);

	cout << "average pos: X: " << sumPosition.x << " Y:" << sumPosition.y << "\n";

	newVelocity = NA_Vector::twoPointsIntoVector(position, sumPosition); //modify velocity to head towards the average position






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

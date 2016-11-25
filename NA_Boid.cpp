#include "NA_Boid.h"
#include "stdafx.h"

//const 
float BOID_SPEED_MAX = 2.0f;
//const 
float BOID_RESPECT_DIST = 25.0f; //boid to boid spacing
//const 
float BOID_ROTATE_MAX = 5.0f;
//const 
float BOID_MOUSE_FEAR = 50.0f; //boid distance from mouse
//const
float BOID_COHESION_WEIGHTING = 0.01f;

NA_Boid::NA_Boid()
{

}

void NA_Boid::update()
{
	extern vector<NA_Boid> boidList;
	extern NA_MathsLib na_maths;
	extern cRenderClass graphics;
	//TODO: find nearby boids and only consider them



	//alignment - align self to average heading
	//calc sum velocity
	NA_Vector sumVelocity;
	for (int i = 0; i < BOID_MAX; i++)
	{
		sumVelocity.x += boidList[i].currentVelocity.x;
		sumVelocity.y += boidList[i].currentVelocity.y;
	}
	//convert to average
	sumVelocity.x = sumVelocity.x / (BOID_MAX);
	sumVelocity.y = sumVelocity.y / (BOID_MAX);

	//cout << "average vel: X: " << sumVelocity.x << " Y:" << sumVelocity.y << "\n";

	newVelocity = sumVelocity; //TODO: maybe should change this gradually
	


	
	//cohesion - move towards average position
	//calc sum position
	NA_Vector sumPosition;
	for (int i = 0; i < BOID_MAX; i++)
	{
		sumPosition.x += boidList[i].position.x;
		sumPosition.y += boidList[i].position.y;
	}
	//convert to average
	sumPosition.x = sumPosition.x / (BOID_MAX);
	sumPosition.y = sumPosition.y / (BOID_MAX);


	//TODO: if i'm close already maybe i should go slower
	NA_Vector temp = NA_Vector::twoPointsIntoVector(position, sumPosition); //modify velocity to head towards the average position
	
	temp.scale(BOID_COHESION_WEIGHTING);

	newVelocity.x += temp.x;
	newVelocity.y += temp.y;


	//separation
	for (int i = 0; i < BOID_MAX; i++)
	{
		if (&boidList[i] != this) //ignore self
		{
			NA_Vector d = NA_Vector::twoPointsIntoVector(boidList[i].position, position);
			if (d.length() < BOID_RESPECT_DIST)
			{
				newVelocity = d; //TODO: what if near multiple boids?
			}
		}
	}

	if (graphics.mouseIsScary)
	{
		NA_Vector d = NA_Vector::twoPointsIntoVector(graphics.mousePos, position);
		//cout << "mouse dist: " << d.length() << "\n";
		if (d.length() < BOID_MOUSE_FEAR)
		{
			//cout << "AHHH A MOUSE!!!\n";

			newVelocity = d;

		}
	}

}

void NA_Boid::postUpdate()
{
	
	//TODO: enforce rotation limit
	//need to find angle between vectors: http://stackoverflow.com/questions/14066933/direct-way-of-computing-clockwise-angle-between-2-vectors

	currentVelocity = newVelocity;
	newVelocity = NA_Vector();//prepare vector for next update

	//boids should not break the speed limit
	if (currentVelocity.length() > BOID_SPEED_MAX)
	currentVelocity.normalise();
	currentVelocity.scale(BOID_SPEED_MAX);

	//if (currentVelocity.length() > BOID_SPEED_MAX) cout << "speed limit is poorly enforced\n";
	
	


	//move
	position.x += currentVelocity.x;
	position.y += currentVelocity.y;


	//screen wrap
	if (position.x < 0)
		position.x = SCREEN_WIDTH;
	if (position.x > SCREEN_WIDTH)
		position.x = 0;

	if (position.y < 0)
		position.y = SCREEN_HEIGHT;
	if (position.y > SCREEN_HEIGHT)
		position.y = 0;


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
	graphics.setPointSize(3);
	graphics.drawPixel(position.x,position.y);

	//draw 'nose'
	graphics.setColour(1, 0, 0);
	graphics.setPointSize(1);
	NA_Vector noseOffset = currentVelocity;
	noseOffset.normalise();
	graphics.drawPixel(position.x+(noseOffset.x*5.0f), position.y+(noseOffset.y*5.0f));

	

}

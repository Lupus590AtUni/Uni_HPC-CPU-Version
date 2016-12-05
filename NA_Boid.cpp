#include <iostream>
using std::cout;
#include "globals.h"
#include "cRenderClass.h"

#include <vector>
using std::vector;

#include "NA_Boid.h"
#include "NA_MathsLib.h"
#include "NA_Matrix.h"


NA_Boid::NA_Boid()
{

}

void NA_Boid::update()
{
	extern vector<NA_Boid> boidList;
	extern NA_MathsLib na_maths;
	extern cRenderClass graphics;

	vector<NA_Boid> shortBoidList;
	//find nearby boids and only consider them
	for (int i = 0; i < BOID_MAX; i++)
	{
		/*if (&boidList[i] == this) //don't add self  //TODO: BUG: boids disappear if this is active
		{
			continue;
		}*/
		if (NA_Vector::twoPointsIntoVector(position, boidList[i].position).length() < BIOD_SIGHT_RANGE)
		{
			shortBoidList.push_back(boidList[i]);
		}
	}

	int shortBoidListSize = shortBoidList.size();
	//alignment - align self to average heading
	//calc sum velocity
	NA_Vector sumVelocity;
	for (int i = 0; i < shortBoidListSize; i++)
	{
		sumVelocity.x += shortBoidList[i].currentVelocity.x;
		sumVelocity.y += shortBoidList[i].currentVelocity.y;
	}
	//convert to average
	sumVelocity.x = sumVelocity.x / (shortBoidListSize);
	sumVelocity.y = sumVelocity.y / (shortBoidListSize);

	//cout << "average vel: X: " << sumVelocity.x << " Y:" << sumVelocity.y << "\n";

	newVelocity = sumVelocity;
	


	
	//cohesion - move towards average position
	//calc sum position
	NA_Vector sumPosition;
	for (int i = 0; i < shortBoidListSize; i++)
	{
		sumPosition.x += shortBoidList[i].position.x;
		sumPosition.y += shortBoidList[i].position.y;
	}
	//convert to average
	sumPosition.x = sumPosition.x / (shortBoidListSize);
	sumPosition.y = sumPosition.y / (shortBoidListSize);


	//TODO: if i'm close already maybe i should go slower
	NA_Vector temp = NA_Vector::twoPointsIntoVector(position, sumPosition); //modify velocity to head towards the average position
	
	temp.scale(BOID_COHESION_WEIGHTING);

	newVelocity.x += temp.x;
	newVelocity.y += temp.y;


	//separation
	for (int i = 0; i < shortBoidListSize; i++)
	{
		if (&shortBoidList[i] != this) //ignore self //self is never in short list, this is left over from when using the full list
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

	//TODO: LOW: BUG: some boids stop
	//they stop when they interact with other boids
	//fudge stopped boids
	if (na_maths.aboutEqual(currentVelocity.length(), 0.0f))
	{
		currentVelocity.x = float(na_maths.dice(-100, 100)) / 100.0f;
		currentVelocity.y = float(na_maths.dice(-100, 100)) / 100.0f;
	}

}

void NA_Boid::postUpdate()
{
	
	//enforce rotation limit
	
	if (newVelocity.clockwiseAngle(currentVelocity) > BOID_ROTATE_MAX && currentVelocity.clockwiseAngle(newVelocity) > BOID_ROTATE_MAX)
	{
		
		if (newVelocity.clockwiseAngle(currentVelocity) < currentVelocity.clockwiseAngle(newVelocity))//clockwise or counterclockwise?
		{
			
			NA_Matrix r = NA_Matrix(NA_Matrix::types::rotateZ, BOID_ROTATE_MAX);
			newVelocity = r.matrixXvector(newVelocity);
		}
		else
		{

			NA_Matrix r = NA_Matrix(NA_Matrix::types::rotateZ, -BOID_ROTATE_MAX);
			newVelocity = r.matrixXvector(newVelocity);
		}
	}
	

	//boids should not break the speed limit
	if (newVelocity.length() > BOID_SPEED_MAX)
		newVelocity.normalise();
	newVelocity.scale(BOID_SPEED_MAX);

	//if (newVelocity.length() > BOID_SPEED_MAX) cout << "speed limit is poorly enforced\n";
	
	currentVelocity = newVelocity; //TODO: Acceleration limit?
	newVelocity = NA_Vector();//prepare vector for next update

	//move
	position.x += currentVelocity.x;
	position.y += currentVelocity.y;


	//screen wrap
	if (position.x < 0)
		position.x += SCREEN_WIDTH;
	if (position.x > SCREEN_WIDTH)
		position.x -= SCREEN_WIDTH;

	if (position.y < 0)
		position.y += SCREEN_HEIGHT;
	if (position.y > SCREEN_HEIGHT)
		position.y -= SCREEN_HEIGHT;
	
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

	short int bodyColourR, bodyColourG, bodyColourB;
	bodyColourR = 1;
	bodyColourG = 1;
	bodyColourB = 1;

	if (DEBUG_HIGHLIGHT_FIRST_BOID)
	{
		extern vector<NA_Boid> boidList;
		if (this == &boidList[0])
		{
			bodyColourR = 0;
			bodyColourG = 1;
			bodyColourB = 0;
		}
	}

	//draw body
	graphics.setColour(bodyColourR, bodyColourG, bodyColourB);
	graphics.setPointSize(3);
	graphics.drawPixel(position.x,position.y);

	//draw 'nose'
	graphics.setColour(1, 0, 0);
	graphics.setPointSize(1);
	NA_Vector noseOffset = currentVelocity;
	noseOffset.normalise();
	graphics.drawPixel(position.x+(noseOffset.x*5.0f), position.y+(noseOffset.y*5.0f));

}

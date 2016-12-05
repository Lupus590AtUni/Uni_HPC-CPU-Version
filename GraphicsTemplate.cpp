// GraphicsTemplate.cpp
// 
//////////////////////////////////////////////////////////////////////////////////////////
// includes 
//////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
using std::cout;
#include <tchar.h>
#include <windows.h>
#include "GL/glut.h"
#include "globals.h"
#include "cRenderClass.h"
#include <vector>
using std::vector;
//
#include "NA_Boid.h"
#include "NA_MathsLib.h"
#include "NA_Timer.h"

//////////////////////////////////////////////////////////////////////////////////////////
// externals 
//////////////////////////////////////////////////////////////////////////////////////////
extern cRenderClass graphics;
extern NA_MathsLib na_maths;

vector<NA_Boid> boidList; //not really a list

//////////////////////////////////////////////////////////////////////////////////////////
// renderScene() - render the scene
//////////////////////////////////////////////////////////////////////////////////////////
void renderScene()
{
	for (int i = 0; i < BOID_MAX; i++)
	{
		boidList[i].draw();
	}

	if (DEBUG_AVERAGE_POS)
	{
		NA_Vector sumPosition;
		for (int i = 0; i < BOID_MAX; i++)
		{
			sumPosition.x += boidList[i].position.x;
			sumPosition.y += boidList[i].position.y;
		}
		//convert to average
		sumPosition.x = sumPosition.x / (BOID_MAX);
		sumPosition.y = sumPosition.y / (BOID_MAX);

		graphics.setPointSize(10);
		graphics.setColour(0.0f, 0.0f, 1.0f);
		graphics.drawPixel(sumPosition.x, sumPosition.y);
	}

	// render the scene
	graphics.render();
}

//////////////////////////////////////////////////////////////////////////////////////////
// update() - update function
//////////////////////////////////////////////////////////////////////////////////////////
void update()
{
	static bool first = true;

	if (first)
		renderScene();
	first = false;

	//renderScene();
	//cout << "first render done\n";
	// add any update code here...
	static NA_Timer fpsCap;//wait if FPS is too high (if boids move too fast)
	fpsCap.restart();
	if (DEBUG_PRINT_POS_OF_ALL_BOIDS)
		fpsCap.setDuration(DEBUG_UPDATE_FREQUENCY);
	else
		fpsCap.setDuration(1.0f / FPS_MAX);


	if (first && !DEBUG_RUN_TOP_SPEED)
		fpsCap.wait();

	for (int i = 0; i < BOID_MAX; i++)
	{
		boidList[i].update();
	}

	if (DEBUG_PRINT_POS_OF_ALL_BOIDS || DEBUG_PRINT_POS_OF_FIRST_BOID) system("cls");
	for (int i = 0; i < BOID_MAX; i++)
	{
		boidList[i].postUpdate();
		if (DEBUG_PRINT_POS_OF_ALL_BOIDS || DEBUG_PRINT_POS_OF_FIRST_BOID && i == 0) cout << "pos: " << boidList[i].position.x << " " << boidList[i].position.y << "\n";
	}



	//cout << "updates done, waiting\n";

	extern void debugMouse();
	//debugMouse();
	//cout << "mouse scary? " << graphics.mouseIsScary << "\n";
	
	if (!DEBUG_RUN_TOP_SPEED) fpsCap.wait();

	// always re-render the scene..
	renderScene();
	//cout << " post render done\n";
}



//////////////////////////////////////////////////////////////////////////////////////////
// _tmain() - program entry point
//////////////////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{	
	// init glut stuff..
	graphics.create(argc, argv);

	// good place for one-off initialisations and objects creation..

	//make all boids
	na_maths.seedDice();
	for (int i = 0; i < BOID_MAX; i++)
	{
		NA_Boid temp;
		temp.position.x = na_maths.dice(SCREEN_WIDTH);
		temp.position.y = na_maths.dice(SCREEN_HEIGHT);

		//temp.position.x = 100.0f;
		//temp.position.y = 100.0f;

		temp.currentVelocity.x = float(na_maths.dice(-100,100))/100.0f;
		temp.currentVelocity.y = float(na_maths.dice(-100, 100))/100.0f;

		boidList.push_back(temp);

		//cout << "POS: X: " << temp.position.x << " Y: " << temp.position.y << "\n";
		//cout << "VEL: X: " << temp.currentVelocity.x << " Y: " << temp.currentVelocity.y << "\n";

		//NA_Vector t = temp.currentVelocity;
		//t.normalise();
		//cout << "NV: X: " << t.x << " Y: " << t.y << "\n\n";


	}


	// enter game loop..
	graphics.loop();	

	return 0;
}





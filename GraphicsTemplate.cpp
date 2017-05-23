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
#include <vector>
using std::vector;
//
#include "NA_Boid.h"
#include "NA_MathsLib.h"

//http://www.cplusplus.com/reference/chrono/high_resolution_clock/now/
#include <ctime>
#include <ratio>
#include <chrono>
using namespace std::chrono;

//http://www.cplusplus.com/reference/string/stoi/
#include <string> 

//////////////////////////////////////////////////////////////////////////////////////////
// externals 
//////////////////////////////////////////////////////////////////////////////////////////

extern NA_MathsLib na_maths;

vector<NA_Boid> boidList; //not really a list





//////////////////////////////////////////////////////////////////////////////////////////
// _tmain() - program entry point
//////////////////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{	
	int loopCount;
	if (argc != 3)
	{
		std::cerr << "usage: "<< argv[0] << " <boidCount> <loopCount> \n";
		return -1;
	}
	else
	{
		BOID_MAX = std::stoi(argv[1], NULL); //http://www.cplusplus.com/reference/string/stoi/
		loopCount = std::stoi(argv[2], NULL);
		
	}






	//make all boids
	na_maths.seedDice(0);
	for (int i = 0; i < BOID_MAX; i++)
	{
		NA_Boid temp;
		temp.position.x = na_maths.dice(SCREEN_WIDTH);
		temp.position.y = na_maths.dice(SCREEN_HEIGHT);

		temp.currentVelocity.x = float(na_maths.dice(-100,100))/100.0f;
		temp.currentVelocity.y = float(na_maths.dice(-100, 100))/100.0f;

		boidList.push_back(temp);


	}

	// actual simulation bit, start timer
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
	
	for (int loop = 0; loop < loopCount; loop++)
	{
		// for each boid, call update and then postUpdate
		for (int i = 0; i < BOID_MAX; i++)
		{
			boidList[i].update();
		}
		for (int i = 0; i < BOID_MAX; i++)
		{
			boidList[i].postUpdate();
		}
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	// calculate and output the time taken
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	cout << time_span.count() << "\n";

	return 0;
}





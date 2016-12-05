#pragma once




//////////////////////////////////////////////////////////////////////////////////////////
// constants 
//////////////////////////////////////////////////////////////////////////////////////////
const int SCREEN_WIDTH	= 500;
const int SCREEN_HEIGHT = 500;

const int FPS_MAX = 60;//anything bigger than 60 fps is pointless on most machines as the monitor won't take more

const int BOID_MAX = 50;

const float BOID_SPEED_MAX = 2.0f;
const float BOID_RESPECT_DIST = 25.0f; //boid to boid spacing
const float BOID_ROTATE_MAX = 0.00000000001f;
const float BOID_MOUSE_FEAR = 50.0f; //boid distance from mouse
const float BOID_COHESION_WEIGHTING = 0.0025f;

const bool DEBUG_AVERAGE_POS = false;
const bool DEBUG_HIGHLIGHT_FIRST_BOID = true;
const bool DEBUG_PRINT_POS_OF_FIRST_BOID = true;
const bool DEBUG_PRINT_POS_OF_ALL_BOIDS = false;
const float DEBUG_UPDATE_FREQUENCY = 0.00000001f;
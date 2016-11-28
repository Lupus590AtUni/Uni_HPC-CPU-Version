// cRenderClass.cpp
// 
//////////////////////////////////////////////////////////////////////////////////////////
// includes 
//////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
using std::cout;
#include "globals.h"
#include "cRenderClass.h"

//////////////////////////////////////////////////////////////////////////////////////////
// Declarations 
//////////////////////////////////////////////////////////////////////////////////////////
cRenderClass graphics( SCREEN_WIDTH, SCREEN_HEIGHT );

//////////////////////////////////////////////////////////////////////////////////////////
// cRenderClass() - constructor 
//////////////////////////////////////////////////////////////////////////////////////////
cRenderClass::cRenderClass(const int w, const int h)
{
	m_sw = w;
	m_sh = h;

	int total_count = w*h*3;

	m_buffer = new float[total_count];

	for( int i=0; i<total_count; i++ )
	{
		m_buffer[i] = 0;
	}

	m_point_size = 1;
}

//////////////////////////////////////////////////////////////////////////////////////////
// cRenderClass() - destructor 
//////////////////////////////////////////////////////////////////////////////////////////
cRenderClass::~cRenderClass()
{
}

//////////////////////////////////////////////////////////////////////////////////////////
// loop() - enters game loop
//////////////////////////////////////////////////////////////////////////////////////////
void cRenderClass::loop()
{
	glutMainLoop();
}

//////////////////////////////////////////////////////////////////////////////////////////
// initialize glut stuff
//////////////////////////////////////////////////////////////////////////////////////////
void cRenderClass::create(int argc, _TCHAR* argv[])
{
	// initialise the glut library
	glutInit(&argc, argv);

	// set up the initial display mode
	// need both double buffering and z-buffering
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// set the initial window position
	glutInitWindowPosition(100, 100);

	// set the initial window size
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// create and name the window
	glutCreateWindow("Wow!");

	// reshape callback for current window
	glutReshapeFunc(winReshapeFunc);

	// set display callback for current window
	glutDisplayFunc(renderScene);	

	glutMouseFunc(click);
	glutKeyboardFunc(key);
	glutMotionFunc(mouse);
	glutPassiveMotionFunc(mouse);

	// set up the global idle callback
	glutIdleFunc(update);
}

//////////////////////////////////////////////////////////////////////////////////////////
// clear() - clears out the render buffer 
//////////////////////////////////////////////////////////////////////////////////////////
void cRenderClass::clear()
{
	memset( m_buffer, 0, sizeof(float)*m_sw*m_sh*3 );
}

//////////////////////////////////////////////////////////////////////////////////////////
// setPointSize() - set the pixel size 
//////////////////////////////////////////////////////////////////////////////////////////
void cRenderClass::setPointSize(int size)
{
	m_point_size = size;
}

//////////////////////////////////////////////////////////////////////////////////////////
// drawPixel() -  
//////////////////////////////////////////////////////////////////////////////////////////
void cRenderClass::drawPixel(int x, int y)
{
	int start, end;

	start = -(m_point_size/2);
	end	= (int)((m_point_size/2.0f) + 0.5);

	for( int i=start; i<end; i++ )
	{
		for( int j=start; j<end; j++ )
		{
			if( (x+j < 0) || (x+j >= m_sw) )
				continue;

			if( (y+i < 0) || (y+i >= m_sh) )
				continue;

			m_buffer[(((y+i)*m_sw+(x+j))*3) + 0] = m_colour.r;
			m_buffer[(((y+i)*m_sw+(x+j))*3) + 1] = m_colour.g;
			m_buffer[(((y+i)*m_sw+(x+j))*3) + 2] = m_colour.b;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// render() - renders this buffer to screen 
//////////////////////////////////////////////////////////////////////////////////////////
void cRenderClass::render()
{
	// clear the back buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawPixels( m_sw, m_sh, GL_RGB, GL_FLOAT, m_buffer );

	// swap the buffers of the current window
	glutSwapBuffers();

	// clear out the buffer
	clear();
}

//////////////////////////////////////////////////////////////////////////////////////////
// setColour() - sets the current colour 
//////////////////////////////////////////////////////////////////////////////////////////
void cRenderClass::setColour(float r, float g, float b)
{
	m_colour.r = r;
	m_colour.g = g;
	m_colour.b = b;
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// winReshapeFunc() - gets called initially and whenever the window get resized
// resizing has been locked
//////////////////////////////////////////////////////////////////////////////////////////
void winReshapeFunc(GLint w, GLint h)
{
	// specify current matrix
	glMatrixMode(GL_PROJECTION);

	// load an identity matrix
	glLoadIdentity();	

	// create a projection matrix... i.e. 2D projection onto xy plane
	glOrtho( -SCREEN_WIDTH, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// set up the viewport
	glViewport
	(
		0,				// lower left x position
		0,				// lower left y position
		(GLsizei) SCREEN_WIDTH,	// viewport width
		(GLsizei) SCREEN_HEIGHT	// viewport height
	);
}

int mouseRawX, mouseRawY;


void debugMouse()
{
	cout << "Mouse:\n";
	cout << " raw pos : " << mouseRawX << ", " << mouseRawY << "\n";
	cout << " adjusted pos : " << graphics.mousePos.x << ", " << graphics.mousePos.y << "\n";
	
	
	//draw a dot under the mouse for debugging
	graphics.setColour(0.0f, 0.0f, 1.0f);
	graphics.setPointSize(3);
	graphics.drawPixel(graphics.mousePos.x, graphics.mousePos.y);
	graphics.setColour(1.0f, 0.0f, 0.0f);
	graphics.setPointSize(1);
	graphics.drawPixel(graphics.mousePos.x, graphics.mousePos.y);

}

void adjustMouse()
{
	graphics.mousePos.y = -graphics.mousePos.y + SCREEN_HEIGHT;
}

void mouse(int x, int y)
{
	mouseRawX = x;
	mouseRawY = y;

	graphics.mousePos.x = x;
	graphics.mousePos.y = y;

	adjustMouse();
}

void key(unsigned char c, int x, int y)
{

}

void click(int button, int state, int x, int y)
{
	//cout << "click\n";
	if (button == GLUT_LEFT_BUTTON)
	{
		//cout << "left mouse\n";
		if (state == GLUT_DOWN)
		{
			//cout << "down\n";
			graphics.mouseIsScary = true;
			mouse(x, y);
			//cout << "mouseIsScary " << mouseIsScary << "\n";
		}
		else
		{
			graphics.mouseIsScary = false;
		}
	}

}
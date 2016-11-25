#include "stdafx.h"
#include "NA_Vector.h"

class cRenderClass
{
public:

	bool mouseIsScary = false;
	NA_Vector mousePos;

	cRenderClass(const int, const int);
	~cRenderClass();

	void create(int argc, _TCHAR* argv[]);
	void loop();

	void clear();

	void render();
	void setColour(float, float, float);
	void setPointSize(int);
	void drawPixel(int, int);

private:

	int		 m_sw, m_sh;
	int		 m_point_size;
	float	*m_buffer;
	sRGB	 m_colour;
};
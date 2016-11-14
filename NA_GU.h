//my graphics utilities
#pragma once

struct NA_Pixel
{
	sVec2f position;
	sRGB colour; 
};

struct NA_Line
{
	NA_Pixel start;
	NA_Pixel end;
};

struct NA_ClipBoundry
{
	sVec2f min;
	sVec2f max;
};

class NA_GU
{
private:
	void n_ds(const NA_Pixel start, const NA_Pixel end);
	void n_vertical(const NA_Pixel start, const NA_Pixel end);
	void n_dda(const NA_Pixel start, const NA_Pixel end);
	void drawCirclePoints(const NA_Pixel centre, const NA_Pixel point);
	bool visable(NA_Pixel clipMe);
	NA_Line clip(NA_Line clipMe);
	void setColour(sRGB c);
	sRGB interpolate(const NA_Pixel p1, const NA_Pixel p, const NA_Pixel p2);
  
  void directScan(NA_Pixel start, NA_Pixel end);
	void bresenham(NA_Pixel start, NA_Pixel end);
	void DDA(NA_Pixel start, NA_Pixel end);

	NA_ClipBoundry clipBoundry;

public:
	NA_GU();
	~NA_GU();
	
  void drawLine(const sVec2f start, const sVec2f end);//abstracts algorithm
	
	void drawCircle(NA_Pixel centre, const float radius);
	void drawTriangle(NA_Pixel p1, NA_Pixel p2, NA_Pixel p3);
};
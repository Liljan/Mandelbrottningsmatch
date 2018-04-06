#pragma once

class Image
{
public:
	Image(const int w, const int h);
	~Image();

	void SetPixel(int x, int y, float r, float g, float b);
	void FillImage(float r, float g, float b);
	
	void ExportPPM(const char* fileName);
	void ExportPGM(const char* fileName);

private:

	float * m_pixelValues;
	const int WIDTH, HEIGHT;
};

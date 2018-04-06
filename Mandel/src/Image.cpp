#include "..\include\Image.h"

#include <iostream>
#include <fstream>
#include <algorithm>

Image::Image(const int w, const int h) : WIDTH(w), HEIGHT(h)
{
	m_pixelValues = new float[w * h * 3];
}


Image::~Image()
{
	delete[] m_pixelValues;
}

void Image::SetPixel(int x, int y, float r, float g, float b)
{
	m_pixelValues[(x + y * WIDTH) * 3] = r;
	m_pixelValues[(x + y * WIDTH) * 3 + 1] = g;
	m_pixelValues[(x + y * WIDTH) * 3 + 2] = b;
}

void Image::FillImage(float r, float g, float b)
{
	//#pragma omp parallel for
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			SetPixel(x, y, r, g, b);
		}
	}
}

void Image::ExportPPM(const char * fileName)
{
	std::cout << "Beginning image saving..." << std::endl;
	if (WIDTH == 0 || HEIGHT == 0) { fprintf(stderr, "Can't save an empty image\n"); return; }

	std::ofstream out_file;

	std::string file_name_str = fileName;
	file_name_str.append(".ppm");

	try {
		out_file.open(file_name_str.c_str(), std::ios::binary);					// Need to spec. binary mode for Windows
		if (out_file.fail()) throw("Can't open output file");

		// Specific header for PPM images
		out_file << "P3\n";
		out_file << WIDTH << " " << HEIGHT << "\n";
		out_file << "255\n";
		
		//float* current_pixel = m_pixelValues;

		#pragma omp parallel for
		for (int h = 0; h < HEIGHT; ++h)
		{
			for (int w = 0; w < WIDTH; ++w)
			{
				int index = h * WIDTH + w;
				int r = std::max(0.0f, roundf(std::min(1.f, m_pixelValues[index]) * 255));
				int g = std::max(0.0f, roundf(std::min(1.f, m_pixelValues[index + 1]) * 255));
				int b = std::max(0.0f, roundf(std::min(1.f, m_pixelValues[index + 2]) * 255));

				out_file << static_cast<char>(r) << static_cast<char>(g) << static_cast<char>(b);
			}
		}

		out_file.close();
		std::cout << "Successfully saved image!" << std::endl;
	}
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		out_file.close();
	}
}

void Image::ExportPGM(const char * fileName)
{
	std::cout << "Beginning image saving..." << std::endl;
	if (WIDTH == 0 || HEIGHT == 0) { fprintf(stderr, "Can't save an empty image\n"); return; }

	std::ofstream out_file;

	std::string file_name_str = fileName;
	file_name_str.append(".pgm");

	try {
		out_file.open(file_name_str.c_str(), std::ios::binary);					// Need to spec. binary mode for Windows
		if (out_file.fail()) throw("Can't open output file");
		out_file << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";	// Specific header for PPM images

		float r, g, b;
		float* current_pixel = m_pixelValues;

		// loop over each pixel in the image, clamp from 0 to 255, convert to char format and write to file. 
		for (int h = 0; h < HEIGHT; ++h) {
			for (int w = 0; w < WIDTH; ++w) {

				r = std::max(0.0f, roundf(std::min(1.f, current_pixel[0]) * 255));
				g = std::max(0.0f, roundf(std::min(1.f, current_pixel[1]) * 255));
				b = std::max(0.0f, roundf(std::min(1.f, current_pixel[2]) * 255));

				out_file << static_cast<char>(r) << static_cast<char>(g) << static_cast<char>(b);
				current_pixel += 3;
			}
		}
		out_file.close();
		std::cout << "Successfully saved image!" << std::endl;
	}
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		out_file.close();
	}
}

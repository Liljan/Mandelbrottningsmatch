#include <iostream>
#include "Image.h"

int main()
{
	Image img(720, 544);
	img.FillImage(0.5f, 0.5f, 0.5f);

#pragma omp parallel for
	for (int i = 0; i < 100; ++i)
		std::cout << i << " ";

	img.ExportPPM("TestImage");

	return 0;
}
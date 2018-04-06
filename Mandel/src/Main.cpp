#include <iostream>
#include <complex>
#include "Image.h"

int MandelbrotCalculation(const std::complex<float> & c, int maxIter)
{
	// iterates z = z + c until |z| >= 2 or maxiter is reached,
	// returns the number of iterations.
	std::complex<float> z = c;
	int n = 0;
	for (; n < maxIter; ++n)
	{
		if (std::abs(z) >= 2.0) break;
		z = z*z + c;
	}
	return n;
}


int main()
{
	const int WIDTH = 2560;
	const int HEIGHT = 1440;

	const std::complex<float> center(-0.7f, 0.0f);
	const std::complex<float> span(2.7f, -(4.f/3.0f) * 2.7f * HEIGHT / WIDTH);
	const std::complex<float> enter = center -0.5f*span;

	const int MAX_ITERATIONS = 100;

	Image img(WIDTH, HEIGHT);

	#pragma omp parallel for ordered schedule(dynamic)
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			std::complex<float> c = enter + std::complex<float>(x * span.real() / (WIDTH + 1),
				y * span.imag() / (HEIGHT + 1));

			int n = MandelbrotCalculation(c, MAX_ITERATIONS);

			float f = (float)n / MAX_ITERATIONS;
			//float f = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

			img.SetPixel(x, y, f, f, f);
		}
	}

	img.ExportPPM("Random Background");

	return 0;
}
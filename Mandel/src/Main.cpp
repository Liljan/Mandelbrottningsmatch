#include <iostream>

int main()
{
	#pragma omp parallel for
	for (int i = 0; i < 100; ++i)
		std::cout << i << " ";

	return 0;
}
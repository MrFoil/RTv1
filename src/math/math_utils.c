//
// Created by artem.rudencko on 9/25/2018.
//

#include "vector_math.h"

double randfrom(double min, double max)
{
	double range = (max - min);
	double div = RAND_MAX / range;
	return min + (rand() / div);
}

/*void decToHexa(int n) {
	// char array to store hexadecimal number
	uint8_t hexaDeciNum[100];

	ft_bzero(hexaDeciNum, 100);

	// counter for hexadecimal number array
	int i = 0;
	while (n != 0) {
		// temporary variable to store remainder
		int temp = 0;

		// storing remainder in temp variable.
		temp = n % 16;

		// check if temp < 10
		if (temp < 10) {
			hexaDeciNum[i] = temp + 48;
			i++;
		} else {
			hexaDeciNum[i] = temp + 55;
			i++;
		}

		n = n / 16;
	}
	ft_putstr(hexaDeciNum);
	ft_putstr("\n");
}*/
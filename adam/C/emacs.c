#include <stdio.h>

double square_reverse(const double *x, double *y, const int len)
{
	double sum = 0;

	for (int i = 0; i < len; i++)
	{
		sum += x[i];
		y[2 - i] = x[i] * x[i];
	}

	return sum;
}

int main(void)
{
	printf("\n");

	double in[] = {-11.0, 20.0, 100.0};
	double out[3];

	printf("109.0 = %f\n\n", square_reverse(in, out, 3));

	for (int i = 0; i < 3; i++)
	{
		printf("%f\n", out[i]);
	}

	printf("\n");
}
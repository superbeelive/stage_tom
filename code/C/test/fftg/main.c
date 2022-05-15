#include<stdio.h>
#include<stdlib.h>
#include<complex.h>
#include<fftw3.h>
int main() 
{
	fftw_plan = p;
	double test[]={3.920000,0.160000,5.630000,4.750000,0.370000,2.010000,5.870000,6.730000,9.870000,4.340000,9.950000,5.460000,8.420000,3.120000,3.670000,4.870000,3.280000,6.050000,4.650000,0.500000};
	p = fftw_plan_dft_r2c_1d(int n, double *in, fftw_complex *out,unsigned flags);

	return 0;
}


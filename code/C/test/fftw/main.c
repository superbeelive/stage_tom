#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<complex.h>
#include<fftw3.h>

int main() 
{
	unsigned int N = 20;
	int i;
	double *out = malloc(sizeof(double) * N);
	double list[]={3.920000,0.160000,5.630000,4.750000,0.370000,2.010000,5.870000,6.730000,9.870000,4.340000,9.950000,5.460000,8.420000,3.120000,3.670000,4.870000,3.280000,6.050000,4.650000,0.500000};
	double * values;
	values = malloc(sizeof(double)*N);
	fftw_plan p;
	p = fftw_plan_r2r_1d(N,values,out,FFTW_HC2R,FFTW_MEASURE);
	
	for(i=0;i<20;i++){
			values[i]=list[i];
	}
	
	fftw_execute(p);
	for(i=0;i<11;i++){
			printf("%f",out[i]);
	}
	fftw_destroy_plan(p);
	//fftw_free(out);
	free(out);
	return 0;
}


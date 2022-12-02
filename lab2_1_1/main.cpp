//func.c
#include <stdio.h>
#include <locale.h>
#include <cmath>
float y (float x, float d)
{
	if(x>1) d=sqrt(tan(pow(x,2)-1));
	if(x>=0 && x<=1) d=-2*x;
	if(x<0) d=exp(cos(x));
	return d;
}

int main(void)
{
	float x,d;
	printf("Enter x\n");
	scanf("%f",&x);
	printf("\ny(x)=%f",y(x,d));
	return(0);
}

#include <stdio.h>
#include <conio.h>
#include <locale.h>

int main(void)
{
	float x,y;
	printf("Enter x\n");
	scanf("%f",&x);
	if(x>1) y=sqrt(tan(pow(x,2)-1));
	if(x>=0 && x<=1) y=-2*x;
	if(x<0) y=exp(cos(x));
	printf("\ny=%f",y);
	return(0);
}
//func.c
#include <stdio.h>
#include <stdlib.h>

float F (float i, float a, float b, float c){
	float y;
	if ((a<0) && (c!=0)) y=a*i*i+b*i+c;
	 else if ((a>0) && (c=0)) y=-a/(i-c);
	  else y=a*(i+c);
	return y;
}
int main(){
	float xn,xk,dx,i,a,b,c;
	do{
		printf("input a, b, c, xn, xk, dx\n");
		scanf("%f%f%f%f%f%f",&a,&b,&c,&xn,&xk,&dx);
		if(xn==c||xk==c||xn==xk)
		 printf("input Error\n");
	}
	while((xn==c)||(xk==c)||(xn==xk));
	
	printf("|  x  |  F  |\n");
	for(i=xn;i<=xk;i+=dx)
	printf("|%5.2f|%5.2f|\n",i,F(i,a,b,c));
	getch();
	return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main(){
	float xn,xk,dx,i,a,b,c,F;
	do{
		printf("input a, b, c, xn, xk, dx\n");
		scanf("%f%f%f%f%f%f",&a,&b,&c,&xn,&xk,&dx);
		if(xn==c||xk==c||xn==xk)
		 printf("input Error\n");
	}
	while((xn==c)||(xk==c)||(xn==xk));
	
	printf("|  x  |  F  |\n");
	for(i=xn;i<=xk;i+=dx){
		if((a<0)&&(c!=0)) F=a*i*i+b*i+c;
		 else if((a>0)&&(c=0)) F=a/(i-c);
		  else F=a*(i+c);
	  	printf("|%5.2f|%5.2f|\n",i,F);
	}
	getch();
	return 0;

}
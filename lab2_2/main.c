#include <stdio.h>
#include <conio.h>
#include <locale.h>

int main(void){
	int a;
	printf("Enter the person's age: ",a);
	scanf("%d",&a);
	if(a>=0 && a<=13) printf("Boy");
	 else if(a>=14 && a<=20) printf("Young man");
	  else if(a>=21 && a<=70) printf("Man");
	   else if(a>=71) printf("The elder");
	    else printf("Error");
}
#include <stdio.h>
#include <stdlib.h>

void main(void){
	int i;
	int a[6]={0,5,2,-3,0,9};
	for(i=0;i<6;i++)
	printf("%d ",a[i]);
	
	int P=1;
	for(i=0; i<6; i+=2)
	P*=a[i];
	printf("\nProduct of array elements with even numbers:%d",P);
	
	int s=0;
	int k=0,p=0;
	for(i=0;i<6;i++){
		if(a[i]==0){
			k=i;
			break;
		}
	}
	for(i=6-1;i>=0;i--)
	if(a[i]==0){
		p=i;
		break;
	}
	for(i=k;i<=p;i++){
		s+=a[i];
	}
	printf("\nSum of array elements located between the first and last null element:%d",s);
	
	int j,temp=0;
	for(i=0;i<6-1;i++){
		for(j=0;j<6-1;j++)
		if(a[j]<a[j+1]){
			temp=a[j];
			a[j]=a[j+1];
			a[j+1]=temp;
		}
	}
	printf("\n");
	for(i=0;i<6;i++)
	printf("%d ",a[i]);
	getch();
	return 0;
}

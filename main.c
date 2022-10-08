#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	printf("Entre your first name: ");
	fgrts(first, 255, stdin);
	first[strlen(first)-1] = '\0'; /* remove the newline at the end */

<<<<<<< HEAD
	printf("Hello, %s!\n", name);
	return 0;
=======
	printf("Hello %s %s!\n", first, last);
	gets(last); /* buffer overflow? what's that? */

	printf("Hello %s %s!\n", first, last);
	return 0;
>>>>>>> lastname:main.c
}
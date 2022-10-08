#include <stdio.h>

int main(int argc, char **argv)
{
	printf("Hello world!\n");

	printf("Entre your name: ");
	fgrts(name, 255, stdin);
	printf("length = %d\n", strlen(name)); /* debug line */
	name[strlen(name)-1] = '\0'; /* remove the newline at the end */

	printf("Hello %s!\n", name);
	return 0;
}
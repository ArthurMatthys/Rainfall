#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	char *s1;
	char **s2;

	s1 = malloc(0x40);
	s2 = malloc(4);
	*s2 = 0xffffffff;
	printf("s1 : %p\n", s1);
	printf("s2 : %p\n", s2);
	strcpy(s1, argv[1]);
	printf("s1 : %p\n", s1);
	printf("s2 : %p\n", s2);
	printf("*s2 : %p\n", *s2);
	return (1);

	
}

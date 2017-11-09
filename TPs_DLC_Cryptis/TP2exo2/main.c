#include <stdio.h>
/*
 * main.c
 *
 *  Created on: 26 oct. 2014
 *      Author: quetzalli
 */
#define type_size 32
#define rotateleft(a,m) \
	unsigned int n = m;\
	unsigned int b = *a;\
	unsigned int leftshift = (b) << (n);\
	unsigned int c = *a;\
	unsigned int rightshift = (c) >> (type_size - (n)) ;\
	*a = leftshift | rightshift;

#define rotateright(a,m) \
	n = m;\
	b = *a;\
	rightshift = (b) >> (n);\
	c = *a;\
	leftshift = (c) << (type_size - (n)) ;\
	*a = leftshift | rightshift;

//pour int
//#define type_size 32
int main(int argc, char* argv[])
{
	unsigned int a = 14090240;
	//unsigned short a = 32768;
	printf("BeforeL: a=%x\n",a);
	rotateleft(&a,atoi(argv[1])%type_size);
	printf("AfterL: a=%x\n",a);
	rotateright(&a,atoi(argv[1])%type_size);
	printf("AfterR: a=%x\n",a);
}



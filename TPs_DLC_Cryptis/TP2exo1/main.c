
#include <stdio.h>
/*
 * main.c
 *
 *  Created on: 26 oct. 2014
 *      Author: quetzalli
 */
//pour short
//#define type_size 16
//pour int
#define type_size 32
//parametre à mettre en unsigned int si on veut travailler avec des int
void rotateleft(unsigned int* a, unsigned int n)
{
	//mettre en unsigned int
	unsigned int rightshift;
	unsigned int leftshift;
	unsigned int b = *a;
	leftshift = (b) << n;
	printf("LS:%08x\n",leftshift);
	b = *a;
	rightshift = (b) >> (type_size - n) ;
	printf("RS:%08x\n",rightshift);
	*a = leftshift | rightshift;
}
void rotateright(unsigned int* a, unsigned int n)
{
	//mettre en unsigned int
	unsigned int rightshift;
	unsigned int leftshift;
	unsigned int b = *a;
	rightshift = (b) >> n;
	printf("RS:%08x\n",rightshift);
	b = *a;
	leftshift = (b) << (type_size - n) ;
	printf("LS:%08x\n",leftshift);
	*a = leftshift | rightshift;
}
int main(int argc, char* argv[])
{
	unsigned int a = 14090240;

	//unsigned short a = 32768;
	printf("BeforeL: a=%08x\n",a);
	rotateleft(&a,atoi(argv[1])%type_size);
	printf("AfterL: a=%08x\n",a);
	rotateright(&a,atoi(argv[1])%type_size);
	printf("AfterR: a=%08x\n",a);
}



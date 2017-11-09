#include<stdio.h>
/*
 * main.c
 *
 *  Created on: 26 oct. 2014
 *      Author: quetzalli
 */
int main()
{
	char a;
	printf("taille d'un char: %u \n",sizeof(a));
	int b;
	printf("taille d'un int: %u \n",sizeof(b));
	short c;
	printf("taille d'un short: %u \n",sizeof(c));
	long int d;
	printf("taille d'un long int: %u \n",sizeof(d));
	long long int e;
	printf("taille d'un long long int: %u \n",sizeof(e));
	float f;
	printf("taille d'un float: %u \n",sizeof(f));
	double g;
	printf("taille d'un double: %u \n",sizeof(g));
	long double h;
	printf("taille d'un long double: %u \n",sizeof(h));
	size_t t;
	printf("taille d'un size_t: %u \n",sizeof(t));
	return 0;

}


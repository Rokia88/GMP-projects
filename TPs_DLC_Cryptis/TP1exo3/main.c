#include <stdio.h>
/*
 * main.c
 *
 *  Created on: 26 oct. 2014
 *      Author: quetzalli
 */
int main()
{
	unsigned char *ptr;
	float x;
	//x = 12.45;
	x= 0.40625;
	//x = -38.25;
	printf("\n");
	printf("Valeur de x : %f\n", x);
	ptr = (unsigned char *) &x;
	printf("\n");
	printf("Adresse de la variable x : %p\n", ptr);
	printf("\n");
	printf("Valeur de l’octet à l’adresse %p : %02X\n", ptr + 0, *(ptr + 0));
	printf("Valeur de l’octet à l’adresse %p : %02X\n", ptr + 1, *(ptr + 1));
	printf("Valeur de l’octet à l’adresse %p : %02X\n", ptr + 2, *(ptr + 2));
	printf("Valeur de l’octet à l’adresse %p : %02X\n", ptr + 3, *(ptr + 3));


	*(ptr + 2) = (char) 0x99;
	printf("\n");
	printf("Valeur de x : %f\n", x);
	printf("\n");
	return 0;
}


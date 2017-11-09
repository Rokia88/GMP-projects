#include <stdio.h>
/*
 * main.c
 *
 *  Created on: 26 oct. 2014
 *      Author: quetzalli
 */
int main()
{
	int a = 3;
	int b = 4;
	int c = 1;
	if((a==3 || b > 5) && c!=0)
	{
		printf("vrai1\n");
	}
	if(a==3 || b > 5 && c!=0)
	{
		printf("vrai2\n");
	}
	if(a==2 || b!= 4 || c < 7 )
	{
		printf("vrai3\n");
	}
	return 0;
}


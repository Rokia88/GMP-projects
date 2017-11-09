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
	if((a==3) || b > 5)
	{
		printf("vrai1\n");
	}
	printf("%d\n",a=3);
	if((a=3) && b!=b)
	{
		printf("vrai2\n");
	}
	if(1 && 3 )
	{
		printf("vrai3\n");
	}
	if(!0 || b)
		{
			printf("vrai4\n");
		}
	if(!0 && b)
			{
				printf("vrai5\n");
			}
	if(a)
			{
				printf("vrai6\n");
			}
	if(a=b)
	{
		printf("vrai7\n");
	}
	return 0;
}


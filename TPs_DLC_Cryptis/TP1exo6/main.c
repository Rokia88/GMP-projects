#include <stdio.h>
/*
 * main.c
 *
 *  Created on: 26 oct. 2014
 *      Author: quetzalli
 */
int main()
{
	int a = 0;
	int b = 2;
	int c = 5;
	if(b == c == a)
	{
		printf("vrai1\n");
	}
	else
	{
		printf("faux1\n");
	}

	/*if(b == c = a)
		{
			printf("vrai2\n");
		}
		else
		{
			printf("faux2\n");
		}*/

	//si tu inverse l'ordre de ces 2 if , on aura un résultat différent
	//car le deuxième if assigne à c et b la valeur 0, donc dans le premier if c==a vaut vrai
	//et donc b vaudra 1
	if(b = c == a)
			{
				printf("vrai4\n");
			}
			else
			{
				printf("faux4\n");
			}
	if(b = c = a)
			{
				printf("vrai3\n");
			}
			else
			{
				printf("faux3\n");
			}
	return 0;
}


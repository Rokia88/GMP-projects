#include <stdio.h>
/*
 * main.c
 *
 *  Created on: 26 oct. 2014
 *      Author: quetzalli
 */
int main(int argc, char* argv[])
{
	if (argc != 2)
	  {
	    printf("Usage : %s bit_size\n", argv[0]);
	    exit(-1);
	  }
	unsigned char a = atoi(argv[1]);
	printf("Before a = %u \n",a);
	unsigned char b;
	unsigned char c[8];
	unsigned char d[8];
	int i;
	for(i=0;i < 8; i++)
	{
		if( a & (1 << i))
		{
			c[i] = 1;
		}
		else
		{
			c[i] = 0;
		}
	}
	//permutation
	d[0] = c[3];
	d[1] = c[6];
	d[2] = c[1];
	d[3] = c[0];
	d[4] = c[2];
	d[5] = c[7];
	d[6] = c[4];
	d[7] = c[5];

	//b = (d[0] )  | (d[1] << 1) | (d[2] << 2) | (d[3] << 3)| (d[4] << 4)| (d[5] << 5)| (d[6] << 6)| (d[7] << 7);

	b = (d[7] )  | (d[6] << 1) | (d[5] << 2) | (d[4] << 3)| (d[3] << 4)| (d[2] << 5)| (d[1] << 6)| (d[0] << 7);

	printf("After a = %u \n",b);
	return 0;
}


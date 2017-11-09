/*
 * main.c
 *
 *  Created on: 19 oct. 2014
 *      Author: quetzalli
 */
#include <math.h>
#include <stdio.h>
#include "gmp.h"

int main(){

	mpz_t **Tab;
	*Tab = (mpz_t *)malloc(10 * sizeof(mpz_t));
	mpz_init_set_d((*Tab)[0], 12);
	gmp_printf("Tab[0] = %Zd\n", *Tab[0]);

	return 0;
}
/*int main()
{
	 mpz_t z_n;
	 mpz_init_set_ui(z_n,12345678);
	 size_t result = mpz_sizeinbase(z_n, 10);
	 //printf("********");
	 //printf("%u",result);
	 mpz_set_str(z_n, "1234", 0);
	 gmp_printf("%Zu",z_n);
	 return 0;
	//unsigned char c = 246;
	//printf("%d",c);
}*/


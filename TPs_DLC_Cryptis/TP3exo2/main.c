#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include "gmp.h"

void decipher(mpz_t a,mpz_t Z_c,mpz_t Z_n,mpz_t Z_d)
{
	mpz_set_ui(a,1);
	unsigned int bit_size = mpz_sizeinbase(Z_d, 2);
	int i;
	for(i = bit_size -1; i>=0; i--)
	{
		mpz_mul(a,a,a);
		mpz_mod(a,a,Z_n);
		if (mpz_tstbit(Z_d, i) == 1)
		   {
		      // result <-- result * base mod modulus
		      mpz_mul(a, a, Z_c);
		      mpz_mod(a, a, Z_n);
		    }
	}

}

void decipher_1(mpz_t a,mpz_t Z_c,mpz_t Z_n,mpz_t Z_d)
{
	mpz_set_ui(a,1);
	mpz_t b;
	mpz_init(b);
	mpz_set(b,Z_c);
	unsigned int bit_size = mpz_sizeinbase(Z_d, 2);
	int i;
	for(i = 0; i < bit_size; i++)
	{
		if (mpz_tstbit(Z_d, i) == 1)
		   {
		      // result <-- result * base mod modulus
		      mpz_mul(a, a, b);
		      mpz_mod(a, a, Z_n);
		    }
		mpz_mul(b, b, b);
	    mpz_mod(b, b, Z_n);
	}

}


int main()
{
	FILE *f;
	f = fopen("private_key.txt","r");
	if(f == NULL)
	{
		fputs("Echec du chargement du fichier!\n",stderr);
		exit(-1);
	}

	//Retrieve the size of the file
	struct stat file_status;
	char*file_buffer = NULL;
	stat("private_key.txt", &file_status);
	long file_size = file_status.st_size;
	file_buffer = (char *)malloc(file_size); //Allocate memory for the buffer using the size of the file
	fread(file_buffer,1,file_size,f);
	fclose(f);

	//récupere n et d
	char *tok = NULL;
	tok = strtok(file_buffer, "\n");
	char* n = (char*) malloc(strlen(tok)+1);
	strcpy(n,tok+4);
	//printf("%s\n",n);
	tok = strtok(NULL, "\n");
	char* d = (char*) malloc(strlen(tok)+1);
	strcpy(d,tok+4);
	//printf("%s\n",tok+4);
	mpz_t Z_n;
	mpz_t Z_d;
	mpz_t Z_c;
	mpz_t Z_m;
	mpz_t plain;
	mpz_inits(Z_n,Z_d,Z_c,Z_m,plain,NULL);
	mpz_set_str(Z_n,n,16);
	gmp_printf("n:0x%ZX\n",Z_n);
	mpz_set_str(Z_d,d,16);
	gmp_printf("d:0x%ZX\n",Z_d);

	f = fopen("ciphertext.txt","r");
	if(f == NULL)
		{
			fputs("Echec du chargement du fichier!\n",stderr);
			exit(-1);
		}

	file_buffer = NULL;
	stat("ciphertext.txt", &file_status);
	file_size = file_status.st_size;
	file_buffer = (char *)malloc(file_size); //Allocate memory for the buffer using the size of the file
	fread(file_buffer,1,file_size,f);
	fclose(f);

	tok = NULL;
	tok = strtok(file_buffer, "\n");
	char* c = (char*) malloc(strlen(tok)+1);
	strcpy(c,tok+4);
	mpz_set_str(Z_c,c,16);
	gmp_printf("c:0x%ZX\n",Z_c);


	f = fopen("plaintext.txt","r");
	if(f == NULL)
			{
				fputs("Echec du chargement du fichier!\n",stderr);
				exit(-1);
			}

	file_buffer = NULL;
	stat("plaintext.txt", &file_status);
	file_size = file_status.st_size;
	file_buffer = (char *)malloc(file_size); //Allocate memory for the buffer using the size of the file
	fread(file_buffer,1,file_size,f);
	fclose(f);

	tok = NULL;
	tok = strtok(file_buffer, "\n");
	char* m = (char*) malloc(strlen(tok)+1);
	strcpy(m,tok+4);
	mpz_set_str(Z_m,m,16);
	//gmp_printf("m:0x%ZX\n",Z_m);
	//left to right
	//decipher(plain,Z_c,Z_n,Z_d);

	//right to left
	decipher_1(plain,Z_c,Z_n,Z_d);
	gmp_printf("plain:0x%ZX\n",plain);
	if(mpz_cmp(plain,Z_m)==0)
	{
		printf("It is OK\n");
	}




}

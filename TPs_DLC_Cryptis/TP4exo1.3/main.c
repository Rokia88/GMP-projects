
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <openssl/md5.h>
#include "gmp.h"

void sign(mpz_t sig,const unsigned char* hash, mpz_t d, mpz_t n)
	{
		mpz_t m;
		mpz_init(m);
		mpz_set_str(m,hash,16);
		gmp_printf("h before reduction :0x%ZX \n",m);
		mpz_mod(m,m,n);
		mpz_powm(sig,m,d,n);
		gmp_printf("h :0x%ZX \n",m);
		gmp_printf("sig :0x%ZX \n",sig);
		//mpz_clear(m);
	}

void verify(mpz_t sig, char* filename,char* keyfile)
{
		FILE* f = fopen(filename,"r");
		if(f == NULL)
		{
			fputs("Echec du chargement du fichier!\n",stderr);
			exit(-1);
		}

		//Retrieve the size of the file
		struct stat file_status;
		char*file_buffer = NULL;
		stat(filename, &file_status);
		long file_size = file_status.st_size;
		file_buffer = (char *)malloc(file_size); //Allocate memory for the buffer using the size of the file
		fread(file_buffer,1,file_size,f);
		fclose(f);

		unsigned char hash[MD5_DIGEST_LENGTH];
		unsigned char *h= (unsigned char*) malloc(8);
		unsigned char *h_f= (unsigned char*) malloc(MD5_DIGEST_LENGTH*2);
		MD5(file_buffer, strlen(file_buffer), hash);
		for (int i= 0; i< MD5_DIGEST_LENGTH; ++i)
		{
			sprintf(h,"%x",hash[i]);
			strcat(h_f,h);
		}
		printf("hash du fichier:%s \n",h_f);

		mpz_t m;
		mpz_init(m);
		mpz_set_str(m,h_f,16);

		//charger la clé
		f = fopen(keyfile,"r");
			if(f == NULL)
				{
					fputs("Echec du chargement de la clef!\n",stderr);
					exit(-1);
				}
		stat(keyfile, &file_status);
		file_buffer = NULL;
		file_size = file_status.st_size;
		file_buffer = (char *)malloc(file_size);
		fread(file_buffer,1,file_size,f);
		fclose(f);

		//récupere n et e
		char *tok = NULL;
		tok = strtok(file_buffer, "\n");
		char* n = (char*) malloc(strlen(tok)+1);
		strcpy(n,tok);
		tok = strtok(NULL, "\n");

		mpz_t Z_n;
		mpz_t Z_e;
		mpz_inits(Z_n,Z_e,NULL);
		mpz_set_str(Z_n,n,10);
		gmp_printf("n:0x%ZX\n",Z_n);
		mpz_set_str(Z_e,tok,10);
		gmp_printf("e:0x%ZX\n",Z_e);

		mpz_t v;
		mpz_init(v);
		mpz_mod(m,m,Z_n);
		gmp_printf("h:0x%ZX\n",m);
		mpz_powm(v,sig,Z_e,Z_n);
		if(mpz_cmp(v,m)==0)
		{
			printf("verification successful\n");
		}
		mpz_clears(Z_n,Z_e,m,v,NULL);
}

int main(int argc, char* argv[])
{
	char* filename;
	char* privatekey;
	/*if(argc < 3)
		{
			printf("nombre insuffisant d'arguments\n");
			exit(-1);
		}*/
	filename= argv[1];
	privatekey = argv[2];
	FILE *f;
	f = fopen(filename,"r");
	if(f == NULL)
	{
		fputs("Echec du chargement du fichier!\n",stderr);
		exit(-1);
	}

	//Retrieve the size of the file
	struct stat file_status;
	char*file_buffer = NULL;
	stat(filename, &file_status);
	long file_size = file_status.st_size;
	file_buffer = (char *)malloc(file_size); //Allocate memory for the buffer using the size of the file
	fread(file_buffer,1,file_size,f);
	fclose(f);
	unsigned char hash[MD5_DIGEST_LENGTH];
	unsigned char *h= (unsigned char*) malloc(8);//8 juste pour contenir 2 digits comme '7b'
	unsigned char *h_f= (unsigned char*) malloc(MD5_DIGEST_LENGTH*2);// pour contenir les 32 digits
	MD5(file_buffer, strlen(file_buffer), hash);
	for (int i= 0; i< MD5_DIGEST_LENGTH; ++i)
	{
			sprintf(h,"%x",hash[i]);
		    strcat(h_f,h);
	}
	printf("hash du fichier:%s \n",h_f);


	f = fopen(privatekey,"r");
	if(f == NULL)
		{
			fputs("Echec du chargement de la clef!\n",stderr);
			exit(-1);
		}
	stat(privatekey, &file_status);
	file_buffer = NULL;
	file_size = file_status.st_size;
	file_buffer = (char *)malloc(file_size);
	fread(file_buffer,1,file_size,f);
	fclose(f);

	//recuperer d et n
	char *tok = NULL;
	tok = strtok(file_buffer, "\n");
	char* n = (char*) malloc(strlen(tok)+1);
	strcpy(n,tok);
	tok = strtok(NULL, "\n");

	mpz_t Z_n;
	mpz_t Z_d;
	mpz_t sig;
	mpz_inits(Z_n,Z_d,sig,NULL);
	mpz_set_str(Z_n,n,10);
	gmp_printf("n:0x%ZX\n", Z_n);
	mpz_set_str(Z_d,tok,10);
	gmp_printf("d:0x%ZX\n", Z_d);
	sign(sig,h_f,Z_d,Z_n);
	printf("****verification*****\n");
	verify(sig,filename,"key.pub");
	mpz_clears(Z_n,Z_d,sig,NULL);

}

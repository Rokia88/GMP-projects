
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gmp.h"

gmp_randstate_t generateur;

void decrypt_rsa_msg(mpz_t c, mpz_t n, mpz_t d)
{
	mpz_t m;
	mpz_init(m);
   	mpz_mod(c,c,n);
	mpz_powm(m,c,d,n);
	gmp_printf("c :0x%ZX \n",c);
	gmp_printf("m :0x%ZX \n",m);
	char *msg = mpz_get_str(NULL,36,m);
	printf("plain text: %s \n",msg);//on ne peut pas retrouver le meme msg
	//texte si il a subit une réduction mod n avant le chiffrement
}


void encrypt_rsa_msg(mpz_t c,char* msg, mpz_t n, mpz_t e)
{
	mpz_t m;
	mpz_init(m);
	int rslt = mpz_set_str(m,msg,36);
	gmp_printf("m before reduction :0x%ZX \n",m);
	mpz_mod(m,m,n);
	mpz_powm(c,m,e,n);
	gmp_printf("m :0x%ZX \n",m);
	gmp_printf("c :0x%ZX \n",c);
}

void encrypt_rsa(mpz_t c,mpz_t m, mpz_t n,mpz_t e)
{
	mpz_mod(m,m,n);
	mpz_powm(c,m,e,n);
	gmp_printf("m :0x%ZX \n",m);
	gmp_printf("c :0x%ZX \n",c);
}

void decrypt_rsa(mpz_t m,mpz_t c, mpz_t n,mpz_t d)
{
	mpz_mod(c,c,n);
	mpz_powm(m,c,d,n);
	gmp_printf("c :0x%ZX \n",c);
	gmp_printf("m :0x%ZX \n",m);
}


void generate_prime_number(mpz_t alea, unsigned int nbr_bit)
{
	int premier;
	mpz_t k;
	mpz_init(k);
	mpz_ui_pow_ui(k,2,nbr_bit-1);
	do
	{
		mpz_urandomb(alea, generateur, nbr_bit-1);
		mpz_add(alea,alea,k);
		premier = mpz_probab_prime_p(alea,10);
	}while(premier==0);
	mpz_clear(k);
}

void write_key_file(mpz_t modulo,mpz_t key,int public)
{
	FILE *f;
	if(public == 1)
	{
		f = fopen("/Users/quetzalli/Documents/Cryptis14-15/DLC/workspace/TP4exo1.3/key.pub","w");
		if(f==NULL)
		{
			fputs("Echec du chargement de la clef!\n",stderr);
			exit(-1);
		}
		char *pub_key_m = mpz_get_str(NULL,10,modulo);
		fwrite(pub_key_m,1,strlen(pub_key_m),f);
		fwrite("\n",1,strlen("\n"),f);
		char *pub_key_e = mpz_get_str(NULL,10,key);
		fwrite(pub_key_e,1,strlen(pub_key_e),f);
		fwrite("\n",1,strlen("\n"),f);
		fclose(f);
	}

	else if(public == 0)
	{
		f = fopen("/Users/quetzalli/Documents/Cryptis14-15/DLC/workspace/TP4exo1.3/key.priv","w");
		if(f==NULL)
		{
			fputs("Echec du chargement de la clef!\n",stderr);
			exit(-1);
		}
		char *priv_key_m = mpz_get_str(NULL,10,modulo);
		fwrite(priv_key_m,1,strlen(priv_key_m),f);
		fwrite("\n",1,strlen("\n"),f);
		char *priv_key_d = mpz_get_str(NULL,10,key);
		fwrite(priv_key_d,1,strlen(priv_key_d),f);
		fwrite("\n",1,strlen("\n"),f);
		fclose(f);
	}


}

int main(int argc, char* argv[])
{
	unsigned int e = 0;
	unsigned int nbr_bit = 0;
	nbr_bit = (unsigned int) (atoi(argv[1])/2);
	e = atoi(argv[2]);
	if(argc < 5)
	{
		printf("nombre insuffisant d'arguments\n");
		exit(-1);
	}
	int text = atoi(argv[4]);
	if(text !=1 && text!=0)
	{
		printf("le dernier argument est = à 1 si le msg à chiffrer est un msg texte, et = à 0 sinon\n");
		exit(-1);
	}

	mpz_t p;
	mpz_t Z_e;
	mpz_t q;
	mpz_t n;
	mpz_t pgcd;
	mpz_t d;
	mpz_t pMinus1;
	mpz_t qMinus1;
	mpz_t phi_N;
	mpz_inits(p,Z_e,q,n,pgcd,d,pMinus1,qMinus1,phi_N,NULL);
	mpz_set_ui(Z_e,e);
	unsigned int bit_size;
	gmp_randinit_default(generateur);
	gmp_randseed_ui(generateur, time(NULL));
	do
	{		generate_prime_number(p,nbr_bit);
			mpz_sub_ui(pMinus1,p,1);
			mpz_gcd_ui(pgcd, pMinus1,e);
	}while(mpz_cmp_ui(pgcd,1)!=0);

	gmp_printf("p :0x%ZX \n",p);

	do
	{		generate_prime_number(q,nbr_bit);
			mpz_sub_ui(qMinus1,q,1);
			mpz_gcd_ui(pgcd, qMinus1,e);
	}while(mpz_cmp_ui(pgcd,1)!=0 || mpz_cmp(p,q)==0);

	gmp_printf("q :0x%ZX \n",q);

	bit_size = mpz_sizeinbase(p,2);
	printf("p: %u bits, %u chiffres\n", bit_size, (unsigned int) ceil(bit_size / (log(10) / log(2))));
	bit_size = mpz_sizeinbase(q, 2);
	printf("q: %u bits, %u chiffres\n", bit_size, (unsigned int) ceil(bit_size / (log(10) / log(2))));

	mpz_mul(n,p,q);
	write_key_file(n,Z_e,1);

	bit_size = mpz_sizeinbase(n,2);
	printf("n: %u bits, %u chiffres\n", bit_size, (unsigned int) ceil(bit_size / (log(10) / log(2))));

	mpz_mul(phi_N,pMinus1,qMinus1);
	mpz_invert(d,Z_e,phi_N);

	write_key_file(n,d,0);

	gmp_printf("e :0x%ZX \n",Z_e);
	gmp_printf("n :0x%ZX \n",n);
	gmp_printf("d :0x%ZX \n",d);

	gmp_randclear(generateur);

	mpz_t cipher;
	mpz_t plain;
	mpz_inits(cipher,plain,NULL);
	unsigned int msg ;
	if(text == 0)
	{
		msg = atoi(argv[3]);
		mpz_set_ui(plain,msg);
		printf("msg:%d\n",msg);
		printf("****Chiffrement****\n");
		encrypt_rsa(cipher, plain, n, Z_e);
		mpz_init(plain);
		printf("****Déchiffrement****\n");
		decrypt_rsa(plain, cipher, n, d);
	}
	else if (text == 1)
	{
		printf("msg texte:%s\n",argv[3]);
		printf("****Chiffrement****\n");
		encrypt_rsa_msg(cipher,argv[3],n,Z_e);
		printf("****Déchiffrement****\n");
		decrypt_rsa_msg(cipher,n,d);
	}

	mpz_clears(p,Z_e,q,n,pgcd,d,pMinus1,qMinus1,phi_N,NULL);
	mpz_clears(cipher,plain,NULL);


	return 0;
}

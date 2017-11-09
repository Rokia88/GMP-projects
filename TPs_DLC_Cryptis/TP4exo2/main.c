#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gmp.h"

gmp_randstate_t generateur;


void decrypt_rsa_msg(mpz_t c, mpz_t p,mpz_t q,mpz_t d_p,mpz_t d_q,mpz_t I_p)
{
	mpz_t m_p;
	mpz_t m_q;
	mpz_t m;
	mpz_inits(m,m_p,m_q,NULL);
	gmp_printf("c :0x%ZX \n",c);
	mpz_powm(m_p,c,d_p,p);
	mpz_powm(m_q,c,d_q,q);
	gmp_printf("m_p :0x%ZX \n",m_p);
	gmp_printf("m_q :0x%ZX \n",m_q);
	mpz_sub(m_q,m_q,m_p);
	mpz_mul(m_q,m_q,I_p);
	mpz_mod(m_q,m_q,q);
	mpz_mul(m_q,m_q,p);
	mpz_add(m,m_p,m_q);
	gmp_printf("m :0x%ZX \n",m);
	char *msg = mpz_get_str(NULL,62,m);
	printf("plain text: %s \n",msg);//on ne peut pas retrouver le meme msg
	//texte si il a subit une réduction mod n avant le chiffrement
}


void encrypt_rsa_msg(mpz_t c,char* msg, mpz_t n, mpz_t e)
{
	mpz_t m;
	mpz_init(m);
	mpz_set_str(m,msg,62);
	gmp_printf("m before reduction :0x%ZX \n",m);
	mpz_mod(m,m,n);
	mpz_powm(c,m,e,n);
	gmp_printf("m after reduction:0x%ZX \n",m);
	gmp_printf("c :0x%ZX \n",c);
}

void encrypt_rsa(mpz_t c,mpz_t m, mpz_t n,mpz_t e)
{
	mpz_mod(m,m,n);
	mpz_powm(c,m,e,n);
	gmp_printf("m :0x%ZX \n",m);
	gmp_printf("c :0x%ZX \n",c);
}

void write_key_file(mpz_t n,mpz_t e,mpz_t p,mpz_t q,mpz_t d_p,mpz_t d_q,mpz_t I_p,int public)
{
	FILE *f;
	if(public == 1)
	{
		f = fopen("/Users/quetzalli/Documents/Cryptis14-15/DLC/workspace/TP4exo2.3/key.pub","w");
		if(f==NULL)
		{
			fputs("Echec du chargement de la clef!\n",stderr);
			exit(-1);
		}
		char *pub_key_m = mpz_get_str(NULL,10,n);
		fwrite(pub_key_m,1,strlen(pub_key_m),f);
		fwrite("\n",1,strlen("\n"),f);
		char *pub_key_e = mpz_get_str(NULL,10,e);
		fwrite(pub_key_e,1,strlen(pub_key_e),f);
		fwrite("\n",1,strlen("\n"),f);
		fclose(f);
	}

	else if(public == 0)
	{
		f = fopen("/Users/quetzalli/Documents/Cryptis14-15/DLC/workspace/TP4exo2.3/key.priv","w");
		if(f==NULL)
		{
			fputs("Echec du chargement de la clef!\n",stderr);
			exit(-1);
		}
		char *priv_key_p = mpz_get_str(NULL,10,p);
		fwrite(priv_key_p,1,strlen(priv_key_p),f);
		fwrite("\n",1,strlen("\n"),f);
		char *priv_key_q = mpz_get_str(NULL,10,q);
		fwrite(priv_key_q,1,strlen(priv_key_q),f);
		fwrite("\n",1,strlen("\n"),f);
		char *priv_key_dp = mpz_get_str(NULL,10,d_p);
		fwrite(priv_key_dp,1,strlen(priv_key_dp),f);
		fwrite("\n",1,strlen("\n"),f);
		char *priv_key_dq = mpz_get_str(NULL,10,d_q);
		fwrite(priv_key_dq,1,strlen(priv_key_dq),f);
		fwrite("\n",1,strlen("\n"),f);
		char *priv_key_ip = mpz_get_str(NULL,10,I_p);
		fwrite(priv_key_ip,1,strlen(priv_key_ip),f);
		fwrite("\n",1,strlen("\n"),f);
		fclose(f);
	}


}


void decrypt_rsa(mpz_t m,mpz_t c, mpz_t p,mpz_t q,mpz_t d_p,mpz_t d_q,mpz_t I_p)
{
	mpz_t m_p;
	mpz_t m_q;
	mpz_inits(m_p,m_q,NULL);
	gmp_printf("c :0x%ZX \n",c);
	mpz_powm(m_p,c,d_p,p);
	mpz_powm(m_q,c,d_q,q);
	gmp_printf("m_p :0x%ZX \n",m_p);
	gmp_printf("m_q :0x%ZX \n",m_q);
	mpz_sub(m_q,m_q,m_p);
	mpz_mul(m_q,m_q,I_p);
	mpz_mod(m_q,m_q,q);
	mpz_mul(m_q,m_q,p);
	mpz_add(m,m_p,m_q);
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
	mpz_t d_p;
	mpz_t d_q;
	mpz_t I_p;
	mpz_t pMinus1;
	mpz_t qMinus1;
	mpz_inits(p,Z_e,q,n,pgcd,d_p,d_q,pMinus1,qMinus1,I_p,NULL);
	mpz_set_ui(Z_e,e);
	unsigned int bit_size;
	gmp_randinit_default(generateur);
	gmp_randseed_ui(generateur, time(NULL));
	do{
		generate_prime_number(p,nbr_bit);
		mpz_sub_ui(pMinus1,p,1);
		mpz_gcd_ui(pgcd, pMinus1,e);
	}while(mpz_cmp_ui(pgcd,1)!=0);

	gmp_printf("p :0x%ZX \n",p);

	do{
		generate_prime_number(q,nbr_bit);
		mpz_sub_ui(qMinus1,q,1);
		mpz_gcd_ui(pgcd, qMinus1,e);
	}while(mpz_cmp_ui(pgcd,1)!=0 || mpz_cmp(p,q)==0);

	gmp_printf("q :0x%ZX \n",q);

	bit_size = mpz_sizeinbase(p,2);
	printf("p: %u bits, %u chiffres\n", bit_size, (unsigned int) ceil(bit_size / (log(10) / log(2))));
	bit_size = mpz_sizeinbase(q, 2);
	printf("q: %u bits, %u chiffres\n", bit_size, (unsigned int) ceil(bit_size / (log(10) / log(2))));

	mpz_mul(n,p,q);
	write_key_file(n,Z_e,NULL,NULL,NULL,NULL,NULL,1);

	bit_size = mpz_sizeinbase(n,2);
	printf("n: %u bits, %u chiffres\n", bit_size, (unsigned int) ceil(bit_size / (log(10) / log(2))));

	mpz_invert(d_p,Z_e,pMinus1);
	mpz_invert(d_q,Z_e,qMinus1);
	mpz_invert(I_p,p,q);

	write_key_file(NULL,NULL,p,q,d_p,d_q,I_p,0);

	gmp_printf("e :0x%ZX \n",Z_e);
	gmp_printf("n :0x%ZX \n",n);
	gmp_printf("d_p :0x%ZX \n",d_p);
	gmp_printf("d_q :0x%ZX \n",d_q);
	gmp_printf("I_p :0x%ZX \n",I_p);

	gmp_randclear(generateur);

	mpz_t cipher;
	mpz_t plain;
	mpz_inits(cipher,plain,NULL);
	if(text == 0)
		{

			mpz_set_str(plain,argv[3],10);
			printf("msg:%s\n",argv[3]);
			printf("****Chiffrement****\n");
			encrypt_rsa(cipher, plain, n, Z_e);
			mpz_init(plain);
			printf("****Déchiffrement****\n");
			decrypt_rsa(plain,cipher,p,q,d_p,d_q,I_p);
		}

		else if (text == 1)
		{
			printf("msg texte:%s\n",argv[3]);
			printf("****Chiffrement****\n");
			encrypt_rsa_msg(cipher,argv[3],n,Z_e);
			printf("****Déchiffrement****\n");
			decrypt_rsa_msg(cipher,p,q,d_p,d_q,I_p);
		}

		mpz_clears(p,Z_e,q,n,pgcd,d_p,d_q,pMinus1,qMinus1,I_p,cipher,plain,NULL);


}




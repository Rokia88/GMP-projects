#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

gmp_randstate_t generateur;

//au plus k_bits
void generate_prime_number_0(mpz_t alea, unsigned int nbr_bit)
{
	int premier;
	do
	{
		mpz_urandomb(alea, generateur, nbr_bit);
		premier = mpz_probab_prime_p(alea,10);
	}while(premier==0);
}
//k_bit exactement
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

//au plus k_chiffres
void generate_prime_number_1(mpz_t alea, unsigned int nbr_chiffres)
{
	int premier;
	unsigned int nbr_bit = nbr_chiffres * floor(log(10)/log(2));
	do
	{
		mpz_urandomb(alea, generateur, nbr_bit);
		premier = mpz_probab_prime_p(alea,10);
	}while(premier==0);
}

//k_chiffres exactement
void generate_prime_number_2(mpz_t alea, unsigned int nbr_chiffres)
{
	int premier;
	mpz_t k;
	mpz_init(k);
	unsigned int nbr_bit = nbr_chiffres * floor(log(10)/log(2));
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
unsigned int nbr = 0;
unsigned int mthd = 0;

nbr = atoi(argv[1]);
mthd = atoi(argv[2]);

mpz_t alea;
mpz_t reste;
mpz_init(alea);
int premier;
gmp_randinit_default(generateur);
time_t t = time(NULL);
unsigned int bit_size = 0;
gmp_randseed_ui(generateur,t);
if(mthd==0)
{
	printf("***%d-bit exactement**** \n",nbr);
	generate_prime_number(alea,nbr);
	gmp_printf("alea :%Zu \n",alea);
	bit_size = mpz_sizeinbase(alea, 2);
	printf("alea: %u bits, %u chiffres\n", bit_size, (unsigned int) ceil(bit_size / (log(10) / log(2))));
}
if(mthd==1)
{
	printf("***au plus %d- chiffres**** \n",nbr);
	generate_prime_number_1(alea,nbr);
	gmp_printf("alea :%Zu \n",alea);
	bit_size = mpz_sizeinbase(alea, 2);
	printf("alea: %u bits, %u chiffres\n", bit_size, (unsigned int) ceil(bit_size / (log(10) / log(2))));
}
if(mthd==2)
{
	printf("***exactement %d- chiffres**** \n",nbr);
	generate_prime_number_2(alea,nbr);
	gmp_printf("alea :%Zu \n",alea);
	bit_size = mpz_sizeinbase(alea, 2);
	printf("alea: %u bits, %u chiffres\n", bit_size, (unsigned int) ceil(bit_size / (log(10) / log(2))));
}

if(mthd==3)
{
	printf("***au plus %d- bits**** \n",nbr);
	generate_prime_number_0(alea,nbr);
	gmp_printf("alea :%Zu \n",alea);
	bit_size = mpz_sizeinbase(alea, 2);
	printf("alea: %u bits, %u chiffres\n", bit_size, (unsigned int) ceil(bit_size / (log(10) / log(2))));
}

gmp_randclear(generateur);
mpz_clear(alea);

return 0;
}

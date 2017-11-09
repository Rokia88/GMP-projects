#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>


/*int main(int argc, char* argv[])
{
unsigned int nbr_bit = 0;

nbr_bit = atoi(argv[1]);

mpz_t alea;
mpz_t reste;
mpz_init(alea);
int premier;
gmp_randstate_t generateur;
gmp_randinit_default(generateur);
time_t t = time(NULL);
gmp_randseed_ui(generateur,t );
printf("seed :%d \n",t);
do
{
mpz_urandomb(alea, generateur, nbr_bit);
gmp_printf("alea :%Zu \n",alea);
premier = mpz_probab_prime_p(alea,10);
}while(premier == 0);

gmp_randclear(generateur);
mpz_clear(alea);
mpz_clear(reste);

return 0;
}*/

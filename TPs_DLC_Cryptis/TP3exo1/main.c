#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include <time.h>


/*int main(int argc, char* argv[])
{
unsigned int nbr_bit = 0;

nbr_bit = atoi(argv[1]);

mpz_t alea;
mpz_t reste;
mpz_init(alea);
mpz_init(reste);
gmp_randstate_t generateur;
gmp_randinit_default(generateur);
gmp_randseed_ui(generateur, time(NULL));
do
{
mpz_urandomb(alea, generateur, nbr_bit);
gmp_printf("alea :%Zu \n",alea);
mpz_mod_ui(reste, alea,20);
}while(mpz_cmp_ui(reste,0));

gmp_randclear(generateur);
mpz_clear(alea);
mpz_clear(reste);

return 0;
}*/

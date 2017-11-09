#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// On définit le type BYTE

#define taille 4
typedef unsigned char BYTE;


BYTE secret_key[4] = {0x0B, 0x17, 0xD9, 0xFF};

// -----------------------------------------------------

int encrypt(BYTE* c, BYTE* m, BYTE* k)
{
  int i;

  for (i = 0; i < taille; i++)
  {
    c[i] = m[i] ^ k[i];
  }

  return 0;
}

// -----------------------------------------------------

int main()
{
  BYTE m0[4] = {0xCA, 0x08, 0xFE, 0x35};
  BYTE c0[4];
  BYTE k[4] = {0,0,0,0};

  int i;

  //{0xCA, 0x08, 0xFE, 0x35};

  // Génère un couple clair-chiffré de référence
  encrypt(c0, m0, secret_key);

  printf("\n");
  printf("Message de reference : ");
  for (i = 0; i < taille; i++)
  {
    printf(" %02X", m0[i]);
  }
  printf("\n");
  printf("Chiffre de reference : ");
  for (i = 0; i < taille; i++)
  {
    printf(" %02X", c0[i]);
  }
  printf("\n");
  printf("\n");

  // Recherche exhaustive
  BYTE c[taille];
  int bfound = 0;
  do
  {
	  k[1] = 0;
	  do
	  {
		  k[2] = 0;
		  do
		  {
			  k[3] = 0;
			  do
			  {
				  	 encrypt(c,m0,k);
				  	 if(memcmp(c,c0,4)==0)
				  	 {
				  		 	printf("clé trouvé");
				  		 	bfound =1;
				  	 }
				  	 //k[3]++; // si je laisse l'increm ici, la clé trouvée à la fin sera la clé réelle plus 1
			  }while(bfound==0 && ++k[3] >0);
			  //k[2]++;

		  }while(bfound==0 && ++k[2] >0);

		  //k[1]++;
	  }while(bfound==0 && ++k[1] >0);
	  //k[0]++;
  }while(bfound==0 && ++k[0] >0);

  printf("CLE : ");
    for (i = 0; i < taille; i++)
    {
      printf(" %02X", k[i]);
    }


  return 0;
}

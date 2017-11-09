#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// On définit le type BYTE

#define taille 5
typedef unsigned char BYTE;


BYTE secret_key[taille] = {0x0B, 0x2F, 0xD9,0x24,0xFF};

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
  BYTE m0[taille] = {0xCA, 0x08, 0xFE,0x35,0x10};
  BYTE c0[taille];
  BYTE k[taille];

  memset(k,0,taille);

  //{0xCA, 0x08, 0xFE, 0x35};

  // Génère un couple clair-chiffré de référence
  encrypt(c0, m0, secret_key);
  int i;
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
  int bstop = 0;
  int pos = 0;
  do
  {
	  encrypt(c,m0,k);
	  if(memcmp(c,c0,taille)==0)
	  {
		  bfound = 1;
		  printf("clef trouvée\n");
		  //break;
	  }
	  if(bfound == 0)
	  {
		 pos = 0;
		 while(pos < taille && k[pos] == (unsigned char) 0xFF)
		 {
			 k[pos] = 0;
			 pos++;
		 }
		 if(pos < taille)
		 {
		 	 k[pos]++;
		 }
		 if(pos >= taille)
		 {
			 bstop = 1;
		 }

	  }

  }while(bfound==0 && bstop == 0);

  printf("CLE : ");
    for (i = 0; i < taille; i++)
    {
      printf(" %02X", k[i]);
    }


  return 0;
}

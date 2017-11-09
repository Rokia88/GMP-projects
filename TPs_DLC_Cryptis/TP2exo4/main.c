#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// On définit le type BYTE

/*typedef unsigned char BYTE;

BYTE secret_key[4] = {0x0B, 0x2F, 0xD9, 0x24};

// -----------------------------------------------------

int encrypt(BYTE* c, BYTE* m, BYTE* k)
{
  int i;

  for (i = 0; i < 4; i++)
  {
    c[i] = m[i] ^ k[i];
  }

  return 0;
}*/

// -----------------------------------------------------

/*int main()
{
  BYTE m0[4] = {0xCA, 0x08, 0xFE, 0x35};
  BYTE c0[4];
  BYTE k[4] = {0,0,0,0};

  int i;

  // Génère un couple clair-chiffré de référence
  encrypt(c0, m0, secret_key);

  printf("\n");
  printf("Message de reference : ");
  for (i = 0; i < 4; i++)
  {
    printf(" %02X", m0[i]);
  }
  printf("\n");
  printf("Chiffre de reference : ");
  for (i = 0; i < 4; i++)
  {
    printf(" %02X", c0[i]);
  }
  printf("\n");
  printf("\n");

  // Recherche exhaustive
  BYTE c[4];
  int j;
  for(j=0; j < 4;j++)
  	 {
	  for(i=0; i < 256; i++)
	    {
		  k[j] = i;
		  encrypt(c, m0, k);
		  if(c[j] == c0[j])
		  {
			  break;
		  }
	    }
  	 }
  printf("CLE : ");
    for (i = 0; i < 4; i++)
    {
      printf(" %02X", k[i]);
    }


  return 0;
}*/

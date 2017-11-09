#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// On définit le type BYTE

typedef unsigned char BYTE;


BYTE secret_key[4] = {0x0B, 0x2F, 0xD9, 0xFF};

// -----------------------------------------------------

int encrypt(BYTE* c, BYTE* m, BYTE* k)
{
  int i;

  for (i = 0; i < 4; i++)
  {
    c[i] = m[i] ^ k[i];
  }

  return 0;
}

// -----------------------------------------------------

int main()
{
  BYTE c0[4];
  BYTE k[4] = {0,0,0,0};
  BYTE m0[4] = {0xCA, 0x08, 0xEF, 0x35};

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
  //int j;
  short l = 0x00FF;
  int found = 0;
  for(k[0]=0; k[0] <= l ; k[0]++) // s à la place de l on met 256,on va meme pas rentrer dans la boucle, car 256 = 0xFFFFFFFF < 0 or k[i] > 0
  {
	  for(k[1]=0;k[1] <= l ; k[1]++)
	  {
		  for(k[2]=0;k[2] <= l; k[2]++)
		  {
			  for(k[3]=0; k[3]<=l; k[3]++)
			  {
				  	 encrypt(c,m0,k);
				  	 if(memcmp(c,c0,4)==0)
				  	 {
				  		 	printf("clef trouvée\n");
				  		 	found = 1;
				  	 }
				  	 if(found == 1)
				  	 {
				  		 break;
				  	 }
				  	 //printf("%u\n",k[3]);
			  }
			  if(found == 1)
			  {
				  break;
			  }
		  }
		  if(found == 1)
		  {
			  break;
		  }
	  }
	  if(found == 1)
	  {
		  break;
	  }

  }

  printf("CLE : ");
    for (i = 0; i < 4; i++)
    {
      printf(" %02X", k[i]);
    }
  /*

    Pour chaque candidat clé k de 4 octets il faut tester si le chiffré de m0
    sous la clé k est égal à c0. On s'arrête alors en affichant k

    A vous de jouer ...

  */

  return 0;
}

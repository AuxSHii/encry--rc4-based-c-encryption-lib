#include <stdio.h>
#include "encry.h"

#define F fflush(stdout)

void printbin(int8 *input ,const int16 size) {
  int16 i; //iterator
  int8 *p; //ptr for input of encry text
  assert(size > 0);
  for (i = size , p = input; i ;i-- , p++)
    {
    	if ( i % 2 == 0 )
    	   printf("  "); //print a space
    	printf("%.02x", *p );
    }  
    printf("\n");

    return;

}



int main()
{
   encry *enc3;     //dt declaration
   char *key, *from;
   int16 skey , stext;
   int8 *encrypted , *decrypted;

   key = "ashi";
   skey = strlen(key);
   from = "the true nature of ours is infact not true; its merely symbolic";
   stext = strlen(from);

   printf("Initializing encryption ..."); F;
   enc3 = encryinit((int8 *)key , skey); //store struct returned in var
   printf("done\n");

   printf("'%s'\n  -> ",from);
   encrypted = encrygiven(enc3 ,(int8 *)from ,stext);
   printbin(encrypted , stext);
   encryuninit(enc3);

//decryption

   printf("Initializing decryption ..."); F;
   enc3 = encryinit((int8 *)key , skey); //store struct returned in var
   printf("done\n");


   decrypted = decrypt(enc3 , encrypted ,stext);
   printf("    -> '%s'\n", decrypted);
   encryuninit(enc3);

   return 0;
}

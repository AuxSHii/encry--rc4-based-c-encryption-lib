#include "encry.h"
#include <stdio.h>  
#include <stdlib.h>  
//initializaion fxn
export encry *encryinit(int8 *key, int16 size) {
	int16 x; //counter var to empty the arr
	int8 tmp1,tmp2; //to swap arr values
	encry *p; //pointer p for structure used from .h file that will be used by byte fxn
    int32 n;

//allowcate memory to structure and check for error
// p* = memory location of struct ; p = struct
    p = malloc(sizeof(struct s_encry));
        if (p == NULL)
        {
        	perror("malloc failed");
        	exit(EXIT_FAILURE);
        }
//empty the array with x (initializing from zero)
    for (x = 0; x < 256; x++)
    {
    	p->s[x] = 0;
    }
//initialize every var from zero
    p->i = p->j = p->k = 0;
    tmp1 = tmp2 = 0;
//rc4 algo to initialize to start with an arry [0->255]
    for (p->i = 0; p->i < 256; p->i++)
        p->s[p->i] = p->i;
// then shuffle	the array with the key by swaping at random posn decided by the key
     for (p->i = 0; p->i < 256; p->i++) {
        tmp1 = p->i % size;
        tmp2 = p->j + p->s[p->i] + key[tmp1];
        p->j = tmp2 % 256;
        tmp1 = p->s[p->i];
        tmp2 = p->s[p->j];
        p->s[p->i] = tmp2;
        p->s[p->j] = tmp1;
     }

     p->i=p->j = 0;

     encrywhitewash(n, p); //whitewash 

   return p; //poiter to the structure having scrambled array
}

int8 encrybyte(encry *p) {

   int16 tmp1,tmp2;
//pseudo random gen algo -> to genrate a keystream
//keystream -> random seq of binary data..
//1 byte keystream - per iteration |  using the scrambled array
    p->i = (p->i + 1) % 256;
    p->j = (p->j + p->s[p->i]) % 256;
    tmp1 = p->s[p->i];
    tmp2 = p->s[p->j];
    p->s[p->i] = tmp2;
    p->s[p->j] = tmp1;
    tmp1 = (p->s[p->i] + p->s[p->j]) % 256;
    p->k = p->s[tmp1];

    return p->k;  //returned the key stream 
    //which will use on XOR with binary(clear text) to create a binary(cypher text)

}

export int8 *encrygiven(encry *p,int8 *cleartext , int16 size ) {
    int8 *ciphertext;  //ptr named cyphertext 
    int16 x;


//allowcate memory to cyphertext pointer through malloc

    ciphertext = (int8 *)malloc(size + 1); //cyphertxt is an int8 ptr therefore typecast the memory    
         if (ciphertext == NULL) 
         {
         	perror("malloc failed");
         	exit(EXIT_FAILURE);

         }
    for (x = 0; x < size; x++)  
        ciphertext[x] = cleartext[x] ^ encrybyte(p);
    ciphertext[size] = '\0';            
    return ciphertext;
// null-terminated the string, creating a valid C string by writing the null character (\0) into the final array index, which ensures functions like printf recognize the exact boundary of allocated buffer memory
// returning a pointer[cyphertext] which points to a location in memory which contains an array which collectively is the cypher text
}



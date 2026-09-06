#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#define MS             2
#define export          __attribute__((visibility("default")))
#define encryuninit(x)         free(x)
#define decrypt(x,y,z)     encrygiven(x,y,z)
#define encrywhitewash(x,y)          for (x=0; x<(MS*10); x++) \
                                         (volatile int8)encrybyte(y);   


typedef unsigned char int8;   //typedef dt will use
typedef unsigned short int int16;
typedef unsigned int int32;


struct s_encry   //structure for encry eng.
{
	int16 i , j , k;
	int8 s[256];
};

typedef struct s_encry encry;  //typedef my structure

//define my functions
export encry *encryinit(int8* ,int16);
int8 encrybyte(encry*);
export int8 *encrygiven(encry* ,int8*, int16);

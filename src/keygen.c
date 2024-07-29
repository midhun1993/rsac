#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <gmp.h>

int get_passpharse_prod (char * passpharse) {

  int accu = 0;
  for(int i = 0; i< strlen(passpharse); i++) {
    printf("value of unicode: %d\n",passpharse[i]);
    accu = accu + passpharse[i];
  }
  return accu/strlen(passpharse);
}

bool is_prime( int n) {
   
   static int i = 2;
    if(n == 0 || n ==1) {
      i = 2;
      return false;
    }
    if(n == i) {
       i = 2;
      return true;
    }
    if(n % i ==0 ) {
       i = 2;
      return false;
    }
    i++;
    return is_prime(n);
}

 int get_prime( int start, int forword) {
   // printf("%d - %d\n", start, forword);
   while(!is_prime(start)) {
      // printf("%d \n", start);
      // printf("%d \n",forword );
      if(forword == 1) {
        start += 1;
      } else{
        start--;
        //printf("Here it come 2: %d\n", start);
       
      }
   }
   return start;
}

int modInverse(int A, int M)
{
    for (int X = 1; X < M; X++)
        if (((A % M) * (X % M)) % M == 1)
            return X;
}

void main(int argc, char ** argv){
  char * passpharse = (char *)malloc(sizeof(char));
  int arg_counter = 0;

  while(arg_counter < argc ) {
    if(strcmp(argv[arg_counter], "-p") == 0) {
      arg_counter++;
      strcpy(passpharse, argv[arg_counter]);
    }
    arg_counter++;
  }

  int start = get_passpharse_prod(passpharse);
  int neg_start  = start  - 1;
  //printf("start : %d \n", start);

  printf("p : %d\n", get_prime(start, 1));
  printf("q : %d\n", get_prime(neg_start, 0));
  int prime = get_prime(start, 1);
  int prime2 = get_prime(neg_start, 0);
  int product_of_prime  =  prime * prime2;
  printf("n : %d\n", product_of_prime);

   int max, lcm;

   max = (prime-1 > prime2-1) ? prime-1 : prime2-1;

    // While loop to check if max variable
    // is divisible by x and y
    while (1) {
        if (max % (prime-1) == 0 && max % (prime2-1) == 0) {
            //printf("%d \n", max);
            lcm = max;
            break;
        }

        ++max;
    }
  printf("lcm: %d \n", lcm);
    int coprime = 2;
    while (1) {
      if((lcm % coprime) != 0 && is_prime(coprime)) {
        break;
      }
      coprime++;
    }
  printf("e: %d \n", coprime);
  printf("d: %d \n", modInverse(coprime, lcm));
 
  
}
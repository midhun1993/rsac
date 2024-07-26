#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include<gmp.h>


#define DEBUG 0 // DEBUG flag

int decrypt_char_code(int char_code) {
/**
     * This code is good mod only exist for int so we need to convert float to int
     */
    // hard coded will replace later
    int hardcoded_power = 413; 
    int modulo = 3233;
    int ev;

    // default precision of gmp to avoid unwanted rounding
    mpf_set_default_prec(100000);    
    
    // pow
    mpf_t pc, char_code_mpf;
    mpf_inits(pc, char_code_mpf, NULL);
    mpf_set_ui(char_code_mpf, char_code);
    mpf_pow_ui(pc, char_code_mpf, hardcoded_power);

    // mod
    mpz_t r, n, d;
    mpz_inits(r, n, d, NULL);
    mpz_set_f(n ,pc);
    mpz_init_set_ui(d ,modulo);
    mpz_mod(r, n, d);

    if(DEBUG) {
        gmp_printf("%Zd\n", r);
    }
    // assign  value to ev
    ev = mpz_get_ui(r);

    //clear
    mpz_clears(r, n, d, NULL);
    mpf_clears(pc, char_code_mpf, NULL);

    return ev;
}

int main(int argc, char** argv) {
    // check the argument count is 3
    if(argc != 3) {
        printf("Error: arguments missing\n");
        return 1;
    }    

    // extarct the ciphar from argv
    // now we are only expecting ciphar so access value using index is fine.
    // int arg_counter =0;
    // while(arg_counter < argc) {
    //     printf("%s\n", argv[arg_counter]);
    //     arg_counter++;
    // }
    
    char ciphar[] ="bb8c6b7c8c33c6b6ed87a8708bb";
    
    int expected_parts_chunks = strlen(ciphar)/3;
    int * parts = (int *) malloc(sizeof(int) * expected_parts_chunks);
    int parts_length = 0;


    char hex_str[4]= {0};
    int len_string_encrypted = strlen(ciphar);
    int limit = len_string_encrypted + 1;

    int hex_length = 0;
    for(int i = 0; i < limit; i++ ) {
         if(hex_length == 3) {
            hex_str[hex_length] = '\0';
            parts[parts_length] =(int)strtol(hex_str, NULL, 16);
            parts_length++;
            hex_length = 0;
        }
        hex_str[hex_length] = ciphar[i];
        hex_length++;
    }

    for(int i = 0; i < expected_parts_chunks; i++) {
         printf("%c", decrypt_char_code(parts[i]));
    }
    
    printf("\n");
    free(parts);
    return 0;
}
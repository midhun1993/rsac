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

void main() {
    char string_encrypted[] = "bb85212e92e9889";
    int expected_parts_chunks = strlen(string_encrypted)/3;
    int * parts = (int *) malloc(sizeof(int) * expected_parts_chunks);
    int parts_length = 0;


    char hex_str[4]= {0};
    int len_string_encrypted = strlen(string_encrypted);
    int limit = len_string_encrypted + 1;

    int hex_length = 0;
    for(int i = 0; i < limit; i++ ) {
         if(hex_length == 3) {
            hex_str[hex_length] = '\0';
            parts[parts_length] =(int)strtol(hex_str, NULL, 16);
            parts_length++;
            hex_length = 0;
        }
        hex_str[hex_length] = string_encrypted[i];
        hex_length++;
    }

    for(int i = 0; i < expected_parts_chunks; i++) {
         printf("%c", decrypt_char_code(parts[i]));
    }
    
    printf("\n");
    free(parts);
}
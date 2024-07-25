#include<stdio.h>
#include<string.h>
#include<gmp.h>


#define DEBUG 1 // DEBUG flag

int encrypted_char_code(int char_code) {

    /**
     * This code is good mod only exist for int so we need to convert float to int
     */
    // hard codeded will replace later
    // int hardcoded_power = 17; 
    // int moduleo = 3233;

    // // default precision of gmp to avoid unwanted rounding
    // mpf_set_default_prec(100000);    
    // mpf_t pc, char_code_mpf, rem, mod;
    // mpf_inits(pc, char_code_mpf, mod, rem, NULL);

    // mpf_set_ui(char_code_mpf, char_code);
    // mpf_set_ui(rem, moduleo);

    // mpf_pow_ui(pc, char_code_mpf, hardcoded_power);
    // mpz_mod(mod, pc, rem);
    // gmp_printf("%.Ff\n", mod);
    // mpf_clears(pc, char_code_mpf, mod, rem, NULL);
    return char_code;
}

int main() {
    char text[] = "Hello";
    for(int i =0; i < strlen(text); i++) {
        printf("%d \n", encrypted_char_code(text[i]));
    }
    if(DEBUG) {
        printf("Hi\n");
    }
   return 1;
}

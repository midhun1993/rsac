#include<stdio.h>
#include<string.h>
#include<gmp.h>
#include<stdlib.h>


#define DEBUG 0 // DEBUG flag

int encrypted_char_code(int char_code, int *parts) {

    




    /**
     * This code is good mod only exist for int so we need to convert float to int
     */
    // hard coded will replace later
    int hardcoded_power = parts[0]; 
    int modulo = parts[1];
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


    // retrive the keys from here not the right way to do it.
    // we willl do like now.

    FILE *pk;
    pk = fopen("rsac.pubk", "r");

    if(pk == NULL) {
        fprintf(stderr, "File not found\n");
        return -1;
    }

    fseek(pk, 0, SEEK_END);
    long fileSize = ftell(pk);
    fseek(pk, 0, SEEK_SET);

    char *file_content = malloc(fileSize + 1);
    if (file_content == NULL) {
        fprintf(stderr, "Error allocating memory");
        fclose(pk);
    }
   
    size_t bytesRead = fread(file_content, 1, fileSize, pk);

    file_content[fileSize] = '\0';
    fclose(pk);

    // we have the file content here, we need to purse it
    char token[50]; // for nown  i set the token size to 50
    int part[2];
    int part_inc = 0;
    int token_inc = 0; 
    for(int j = 0; j < strlen(file_content);j++ ) {
        if(file_content[j] == '#' ) {
                token_inc++;
                token[token_inc] = '\0';
                part[part_inc] = (int)atoi(token);
                part_inc++;
                token_inc = 0;
                continue;
        }
        token[token_inc] = file_content[j];
        token_inc++;
    }

     free(file_content);
    printf("keys used d: %d, m:%d\n", part[0],  part[1]);
   
    char * text = (char *) malloc(sizeof(char) *2);
    if(text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 2;
    }
    int arg_counter =0;
    while(arg_counter < argc) {
        if(strcmp(argv[arg_counter], "-m") == 0) {
            arg_counter++;
            int str_len = strlen(argv[arg_counter]);
            text = (char *) realloc(text, sizeof(char) * (str_len-1) );
            strcpy(text, argv[arg_counter]);
        }
        arg_counter++; 
    }

    if(DEBUG) {
        printf("string: %s \n", text);
    }

    for(int i =0; i < strlen(text); i++) {
        printf("%x", encrypted_char_code(text[i], part));
    }
    printf("\n");
    return 1;
}

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

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
         printf("%d\n", parts[i]);
        long double power_val =  pow(parts[i], 413);
        printf("%Lf\n", power_val);
        long int mod = (long int) fmod(power_val,(double) 3233);
        printf("%d\n", (int)mod);
    }

    free(parts);
}
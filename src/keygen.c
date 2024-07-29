#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

  // Find ciphar from command
  int arg_counter = 0;
  char *ciphar = NULL;

  while (arg_counter < argc)
  {
    if (strcmp(argv[arg_counter], "-c") == 0)
    {
      arg_counter++;
      if (arg_counter < argc)
      {
        size_t ciphar_length = strlen(argv[arg_counter]);
        char *new_ciphar = (char *)realloc(ciphar, sizeof(char) * (ciphar_length + 1));
        if (new_ciphar == NULL)
        {
           fprintf(stderr, "Heap allocation failed! \n");
        }
        
        strcpy(new_ciphar, argv[arg_counter]);
        ciphar = new_ciphar;
      }
      else
      {
        fprintf(stderr, "Param value missing!\n");
      }
    }
    arg_counter++;
  }

  if (ciphar != NULL)
  {
    printf("%s", ciphar);
    free(ciphar);
  }
}
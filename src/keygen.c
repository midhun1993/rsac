#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int num_from_ciphar(char *ciphar)
{
  int accu = 0;
  size_t ciphar_length = strlen(ciphar);
  for (int i = 0; i < ciphar_length; i++)
  {
    accu += ciphar[i];
  }
  return accu / ciphar_length;
}

bool is_prime(int num)
{
  int static i = 2;

  if (num < 1)
  {
    i = 2;
    return false;
  }

  if (num == i)
  {
    i = 2;
    return true;
  }

  if ((num % i) == 0)
  {
    i = 2;
    return false;
  }
  i++;
  return is_prime(num);
}

int find_prime_from_num(int start, bool forward_direction)
{
  int start_pos = start;
  while (!is_prime(start_pos))
  {
    if (forward_direction == true)
    {
      start_pos += 1;
    }
    else
    {
      start_pos = start_pos - 1;
    }
  }

  return start_pos;
}

int gcd(int a, int b)
{
  while (b != 0)
  {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

// Function to compute the LCM of two numbers
int lcm(int a, int b)
{
  return (a * b) / gcd(a, b);
}

int find_coprime(int limit)
{
  int i = 3;
  while (i < limit)
  {
    if ((limit % i) != 0 && is_prime(i))
    {
      break;
    }
    i++;
  }
  return i;
}

// Function to perform the Extended Euclidean Algorithm
// It returns the gcd of a and b and updates x and y such that
// a * x + b * y = gcd(a, b)
int extended_gcd(int a, int b, int *x, int *y)
{
  if (b == 0)
  {
    *x = 1;
    *y = 0;
    return a;
  }

  int x1, y1;
  int gcd = extended_gcd(b, a % b, &x1, &y1);

  *x = y1;
  *y = x1 - (a / b) * y1;

  return gcd;
}

// Function to find the modular multiplicative inverse of a modulo m
int modular_inverse(int a, int m)
{
  int x, y;
  int gcd = extended_gcd(a, m, &x, &y);

  // If gcd is not 1, then the modular inverse does not exist
  if (gcd != 1)
  {
    printf("Inverse does not exist.\n");
    return -1;
  }

  // x may be negative, convert it to positive
  int result = (x % m + m) % m;
  return result;
}

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
    // create a number from ciphar;
    int random_number = num_from_ciphar(ciphar);
    int p = find_prime_from_num(random_number, true);
    int q = find_prime_from_num(random_number - 1, false);
    int n = p * q;
    int limit = lcm(p - 1, q - 1);
    int e = find_coprime(limit);
    int d = modular_inverse(e, limit);

    printf("ciphar: %s\n", ciphar);
    printf("generated number: %d \n", random_number);
    printf("p: %d \n", p);
    printf("q: %d \n", q);
    printf("n: %d \n", n);
    printf("limit: %d \n", limit);
    printf("e: %d \n", e);
    printf("d: %d \n", d);

    free(ciphar);
  }
}
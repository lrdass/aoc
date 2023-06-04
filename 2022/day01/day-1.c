#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

char* input = "1000\
2000\
3000\
\n\
4000\
\n\
5000\
6000\
\n\
7000\
8000\
9000\
\n\
10000";

#define MAX_NUMBERS 1024

typedef struct {
  int *values;
  size_t size;
} Elf;

int get_input(char *filename, int *result, int *total_elfs)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening the file.\n");
    return 1;
  }

  int numbers[MAX_NUMBERS];
  char buffer[100];

  int total_sum = 0;
  int ind = 0;

  while (fgets(buffer, sizeof(buffer), file) != NULL) {

    if(buffer[0] == '\n'){
      result[ind++] = total_sum;

      total_sum = 0;
    }

    *total_elfs = ind;
    total_sum += atoi(buffer);

  } 


  fclose(file);
  return 0;

}

void swap (int *a, int *b)
{
  int swap = *b;
  *b = *a;
  *a = swap;
}

void sort(int *buffer, size_t size)
{
  if (size < 1) return;

  for (int i = 0; i < size -1; ++i) {
    if(buffer[i] > buffer[i+1]){
      swap(&buffer[i], &buffer[i+1]);
    }
  }
  sort(buffer, size-1);

}

int main(void)
{

  int total_elfs;
  int sum_numbers[MAX_NUMBERS];
  get_input("input.txt", sum_numbers, &total_elfs);

  int largest;
  int index_largest = 0;

  sort(sum_numbers, total_elfs);
  int result = 0;
  for (int i = total_elfs - 1; i >= total_elfs -3 ; --i){
    printf("%d, \n", sum_numbers[i]);
    result += sum_numbers[i];
  }
  printf("final result %d \n", result);

  return 0;

}





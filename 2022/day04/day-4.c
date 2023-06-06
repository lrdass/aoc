#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>


#define MAX_NUMBERS 1024

char* get_input(char *filename, size_t *size)
{
  FILE *f = fopen(filename, "r");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

  char *inputed_txt = malloc(fsize + 1);
  fread(inputed_txt, fsize, 1, f);
  fclose(f);
  return inputed_txt;
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



void get_input_line(char *dst_buffer, char *input, int line)
{
  int curr_line = 0, cur = 0 ;
  size_t input_size = strlen(input);

  for(int i = 0; i < input_size; ++i){
    if(input[i] == '\n' && curr_line <= line){
      curr_line++;
      cur = i + 1;
    } else if(curr_line == line) {
      break;
    }
  }

  int i = 0;
  while(i + cur < input_size){
    dst_buffer[i] = input[cur + i];
    if(input[i + cur] == '\n'){
      dst_buffer[i] = '\0';
      return;
    }
    ++i;
  }

}



void count_lines(int *dst, char *input)
{
  *dst = 0;
  size_t size = strlen(input);
  for(int i = 0; i < size; ++i){
    if(input[i] == '\n'){
      *dst+=1;
    }
  }

}

int char_at(char *input, char entry)
{
  for(int i = 0; i < strlen(input); ++i){
    if(input[i] == entry) return i;
  }
  return -1;
}

typedef struct {
  int min;
  int max;
}Interval;

#define BUFFER_SIZE 100 
char *input ="\
10-16,9-15\n\
\n";


void interval_from_string_pair(char *input, Interval *i1, Interval *i2)
{
  int i = 0, digit = 0, digit_ind = 0;
  char digits[20] = {0};

  int numbers[4];

  while(input[i] != '\0'){
    int cur = input[i];
    if(cur == '-' || cur == ','){
      digit_ind= 0;
      numbers[digit] = atoi(digits);
      digit++;
      memset(digits, 0, 20);
    } else {
      digits[digit_ind] = cur;
      ++digit_ind;

      if(input[i + 1] == '\0'){
        numbers[digit] = atoi(digits);
      }
    }
    ++i;
  }

  i1->min = numbers[0];
  i1->max= numbers[1];
  i2->min = numbers[2];
  i2->max = numbers[3];

}

bool is_interval_fully_contained(const Interval *x, const Interval *y)
{
  return (x->min >= y->min && x->max <= y->max ||
          y->min >= x->min && y->max <= x->max ||
          x->min <= y->min && y->min <= x->max ||
          y->min <= x->min && x->min <= y->max);
}

int main (void)
{


  int total = 0;
  size_t size;
  char *input = get_input("input.txt", &size );

  int num_lines = 0;
  count_lines(&num_lines, input);


  for(int l = 0; l < num_lines; ++l){
    char *line;
    get_input_line(line, input, l);

    Interval i1;
    Interval i2;
    interval_from_string_pair(line, &i1, &i2);
    if(is_interval_fully_contained(&i1, &i2)){
        printf("[%d, %d] [%d, %d] \n", i1.min, i1.max, i2.min, i2.max );
        total += 1;
    }
  }


  printf("total: %d \n", total);


  return 0;
}



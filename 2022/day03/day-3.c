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

#define BUFFER_SIZE 100 
char *input ="\
vJrwpWtwJgWrhcsFMMfFFhFp\n\
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\n\
PmmdzqPrVvPwwTWBwg\n\
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn\n\
ttgJtRGJQctTZtZT\n\
CrZsJsPPZsGzwwsLwLmpwMDw\n";

// a - z -> 1 - 26 
// A - Z -> 27 - 52 

// find the only letter that repeats for each line in both of its halfs
// sum their priorities

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


short map_char_to_int(char l)
{
  if('a' <= l  && l <= 'z')
    return (l % 'a') + 1;
  if('A' <= l && l <= 'Z')
    return (l % 'A') + 27;
  return '\0';
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


int main (void)
{
  size_t size;
  char *input = get_input("input.txt", &size );

  int num_lines = 0;
  count_lines(&num_lines, input);

  int total = 0;

  for(int x =0; x < num_lines; ++x) {
    int cur_line = x;
    char cur_buffer[BUFFER_SIZE] = {0};
    get_input_line(cur_buffer, input, cur_line);

  
    size_t sz_buffer = strlen(cur_buffer) /2 ;
    char h1[sz_buffer];
    char h2[sz_buffer];

    strncpy(h1, cur_buffer, sz_buffer);
    strncpy(h2, cur_buffer + sz_buffer, sz_buffer);

    char result = 0 ;
    for(int i = 0; i < sz_buffer; ++i){
      for(int j = 0; j < sz_buffer; ++j){
        if(h1[i] == h2[j]){
          result = h1[i];
        }
      }
    }

    short value = map_char_to_int(result);
    total += value;
    printf("result: %d \n", value);
  }

  printf("total: %d \n", total);
  
  return 0;
}



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

// part 2
// now instead of each line
// read 3 lines and see which letter is common between the three
// still evaluate the priority value

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

int char_at(char *input, char entry)
{
  for(int i = 0; i < strlen(input); ++i){
    if(input[i] == entry) return i;
  }
  return -1;
}

int main (void)
{

  char *line;
  get_input_line(line, "1234\n", 0);

  printf("%s",line);

  return 0;

  size_t size;
  char *input = get_input("input.txt", &size );

  int num_lines = 0;
  count_lines(&num_lines, input);

  int total = 0;
  char result = 0;

  for (int l = 0; l < num_lines / 3; ++l) {
    char cur_buffer[3][BUFFER_SIZE] = {0};

    get_input_line(cur_buffer[0], input,  3*l+0);
    get_input_line(cur_buffer[1], input,  3*l+1);
    get_input_line(cur_buffer[2], input,  3*l+2);

    printf("------------------------------\n");
    printf("buf %d, %s \n", 3*l+0 , cur_buffer[0]);
    printf("buf %d, %s \n", 3*l+1 , cur_buffer[1]);
    printf("buf %d, %s \n", 3*l+2 , cur_buffer[2]);
    printf("------------------------------\n");

    #define NOT_FOUND '\n'
    char curr_search ;
    char first_search, second_search = NOT_FOUND;
    for (int i = 0; i < strlen(cur_buffer[0]); ++i){
      // ignore linebreaks for all searches
      if(cur_buffer[0][i] == '\n') break;
      if(cur_buffer[0][i] == '\0') printf("wtf?? \n");

      curr_search = cur_buffer[0][i];
      first_search= NOT_FOUND;
        second_search = NOT_FOUND;

      for(int j = 0; j < strlen(cur_buffer[1]); ++j){
        if(cur_buffer[1][j] == curr_search ){
          first_search = cur_buffer[1][j];
          break;
        }
      }

      if(first_search == NOT_FOUND) continue;

      for(int j = 0; j < strlen(cur_buffer[2]); ++j){
        if(cur_buffer[2][j] == curr_search ){
          second_search = cur_buffer[2][j];
          break;
        }
      }

      if(second_search == NOT_FOUND) continue;

      if(first_search == second_search){
        result= first_search;
        printf("---------- \n");
        printf("line search: %d\n",l );
        printf("search value: %c\n", curr_search);
        printf("value at original : %d \n", char_at(cur_buffer[0], curr_search));
        printf("found in buffer 1 at: %d\n", char_at(cur_buffer[1], first_search));

        printf("found in buffer 2 at: %d\n", char_at(cur_buffer[2], second_search));
        printf("---------- \n");
        break;
      }
    }

    short value = map_char_to_int(result);
    printf("result of %c, point: %d\n", result, value);
    result=0;

    total += (int)value;
  }

  printf("total: %d \n", total);
  
  return 0;
}



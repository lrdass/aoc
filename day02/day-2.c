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

// 0 2 => 0 1 -> % 2 = 0 1 
// 4 6 => 0 1  /2 -> 2 3 %2 0 1
// 8 10 => 0 1 /2 -> 4, 5 -> 0 1
char *input = "\
A Y\n\
B X\n\
C Z\n\
";
  
// win 6, draw 3, lose 0
// player:  X lose, Y draw, Z win
// oppponen:  A rock, B paper, C scisors


typedef struct {
  char key;
  short points[3];
} PointMap;



int get_round_value(char opponent, char player, PointMap *map)
{
  short player_index = (short) player % 'X';

  for(int i = 0; i < 3; ++i){
    char current_key = map[i].key;
    short *value = map[i].points;


    if(current_key == opponent){
      return value[player_index];
    }
  }
  return 0;

}

unsigned short get_piece_value(char player)
{
  return (unsigned short) player % 'X' + 1;
}

int main (void)
{

  //size_t size;
  // char *input = get_input("input.txt", &size );

// player:  X lose, Y draw, Z win
  PointMap point_map[3] = {
    {
      .key = 'A', // pedra
      .points = {0, 3, 6}
    },
    {
      .key = 'B', //papel 
      .points = {0, 3, 6}
    }, 
    {
      .key = 'C', //tesoura 
      .points = {0, 3, 6}
    },
  };


  int i = 0;
  char buffer[2];
  int total = 0;
  while (input[i] != '\0'){

    if(!isspace(input[i])){
      buffer[(i / 2) % 2] = input[i];
    }

    if(input[i] == '\n'){

      int value_round = get_round_value(buffer[0], buffer[1], point_map);
      printf("value round %d \n", value_round);

      value_round += get_piece_value(buffer[1]);
      printf("piece value %d,  piece : %c \n", get_piece_value(buffer[1]), buffer[1]);
      total += value_round;
    }
    ++i;

  }

  printf("total round: %d \n", total);

  //free(input);
  return 0;

}





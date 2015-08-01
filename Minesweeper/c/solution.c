#include <stdio.h>
#include <stdlib.h>

char** get_minefield(int width, int height);
void solve_minefield(char** minefield, int width, int height);
void print_minefield(char** minefield, int width, int height);

int main(int argc, char **argv) {
  
    char** minefield = get_minefield(4,4);
  /*char temp;
  while((temp = getchar()) != EOF) {
    printf("%c",temp);
    }*/
    print_minefield(minefield, 4,4);
  
  return 0;
}

/* Read a minefield from standard in, malloc it as a multidimensional char array
   and return it. */
char** get_minefield(int width, int height) {
  char** c;
  c = malloc(height*sizeof(char*));
  
  int i,j;
  for(i = 0 ; i < width ; i++) {
    *(c + i) = malloc(width*sizeof(char));
  }

  for(i = 0 ; i < height ; i++) {
    for(j = 0 ; j < width ; j++) {
      char temp = getchar();
      if(temp == '\n') continue;
      printf("%d", j);
      c[i][j] = temp;
    }
    printf("\n");
  }
  printf("\n");
  return c;
}

/* Solve the minefield */
void solve_minefield(char** minefield, int width, int height) {

}

/* Print the minefield to standard out */
void print_minefield(char** minefield, int width, int height) {
  int i,j;
  for(i = 0; i < height ; i++) {
    for(j = 0; j < width ; j++) {
      printf("%c", minefield[i][j]);
    }
    printf("\n");
  }
}

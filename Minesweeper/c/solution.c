#include <stdio.h>
#include <stdlib.h>

char** get_minefield(int width, int height);
void solve_minefield(char** minefield, int width, int height);
void print_minefield(char** minefield, int width, int height, int count);
void increment_fields(char** minefield, int row_index, int col_index, int width, int height);
void free_minefield(char** minefield, int width, int height);

int main(int argc, char **argv) {

  int width, height;
  char** minefield;

  int i;
  for(i = 1;;i++) {
    scanf("%d %d",&height, &width);

    if(width == 0 && height == 0) break;
    else if(i != 1) printf("\n");

    minefield = get_minefield(width, height);
    solve_minefield(minefield, width, height);
    print_minefield(minefield, width, height, i);
    free_minefield(minefield, width, height);
  }
  
  return 0;
}

/* Read a minefield from standard in, malloc it as a multidimensional char array
   and return it. */
char** get_minefield(int width, int height) {
  char** c;
  c = malloc(height*sizeof(char*));
  
  int i,j;
  for(i = 0 ; i < height; i++) {
    *(c + i) = malloc(width*sizeof(char));
  }

  for(i = 0 ; i < height ; i++) {
    for(j = 0 ; j < width ; j++) {
      char temp;
      if((temp = getchar()) == '\n') temp = getchar();
      if(temp == '*') {
	c[i][j] = temp;
      } else {
	c[i][j] = '0';
      }
    }
  }
  return c;
}

/* Free memory that was malloced to create board */
void free_minefield(char** minefield, int width, int height) {
  int i;
  for(i = 0; i < height ; i++) {
    free(minefield[i]);
  }
  free(minefield);
}


/* Solve the minefield */
void solve_minefield(char** minefield, int width, int height) {
  int i,j;
  for(i = 0 ; i < height ; i++) {
    for(j = 0 ; j < width ; j++) {
      if(minefield[i][j] == '*') increment_fields(minefield, i, j, width, height);
    }
  }
}

/* Increment all fields around the mine, taking care to not go over the board or overwrite mines*/
void increment_fields(char** minefield, int row_index, int col_index, int width, int height) {
  int i,j;
  for(i = -1 ; i < 2 ; i++) {
    for(j = -1 ; j < 2 ; j++) {

      int temp_i = row_index + i;
      int temp_j = col_index + j;

      if(temp_i < 0
	 || temp_j < 0
	 || temp_i >= height
	 || temp_j >= width
	 || minefield[temp_i][temp_j] == '*') {
	continue;
      }	       
      minefield[temp_i][temp_j]++;
    }
  }
}

/* Print the minefield to standard output */
void print_minefield(char** minefield, int width, int height, int count) {
  printf("Field #%d:\n", count);
  int i,j;
  for(i = 0; i < height ; i++) {
    for(j = 0; j < width ; j++) {
      if(minefield[i][j] == '*') {
	printf("%c", minefield[i][j]);
      } else {
	printf("%d", minefield[i][j] - '0');
      }
    }
    printf("\n");
  }
}

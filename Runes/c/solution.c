#include <stdio.h>
#include <stdlib.h>

int (*get_operator(char)) (int, int);
int plus(int first, int second);
int minus(int first, int second);
int multiply(int first, int second);
struct Rune* get_rune();
void init_rune(struct Rune**);
int is_operator(char c);
void string_copy(char *to, char *from, int start, int end);

struct Rune {
  char *first_num;
  char *second_num;
  char *answer;
  int (*operator)(int,int);
};

int main(int argc, char **argv) {

  int num_test_cases;
  scanf("%d", &num_test_cases);
  getchar();//get rid of dangling newline

  int i;
  for(i = 0; i < num_test_cases; i++) {
    struct Rune *cur_rune = get_rune();
    printf("%s\n", cur_rune->first_num);
  }

  return 0;
}

struct Rune* get_rune() {
  struct Rune *rune;
  
  /* Read in the maximum possible length of a line */
  /* The longest possible is -999999*999999=-999998000001 */
  int max_line_length = 29;
  char buffer[max_line_length];

  fgets(buffer, sizeof(buffer), stdin);
  
  int i;
  for(i = 0 ; i < max_line_length ; i++) {
    if(buffer[i] == '\n') {
      buffer[i] = '\0';
      break;
    }
  }
  
  int line_length = i + 1;
  
  init_rune(&rune);

  /*Now, find the first number */
  if(buffer[0] == '-') {
    i = 1; 
  } else {
    i = 0;
  }

  for(; is_operator(buffer[i]) ; i++);

  rune->first_num = (char*) malloc(i + 1);
  string_copy(buffer, rune->first_num, 0, i);
  *(rune->first_num + i) = '\0';
  
  /* Get our function */
  rune->operator = get_operator(buffer[i]);

  /* Get our second number */
  int j = i + 1;
  for(; buffer[j] != '=' ; j++);

  rune->second_num = (char*) malloc(j - i);
  string_copy(buffer, rune->second_num, i + 1, j);
  *(rune->second_num + (j - i - 1)) = '\0';

  
  /* Now, get the answer */
  rune->answer = (char*) malloc(line_length - j);
  string_copy(buffer, rune->answer, j + 1, line_length);
  *(rune->answer + (line_length - j - 1)) = '\0';
  
  return rune;
}


/* 
   Copies a string from the 'from' parameter to the 'to' parameter. 
   Begins copying at the start parameter and stops at the 'end' parameter, exclusive.
 */
void string_copy(char* from, char* to, int start, int end) {
  int i;
  for(i = start ; i < end ; i++) {
    *(to + i) = *(from + i);
  }
}

int is_operator(char c) {
  return c == '+'
      || c == '-' 
      || c == '*';
}

void init_rune(struct Rune** rune) {
  *rune = (struct Rune*) malloc(sizeof(struct Rune));
}

/*
  Given a arithmetic character ('+','-', '*'), returns a function pointer that will
  perform that operation on two ints.
 */
int (*get_operator(char operator)) (int,int) {
  int (*func)(int,int);
  switch(operator) {
  case '+':
    func = plus;
    break;
  case '-':
    func = minus;
    break;
  case '*':
    func = multiply;
    break;
  default:
    return NULL;
  }
  return func;
}

/* Adds the first and second argument together and returns it. */
int plus(int first, int second) {
  return first + second;
}

/* Multiplies the first and second argument together and returns it. */
int multiply(int first, int second) {
  return first * second;
}

/* Subtracts the second argument from the first argument and returns it. */
int minus(int first, int second) {
  return first - second;
}

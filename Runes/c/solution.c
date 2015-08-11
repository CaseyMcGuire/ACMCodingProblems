#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int (*get_operator(char)) (int, int);
int plus(int first, int second);
int minus(int first, int second);
int multiply(int first, int second);
struct Rune* get_rune();
void init_rune(struct Rune**);
int is_operator(char c);
void string_copy(char *to, char *from, int start, int end);
long str_to_long(char *str);
int solve_rune(struct Rune *rune);
void get_possible_digits(char *arr, struct Rune *rune);
void filter_val(char *arr, char *num);
int is_solution(char cur_char, struct Rune *rune);

struct Rune {
  char *first_num;
  char *second_num;
  char *answer;
  int (*operator)(int,int);
};

const char nums[] = {'0', '1', '2', '3','4','5','6','7','8','9' };

int main(int argc, char **argv) {

  int num_test_cases;
  scanf("%d", &num_test_cases);
  getchar();//get rid of dangling newline

  int i;
  for(i = 0; i < num_test_cases; i++) {
    struct Rune *cur_rune = get_rune();
    printf("%d\n", solve_rune(cur_rune));
    //    printf("first num : %s\n", cur_rune->first_num);
    //    printf("second num : %s\n", cur_rune->second_num);
    //    printf("answer : %s\n", cur_rune->answer);
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

  for(; !is_operator(buffer[i]) ; i++);

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

int solve_rune(struct Rune *rune) {
  char possible_digits[10];
  int i;
  for(i = 0 ; i < 10 ; i++) {
    possible_digits[i] = i + '0';
  }

  get_possible_digits(possible_digits, rune);

  for(i = 0 ; i < 10 ; i++) {
    if(possible_digits[i] != '\0' && is_solution(possible_digits[i], rune)) {
      return i;
    }
  }
  return -1;
}

int is_solution(char cur_char, struct Rune *rune) {
  int first_length = strlen(rune->first_num) + 1;
  char new_first[first_length];
  strcpy(new_first, rune->first_num);
  
  int second_length = strlen(rune->second_num) + 1;
  char new_second[second_length];
  strcpy(new_second, rune->second_num);

  int answer_length = strlen(rune->answer) + 1;
  char new_answer[answer_length];
  strcpy(new_answer, rune->answer);

  int i;
  for(i = 0 ; i < first_length ; i++) {
    if(new_first[i] == '?') new_first[i] = cur_char;
  }

  for(i = 0 ; i < second_length ; i++) {
    if(new_second[i] == '?') new_second[i] = cur_char;
  }

  for(i = 0 ; i < answer_length ; i++) {
    if(new_answer[i] == '?') new_answer[i] = cur_char;
  }

  return rune->operator(atol(new_first), atol(new_second)) == atol(new_answer);
}


void get_possible_digits(char *arr, struct Rune *rune) {
  filter_val(arr, rune->first_num);
  filter_val(arr, rune->second_num);
  filter_val(arr, rune->answer);
}

void filter_val(char *arr, char *num) {
 int i;
  for(i = 0 ; i < strlen(num) ; i++) {
    if(num[i] != '?') arr[num[i] - '0'] = '\0';
  }
}

/* 
   Copies a string from the 'from' parameter to the 'to' parameter. 
   Begins copying at the start parameter and stops at the 'end' parameter, exclusive.
 */
void string_copy(char* from, char* to, int start, int end) {
  int i,j;
  for(i = start, j = 0; i < end ; i++, j++) {
    *(to + j) = *(from + i);
  }
}

/* Returns whether the passed char is one of the possible operators */
int is_operator(char c) {
  return c == '+'
      || c == '-' 
      || c == '*';
}

/* Allocates a rune struct and returns a pointer to it. */
void init_rune(struct Rune** rune) {
  *rune = (struct Rune*) malloc(sizeof(struct Rune));
}

void free_rune(struct Rune *rune) {
  
}


/* Converts the given string to a long. Assumes that every character in the string is a digit
 and that the string is null-terminated.*/
long str_to_long(char *str) {
  /*
  int length = strlen(str);
  int i,counter = 0;

  for(i = 0; i < length ; i++) {
    if(i == 0) counter = 1;
    else counter *= 10;
  }

  long num = 0;
  for(i = 0 ; i < length ; i++) {
    num += (counter * (str[i] - '0'));
    counter /= 10;
  }

  return num;*/
  return atol(str);
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

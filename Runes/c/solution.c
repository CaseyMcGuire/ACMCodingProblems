#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long (*get_operator(char)) (long, long);
long plus(long first, long second);
long minus(long first, long second);
long multiply(long first, long second);
struct Rune* get_rune();
void init_rune(struct Rune**);
int is_operator(char c);
void string_copy(char *to, char *from, int start, int end);
int solve_rune(struct Rune *rune);
void free_rune(struct Rune *rune);
void get_possible_digits(char *arr, struct Rune *rune);
void filter_val(char *arr, char *num);
int is_solution(char cur_char, struct Rune *rune);
void fill_array(char *num, char replacement, int length);
int is_valid_number(char *num, int length);

struct Rune {
  char *first_num;
  int first_num_length;
  char *second_num;
  int second_num_length;
  char *answer;
  int answer_length;
  long (*operator)(long,long);
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
    free_rune(cur_rune);
  }
  return 0;
}

struct Rune* get_rune() {
  struct Rune *rune;
  
  /* Read in the maximum possible length of a line */
  /* The longest possible is -999999*999999=-999998000001*/
  /* By my count, this about 29 characters. */
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
  rune->first_num_length = strlen(rune->first_num);

  /* Get our function */
  rune->operator = get_operator(buffer[i]);

  /* Get our second number */
  int j = i + 1;
  for(; buffer[j] != '=' ; j++);
  rune->second_num = (char*) malloc(j - i);
  string_copy(buffer, rune->second_num, i + 1, j);

  *(rune->second_num + (j - i - 1)) = '\0';
  rune->second_num_length = strlen(rune->second_num);

  /* Now, get the answer */
  rune->answer = (char*) malloc(line_length - j);
  string_copy(buffer, rune->answer, j + 1, line_length);
  *(rune->answer + (line_length - j - 1)) = '\0';
  rune->answer_length = strlen(rune->answer);

  return rune;
}

/* Given a rune, return the number that will solve it. */
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

/* Returns whether the passed character is a solution for the passed rune.  */
int is_solution(char cur_char, struct Rune *rune) {
  int first_length = rune->first_num_length + 1;
  char new_first[first_length];
  strcpy(new_first, rune->first_num);
  
  int second_length = rune->second_num_length + 1;
  char new_second[second_length];
  strcpy(new_second, rune->second_num);

  int answer_length = rune->answer_length + 1;
  char new_answer[answer_length];
  strcpy(new_answer, rune->answer);

  fill_array(new_first, cur_char, first_length);
  if(!is_valid_number(new_first, first_length)) return 0;

  fill_array(new_second, cur_char, second_length);
  if(!is_valid_number(new_second, second_length)) return 0;

  fill_array(new_answer, cur_char, answer_length);
  if(!is_valid_number(new_answer, answer_length)) return 0;

  return rune->operator(atol(new_first), atol(new_second)) == atol(new_answer);
}

/* Replaces all question marks in the num char array with the replacement parameter.  */
void fill_array(char *num, char replacement, int length) {
  int i;
  for(i = 0 ; i < length ; i++) {
    if(num[i] == '?') num[i] = replacement;
  }
}

/* Returns whether the passed string is a valid number. A number is valid if it doesn't start with
 a zero or is only one character (Note: this assumes each char is a digit)*/
int is_valid_number(char *num, int length) {
  return length == 2 || num[0] != '0';
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
  free(rune->first_num);
  free(rune->second_num);
  free(rune->answer);
  free(rune);
  rune = NULL;
}

/*
  Given a arithmetic character ('+','-', '*'), returns a function pointer that will
  perform that operation on two ints.
 */
long (*get_operator(char operator)) (long,long) {
  long (*func)(long,long);
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
long plus(long first, long second) {
  return first + second;
}

/* Multiplies the first and second argument together and returns it. */
long multiply(long first, long second) {
  return first * second;
}

/* Subtracts the second argument from the first argument and returns it. */
long minus(long first, long second) {
  return first - second;
}

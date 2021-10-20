/*
 * @ProjectName - 1. Projekt - Práce s textem;
 * @Author - Jáchym Doležal;
 * @Login - xdolez0c;
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define BUFFER_SIZE 102
#define CHAR_TABLE_SIZE 127

//Replaces \n with \0
void my_newlineremoval(char * str){ 
  for(int index = 0; str[index] != '\0'; index++){
    if(str[index] == '\n'){
      str[index] = '\0';
    }
  }
}

/**
 * @description - Counts a length of a string until it reaches the end of it.
 * @param str - string 
 * @returns strlen - number of a characters in a given string
 */
int my_strlen(char * str) { 
  int strlen = 0;
  while (str[strlen] != '\0' && str[strlen] != '\r' && str[strlen] != '\n') {
    strlen++;
  }
  return strlen;
}

//Returns true if two compared strings are the same, otherwise returns false.
bool my_strcmp(char * mystr, char * cmpdstr) { 
  for (int index = 0; mystr[index] == cmpdstr[index]; index++) {
    if (mystr[index] == '\0') {
      return true;
    }
  }
  return false;
}

//Returns true if a lowercase char is present in a string, otherwise returns false.
bool lowercase_check(char * mystr) { 
  for (int index = 0; mystr[index] != '\0'; index++) {
    if (mystr[index] >= 'a' && mystr[index] <= 'z') {
      return true;
    }
  }
  return false;
}

//Returns true if an uppercase char is present in a string, otherwirse returns false.
bool uppercase_check(char * mystr) { 
  for (int index = 0; mystr[index] != '\0'; index++) {
    if (mystr[index] >= 'A' && mystr[index] <= 'Z') {
      return true;
    }
  }
  return false;
}

//Returns true if a number char is present in a string, otherwise returns false.
bool num_check(char * mystr) { 
  for (int index = 0; mystr[index] != '\0'; index++) {
    if (mystr[index] >= '0' && mystr[index] <= '9') {
      return true;
    }
  }
  return false;
}

//Returns true if char is present in the range from 33 to 126 in the ASCII table.
bool specialsign_check(char * mystr) { 
  // 32-126
  for (int index = 0; mystr[index] != '\0'; index++) {
    if ((mystr[index] >= ' ' && mystr[index] <= '/') ||
      (mystr[index] >= ':' && mystr[index] <= '@') ||
      (mystr[index] >= '[' && mystr[index] <= '`') ||
      (mystr[index] >= '{' && mystr[index] <= '~')) {
      return true;
    }
  }
  return false;
}

//Returns false if an upperboundery of repeating characters is found.
bool samechars_check(int param, char * mystr) { 
  int count = 0;
  for (int index = 0; mystr[index] != '\0'; index++) {
    if (mystr[index + 1] == '\0') {
      continue;
    } else if (mystr[index + 1] == mystr[index]) {
      count++;
    } else {
      count = 0;
    }
    if (count == param - 1) {
      return false; }
  }
  return true;
}

//Returns true if an upperboundary of reapeting substrings is found. 
bool substrings_check(int param, char * mystr) { 
  int count;
  int strike = 0;
  for (int index = 0; mystr[index + param] != '\0'; index++) {
    for (int idx = index + 1; mystr[idx] != '\0'; idx++) {
      count = index;
      for (int i = idx; i < param + idx && mystr[i] != '\0'; i++) {
        if (mystr[count] == mystr[i]) {
          strike++;
        } else {
          strike = 0;
        }
        if (strike >= param) {

          return false;
        }
        count++;
      }
    }
  }
  return true;
}

//Counts all unique characters in a string and outputs the result when used output = true and "printresults as a input string" 
int unique_chars(char * mystr, bool output, int array[]) { 
  int result = 0;
  int char_index;
  for (int index = 0; mystr[index] != '\0'; index++) {
    for (int index = 0; mystr[index] != '\0' && mystr[index] != '\n' && mystr[index] != '\r'; index++) {
      char_index = (int)(mystr[index]);
      if (array[char_index] == 0) {
        array[char_index] = 1;
      }
    }

    // If parameter output is set true, it returns the number of unique characters. 
    if (output) {
      for (int index = 0; index < CHAR_TABLE_SIZE; index++) {
        if (array[index] == 1) {
          result++;
        }
      }
      return result;
    }
  }
  return 0;
}

//Based on parameters level and param decided which functions for password checking will be called.
bool arg_parser(int level, int param, bool *upchars,bool *numchars,bool *specialchars, bool *samechars, bool *substrings, bool *lowchars, bool *printing){
    if (level >= 1 && level <= 4 && param >= 1 && param <= 4) {
    if (level == 4) {
      *lowchars = true;
      *upchars = true;
      *substrings = true;
      *samechars = true;
      *substrings = true;
    }
    if (level == 3) {
      *lowchars = true;
      *upchars = true;
      *samechars = true;
    }
    if (level >= 2 && param <= 4) {
      *lowchars = true;
      *upchars = true;
    }
    if (level >= 1 && param <= 4) {
      *lowchars = true;
      *upchars = true;
    }
    if (level >= 2 && (param >= 3 && param <= 4)) {
      *lowchars = true;
      *upchars = true;
      *numchars = true;
    }
    if (level >= 2 && param == 4) {
      *lowchars = true;
      *upchars = true;
      *numchars = true;
      *specialchars = true;
    }
  }
  if (param > 4) {
    *printing = false;
  }
  return 0;
}

int main(int argc, char * argv[]) {
  int ascii[CHAR_TABLE_SIZE] = {0};
  int str_tot_count = 0;
  int min_str = 100;
  int str_tot_sum = 0;
  float str_len_avg;
  char * pEnd_param, * pEnd_level;
  bool upchars = false;
  bool numchars = false;
  bool specialchars = false;
  bool samechars = false;
  bool substrings = false;
  bool stats = false;
  bool lowchars = false;
  bool printing = true;

  //Checks for unexcpected number of arguments
  if (argc <= 2 || argc > 4) { 
    fprintf(stderr, "Error, unexcpected number of arguments.\n");
    return EXIT_FAILURE;
  }

  int level = strtol(argv[1], & pEnd_level, 10);
  int param = strtol(argv[2], & pEnd_param, 10);

  //Returns error when argument param is smaller than 1
  if (param <= 0) {
    fprintf(stderr, "ERROR! parameter Param is smaller than 1\n");
    return EXIT_FAILURE;
  }

  if (level < 1 || level > 4) {
    fprintf(stderr, "ERROR! parameter LEVEL is not in range <1,4>\n");
    return EXIT_FAILURE;
  }

  if (argc == 4) {
    if (my_strcmp(argv[3], "--stats")) {
      stats = true;
    } else {
      fprintf(stderr, "Parameter stats is not in valid format (--stats)\n");
      return EXIT_FAILURE;
    }
  }
  if ((my_strlen(pEnd_level) > 0) || (my_strlen(pEnd_param) > 0)) {
    fprintf(stderr, "Parameter level and param must be only numbers\n");
    return EXIT_FAILURE;
  }

  arg_parser(level,param,&upchars,&numchars,&specialchars,&samechars,&substrings,&lowchars,&printing);

  char password[BUFFER_SIZE];
  while (fgets(password, sizeof(password), stdin) != NULL) {
    my_newlineremoval(password);
    int len = my_strlen(password);
    if (len > 100) {
      fprintf(stderr, "password was too long\n");
      return EXIT_FAILURE;
    }
    if (stats) {
      str_tot_sum += len;
      if (len < min_str) {
        min_str = len;
      }
      str_tot_count++;
      unique_chars(password, false, ascii);
    }
    if (lowchars) {
      if (lowercase_check(password) == false) {
        continue;
      }
    }
    if (upchars) {
      if (uppercase_check(password) == false) {
        continue;
      }
    }
    if (numchars) {
      if (num_check(password) == false) {
        continue;
      }
    }
    if (specialchars) {
      if (specialsign_check(password) == false) {
        continue;
      }
    }
    if (samechars) {
      if (samechars_check(param, password) == false) {
        continue;
      }
    }
    if (substrings) {
      if (substrings_check(param, password) == false) {
        continue;
      }
    }
    if (printing) {
      printf("%s\n", password);
    }
  }
  if (stats) {
    str_len_avg = (float) str_tot_sum / (float) str_tot_count;
    str_len_avg = ((float)((int)(str_len_avg * 10))) / 10;
    printf("Statistika:\nRuznych znaku: %d\nMinimalni delka: %d\nPrumerna delka: %.1f\n", unique_chars(password, true, ascii), min_str, str_len_avg);
  }
  return 0;
}
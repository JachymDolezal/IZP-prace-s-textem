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

//Replaces '\n' with '\0'
void my_newlineremoval(char * str){ 
  for(int index = 0; str[index] != '\0'; index++){
    if(str[index] == '\n'){
      str[index] = '\0';
    }
  }
}

//description - Counts a length of a string until it reaches the end of it.
int my_strlen(char * str) { 
  int strlen = 0;
  while (str[strlen] != '\0' && str[strlen] != '\r' && str[strlen] != '\n') {
    strlen++;
  }
  return strlen;
}

// Compares two strings, return true when they match
bool my_strcmp(char * str, char * cmpdstr) { 
  for (int index = 0; str[index] == cmpdstr[index]; index++) {
    if (str[index] == '\0') {
      return true;
    }
  }
  return false;
}

//Returns true if a lowercase char is present in a string, otherwise returns false.
bool lowercase_check(char * str) { 
  for (int index = 0; str[index] != '\0'; index++) {
    if (str[index] >= 'a' && str[index] <= 'z') {
      return true;
    }
  }
  return false;
}

//Returns true if an uppercase char is present in a string, otherwirse returns false.
bool uppercase_check(char * str) { 
  for (int index = 0; str[index] != '\0'; index++) {
    if (str[index] >= 'A' && str[index] <= 'Z') {
      return true;
    }
  }
  return false;
}

//Returns true if a number char is present in a string, otherwise returns false.
bool num_check(char * str) { 
  for (int index = 0; str[index] != '\0'; index++) {
    if (str[index] >= '0' && str[index] <= '9') {
      return true;
    }
  }
  return false;
}

//Returns true if char of special sign is found in a given string. 
bool specialsign_check(char * str) { 
  for (int index = 0; str[index] != '\0'; index++) {
    if ((str[index] >= ' ' && str[index] <= '/') ||
      (str[index] >= ':' && str[index] <= '@') ||
      (str[index] >= '[' && str[index] <= '`') ||
      (str[index] >= '{' && str[index] <= '~')) {
      return true;
    }
  }
  return false;
}

//Returns false if an upperboundery of repeating characters is found.
bool samechars_check(int param, char * str) { 
  int samechar_count = 0;
  for (int index = 0; str[index] != '\0'; index++) {
    if (str[index + 1] == '\0') {
      continue;
    } else if (str[index + 1] == str[index]) {
      samechar_count++;
    } else {
      samechar_count = 0;
    }
    if (samechar_count == param - 1) {
      return false; }
  }
  return true;
}

//Returns true if an upperboundary of reapeting substrings is found. 
bool substrings_check(int param, char * str) { 
  int sub;
  int samechar_count = 0;
  for (int i = 0; str[i + param] != '\0'; i++) {
    for (int j = i + 1; str[j] != '\0'; j++) {
      sub = i;
      for (int k = j; i < param + j && str[k] != '\0'; k++) {
        if (str[sub] == str[k]) {
          samechar_count++;
        } else {
          samechar_count = 0;
        }
        if (samechar_count >= param) {

          return false;
        }
        sub++;
      }
    }
  }
  return true;
}

//Counts all unique characters in a string and outputs the result when used output = true and "printresults as a input string" 
void unique_chars(char * str, int array[]) { 
  int char_index;
    for (int index = 0; str[index] != '\0' && str[index] != '\n' && str[index] != '\r'; index++) {
      char_index = (int)(str[index]);
      if (array[char_index] == 0) {
        array[char_index] = 1;
        } 
      }
    }

//Returns sum of an array.
int sum_of_array(int array[]) {
  int result = 0;

  for(int index = 0; index < CHAR_TABLE_SIZE; index++){
    if (array[index] == 1){
      result++;
    }
  }
  return result;
}


//Based on parameters level and param decides which functions for password checking will be called.
bool arg_parser(int level, int param, bool *upchars,bool *numchars,bool *specialchars, bool *samechars, bool *substrings, bool *lowchars){

  *upchars = false;
  *numchars = false;
  *specialchars = false;
  *samechars = false;
  *substrings = false;
  *lowchars = false;

    if (level >= 1 && level <= 4 && param >= 1) {
      if(level >= 1 && level <= 4){
        *lowchars = true;
        *upchars = true;
      }
      if(level >= 2 && param >= 3){
        *numchars = true;
      }
      if(level >= 2 && param >= 4){
        *specialchars = true;
      }
      if(level >= 3){
        *samechars = true;
      }
      if(level == 4){
        *substrings = true;
      }
    }
  return 0;
}

typedef struct{
  bool upchars;
  bool numchars;
  bool specialchars;
  bool samechars;
  bool substrings;
  bool stats;
  bool lowchars;

} Functions;

typedef struct{

int str_tot_count;
int min_str;
int str_tot_sum;

} Statistics; 

int main(int argc, char * argv[]) {
  Functions func;
  Statistics var_stats;
  int ascii[CHAR_TABLE_SIZE] = {0};
  char password[BUFFER_SIZE];
  var_stats.str_tot_count = 0;
  var_stats.min_str = 100;
  var_stats.str_tot_sum = 0;
  float str_len_avg;
  char * pEnd_param, * pEnd_level;
  func.stats = false;
  //added in front of argc check
  int level = strtol(argv[1], & pEnd_level, 10);
  int param = strtol(argv[2], & pEnd_param, 10);

  //Checks for unexcpected number of arguments
  if (argc <= 2 || argc > 4) { 
    fprintf(stderr, "Nepovoleny pocet argumentu.\n");
    return EXIT_FAILURE;
  }

  //Returns error when argument param is smaller than 1
  if (param <= 0) {
    fprintf(stderr, "Parametr param musi byt nenulove prirozene cislo.\n");
    return EXIT_FAILURE;
  }
  if (level < 1 || level > 4) {
    fprintf(stderr, "Parametr level neni v povolenem intervalu (povoleny interval: 1-4).\n");
    return EXIT_FAILURE;
  }
  if (argc == 4) {
    if (my_strcmp(argv[3], "--stats")) {
      func.stats = true;
    } else {
      fprintf(stderr, "Parametr stats neni ve spravnem formatu (spravny format: --stats).\n");
      return EXIT_FAILURE;
    }
  }
  if ((my_strlen(pEnd_level) > 0) || (my_strlen(pEnd_param) > 0)) {
    fprintf(stderr, "Vstupni parametry level a param mohou byt pouze nenulova prirozena cisla.\n");
    return EXIT_FAILURE;
  }

  arg_parser(level,param,&func.upchars,&func.numchars,&func.specialchars,&func.samechars,&func.substrings,&func.lowchars);
  
  while (fgets(password, sizeof(password), stdin) != NULL) {
    my_newlineremoval(password);

    int len = my_strlen(password);

    if (len > 100) {
      fprintf(stderr, "Heslo nesmi byt delsi nez sto znaku\n");
      return EXIT_FAILURE;
    }

    if (func.stats) {
      var_stats.str_tot_sum += len;
      if (len < var_stats.min_str) {
        var_stats.min_str = len;
      }
      var_stats.str_tot_count++;
      unique_chars(password, ascii);
    }

    if (func.lowchars) {
      if (lowercase_check(password) == false) {
        continue;
      }
    }
    if (func.upchars) {
      if (uppercase_check(password) == false) {
        continue;
      }
    }
    if (func.numchars) {
      if (num_check(password) == false) {
        continue;
      }
    }
    if (func.specialchars) {
      if (specialsign_check(password) == false) {
        continue;
      }
    }
    if (func.samechars) {
      if (samechars_check(param, password) == false) {
        continue;
      }
    }
    if (func.substrings) {
      if (substrings_check(param, password) == false) {
        continue;
      }
    }
 
    printf("%s\n", password);
  
  }
  if (func.stats) {
    str_len_avg = (float) var_stats.str_tot_sum / (float) var_stats.str_tot_count;
    str_len_avg = ((float)((int)(str_len_avg * 10))) / 10;
    printf("Statistika:\nRuznych znaku: %d\nMinimalni delka: %d\nPrumerna delka: %.1f\n", sum_of_array(ascii), var_stats.min_str, str_len_avg);
  }
  return 0;
}
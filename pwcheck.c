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

//Replaces newline char with \0.
void my_newlineremoval(char * str) {
  for (int index = 0; str[index] != '\0'; index++) {
    if (str[index] == '\n') {
      str[index] = '\0';
    }
  }
}

//Counts a length of a string until it reaches the end of it.
int my_strlen(char * str) {
  int strlen = 0;
  while (str[strlen] != '\0' && str[strlen] != '\r' && str[strlen] != '\n') {
    strlen++;
  }
  return strlen;
}

//Compares two strings, returns true when they match.
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
      return false;
    }
  }
  return true;
}

//Returns true if an upperboundary of reapeting substrings is found. 
bool substrings_check(int param, char * str) {
  int sub;
  int samechar_count = 0;
  if (param >= my_strlen(str)) {
    return true;
  }
  for (int i = 0; str[i + param] != '\0'; i++) {
    for (int j = i + 1; str[j] != '\0'; j++) {
      sub = i;
      samechar_count = 0;
      for (int k = j; k < param + j && str[k] != '\0'; k++) {
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

//Counts all unique characters in a string. 
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

  for (int index = 0; index < CHAR_TABLE_SIZE; index++) {
    if (array[index] == 1) {
      result++;
    }
  }
  return result;
}

//Returns true if password meets all rules given by arguments level and param. 
bool pwchecker(int level, int param, char * password) {
  if (level >= 1 && level <= 4 && param >= 1) {
    if (level >= 1 && level <= 4) {
      if (lowercase_check(password) == false || uppercase_check(password) == false) {
        return false;
      }
    }
    if (level >= 2 && param >= 3) {
      if (num_check(password) == false) {
        return false;
      }
    }
    if (level >= 2 && param >= 4) {
      if (specialsign_check(password) == false) {
        return false;
      }
    }
    if (level >= 3) {
      if (samechars_check(param, password) == false) {
        return false;
      }
    }
    if (level == 4) {
      if (substrings_check(param, password) == false) {
        return false;
      }
    }
  }
  return true;
}

//Checks for errors in the input parameters.
bool error_check(int * level, int * param, char ** argv, int argc, bool * stats) {
  if (argc < 3 || argc > 4) {
    fprintf(stderr, "Nedovoleny pocet argumentu (dovoleny pocet argumentu: 2-3).\n");
    return false;
  }
  char * pEnd_param, * pEnd_level;
  * level = strtol(argv[1], & pEnd_level, 10);
  * param = strtol(argv[2], & pEnd_param, 10);

  if ( * param <= 0) {
    fprintf(stderr, "Parametr param musi byt kladne cele cislo.\n");
    return false;
  }
  if ( * level < 1 || * level > 4) {
    fprintf(stderr, "Parametr level neni v povolenem intervalu (povoleny interval: [1,4]).\n");
    return false;
  }
  if (argc == 4) {
    if (my_strcmp(argv[3], "--stats")) {
      * stats = true;
    } else {
      fprintf(stderr, "Parametr stats neni ve spravnem formatu (spravny format: --stats).\n");
      return false;
    }
  }
  if ((my_strlen(pEnd_level) > 0) || (my_strlen(pEnd_param) > 0)) {
    fprintf(stderr, "Vstupni parametry level a param mohou byt pouze nenulova prirozena cisla.\n");
    return false;
  }
  return true;
}

//Structure for variables used for calculating statistics.
typedef struct {

  int str_tot_count;
  int min_str;
  int str_tot_sum;
  int ascii[CHAR_TABLE_SIZE];

}
Statistics;

//Counts statistics of the passwords.
void stats_count(Statistics * var_stats, char * str) {
  int len = my_strlen(str);
  var_stats -> str_tot_sum += len;
  if (len < var_stats -> min_str) {
    var_stats -> min_str = len;
  }
  var_stats -> str_tot_count++;
  unique_chars(str, var_stats -> ascii);
}

//Outputs the results of the statisitcs to stdout.
void stats_print(Statistics var_stats) {
  float str_len_avg;
  if (var_stats.str_tot_sum != 0) {
    str_len_avg = (float) var_stats.str_tot_sum / (float) var_stats.str_tot_count;
    str_len_avg = ((float)((int)(str_len_avg * 10))) / 10;
  } else {
    str_len_avg = 0;
    var_stats.min_str = 0;
  }
  printf("Statistika:\nRuznych znaku: %d\nMinimalni delka: %d\nPrumerna delka: %.1f\n", sum_of_array(var_stats.ascii), var_stats.min_str, str_len_avg);
}

int main(int argc, char * argv[]) {
  //Sets initial values of the statistics variables.
  Statistics var_stats = {
    .str_tot_count = 0,
    .min_str = 100,
    .str_tot_sum = 0,
    .ascii = {0}
  };
  bool stats = false;
  char password[BUFFER_SIZE];
  int param;
  int level;

  //Checks for errors that might be caused by wrong input parameters. 
  if (error_check( &level, &param, argv, argc, &stats) == false) {
    return EXIT_FAILURE;
  }

  //Main loop that checks passwords one by one from stdin. 
  while (fgets(password, sizeof(password), stdin) != NULL) {

    my_newlineremoval(password);

    int len = my_strlen(password);

    if (len > 100) {
      fprintf(stderr, "Heslo nesmi byt delsi nez sto znaku\n");
      return EXIT_FAILURE;
    }

    if (stats) {
      stats_count( &var_stats, password);
    }

    if (pwchecker(level, param, password) == true) {
      printf("%s\n", password);
    }
  }

  if (stats) {
    stats_print(var_stats);
  }

  return EXIT_SUCCESS;
}
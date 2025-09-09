#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} config;

int is_spec(int c);
void instructions_for_flags(config *flags);
int is_tab(int c);
int is_new_line(int c);
int readFile(char *filename, config flags);
int parse_params(int argc, char **argv, char *short_options,
                 struct option long_options[], config *flags);

int main(int argc, char *argv[]) {
  config flags = {0};
  char *short_options = "beEnstTv";
  struct option long_options[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                  {"number", no_argument, NULL, 'n'},
                                  {"squeeze-blank", no_argument, NULL, 's'}};
  int error = parse_params(argc, argv, short_options, long_options, &flags);
  instructions_for_flags(&flags);
  if (error == 0) {
    while (optind < argc) {
      char *file = argv[optind++];
      if (readFile(file, flags) == 1) {
        printf("s21_cat: %s: No such file or directory\n", file);
      }
    }
  }
  if (error == 1) printf("usage: s21_cat [-beEnstTv] [file ...]\n");

  return 0;
}

void instructions_for_flags(config *flags) {
  if (flags->b == 1 && flags->n == 1) flags->n = 0;
  return;
}

int is_spec(int c) {
  int res = 0;
  if ((c >= 0 && c <= 8) || (c >= 11 && c <= 31) || (c >= 127 && c <= 159))
    res = 1;
  return res;
}

int is_tab(int c) {
  int res = 0;
  if (c == '\t') res = 1;
  return res;
}

int is_new_line(int c) {
  int res = 0;
  if (c == '\n') res = 1;
  return res;
}

int readFile(char *filename, config flags) {
  FILE *f = NULL;
  int fileError = 0;
  if ((f = fopen(filename, "r")) == NULL) {
    fileError = 1;
  } else {
    int ch;
    int start_line = 1;          // is it first char of line? yes = 1
    int line_number = 1;         // Number of line for flag b or n
    int empty_line_counter = 0;  // count of empty lines in row
    while ((ch = fgetc(f)) != EOF) {
      if (flags.s == 1 && start_line == 1 && is_new_line(ch) &&
          empty_line_counter > 0)
        continue;
      if (flags.s == 1 && start_line == 1 && is_new_line(ch) &&
          empty_line_counter == 0)
        empty_line_counter++;
      if (!is_new_line(ch) && start_line == 1 &&
          (flags.b == 1 || flags.n == 1)) {
        printf("%6u\t", line_number++);
      }
      if (is_new_line(ch) && start_line == 1 && flags.n == 1) {
        printf("%6u\t", line_number++);
        start_line = 0;
      }
      if (is_new_line(ch) && start_line == 1 && flags.b == 1 && flags.e == 1) {
        start_line = 0;
      }
      if ((is_spec(ch) && flags.v == 1) || (is_tab(ch) && flags.t == 1)) {
        start_line = 0;
        empty_line_counter = 0;
        if (ch > 127) printf("M-");
        printf("^%c", ch >= 32 ? ch - '@' : ch + '@');
      } else if (is_new_line(ch)) {
        start_line = 1;
        if (flags.e == 1) {
          printf("$\n");
        } else {
          printf("\n");
        }
      } else {
        empty_line_counter = 0;
        start_line = 0;
        printf("%c", ch);
      }
    }
    fclose(f);
  }

  return fileError;
}

int parse_params(int argc, char **argv, char *short_options,
                 struct option long_options[], config *flags) {
  int res = 0;
  int error = 0;
  int idx = 0;

  while ((res = getopt_long(argc, argv, short_options, long_options, &idx)) !=
         -1) {
    switch (res) {
      case 'b':
        flags->b = 1;
        break;
      case 'e':
        flags->e = 1;
        flags->v = 1;
        break;
      case 'E':
        flags->e = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 't':
        flags->t = 1;
        flags->v = 1;
        break;
      case 'T':
        flags->t = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case '?':
        error = 1;
        break;
      default:
        error = 1;
        break;
    }
  }
  return error;
}

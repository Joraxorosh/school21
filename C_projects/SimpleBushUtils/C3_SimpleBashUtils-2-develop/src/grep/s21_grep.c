#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct templates {
  char *tpl;
  struct templates *next;
} LIST;

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int single_file;
} config;

int parse_args(int argc, char **argv, config *flags, LIST **templates);
int process_flags(config *flags, int getopt_result, LIST **templates);
int process_e_flag(char *template_str, LIST **templates);
int process_f_flag(char *file_name, LIST **templates);
int add_str_to_templates(char *str, LIST **templates);
void process_files(char *file_name, config flags, LIST *templates);
LIST *process_line(char *checked_line, config flags, LIST *templates);
LIST *process_v_flag(config flags, const char *checked_line, LIST *tokens);
int process_l_flag(config flags, int token_line_cnt, const LIST *tokens);
LIST *process_o_flag(const char *checked_line, LIST *templates,
                     regmatch_t *regmatch, int cflags, regex_t *reg,
                     int match_res, LIST *founded_list, size_t *offset);
LIST *reverse_list(LIST *head);
LIST *add_node(LIST *head, char *template);
void free_list(LIST *head);
void line_print(char const *file_name, char *str, int cnt, config flags);
void flag_lc_print(char *str, int line_cnt, config flags);
void print_arg_error();
void print_file_error(char *file_name);
void print_tokens(const char *file_name, config flags, int file_line_cnt,
                  LIST *head_tokens);

int main(int argc, char **argv) {
  config flags = {0};
  LIST *templates = NULL;
  int result_code = 1;
  if (argc > 2)
    result_code = parse_args(argc, argv, &flags, &templates);
  else
    result_code = 1;
  if (result_code == 0)
    while (optind < argc) {
      char *file_name = argv[optind++];
      process_files(file_name, flags, templates);
    }
  if (result_code == 1) print_arg_error();
  free_list(templates);
  return result_code;
}

int parse_args(int argc, char **argv, config *flags, LIST **templates) {
  int getopt_result = 0;
  int result_code = 0;
  struct option long_options[] = {0};
  while (getopt_result > -1 && result_code == 0) {
    int option_index = 0;
    getopt_result =
        getopt_long(argc, argv, "ivclnhsoe:f:", long_options, &option_index);
    result_code = process_flags(flags, getopt_result, templates);
  }
  if (result_code == 0 && *templates == NULL)
    result_code = add_str_to_templates(argv[optind++], templates);
  if (argc - optind == 1) flags->single_file = 1;
  *templates = reverse_list(*templates);
  return result_code;
}

int process_flags(config *flags, int getopt_result, LIST **templates) {
  int result_code = 0;
  if (getopt_result == 'i')
    flags->i = 1;
  else if (getopt_result == 'v')
    flags->v = 1;
  else if (getopt_result == 'c')
    flags->c = 1;
  else if (getopt_result == 'l')
    flags->l = 1;
  else if (getopt_result == 'n')
    flags->n = 1;
  else if (getopt_result == 'h')
    flags->h = 1;
  else if (getopt_result == 's')
    flags->s = 1;
  else if (getopt_result == 'o')
    flags->o = 1;
  else if (getopt_result == 'e')
    result_code = process_e_flag(optarg, templates);
  else if (getopt_result == 'f')
    result_code = process_f_flag(optarg, templates);
  else if (getopt_result == '?')
    result_code = 1;
  return result_code;
}

int process_e_flag(char *template_str, LIST **templates) {
  return add_str_to_templates(template_str, templates);
}

int process_f_flag(char *file_name, LIST **templates) {
  int result_code = 0;
  FILE *fp = fopen(file_name, "r");
  if (fp == NULL) {
    print_file_error(file_name);
    result_code = 1;
  }
  if (!result_code) {
    char *template_str = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&template_str, &len, fp)) != EOF &&
           result_code == 0) {
      if (template_str[read - 1] == '\n') template_str[read - 1] = '\0';
      result_code = add_str_to_templates(template_str, templates);
    }
    free(template_str);
    fclose(fp);
  }
  return result_code;
}

int add_str_to_templates(char *template_str, LIST **templates) {
  int result_code = 0;
  char *template = strdup(template_str);
  if (template == NULL)
    result_code = 1;
  else
    *templates = add_node(*templates, template);
  return result_code;
}

void process_files(char *file_name, config flags, LIST *templates) {
  int error = 0;
  FILE *fp = fopen(file_name, "r");
  if (fp == NULL) {
    if (flags.s == 0) print_file_error(file_name);
    error = 1;
  }
  if (!error) {
    int file_line_cnt = 0;
    int token_line_cnt = 0;
    char *checked_line = NULL;
    size_t len = 0;

    ssize_t read;
    while ((read = getline(&checked_line, &len, fp)) != EOF) {
      if (checked_line[read - 1] == '\n') checked_line[read - 1] = '\0';
      file_line_cnt++;
      LIST *tokens = process_line(checked_line, flags, templates);
      tokens = process_v_flag(flags, checked_line, tokens);
      token_line_cnt = process_l_flag(flags, token_line_cnt, tokens);
      print_tokens(file_name, flags, file_line_cnt, tokens);
      free_list(tokens);
    }
    flag_lc_print(file_name, token_line_cnt, flags);
    free(checked_line);
    fclose(fp);
  }
}

void print_tokens(const char *file_name, config flags, int file_line_cnt,
                  LIST *head_tokens) {
  while (head_tokens) {
    if (!flags.v || !flags.o)
      line_print(file_name, head_tokens->tpl, file_line_cnt, flags);
    head_tokens = head_tokens->next;
  }
}

int process_l_flag(config flags, int token_line_cnt, const LIST *tokens) {
  if (tokens) {
    if (flags.l == 1 && token_line_cnt == 0)
      token_line_cnt = 1;
    else if (flags.l == 0)
      token_line_cnt += 1;
  }
  return token_line_cnt;
}

LIST *process_v_flag(config flags, const char *checked_line, LIST *tokens) {
  if (flags.v == 1 && !tokens) {
    char *fnd_line = strdup(checked_line);
    tokens = add_node(tokens, fnd_line);
  } else if (flags.v == 1 && tokens) {
    free_list(tokens);
    tokens = NULL;
  }
  return tokens;
}

LIST *process_line(char *checked_line, config flags, LIST *templates) {
  LIST *founded_list = NULL;
  size_t line_length = strlen(checked_line);
  regmatch_t regmatch[1] = {0};
  int cflags = 0;
  if (flags.i == 1) cflags |= REG_ICASE;
  regex_t reg = {0};
  LIST *head_templates = templates;
  int match_res = REG_NOMATCH;

  size_t offset = 0;
  if (flags.o == 0) {
    while (head_templates && match_res != 0) {
      if (regcomp(&reg, head_templates->tpl, cflags) == 0) {
        match_res = regexec(&reg, checked_line, 1, regmatch, 0);
        regfree(&reg);
      }
      head_templates = head_templates->next;
    }
    if (match_res == 0) {
      char *founded_line = strdup(checked_line);
      founded_list = add_node(founded_list, founded_line);
    }
  } else {
    while (offset <= line_length)
      founded_list = process_o_flag(checked_line, templates, regmatch, cflags,
                                    &reg, match_res, founded_list, &offset);
  }
  founded_list = reverse_list(founded_list);
  return founded_list;
}

LIST *process_o_flag(const char *checked_line, LIST *templates,
                     regmatch_t *regmatch, int cflags, regex_t *reg,
                     int match_res, LIST *founded_list, size_t *offset) {
  LIST *start_templates = templates;
  size_t max_fnd_len = 0;
  long long min_start_pos = 0;
  char *fnd_token = NULL;
  while (start_templates) {
    int eflags = 0;
    if ((*offset) > 0) eflags |= REG_NOTBOL;
    if (regcomp(reg, start_templates->tpl, cflags) == 0) {
      match_res = regexec(reg, checked_line + (*offset), 1, regmatch, eflags);
      regfree(reg);
      if (match_res == 0) {
        size_t fnd_len = regmatch->rm_eo - regmatch->rm_so;
        if ((regmatch->rm_so <= min_start_pos) && (fnd_len > max_fnd_len)) {
          min_start_pos = regmatch->rm_so;
          max_fnd_len = fnd_len;
          free(fnd_token);
          fnd_token = calloc(fnd_len + 1, sizeof(char));
          if (fnd_token)
            strncpy(fnd_token, checked_line + (*offset) + regmatch->rm_so,
                    fnd_len);
        }
      }
    }
    start_templates = start_templates->next;
  }
  if (max_fnd_len == 0)
    (*offset) += 1;
  else {
    (*offset) += max_fnd_len;
    founded_list = add_node(founded_list, fnd_token);
  }
  return founded_list;
}

LIST *reverse_list(LIST *head) {
  LIST *tail = head;
  while (tail) tail = tail->next;
  while (head) {
    LIST *node = NULL;
    node = head;
    head = head->next;
    node->next = tail;
    tail = node;
  }
  return tail;
}

LIST *add_node(LIST *head, char *template) {
  LIST *node = malloc(sizeof(LIST));
  node->next = head;
  node->tpl = template;
  return node;
}

void free_list(LIST *head) {
  while (head) {
    LIST *node = head;
    head = head->next;
    free(node->tpl);
    free(node);
  }
}

void print_arg_error() {
  printf("usage: s21_grep [-eivclnhsfo] [pattern] [file ...]\n");
}

void print_file_error(char *file_name) {
  printf("s21_grep: %s: No such file or directory\n", file_name);
}

void flag_lc_print(char *str, int line_cnt, config flags) {
  if (flags.c == 1 && !flags.l) {
    if (flags.single_file == 1)
      printf("%d\n", line_cnt);
    else {
      if (flags.h == 0)
        printf("%s:%d\n", str, line_cnt);
      else
        printf("%d\n", line_cnt);
    }
  }
  if (flags.l == 1 && line_cnt > 0) printf("%s\n", str);
}

void line_print(char const *file_name, char *str, int cnt, config flags) {
  if (!flags.c && !flags.l) {
    if (!flags.single_file && flags.n)
      if (!flags.h)
        printf("%s:%d:%s\n", file_name, cnt, str);
      else
        printf("%d:%s\n", cnt, str);
    else if (!flags.single_file && !flags.n)
      if (!flags.h)
        printf("%s:%s\n", file_name, str);
      else
        printf("%s\n", str);
    else if (flags.single_file && flags.n)
      printf("%d:%s\n", cnt, str);
    else if (flags.single_file && !flags.n)
      printf("%s\n", str);
  }
}
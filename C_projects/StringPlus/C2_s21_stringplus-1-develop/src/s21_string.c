#include "s21_string.h"

// ======================= STRING.H ============================
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int flag = 0;
  if (str1 != S21_NULL && str2 != S21_NULL) {
    unsigned char *ptr_str1 = (unsigned char *)str1;
    unsigned char *ptr_str2 = (unsigned char *)str2;
    for (s21_size_t i = 0; i < n && flag == 0; i++) {
      if (ptr_str1[i] != ptr_str2[i]) {
        flag = (int)ptr_str1[i] - (int)ptr_str2[i];
      }
    }
  }
  return flag;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  if (str != S21_NULL && n > 0) {
    unsigned char *ptr_str = (unsigned char *)str;
    for (s21_size_t i = 0; i < n; i++) {
      if (ptr_str[i] == (unsigned char)c) {
        return (void *)(ptr_str + i);
      }
    }
  }
  return S21_NULL;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  if (dest != S21_NULL || src != S21_NULL) {
    unsigned char *ptr_dest = (unsigned char *)dest;
    unsigned char *ptr_src = (unsigned char *)src;

    for (s21_size_t i = 0; i < n; i++) {
      ptr_dest[i] = ptr_src[i];
    }
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  if (str != S21_NULL) {
    unsigned char *ptr_str = (unsigned char *)str;
    for (s21_size_t i = 0; i < n; i++) {
      ptr_str[i] = (unsigned char)c;
    }
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  if (dest != S21_NULL && src != S21_NULL) {
    s21_size_t dest_len = s21_strlen(dest);
    s21_size_t i = 0;
    while (i < n && src[i] != '\0') {
      dest[dest_len] = src[i];
      dest[dest_len + 1] = '\0';
      i++;
      dest_len++;
    }
  }
  return dest;
}

char *s21_strchr(const char *str, int ch) {
  s21_size_t i = 0;
  char *val = S21_NULL;
  char flag = 0;
  while (!flag && (str[i] != '\0')) {
    if (str[i] == ch) {
      val = (char *)(str + i);
      flag = 1;
    }
    i++;
  }
  return val;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int out = 0;
  if (n > 0 && str1 && str2) {
    for (size_t i = 0; i < n && out == 0; i++) {
      if (str1[i] == '\0' || str1[i] != str2[i]) out = str1[i] - str2[i];
    }
  }
  return out;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *temp = dest;
  s21_size_t src_len = s21_strlen(src);
  s21_size_t copy_len = (n > src_len ? src_len + 1 : n);
  for (s21_size_t i = copy_len; i != 0 && (*temp = *src) != 0;
       i--, temp++, src++) {
    ;
  }
  dest[n] = '\0';
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t val = 0;
  char flag = 0;
  s21_size_t len = s21_strlen(str2);
  while (str1[val] != '\0' && !flag) {
    for (s21_size_t i = 0; i < len && !flag; i++) {
      if (str1[val] == str2[i]) flag = 1;
    }
    if (!flag) val++;
  }
  return val;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t val = 0;
  while (str[val++] != '\0') {
  }
  return val - 1;
}

char *s21_strrchr(const char *str, int ch) {
  char *val = (char *)str;
  s21_size_t i = 0;
  int count = 0;
  while (str[i] != '\0') {
    if (str[i] == ch) {
      val = (char *)(str + i);
      count++;
    }
    i++;
  }
  if (count == 0) val = S21_NULL;
  return val;
}

char *s21_strtok(char *str, const char *delim) {
  static char *last;
  static char *start;
  char cycle_flag = 0;
  char null_str = 0;
  s21_size_t len = s21_strlen(delim);
  if (str) {
    start = str;
    last = start;
  } else {
    start = last;
    null_str = 1;
  }
  while ((*last != '\0') && !cycle_flag) {
    for (s21_size_t i = 0; (i < len) && !cycle_flag; i++) {
      if (*last == delim[i]) {
        *last = '\0';
        cycle_flag = 1;
      }
    }
    last++;
  }
  if (!cycle_flag) {
    if (!null_str) start = S21_NULL;
    last = S21_NULL;
  }
  return start;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *val = (char *)str1;
  char cycle_flag = 0;
  s21_size_t len = s21_strlen(str2);
  while ((*val != '\0') && !cycle_flag) {
    for (int j = 0; (j < (int)len) && !cycle_flag; j++) {
      if (*val == str2[j]) cycle_flag = 1;
    }
    if (!cycle_flag) val++;
  }
  return (*val == '\0') ? NULL : val;
}

char *s21_strstr(const char *strB, const char *strA) {
  s21_size_t len1, len2;
  char *p = S21_NULL;
  len2 = s21_strlen(strA);
  if (len2 == 0)
    p = (char *)strB;
  else {
    int flag = 0;
    len1 = s21_strlen(strB);
    while (len1 >= len2 && !flag) {
      len1--;
      if (!s21_memcmp(strB, strA, len2)) {
        p = (char *)strB;
        flag = 1;
      }
      strB++;
    }
  }
  return p;
}

// ======================= SPECIAL STRING PROCESSING FUNCTIONS
// =========================

void *s21_to_upper(const char *str) {
  char *result = S21_NULL;
  if (str != S21_NULL) {
    int resultLen = s21_strlen(str) + 1;
    result = (char *)calloc(resultLen, sizeof(char));
    for (int i = 0; i < resultLen; i++) {
      if (str[i] >= 'a' && str[i] <= 'z')
        result[i] = str[i] - 32;
      else
        result[i] = str[i];
    }
  } else
    result = S21_NULL;
  return result;
}

void *s21_to_lower(const char *str) {
  char *result = S21_NULL;
  if (str != S21_NULL) {
    int resultLen = s21_strlen(str) + 1;
    result = (char *)calloc(resultLen, sizeof(char));
    for (int i = 0; i < resultLen; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z')
        result[i] = str[i] + 32;
      else
        result[i] = str[i];
    }
  } else
    result = S21_NULL;
  return result;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = S21_NULL;
  if (src && str && s21_strlen(src) >= start_index) {
    result =
        (char *)malloc((s21_strlen(src) + s21_strlen(str) + 1) * sizeof(char));
    if (result) {
      s21_strncpy(result, src, start_index);
      *(result + start_index) = '\0';
      s21_strncat(result, str, s21_strlen(str));
      s21_strncat(result, src + start_index, s21_strlen(src + start_index));
    }
  }
  return result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = S21_NULL;
  if (src && trim_chars) {
    const char *start_str = src;
    while (*start_str && s21_strchr(trim_chars, *start_str)) {
      start_str++;
    }
    if (*start_str != '\0') {
      const char *end_str = src + s21_strlen(src) - 1;
      while (end_str > start_str && s21_strchr(trim_chars, *end_str)) {
        end_str--;
      }
      s21_size_t len = (size_t)(end_str - start_str + 1);
      result = (char *)malloc(len + 1);
      if (result) {
        s21_memcpy(result, start_str, len);
        result[len] = '\0';
      }
    } else {
      result = (char *)malloc(1);
      if (result) {
        result[0] = '\0';
      }
    }
  }
  return result;
}

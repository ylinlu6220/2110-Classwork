// DO NOT MODIFY THIS FILE
#ifndef MY_STRING_H
#define MY_STRING_H

#include <stddef.h>

#define UNUSED_PARAM(x) ((void) x) // This macro is only used for turning off compiler errors initially

// Function prototypes for my_string.c
size_t my_strlen(const char *s);
int my_strncmp(const char *s1, const char *s2, size_t n);
char *my_strncpy(char *dest, const char *src, size_t n);
char *my_strncat(char *dest, const char *src, size_t n);
void *my_memset(void *str, int c, size_t n);
int is_palindrome_ignore_case(const char *str);
void caesar_shift(char *str, int shift);
void deduplicate_str(char *str);
void swap_strings(char **s1, char **s2);

#endif
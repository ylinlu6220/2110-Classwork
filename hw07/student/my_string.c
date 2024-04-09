/**
 * @file my_string.c
 * @author Yu Lin Lu
 * @brief Your implementation of the famous string.h library functions!
 *
 * NOTE: NO ARRAY NOTATION IS ALLOWED IN THIS FILE
 *
 * @date 2024-03-xx
 */

#include "my_string.h"

/* Note about UNUSED_PARAM
*
* UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
* parameters prior to implementing the function. Once you begin implementing this
* function, you can delete the UNUSED_PARAM lines.
*/

/**
 * @brief Calculate the length of a string
 *
 * @param s a constant C string
 * @return size_t the number of characters in the passed in string
 */
size_t my_strlen(const char *s)
{
    size_t length = 0;
    while (*s != '\0')
    {
        length++;
        s++;    
    }
    
    return length;
}

/**
 * @brief Compare two strings
 *
 * @param s1 First string to be compared
 * @param s2 Second string to be compared
 * @param n First (at most) n bytes to be compared
 * @return int representing the difference between the strings:
 *          - 0 if the strings are equal
 *          - arbitrary positive number if s1 > s2
 *          - arbitrary negative number if s1 < s2
 */
int my_strncmp(const char *s1, const char *s2, size_t n)
{
    int diff = 0;
    while (n > 0)
    {
        if (*s1 == '\0' && *s2 == '\0')
        {
            return 0;
        }
        diff = *s1 - *s2;
        if (diff != 0)
        {
            return diff;
        }
        s1++;
        s2++;
        n--;
    }
    return 0;
}

/**
 * @brief Copy a string
 *
 * @param dest The destination buffer
 * @param src The source to copy from
 * @param n maximum number of bytes to copy
 * @return char* a pointer same as dest
 */
char *my_strncpy(char *dest, const char *src, size_t n)
{
    char *dStart = dest;
    while (n > 0)
    {
        if (*src == '\0')
        {
            *dest = '\0';
        } else {
            *dest = *src;
            src++;
        }
        dest++;
        n--;
    }
    
    return dStart;
}

/**
 * @brief Concatenates two strings and stores the result
 * in the destination string
 *
 * @param dest The destination string
 * @param src The source string
 * @param n The maximum number of bytes (or characters) from src to concatenate
 * @return char* a pointer same as dest
 */
char *my_strncat(char *dest, const char *src, size_t n)
{
    char *dStart = dest;
    while (*dest != '\0')
    {
        dest++;
        
    }
    while (n > 0) {
        if (*src == '\0')
        {
            *dest = '\0';
            return dStart;
        } else {
            *dest = *src;
            src++;
        }
        dest++;
        n--;
    }
    return dStart;
}

/**
 * @brief Copies the character c into the first n
 * bytes of memory starting at *str
 *
 * @param str The pointer to the block of memory to fill
 * @param c The character to fill in memory
 * @param n The number of bytes of memory to fill
 * @return char* a pointer same as str
 */
void *my_memset(void *str, int c, size_t n)
{
    char *sStart = str; //sstart is a pointer to a character (str)
    char *start = sStart;   
    char byteC = (0xFF & c);
    while (n > 0)
    {
        *sStart = byteC;
        sStart++;
        n--;
    }
    return start;
}

/**
 * @brief Checks whether the string is a palindrome
 * (i.e., reads the same forwards and backwards)
 * assuming that the case of letters is irrelevant.
 * 
 * @param str The pointer to the string
 * @return 1 if the string is a palindrome,
 * or 0 if the string is not
*/
int is_palindrome_ignore_case(const char *str) 
{
    const char *strStart = str;
    const char *strEnd = str;
    while (*strEnd != '\0')
    {
        strEnd++;
    }
    strEnd--;
    
    while(strStart < strEnd)
    {
        char startChar = *strStart;
        char endChar = *strEnd;

        if (startChar >= 'A' && startChar <= 'Z'){
            startChar += 32;
        }
        if (endChar >= 'A' && endChar <= 'Z'){
            endChar += 32;
        }
        if (startChar != endChar){
            return 0;
        }
        strStart++;
        strEnd--;
    }
    return 1;
}

/**
 * @brief Apply a Caesar shift to each character
 * of the provided string in place.
 * 
 * @param str The pointer to the string
 * @param shift The amount to shift by
*/
void caesar_shift(char *str, int shift) 
{
    while (*str != '\0')
    {
        if (*str >= 'A' && *str <= 'Z')
        {
            *str = (*str - 'A' + shift) % 26 + 'A';
        } else if (*str >= 'a' && *str <= 'z')
        {
            *str = (*str - 'a' + shift) % 26 + 'a';
        }
        str++;
    }
    return;
}

/**
 * @brief Mutate the string in-place to
 * remove duplicate characters that appear
 * consecutively in the string.
 * 
 * @param str The pointer to the string
*/
void deduplicate_str(char *str) 
{
    char *strPtr = str;
    char *curr = str;
    while (*curr != '\0')
    {
        if (*curr != *(curr + 1)){
            *strPtr = *curr;
            curr++;
            strPtr++;
        } else {
            curr++;
        }
    }
    *strPtr = '\0';

    return;
}

/**
 * @brief Swap the position of
 * two strings in memory.
 * 
 * @param s1 The first string
 * @param s2 The second string
*/
void swap_strings(char **s1, char **s2) 
{
    char *temp = *s1;
    *s1 = *s2;
    *s2 = temp;

    return;
}
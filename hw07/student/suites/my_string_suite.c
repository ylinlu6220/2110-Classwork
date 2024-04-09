/**
 * @file my_string_suite.c
 * @author Farzam TN a.k.a Unc Zam
 * @brief Testing Suites to HW7 - Spring 2020
 * @date 2020-03-06
 */

// Check Docs
// Tutorial : https://libcheck.github.io/check/doc/check_html/check_3.html
// Check API: https://libcheck.github.io/check/doc/doxygen/html/check_8h.html

// System Headers

#include "test_utils.h"
#include <check.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static void randStringGenerator(char *dest, int length);

/******************************************************************************/
/**************************** my_strlen tests *********************************/
/******************************************************************************/

START_TEST(test_my_strlen_1) {
  const char *str = "12345";
  const char *backup = str; // pointers should not be changed
  size_t retVal = my_strlen(str);
  ck_assert_ptr_eq(str, backup);
  ck_assert_int_eq(retVal, strlen(str));
}
END_TEST

START_TEST(test_my_strlen_2) {
  const char *str = "1\0";
  const char *backup = str; // pointers should not be changed

  size_t retVal = my_strlen(str);
  ck_assert_ptr_eq(str, backup);
  ck_assert_int_eq(retVal, strlen(str));
}
END_TEST

START_TEST(test_my_strlen_3) {
  const char str[] = {'1', '2', '3', '\0', 'Z', 'f'};
  const char *backup = str; // pointers should not be changed
  size_t retVal = my_strlen(str);
  ck_assert_ptr_eq(str, backup);
  ck_assert_int_eq(retVal, strlen(str));
}
END_TEST

START_TEST(test_my_strlen_4) {
  srand(time(0));
  unsigned long randBoi = rand() % 512;
  if (randBoi < 100) {
    // Everybody gotta do at least 155 characters
    randBoi += 155;
  }

  // The only function that doesn't use the random string generator
  char str[512];
  const char *backup = str; // pointers should not be changed

  memset(str, 7, randBoi - 1);
  str[randBoi] = '\0';

  size_t retVal = my_strlen(str);
  ck_assert_ptr_eq(str, backup);
  ck_assert_int_eq(retVal, strlen(str));
}
END_TEST

START_TEST(test_my_strlen_5) {
  const char *str = "";
  const char *backup = str; // pointers should not be changed
  size_t retVal = my_strlen(str);
  ck_assert_ptr_eq(str, backup);
  ck_assert_int_eq(retVal, strlen(str));
}
END_TEST

/******************************************************************************/
/**************************** my_strncmp tests ********************************/
/******************************************************************************/

/**
 * All the strncmp test cases just check for negative, positive, or zero value
 * and the actual value doesn't matter. This is done to adhere to strncmp man
 * page and resources online.
 */

START_TEST(test_my_strncmp_equal) {
  const char *str1 = "1234/#?\\21tenMo";
  const char *str2 = "1234/#?\\21tenMo";

  const char *backup1 = str1; // pointers should not be changed
  const char *backup2 = str2; // pointers should not be changed

  size_t n = strlen(str1);

  int retVal = my_strncmp(str1, str2, n);
  int correctValSign = strncmp(str1, str2, n);

  if (correctValSign < 0) {
    ck_assert_int_lt(retVal, 0);
  } else if (correctValSign > 0) {
    ck_assert_int_gt(retVal, 0);
  } else {
    ck_assert_int_eq(retVal, correctValSign);
  }

  ck_assert_ptr_eq(str1, backup1);
  ck_assert_ptr_eq(str2, backup2);
}
END_TEST

START_TEST(test_my_strncmp_null_terminator_in_middle_almost_same) {
  const char str1_buf[] = {'Z', '\0', 'y', '0', 'h', 'a', '\0', 'Z', 'f'};
  const char *str1 = str1_buf + 2;
  const char str2_buf[] = {'A', 'a', 'y', '0', 'h', 'a', '\0', 'A', 'a'};
  const char *str2 = str2_buf + 2;

  const char *backup1 = str1; // pointers should not be changed
  const char *backup2 = str2;

  size_t n = strlen(str1) + 2;

  int retVal = my_strncmp(str1, str2, n);
  int correctValSign = strncmp(str1, str2, n);

  if (correctValSign < 0) {
    ck_assert_int_lt(retVal, 0);
  } else if (correctValSign > 0) {
    ck_assert_int_gt(retVal, 0);
  } else {
    ck_assert_int_eq(retVal, correctValSign);
  }

  ck_assert_ptr_eq(str1, backup1);
  ck_assert_ptr_eq(str2, backup2);
}
END_TEST

START_TEST(test_my_strncmp_null_terminator_in_middle_different) {
  // Should return negative
  const char str1_buf[] = {'Z', 'f', 'y', 'e', 'e', 'h', 'a', '\0', 'Z', 'f'};
  const char *str1 = str1_buf + 2;
  const char str2_buf[] = {'A', '\0', 'y', 'e',  'e', 'h', 'a',
                           'B', 'r',  'o', '\0', 'A', 'a'};
  const char *str2 = str2_buf + 2;

  const char *backup1 = str1; // pointers should not be changed
  const char *backup2 = str2;
  size_t n = strlen(str1) + 1;

  int retVal = my_strncmp(str1, str2, n);
  int correctValSign = strncmp(str1, str2, n);

  if (correctValSign < 0) {
    ck_assert_int_lt(retVal, 0);
  } else if (correctValSign > 0) {
    ck_assert_int_gt(retVal, 0);
  } else {
    ck_assert_int_eq(retVal, correctValSign);
  }

  ck_assert_ptr_eq(str1, backup1);
  ck_assert_ptr_eq(str2, backup2);
}
END_TEST

START_TEST(test_my_strncmp_random) {
  // Let's see if student's can hack this test case (without zerodays tho..)

  srand(time(0));
  unsigned int randBoi = rand() % 128;
  if (randBoi < 69) // "nice" - the person shall remain nameless
  {
    randBoi += 100; // Everybody gonna do 100 minimum
  }
  char str1[169];

  randStringGenerator(str1, sizeof(str1));

  char str2[169];
  strncpy(str2, str1, strlen(str1)); // Creating a copy
  str2[randBoi] = '\0';

  str2[5] = 'F'; // Yeah boiii

  const char *backup1 = str1; // pointers should not be changed
  const char *backup2 = str2;

  size_t n = (strlen(str1) / 2) + 1;

  int retVal = my_strncmp(str1, str2, n);
  int correctValSign = strncmp(str1, str2, n);

  if (correctValSign < 0) {
    ck_assert_int_lt(retVal, 0);
  } else if (correctValSign > 0) {
    ck_assert_int_gt(retVal, 0);
  } else {
    ck_assert_int_eq(retVal, correctValSign);
  }

  ck_assert_ptr_eq(str1, backup1);
  ck_assert_ptr_eq(str2, backup2);
}
END_TEST

/*
Test for shuffled letters in a string
Eg. s1 = "ABC", s2 = "CBA"
*/
START_TEST(test_my_strncmp_letters_shuffled) {
  const char *str1 = "ABCD";
  const char *str2 = "BCDA";

  const char *backup1 = str1; // pointers should not be changed
  const char *backup2 = str2; // pointers should not be changed

  size_t n = strlen(str1) + 1;

  int retVal = my_strncmp(str1, str2, n);
  int correctValSign = strncmp(str1, str2, n);

  if (correctValSign < 0) {
    ck_assert_int_lt(retVal, 0);
  } else if (correctValSign > 0) {
    ck_assert_int_gt(retVal, 0);
  } else {
    ck_assert_int_eq(retVal, correctValSign);
  }

  ck_assert_ptr_eq(str1, backup1);
  ck_assert_ptr_eq(str2, backup2);
}
END_TEST

START_TEST(test_my_strncmp_first_half_same_end_different_large_n) {
  const char *str1 = "chocolatecake";
  const char *str2 = "chocolatechipcookie";

  const char *backup1 = str1; // pointers should not be changed
  const char *backup2 = str2; // pointers should not be changed

  size_t n = strlen(str2) + 1;

  int retVal = my_strncmp(str1, str2, n);
  int correctValSign = strncmp(str1, str2, n);

  if (correctValSign < 0) {
    ck_assert_int_lt(retVal, 0);
  } else if (correctValSign > 0) {
    ck_assert_int_gt(retVal, 0);
  } else {
    ck_assert_int_eq(retVal, correctValSign);
  }

  ck_assert_ptr_eq(str1, backup1);
  ck_assert_ptr_eq(str2, backup2);
}
END_TEST

START_TEST(test_my_strncmp_first_half_same_end_different_small_n) {
  const char *str1 = "chocolatecake";
  const char *str2 = "chocolatechipcookie";

  const char *backup1 = str1; // pointers should not be changed
  const char *backup2 = str2; // pointers should not be changed

  size_t n = 7;

  int retVal = my_strncmp(str1, str2, n);
  int correctValSign = strncmp(str1, str2, n);

  if (correctValSign < 0) {
    ck_assert_int_lt(retVal, 0);
  } else if (correctValSign > 0) {
    ck_assert_int_gt(retVal, 0);
  } else {
    ck_assert_int_eq(retVal, correctValSign);
  }

  ck_assert_ptr_eq(str1, backup1);
  ck_assert_ptr_eq(str2, backup2);
}
END_TEST

START_TEST(test_my_strncmp_almost_equal) {
  const char *str1 = "spooky scary skeleton";
  const char *str2 = "spooky scary skeletons";

  const char *backup1 = str1; // pointers should not be changed
  const char *backup2 = str2; // pointers should not be changed

  size_t n = strlen(str2);

  int retVal = my_strncmp(str1, str2, n);
  int correctValSign = strncmp(str1, str2, n);

  if (correctValSign < 0) {
    ck_assert_int_lt(retVal, 0);
  } else if (correctValSign > 0) {
    ck_assert_int_gt(retVal, 0);
  } else {
    ck_assert_int_eq(retVal, correctValSign);
  }

  ck_assert_ptr_eq(str1, backup1);
  ck_assert_ptr_eq(str2, backup2);
}
END_TEST

/******************************************************************************/
/*************************** my_strncpy tests *********************************/
/******************************************************************************/
START_TEST(test_my_strncpy_basic) {
  char src[] = {'\0'};
  const char *backup = src; // pointers should not be changed

  char dest[] = {'a', '\0'};
  size_t n = 1;

  char *retVal = my_strncpy(dest, src, n);

  // Checking if dest didn't change
  ck_assert_ptr_eq(retVal, dest);

  ck_assert_ptr_eq(src, backup);

  // Checking if strncmp returns 0
  ck_assert_msg(!strncmp(dest, src, n),
                "did not overwrite first byte of dest\n");
}
END_TEST

START_TEST(test_my_strncpy_destination_larger) {
  char *src =
      "His palms are sweaty, knees weak, arms are heavy ... mom's spaghetti";
  const char *backup = src; // pointers should not be changed

  char dest[100];
  memset(dest, 0, sizeof(dest)); // just to be safe
  size_t n = strlen(src);

  char *retVal = my_strncpy(dest, src, n);

  // Checking if dest didn't change
  ck_assert_ptr_eq(retVal, dest);

  ck_assert_ptr_eq(src, backup);

  // Checking if strncmp returns 0
  ck_assert_msg(!strncmp(dest, src, n),
                "did not overwrite first byte of dest\n");
}
END_TEST

START_TEST(test_my_strncpy_random_basic_256) {
  srand(time(0) - 5000); // 5000 means something Sean

  // Generate random source
  char src[256 + 1];
  const char *backup = src; // pointers should not be changed

  randStringGenerator(src, sizeof(src));

  // No null-termination on dest on purpose
  char dest[256];
  size_t n = strlen(src);
  char *retVal = my_strncpy(dest, src, n);

  // Checking if dest didn't change
  ck_assert_ptr_eq(retVal, dest);

  ck_assert_ptr_eq(src, backup);

  // Checking if strncmp returns 0
  ck_assert_msg(
      !strncmp(dest, src, n),
      "did not copy the first 256 characters of src to dest correctly\n");
}
END_TEST

START_TEST(test_my_strncpy_null_terminator_in_middle) {
  srand(time(0) - 5000); // 5000 means something Sean

  // Generate random source
  char src[256];
  randStringGenerator(src, sizeof(src));
  const char *backup = src; // pointers should not be changed

  // Null terminating in middle to make sure they only copy all the way to null
  // terminator
  150 [src] = 0; // gangsta move

  // No null-termination on dest on purpose
  char dest[256];
  memset(dest, 7, sizeof(256)); // Filling destination with arbitrary val
  size_t n = 256;
  char *retVal = my_strncpy(dest, src, n);

  // Checking if dest didn't change
  ck_assert_ptr_eq(retVal, dest);

  ck_assert_ptr_eq(src, backup);

  // Size should be the same because of n and null terminator position
  ck_assert_int_eq(strlen(dest), strlen(src));

  // Checking if strncmp returns 0
  ck_assert_msg(
      !strncmp(dest, src, strlen(src) + 1),
      "did not copy src to dest correctly when null terminator is in middle\n");
}
END_TEST

START_TEST(test_my_strncpy_overwrite) {
  char src[100];
  randStringGenerator(src, sizeof(src));
  const char *backup = src; // pointers should not be changed

  char dest[100];
  randStringGenerator(dest, sizeof(dest));
  size_t n = strlen(dest);

  char *retVal = my_strncpy(dest, src, n);

  // Checking if dest didn't change
  ck_assert_ptr_eq(retVal, dest);

  ck_assert_ptr_eq(src, backup);

  // Checking if strncmp returns 0
  ck_assert_msg(!strncmp(dest, src, n),
                "did not overwrite destination completely\n");
}
END_TEST

START_TEST(test_my_strncpy_adv) {
  char src[77];
  randStringGenerator(src, sizeof(src));
  const char *backup = src; // pointers should not be changed

  // Making sure we overwrite null terminator at the end so strncpy doesn't halt
  // early
  src[strlen(src) - 1] = 'F';

  char dest[100];
  randStringGenerator(dest, sizeof(dest));
  size_t n = strlen(dest) - 1;

  // so everything after src length should be nulled out

  char *retVal = my_strncpy(dest, src, n);

  // Checking if dest didn't change
  ck_assert_ptr_eq(retVal, dest);
  ck_assert_ptr_eq(src, backup);

  // Checking if strncmp returns 0
  ck_assert_msg(!strncmp(dest, src, strlen(src)),
                "did not overwrite destination completely\n");

  // Making sure students actually read the man page
  // "If the length of src is less than n, strncpy() writes additional null
  // bytes to dest to ensure that a total of n bytes are written."
  char zeroedOut[100];
  memset(zeroedOut, '\0', sizeof(zeroedOut));
  int test = !strncmp(dest + strlen(src), zeroedOut, n - strlen(src));
  ck_assert_msg(test, "Make sure you read the man page carefully\n");
}
END_TEST

/******************************************************************************/
/**************************** my_strncat tests ********************************/
/******************************************************************************/
START_TEST(test_my_strncat_basic) {
  char src[] = {'b', '\0'};

  char dest[] = {'a', '\0'};
  size_t n = 1;

  char *retVal = my_strncat(dest, src, n);

  // Checking if dest didn't change
  ck_assert_ptr_eq(retVal, dest);

  // Checking if strncmp returns 0
  char dest1[] = {'a', '\0'};
  char *correctVal = strncat(dest1, src, n);
  ck_assert_int_eq(strncmp(retVal, correctVal, strlen(correctVal)), 0);
}
END_TEST

START_TEST(test_my_strncat_random) {
  char src[100];
  randStringGenerator(src, sizeof(src));

  char dest[200] = "123";
  char dest1[200] = "123";
  size_t n = strlen(src);

  char *retVal = my_strncat(dest, src, n);
  char *correctVal = strncat(dest1, src, n);

  // Checking if dest pointer didn't change
  ck_assert_ptr_eq(retVal, dest);

  // Checking if strncmp returns 0
  ck_assert_int_eq(strncmp(retVal, correctVal, strlen(dest1)), 0);
}
END_TEST

START_TEST(test_my_strncat_null_terminator) {
  char src[100];
  randStringGenerator(src, sizeof(src));

  char dest[200] = "This is the first half of the string";
  char dest1[200] = "This is the first half of the string";
  size_t n = strlen(src) - 10; // don't concat all of n (add a null terintator)

  char *retVal = my_strncat(dest, src, n);
  char *correctVal = strncat(dest1, src, n);

  // Checking if dest pointer didn't change
  ck_assert_ptr_eq(retVal, dest);

  // Checking if strncmp returns 0
  ck_assert_int_eq(strncmp(retVal, correctVal, 200), 0);
}
END_TEST

START_TEST(test_my_strncat_with_empty_string_first) {
  char my_str[1000];
  randStringGenerator(my_str,
                      sizeof(my_str) - 500); // fill buffer with 500 rando chars
  char empty[1000] = "\0";

  char *retVal = my_strncat(empty, my_str, 400);

  // Checking if dest pointer didn't change
  ck_assert_ptr_eq(retVal, empty);

  // Checking if the empty is the as my_str after concat
  ck_assert_int_eq(strncmp(empty, my_str, 400), 0);
}
END_TEST

START_TEST(test_my_strncat_with_empty_string_second) {
  char my_str[1000];
  randStringGenerator(my_str,
                      sizeof(my_str) - 500); // fill buffer with 500 rando chars
  char empty[100] = "\0";
  size_t n = 100; // attempt to concat empty buffer

  char *retVal = my_strncat(my_str, empty, n);

  // Checking if dest pointer didn't change
  ck_assert_ptr_eq(retVal, my_str);

  // Checking if concat string = original string
  ck_assert_str_eq(retVal, my_str);
}
END_TEST

/******************************************************************************/
/**************************** my_memset tests ********************************/
/******************************************************************************/
START_TEST(test_my_memset_basic) {
  char my_str[100] = "abcdefghij";
  char str[100] = "abcdefghij";
  char *backup = my_str;
  my_memset(my_str + 3, '*', 2);
  memset(str + 3, '*', 2);
  // Checking if my_str pointer didn't change
  ck_assert_ptr_eq(my_str, backup);

  // Checking if strncmp returns 0
  ck_assert_int_eq(strcmp(str, my_str), 0);
}
END_TEST

START_TEST(test_my_memset_random_n) {
  char my_str[200];
  char str[200];
  randStringGenerator(my_str, sizeof(my_str));
  randStringGenerator(str, sizeof(str));
  srand(time(0));
  size_t num = rand() % 198; // n < string buffer size
  if (num < 50) {
    num += 100;
  }
  char *backup = my_str;
  my_memset(my_str, 's', num);
  my_memset(my_str + num, '\0', 1);
  memset(str, 's', num);
  memset(str + num, '\0', 1);
  // Checking if my_str pointer didn't change
  ck_assert_ptr_eq(my_str, backup);

  // Checking if strncmp returns 0
  ck_assert_int_eq(strcmp(str, my_str), 0);
}
END_TEST

START_TEST(test_my_memset_replace_char) {
  char my_str[100];
  randStringGenerator(my_str, sizeof(my_str));
  srand(time(0));
  size_t num = rand() % 99; // num < string buffer size
  char *backup = my_str;
  my_memset(my_str + num, '*', 1);
  char replacedChar = my_str[num];
  // Checking if my_str pointer didn't change
  ck_assert_ptr_eq(my_str, backup);

  // Checking if the char was correctly set
  ck_assert_int_eq(replacedChar, '*');
}
END_TEST

START_TEST(test_my_memset_replace_all) {
  char arr[100];
  char arr1[100];
  randStringGenerator(arr, 100);  // random string 1
  randStringGenerator(arr1, 100); // random string 2

  // replace all string chars with 0
  my_memset(arr, 0, 100);
  memset(arr1, 0, 100);
  // check buffers are equal
  ck_assert_str_eq(arr, arr1);
}
END_TEST

/******************************************************************************/
/******************** is_palindrome_ignore_case tests *************************/
/******************************************************************************/
START_TEST(test_is_palindrome_ignore_case_basic) {
    // Test cases
    const char *test_cases[] = {
        "A man a plan a canal Panama", "Able was I ere I saw Elba",
        "Madam Arora teaches malayalam", "Was it a car or a cat I saw",
        "Madam in Eden Im Adam", "racecar", 
        "tacocat", NULL};

    char test_desc[400];

    // Iterate over test cases
    for (int i = 0; test_cases[i] != NULL; i++) {
        // Call your function
        int ground_truth = s_is_palindrome_ignore_case(test_cases[i]);

        // Call student's function
        int student_result = is_palindrome_ignore_case(test_cases[i]);

        // Compare results
        sprintf(test_desc, "is_palindrome_ignore_case(\"%s\")", test_cases[i]);
        ck_assert_msg(ground_truth == student_result, EXPECTED_RETVAL_MSG, test_desc, ground_truth, student_result);
    }
}
END_TEST

/** Random Palindrome Tests
* Randomly generated palindromes
*/
START_TEST(test_is_palindrome_ignore_case_random_true) {
    char test_str[100];
    char student_str[100];
    srand(time(0));
    int TEST_COUNT = 10;

    char test_desc[400];

    for (int i = 0; i < TEST_COUNT; i++) {
        // Generate random palindrome
        generate_random_palindrome(test_str, 100);
        strcpy(student_str, test_str);

        // Call your function
        int ground_truth = s_is_palindrome_ignore_case(test_str);

        // Call student's function
        int student_result = is_palindrome_ignore_case(student_str);

        // Compare results
        sprintf(test_desc, "is_palindrome_ignore_case(\"%s\")", test_str);
        ck_assert_msg(ground_truth == student_result, EXPECTED_RETVAL_MSG, test_desc, ground_truth, student_result);
    }
}
END_TEST

/*** Empty Palindrome Tests
*/
START_TEST(test_is_palindrome_ignore_case_empty_true) {
    char test_str[] = "";
    char student_str[] = "";

    // Call your function
    int ground_truth = s_is_palindrome_ignore_case(test_str);

    // Call student's function
    int student_result = is_palindrome_ignore_case(student_str);

    // Compare results
    ck_assert_msg(ground_truth == student_result,
                  EXPECTED_RETVAL_MSG, "is_palindrome_ignore_case(\"\")", ground_truth,
                  student_result);
}
END_TEST

/*** Random Non-Palindrome Tests
* Randomly generated non-palindromes
*/
START_TEST(test_is_palindrome_ignore_case_random_false) {
    char test_str[100];
    char student_str[100];
    srand(time(0));
    int TEST_COUNT = 10;

    char test_desc[400];

    for (int i = 0; i < TEST_COUNT; i++) {
        // Generate random non-palindrome
        generate_random_string(test_str, 100);
        strcpy(student_str, test_str);

        // Call your function
        int ground_truth = s_is_palindrome_ignore_case(test_str);

        // Call student's function
        int student_result = is_palindrome_ignore_case(student_str);

        // Compare results
        sprintf(test_desc, "is_palindrome_ignore_case(\"%s\")", test_str);
        ck_assert_msg(ground_truth == student_result, EXPECTED_RETVAL_MSG, test_desc, ground_truth, student_result);
    }
}
END_TEST
/******************************************************************************/
/****************************** s_deduplicate_str tests ***********************/
/******************************************************************************/

START_TEST(test_s_deduplicate_str_basic) {
    char ground_truth[] = "aabbcc";
    char student_str[] = "aabbcc";

    s_deduplicate_str(ground_truth);
    deduplicate_str(student_str);
    ck_assert_msg(strcmp(ground_truth, student_str) == 0, EXPECTED_STR_MSG, "deduplicate_str(\"aabbcc\")", ground_truth, student_str);
}
END_TEST

START_TEST(test_s_deduplicate_str_random_duplicates) {
    char test_str[100];
    char ground_truth[100];
    char student_str[100];
    int TEST_COUNT = 10;

    char test_desc[400];

    srand(time(0));

    for (int i = 0; i < TEST_COUNT; i++) {
        // Generate duplicated string
        generate_duplicated_string(test_str, 100);
        strcpy(student_str, test_str);
        strcpy(ground_truth, test_str);

        // Call your function
        s_deduplicate_str(ground_truth);

        // Call student's function
        deduplicate_str(student_str);

        // Compare results
        sprintf(test_desc, "deduplicate_str(\"%s\")", test_str);
        ck_assert_msg(strcmp(ground_truth, student_str) == 0, EXPECTED_STR_MSG, test_desc, ground_truth, student_str);
    }
}
END_TEST

START_TEST(test_s_deduplicate_str_empty) {
    char ground_truth[] = "";
    char student_str[] = "";

    s_deduplicate_str(ground_truth);
    deduplicate_str(student_str);

    ck_assert_msg(strcmp(ground_truth, student_str) == 0, EXPECTED_STR_MSG, "deduplicate_str(\"\")", ground_truth, student_str);
}
END_TEST

START_TEST(test_s_deduplicate_str_random_string) {
    char test_str[100];
    char ground_truth[100];
    char student_str[100];
    int TEST_COUNT = 10;

    char test_desc[400];

    srand(time(0));

    for (int i = 0; i < TEST_COUNT; i++) {
        // Generate random string
        generate_random_string(test_str, 100);
        strcpy(student_str, test_str);
        strcpy(ground_truth, test_str);

        // Call your function
        s_deduplicate_str(ground_truth);

        // Call student's function
        deduplicate_str(student_str);

        // Compare results
        sprintf(test_desc, "deduplicate_str(\"%s\")", test_str);
        ck_assert_msg(strcmp(ground_truth, student_str) == 0, EXPECTED_STR_MSG, test_desc, ground_truth, student_str);
    }
}
END_TEST
/******************************************************************************/
/********************************* s_caesar_shift ******************************/
/******************************************************************************/

START_TEST(test_s_caesar_shift_basic) {
    char test_desc[100];

    for (int i = 0; i < 10; i++)
    {
      char ground_truth[] = "abc";
      char student_str[] = "abc";
      s_caesar_shift(ground_truth, i);
      caesar_shift(student_str, i);
      sprintf(test_desc, "caesar_shift(\"abc\", %d)", i);
      ck_assert_msg(strcmp(ground_truth, student_str) == 0, EXPECTED_STR_MSG, test_desc, ground_truth, student_str);
    }
}
END_TEST

START_TEST(test_s_caesar_shift_random) {
    char test_str[100];
    char ground_truth[100];
    char student_str[100];
    int TEST_COUNT = 10;

    char test_desc[400];

    srand(time(0));

    int shift;
    for (int i = 0; i < TEST_COUNT; i++) {
        // Generate random string
        generate_random_string(test_str, 100);
        strcpy(student_str, test_str);
        strcpy(ground_truth, test_str);

        // Don't want to test on RAND_MAX too high with fear of overflow
        shift = rand() % (52 + 1);
        // Call your function
        s_caesar_shift(ground_truth, shift);

        // Call student's function
        caesar_shift(student_str, shift);

        // Compare results
        sprintf(test_desc, "caesar_shift(\"%s\", %d)", test_str, shift);
        ck_assert_msg(strcmp(ground_truth, student_str) == 0, EXPECTED_STR_MSG, test_desc, ground_truth, student_str);
    }
}
END_TEST

START_TEST(test_s_caesar_shift_empty) {
    char test_desc[100];

    for (int i = 0; i < 10; i++)
    {
      char ground_truth[] = "";
      char student_str[] = "";
      s_caesar_shift(ground_truth, 1);
      caesar_shift(student_str, 1);
      sprintf(test_desc, "caesar_shift(\"\", %d)", i);
      ck_assert_msg(strcmp(ground_truth, student_str) == 0, EXPECTED_STR_MSG, test_desc, ground_truth, student_str);
    }
}
END_TEST

/******************************************************************************/
/********************************* s_swap_strings ******************************/
/******************************************************************************/

START_TEST(test_s_swap_strings_basic) {
    char *str1 = "abc";
    char *str2 = "def";
    char *student_str1 = "abc";
    char *student_str2 = "def";

    s_swap_strings(&str1, &str2);
    swap_strings(&student_str1, &student_str2);

    char *test_desc = "swap_strings(&\"abc\", &\"def\")";

    ck_assert_msg(strcmp(str1, student_str1) == 0, "%s - FAILED test case: str1 - got \"%s\", expected \"%s\"\n", test_desc, student_str1, str1);
    ck_assert_msg(strcmp(str2, student_str2) == 0, "%s - FAILED test case: str2 - got \"%s\", expected \"%s\"\n", test_desc, student_str2, str2);
}
END_TEST

START_TEST(test_s_swap_strings_random) {
    char str1[50];
    char str2[50];
    char ground_truth1[50];
    char ground_truth2[50];
    char student_str1[50];
    char student_str2[50];
    int TEST_COUNT = 10;

    char test_desc[400];

    for (int i = 0; i < TEST_COUNT; i++) {
        // Generate random string
        generate_random_string(str1, 50);
        generate_random_string(str2, 50);
        strcpy(ground_truth1, str1);
        strcpy(ground_truth2, str2);
        strcpy(student_str1, str1);
        strcpy(student_str2, str2);
        
        char *p_ground_truth1 = &ground_truth1[0];
        char *p_ground_truth2 = &ground_truth2[0];
        char *p_student_str1 = &student_str1[0];
        char *p_student_str2 = &student_str2[0];

        // Call your function
        // s_swap_strings(&p_ground_truth1, &p_ground_truth2);
        s_swap_strings(&p_ground_truth1, &p_ground_truth2);

        // Call student's function
        swap_strings(&p_student_str1, &p_student_str2);

        sprintf(test_desc, "swap_strings(&\"%s\", &\"%s\")", str1, str2);

        // Compare results
        ck_assert_msg(strcmp(p_ground_truth1, p_student_str1) == 0, "%s - FAILED test case: str1 - got \"%s\", expected \"%s\"\n", test_desc, student_str1, ground_truth1);
        ck_assert_msg(strcmp(p_ground_truth2, p_student_str2) == 0, "%s - FAILED test case: str2 - got \"%s\", expected \"%s\"\n", test_desc, student_str2, ground_truth2);
    }
}
END_TEST

START_TEST(test_s_swap_strings_empty) {
    char *str1 = "";
    char *str2 = "";
    char *student_str1 = "";
    char *student_str2 = "";

    s_swap_strings(&str1, &str2);
    swap_strings(&student_str1, &student_str2);

    char *test_desc = "swap_strings(&\"\", &\"\")";

    ck_assert_msg(strcmp(str1, student_str1) == 0, "%s - FAILED test case: str1 - got \"%s\", expected \"%s\"\n", test_desc, student_str1, str1);
    ck_assert_msg(strcmp(str2, student_str2) == 0, "%s - FAILED test case: str2 - got \"%s\", expected \"%s\"\n", test_desc, student_str2, str2);

}
END_TEST

/**
 * @brief Automatically ran before every test.
 */
static void setup(void) {}

/**
 * @brief Helper function for creating random strings. It will null-terminate
 * like a champ.
 */
// Thanks bro -->
// https://stackoverflow.com/questions/15767691/whats-the-c-library-function-to-generate-random-string/15768317
static void randStringGenerator(char *buffer, int length) {
  // C weird syntax once again
  char charset[] = "0123456789"
                   "abcdefghijklmnopqrstuvwxyz"
                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  // So we don't have to keep adding space for the null terminator
  length--;

  while (length-- > 0) {
    // The magic of double, this guy is a flexer
    size_t index = ((double)rand() / RAND_MAX) * (sizeof(charset) - 1);
    *buffer++ = charset[index];
  }

  *buffer = '\0';
}

Suite *my_string_suite(void) {
  Suite *s = suite_create("my_string_suite");

  tcase_add(s, setup, NULL, test_my_strlen_1);
  tcase_add(s, setup, NULL, test_my_strlen_2);
  tcase_add(s, setup, NULL, test_my_strlen_3);
  tcase_add(s, setup, NULL, test_my_strlen_4);
  tcase_add(s, setup, NULL, test_my_strlen_5);

  tcase_add(s, setup, NULL, test_my_strncmp_equal);
  tcase_add(s, setup, NULL,
            test_my_strncmp_null_terminator_in_middle_almost_same);
  tcase_add(s, setup, NULL,
            test_my_strncmp_null_terminator_in_middle_different);
  tcase_add(s, setup, NULL, test_my_strncmp_random);
  tcase_add(s, setup, NULL, test_my_strncmp_letters_shuffled);
  tcase_add(s, setup, NULL,
            test_my_strncmp_first_half_same_end_different_large_n);
  tcase_add(s, setup, NULL,
            test_my_strncmp_first_half_same_end_different_small_n);
  tcase_add(s, setup, NULL, test_my_strncmp_almost_equal);

  tcase_add(s, setup, NULL, test_my_strncpy_basic);
  tcase_add(s, setup, NULL, test_my_strncpy_destination_larger);
  tcase_add(s, setup, NULL, test_my_strncpy_random_basic_256);
  tcase_add(s, setup, NULL, test_my_strncpy_null_terminator_in_middle);
  tcase_add(s, setup, NULL, test_my_strncpy_overwrite);
  tcase_add(s, setup, NULL, test_my_strncpy_adv);

  tcase_add(s, setup, NULL, test_my_strncat_basic);
  tcase_add(s, setup, NULL, test_my_strncat_random);
  tcase_add(s, setup, NULL, test_my_strncat_null_terminator);
  tcase_add(s, setup, NULL, test_my_strncat_with_empty_string_first);
  tcase_add(s, setup, NULL, test_my_strncat_with_empty_string_second);

  tcase_add(s, setup, NULL, test_my_memset_basic);
  tcase_add(s, setup, NULL, test_my_memset_random_n);
  tcase_add(s, setup, NULL, test_my_memset_replace_char);
  tcase_add(s, setup, NULL, test_my_memset_replace_all);

  tcase_add(s, setup, NULL, test_is_palindrome_ignore_case_basic);
  tcase_add(s, setup, NULL, test_is_palindrome_ignore_case_random_true);
  tcase_add(s, setup, NULL, test_is_palindrome_ignore_case_empty_true);
  tcase_add(s, setup, NULL, test_is_palindrome_ignore_case_random_false);

  tcase_add(s, setup, NULL, test_s_caesar_shift_basic);
  tcase_add(s, setup, NULL, test_s_caesar_shift_random);
  tcase_add(s, setup, NULL, test_s_caesar_shift_empty);

  tcase_add(s, setup, NULL, test_s_deduplicate_str_basic);
  tcase_add(s, setup, NULL, test_s_deduplicate_str_random_duplicates);
  tcase_add(s, setup, NULL, test_s_deduplicate_str_empty);
  tcase_add(s, setup, NULL, test_s_deduplicate_str_random_string);

  tcase_add(s, setup, NULL, test_s_swap_strings_basic);
  tcase_add(s, setup, NULL, test_s_swap_strings_random);
  tcase_add(s, setup, NULL, test_s_swap_strings_empty);
  return s;
}

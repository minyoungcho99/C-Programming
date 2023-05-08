#include <stddef.h>
#include "my_string.h"
/**
 * Calculates the length of a string.
 * @param s a constant string
 * @return size_t the number of characters in the passed in string
 */
size_t my_strlen(const char *s) {
     size_t length = 0;

    while (*s != '\0') {
        ++s;
        ++length;
    }

    return length;
}

/**
 * Compares two strings.
 * @param s1 First string to be compared
 * @param s2 Second string to be compared
 * @param n First (at most) n bytes to be compared
 * @return int "less than, equal to, or greater than zero if s1 (or the first n
 * bytes thereof) is found, respectively, to be less than, to match, or be
 * greater than s2"
 */
int my_strncmp(const char *s1, const char *s2, size_t n) {
    while (n-- > 0) {
        if (*s1 != *s2) {
            return *s1 - *s2;
        }
        if (*s1 == '\0') {
            break;
        }
        s1++;
        s2++;
    }
    return 0;
}

/**
 * Copies a string.
 * @param dest The destination buffer
 * @param src The source to copy from
 * @param n maximum number of bytes to copy
 * @return char* a pointer same as dest
 */
char *my_strncpy(char *dest, const char *src, size_t n) {
    char *pointer = dest;
    while (n-- > 0) {
        if (*src == '\0') {
            *dest++ = '\0';
        } else {
            *dest++ = *src++;
        }
    }
    return pointer;
}

/**
 * Concatenates two strings and stores the result in the destination string.
 * @param dest The destination string
 * @param src The source string
 * @param n The maximum number of bytes from src to concatenate
 * @return char* a pointer same as dest
 */
char *my_strncat(char *dest, const char *src, size_t n) {
    char *pointer = dest;

    while (*dest != '\0') {
        ++dest;
    }

    while (n-- > 0 && *src != '\0') {
        *dest++ = *src++;
    }

    *dest = '\0';
    return pointer; 
}

/**
 * Copies the character c into the first n bytes of memory starting at *str.
 * @param str The pointer to the block of memory to fill
 * @param c The character to fill in memory
 * @param n The number of bytes of memory to fill
 * @return char* a pointer same as str
 */
void *my_memset(void *str, int c, size_t n) {
    unsigned char *pointer = str;
    unsigned char v = (unsigned char) c;
    while (n-- > 0) {
        *pointer++ = v;
    }
    
    return str;
}

/**
 * Finds the first instance of c in str and removes it from str in place.
 * @param str The pointer to the string
 * @param c The character we are looking to delete
 */
void remove_first_instance(char *str, char c) {
    char *pointer = str;
    while (*pointer && (*pointer != c)) {
        ++pointer;
    }
    if (*pointer == c) {
        char *a = pointer + 1;
        while (*a) {
            *pointer++ = *a++;
        }
        *pointer = '\0';
    }
}

/**
 * Finds the first instance of c in str and replaces it with the contents of replaceStr.
 * @param str The pointer to the string
 * @param c The character we are looking to delete
 * @param replaceStr The pointer to the string we are replacing c with
 */
void replace_character_with_string(char *str, char c, char *replaceStr) {
     char *pointer = str;

    if (*replaceStr == '\0') {
        do {
            if (*pointer == c) {
                char *a = pointer + 1;
                while (*a != '\0') {
                    *(a - 1) = *a;
                    a = a + 1;
                }
                *(a - 1) = '\0';
            } else {
                pointer++;
            }
        } while (*pointer != '\0');
        return;
    }

    while (*pointer != '\0') {
        if (*pointer == c) {
            int len = my_strlen(str);
            int replace = my_strlen(replaceStr);
            char *a = len + replace + str - 1;

            while (*a != '\0') {
                a++;
            }

            while (a >= pointer) {
                *(a + replace - 1) = *a;
                a--;
            }

            a = replaceStr;

            while (*a != '\0') {
                *pointer = *a;
                a++;
                pointer++;
            }

            *(str + len + replace - 1) = '\0';
            return;
        } else {
            pointer++;
        }
    }   
}

/**
 * Removes the first character of str (ie. str[0]).
 * @param str A pointer to a pointer of the string
 */
void remove_first_character(char **str) {
    *str += 1;
    return;
}
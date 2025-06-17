#include "strings.h"

void *memset(void *s, int c, size_t n)
{
    char *char_s = (char *)s;
    for (size_t i = 0; i < n; i++)
    {
        char_s[i] = (unsigned char) c;
    }
    return s;
}

void *memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *char_dst = (unsigned char *)dst;
    unsigned char *char_src = (unsigned char *)src;
    for (size_t i = 0; i < n; i++)
    {
        char_dst[i] = char_src[i];
    }
    return dst;
}

size_t strlen(const char *s)
{
    /* Implementation a gift to you from lab3 */
    int n = 0;
    while (s[n] != '\0') {
        n++;
    }
    return n;
}

int strcmp(const char *s1, const char *s2)
{
    int n = 0;
    while (1) {
        if (s1[n] == '\0' || s2[n] == '\0') {
            if (s1[n] == '\0' && s2[n] != '\0') {
                return -1;
            }
            if (s1[n] != '\0' && s2[n] == '\0') {
                return 1;
            }
            break;
        }
        if (s1[n] != s2[n]) 
        {
            if (s1[n] > s2[n])
            {
                return 1;
            } else {
                return -1;
            }
        }
        n++;
    }
    return 0;
}

size_t strlcat(char *dst, const char *src, size_t maxsize)
{
    /* TODO: Your code here */
    return 0;
}

unsigned int strtonum(const char *str, const char **endptr)
{
    /* TODO: Your code here */
    return 0;
}

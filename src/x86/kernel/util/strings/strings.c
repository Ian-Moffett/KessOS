#include "strings.h"


unsigned int strlen(const char* const STR) {
    unsigned int len = 0;
    while (STR[len++]);
    return len;
}

unsigned char* strncpy(unsigned char* dst, const unsigned char* src, const unsigned char len) {
    for (unsigned char i = 0; src[i] && i < len; i++)
        dst[i] = src[i];

    return dst;
}


unsigned char strcmp(const char* str1, const char* str2) {
    if (strlen(str1) != strlen(str2)) {
        return 0;
    }

    for (int i = 0; i < strlen(str1); ++i) {
        if (str1[i] != *str2) {
            return 0;
        }

        ++str2;
    }

    return 1;
}

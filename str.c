#include <stdint.h>
#include "str.h"

void str_hex(char *s, void *d, size_t len) {
    uint8_t *c = d + len - 1;
    for (size_t i = len; i > 0; i--) {
        if ((*c >> 4) < 10)
            *s++ = (*c >> 4) + '0';
        else
            *s++ = (*c >> 4) + ('a' - 10);

        if ((*c & 0xf) < 10)
            *s++ = (*c & 0xf) + '0';
        else
            *s++ = (*c & 0xf) + ('a' - 10);

        c--;
    }

    *s = '\0';
}

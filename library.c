#include "library.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fastache_compile_buf(const char *buf, unsigned int len, fastache_tmpl *out) {

}

int fastache_compile_file(const char *path, fastache_tmpl *out) {
    int ret;
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        return errno;
    }

    char *buf = malloc(1024);
    unsigned int len = 1024, pos = 0;
    while (!feof(f)) {
        if (pos == len) {
            len *= 2;
            buf = realloc(buf, len);
        }

        pos += fread(buf, 1, len - pos, f);
        if (ferror(f)) {
            ret = errno;
            goto out;
        }
    }

    ret = fastache_compile_buf(buf, pos, out);

out:
    fclose(f);
    free(buf);
    return ret;
}



void hello(void) {
    printf("Hello, World!\n");
}

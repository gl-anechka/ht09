#define BASIS 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dlfcn.h>
#include "random_source.h"

int
main(int argc, char *argv[])
{
    if (argc != 4) {
        return 1;
    }

    void *handle = dlopen(NULL, RTLD_LAZY);
    if (handle == NULL) {
        return 1;
    }

    char *eptr = NULL;
    errno = 0;
    long n = strtol(argv[2], &eptr, BASIS);
    if (errno || *eptr || eptr == argv[2] || (int) n != n) {
        return 1;
    }

    RandomSource *generator;
    void *sym_func;
    RandomSource* (*func) (const char *);

    if (!strcmp(argv[1], "mt")) {
        sym_func = dlsym(handle, "random_mt_factory");
        if (sym_func == NULL) {
            dlclose(handle);
            return 1;
        }

        func = (RandomSource* (*) (const char *)) sym_func;

        generator = func(argv[3]);
        for (int i = 0; i < n; i++) {
            printf("%.10g\n", generator->ops->next(generator));
        }
        generator->ops->destroy(generator);
    } else if (!strcmp(argv[1], "linear")) {
        sym_func = dlsym(handle, "random_linear_factory");
        if (sym_func == NULL) {
            dlclose(handle);
            return 1;
        }

        func = (RandomSource* (*) (const char *)) sym_func;

        generator = func(argv[3]);
        for (int i = 0; i < n; i++) {
            printf("%.10g\n", generator->ops->next(generator));
        }
        generator->ops->destroy(generator);
    }

    if (dlclose(handle) < 0) {
        return 1;
    }
    return 0;
}

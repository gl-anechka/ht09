#define MULTIPLIER 1103515245
#define INCREMENT 12345
#define MODULE 2147483648

#define BASIS 10
#define MASK 0x7FFFFFFF

#include <stdlib.h>
#include <errno.h>
#include "random_source.h"

/* Функция освобождает ресурсы, используемые в объекте src, включая сам объект.
 * Всегда возвращает NULL. */
RandomSource *linear_destroy(RandomSource *src)
{
    free(src->ops);
    free(src);
    return NULL;
}

/* Функция возвращает следующее случайное значение.*/
double linear_next(RandomSource *src)
{
    src->number = (MULTIPLIER * src->number + INCREMENT) % MODULE;
    return ((double) src->number) / MODULE;
}

/* Фабрика объектов. */
RandomSource *random_linear_factory(const char *params)
{
    //преобразование строки
    char *eptr = NULL;
    errno = 0;
    unsigned long seed = (unsigned long) strtol(params, &eptr, BASIS);
    if (errno || *eptr || eptr == params || (unsigned) seed != seed) {
        return NULL;
    }

    //учет только младших 31 бит
    seed &= MASK;

    //инициализация генератора
    RandomSource *generator = calloc(1, sizeof(*generator));
    if (generator == NULL) {
        return NULL;
    }
    generator->number = seed;
    generator->ops = calloc(1, sizeof(*generator->ops));
    if (generator->ops == NULL) {
        return NULL;
    }
    generator->ops->destroy = linear_destroy;
    generator->ops->next = linear_next;
    return generator;
}

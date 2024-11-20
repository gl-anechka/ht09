#define BASIS 10

#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include "random_source.h"
#include "mtwister.h"

struct
{
    RandomSource *src;
    MTRand rand;
} mt_rand;

/* Функция освобождает ресурсы, используемые в объекте src, включая сам объект.
 * Всегда возвращает NULL. */
RandomSource *
mt_destroy(RandomSource *src)
{
    free(src->ops);
    free(src);
    return NULL;
}

/* Функция возвращает следующее случайное значение.*/
double
mt_next(RandomSource *src)
{
    return genRand(&mt_rand.rand);
}

/* Фабрика объектов. */
RandomSource *
random_mt_factory(const char *params)
{
    /*преобразование строки*/
    char *eptr = NULL;
    errno = 0;
    unsigned long seed = (unsigned long) strtol(params, &eptr, BASIS);
    if (errno || *eptr || eptr == params || (unsigned) seed != seed) {
        return NULL;
    }

    /*создание генератора*/
    mt_rand.rand = seedRand((uint32_t) seed);

    /*инициализация генератора*/
    mt_rand.src = calloc(1, sizeof(*mt_rand.src));
    if (mt_rand.src == NULL) {
        return NULL;
    }
    mt_rand.src->number = seed;
    mt_rand.src->ops = calloc(1, sizeof(*mt_rand.src->ops));
    if (mt_rand.src->ops == NULL) {
        return NULL;
    }
    mt_rand.src->ops->destroy = mt_destroy;
    mt_rand.src->ops->next = mt_next;
    return mt_rand.src;
}

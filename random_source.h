#ifndef RANDOMSOURSE_H
#define RANDOMSOURSE_H

typedef struct RandomSource RandomSource;
typedef struct RandomSourceOperations RandomSourceOperations;

/* Тип, который будет реализовывать генерацию равномерно распределенных
 * случайных чисел на отрезке [0;1). */
struct RandomSource
{
    unsigned number;
    RandomSourceOperations *ops;
};

/* Тип для хранения указателей на функции работы с RandomSource.
 * Содержит поля destroy и next, которые являются указателями на функции. */
struct RandomSourceOperations
{
    RandomSource* (*destroy)(RandomSource *src);
    double (*next)(RandomSource *src);
};

/* Фабрика объектов для создания объектов типа RandomSource для линейного генератора. */
RandomSource *random_linear_factory(const char *params);

/* Фабрика объектов для создания объектов типа RandomSource для Mersenne Twister. */
RandomSource *random_mt_factory(const char *params);

#endif

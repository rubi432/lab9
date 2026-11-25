#ifndef MATRIXFUNC_H
#define MATRIXFUNC_H

#include <stddef.h> /* для size_t */

/* Вариант 7 (последняя цифра зачетки): функции №6, №11, №30.

   Все функции получают указатель на первый элемент матрицы (matptr)
   и ее размеры rows x cols. Элемент с индексами (i, j) лежит по адресу
   *(matptr + i * cols + j), потому что матрица хранится в памяти
   строка за строкой. */

/* Функция №6: среднее арифметическое всех элементов матрицы. */
double average_matrix(double *matptr, size_t rows, size_t cols);

/* Функция №11: максимальный элемент каждой строки.
   Результат для строки i записывается в result_array[i],
   поэтому массив результатов должен быть не короче rows. */
void max_in_rows(double *matptr, size_t rows, size_t cols,
                 double *result_array);

/* Функция №30: разность между максимальным и минимальным элементами. */
double diff_max_min(double *matptr, size_t rows, size_t cols);

#endif

#include "matrixfunc.h"

/* Здесь нельзя писать matptr[i][j] или matptr[k]:
   доступ к элементам идет только через *(matptr + i * cols + j). */

/* Функция №6: среднее арифметическое всех элементов матрицы. */
double average_matrix(double *matptr, size_t rows, size_t cols) {
    size_t i, j;
    double sum = 0.0;

    if (rows == 0 || cols == 0) {
        return 0.0;
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            sum += *(matptr + i * cols + j);
        }
    }

    return sum / (double)(rows * cols);
}

/* Функция №11: максимальный элемент каждой строки.
   Для строки i ответ пишем в result_array[i]. */
void max_in_rows(double *matptr, size_t rows, size_t cols,
                 double *result_array) {
    size_t i, j;

    if (rows == 0 || cols == 0) {
        return;
    }

    for (i = 0; i < rows; i++) {
        /* Первый элемент строки - временный максимум. */
        double max_value = *(matptr + i * cols + 0);

        for (j = 1; j < cols; j++) {
            double current = *(matptr + i * cols + j);

            if (current > max_value) {
                max_value = current;
            }
        }

        *(result_array + i) = max_value;
    }
}

/* Функция №30: разность между максимальным и минимальным элементами. */
double diff_max_min(double *matptr, size_t rows, size_t cols) {
    size_t i, j;
    double max_value;
    double min_value;

    if (rows == 0 || cols == 0) {
        return 0.0;
    }

    /* Сначала и максимумом, и минимумом считаем первый элемент. */
    max_value = *matptr;
    min_value = *matptr;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            double current = *(matptr + i * cols + j);

            if (current > max_value) {
                max_value = current;
            }
            if (current < min_value) {
                min_value = current;
            }
        }
    }

    return max_value - min_value;
}

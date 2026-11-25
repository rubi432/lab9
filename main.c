/* Практическая работа №9. Многомерные массивы.
   Вариант: последняя цифра зачетки 7 - функции №6, №11, №30.

   В main.c находится только служебный блок: меню, задание размеров,
   ввод и просмотр матрицы, вызов библиотечных функций и печать ответов.
   Вся обработка матрицы вынесена в matrixfunc.c. */

#include <stdio.h>
#include <stdlib.h> /* strtod, strtol */
#include "matrixfunc.h"

#define MAX_ROWS 10
#define MAX_COLS 10

/* Матрица хранится в памяти как одна длинная строка: сначала идут
   элементы строки 0, сразу за ними - строки 1 и так далее.
   Поэтому элемент (i, j) - это mat[i * cols + j], и его адрес
   считается по формуле из методички: *(matptr + i * cols + j).
   Именно поэтому здесь одномерный массив, а не mat[10][10]. */
static double mat[MAX_ROWS * MAX_COLS];

/* Прочитать одно слово (до пробела или перевода строки).
   Возвращает 1 при успехе и 0, если ввод закончился (EOF).
   Буфер word должен быть не короче 32 байт. */
static int read_word(char *word) {
    return scanf("%31s", word) == 1;
}

/* Прочитать число с плавающей точкой.
   1 - число прочитано, 0 - введено не число, -1 - конец ввода. */
static int read_double(double *value) {
    char word[32];
    char *end;

    if (!read_word(word)) {
        return -1;
    }

    *value = strtod(word, &end);
    if (end == word || *end != '\0') {
        return 0;
    }

    return 1;
}

/* Проверить, что в строке нет ничего, кроме пробелов. */
static int line_is_blank(const char *line) {
    while (*line == ' ' || *line == '\t' || *line == '\r' || *line == '\n') {
        line++;
    }
    return *line == '\0';
}

/* Прочитать размеры матрицы (два числа в одной строке).
   1 - успех, 0 - ошибка, -1 - конец ввода. */
static int read_size_line(size_t *rows, size_t *cols) {
    char line[128];
    long r, c;

    for (;;) {
        if (fgets(line, sizeof line, stdin) == NULL) {
            return -1;
        }
        if (line_is_blank(line)) {
            continue; /* пустую строку просто пропускаем */
        }
        if (sscanf(line, "%ld %ld", &r, &c) != 2) {
            return 0; /* ввели не два числа */
        }
        if (r < 1 || c < 1 || r > MAX_ROWS || c > MAX_COLS) {
            return 0; /* числа не в том диапазоне */
        }

        *rows = (size_t)r;
        *cols = (size_t)c;
        return 1;
    }
}

static void print_menu(void) {
    printf("\n--- МЕНЮ ---\n");
    printf("a. Задать размер матрицы (строки, столбцы)\n");
    printf("b. Заполнить матрицу\n");
    printf("c. Представление матрицы (значения, адреса элементов)\n");
    printf("d. [Функция 1] > average_matrix: среднее арифметическое\n");
    printf("e. [Функция 2] > max_in_rows: максимум в каждой строке\n");
    printf("f. [Функция 3] > diff_max_min: разность максимума и минимума\n");
    printf("g. Выход\n");
    printf("Выберите пункт: ");
}

/* Заполнить матрицу rows x cols.
   1 - все числа введены, 0 - конец ввода. */
static int fill_matrix(size_t rows, size_t cols) {
    size_t i, j;

    printf("Введите элементы матрицы, всего: %zu\n", rows * cols);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            int result;

            /* Если ввели не число, просим это же значение еще раз. */
            do {
                result = read_double(&mat[i * cols + j]);

                if (result == -1) {
                    return 0;
                }
                if (result == 0) {
                    printf("Это не число, повторите: ");
                }
            } while (result != 1);
        }
    }

    return 1;
}

/* Показать значения и адреса элементов матрицы. */
static void show_matrix(size_t rows, size_t cols) {
    size_t i, j;

    printf("Матрица (значение | адрес):\n");

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%8.2f | %p  ", mat[i * cols + j],
                   (void *)&mat[i * cols + j]);
        }
        printf("\n");
    }
}

int main(void) {
    size_t rows = 0; /* пока размер не задан, матрица пустая */
    size_t cols = 0;
    int running = 1;

    while (running) {
        char word[32];
        char command;

        print_menu();

        if (!read_word(word)) {
            printf("\nКонец ввода. Завершение работы.\n");
            break;
        }
        command = word[0];

        if (command == 'a') {
            size_t new_rows = 0;
            size_t new_cols = 0;
            int result;

            printf("Введите количество строк и столбцов (каждое от 1 до %d): ",
                   MAX_ROWS);

            result = read_size_line(&new_rows, &new_cols);

            if (result == -1) {
                printf("\nКонец ввода. Завершение работы.\n");
                running = 0;
            } else if (result == 0) {
                printf("Ошибка: нужно два целых числа от 1 до %d.\n",
                       MAX_ROWS);
            } else {
                rows = new_rows;
                cols = new_cols;
                printf("Размер матрицы: %zu x %zu\n", rows, cols);
            }
        }
        else if (command == 'b') {
            if (rows == 0 || cols == 0) {
                printf("Сначала задайте размер матрицы (пункт a).\n");
                continue;
            }

            if (!fill_matrix(rows, cols)) {
                printf("\nКонец ввода. Завершение работы.\n");
                running = 0;
            } else {
                printf("Матрица заполнена.\n");
            }
        }
        else if (command == 'c') {
            if (rows == 0 || cols == 0) {
                printf("Матрица пуста!\n");
                continue;
            }

            show_matrix(rows, cols);
        }
        else if (command == 'd') {
            if (rows == 0 || cols == 0) {
                printf("Матрица пуста!\n");
                continue;
            }

            printf("Среднее арифметическое: %.2f\n",
                   average_matrix(mat, rows, cols));
        }
        else if (command == 'e') {
            double maximums[MAX_ROWS];
            size_t i;

            if (rows == 0 || cols == 0) {
                printf("Матрица пуста!\n");
                continue;
            }

            max_in_rows(mat, rows, cols, maximums);

            printf("Максимум в каждой строке:\n");
            for (i = 0; i < rows; i++) {
                printf("Строка %zu: %.2f\n", i + 1, maximums[i]);
            }
        }
        else if (command == 'f') {
            if (rows == 0 || cols == 0) {
                printf("Матрица пуста!\n");
                continue;
            }

            printf("Разность (max - min): %.2f\n",
                   diff_max_min(mat, rows, cols));
        }
        else if (command == 'g') {
            printf("Выход...\n");
            running = 0;
        }
        else {
            printf("Неизвестный пункт '%c'. Нужна буква от a до g.\n",
                   command);
        }
    }

    return 0;
}

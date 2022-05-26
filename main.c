#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(double *matrix, const unsigned SIZE) {
    for (unsigned i = 0; i < SIZE * SIZE; ++i) {
        if (i % SIZE == 0)printf("\n");
        printf("%f ", matrix[i]);
    }
    printf("\n");
}

double diagonalMultiplication(const double *matrix, const unsigned SIZE) {
    double rez = 1;
    for (unsigned i = SIZE; i >= 1; --i) rez *= matrix[(SIZE + 1) * (SIZE - i)];
    return rez;
}

int zeroesCheck(const double *range, const int n, const unsigned *SIZE) {
    int count = 0, flag = 1;
    for (unsigned i = n; i < *SIZE; ++i)
        if (range[i] == 0 && flag) {
            count++;
        } else flag = 0;
    return count;
}

int power(int a, int b) {
    int rez = 1;
    for (int i = 0; i < b; ++i) rez *= a;
    return rez;
}

void swap(double *range, unsigned n, const unsigned *SIZE) {
    double tmp;
    for (unsigned i = n; i < n + *SIZE; ++i) {
        tmp = range[i];
        range[i] = range[i + *SIZE];
        range[i + *SIZE] = tmp;
    }
}

int sort(double *matrix, const unsigned *SIZE) {
    int count = 0;
    for (unsigned i = 0; i < (*SIZE - 1) * *SIZE; i += *SIZE)
        if (zeroesCheck(matrix, i, SIZE) > zeroesCheck(matrix, i + *SIZE, SIZE)) {
            count++;
            swap(matrix, i, SIZE);
        }
    return power(-1, count);
}

double gaussianDeterminant(double *matrix, const unsigned SIZE) {
    unsigned size = SIZE;
    int k = 1, flag = 1;
    double first, factor, res;
    while (size > 1) {
        if (matrix[(SIZE + 1) * (SIZE - size)] == 0) {
            flag = 0;
            break;
        }
        first = matrix[(SIZE + 1) * (k - 1)];
        for (unsigned ind = 0; ind < size * size - size; ++ind) {
            unsigned i = (ind / size * SIZE + SIZE - 1 - ind % size + k * SIZE); // reverse
            factor = matrix[(i / SIZE) * SIZE + k - 1] / first;
            matrix[i] -= matrix[(k - 1) * SIZE + i % SIZE] * factor;
        }
        k++;
        size--;
    }
    if (flag)
        res = diagonalMultiplication(matrix, SIZE);
    else res = 0;
    return res;
}

void init() {
    FILE *fp1, *fp2;
    if ((fp1 = fopen("read.txt", "r")) == NULL) {
        printf("Can't open file 'read.txt'\n");
        exit(-1);
    }
    if ((fp2 = fopen("write.txt", "w")) == NULL) {
        printf("Can't open file 'write.txt'\n");
        exit(-1);
    }
    double *matrix;
    double determinant;
    unsigned SIZE;
    int sign;
    clock_t time_start, time_finish;
    while (fscanf(fp1, "%u", &SIZE) == 1) {
        time_start = clock();
        matrix = (double *) malloc(SIZE * SIZE * sizeof(double));
        if (!matrix)exit(-3);
        for (unsigned i = 0; i < SIZE * SIZE; ++i) {
            fscanf(fp1, "%lf", &matrix[i]);
        }
        sign = sort(matrix, &SIZE);
        determinant = gaussianDeterminant(matrix, SIZE) * (double) sign;
        time_finish = clock();
        fprintf(fp2, "%ld %f\n", time_finish - time_start, determinant);
        printf("%d\n", SIZE);
        free(matrix);
    }
    fclose(fp1);
    fclose(fp2);
}

int main() {
    init();
    return 0;
}

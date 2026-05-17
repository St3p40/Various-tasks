#include <stdio.h>
#include <stdlib.h>

void solveMatrix(int n, double *a, double *c, double *b, double *f, double *x) {
    double *gamma = (double *)malloc(n * sizeof(double));
    double *delta = (double *)malloc(n * sizeof(double));

    for (int i = n - 1; i >= 1; i--) {
        double denominator = c[i] + b[i] * gamma[i + 1];
        if (i < n - 1) {
            gamma[i] = -a[i] / denominator;
        }
        delta[i] = (f[i] - b[i] * delta[i + 1]) / denominator;
    }

    x[0] = (f[0] - b[0] * delta[1]) / c[0] + b[0] * gamma[1];
    for (int i = 1; i < n; i++) {
        x[i] = delta[i] + gamma[i] * x[i - 1];
    }
    free(gamma);
    free(delta);
}

void printMatrix(int n, double *a, double *c, double *b, double *f) {
    printf("Matrix A (tridiagonal):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == i) {
                printf("%10.2f ", c[i]);
            } else if (j == i + 1) {
                printf("%10.2f ", b[i]);
            } else if (j == i - 1) {
                printf("%10.2f ", a[i]);
            } else {
                printf("%10.2f ", 0.0);
            }
        }
        printf("\n");
    }

    printf("Right-hand side vector f:\n");
    for (int i = 0; i < n; i++) {
        printf("%10.2f\n", f[i]);
    }
}

int main() {
    int n;

    printf("Enter the number of equations (n): ");
    scanf("%d", &n);

    double *a = (double *)malloc(n * sizeof(double));
    double *c = (double *)malloc(n * sizeof(double));
    double *b = (double *)malloc(n * sizeof(double));
    double *f = (double *)malloc(n * sizeof(double));
    double *x = (double *)malloc(n * sizeof(double));

    printf("Enter the below diagonal elements (a): ");
    for (int i = 1; i < n; i++) {
        scanf("%lf", &a[i]);
    }
    a[0] = 0;

    printf("Enter the main diagonal elements (c): ");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &c[i]);
    }

    printf("Enter the above diagonal elements (b): ");
    for (int i = 0; i < n - 1; i++) {
        scanf("%lf", &b[i]);
    }
    b[n - 1] = 0;

    printf("Enter the right-hand side vector (f): ");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &f[i]);
    }

    printMatrix(n, a, c, b, f);
    solveMatrix(n, a, c, b, f, x);

    printf("Solution vector x:\n");
    for (int i = 0; i < n; i++) {
        printf("%10.2f\n", x[i]);
    }

    free(a);
    free(c);
    free(b);
    free(f);
    free(x);

    return 0;
}

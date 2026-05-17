#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void jacobiMethod(int n, double **a, double *b, double *x, double tolerance, int max_iter) {
    double *x_new = (double *)malloc(n * sizeof(double));
    int iter = 0;

    while (iter < max_iter) {
        for (int i = 0; i < n; i++) {
            x_new[i] = b[i];
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    x_new[i] -= a[i][j] * x[j];
                }
            }
            x_new[i] /= a[i][i];
        }

        double max_diff = 0.0;
        for (int i = 0; i < n; i++) {
            double diff = fabs(x_new[i] - x[i]);
            if (diff > max_diff) {
                max_diff = diff;
            }
        }

        if (max_diff < tolerance) {
            printf("Converged after %d iterations\n", iter + 1);
            break;
        }

        for (int i = 0; i < n; i++) {
            x[i] = x_new[i];
        }

        iter++;
    }

    if (iter == max_iter) {
        printf("Warning: Maximum iterations reached without convergence\n");
    }

    free(x_new);
}

int main() {
    int n;

    printf("Enter the number of equations (n): ");
    scanf("%d", &n);

    double **a = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        a[i] = (double *)malloc(n * sizeof(double));
    }

    double *b = (double *)malloc(n * sizeof(double));
    double *x = (double *)malloc(n * sizeof(double));

    printf("Enter elements (a): \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &a[i][j]);
        }
    }

    printf("Enter the right-hand side vector (b): ");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &b[i]);
    }

    printf("Enter the initial guess for the solution (x0): ");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &x[i]);
    }


    double tolerance = 0.01;
    int max_iter = 1000;

    jacobiMethod(n, a, b, x, tolerance, max_iter);

    printf("Solution vector x:\n");
    for (int i = 0; i < n; i++) {
        printf("%10.6f\n", x[i]);
    }

    for (int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
    free(b);
    free(x);

    return 0;
}

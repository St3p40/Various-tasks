#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void generate_random_samples(int samples[], int n, int min, int max)
{
    for (int i = 0; i < n; i++)
    {
        samples[i] = rand() % (max - min + 1) + min;
    }
}

double calc_avg(int samples[], int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum += samples[i];
    }
    return sum / n;
}

double calc_median(int samples[], int n)
{
    qsort(samples, n, sizeof(int), cmpfunc);
    if (n % 2 == 0)
    {
        return (samples[n / 2 - 1] + samples[n / 2]) / 2.0;
    }
    else
    {
        return samples[n / 2];
    }
}

void calc_mode(int samples[], int n, int modes[], int *mode_count, int max_value)
{
    int frequency[max_value + 1];
    memset(frequency, 0, sizeof(frequency));
    int max_count = 0;

    for (int i = 0; i < n; i++)
    {
        frequency[samples[i]]++;
        if (frequency[samples[i]] > max_count)
        {
            max_count = frequency[samples[i]];
        }
    }

    *mode_count = 0;
    for (int i = 1; i <= max_value; i++)
    {
        if (frequency[i] == max_count && max_count > 1)
        {
            modes[*mode_count] = i;
            (*mode_count)++;
        }
    }
}

double calc_dev(int samples[], int n, double avg)
{
    double sum_squared_diff = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum_squared_diff += (samples[i] - avg) * (samples[i] - avg);
    }
    return sum_squared_diff;
}

double calc_variance(int samples[], int n, double avg)
{
    return calc_dev(samples, n, avg) / n;
}

double calc_disparce(int samples[], int n, double avg)
{
    return calc_dev(samples, n, avg) / (n - 1);
}

double calc_standard(double variance)
{
    return sqrt(variance);
}

double calc_variation(double stddev, double avg)
{
    return stddev / avg;
}

double calc_range(int samples[], int n)
{
    int max_val = samples[0];
    int min_val = samples[0];
    for (int i = 1; i < n; i++)
    {
        if (samples[i] > max_val)
            max_val = samples[i];
        if (samples[i] < min_val)
            min_val = samples[i];
    }
    return max_val - min_val;
}

double calc_central_moment(int samples[], int n, double avg, double stddev, double k)
{
    double moment = 0.0;
    for (int i = 0; i < n; i++)
    {
        moment += pow((samples[i] - avg), k);
    }
    return moment / n;
}
double calc_asymmetry(int samples[], int n, double avg, double stddev)
{
    return calc_central_moment(samples, n, avg, stddev, 3) / pow(calc_central_moment(samples, n, avg, stddev, 2), 1.5);
}

double calc_kurtosis(int samples[], int n, double avg, double stddev)
{
    return (calc_central_moment(samples, n, avg, stddev, 4) / pow(calc_central_moment(samples, n, avg, stddev, 2), 2)) - 3;
}

void print_variation_series(int samples[], int n)
{
    qsort(samples, n, sizeof(int), cmpfunc);
    printf("Варіаційний ряд:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", samples[i]);
    }
    printf("\n");
}

void print_frequency_table(int samples[], int n, int max_value)
{
    int frequency[max_value + 1];
    memset(frequency, 0, sizeof(frequency));

    for (int i = 0; i < n; i++)
    {
        frequency[samples[i]]++;
    }

    printf("\n| X i | N i |\n");
    printf("|-----|-----|\n");
    for (int i = 1; i <= max_value; i++)
    {
        if (frequency[i] > 0)
        {
            printf("|%5d|%5d|\n", i, frequency[i]);
        }
    }
    printf("|-----|-----|\n");
}

void print_frequency_graph(int frequency[], int max_value)
{
    printf("\nДіаграма частот:\n");
    for (int i = 1; i <= max_value; i++)
    {
        if (frequency[i] > 0)
        {
            printf("%2d | ", i);
            for (int j = 0; j < frequency[i] - 1; j++)
            {
                printf("-");
            }
            printf("|");
            printf(" (%d)\n", frequency[i]);
        }
        else
            printf("%2d | (0)\n", i);
    }
}

void calc_empirical_distribution(int samples[], int n, int max_value)
{
    int frequency[max_value + 1];
    memset(frequency, 0, sizeof frequency);

    for (int i = 0; i < n; i++)
    {
        frequency[samples[i]]++;
    }

    double cumulative_frequency[max_value + 1];
    memset(cumulative_frequency, 0, sizeof cumulative_frequency);
    cumulative_frequency[0] = (double)frequency[0] / n;

    for (int i = 0; i <= max_value; i++)
    {
        cumulative_frequency[i] = cumulative_frequency[i - 1] + (double)frequency[i] / n;
    }

    printf("\nЕмпірична функція розподілу:\n");
    printf("| Значення | Емпірична ймовірність |\n");
    printf("|----------|-----------------------|\n");
    for (int i = 0; i <= max_value; i++)
    {
        if (frequency[i] || i == 0)
            printf("| %8d | %21.4f |\n", i, cumulative_frequency[i]);
    }
    printf("|----------|-----------------------|\n");
}

void print_statistics(double avg, double median, int modes[], int mode_count,
                      double variance, double disparce, double stddev, double variation, double range,
                      double asymmetry, double kurtosis)
{
    printf("\n| Характеристика                | Значення\n");
    printf("|-------------------------------|\n");
    printf("| Середнє                       | %.2f\n", avg);
    printf("| Медіана                       | %.2f\n", median);
    printf("| Мода                          | %s", mode_count > 0 ? "" : "Немає");
    for (int i = 0; i < mode_count; i++)
    {
        printf("%d%s", modes[i], (i < mode_count - 1) ? ", " : " ");
    }
    printf("\n\n");

    printf("| Розмах                        | %.2f\n", range);
    printf("| Варіанса                      | %.2f\n", variance);
    printf("| Вибіркова дисперсія           | %.2f\n", disparce);
    printf("| Стандарт                      | %.2f\n", stddev);
    printf("| Варіація                      | %.2f\n\n", variation);

    printf("| Асиметрія                     | %.2f\n", asymmetry);
    printf("| Ексцес                        | %.2f\n", kurtosis);
    printf("|-------------------------------|\n");
}

int main()
{
    srand(time(NULL));

    int n;
    int max_value;

    printf("Введіть розмір вибірки: ");
    scanf("%d", &n);
    printf("Введіть максимальне значення: ");
    scanf("%d", &max_value);

    int min = 1;
    int samples[n];

    generate_random_samples(samples, n, min, max_value);

    printf("Вибірка:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", samples[i]);
    }
    printf("\n");

    double avg = calc_avg(samples, n);
    double median = calc_median(samples, n);

    int modes[max_value];
    int mode_count = 0;
    calc_mode(samples, n, modes, &mode_count, max_value);

    double variance = calc_variance(samples, n, avg);
    double disparce = calc_disparce(samples, n, avg);
    double stddev = calc_standard(variance);
    double variation = calc_variation(stddev, avg);
    double range = calc_range(samples, n);
    double asymmetry = calc_asymmetry(samples, n, avg, stddev);
    double kurtosis = calc_kurtosis(samples, n, avg, stddev);

    print_variation_series(samples, n);
    print_frequency_table(samples, n, max_value);

    int frequency[max_value + 1];
    memset(frequency, 0, sizeof(frequency));
    for (int i = 0; i < n; i++)
    {
        frequency[samples[i]]++;
    }
    print_frequency_graph(frequency, max_value);
    calc_empirical_distribution(samples, n, max_value);
    print_statistics(avg, median, modes, mode_count, variance, disparce, stddev, variation, range, asymmetry, kurtosis);
    return 0;
}

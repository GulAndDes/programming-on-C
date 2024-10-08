#include <stdio.h>
#include <math.h>

// Факториал
double factorial(int n) {
    double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// 1. Функция для вычисления гаммы через предел
double gamma_limit(int m) {
    m = 23;
    double result = 0.0;
    for (int k = 1; k <= m; k++) {
        long long  cmk = factorial(m) / (factorial(k) * (factorial(m - k)));
        double term = cmk * (pow(-1, k) / k) * log(factorial(k));
        result += term;
    }
    return result;
}

// 2. Функция для вычисления гаммы через сумму ряда
double gamma_series(int max_k) {
    double result = -pow(3.14, 2) / 6.0;
    for (int k = 2; k <= 100000; k++) {
        result += (1.0 / pow(floor(sqrt(k)), 2)) - (1.0 / k);
    }
    return result;
}

// Простая проверка простого числа
int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// 3. Функция для вычисления гаммы через уравнение (через логарифм и произведение простых чисел)
double gamma_equation(int t) {
    double product = 1.0;
    for (int p = 2; p <= t; p++) {
        if (is_prime(p)) {
            product *= (double)(p - 1) / p;
        }
    }
    return -log(log(t) * product);
}

int main() {
    int m = 100;     // Количество итераций для предела
    int max_k = 10000; // Количество итераций для ряда
    int t = 100000;    // Предел для логарифма и произведения

    // 1. Вычисление гаммы через предел
    double gamma_by_limit = gamma_limit(m);
    printf("Гамма через предел: %.15f\n", gamma_by_limit);

    // 2. Вычисление гаммы через сумму ряда
    double gamma_by_series = gamma_series(max_k);
    printf("Гамма через ряд: %.15f\n", gamma_by_series);

    // 3. Вычисление гаммы через уравнение
    double gamma_by_equation = gamma_equation(t);
    printf("Гамма через уравнение: %.15f\n", gamma_by_equation);

    return 0;
}

#include <stdio.h>
#include <math.h>

double e_lim(int n) {
    return pow(1.0 + 1.0 / n, n);
}

double e_ser(int terms) {
    double e = 1.0;
    double factorial = 1.0;
    for (int i = 1; i < terms; i++) {
        factorial *= i;
        e += 1.0 / factorial;
    }
    return e;
}

double e_eq() {
    return exp(1.0);
}


double pi_lim(int n){
    n = 45;
    double nfactorial = 1.0;
    double twonfactorial = 1.0;
    for (int i = 1; i <= n; i++) {
        nfactorial *= i;
    }
    for (int i = 1; i <= 2 * n; i++) {
        twonfactorial *= i;
    }

    return pow(pow(2, n) * nfactorial,  4) / (n * pow(twonfactorial, 2));
}

double pi_ser(int terms){
    double pi = 0.0;
    for (int i = 1; i <= terms; i++){
        pi += pow(-1, (i - 1)) / (2.0 * i - 1.0);
    }
    return pi * 4;
}

double pi_eq(){
    return acos(-1.0);
}

double ln2_lim(int n) {
    return n * (pow(2, 1.0 / n) - 1);
}

double ln2_ser(int terms) {
    double ln2 = 0.0;
    for (int n = 1; n <= terms; n++) {
        ln2 += pow(-1, n - 1) / n;
    }
    return ln2;
}

double ln2_eq() {
    return log(2.0);  
}

double sqrt2_lim(int n) {
    double x_n = -0.5;  
    for (int i = 0; i < n; i++) {
        x_n = x_n - (x_n * x_n - 2.0) / (2.0);
    }
    return x_n;
}

double sqrt2_ser(int terms) {
    double sq2 = 1.0;
    for (int k = 2; k <= terms; k++) {
        sq2 *= pow(2, pow(2, -k));
    }
    return sq2;
}

double sqrt2_eq() {
    return sqrt(2.0);  
}


double factorial(int n) {
    double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

double gamma_lim(int m) {
    m = 23;
    double gamma = 0.0;
    for (int k = 1; k <= m; k++) {
        long long  cmk = factorial(m) / (factorial(k) * (factorial(m - k)));
        double x = cmk * (pow(-1, k) / k) * log(factorial(k));
        gamma += x;
    }
    return gamma;
}

double gamma_ser(int max_k) {
    double gamma = -pow(3.14, 2) / 6.0;
    for (int k = 2; k <= 100000; k++) {
        gamma += (1.0 / pow(floor(sqrt(k)), 2)) - (1.0 / k);
    }
    return gamma;
}

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

double gamma_eq(int t) {
    double x = 1.0;
    for (int p = 2; p <= t; p++) {
        if (is_prime(p)) {
            x *= (double)(p - 1) / p;
        }
    }
    return -log(log(t) * x);
}

int main(int argc, char *argv[]) {
    if (argc != 2 ){
        printf("enter: epsilon\n");
        return 1;
    }
    int n = 10000;
    int terms = 10000; 

    printf("e  : %.15f\n", e_lim(n));
    printf("e  : %.15f\n", e_ser(terms));
    printf("e  : %.15f\n", e_eq());
    printf("\n");
    printf("pi  : %.15f\n", pi_lim(n));
    printf("pi  : %.15f\n", pi_ser(terms));
    printf("pi  : %.15f\n", pi_eq());
    printf("\n");
    printf("ln2  : %.15f\n", ln2_lim(n));
    printf("ln2  : %.15f\n", ln2_ser(terms));
    printf("ln2  : %.15f\n", ln2_eq());
    printf("\n");
    printf("sq2  : %.15f\n", sqrt2_lim(n));
    printf("sq2  : %.15f\n", sqrt2_ser(terms));
    printf("sq2  : %.15f\n", sqrt2_eq());
    printf("\n");
    printf("gamma  : %.15f\n", gamma_lim(n));
    printf("gamma  : %.15f\n", gamma_ser(terms));
    printf("gamma  : %.15f\n", gamma_eq(n));



    return 0;
}

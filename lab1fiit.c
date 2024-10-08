#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void pr_k(int x) {
    int F = 0;
    for (int i = x; i <= 100; i += x) {
        printf("%d ", i);
        F = 1;
    }
    if (!F) {
        printf("no num kratnih %d\n", x);
    } else {
        printf("\n");
    }
}

void is_prime(int x) {
    if (x < 2) {
        printf("%d cringe\n", x);
        return;
    }
    int F = 1;
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            F = 0;
            break;
        }
    }
    if (F) {
        printf("%d  prostoe \n", x);
    } else {
        printf("%d sostavnoe  \n", x);
    }
}

void hex(int x) {
    printf("num  16sys: ");
    for (int i = 7; i >= 0; i--) {
        int digit = (x >> (i * 4)) & 0xF;
        if (digit || i == 0 || x >> (i * 4)) {
            printf("%X ", digit);
        }
    }
    printf("\n");
}

void pr_st(int x) {
    if (x > 10) {
        printf("num x > 10 = cringe\n");
        return;
    }
    for (int i = 1; i <= 10; i++) {
        printf("%d^%d = %.0f\n", i, x, pow(i, x));
    }
}

void sum_nat_num(int x) {
    int sum = 0;
    for (int i = 1; i <= x; i++) {
        sum += i;
    }
    printf("sum nat num from 1 to %d: %d\n", x, sum);
}

void fact(int x) {
    long long fact = 1;
    for (int i = 1; i <= x; i++) {
        fact *= i;
    }
    printf("factorial %d: %lld\n", x, fact);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("enter: number and flag\n");
        return 1;
    }

    int x = atoi(argv[1]);
    char *flag = argv[2];

    if (strcmp(flag, "-h") == 0 || strcmp(flag, "/h") == 0) {
        pr_k(x);
    } else if (strcmp(flag, "-p") == 0 || strcmp(flag, "/p") == 0) {
        is_prime(x);
    } else if (strcmp(flag, "-s") == 0 || strcmp(flag, "/s") == 0) {
        hex(x);
    } else if (strcmp(flag, "-e") == 0 || strcmp(flag, "/e") == 0) {
        pr_st(x);
    } else if (strcmp(flag, "-a") == 0 || strcmp(flag, "/a") == 0) {
        sum_nat_num(x);
    } else if (strcmp(flag, "-f") == 0 || strcmp(flag, "/f") == 0) {
        fact(x);
    } else {
        printf("No flag: %s\n", flag);
    }

    return 0;
}

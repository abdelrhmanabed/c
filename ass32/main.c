#include <stdio.h>
#include <stdlib.h>


/*
 * Function declarations
 */
double powerOfNumber(double , int);
int factorialOfNumber(int);
double computeExpo(double );

int main() {

    printf("Please enter value of x :");
    double x;
    scanf("%lf",&x);
    double ex = computeExpo(x);
    printf("Answer: %.2lf",ex);

    return 0;
}

double powerOfNumber(double x, int y) {
    double power = 1;
    while (y != 0) {
        power *= x;
        y--;
    }
    return power;
}

int factorialOfNumber(int x) {
    int factorial = 1;
    for (int i=1;i<=x;i++) {
        factorial *= i;
    }
    return factorial;
}

double computeExpo(double x) {
    double ex = 0;
    int term = 0;
    do {
        ex =  ex + powerOfNumber(x,term)/factorialOfNumber(term);
        term++;
    } while (term !=10);
    return ex;
}

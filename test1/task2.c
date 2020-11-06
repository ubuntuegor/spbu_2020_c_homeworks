#include <stdio.h>

typedef struct Complex {
    double real;
    double imaginary;
} Complex;

void printComplex(Complex n)
{
    printf("Real: %f\nIm: %f\n\n", n.real, n.imaginary);
}

Complex add(Complex a, Complex b)
{
    Complex result = { a.real + b.real, a.imaginary + b.imaginary };
    return result;
}

Complex subtract(Complex a, Complex b)
{
    Complex result = { a.real - b.real, a.imaginary - b.imaginary };
    return result;
}

Complex multiply(Complex a, Complex b)
{
    double real = a.real * b.real - a.imaginary * b.imaginary;
    double imaginary = a.real * b.imaginary + a.imaginary * b.real;
    Complex result = { real, imaginary };
    return result;
}

Complex divide(Complex a, Complex b)
{
    double real = (a.real * b.real + a.imaginary * b.imaginary) / (b.real * b.real + b.imaginary * b.imaginary);
    double imaginary = (a.imaginary * b.real - a.real * b.imaginary) / (b.real * b.real + b.imaginary * b.imaginary);
    ;
    Complex result = { real, imaginary };
    return result;
}

int main()
{
    Complex n = { 1, 4 };
    Complex m = { 10, -5.5 };

    printf("Number 1:\n");
    printComplex(n);
    printf("Number 2:\n");
    printComplex(m);
    printf("Sum:\n");
    printComplex(add(n, m));
    printf("Diff:\n");
    printComplex(subtract(n, m));
    printf("Multiplication:\n");
    printComplex(multiply(n, m));
    printf("Division:\n");
    printComplex(divide(n, m));
    return 0;
}

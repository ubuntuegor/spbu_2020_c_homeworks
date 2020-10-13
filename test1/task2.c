#include <stdio.h>

typedef struct Complex {
    double real;
    double imaginary;
} Complex;

void printComplex(Complex n)
{
    printf("\nReal: %f\nIm: %f\n", n.real, n.imaginary);
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
    printComplex(n);
    printComplex(m);
    printComplex(add(n, m));
    printComplex(subtract(n, m));
    printComplex(multiply(n, m));
    printComplex(divide(n, m));
    return 0;
}

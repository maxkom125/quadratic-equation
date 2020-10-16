// This program solves equation ax^2 + bx + c = 0. Input: a b c; Output: x1, x2 and number of roots
#include<stdio.h>
#include<math.h>

const double EPS = 0.000001; // accuracy of comparsion double
//#define Debug
#ifdef Debug
#define TEST testSolveEquation()
#else
#define TEST 1
#endif

void assert(double x)
{
    if (isnan(x) != 0)
    {
        printf("argument is not double \n");
        system("pause");
        exit(1);
    }
}

#define UNIT_TEST(koefa, koefb, koefc, root1, root2, numberofroots)/*please, write koefficients and roots in double format, like 1.0 numberofroots - int format*/\
double ux1 = NAN, ux2 = NAN; \
int unRoots = solveEquation(koefa, koefb, koefc, &ux1, &ux2);\
if (unRoots != numberofroots || checkRoots(ux1, ux2, root1, root2) == 0)\
{\
	printf(" \n ERROR in function solveEquation input: %lf  %lf  %lf; must return: %d; x1 = %lf, x2 = %lf; returns: %d x1 = %lf, x2 = %lf \n ", \
/*                                               */koefa, koefb, koefc,    numberofroots, root1,    root2,      unRoots,     ux1,      ux2);\
}

void obNAN(double* x1, double* x2)
{
    *x1 = NAN;
    *x2 = NAN;
}

int comparsionDouble(double arg1, double arg2)
{
    if ((arg1 - arg2) > EPS || (arg1 - arg2) < -1*EPS)
        return 0;
    else
        return 1;
}

int solveLinealEquation(double k, double l, double* x)// Function finds root x of equation kx + c = 0
{                                                     // Returns -1 - infinitely roots; 0 - no roots; 1 - one root
    assert(k);
    assert(l);

    if (comparsionDouble(k, 0))
    {
        if (comparsionDouble(l, 0))
            return -1;
        else
            return 0;
    }
    *x = -l / k;
    return 1;
}

int solveEquation(double a, double b, double c, double* x1, double* x2) // Function finds roots x1, x2 of equation ax^2 + bx + c = 0
{                                                                       // Returns -1 - infinitely roots; 0 - no roots; 1 - one root; 2 - two roots
    int nRoots = -2;
    double discriminant = b * b - 4 * a * c;
    // Check the number of roots
    if (comparsionDouble(a, 0) && comparsionDouble(b, 0) && comparsionDouble(c, 0)) // infinitely roots
        return -1;
    if ((discriminant < -1*EPS && ! comparsionDouble(a, 0)) || (comparsionDouble(a, 0) && comparsionDouble(b, 0) && ! comparsionDouble(c, 0)) ) // no roots if discriminant < 0 and equation is square, or equation has the form: c = 0; but entered c != 0;
    {
        return 0;
    }
    if (comparsionDouble(a, 0)) // equation is not square, bx + c = 0
    {
        nRoots = solveLinealEquation(b, c, x1);
        *x2 = *x1;
        return nRoots;
    }
    if (comparsionDouble(discriminant, 0)) // 1 root
        nRoots = 1;
    if (discriminant > EPS) // 2 roots
        nRoots = 2;

    // Calculate roots
    double sqrtdiscriminant = sqrt(discriminant);
    *x1 = (-b + sqrtdiscriminant) / (2 * a);
    *x2 = (-b - sqrtdiscriminant) / (2 * a);
    return nRoots;
}

//-----------------------------------------------test block-----------------------------------------------
int checkRoots(double x1, double x2, double val1, double val2) // check are first two values coincide with second two values. Returns 1 if true; 0 if false
{
    if((comparsionDouble(x1, val1) && comparsionDouble(x2, val2)) || (comparsionDouble(x1, val2) && comparsionDouble(x2, val1)) || (isnan(x1) != 0 && isnan(x2) != 0 && isnan(val1) != 0 && isnan(val2) != 0))
        return 1;
    else
        return 0;
}

int testSolveEquation()
{
    int retur = 1; // if this parameter in the end of function == 1 all solveEquation passed all tests; if retur == 0 - some errors
    double x1 = NAN, x2 = NAN;
    int nRoots = solveEquation(0, 0, 1, &x1, &x2);
    if (nRoots != 0)
    {
        printf(" /n ERROR in function solveEquation input: 0 0 1; must return: 0; returns: %d \n ", nRoots);
        retur = 0;
    }
    nRoots = solveEquation(0, 0, 0, &x1, &x2);
    if (nRoots != -1)
    {
        printf("/n ERROR in function solveEquation input: 0 0 0; must return: -1; returns: %d \n ", nRoots);
        retur = 0;
    }
    obNAN(&x1, &x2);
    nRoots = solveEquation(0, -1, 1, &x1, &x2);
    assert(x1);
    assert(x2);
    if (nRoots != 1 || checkRoots(x1, x2, 1, 1) == 0)
    {
        printf(" \n ERROR in function solveEquation input: 0 -1 1; must return: 1; x1 = 1; x2 = 1; returns: %d x1 = %lf, x2 = %lf \n ", nRoots, x1, x2);
        retur = 0;
    }
    obNAN(&x1, &x2);
    nRoots = solveEquation(0, 1, 0, &x1, &x2);
    assert(x1);
    assert(x2);
    if (nRoots != 1 || checkRoots(x1, x2, 0, 0) == 0)
    {
        printf(" \n ERROR in function solveEquation input: 0 1 0; must return: 1; x1 = x2 = 0; returns: %d x1 = %lf, x2 = %lf \n ", nRoots, x1, x2);
        retur = 0;
    }
    obNAN(&x1, &x2);
    nRoots = solveEquation(1, 0, 0, &x1, &x2);
    assert(x1);
    assert(x2);
    if (nRoots != 1 || checkRoots(x1, x2, 0, 0) == 0)
    {
        printf(" \n ERROR in function solveEquation input: 1 0 0; must return: 1; x1 = x2 = 0; returns: %d x1 = %lf, x2 = %lf \n ", nRoots, x1, x2);
        retur = 0;
    }
    obNAN(&x1, &x2);
    nRoots = solveEquation(1, 0, 1, &x1, &x2);
    if (nRoots != 0)
    {
        printf(" \n ERROR in function solveEquation input: 1 0 1; must return: 0; returns: %d \n ", nRoots);
        retur = 0;
    }
    obNAN(&x1, &x2);
    nRoots = solveEquation(1, 0, -1, &x1, &x2);
    assert(x1);
    assert(x2);
    if (nRoots != 2 || checkRoots(x1, x2, 1, -1) == 0)
    {
        printf(" \n ERROR in function solveEquation input: 1 0 -1; must return: 2; x1 = 1; x2 = -1; returns: %d x1 = %lf, x2 = %lf \n ", nRoots, x1, x2);
        retur = 0;
    }
    obNAN(&x1, &x2);
    nRoots = solveEquation(1, 1, 8, &x1, &x2);
    if (nRoots != 0)
    {
        printf(" \n ERROR in function solveEquation input: 1 1 8; must return: 0; returns: %d \n ", nRoots);
        retur = 0;
    }
    obNAN(&x1, &x2);
    nRoots = solveEquation(1, 2, 1, &x1, &x2);
    assert(x1);
    assert(x2);
    if (nRoots != 1 || checkRoots(x1, x2, -1, -1) == 0)
    {
        printf(" \n ERROR in function solveEquation input: 1 2 1; must return: 1; x1 = -1; x2 = -1; returns: %d x1 = %lf, x2 = %lf \n ", nRoots, x1, x2);
        retur = 0;
    }
    obNAN(&x1, &x2);
    nRoots = solveEquation(1, 1, -6, &x1, &x2);
    assert(x1);
    assert(x2);
    if (nRoots != 2 || checkRoots(x1, x2, -3, 2) == 0)
    {
        printf(" \n ERROR in function solveEquation input: 1 1 -6; must return: 2; x1 = -3; x2 = 2; returns: %d x1 = %lf, x2 = %lf \n ", nRoots, x1, x2);
        retur = 0;
    }
    obNAN(&x1, &x2);
    nRoots = solveEquation(1, 0.5, -1.5, &x1, &x2);
    assert(x1);
    assert(x2);
    if (nRoots != 2 || checkRoots(x1, x2, 1, -1.5) == 0)
    {
        printf(" \n ERROR in function solveEquation input: 1 0.5 -1.5; must return: 2; x1 = 1; x2 = -1.5; returns: %d x1 = %lf, x2 = %lf \n ", nRoots, x1, x2);
        retur = 0;
    }
    if (retur == 0)
        printf("\n TESTS DIDN'T PASS \n");
    else
        printf("\n TESTS PASSED \n");
    system("pause");
    return retur;
}


int main()
{
    UNIT_TEST(1.0, 2.0, 1.0, -1.0, -1.0, 1);
    int testt = TEST;
    if (testt == 0)
        return 0;
    double a = NAN, b = NAN, c = NAN, x1 = 0, x2 = 0;
    printf("\n This program solves equation ax^2 + bx + c = 0 \n\n");
    printf("Write coefficients of equation a b c separated by space \n");
    scanf("%lf %lf %lf", &a, &b, &c);
    assert(a); //
    assert(b); // check user input
    assert(c); //
    int nRoots = -2;
    int retur = 0;
    nRoots = solveEquation(a, b, c, &x1, &x2);
    if (isfinite(nRoots) == 0)
        nRoots = -1; //for case in switch
    switch (nRoots) // print number of roots
    {
        case -1: printf("\n Equation has infinitely roots \n");
            break;
        case 0: printf("\n Equation has not roots \n");
            break;
        case 1: printf("\n Equation has 1 root: %lf \n", x1);
            break;
        case 2: printf("\n Equation has 2 roots: %lf; %lf \n", x1, x2);
            break;
        default: printf("\n ERROR no equation \n");
            break;
    }
    system("pause");
    return 0;
}
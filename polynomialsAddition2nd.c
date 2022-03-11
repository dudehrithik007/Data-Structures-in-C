#include<stdio.h>
#include<stdlib.h> // for Dynamic Array Allocation using calloc(sizeofarray, sizeof(data_type)). Can use Malloc() too. Static Allocation syntax also works for dynamic allocation in VSCode but doesn't work in debugger.

// *(int(*)[size_of_array_as_a_constant])pointer_name_for array => use this as watch in the debugger for each array to see the dynamically allocated array elements.

// Please note: Each term of an input polynomial must have a unique exponent of the variable. (Default definition of a term of a polynomial in this code)

void polyAdd2nd(int m1, int m2, int b1[], int e1[], int b2[], int e2[]);
void printPoly(int er[], int br[], int n);

void main()
{
    printf("\nProgram to add two polynomials represented using Scheme 2.\n");
    printf("Polynomials in Scheme 2 are of the form: (m, e[m-1], b[m-1], e[m-2], b[m-2]..., e[0], b[0]). \n");
    printf("Here m represent the number of non zero terms, b's and e's represent the coefficient-exponent pairs of the non zero terms.\n\n");

    printf("Enter the number of non-zero terms of the first polynomial to be added: ");
    int m1;
    do // Input Validation.
    {
        scanf("%d", &m1);
        if(m1 < 0)
            printf("Number of non-zero terms cannot be < 0. Please enter again:");
    } while (m1 < 0);

    printf("Enter the first polynomial: ");
    int* e1 = (int*) calloc(m1,sizeof(int)); // Exponent Array for 1st Polynomial.
    int* b1 = (int*) calloc(m1,sizeof(int)); // coefficient Array for 1st Polynomial.
    char plus;
    for(int i = 0; i < m1; i++)
    {
        scanf("%d x^ %d", &b1[i], &e1[i]);
        if(i < m1-1)
            scanf(" %c ", &plus);
    }
    printf("\nFirst Polynomial: ");
    printPoly(e1, b1, m1);

    printf("\n\nEnter the number of non-zero terms of the second polynomial to be added: ");
    int m2;
    do // Input Validation.
    {
        scanf("%d", &m2);
        if(m2 < 0)
            printf("Number of non-zero terms cannot be < 0. Please enter again:");
    } while (m2 < 0);

    printf("Enter the second polynomial: ");
    int* e2 = (int*) malloc(m2*sizeof(int)); // Exponent Array for 2nd Polynomial.
    int* b2 = (int*) malloc(m2*sizeof(int)); // coefficient Array for 2nd Polynomial.
    for(int i = 0; i < m2; i++)
    {
        scanf("%d x^ %d", &b2[i], &e2[i]);
        if(i < m2-1)
            scanf(" %c ", &plus);
    }
    printf("\nSecond Polynomial: ");
    printPoly(e2, b2, m2);
    printf("\n");

    polyAdd2nd(m1, m2, b1, e1, b2, e2);
}



void polyAdd2nd(int m1, int m2, int b1[], int e1[], int b2[], int e2[])
{
    int i,j;
    int k = 0;
    int flag;
    int m3 = 0;
    int* e3 = (int*) malloc(m3*sizeof(int)); // Exponent Array for 3rd Polynomial.
    int* b3 = (int*) malloc(m3*sizeof(int)); // coefficient Array for 3rd Polynomial.

    for(i = 0; i < m1; i++) // Comparing each term of 1st Polynomial with each term of 2nd Polynomial.
    {
        flag = 0; // flag keeps track whether any term's exponent of 1st Polynomial is equal to that of 2nd.
        for(j=0; j < m2; j++)
        {
            if(e1[i] == e2[j]) // If exponents are equal, adding below the coefficients.
            {
                b3[k] = b1[i] + b2[i];
                e3[k] = e1[i];
                k++;
                m3++;
                flag = 1; // flag set to 1 when exponents are same.
                break;
            }
            flag = 0;
        }
        if(flag == 1)
            continue;
        else // If flag is unset (= 0) => i'th exponent of 1st Polynomial is not equal to any exponent of 2nd Polynomial => put that term in the sum polynomial below as it is. 
        {
            b3[k] = b1[i];
            e3[k] = e1[i];
            k++;
            m3++;
        }
    }

    // Below code is same as the above block (between the two blank lines) except in this we compare the exponents of 2nd Polynomial with the 1st instead of vice versa as done in the above block.
    for(i = 0; i < m2; i++)
    {
        flag = 0;
        for(j=0; j < m1; j++)
        {
            if(e1[i] == e2[j])
            {
                flag = 1;
                break;
            }
            flag = 0;
        }
        if(flag == 1)
            continue;
        else
        {
            b3[k] = b2[i];
            e3[k] = e2[i];
            m3++;
            k++;
        }
    }

    printf("\nSum of Polynomials: ");
    printPoly(e3, b3, m3);

    printf("\n\n");
}

void printPoly(int er[], int br[], int n)
{
    // Using Bubble Sort to sort the terms according to the exponents in descending order - the usual notation.
    int t1, t2;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n - 1; j++)
        {
            if(er[j] < er[j+1])
            {  
                t1 = er[j];
                er[j] = er[j+1];
                er[j+1] = t1;

                t2 = br[j];
                br[j] = br[j+1];
                br[j+1] = t2;
            }
        }
    }
    
    for(int i = 0; i < n; i++)
    {
        printf("%dx^%d", br[i], er[i]);
        if(i < n-1)
            printf(" + ");
    }
}
#include<stdio.h>
#include<stdlib.h>

int** matricesMultiply(int m1, int n1, int n2, int** A, int** B);
int** subAdd(int m1, int n2, int** A, int** B);
void printArray(int m, int n, int** ar);

void valid(int *m, int *n)
{
    while (*m <= 0 || *n <= 0)
    {
        printf("\nNumber of Rows and Columns are Natural Numbers. Enter again:\n");
        printf("m = ");
        scanf("%d", m);
        printf("\n n = ");
        scanf("%d", n);
    }
}

void main()
{
    printf("\n\nC Program to find the product of two complex-valued matrices. Each complex-valued matrix is represented by a pair of real-valued matrices.\n\n");
    
    int m1, n1, m2, n2;

    printf("For 1st Complex-Valued Matrix:\n\n");
    printf("Enter the size:\n");
    scanf("%d", &m1);
    scanf("%d", &n1);
    valid(&m1, &n1);

    printf("\nFor 2nd Complex-Valued Matrix:\n\n");
    printf("Enter the size:\n");
    scanf("%d", &m2);
    scanf("%d", &n2);
    valid(&m2, &n2);

    if(n1 != m2)
    {
        printf("\nMultiplication is not possible.\n");
        exit(0);
    }

    printf("\nMultiplication is possible.\n\n");

    int** A = (int**) calloc(m1, sizeof(int*));
    for(int i = 0; i < m1; i++)
        A[i] = (int*) calloc(n1, sizeof(int));

    int** B = (int**) calloc(m1, sizeof(int*));
    for(int i = 0; i < m1; i++)
        B[i] = (int*) calloc(n1, sizeof(int));

    int** C = (int**) calloc(m2, sizeof(int*));
    for(int i = 0; i < m2; i++)
        C[i] = (int*) calloc(n2, sizeof(int));

    int** D = (int**) calloc(m2, sizeof(int*));
    for(int i = 0; i < m2; i++)
        D[i] = (int*) calloc(n2, sizeof(int));

    printf("For 1st Complex-Valued Matrix:\n\n");

    printf("Enter the values in the Real-Part Matrix: \n");
    for(int i = 0; i < m1; i++)
        for(int j = 0; j < n1; j++)
            scanf("%d", &A[i][j]);

    printf("\n");

    printf("Enter the values in the Imaginary-Part Matrix: \n");
    for(int i = 0; i < m1; i++)
        for(int j = 0; j < n1; j++)
            scanf("%d", &B[i][j]);

    printf("\n");
    
    printf("For 2nd Complex-Valued Matrix:\n\n");

    printf("Enter the values in the Real-Part Matrix: \n");
    for(int i = 0; i < m2; i++)
        for(int j = 0; j < n2; j++)
            scanf("%d", &C[i][j]);

    printf("\n");

    printf("Enter the values in the Imaginary-Part Matrix: \n");
    for(int i = 0; i < m2; i++)
        for(int j = 0; j < n2; j++)
            scanf("%d", &D[i][j]);

    printf("\n");

    int** AC = (int**) calloc(m1, sizeof(int*));
    for(int i = 0; i < m1; i++)
        AC[i] = (int *) calloc(n2, sizeof(int));

    AC = matricesMultiply(m1, n1, n2, A, C);

    int** AD = (int**) calloc(m1, sizeof(int*));
    for(int i = 0; i < m1; i++)
        AD[i] = (int *) calloc(n2, sizeof(int));

    AD = matricesMultiply(m1, n1, n2, A, D);

    int** BC = (int**) calloc(m1, sizeof(int*));
    for(int i = 0; i < m1; i++)
        BC[i] = (int *) calloc(n2, sizeof(int));

    BC = matricesMultiply(m1, n1, n2, B, C);

    int** BD = (int**) calloc(m1, sizeof(int*));
    for(int i = 0; i < m1; i++)
        BD[i] = (int *) calloc(n2, sizeof(int));

    BD = matricesMultiply(m1, n1, n2, B, D);

    int** P = (int**) calloc(m1, sizeof(int*));
    for(int i = 0; i < m1; i++)
        P[i] = (int *) calloc(n2, sizeof(int));

    P = subAdd(m1, n2, AC, BD);

    int** Q = (int**) calloc(m1, sizeof(int*));
    for(int i = 0; i < m1; i++)
        Q[i] = (int *) calloc(n2, sizeof(int));

    Q = subAdd(m1, n2, AD, BC);

    printf("\n=> A + iB = \n\n");
    printArray(m1, n1, A);
    printf("\n+ i*\n\n");
    printArray(m1, n1, B);

    printf("\n=> C + iD = \n\n");
    printArray(m2, n2, C);
    printf("\n+ i*\n\n");
    printArray(m2, n2, D);

    printf("\n=> (A, B) * (C, D) = (A + iB)(C + iD) = (AC - BD) + i(AD + BC) = \n\n");
    printArray(m1, n2, AC);
    printf("\n- \n\n");
    printArray(m1, n2, BD);
    printf("\n+ i*\n\n(\n\n");
    printArray(m1, n2, AD);
    printf("\n+ \n\n");
    printArray(m1, n2, BC);
    printf("\n)\n\n= \n\n");

    printArray(m1, n2, P);
    printf("\n+ i*\n\n");
    printArray(m1, n2, Q);

    printf("\n\n");
}

int** matricesMultiply(int m1, int n1, int n2, int** A, int** B)
{
    int** AB = (int**) calloc(m1, sizeof(int*));
    for(int i = 0; i < m1; i++)
        AB[i] = (int *) calloc(n2, sizeof(int));

    for(int i = 0; i < m1; i++)
    {
        for(int j = 0; j < n2; j++)
        {
            AB[i][j] = 0;
            for(int k = 0; k < n1; k++)
            {
                AB[i][j] = AB[i][j] + A[i][k] * B[k][j];
            }
        }
    }
    return AB; 
}

int flag = 0; // flag is used to track whether addition is performed or subtraction. So as flag
// is a global variable it'll retain its value in between function calls. First we wanna perform one addition operation as seen in
// main(), so flag = 0 and after addition flag is set to 1 so that we perform one subtraction operation. This usage of flag in this
// code is limited to this functionality only.

int** subAdd(int m1, int n2, int** A, int** B)
{
    int** R = (int**) calloc(m1, sizeof(int*));
    for(int i = 0; i < m1; i++)
        R[i] = (int *) calloc(n2, sizeof(int));

    for(int i = 0; i < m1; i++)
        for(int j = 0; j < n2; j++)
        {
            if(flag == 0)
                R[i][j] = A[i][j] - B[i][j];
            if(flag == 1)
                R[i][j] = A[i][j] + B[i][j];
        }
    flag = 1;    
    return R;
}

void printArray(int m, int n, int** ar)
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d ", ar[i][j]);
        }
        printf("\n");
    }
}

// If all the matrices are of size n x n then the total number of additions/subtractions = 2(n^2)(n-1) and the total number of multiplications = n^3.
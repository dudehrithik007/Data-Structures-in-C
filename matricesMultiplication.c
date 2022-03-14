#include <stdio.h>

void matrixMultiplication(int m, int n, int n1, int ar[][n], int br[][n]);

int main()
{
    printf("Multiplication of Two Matrices: \n\n");
    printf("Enter the Dimensions of Matrix 1 and Matrix 2: \n");
    int m1,n1,m2,n2;
    do
    {
        printf("m1 = ");
        scanf("%d", &m1);
        printf("n1 = ");
        scanf("%d", &n1);
        printf("m2 = ");
        scanf("%d", &m2);
        printf("n2 = ");
        scanf("%d", &n2);
        if(m1 < 1 || n1 < 1 || m2 < 1 || n2 < 1)
            printf("\nInvalid entry/entires. Enter Again:\n ");
    }while(m1 < 1 || n1 < 1 || m2 < 1 || n2 < 1);
    
    if(n1 == m2)
        {
            printf("\nMatrix Multiplication is possible.\n\n");
            int ar[m1][n1], br[m2][n2];
            printf("Enter Elements of Matrix 1:\n\n");
            for(int i = 0; i < m1 ; i++)
                for(int j = 0; j < n1; j++)
                {
                    printf("ar[%d][%d] = ", i+1, j+1);
                    scanf("%d", &ar[i][j]);
                }
            printf("\nEnter Elements of Matrix 2:\n");
            for(int i = 0; i < m2 ; i++)
                for(int j = 0; j < n2; j++)
                {
                    printf("br[%d][%d] = ", i+1, j+1);
                    scanf("%d", &br[i][j]);
                }
            matrixMultiplication(m1,n2, n1, ar, br);
        }
    else
        printf("Matrix Multiplication isn't possible. Orders don't match.\n");
    
    printf("\n\n");
    return 0;
}

void matrixMultiplication(int m, int n, int n1, int ar[][n], int br[][n])
{
    int cr[m][n];
    for(int i = 0; i < m ; i++)
        for(int j = 0; j < n; j++)
        {
            cr[i][j] = 0;
            for(int k = 0; k < n1; k++)
                cr[i][j] += ar[i][k] * br[k][j];
        }
    printf("\nObjective: \n\n");
    for(int i = 0; i < m ; i++)
    {
        for(int j = 0; j < n1; j++)
        {
            printf("%d ", ar[i][j]);
        }
        printf("\n");
    }
    printf("\n. \n\n");
    for(int i = 0; i < n1 ; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d ", br[i][j]);
        }
        printf("\n");
    }
    printf("\n= \n\n");
    for(int i = 0; i < m ; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d ", cr[i][j]);
        }
        printf("\n");
    }
}
#include<stdio.h>
#include<stdlib.h>

void valid(int *m, int *n);
void sparInput();
void spTranspose(int **spr);

void main()
{
    printf("\nProgram to input a matrix in the sparse format, store it, and find and store the transpose of the sparse matrix, display it and store and display the transpose in the usual format.\n\n");
    sparInput();
}

void sparInput()
{
    int m, n;
    printf("Enter the size of the Matrix:\n");
    printf("m = ");
    scanf("%d", &m);
    printf("n = ");
    scanf("%d", &n);

    valid(&m, &n);

    printf("\nEnter the number of non-zero elements: ");
    int nz;
    do
    {   
        scanf("%d", &nz);
        if(nz < 0)
            printf("\nThe number of non-zero elements is a whole number. Enter again: ");
    } while (nz < 0);

    int** spr = (int**) calloc(nz+1, sizeof(int*));
    for(int i = 0; i < nz+1; i++)
        spr[i] = (int*) calloc(3, sizeof(int));

    spr[0][0] = m;
    spr[0][1] = n;
    spr[0][2] = nz;

    printf("\nEnter i, j and the element[i][j] in this order itself into the sparse matrix: \n");
    for(int si = 1; si < nz+1; si++)
    {  
        printf("\ni = ");
        scanf("%d", &spr[si][0]);
        printf("j = ");
        scanf("%d", &spr[si][1]);
        printf("element[%d][%d] = ", spr[si][0], spr[si][1]);
        scanf("\n%d", &spr[si][2]);
    }

    printf("\nSparse Matrix Entered:\n");
    for(int i = 0; i < nz+1; i++)
    {
        for(int j = 0; j < 3; j++)
            printf("%d ", spr[i][j]);
        printf("\n");
    }

    spTranspose(spr); 
}

void valid(int *m, int *n)
{
    while (*m < 0 || *n < 0)
    {
        printf("\nNumber of Rows and Columns are Whole Numbers. Enter again:\n");
        printf("m = ");
        scanf("%d", m);
        printf("\n n = ");
        scanf("%d", n);
    }
}

void spTranspose(int **spr)
{
    int m = spr[0][0];
    int n = spr[0][1];
    int nz = spr[0][2];

    int **tr = (int**) calloc(n, sizeof(int*));
    for(int i = 0; i < n; i++)
        tr[i] = (int*) calloc(m, sizeof(int));
    
    /*
    // Use below if we used malloc above.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            tr[i][j] = 0; // Initialise all transpose matrix elements to 0.
    */

    /*  
    // Transpose and converting into sparse matrix simultaneously. 
    for(int i = 1; i < nz+1; i++)
    {
        tr[spr[i][1]][spr[i][0]] = spr[i][2];
    }
    */

    // Making Sparse Transpose from Sparse:
    int** sprt = (int**) calloc(nz+1, sizeof(int*));
    for(int i = 0; i < nz+1; i++)
        sprt[i] = (int*) calloc(3, sizeof(int));

    for(int i = 0; i < nz+1; i++)
    {
        sprt[i][2] = spr[i][2];
        sprt[i][1] = spr[i][0];
        sprt[i][0] = spr[i][1];
    }

    printf("\nSparse Transpose Matrix:\n");
    for(int i = 0; i < nz+1; i++)
    {
        for(int j = 0; j < 3; j++)
            printf("%d ", sprt[i][j]);
        printf("\n");
    }

    // Converting Sparse Transpose to (usual formatted) Transpose:
    for(int i = 1; i < nz+1; i++)
    {
        tr[sprt[i][0]][sprt[i][1]] = sprt[i][2];
    }

    printf("\nTranspose in Usual format: \n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            printf("%d ", tr[i][j]);
        printf("\n");
    }
    printf("\n");
}


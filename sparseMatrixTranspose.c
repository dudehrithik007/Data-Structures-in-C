#include<stdio.h>
#include<stdlib.h>

void valid(int *m, int *n);
void arInput();
void sparseMatrix(int **ar, int m, int n);
void spTranspose(int **spr);

void main()
{
    printf("\nProgram to input a matrix in the usual format, convert it to a sparse matrix, store it, and store the transpose of the sparse matrix and display and store the transpose in the usual format.\n\n");
    arInput();
}

void arInput()
{
    int m, n;
    printf("Enter the size of the Matrix:\n");
    printf("m = ");
    scanf("%d", &m);
    printf("n = ");
    scanf("%d", &n);

    valid(&m, &n);

    int** ar = (int**) calloc(m, sizeof(int*));
    for(int i = 0; i < m; i++)
        ar[i] = (int*) calloc(n, sizeof(int));

    printf("\nEnter Array Elements: \n");
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &ar[i][j]);

    printf("\nArray Entered:\n");
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%d ", ar[i][j]);
        printf("\n");
    }    
    
    sparseMatrix(ar, m, n);
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

int flag = 0;
void sparseMatrix(int **ar, int m, int n)
{
    // Counting the number of non-zero elements in the entered matrix.
    int nz = 0;
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            if(ar[i][j] != 0)
                nz++;
    
    int** spr = (int**) calloc(nz+1, sizeof(int*));
    for(int i = 0; i < nz+1; i++)
        spr[i] = (int*) calloc(3, sizeof(int));

    // Conversion into Sparse Matrix: Step 1
    spr[0][0] = m;
    spr[0][1] = n;
    spr[0][2] = nz;

    // Conversion into Sparse Matrix: Step 2
    int k = 1;
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            if(ar[i][j] != 0)
            {
                spr[k][0] = i;
                spr[k][1] = j;
                spr[k][2] = ar[i][j];
                k++;
            }

    printf("\nSparse Matrix:\n");
    for(int i = 0; i < nz+1; i++)
    {
        for(int j = 0; j < 3; j++)
            printf("%d ", spr[i][j]);
        printf("\n");
    }
    extern int flag;
    if(flag == 0)
    {
        flag = 1;
        spTranspose(spr); // Flag used here to call this function only once to transpose the given sparse matrix and not call it again when we wanna call sparseMatrix() to convert another matrix to a sparse matrix and print it. --1
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

    /*
    // Sorting Sparse Transpose Matrix using Bubble Sort:
    int temp;
    for(int i = 1; i < nz + 1; i++)
    {
        for(int j = 1; j < nz; j++)
        {
            if(sprt[j][0] > sprt[j+1][0] || (sprt[j][0] == sprt[j+1][0] && sprt[j][1] > sprt[j+1][1]))
            {   
                for(int k = 0; k < 3; k++)
                {
                    temp = sprt[j][k];
                    sprt[j][k] = sprt[j+1][k];
                    sprt[j+1][k] = temp;
                } 
            }
        }
    }
    */

    /*
    //Printing of Sparse Transpose Matrix without/after sort:
    printf("\nPrinting of Sparse Transpose Matrix after sort:\n");
    for(int i = 0; i < nz+1; i++)
    {
        for(int j = 0; j < 3; j++)
            printf("%d ", sprt[i][j]);
        printf("\n");
    }
    */

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

    /*
    printf("\nTranspose in Sparse format:");
    sparseMatrix(tr, n, m); // Explanation given above see: --1
    printf("\n");
    */
}


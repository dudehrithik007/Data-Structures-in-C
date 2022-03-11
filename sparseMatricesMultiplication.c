#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void valid(int *m, int *n);
int **arInput(int *m, int *n);
int **sparseMatrix(int **ar, int m, int n);
void spMult(int **sp1, int **sp2);

void main()
{
    printf("\nProgram to input two matrices in the usual format, convert them to sparse matrices, and store the multiplication of the sparse matrices and display it in the usual format.\n\n");
    
    int m1, n1, m2, n2;

    printf("Enter the size of the first matrix:\n");
    printf("m1 = ");
    scanf("%d", &m1);
    printf("n1 = ");
    scanf("%d", &n1);
    valid(&m1, &n1);

    printf("Enter the size of the second matrix:\n");
    printf("m2 = ");
    scanf("%d", &m2);
    printf("n2 = ");
    scanf("%d", &n2);
    valid(&m2, &n2);

    if(n1 == m2)
    {
        printf("\nMultiplication is possible.\n");
        printf("\nFor 1st Array:\n");
        int** ar1 = arInput(&m1, &n1);
        int** sp1 = sparseMatrix(ar1, m1, n1);
        printf("\nFor 2nd Array:\n");
        int** ar2 = arInput(&m2, &n2);
        int** sp2 = sparseMatrix(ar2, m2, n2);
        spMult(sp1, sp2);
    }
    else
        printf("\nMultiplication not possible.\n\n");
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

int **arInput(int *m, int *n)
{
    int** ar = (int**) calloc((*m), sizeof(int*));
    for(int i = 0; i < (*m); i++)
        ar[i] = (int*) calloc((*n), sizeof(int));

    printf("\nEnter Array Elements: \n");
    for(int i = 0; i < (*m); i++)
        for(int j = 0; j < (*n); j++)
            scanf("%d", &ar[i][j]);

    printf("\nArray Entered:\n");
    for(int i = 0; i < (*m); i++)
    {
        for(int j = 0; j < (*n); j++)
            printf("%d ", ar[i][j]);
        printf("\n");
    }    

    return ar;
}

int **sparseMatrix(int **ar, int m, int n)
{
    int nz = 0;
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            if(ar[i][j] != 0)
                nz++;
    
    int** spr = (int**) calloc(nz+1, sizeof(int*));
    for(int i = 0; i < nz+1; i++)
        spr[i] = (int*) calloc(3, sizeof(int));

    spr[0][0] = m;
    spr[0][1] = n;
    spr[0][2] = nz;

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
    return spr;
}

void spMult(int **sp1, int **sp2)
{
    int m = sp1[0][0]; // --1: Row Number of 1st matrix will be Row Number of the product matrix. 
    int n = sp2[0][1]; // --2: Column Number of 2nd matrix will be Column Number of the product matrix. 
    int nz1 = sp1[0][2];
    int nz2 = sp2[0][2];
    
    // --3: Initialising the product matrix with zeroes - used later 
    int** sps = (int**) calloc(m*n+1, sizeof(int*));
    for(int i = 0; i < m*n+1; i++)
        sps[i] = (int*) calloc(3, sizeof(int));
    
    sps[0][0] = m; // --1
    sps[0][1] = n; // --2
    
    int k = 0;
    int flag = 0;
    for(int i = 1; i < nz1+1; i++)
    {
        for(int j = 1; j < nz2+1; j++)
        {
            if(sp1[i][1] == sp2[j][0]) // Checking whether column number of 1st matrix is equal to the row number of the 2nd matrix. If they match then only we multiply as sparse matrix only contains non-zero elements so multiplying with 0 and adding 0 has been avoided here due to the use of sparse matrices.
            {
                flag = 0;
                for(int p = 1; p < k+1; p++) // Here onwards: Checking until the elements already present in the product matrix(that's why k+1 is used here) whether the current i,j or the element position in the product matrix exists. If yes, then we add the multiplication of the corresponding elements to the value at the current i,j in the product matrix. --4
                {
                    if(sp1[i][0] == sps[p][0] && sps[p][1] == sp2[j][1])
                    {
                        sps[p][2] = sps[p][2] + sp1[i][2] * sp2[j][2]; // Here we add the multiplication obtained for current i,j th position to the element in the product matrix we obtained earlier for the current i,j th position. --5 
                        flag = 1; // flag tracks what is mentioned in the above comment. --4
                    }
                }
                if(flag == 0) // If flag is 0 that means the current i,j doesn't exist in the product matrix and we have to add a new row to it. (Therefore, it'll be 0 + Current value = Current value)
                {
                    k++;
                    sps[k][0] = sp1[i][0];
                    sps[k][1] = sp2[j][1];
                    sps[k][2] = sps[k][2] + sp1[i][2] * sp2[j][2]; // Here "sps[k][2] = sps[k][2] + ..." signifies how initialising the product matrix with 0s helps. --3 --5
                }     
            } 
        }
    }
    /* --5: The multiplication and addition done (LHS = LHS + RHS) illustrates how we multiply 2 matrices that is the for the
    // i,j th value in the product matrix, the ith row of 1st matrix, that is the corresponding elements of the ith row
    // in the 1st matrix are multiplied with the jth column of 2nd matrix, that is with the corresponding elements of the jth row
    // in the 2nd matrix and then the values obtained are added to get the final result.
    */

    int nz3=0;
    for(int i = 1; i < m*n+1; i++)
    {
        if(sps[i][2] != 0) // One advantage of --3
            nz3++; // Counting the number of non-zero elements in the product/resultant matrix.
    }

    sps[0][2] = nz3;

    printf("\nSparse Product/Resultant Matrix:\n");
    for(int i = 0; i < nz3+1; i++)
    {
        for(int j = 0; j < 3; j++)
            printf("%d ", sps[i][j]);
        printf("\n");
    }

    int **tr = (int**) calloc(m, sizeof(int*));
    for(int i = 0; i < m; i++)
        tr[i] = (int*) calloc(n, sizeof(int));

    for(int i = 1; i < nz3+1; i++)
    {
        tr[sps[i][0]][sps[i][1]] = sps[i][2]; // Converting Sparse Product/Resultant Matrix to Usual Product/Resultant Matrix.
    }

    printf("\nMultiplication in Usual format: \n");
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%d ", tr[i][j]);
        printf("\n");
    }
    printf("\n");

}
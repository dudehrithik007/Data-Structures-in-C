#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void valid(int *m, int *n);
int **sparInput(int *m, int *n, int *nz);
void spAdd(int **sp1, int **sp2);

void main()
{
    printf("\nProgram to input two matrices in the sparse format, store them, and find and store the addition of the sparse matrices entered, display it, and store and display the addition in the usual format.\n\n");
    
    int m1, n1, m2, n2, nz1, nz2;

    printf("Enter the size of the first matrix:\n");
    printf("m1 = ");
    scanf("%d", &m1);
    printf("n1 = ");
    scanf("%d", &n1);
    valid(&m1, &n1);
    printf("\nEnter the number of non-zero elements in the first matrix: ");
    do
    {   
        scanf("%d", &nz1);
        if(nz1 < 0)
            printf("\nThe number of non-zero elements is a whole number. Enter again: ");
    } while (nz1 < 0);

    printf("\nEnter the size of the second matrix:\n");
    printf("m2 = ");
    scanf("%d", &m2);
    printf("n2 = ");
    scanf("%d", &n2);
    valid(&m2, &n2);
    printf("\nEnter the number of non-zero elements in the second matrix: ");
    do
    {   
        scanf("%d", &nz2);
        if(nz2 < 0)
            printf("\nThe number of non-zero elements is a whole number. Enter again: ");
    } while (nz2 < 0);

    if(m1 == m2 && n1 == n2)
    {
        printf("\nAddition is possible.\n");

        printf("\nFor 1st Sparse Matrix:\n");
        int** sp1 = sparInput(&m1, &n1, &nz1);
        printf("\nFor 2nd Matrix:\n");
        int** sp2 = sparInput(&m2, &n2, &nz2);

        spAdd(sp1, sp2);
    }
    else
        printf("\nAddition not possible.\n\n");
}

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

int **sparInput(int *m, int *n, int *nz)
{
    int** spr = (int**) calloc(*(nz)+1, sizeof(int*));
    for(int i = 0; i < *(nz)+1; i++)
        spr[i] = (int*) calloc(3, sizeof(int));

    spr[0][0] = *m;
    spr[0][1] = *n;
    spr[0][2] = *nz;

    printf("\nEnter i, j and the element[i][j] in this order itself into the sparse matrix: \n");
    for(int si = 1; si < *(nz)+1; si++)
    {  
        printf("\ni = ");
        scanf("%d", &spr[si][0]);
        printf("j = ");
        scanf("%d", &spr[si][1]);
        printf("element[%d][%d] = ", spr[si][0], spr[si][1]);
        scanf("\n%d", &spr[si][2]);
    }

    printf("\nSparse Matrix Entered:\n");
    for(int i = 0; i < *(nz)+1; i++)
    {
        for(int j = 0; j < 3; j++)
            printf("%d ", spr[i][j]);
        printf("\n");
    }

    return spr;
}

void spAdd(int **sp1, int **sp2)
{
    int m = sp1[0][0];
    int n = sp1[0][1];
    int nz1 = sp1[0][2];
    int nz2 = sp2[0][2];
    
    // Using calloc() to initialise the sparse array with all zeroes as mentioned later: --1
    int** sps = (int**) calloc(m*n+1, sizeof(int*));
    for(int i = 0; i < m*n+1; i++)
        sps[i] = (int*) calloc(3, sizeof(int));
    
    sps[0][0] = m;
    sps[0][1] = n;

    int k = 1;
    int flag = 0; // Flag is used to track whether we have found a match, that is, matching index numbers in both the sparse matrix so that we can add those two non-zero values.
    for(int i = 1; i < nz1+1; i++)
    {
        for(int j = 1; j < nz2+1; j++)
        {
            flag = 0;
            if(sp1[i][0] == sp2[j][0] && sp1[i][1] == sp2[j][1]) // Same Indices which are in both sp1 and sp2, the elements(Elements of Sparse Matrices(Non-Zero Elements)) at these positions are added and stored in the resultant matrix. 
            {
                sps[k][0] = sp1[i][0];
                sps[k][1] = sp1[i][1];
                sps[k][2] = sp1[i][2] + sp2[j][2]; // For subtraction put - here instead of +
                k++;
                flag = 1;
                break;
            }
        }
        if(flag == 1)
            continue;
        else // Different Indices - here comparing first matrix with all of the second - which are in sp1 and not in sp2 - the elements(Elements of Sparse Matrices(Non-Zero Elements)) at these positions are put as they are in the resultant matrix as 0 + something = something.
        {
            // For subtraction: These statements are same as addition as something - 0 = something.
            sps[k][0] = sp1[i][0];
            sps[k][1] = sp1[i][1];
            sps[k][2] = sp1[i][2];
            k++;
        }
    }

    for(int i = 1; i < nz2+1; i++)
    {
        for(int j = 1; j < nz1+1; j++)
        {
            flag = 0;
            if(sp2[i][0] == sp1[j][0] && sp2[i][1] == sp1[j][1]) // Same Indices which are in both sp1 and sp2, the elements(Elements of Sparse Matrices(Non-Zero Elements)) at these positions are added above and stored in the resultant matrix. Here we ignore them for the below else part. Read Comment:
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
            continue;
        else // Different Indices - here comparing second matrix with all of the first - which are in sp2 and not in sp1 - the elements(Elements of Sparse Matrices(Non-Zero Elements)) at these positions are put as they are in the resultant matrix as 0 + something = something.
        {
            // For subtraction: The LHS of these statements will be equal to -RHS because 0 - something = -something.
            sps[k][0] = sp2[i][0];
            sps[k][1] = sp2[i][1];
            sps[k][2] = sp2[i][2];
            k++;
        }
    }

    int nz3=0;
    for(int i = 1; i < nz1+nz2; i++)
    {
        if(sps[i][2] != 0) // That is why we initialised the sparse array using calloc(). --1
            nz3++; // Counting the number of non-zero elements obtained in sps by the sum of sp1 and sp2.
    }

    sps[0][2] = nz3;

    printf("\nSparse Addition Matrix:\n");
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
        tr[sps[i][0]][sps[i][1]] = sps[i][2]; // Conversion of Sparse Addition Matrix to Usual Addition Matrix.
    }

    printf("\nAddition in Usual format: \n");
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%d ", tr[i][j]);
        printf("\n");
    }
    printf("\n");
}
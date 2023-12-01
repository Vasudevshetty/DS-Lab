/*Create a pointer to two dimensional array of integers, Write function to read and display the 2D array using pointer.*/

#include<stdio.h>

void read(int *ptr, int m, int n){
    printf("Enter the elements of the 2D array : \n");
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", ptr + i*n + j);
}

void display(int *ptr, int m, int n){
    printf("Elements of the array are : \n");
    for(int i = 0; i < m; i++){ 
        for(int j = 0; j < n; j++)
            printf("%d ", *(ptr + i*n + j));
        printf("\n");
    }
}

int main(){
    int m, n;
    printf("Enter the rows and colums of the matrix : ");
    scanf("%d %d", &m, &n);

    int array[m][n];
    int *ptr = array[0];

    read(ptr, m, n);
    display(ptr, m, n);

    return 0;
}
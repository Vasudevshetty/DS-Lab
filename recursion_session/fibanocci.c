/*Function to print all the fibanocci sequence for the no of terms specified.*/

#include<stdio.h>

int fibanocci(int n){
    return n == 0 || n == 1 ? n : fibanocci(n - 1) + fibanocci(n - 2);
}

int main(){
    int n;
    printf("Enter n : ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        printf("%d ", fibanocci(i));
    return 0;
}
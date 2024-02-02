#include<stdio.h>

/*function to find the sum of the n natural numbers.*/

int sum(int n){
    return n == 0 ? 0 : n + sum(n - 1);
}

/*function to find the factorial of the number.*/

int fact(int n){
    return n == 0 ? 1 : n * fact(n - 1);
}

int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Sum of the n natural no is : %d\n", sum(n));
    printf("fact of the n no is : %d", fact(n));
    return 0;
}
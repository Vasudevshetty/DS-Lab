#include<stdio.h>

void toh(int n, char src, char aux, char dest){
    if(n == 0)
        return;
    toh(n - 1, src, dest, aux);
    printf("%d disc from %c to %c\n", n, src, dest);
    toh(n - 1, aux, src, dest);
}

int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    toh(n, 'A', 'B', 'C');
    return 0;
}
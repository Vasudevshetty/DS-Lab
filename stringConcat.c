/*Create two pointers called ps1 and ps2 to two strings, REad the contents using pointers and also write a function 
strcat(ps1, ps2) which concatenates second string to the end of the first string using pointers ps1 and ps2*/

#include<stdio.h>

void strCat(char *ps1, char *ps2){
    while(*ps1 != '\0') ps1++;
    int i = 0;
    while(*ps2 != '\0'){
        *(ps1+i) = *ps2;
        ps2++;
        i++;
    }
    *(ps1+i) = '\0';
}

int main(){
    char str1[10], str2[10];
    printf("Enter two strings : ");
    scanf("%s %s", str1, str2);

    strCat(str1, str2);

    printf("Concatinated string is %s\n", str1);
    return 0;
}
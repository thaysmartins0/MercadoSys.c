#include <stdio.h>

int main(){
    int a, b,c;
    printf("digite o primeiro numero, ele sera chamado de A:\n");
    scanf("%d", &a);
    printf("agora digite o segundo numero, ele sera chamado de B:\n");
    scanf("%d", &b);
    c=a;
    a=b;
    b=c;
    printf("agora perceba que os valores foram invertidos. A se tornou B, e B se tornou A: a=%d, b= %d", a, b);


}
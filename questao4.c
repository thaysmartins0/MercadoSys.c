#include <stdio.h>

int main(){
int x;
int y;
int soma, produto, quociente;
    printf("digite um número: ");
    scanf("%d", &x);
    printf("digite outro número: ");
    scanf("%d", &y);
    soma= x+y;
    produto= x*y;
    quociente=x/y;
    printf("a soma dos números é: %d\n", soma);
    printf("o produto entre eles é: %d\n", produto);
    printf("o quociente entre eles é: %d\n", quociente);   

}
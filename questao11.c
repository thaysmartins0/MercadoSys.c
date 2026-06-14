#include <stdio.h>
#include <math.h>

int main(){
float valorCompra, valorPago, trocoTotal;
int trocoCentavos;
int resto;
int nota100, nota50, nota20, nota10, nota5, nota2;
int cents50, cents25, cents10, cents5;

    printf("auxiliar de caixa de supermercado\n");
    printf("voce precisa informar o valor da compra: \n");
    scanf("%f", &valorCompra);
    printf("agora informe o valor pago pelo cliente, o valor entregue pelo cliente não pode ser menor do que o valor da compra: \n");
    scanf("%f", &valorPago);
    
    if (valorPago<valorCompra){
        printf ("ERRO: valor INSUFICIENTE. faltam %.2f reais \n", valorCompra-valorPago);
    }
    trocoTotal= valorPago-valorCompra;
    printf("troco total: %.2f\n", trocoTotal);
    //cedulas
    nota100 = trocoCentavos/1000;
    resto = trocoCentavos % 10000;
    nota50 = resto / 5000;
    resto = resto % 5000;
    nota20 = resto / 2000;
    resto = resto % 2000;
    nota10 = resto / 1000;
    resto = resto % 1000;
    nota5 = resto / 500;
    resto = resto % 500;
    nota2 = resto / 200;
    resto = resto % 200;

    //moedas
    cents50 = resto / 50;
    resto = resto %50;
    cents25 = resto / 25;
    resto = resto %25;
    cents10 = resto / 10;
    resto = resto %10;
    cents5 = resto / 5;
   
    printf("troco:\n");
    printf("%d nota(s) de 100\n", nota100);
    printf("%d nota(s) de 50\n", nota50);
    printf("%d nota(s) de 20\n", nota20);
    printf("%d nota(s) de 10\n", nota10);
    printf("%d nota(s) de 5\n", nota5);
    printf("%d nota(s) de 20\n", nota2);

    printf("%d moeda(s) de 50\n", cents50);
    printf("%d moeda(s) de 25\n", cents25);
    printf("%d moeda(s) de 10\n", cents10);
      printf("%d moeda(s) de 5", cents5);
}
#include <stdio.h>
#include <math.h>

int main(){
int valor, moedas;
int cedula2, cedula5, cedula10, cedula20, cedula50, cedula100;
    printf("digite o valor que deseja receber \n");
    printf("obs: o valor deve ser positivo: ");
      scanf("%i", &valor);
    
    cedula100=valor/100; valor%=100;
    cedula50=valor/50; valor%=50;
    cedula20=valor/20; valor%=20;
    cedula10=valor/10; valor%=10;
    cedula5=valor/5; valor%=5;
    cedula2=valor/2; valor%=2;
    moedas=valor/1; valor%=1;
    printf("Para o saque desse valor, voce recebera:\n", &valor);
    printf("celulas de 100: %d\n", cedula100);
    printf("celulas de 50:%d\n ", cedula50);
    printf("celulas de 20:%d\n ", cedula20);
    printf("celulas de 10:%d\n ", cedula10);
    printf("celulas de 5:%d\n ", cedula5);
    printf("cedulas de 2:%d\n", cedula2);
    printf("o resto será %d\n moeda(s).", moedas);
    
}

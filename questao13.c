#include <stdio.h>

int main(){
    float precoFabrica, valorImpostos,valorRevendedor, precoFinal;
    printf("informe o preco de fabrica do automovel: \n");
    scanf("%f", &precoFabrica);
    valorImpostos=precoFabrica*0.45;
    valorRevendedor=precoFabrica*0.28;
    precoFinal=precoFabrica+valorRevendedor+valorImpostos;
    printf("o preco do automovel ficou %.2f reais\n", precoFinal);
    
}
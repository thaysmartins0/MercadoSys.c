#include <stdio.h>

int main(){
float centimetros, polegadas;
const float cm_por_polegada=2.54;

    printf("digite quantos centímetros quiser: ");
    scanf("%f", &centimetros);
    polegadas= centimetros/cm_por_polegada;
    printf("%f centimetros são %2.f polegadas.", centimetros, polegadas);

}
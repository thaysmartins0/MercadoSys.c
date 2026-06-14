#include <stdio.h>

int main(){
float raio, altura, area, volume;
float pi=3.14;
    printf("para calcular o raio e o volume de um cilindro vc deve fornecer as seguintes informações:\n");
    printf("digite o raio do seu cilindro: ");
    scanf("%f", &raio);
    printf("agora digite a altura: ");
    scanf("%f", &altura);
    area= 2*pi*raio*(raio + altura);
    volume=pi*raio*raio*altura;
    printf("a area do seu cilindro é: %.2f\n", area);
    printf("o volume do seu cilindro é: %.2f\n", volume);


}
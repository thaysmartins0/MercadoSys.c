#include <stdio.h>

int main(){
float salariofixo, totalvendas, comissao, salariofinal;
    printf("SISTEMA DE VENDAS E COMISSAO\n");
    printf(" para voce saber quanto o vendedor faturou com as comissoes vc deve fornecer os seguintes dados: \n");
    printf("informe o valor do salario fixo: \n");
    scanf("%f", &salariofixo);
    printf("informe o total de vendas mensais do vendedor: \n");
    scanf("%f", &totalvendas);
    comissao = totalvendas*0.15;
    salariofinal=salariofixo*comissao;
    printf(" o salario fixo do vendedor e: %.2f\n", salariofixo);
    printf("o salario final do vendedor e: %.2f\n" , salariofinal);

}
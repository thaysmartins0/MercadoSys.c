#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Declaração dos outros módulos
void menu_cliente(void);
void menu_pedido(void);
void menu_produto(void);
// ==========================================
// CONSTANTES E ESTRUTURAS
// ==========================================
#define MAX_NOME 80
#define MAX_CAT 50

// Envelopamento com #pragma pack para portabilidade absoluta e prevenção de Struct Padding
#pragma pack(push, 1)
typedef struct {
    int codigo;
    char nome[MAX_NOME];
    char categoria[MAX_CAT];
    float preco;
    int quantidade;
    char validade[11]; // Formato DD/MM/AAAA
    int status;        // 1: Ativo, 0: Inativo (Soft Delete)
} Produto;
#pragma pack(pop)

// ==========================================
// FUNÇÕES AUXILIARES DE SEGURANÇA
// ==========================================

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int string_esta_vazia(const char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str)) return 0;
        str++;
    }
    return 1;
}

int ler_string_segura(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) == NULL) {
        return 0;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        limpar_buffer();
    }
    return 1;
}

// Ajuste Fino de UX: Normalização para busca case-insensitive
void string_para_minusculo(char *str) {
    for (int i = 0; str[i]; i++) str[i] = tolower((unsigned char)str[i]);
}

int proximo_codigo_produto() {
    FILE *file = fopen("produtos.dat", "rb");
    if (file == NULL) return 1;

    Produto p;
    int max_id = 0;
    while (fread(&p, sizeof(Produto), 1, file) == 1) {
        if (p.codigo > max_id) max_id = p.codigo;
    }
    fclose(file);
    return max_id + 1;
}

// ==========================================
// OPERAÇÕES DO MÓDULO
// ==========================================

void cadastrar_produto() {
    Produto p;
    p.codigo = proximo_codigo_produto();
    p.status = 1;

    printf("Nome do Produto: ");
    if (!ler_string_segura(p.nome, MAX_NOME) || string_esta_vazia(p.nome)) {
        printf("[ERRO] Entrada invalida.\n"); return;
    }

    printf("Categoria: ");
    if (!ler_string_segura(p.categoria, MAX_CAT) || string_esta_vazia(p.categoria)) {
        printf("[ERRO] Entrada invalida.\n"); return;
    }

    printf("Preco Unitario: ");
    if (scanf("%f", &p.preco) != 1 || p.preco < 0) {
        limpar_buffer(); printf("[ERRO] Preco invalido.\n"); return;
    }
    limpar_buffer();

    printf("Quantidade em Estoque: ");
    if (scanf("%d", &p.quantidade) != 1 || p.quantidade < 0) {
        limpar_buffer(); printf("[ERRO] Quantidade invalida.\n"); return;
    }
    limpar_buffer();

    printf("Data de Validade (DD/MM/AAAA): ");
    if (!ler_string_segura(p.validade, 11) || string_esta_vazia(p.validade)) {
        printf("[ERRO] Data invalida.\n"); return;
    }

    FILE *file = fopen("produtos.dat", "ab");
    if (file == NULL) {
        printf("[ERRO] Nao foi possivel abrir o arquivo.\n"); return;
    }

    if (fwrite(&p, sizeof(Produto), 1, file) == 1) {
        printf("[SUCESSO] Produto cadastrado com ID %d!\n", p.codigo);
    } else {
        printf("[ERRO] Falha ao gravar no disco.\n");
    }
    fclose(file);
}

void exibir_ficha_produto(const Produto *p) {
    printf("   ╔══════════════════════════════════════════════════╗\n");
    printf("   ║                DETALHES DO PRODUTO               ║\n");
    printf("   ╠══════════════════════════════════════════════════╣\n");
    printf("   ║  ID          : %-38d  ║\n", p->codigo);
    printf("   ║  Nome        : %-38.38s  ║\n", p->nome);
    printf("   ║  Categoria   : %-38.38s  ║\n", p->categoria);
    printf("   ║  Preco       : R$ %-35.2f ║\n", p->preco);
    printf("   ║  Estoque     : %-38d  ║\n", p->quantidade);
    printf("   ║  Validade    : %-38.10s  ║\n", p->validade);
    printf("   ║  Status      : %-38.38s  ║\n", p->status ? "Ativo" : "Inativo");
    printf("   ╚══════════════════════════════════════════════════╝\n");
}

void consultar_produto() {
    FILE *file = fopen("produtos.dat", "rb");
    if (file == NULL) { printf("[AVISO] Nenhum produto cadastrado.\n"); return; }

    char termo_busca[MAX_NOME];
    printf("Digite o nome do produto para buscar: ");
    if (!ler_string_segura(termo_busca, MAX_NOME) || string_esta_vazia(termo_busca)) { 
        fclose(file); return; 
    }
    
    string_para_minusculo(termo_busca);

    Produto p;
    int encontrado = 0;
    while (fread(&p, sizeof(Produto), 1, file) == 1) {
        if (p.status == 0) continue;

        char nome_min[MAX_NOME];
        strcpy(nome_min, p.nome);
        string_para_minusculo(nome_min);

        if (strstr(nome_min, termo_busca) != NULL) { 
            exibir_ficha_produto(&p); 
            encontrado = 1; 
        }
    }
    if (!encontrado) printf("Nenhum produto ativo encontrado.\n");
    fclose(file);
}

void alterar_produto() {
    FILE *file = fopen("produtos.dat", "r+b");
    if (file == NULL) { printf("[ERRO] Arquivo nao encontrado.\n"); return; }

    int id_busca;
    printf("Digite o ID do produto para alterar: ");
    
    int resultado_scan = scanf("%d", &id_busca);
    if (resultado_scan == EOF) {
        fclose(file); return;
    } else if (resultado_scan != 1) { 
        limpar_buffer(); fclose(file); printf("[ERRO] ID invalido.\n"); return; 
    }
    limpar_buffer();

    Produto p;
    int encontrado = 0;
    while (fread(&p, sizeof(Produto), 1, file) == 1) {
        if (p.codigo == id_busca && p.status == 0) {
            printf("[ERRO] Produto encontra-se inativo no sistema e nao pode ser modificado.\n");
            encontrado = 1;
            break;
        }

        if (p.codigo == id_busca && p.status == 1) {
            encontrado = 1;
            printf("\nDados Atuais:\n");
            exibir_ficha_produto(&p);

            printf("\nNovo Nome: ");
            if (!ler_string_segura(p.nome, MAX_NOME) || string_esta_vazia(p.nome)) {
                printf("[ERRO] Alteracao abortada: Nome invalido.\n"); fclose(file); return;
            }
            
            printf("Nova Categoria: ");
            if (!ler_string_segura(p.categoria, MAX_CAT) || string_esta_vazia(p.categoria)) {
                printf("[ERRO] Alteracao abortada: Categoria invalida.\n"); fclose(file); return;
            }

            printf("Novo Preco: ");
            if (scanf("%f", &p.preco) != 1 || p.preco < 0) {
                limpar_buffer(); printf("[ERRO] Preco invalido. Alteracao abortada.\n"); fclose(file); return;
            }
            limpar_buffer();

            printf("Nova Quantidade: ");
            if (scanf("%d", &p.quantidade) != 1 || p.quantidade < 0) {
                limpar_buffer(); printf("[ERRO] Quantidade invalida. Alteracao abortada.\n"); fclose(file); return;
            }
            limpar_buffer();

            // CORREÇÃO 1: Inclusão da atualização do campo estrutural de validade omisso
            printf("Nova Data de Validade (DD/MM/AAAA): ");
            if (!ler_string_segura(p.validade, 11) || string_esta_vazia(p.validade)) {
                printf("[ERRO] Alteracao abortada: Data invalida.\n"); fclose(file); return;
            }

            fseek(file, -(long)sizeof(Produto), SEEK_CUR);
            if (fwrite(&p, sizeof(Produto), 1, file) == 1) {
                // CORREÇÃO 2: Consistência de idioma removendo o Spanglish da interface
                printf("[SUCESSO] Produto atualizado com sucesso!\n");
            } else {
                printf("[ERRO] Falha ao atualizar dados.\n");
            }
            break;
        }
    }
    if (!encontrado) printf("[ERRO] ID %d nao localizado.\n", id_busca);
    fclose(file);
}

void excluir_produto() {
    FILE *file = fopen("produtos.dat", "r+b");
    if (file == NULL) { printf("[ERRO] Arquivo nao encontrado.\n"); return; }

    int id_busca;
    printf("Digite o ID do produto para inativar: ");
    
    int resultado_scan = scanf("%d", &id_busca);
    if (resultado_scan == EOF) {
        fclose(file); return;
    } else if (resultado_scan != 1) { 
        limpar_buffer(); fclose(file); printf("[ERRO] ID invalido.\n"); return; 
    }
    limpar_buffer();

    Produto p;
    int encontrado = 0;
    while (fread(&p, sizeof(Produto), 1, file) == 1) {
        if (p.codigo == id_busca && p.status == 0) {
            printf("[AVISO] Este produto ja se encontra inativado no sistema.\n");
            encontrado = 1;
            break;
        }

        if (p.codigo == id_busca && p.status == 1) {
            encontrado = 1;
            p.status = 0; // Soft Delete
            
            fseek(file, -(long)sizeof(Produto), SEEK_CUR);
            if (fwrite(&p, sizeof(Produto), 1, file) == 1) {
                printf("[SUCESSO] Produto inativado com sucesso.\n");
            } else {
                printf("[ERRO] Falha ao atualizar status.\n");
            }
            break;
        }
    }
    if (!encontrado) printf("[ERRO] ID %d nao localizado.\n", id_busca);
    fclose(file);
}

// ==========================================
// CONTROLE PRINCIPAL DO MÓDULO
// ==========================================

void menu_produtos() {
    int opcao;
    do {
        printf("\n=== GESTAO DE ESTOQUE / PRODUTOS ===\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Consultar Produto\n");
        printf("3. Alterar Produto\n");
        printf("4. Inativar Produto (Excluir)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        
        int resultado = scanf("%d", &opcao);

        if (resultado == EOF) {
            printf("\n[AVISO] Interrupcao detectada no fluxo de entrada. Encerrando modulo...\n");
            opcao = 0; 
        } else if (resultado != 1) { 
            limpar_buffer();
            opcao = -1;      
        } else {
            limpar_buffer();
        }

        switch(opcao) {
    case 1:
        menu_produto();
        // Aqui roda o seu código de produtos que já está aí
        break;
    case 2:
        menu_cliente(); // Chama o código do arquivo modulo_cliente.c
        break;
    case 3:
        menu_pedido();  // Chama o código do arquivo modulo_pedido.c
        break;
    case 0:
        printf("Saindo do sistema...\n");
        break;
    default:
        printf("Opção inválida!\n");
        } 
    } while (opcao !=0);
}
void menu_produto(void) {
    int opcao_prod = -1;
    do {
        printf("\n=============================\n");
        printf("--- MÓDULO DE PRODUTOS ---\n");
        printf("=============================\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Consultar Produto\n");
        printf("3. Alterar Produto\n");
        printf("4. Excluir Produto\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("=============================\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao_prod) != 1) {
            limpar_buffer();
            opcao_prod = -1;
        } else {
            limpar_buffer();
        }

        switch (opcao_prod) {
            case 1: cadastrar_produto(); break;
            case 2: consultar_produto(); break;
            case 3: alterar_produto(); break;
            case 4: excluir_produto(); break;
            case 0: printf("Voltando ao menu principal...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao_prod != 0);
}

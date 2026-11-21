/*
 * GERENCIADOR DE TAREFAS
 *
 * Cada tarefa é um REGISTRO (struct) com data, horario, descrição
 * e situacao de conclusao. O vetor "agenda" armazena varios registros.
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_TAREFAS 100

/* REGISTRO: agrupa campos diferentes que pertencem a uma tarefa. */
typedef struct {
    char data[11];        /* DD/MM/AAAA + caractere final */
    char horario[6];      /* HH:MM + caractere final */
    char descricao[100];  /* Descricao digitada pelo usuario */
    bool concluida;       /* true = concluida; false = pendente */
} Tarefa;

/* Vetor de registros e contador de tarefas efetivamente cadastradas. */
Tarefa agenda[MAX_TAREFAS];
int totalTarefas = 0;

/* Descarta o restante da linha deixado no teclado depois de scanf. */
void limparBuffer(void) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
        /* Os caracteres sao descartados. */
    }
}

/* Le uma linha inteira, inclusive espaços, respeitando o tamanho do vetor. */
void lerTexto(char texto[], int tamanho) {
    if (fgets(texto, tamanho, stdin) != NULL) {
        /* Remove o Enter armazenado por fgets. */
        texto[strcspn(texto, "\n")] = '\0';
    } else {
        texto[0] = '\0';
    }
}

/*
 * Le data e horário para o registro indicado por indice.
 * Verifica formato e faixas numericas; não valida o calendario completo.
 */
void lerDataEHora(int indice) {
    char dataDigitada[100];
    char horarioDigitado[100];
    int dia, mes, ano, hora, minuto;
    int valido;

    do {
        printf("Data (DD/MM/AAAA): ");
        lerTexto(dataDigitada, sizeof(dataDigitada));
        valido = 0;

        /* Confere tamanho, separadores e se os demais caracteres são digitos. */
        if (strlen(dataDigitada) == 10 &&
            dataDigitada[2] == '/' && dataDigitada[5] == '/' &&
            isdigit((unsigned char)dataDigitada[0]) &&
            isdigit((unsigned char)dataDigitada[1]) &&
            isdigit((unsigned char)dataDigitada[3]) &&
            isdigit((unsigned char)dataDigitada[4]) &&
            isdigit((unsigned char)dataDigitada[6]) &&
            isdigit((unsigned char)dataDigitada[7]) &&
            isdigit((unsigned char)dataDigitada[8]) &&
            isdigit((unsigned char)dataDigitada[9])) {

            /* Converte cada par de caracteres em um numero inteiro. */
            dia = (dataDigitada[0] - '0') * 10 + (dataDigitada[1] - '0');
            mes = (dataDigitada[3] - '0') * 10 + (dataDigitada[4] - '0');
            ano = (dataDigitada[6] - '0') * 1000
                + (dataDigitada[7] - '0') * 100
                + (dataDigitada[8] - '0') * 10
                + (dataDigitada[9] - '0');

            if (dia >= 1 && dia <= 31 &&
                mes >= 1 && mes <= 12 &&
                ano >= 2000 && ano <= 2100) {
                valido = 1;
            }
        }

        if (!valido) {
            printf("Data invalida. Use DD/MM/AAAA.\n");
        }
    } while (!valido); /* Repete até a data ser considerada válida. */

    /* O ponto acessa um campo da struct armazenada na posicao indice. */
    strcpy(agenda[indice].data, dataDigitada);

    do {
        printf("Horário (HH:MM): ");
        lerTexto(horarioDigitado, sizeof(horarioDigitado));
        valido = 0;

        if (strlen(horarioDigitado) == 5 &&
            horarioDigitado[2] == ':' &&
            isdigit((unsigned char)horarioDigitado[0]) &&
            isdigit((unsigned char)horarioDigitado[1]) &&
            isdigit((unsigned char)horarioDigitado[3]) &&
            isdigit((unsigned char)horarioDigitado[4])) {

            hora = (horarioDigitado[0] - '0') * 10 + (horarioDigitado[1] - '0');
            minuto = (horarioDigitado[3] - '0') * 10 + (horarioDigitado[4] - '0');

            if (hora >= 0 && hora <= 23 && minuto >= 0 && minuto <= 59) {
                valido = 1;
            }
        }

        if (!valido) {
            printf("Horário inválido. Use HH:MM.\n");
        }
    } while (!valido);

    strcpy(agenda[indice].horario, horarioDigitado);
}

/* Cadastra uma tarefa na próxima posicão livre do vetor. */
void adicionar(void) {
    if (totalTarefas >= MAX_TAREFAS) {
        printf("Agenda cheia. Limite de %d tarefas.\n", MAX_TAREFAS);
        return;
    }

    printf("\n________NOVA TAREFA________\n");

    /* Em C, o primeiro indice do vetor é zero.
       totalTarefas indica exatamente a próxima posicão livre. */
    lerDataEHora(totalTarefas);

    printf("Descricao da tarefa: ");
    lerTexto(agenda[totalTarefas].descricao,
             sizeof(agenda[totalTarefas].descricao));

    agenda[totalTarefas].concluida = false;
    totalTarefas++;

    printf("Tarefa cadastrada com sucesso!\n");
}

/* Mostra todos os registros ja cadastrados. */
void listar(void) {
    int i;

    printf("\n________TAREFAS CADASTRADAS________\n");

    if (totalTarefas == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    /* for repete uma vez para cada tarefa cadastrada. */
    for (i = 0; i < totalTarefas; i++) {
        char status;

        if (agenda[i].concluida == true) {
            status = 'X';
        } else {
            status = ' ';
        }

        printf("%d - [%c] %s as %s | %s\n",
               i + 1, status, agenda[i].data,
               agenda[i].horario, agenda[i].descricao);
    }
}

/* Altera o campo concluida do registro selecionado. */
void concluir(void) {
    int id;

    listar();
    if (totalTarefas == 0) {
        return;
    }

    printf("Número da tarefa para concluir (0 cancela): ");
    if (scanf("%d", &id) != 1) {
        printf("Entrada inválida. Digite um número.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    if (id == 0) {
        printf("Operação cancelada.\n");
    } else if (id >= 1 && id <= totalTarefas) {
        /* O usuario conta a partir de 1; o vetor C comeca em 0. */
        agenda[id - 1].concluida = true;
        printf("Tarefa marcada como concluida.\n");
    } else {
        printf("Número de tarefa inválido.\n");
    }
}

/* Atualiza os campos de uma tarefa existente. */
void editar(void) {
    int id;
    int indice;

    listar();
    if (totalTarefas == 0) {
        return;
    }

    printf("Número da tarefa para editar (0 cancela): ");
    if (scanf("%d", &id) != 1) {
        printf("Entrada inválida. Digite um número.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    if (id == 0) {
        printf("Operação cancelada.\n");
    } else if (id >= 1 && id <= totalTarefas) {
        indice = id - 1;
        printf("________EDITANDO TAREFA %d________ \n", id);

        /* Reaproveita a mesma funcao de leitura e validacao. */
        lerDataEHora(indice);

        printf("Nova descrição: ");
        lerTexto(agenda[indice].descricao,
                 sizeof(agenda[indice].descricao));

        agenda[indice].concluida = false;
        printf("Tarefa atualizada com sucesso.\n");
    } else {
        printf("Número de tarefa inválido.\n");
    }
}

/* Pesquisa um trecho de texto na descrição ou na data. */
void pesquisar(void) {
    char termo[100];
    int i;
    int encontrados = 0;

    printf("Digite uma palavra da descricao ou parte da data: ");
    lerTexto(termo, sizeof(termo));

    printf("\n--- RESULTADO DA PESQUISA ---\n");

    for (i = 0; i < totalTarefas; i++) {
        /* strstr retorna NULL quando não encontra o trecho.
           Esta pesquisa diferencia letras maiusculas e minusculas. */
        if (strstr(agenda[i].descricao, termo) != NULL ||
            strstr(agenda[i].data, termo) != NULL) {

            char status;
            if (agenda[i].concluida == true) {
                status = 'X';
            } else {
                status = ' ';
            }

            printf("%d - [%c] %s as %s | %s\n",
                   i + 1, status, agenda[i].data,
                   agenda[i].horario, agenda[i].descricao);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhuma tarefa encontrada.\n");
    }
}

/* main e o ponto de entrada do programa. Controla o menu principal. */
int main(void) {
    int opcao = 0;

    do {
        printf("\n________GERENCIADOR DE TAREFAS________\n");
        printf("1 - Adicionar tarefa\n");
        printf("2 - Listar tarefas\n");
        printf("3 - Marcar tarefa como concluida\n");
        printf("4 - Editar tarefa\n");
        printf("5 - Pesquisar tarefa\n");
        printf("6 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Opcao inválida. Digite um número.\n");
            limparBuffer();
            opcao = 0;
            continue;
        }
        limparBuffer();

        /* switch escolhe qual função sera executada. */
        switch (opcao) {
            case 1: adicionar(); break;
            case 2: listar(); break;
            case 3: concluir(); break;
            case 4: editar(); break;
            case 5: pesquisar(); break;
            case 6: printf("Encerrando a agenda.\n"); break;
            default: printf("Opcao inválida. Escolha de 1 a 6.\n");
        }
    } while (opcao != 6);

    return 0;
}
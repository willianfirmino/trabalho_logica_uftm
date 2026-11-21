/*
 * GERENCIADOR DE TAREFAS
 *
 * Cada tarefa e um REGISTRO (struct) com data, horario, descricao
 * e situacao de conclusao. O vetor "agenda" armazena varios registros.
 *
 * Nota: as mensagens exibidas por printf estao sem acentos para evitar
 * problemas de codificacao em terminais Windows (ex.: Dev-C++ e Code::Blocks).
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_TAREFAS 100

/* REGISTRO: agrupa campos diferentes que pertencem a uma tarefa. */
typedef struct {
    char data[11];        /* DD/MM/AAAA + caractere final '\0' */
    char horario[6];      /* HH:MM + caractere final '\0' */
    char descricao[100];  /* Descricao digitada pelo usuario */
    bool concluida;       /* true = concluida; false = pendente */
} Tarefa;

/* Vetor de registros e contador de tarefas efetivamente cadastradas. */
Tarefa agenda[MAX_TAREFAS];
int totalTarefas = 0;

/* Descarta o restante da linha deixado no teclado depois de scanf ou fgets. */
void limparBuffer(void) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
        /* Os caracteres excedentes sao descartados. */
    }
}

/* Le uma linha inteira, inclusive espacos, respeitando o tamanho do vetor. */
void lerTexto(char texto[], int tamanho) {
    if (fgets(texto, tamanho, stdin) != NULL) {
        /* Se o Enter nao coube no vetor, descarta o restante da linha no buffer. */
        if (strchr(texto, '\n') == NULL) {
            limparBuffer();
        } else {
            /* Remove o Enter armazenado por fgets. */
            texto[strcspn(texto, "\n")] = '\0';
        }
    } else {
        texto[0] = '\0';
    }
}

/* Converte uma copia do texto para letras minusculas (para pesquisa). */
void paraMinusculas(const char origem[], char destino[], int tamanho) {
    int i;
    for (i = 0; origem[i] != '\0' && i < tamanho - 1; i++) {
        /* (unsigned char) garante chamada segura de tolower em C. */
        destino[i] = (char)tolower((unsigned char)origem[i]);
    }
    destino[i] = '\0';
}

/*
 * FUNCAO: verifica se a data segue o formato DD/MM/AAAA e as faixas basicas.
 * Retorna true se for valida ou false caso contrario.
 * Nao valida o calendario completo (como dias reais de fevereiro).
 */
bool validarData(const char dataDigitada[]) {
    int dia, mes, ano;

    /* Confere tamanho, separadores e se os demais caracteres sao digitos.
       (unsigned char) garante chamada segura de isdigit em C. */
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

        /* Subtrair '0' converte o caractere digito em seu valor numerico (tabela ASCII). */
        dia = (dataDigitada[0] - '0') * 10 + (dataDigitada[1] - '0');
        mes = (dataDigitada[3] - '0') * 10 + (dataDigitada[4] - '0');
        ano = (dataDigitada[6] - '0') * 1000
            + (dataDigitada[7] - '0') * 100
            + (dataDigitada[8] - '0') * 10
            + (dataDigitada[9] - '0');

        if (dia >= 1 && dia <= 31 &&
            mes >= 1 && mes <= 12 &&
            ano >= 2000 && ano <= 2100) {
            return true;
        }
    }

    return false;
}

/*
 * FUNCAO: verifica se o horario segue o formato HH:MM e as faixas basicas.
 * Retorna true se for valido ou false caso contrario.
 */
bool validarHorario(const char horarioDigitado[]) {
    int hora, minuto;

    if (strlen(horarioDigitado) == 5 &&
        horarioDigitado[2] == ':' &&
        isdigit((unsigned char)horarioDigitado[0]) &&
        isdigit((unsigned char)horarioDigitado[1]) &&
        isdigit((unsigned char)horarioDigitado[3]) &&
        isdigit((unsigned char)horarioDigitado[4])) {

        hora = (horarioDigitado[0] - '0') * 10 + (horarioDigitado[1] - '0');
        minuto = (horarioDigitado[3] - '0') * 10 + (horarioDigitado[4] - '0');

        if (hora >= 0 && hora <= 23 && minuto >= 0 && minuto <= 59) {
            return true;
        }
    }

    return false;
}

/* Le data e horario para o registro indicado por indice. */
void lerDataEHora(int indice) {
    char dataDigitada[100];
    char horarioDigitado[100];
    bool valido;

    do {
        printf("Data (DD/MM/AAAA): ");
        lerTexto(dataDigitada, sizeof(dataDigitada));
        valido = validarData(dataDigitada);

        if (!valido) {
            printf("Data invalida. Use DD/MM/AAAA.\n");
        }
    } while (!valido); /* Repete ate a data ser considerada valida. */

    /* O ponto acessa um campo da struct armazenada na posicao indice. */
    strcpy(agenda[indice].data, dataDigitada);

    do {
        printf("Horario (HH:MM): ");
        lerTexto(horarioDigitado, sizeof(horarioDigitado));
        valido = validarHorario(horarioDigitado);

        if (!valido) {
            printf("Horario invalido. Use HH:MM.\n");
        }
    } while (!valido);

    strcpy(agenda[indice].horario, horarioDigitado);
}

/* Cadastra uma tarefa na proxima posicao livre do vetor. */
void adicionar(void) {
    if (totalTarefas >= MAX_TAREFAS) {
        printf("Agenda cheia. Limite de %d tarefas.\n", MAX_TAREFAS);
        return;
    }

    printf("\n________NOVA TAREFA________\n");

    /* Em C, o primeiro indice do vetor e zero.
       totalTarefas indica exatamente a proxima posicao livre. */
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

    printf("Numero da tarefa para concluir (0 cancela): ");
    if (scanf("%d", &id) != 1) {
        printf("Entrada invalida. Digite um numero.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    if (id == 0) {
        printf("Operacao cancelada.\n");
    } else if (id >= 1 && id <= totalTarefas) {
        /* O usuario conta a partir de 1; o vetor C comeca em 0. */
        agenda[id - 1].concluida = true;
        printf("Tarefa marcada como concluida.\n");
    } else {
        printf("Numero de tarefa invalido.\n");
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

    printf("Numero da tarefa para editar (0 cancela): ");
    if (scanf("%d", &id) != 1) {
        printf("Entrada invalida. Digite um numero.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    if (id == 0) {
        printf("Operacao cancelada.\n");
    } else if (id >= 1 && id <= totalTarefas) {
        indice = id - 1;
        printf("________EDITANDO TAREFA %d________\n", id);

        /* Reaproveita a mesma funcao de leitura e validacao. */
        lerDataEHora(indice);

        printf("Nova descricao: ");
        lerTexto(agenda[indice].descricao,
                 sizeof(agenda[indice].descricao));

        agenda[indice].concluida = false;
        printf("Tarefa atualizada com sucesso.\n");
    } else {
        printf("Numero de tarefa invalido.\n");
    }
}

/* Pesquisa um trecho de texto na descricao ou na data. */
void pesquisar(void) {
    char termo[100];
    char termoMinusculo[100];
    char descricaoMinuscula[100];
    int i;
    int encontrados = 0;

    printf("Digite uma palavra da descricao ou parte da data: ");
    lerTexto(termo, sizeof(termo));
    paraMinusculas(termo, termoMinusculo, sizeof(termoMinusculo));

    printf("\n________RESULTADO DA PESQUISA________\n");

    for (i = 0; i < totalTarefas; i++) {
        paraMinusculas(agenda[i].descricao, descricaoMinuscula,
                       sizeof(descricaoMinuscula));

        /* strstr retorna NULL quando nao encontra o trecho.
           A conversao para minusculas evita diferenciar maiusculas de minusculas. */
        if (strstr(descricaoMinuscula, termoMinusculo) != NULL ||
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
            printf("Opcao invalida. Digite um numero.\n");
            limparBuffer();
            opcao = 0;
        } else {
            limparBuffer();

            /* switch escolhe qual funcao sera executada. */
            switch (opcao) {
                case 1: adicionar(); break;
                case 2: listar(); break;
                case 3: concluir(); break;
                case 4: editar(); break;
                case 5: pesquisar(); break;
                case 6: printf("Encerrando a agenda.\n"); break;
                default: printf("Opcao invalida. Escolha de 1 a 6.\n");
            }
        }
    } while (opcao != 6);

    return 0;
}

algoritmo "Gerenciador_de_Agenda"

// GERENCIADOR DE TAREFAS
// Este programa permite cadastrar, listar, concluir, editar e pesquisar tarefas.
//
// REGISTRO:
// Um registro agrupa informações relacionadas. Aqui, cada tarefa possui
// data, horário, descrição e situação de conclusão.
//
// VETOR:
// O vetor agenda armazena até 100 registros do tipo Tarefa.

tipo
Tarefa = registro
data: caractere
horario: caractere
descricao: caractere
concluida: logico
fimregistro

var
agenda: vetor[1..100] de Tarefa
totalTarefas, opcao: inteiro

// FUNÇÃO: retorna verdadeiro se todos os caracteres do texto forem dígitos (0 a 9).
funcao somenteDigitos(texto: caractere): logico
var
i: inteiro
c: caractere
resultado: logico
inicio
    resultado <- verdadeiro

    se compr(texto) = 0 entao
        resultado <- falso
    senao
        para i de 1 ate compr(texto) faca
            c <- copia(texto, i, 1)
            se (c < "0") ou (c > "9") entao
                resultado <- falso
            fimse
        fimpara
    fimse

    retorne resultado
fimfuncao

// FUNÇÃO: verifica se a data segue o formato DD/MM/AAAA e as faixas básicas.
// Retorna verdadeiro se for válida ou falso caso contrário.
funcao validarData(dataDigitada: caractere): logico
var
dia, mes, ano: caractere
valido: logico
inicio
    valido <- falso

    // DD/MM/AAAA possui 10 caracteres.
    se compr(dataDigitada) = 10 entao
        // Confere as barras nas posições 3 e 6.
        se (copia(dataDigitada, 3, 1) = "/") e (copia(dataDigitada, 6, 1) = "/") entao
            // COPIA extrai partes do texto. No VisuAlg, a primeira posição é 1.
            dia <- copia(dataDigitada, 1, 2)
            mes <- copia(dataDigitada, 4, 2)
            ano <- copia(dataDigitada, 7, 4)

            // Garante que dia, mês e ano contenham apenas dígitos antes de comparar.
            se somenteDigitos(dia) e somenteDigitos(mes) e somenteDigitos(ano) entao
                // Verifica faixas simples. Não verifica dias reais de cada mês.
                se (dia >= "01") e (dia <= "31") e (mes >= "01") e (mes <= "12") e (ano >= "2000") e (ano <= "2100") entao
                    valido <- verdadeiro
                fimse
            fimse
        fimse
    fimse

    retorne valido
fimfuncao

// FUNÇÃO: verifica se o horário segue o formato HH:MM e as faixas básicas.
// Retorna verdadeiro se for válido ou falso caso contrário.
funcao validarHorario(horarioDigitado: caractere): logico
var
hora, minuto: caractere
valido: logico
inicio
    valido <- falso

    se compr(horarioDigitado) = 5 entao
        se copia(horarioDigitado, 3, 1) = ":" entao
            hora <- copia(horarioDigitado, 1, 2)
            minuto <- copia(horarioDigitado, 4, 2)

            se somenteDigitos(hora) e somenteDigitos(minuto) entao
                se (hora >= "00") e (hora <= "23") e (minuto >= "00") e (minuto <= "59") entao
                    valido <- verdadeiro
                fimse
            fimse
        fimse
    fimse

    retorne valido
fimfuncao

// Recebe a posição do vetor e preenche os campos data e horário.
// O procedimento é reutilizado tanto no cadastro quanto na edição.
procedimento lerDataEHora(indice: inteiro)
var
dataDigitada, horarioDigitado: caractere
valido: logico
inicio
    // REPITA executa pelo menos uma vez e repete enquanto a condição for falsa.
    repita
        escreva("Data (DD/MM/AAAA): ")
        leia(dataDigitada)
        valido <- validarData(dataDigitada)

        se valido = falso entao
            escreval("Data inválida. Use DD/MM/AAAA.")
        fimse
    ate valido = verdadeiro

    // O ponto acessa um campo do registro armazenado na posição indice.
    agenda[indice].data <- dataDigitada

    // Repete a leitura do horário até receber HH:MM dentro das faixas.
    repita
        escreva("Horário (HH:MM): ")
        leia(horarioDigitado)
        valido <- validarHorario(horarioDigitado)

        se valido = falso entao
            escreval("Horário inválido. Use HH:MM.")
        fimse
    ate valido = verdadeiro

    agenda[indice].horario <- horarioDigitado
fimprocedimento

// Cadastra uma tarefa na próxima posição livre do vetor.
procedimento adicionar
inicio
    // Verifica o limite antes de acessar uma posição do vetor.
    se totalTarefas < 100 entao
        escreval("")
        escreval("________NOVA TAREFA________")

        // O contador aumenta e passa a indicar a posição da nova tarefa.
        totalTarefas <- totalTarefas + 1
        lerDataEHora(totalTarefas)

        escreva("Descrição da tarefa: ")
        leia(agenda[totalTarefas].descricao)

        // Toda tarefa nova começa com concluida = falso.
        agenda[totalTarefas].concluida <- falso
        escreval("Tarefa cadastrada com sucesso!")
    senao
        escreval("Agenda cheia. Limite de 100 tarefas.")
    fimse
fimprocedimento

// Percorre e apresenta todos os registros cadastrados.
procedimento listar
var
i: inteiro
status: caractere
inicio
    escreval("")
    escreval("________TAREFAS CADASTRADAS________")

    se totalTarefas = 0 entao
        escreval("Nenhuma tarefa cadastrada.")
    senao
        // PARA percorre os índices de 1 até a quantidade cadastrada.
        para i de 1 ate totalTarefas faca
            se agenda[i].concluida = verdadeiro entao
                status <- "X"
            senao
                status <- " "
            fimse

            // O índice i acessa os quatro campos do mesmo registro.
            escreval(i, " - [", status, "] ", agenda[i].data, " às ", agenda[i].horario, " | ", agenda[i].descricao)
        fimpara
    fimse
fimprocedimento

// Altera o campo lógico concluida do registro escolhido.
procedimento concluir
var
id: inteiro
inicio
    listar

    se totalTarefas > 0 entao
        escreva("Número da tarefa para concluir (0 cancela): ")
        leia(id)

        se id = 0 entao
            escreval("Operação cancelada.")
        senao
            // Impede que o programa acesse uma posição fora do cadastro.
            se (id >= 1) e (id <= totalTarefas) entao
                agenda[id].concluida <- verdadeiro
                escreval("Tarefa marcada como concluída.")
            senao
                escreval("Número de tarefa inválido.")
            fimse
        fimse
    fimse
fimprocedimento

// Altera data, horário e descrição de um registro existente.
procedimento editar
var
id: inteiro
inicio
    listar

    se totalTarefas > 0 entao
        escreva("Número da tarefa para editar (0 cancela): ")
        leia(id)

        se id = 0 entao
            escreval("Operação cancelada.")
        senao
            se (id >= 1) e (id <= totalTarefas) entao
                escreval("________EDITANDO TAREFA ", id, "________")

                // Reutiliza o procedimento de leitura e validação.
                lerDataEHora(id)

                escreva("Nova descrição: ")
                leia(agenda[id].descricao)

                // Após a edição, a tarefa volta a ficar pendente.
                agenda[id].concluida <- falso
                escreval("Tarefa atualizada com sucesso.")
            senao
                escreval("Número de tarefa inválido.")
            fimse
        fimse
    fimse
fimprocedimento

// Pesquisa um trecho na descrição ou na data de cada registro.
procedimento pesquisar
var
termo: caractere
i, encontrados: inteiro
status: caractere
inicio
    escreva("Digite uma palavra da descrição ou parte da data: ")
    leia(termo)
    encontrados <- 0

    escreval("")
    escreval("________RESULTADO DA PESQUISA________")

    para i de 1 ate totalTarefas faca
        // POS retorna a posição do trecho; zero significa que não encontrou.
        // MAIUSC faz a busca na descrição sem diferenciar maiúsculas/minúsculas.
        se (pos(maiusc(termo), maiusc(agenda[i].descricao)) > 0) ou (pos(termo, agenda[i].data) > 0) entao
            se agenda[i].concluida = verdadeiro entao
                status <- "X"
            senao
                status <- " "
            fimse

            escreval(i, " - [", status, "] ", agenda[i].data, " às ", agenda[i].horario, " | ", agenda[i].descricao)
            encontrados <- encontrados + 1
        fimse
    fimpara

    // Se o contador permanecer em zero, nenhuma tarefa correspondeu ao termo.
    se encontrados = 0 entao
        escreval("Nenhuma tarefa encontrada.")
    fimse
fimprocedimento

// PROGRAMA PRINCIPAL: controla o menu e chama os procedimentos.
inicio
    totalTarefas <- 0

    // REPITA mantém o menu ativo até a opção 6.
    repita
        escreval("")
        escreval("________GERENCIADOR DE TAREFAS________")
        escreval("1 - Adicionar tarefa")
        escreval("2 - Listar tarefas")
        escreval("3 - Marcar tarefa como concluída")
        escreval("4 - Editar tarefa")
        escreval("5 - Pesquisar tarefa")
        escreval("6 - Sair")
        escreva("Escolha uma opção: ")
        leia(opcao)

        // ESCOLHA/CASO seleciona o procedimento de acordo com a opção.
        escolha opcao
            caso 1
                adicionar
            caso 2
                listar
            caso 3
                concluir
            caso 4
                editar
            caso 5
                pesquisar
            caso 6
                escreval("Encerrando a agenda.")
            outrocaso
                escreval("Opção inválida. Escolha de 1 a 6.")
        fimescolha
    ate opcao = 6
fimalgoritmo

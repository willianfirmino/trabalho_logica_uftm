"""
GERENCIADOR DE TAREFAS

Cada tarefa e representada por um DICIONÁRIO.
O dicionário funciona conceitualmente como um REGISTRO:
reune campos relacionados (data, horario, descricao e concluida).
A lista "agenda" armazena vários dicionários, ou seja, varios registros.
"""

MAX_TAREFAS = 100

# Lista global que armazenara todos os registros de tarefas.
agenda = []


# Solicita e valida data e horario. Retorna os dois valores.
def ler_data_hora():
    valido = False

    # Enquanto a data nao estiver valida, solicita novamente.
    while not valido:
        data = input("Data (DD/MM/AAAA): ")
        valido = False

        # Uma data no formato DD/MM/AAAA tem dez caracteres.
        if len(data) == 10:
            if data[2] == "/" and data[5] == "/":
                dia = data[0:2]
                mes = data[3:5]
                ano = data[6:10]

                # isdigit verifica se o texto possui somente digitos.
                if dia.isdigit() and mes.isdigit() and ano.isdigit():
                    dia_num = int(dia)
                    mes_num = int(mes)
                    ano_num = int(ano)

                    # Verifica intervalos simples, não o calendário completo.
                    if (dia_num >= 1 and dia_num <= 31 and
                        mes_num >= 1 and mes_num <= 12 and
                        ano_num >= 2000 and ano_num <= 2100):
                        valido = True

        if not valido:
            print("Data inválida. Use DD/MM/AAAA.")

    valido = False

    # Repete a leitura até receber um horário válido.
    while not valido:
        horario = input("Horario (HH:MM): ")
        valido = False

        if len(horario) == 5 and horario[2] == ":":
            hora = horario[0:2]
            minuto = horario[3:5]

            if hora.isdigit() and minuto.isdigit():
                hora_num = int(hora)
                minuto_num = int(minuto)

                if (hora_num >= 0 and hora_num <= 23 and
                    minuto_num >= 0 and minuto_num <= 59):
                    valido = True

        if not valido:
            print("Horario invalido. Use HH:MM.")

    # return devolve os dois valores para a função que chamou.
    return data, horario


# Cria um dicionario (registro) e adiciona esse registro a lista.
def adicionar():
    if len(agenda) >= MAX_TAREFAS:
        print("Agenda cheia. Limite de", MAX_TAREFAS, "tarefas.")
        return

    print("\n________NOVA TAREFA________")
    data, horario = ler_data_hora()
    descricao = input("Descrição da tarefa: ")

    # Cada chave nomeia um campo do registro.
    tarefa = {
        "data": data,
        "horario": horario,
        "descricao": descricao,
        "concluida": False
    }

    # append coloca o novo registro no final da lista.
    agenda.append(tarefa)
    print("Tarefa cadastrada com sucesso!")


# Percorre a lista e mostra os campos de cada registro.
def listar():
    print("\n________TAREFAS CADASTRADAS________")

    if len(agenda) == 0:
        print("Nenhuma tarefa cadastrada.")
    else:
        # range gera os indices de zero ate o último registro.
        for i in range(len(agenda)):
            tarefa = agenda[i]

            if tarefa["concluida"] == True:
                status = "X"
            else:
                status = " "

            # O usuario ve i + 1, pois a numeração apresentada comeca em 1.
            print(i + 1, "- [", status, "]",
                  tarefa["data"], "as", tarefa["horario"],
                  "|", tarefa["descricao"])


# Altera o campo concluida do registro escolhido.
def concluir():
    listar()

    if len(agenda) > 0:
        entrada = input("Numero da tarefa para concluir (0 cancela): ")

        # Verifica se a entrada pode ser convertida em inteiro.
        if entrada.isdigit():
            id_tarefa = int(entrada)

            if id_tarefa == 0:
                print("Operacao cancelada.")
            elif id_tarefa >= 1 and id_tarefa <= len(agenda):
                # Subtrai 1 para converter numeracao humana em indice da lista.
                agenda[id_tarefa - 1]["concluida"] = True
                print("Tarefa marcada como concluida.")
            else:
                print("Numero de tarefa invalido.")
        else:
            print("Entrada invalida. Digite um numero.")


# Localiza um registro e substitui os valores de seus campos.
def editar():
    listar()

    if len(agenda) > 0:
        entrada = input("Número da tarefa para editar (0 cancela): ")

        if entrada.isdigit():
            id_tarefa = int(entrada)

            if id_tarefa == 0:
                print("Operação cancelada.")
            elif id_tarefa >= 1 and id_tarefa <= len(agenda):
                indice = id_tarefa - 1
                print("________EDITANDO TAREFA", id_tarefa,"________")

                data, horario = ler_data_hora()
                descricao = input("Nova descrição: ")

                # Atualiza os campos do mesmo dicionario.
                agenda[indice]["data"] = data
                agenda[indice]["horario"] = horario
                agenda[indice]["descricao"] = descricao
                agenda[indice]["concluida"] = False

                print("Tarefa atualizada com sucesso.")
            else:
                print("Número de tarefa invalido.")
        else:
            print("Entrada inválida. Digite um numero.")


# Pesquisa o termo na descricao ou na data de cada registro.
def pesquisar():
    termo = input("Digite uma palavra da descrição ou parte da data: ")
    encontrados = 0

    print("\n________RESULTADO DA PESQUISA________")

    for i in range(len(agenda)):
        tarefa = agenda[i]

        # in verifica se um texto aparece dentro de outro.
        # A pesquisa diferencia maiusculas de minusculas.
        if termo in tarefa["descricao"] or termo in tarefa["data"]:
            if tarefa["concluida"] == True:
                status = "X"
            else:
                status = " "

            print(i + 1, "- [", status, "]",
                  tarefa["data"], "as", tarefa["horario"],
                  "|", tarefa["descricao"])
            encontrados = encontrados + 1

    if encontrados == 0:
        print("Nenhuma tarefa encontrada.")


# Função principal: apresenta o menu e direciona as operações.
def main():
    opcao = ""

    # O menu continua enquanto o usuario nao escolher "6".
    while opcao != "6":
        print("")
        print("________GERENCIADOR DE TAREFAS________")
        print("1 - Adicionar tarefa")
        print("2 - Listar tarefas")
        print("3 - Marcar tarefa como concluida")
        print("4 - Editar tarefa")
        print("5 - Pesquisar tarefa")
        print("6 - Sair")

        opcao = input("Escolha uma opção: ")

        # Cada alternativa chama a funcao responsavel pela operação.
        if opcao == "1":
            adicionar()
        elif opcao == "2":
            listar()
        elif opcao == "3":
            concluir()
        elif opcao == "4":
            editar()
        elif opcao == "5":
            pesquisar()
        elif opcao == "6":
            print("Encerrando a agenda.")
        else:
            print("Opcao invalida. Escolha de 1 a 6.")


# Chamada da função principal: inicia o programa.
main()
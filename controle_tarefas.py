"""
GERENCIADOR DE TAREFAS

Cada tarefa é representada por um DICIONÁRIO.
O dicionário funciona conceitualmente como um REGISTRO:
reúne campos relacionados (data, horario, descricao e concluida).
A lista "agenda" armazena vários dicionários, ou seja, vários registros.
"""

MAX_TAREFAS = 100

# Lista global que armazenará todos os registros de tarefas.
agenda = []


# FUNÇÃO: verifica se a data segue o formato DD/MM/AAAA e as faixas básicas.
# Retorna True se for válida ou False caso contrário.
def validar_data(data):
    # Uma data no formato DD/MM/AAAA tem dez caracteres.
    if len(data) == 10 and data[2] == "/" and data[5] == "/":
        dia = data[0:2]
        mes = data[3:5]
        ano = data[6:10]

        # isdigit verifica se o texto possui somente dígitos.
        if dia.isdigit() and mes.isdigit() and ano.isdigit():
            dia_num = int(dia)
            mes_num = int(mes)
            ano_num = int(ano)

            # Verifica intervalos simples, não o calendário completo.
            if (dia_num >= 1 and dia_num <= 31 and
                mes_num >= 1 and mes_num <= 12 and
                ano_num >= 2000 and ano_num <= 2100):
                return True

    return False


# FUNÇÃO: verifica se o horário segue o formato HH:MM e as faixas básicas.
# Retorna True se for válido ou False caso contrário.
def validar_horario(horario):
    if len(horario) == 5 and horario[2] == ":":
        hora = horario[0:2]
        minuto = horario[3:5]

        if hora.isdigit() and minuto.isdigit():
            hora_num = int(hora)
            minuto_num = int(minuto)

            if (hora_num >= 0 and hora_num <= 23 and
                minuto_num >= 0 and minuto_num <= 59):
                return True

    return False


# FUNÇÃO: solicita e valida data e horário. Retorna os dois valores.
def ler_data_hora():
    valido = False

    # Enquanto a data não estiver válida, solicita novamente.
    while not valido:
        data = input("Data (DD/MM/AAAA): ")
        valido = validar_data(data)

        if not valido:
            print("Data inválida. Use DD/MM/AAAA.")

    valido = False

    # Repete a leitura até receber um horário válido.
    while not valido:
        horario = input("Horário (HH:MM): ")
        valido = validar_horario(horario)

        if not valido:
            print("Horário inválido. Use HH:MM.")

    # return devolve os dois valores para a função que chamou.
    return data, horario


# Cria um dicionário (registro) e adiciona esse registro à lista.
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
        # range gera os índices de zero até o último registro.
        for i in range(len(agenda)):
            tarefa = agenda[i]

            if tarefa["concluida"] == True:
                status = "X"
            else:
                status = " "

            # O usuário vê i + 1, pois a numeração apresentada começa em 1.
            print(i + 1, "- [" + status + "]",
                  tarefa["data"], "às", tarefa["horario"],
                  "|", tarefa["descricao"])


# Altera o campo concluida do registro escolhido.
def concluir():
    listar()

    if len(agenda) > 0:
        entrada = input("Número da tarefa para concluir (0 cancela): ")

        # Verifica se a entrada pode ser convertida em inteiro.
        if entrada.isdigit():
            id_tarefa = int(entrada)

            if id_tarefa == 0:
                print("Operação cancelada.")
            elif id_tarefa >= 1 and id_tarefa <= len(agenda):
                # Subtrai 1 para converter numeração humana em índice da lista.
                agenda[id_tarefa - 1]["concluida"] = True
                print("Tarefa marcada como concluída.")
            else:
                print("Número de tarefa inválido.")
        else:
            print("Entrada inválida. Digite um número.")


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
                print("________EDITANDO TAREFA", id_tarefa, "________")

                data, horario = ler_data_hora()
                descricao = input("Nova descrição: ")

                # Atualiza os campos do mesmo dicionário.
                agenda[indice]["data"] = data
                agenda[indice]["horario"] = horario
                agenda[indice]["descricao"] = descricao
                agenda[indice]["concluida"] = False

                print("Tarefa atualizada com sucesso.")
            else:
                print("Número de tarefa inválido.")
        else:
            print("Entrada inválida. Digite um número.")


# Pesquisa o termo na descrição ou na data de cada registro.
def pesquisar():
    termo = input("Digite uma palavra da descrição ou parte da data: ")
    termo_minusculo = termo.lower()
    encontrados = 0

    print("\n________RESULTADO DA PESQUISA________")

    for i in range(len(agenda)):
        tarefa = agenda[i]

        # in verifica se um texto aparece dentro de outro.
        # lower() faz a busca na descrição sem diferenciar maiúsculas de minúsculas.
        if termo_minusculo in tarefa["descricao"].lower() or termo in tarefa["data"]:
            if tarefa["concluida"] == True:
                status = "X"
            else:
                status = " "

            print(i + 1, "- [" + status + "]",
                  tarefa["data"], "às", tarefa["horario"],
                  "|", tarefa["descricao"])
            encontrados = encontrados + 1

    if encontrados == 0:
        print("Nenhuma tarefa encontrada.")


# Função principal: apresenta o menu e direciona as operações.
def main():
    opcao = ""

    # O menu continua enquanto o usuário não escolher "6".
    while opcao != "6":
        print("")
        print("________GERENCIADOR DE TAREFAS________")
        print("1 - Adicionar tarefa")
        print("2 - Listar tarefas")
        print("3 - Marcar tarefa como concluída")
        print("4 - Editar tarefa")
        print("5 - Pesquisar tarefa")
        print("6 - Sair")

        opcao = input("Escolha uma opção: ")

        # Cada alternativa chama a função responsável pela operação.
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
            print("Opção inválida. Escolha de 1 a 6.")


# Chamada da função principal: inicia o programa.
main()

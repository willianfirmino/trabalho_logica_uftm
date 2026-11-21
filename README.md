# Gerenciador de Tarefas

Projeto didático de lógica de programação que implementa um pequeno gerenciador de tarefas em três linguagens: **Portugol (VisualG)**, **C** e **Python**.

O programa permite cadastrar tarefas, consultar a lista, marcar tarefas como concluídas, editar informações e pesquisar registros. Os códigos foram organizados em procedimentos ou funções e contêm comentários para auxiliar o acompanhamento da lógica e das instruções.

## Arquivos do projeto

| Arquivo                | Linguagem          | Organização dos dados                                        |
| ---------------------- | ------------------ | ------------------------------------------------------------ |
| `controle_tarefas.alg` | Portugol / VisualG | Vetor de registros (`Tarefa`)                                |
| `controle_tarefas.c`   | C                  | Vetor de estruturas (`struct Tarefa`)                        |
| `controle_tarefas.py`  | Python             | Lista de dicionários (cada dicionário representa uma tarefa) |

> **Importante:** as três versões implementam a mesma proposta, mas respeitam as características de cada linguagem. Em particular, a versão Portugol deste conjunto de arquivos utiliza registros; a versão C utiliza `struct`; e a versão Python utiliza dicionários.

## Funcionalidades

O menu principal oferece seis opções:

1. **Adicionar tarefa:** cadastra data, horário e descrição. A tarefa começa com situação pendente.
2. **Listar tarefas:** exibe as tarefas cadastradas e sua situação.
3. **Marcar tarefa como concluída:** altera a situação da tarefa escolhida.
4. **Editar tarefa:** permite alterar data, horário e descrição. Após a edição, a tarefa volta à situação pendente.
5. **Pesquisar tarefa:** procura um trecho informado pelo usuário na descrição ou na data.
6. **Sair:** encerra o programa.

Cada tarefa possui quatro campos:

- **Data:** formato `DD/MM/AAAA`.
- **Horário:** formato `HH:MM`.
- **Descrição:** texto informado pelo usuário.
- **Concluída:** valor lógico que indica se a tarefa foi finalizada (`verdadeiro`/`falso`, `true`/`false` ou equivalente na linguagem).

## Conceitos de programação demonstrados

| Conceito                             | Aplicação no projeto                                                                                  |
| ------------------------------------ | ----------------------------------------------------------------------------------------------------- |
| Variáveis e tipos de dados           | Armazenamento de opções, contadores, textos e situação lógica das tarefas.                            |
| Vetores e listas                     | Armazenamento de várias tarefas.                                                                      |
| Registros / estruturas / dicionários | Agrupamento dos campos que pertencem a uma mesma tarefa.                                              |
| Procedimentos e funções              | Separação das operações do menu e funções de validação (`validarData`, `validarHorario`, etc.).       |
| Parâmetros e retorno                 | As funções de validação recebem o texto digitado e retornam um valor lógico indicando se é válido.    |
| Estruturas condicionais              | Validação de entradas e seleção das operações do menu.                                                |
| Estruturas de repetição              | Repetição do menu, validação dos dados e percurso das tarefas.                                        |
| Pesquisa em textos                   | Localização de um trecho na descrição ou na data.                                                     |
| Contadores                           | Controle da quantidade de tarefas cadastradas e dos resultados encontrados.                           |

## Como os dados são organizados em cada versão

### Portugol (VisualG)

O arquivo `controle_tarefas.alg` declara o tipo `Tarefa` como um **registro** com os campos `data`, `horario`, `descricao` e `concluida`. O vetor `agenda` armazena até 100 elementos desse tipo. O contador `totalTarefas` informa quantas posições já foram utilizadas.

O VisualG utiliza índices iniciados em 1. Por isso, a primeira tarefa é armazenada em `agenda[1]`.

### C

O arquivo `controle_tarefas.c` define `Tarefa` com `typedef struct` e declara `agenda` como um vetor com 100 estruturas. O campo `concluida` utiliza o tipo lógico `bool`.

Em C, os índices dos vetores começam em 0. O programa converte o número apresentado ao usuário (que começa em 1) para o índice interno subtraindo 1.

### Python

O arquivo `controle_tarefas.py` utiliza uma lista chamada `agenda`. Cada elemento da lista é um dicionário com as chaves `data`, `horario`, `descricao` e `concluida`.

Os índices das listas Python também começam em 0. Assim como na versão C, o programa subtrai 1 do número informado pelo usuário para acessar a tarefa correspondente.

## Validação de data e horário

As versões solicitam:

- Data no formato `DD/MM/AAAA`, com dia entre 01 e 31, mês entre 01 e 12 e ano entre 2000 e 2100.
- Horário no formato `HH:MM`, com hora entre 00 e 23 e minuto entre 00 e 59.

A validação é básica: verifica o formato e as faixas indicadas, mas **não valida o calendário completo**. Portanto, não garante, por exemplo, que 31/02 seja uma data existente.

## Como executar

### Portugol / VisualG

1. Abra o interpretador Visualg
2. Abra `controle_tarefas.alg` ou copie o conteúdo para o editor.
3. Execute o algoritmo e escolha uma opção no menu.
   OBS. Rodei o programa apenas no Visualg instalado, não vi como trabalhar com o tipo de dado registro na versão online.

### C

É necessário ter um compilador C instalado, como o GCC. Em um terminal, na pasta do arquivo, execute:

```bash
gcc -std=c99 -Wall -Wextra controle_tarefas.c -o controle_tarefas
./controle_tarefas
```

No Windows, após compilar, execute `controle_tarefas.exe`.

### Python

É necessário ter Python 3 instalado. Em um terminal, na pasta do arquivo, execute:

```bash
python3 controle_tarefas.py
```

No Windows, dependendo da instalação, o comando pode ser `python controle_tarefas.py`.

## Limitações conhecidas

- O limite é de **100 tarefas**.
- As tarefas ficam armazenadas somente na memória enquanto o programa está em execução. Ao encerrar, os dados não são gravados em arquivo ou banco de dados.
- A validação de data não verifica a quantidade real de dias de cada mês nem anos bissextos.
- A pesquisa na descrição não diferencia letras maiúsculas de minúsculas nas três versões (exceto em letras acentuadas na versão C, devido à limitação padrão de `tolower`). A busca na data procura o trecho informado.
- Na versão C, as mensagens exibidas por `printf` foram mantidas sem acentos para evitar quebra de caracteres em terminais Windows (como Dev-C++ e Code::Blocks).
- Na versão C, a descrição é armazenada em um vetor de caracteres com capacidade para até 99 caracteres úteis, mais o terminador da string. Na versão Python, a entrada de descrição não possui esse mesmo limite fixo no código.
- Na versão Portugol, a leitura de texto segue o comportamento do comando `leia` do VisualG.

## Sugestões para estudar e experimentar

1. Acompanhe o caminho percorrido pelo programa quando o usuário escolhe a opção 1.
2. Identifique como o contador `totalTarefas` controla a quantidade de registros cadastrados.
3. Compare como cada linguagem representa uma tarefa: registro no VisualG, `struct` em C e dicionário em Python.
4. Observe a diferença entre a numeração exibida ao usuário e os índices internos dos vetores/listas.
5. Identifique como os laços são utilizados para validar entradas e percorrer as tarefas.
6. Experimente informar datas e horários fora dos intervalos aceitos.
7. Cadastre tarefas com descrições semelhantes e teste a pesquisa.
8. Pense em como implementar a gravação das tarefas em arquivo para que elas permaneçam disponíveis depois que o programa for encerrado.

--

**Projeto:** Gerenciador de Tarefas  
**Linguagens:** Portugol (VisualG), C e Python  
**Capacidade:** até 100 tarefas  
**Armazenamento:** memória durante a execução

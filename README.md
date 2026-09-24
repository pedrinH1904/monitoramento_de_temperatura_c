## Identificação


| Aluno(a) | Pedro Henrique de Lira Tavares |
| Disciplina |  Algoritmos e Pensamento Computacional |
| Professora | Karla Sartin |
| Data de entrega | 23/09/2026 |
| Repositório | https://github.com/pedrinH1904/monitoramento_de_temperatura_c |

---

## Objetivo

Desenvolver, em linguagem C, um programa que simule o monitoramento contínuo das
temperaturas registradas por um sensor. O programa deve ser capaz de:

- receber do usuário um limite de temperatura considerado seguro;
- ler, uma a uma, as temperaturas informadas pelo sensor (simulado pelo teclado);
- validar entradas inválidas, tanto no limite quanto nas temperaturas;
- identificar quando uma temperatura ultrapassa o limite definido;
- contar quantas temperaturas **consecutivas** ficaram acima do limite;
- encerrar automaticamente o monitoramento caso ocorram 3 leituras seguidas
  acima do limite (situação de risco), ou permitir o encerramento manual;
- apresentar, ao final, um relatório com média, maior e menor temperatura,
  quantidade de leituras acima do limite e o percentual que isso representa.

---

## ⚙️ Funcionamento do programa

### Definição do limite de temperatura

Logo no início da execução, o programa pede ao usuário que digite o limite de
temperatura considerado seguro. Esse valor fica guardado na variável `limite` e é
usado durante todo o monitoramento como referência de comparação.

### Realização das leituras

Depois de definido o limite, o programa entra em um laço de repetição que pede uma
temperatura por vez, simulando a leitura de um sensor real. Cada valor digitado é
armazenado na variável `temperatura` e, se for válido, entra no cálculo das
estatísticas (soma, maior, menor, contagem).

### Tratamento de valores inválidos

Tanto na leitura do limite quanto na leitura de cada temperatura, o programa usa o
retorno da função `scanf` para saber se o que foi digitado é realmente um número.
Se não for, o programa:

1. avisa que o valor é inválido;
2. limpa o que sobrou no buffer de entrada (`while (getchar() != '\n')`);
3. pede o valor novamente, sem avançar para a próxima etapa.

As temperaturas também passam por uma validação de faixa plausível (entre **-90 °C**
e **60 °C**). Valores fora dessa faixa são rejeitados e uma nova leitura é solicitada.

### Identificação de temperaturas acima do limite

A cada leitura válida, o programa compara a temperatura lida com o limite definido
(`if (temperatura > limite)`). Se for maior, a leitura é contabilizada como "acima
do limite" e um aviso é exibido na tela.

### Contagem de temperaturas consecutivas

Uma variável chamada `consecutivas` funciona como um contador de sequência:

- toda vez que a temperatura fica **acima** do limite → `consecutivas++`;
- toda vez que a temperatura fica **dentro** do limite (sequência quebrada) →
  `consecutivas` volta para `0`.

Assim, o contador só sobe enquanto as leituras acima do limite forem seguidas umas
das outras.

### Condição de encerramento do monitoramento

| Situação | Como é detectada |
|---|---|
|  Encerramento automático (segurança) | `consecutivas == 3` |
|  Encerramento manual | usuário digita `-9999` |

Em ambos os casos, o programa sai do laço principal e exibe o relatório final,
informando o motivo do encerramento.

---

##  Estruturas de repetição utilizadas

O programa combina **`while`** e **`do...while`**, cada um resolvendo um problema
diferente:

**`do...while`** — usado nas duas validações de entrada (limite e temperatura). É
impossível saber se um valor é válido antes de lê-lo: a leitura precisa acontecer
pelo menos uma vez para, só depois, ser avaliada. Por isso a condição é testada
**depois** da execução do bloco.

**`while`** — usado no laço principal de monitoramento. Aqui não se sabe, de
antemão, quantas temperaturas serão lidas — isso depende do que acontecer durante
a execução (encerramento manual ou 3 consecutivas acima do limite). Como essa
condição só é conhecida em tempo real, e o laço pode até não precisar rodar nenhuma
vez completa, faz mais sentido testar a condição **antes** de repetir o bloco.

---

## Como executar

Compilar:

    gcc monitoramento.c -o monitoramento

Executar:

    ./monitoramento

Siga as instruções exibidas na tela: informe o limite de temperatura e, em
seguida, as temperaturas lidas uma a uma. Para encerrar manualmente a qualquer
momento, digite `-9999`.

---

## Testes realizados

### Teste 1 — Validação de entradas inválidas

**Entradas:** `abc` (limite inválido) → `30` (válido) → `10` → `xyz` (inválido) →
`20` → `-9999` (saída manual).

    Digite o limite de temperatura considerado seguro (ex: 40.0): Valor invalido! Digite apenas numeros (ex: 35.5).
    Digite o limite de temperatura considerado seguro (ex: 40.0):
    Limite de seguranca definido: 30.00 graus

    Temperatura #1: Temperatura #2: Valor invalido! Digite apenas numeros.
    Temperatura #2: Temperatura #3:
    Encerramento manual solicitado pelo usuario.

    Total de leituras validas.......: 2
    Temperatura media................: 15.00
    Maior temperatura................: 20.00
    Menor temperatura................: 10.00
    Leituras acima do limite.........: 0
    Percentual acima do limite........: 0.00%
    Motivo do encerramento...........: encerramento manual pelo usuario

**Resultado:** as entradas de texto (`abc`, `xyz`) foram corretamente rejeitadas e
novas leituras foram solicitadas, sem contabilizá-las nas estatísticas finais.

### Teste 2 — Temperaturas acima do limite, não consecutivas

**Entradas:** limite `30` → `35`, `20`, `40`, `25`, `-9999`.

    Temperatura #1: >> Atencao: temperatura acima do limite! (1 vez(es) seguida(s))
    Temperatura #2: Temperatura #3: >> Atencao: temperatura acima do limite! (1 vez(es) seguida(s))
    Temperatura #4: Temperatura #5:
    Encerramento manual solicitado pelo usuario.

    Total de leituras validas.......: 4
    Temperatura media................: 30.00
    Maior temperatura................: 40.00
    Menor temperatura................: 20.00
    Leituras acima do limite.........: 2
    Percentual acima do limite........: 50.00%
    Motivo do encerramento...........: encerramento manual pelo usuario

**Resultado:** as leituras 35 e 40 ultrapassaram o limite, mas como a leitura 20
(dentro do limite) apareceu entre elas, o contador de consecutivas reiniciou e o
encerramento automático **não** foi disparado.

### Teste 3 — Três temperaturas consecutivas acima do limite

**Entradas:** limite `30` → `10`, `35`, `36`, `37`.

    Temperatura #1: Temperatura #2: >> Atencao: temperatura acima do limite! (1 vez(es) seguida(s))
    Temperatura #3: >> Atencao: temperatura acima do limite! (2 vez(es) seguida(s))
    Temperatura #4: >> Atencao: temperatura acima do limite! (3 vez(es) seguida(s))

    *** ALERTA: 3 temperaturas consecutivas acima do limite! ***
    *** Monitoramento encerrado automaticamente por seguranca. ***

    Total de leituras validas.......: 4
    Temperatura media................: 29.50
    Maior temperatura................: 37.00
    Menor temperatura................: 10.00
    Leituras acima do limite.........: 3
    Percentual acima do limite........: 75.00%
    Motivo do encerramento...........: 3 temperaturas consecutivas acima do limite

**Resultado:** as leituras 35, 36 e 37 formaram três leituras seguidas acima do
limite, e o programa encerrou automaticamente o monitoramento por segurança —
comportamento previsto no desafio.

> 📸 As capturas de tela da execução real (evidências) estão anexadas junto a
> esta entrega, complementando os resultados descritos acima.

---

## 💭 Reflexão final

> **Por que você escolheu `while`, `do...while` ou uma combinação das duas
> estruturas? Em qual parte do algoritmo a diferença entre testar a condição
> antes ou depois da execução foi importante para sua solução?**

Optei por usar as duas estruturas juntas, cada uma no lugar em que ela funciona
melhor. Usei `do...while` nas duas validações de entrada (limite e temperatura)
porque, nesses casos, é impossível verificar se o dado é válido sem antes lê-lo:
primeiro o programa precisa pedir o número e guardá-lo, para só depois conseguir
checar se ele é numérico e está dentro da faixa esperada. Ou seja, a ação de "ler"
sempre precisa acontecer pelo menos uma vez antes de a condição ser avaliada, e é
exatamente isso que o `do...while` garante.

Já no laço principal do monitoramento, usei `while`, porque ali a situação é
diferente: antes mesmo de começar a primeira leitura, já existe uma condição que
decide se o laço deve rodar (a variável `continuar`). Não faria sentido garantir
que pelo menos uma leitura sempre aconteça, porque, em teoria, o usuário poderia
até decidir encerrar o monitoramento imediatamente. Testar a condição **antes** de
cada repetição foi importante justamente para permitir que o laço pare assim que
uma das duas condições de encerramento (3 consecutivas acima do limite ou saída
manual) for satisfeita, sem forçar uma repetição a mais desnecessária.

Resumindo: o `do...while` foi essencial onde a ordem natural é "faça e depois
confira" (ler um dado e validar), e o `while` foi essencial onde a ordem natural é
"confira e só então faça" (continuar ou não o monitoramento).

---

<p align="center">Trabalho desenvolvido para a disciplina de [PREENCHER] — Profa. Karla Sartin</p>

# Trabalho Prático 1 – Sistemas Operacionais

## Universidade Federal do Amazonas – UFAM
### Faculdade de Tecnologia - FT

**Disciplina:** Sistemas Operacionais  
**Professor:** João Marcos Bastos Cavalcanti  

---

# Implementação de Problemas Clássicos de Concorrência Aplicados a um Portal Acadêmico e Sistema de Pedidos Online

## Alunos:

- Laysa Siqueira
- Tacyele

---

# 1. Introdução

Este trabalho apresenta a implementação de dois problemas clássicos de concorrência estudados em Sistemas Operacionais:

- Leitores × Escritores;
- Produtores × Consumidores.

O objetivo principal foi compreender o funcionamento de threads, regiões críticas, exclusão mútua e sincronização utilizando semáforos e mutex.

As implementações foram desenvolvidas em linguagem C utilizando as bibliotecas:

- `pthread`
- `semaphore`
- `unistd`

Além das versões corretas com sincronização, também foram implementadas versões sem controle de concorrência para demonstrar problemas como condição de corrida, leitura suja e inconsistência dos dados compartilhados.

---

# 2. Tema Escolhido

## 2.1 Leitores × Escritores

Foi escolhido o tema:

# Portal Acadêmico da UFAM

Nesse sistema:

- alunos representam leitores;
- professores representam escritores.

Os alunos podem consultar notas simultaneamente, enquanto os professores atualizam notas no sistema.

A variável compartilhada representa a nota de uma disciplina.

---

## 2.2 Produtores × Consumidores

Foi escolhido o tema:

# Central de Pedidos de Loja Online

Nesse sistema:

- clientes representam produtores;
- funcionários representam consumidores.

Os clientes geram pedidos que são inseridos em um buffer compartilhado e os funcionários processam os pedidos retirando-os do buffer.

---

# 3. Problema Leitores × Escritores

## 3.1 Objetivo

Implementar três versões do problema:

1. Versão com leitura suja;
2. Versão com prioridade para escritores;
3. Versão sem controle de concorrência.

---

## 3.2 Estrutura Compartilhada

A variável compartilhada utilizada foi:

```c
int notaCompartilhada = 0;
```

Ela representa a nota armazenada no sistema acadêmico.

---

# 3.3 Versão 1 – Leitura Suja

Nesta versão:

- leitores acessam simultaneamente;
- escritores podem modificar os dados enquanto leitores realizam consultas;
- pode ocorrer inconsistência nas leituras.

### Funcionamento

As threads leitoras exibem o valor atual da nota compartilhada, enquanto as threads escritoras atualizam a nota.

Como não existe proteção adequada da região crítica, pode ocorrer leitura de valores inconsistentes durante a atualização.

---

# 3.4 Versão 2 – Prioridade para Escritores

Nesta versão foi utilizado controle de concorrência com semáforos.

### Objetivos da solução

- impedir leitura durante escrita;
- permitir múltiplos leitores simultaneamente;
- garantir exclusão mútua para escritores;
- evitar leitura suja.

### Semáforos utilizados

#### `mutex`

Responsável por proteger a variável de controle:

```c
int leitoresAtivos;
```

#### `db`

Controla o acesso à região crítica onde a nota compartilhada é acessada.

---

## Funcionamento da Solução

- vários leitores podem acessar simultaneamente;
- apenas um escritor pode acessar por vez;
- leitores são bloqueados enquanto houver escritor ativo;
- escritores possuem prioridade sobre leitores.

---

# 3.5 Versão 3 – Sem Controle de Concorrência

Nesta versão não existe nenhum mecanismo de sincronização.

### Problemas observados

- dois escritores podem atualizar ao mesmo tempo;
- atualizações podem ser perdidas;
- o valor final depende da ordem de execução das threads;
- ocorre condição de corrida.

Essa versão demonstra claramente a importância da exclusão mútua.

---

# 4. Problema Produtores × Consumidores

## 4.1 Objetivo

Implementar três versões do problema:

1. vários produtores e um consumidor;
2. vários produtores e vários consumidores;
3. versão sem sincronização.

---

## 4.2 Estrutura do Buffer

Foi utilizado um buffer circular compartilhado:

```c
#define TAM_BUFFER 5

int buffer[TAM_BUFFER];
```

---

# 4.3 Versão 1 – Vários Produtores e Um Consumidor

Nesta implementação:

- múltiplos produtores inserem pedidos no buffer;
- um consumidor remove os pedidos;
- semáforos controlam acesso ao buffer.

---

## Semáforos utilizados

### `vazio`

Indica quantas posições livres existem no buffer.

### `cheio`

Indica quantas posições ocupadas existem.

### `mutex`

Controla exclusão mútua durante acesso ao buffer.

---

## Funcionamento

### Produtor

O produtor:

1. gera um pedido;
2. aguarda espaço livre;
3. entra na região crítica;
4. insere o item;
5. libera acesso ao buffer.

### Consumidor

O consumidor:

1. aguarda itens disponíveis;
2. entra na região crítica;
3. remove o item;
4. libera espaço no buffer.

---

# 4.4 Versão 2 – Vários Produtores e Vários Consumidores

Nesta versão:

- múltiplos produtores inserem pedidos;
- múltiplos consumidores processam pedidos;
- semáforos garantem sincronização correta.

---

## Características

- evita acesso simultâneo incorreto;
- impede sobrescrita do buffer;
- impede leitura de posições vazias;
- mantém integridade da fila de pedidos.

---

# 4.5 Versão 3 – Sem Controle de Concorrência

Nesta implementação o buffer é acessado sem proteção.

### Problemas observados

- dois produtores podem escrever na mesma posição;
- consumidores podem remover itens inválidos;
- dados podem ser sobrescritos;
- o buffer fica inconsistente.

Essa versão demonstra os problemas causados pela ausência de sincronização.

---

# 5. Organização do Repositório Git

Estrutura utilizada no projeto:

```text
trabalho-so-concorrencia/
│
├── README.md
├── Relatorio.md
│
├── leitores_escritores/
│   ├── versao1.c
│   ├── versao2.c
│   └── versao3.c
│
├── produtores_consumidores/
│   ├── versao1.c
│   ├── versao2.c
│   └── versao3.c
│
└── imagens/
    ├── execucao_leitores.png
    └── execucao_produtores.png
```

---

# 6. Compilação

## Linux

Compilar utilizando:

```bash
gcc arquivo.c -o programa -pthread
```

Exemplo:

```bash
gcc versao2_prioridade_escritor.c -o leitores -pthread
```

Execução:

```bash
./leitores
```

---

# 7. Exemplos de Execução

## 7.1 Leitores × Escritores

```text
[LEITOR 1] entrou na região crítica
[LEITOR 1] nota lida: 75

[ESCRITOR 1] aguardando acesso

[LEITOR 1] saiu da região crítica

[ESCRITOR 1] entrou na região crítica
[ESCRITOR 1] atualizou nota para 90
```

---

## 7.2 Produtores × Consumidores

```text
[PRODUTOR 1] produziu pedido 50
BUFFER: [50 0 0 0 0]

[CONSUMIDOR 1] consumiu pedido 50
BUFFER: [0 0 0 0 0]
```

---

# 8. Conclusão

O desenvolvimento deste trabalho permitiu compreender de forma prática os principais conceitos de programação concorrente.

Foi possível observar:

- funcionamento de threads;
- regiões críticas;
- exclusão mútua;
- sincronização com semáforos;
- bloqueio de processos;
- condição de corrida;
- problemas causados pela ausência de sincronização.

As versões sem controle de concorrência demonstraram claramente como o acesso simultâneo pode gerar inconsistências e perda de dados.

Já as versões sincronizadas mostraram a importância dos mecanismos de controle para garantir integridade e segurança no acesso às estruturas compartilhadas.

---

# 9. Referências

- SILBERSCHATZ, Abraham. Sistemas Operacionais.
- TANENBAUM, Andrew. Sistemas Operacionais Modernos.
- Documentação POSIX Threads.
- Documentação POSIX Semaphores.
- Slides da disciplina Sistemas Operacionais – UFAM.
- OpenAI ChatGPT como ferramenta auxiliar para organização textual e explicações conceituais.

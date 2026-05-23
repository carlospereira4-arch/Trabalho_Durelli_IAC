# Análise Técnica do Sistema de Conversão de Bases

Este documento apresenta uma documentação detalhada sobre o sistema de conversão de bases numéricas implementado em C++. Abaixo, é explicada a estrutura de cada função, a lógica de negócio encapsulada, o mapeamento de interconexões do sistema, as respostas sobre conceitos avançados utilizados e as oportunidades de melhoria.

---

## 1. Explicação Detalhada das Funções

O código está estruturado em funções utilitárias de manipulação de tipos, algoritmos base de conversão inteira, algoritmos para tratamento de fracionários, exibição detalhada (*trace*) e uma rotina de execução em lote (*batch*).

### 1.1 Funções Utilitárias e Auxiliares

#### `void reverterString(string &str)`
* **Lógica:** Implementa o algoritmo clássico de dois ponteiros (`inicio` e `fim`). O ponteiro `inicio` começa em `0` e incrementa, enquanto `fim` começa no tamanho da string menos 1 e decrementa. Em cada passo, os caracteres nestas posições são trocados via variável temporária `temp`. O laço termina quando os ponteiros se cruzam.
* **Nota Curiosa:** Embora declarada, esta função **não é chamada por nenhuma outra rotina do código**, configurando um código morto (*dead code*).

#### `int stringParaInt(string str)`
* **Lógica:** Converte uma cadeia de caracteres contendo dígitos numéricos em um tipo inteiro decimal. Percorre a string da esquerda para a direita, multiplicando o `resultado` acumulado por 10 e adicionando o valor inteiro do caractere atual. O valor numérico é obtido subtraindo o caractere `'0'` (através do mapeamento da tabela ASCII).

#### `bool validar(string valor, int base)`
* **Lógica:** Garante a consistência dos dados de entrada antes da conversão. Ela verifica se cada caractere da string pertence ao alfabeto aceito pela base numérica especificada:
  * **Base 2:** Aceita apenas `'0'` e `'1'`.
  * **Base 8:** Aceita caracteres entre `'0'` e `'7'`.
  * **Base 16:** Aceita dígitos entre `'0'` e `'9'` e letras de `'A'` a `'F'` (maiúsculas ou minúsculas).
* Retorna `true` se a cadeia for válida e `false` caso encontre algum caractere ilegal.

#### `string ajustarBits(string binario, int grupo)`
* **Lógica:** Insere caracteres `'0'` à esquerda de uma string binária até que o tamanho total da string seja um múltiplo exato do parâmetro `grupo`. Isso é essencial para as conversões diretas entre Binário <-> Octal (onde os grupos devem ser de 3 bits) e Binário <-> Hexadecimal (grupos de 4 bits).

---

### 1.2 Algoritmos de Conversão Inteira Básica (Decimal -> Outras Bases)

Essas funções aplicam o método de divisões sucessivas pela base de destino. O resto de cada divisão compõe o dígito da nova base, mapeado do bit/dígito menos significativo para o mais significativo.

#### `string converterBinario(int valor)` / `string converterOctal(int valor)`
* **Lógica:** Se o valor for 0, retorna `"0"`. Caso contrário, executa um laço `while` dividindo o número por 2 (ou 8) sucessivamente. Os restos são armazenados sequencialmente em um vetor estático de inteiros de tamanho 32 (`binario[32]` ou `octal[32]`). Por fim, um laço `for` percorre esse vetor de trás para frente, concatenando os números convertidos em caracteres à string de `resultado`.

#### `string converterHexadecimal(int valor)`
* **Lógica:** Segue o mesmo princípio de divisões sucessivas, mas o divisor é 16. O vetor temporário armazena caracteres (`char hexa[32]`). Caso o resto da divisão seja menor que 10, converte o dígito adicionando `'0'`. Se o resto estiver entre 10 e 15, faz o mapeamento para as letras de 'A' a 'F' utilizando a expressão `(resto - 10) + 'A'`. A string final é montada invertendo a ordem de leitura do vetor.

---

### 1.3 Algoritmos de Conversão de Bases para Decimal

Estas funções realizam o somatório posicional pesado (Polinômio de Leibniz), onde cada dígito é multiplicado pela base elevada à sua respectiva posição (índice da direita para a esquerda).

#### `int biDecimal(string valorInicial)` / `int octDecimal(string valorInicial)`
* **Lógica:** Primeiro, a string é convertida para um inteiro decimal tradicional usando `stringParaInt` (o que é conceitualmente incorreto para binários/octais longos). Em seguida, calcula-se a quantidade de algarismos usando `log10(abs(valor)) + 1` para alocar dinamicamente um vetor do tamanho exato (`new int[tamanho]`). O número é fragmentado dígito a dígito através do operador de resto por 10 (`valor % 10`). Por fim, percorre-se o vetor calculando a potência da base original: $\text{digito} \times \text{base}^i$. Ao fim, a memória alocada é liberada com `delete[]`.

#### `int hexDecimal(string valorInicial)`
* **Lógica:** Aloca dinamicamente um vetor com base no tamanho real da string recebida (`valorInicial.length()`). Mapeia cada caractere hexadecimal individual para o seu valor numérico correspondente de 0 a 15 usando estruturas condicionais (`if/else`). Em seguida, percorre o vetor de trás para frente, acumulando o valor decimal através de multiplicações por potências de 16 (`pow(16, expoente)`). Libera a memória com `delete[]` antes de retornar.

---

### 1.4 Algoritmos de Conversão Direta entre Bases

#### `string binarioParaOctal(string bin)` / `string binarioParaHexa(string bin)`
* **Lógica:** Ajusta o tamanho da string binária usando `ajustarBits`. Depois, fragmenta a string em sub-cadeias fixas de 3 ou 4 caracteres através da função `.substr(i, tamanho)`. Cada sub-cadeia é comparada com uma tabela indexada de strings estáticas (vetores simulando tabelas de busca). Ao encontrar a correspondência exata, o índice ou o símbolo correspondente é adicionado ao resultado.

#### `string octalParaBinario(string oct)`
* **Lógica:** Percorre cada caractere da string octal, subtrai `'0'` para obter o índice numérico direto e busca em um vetor de strings estático (`tabelaOctal`) o equivalente binário de 3 bits daquele caractere, concatenando tudo de forma direta.

#### `string converterEntreBases(string valor, int baseOrigem, int baseDestino)`
* **Lógica:** Uma centralizadora genérica. Valida a entrada, verifica se as bases são iguais e, se não forem, realiza uma ponte conversora: converte o valor original para a base decimal usando `converterParaDecimal` e, logo em seguida, converte este valor intermediário para a base de destino através de `converterDeDecimal`.

---

### 1.5 Tratamento de Números Fracionários (Ponto Flutuante)

#### `string converterFracionario(double parteFracionaria, int base)`
* **Lógica:** Isola a parte decimal pura (menor que 1). Multiplica a fração sucessivamente pela base de destino. A parte inteira resultante da multiplicação torna-se o dígito na nova base (convertido para caractere numérico ou letra de 'A' a 'F'). A parte inteira é então subtraída e o processo se repete com a nova fração restante. O algoritmo possui uma trava de segurança limitando o cálculo a 16 casas decimais. Caso a fração não zere até lá, o fluxo é encerrado e concatena-se o aviso `" (TRUNCADO)"`.

#### `string converterBinarioF(double valor)` / `converterOctalF(...)` / `converterHexadecimalF(...)`
* **Lógica:** Separam explicitamente a parte inteira e a parte fracionária do `double` original (`long long parteInteira = (long long)valor; double parteFrac = valor - parteInteira;`). A parte inteira é convertida utilizando o algoritmo padrão de divisões sucessivas adaptado para suportar variáveis do tipo `long long`. O resultado inteiro é concatenado com o ponto decimal e o retorno de `converterFracionario(parteFrac, base)`.

#### `double converterParaDecimalF(string valor, int base)`
* **Lógica:** Normaliza a entrada substituindo eventuais vírgulas por pontos decimais. Divide a string em duas sub-strings usando o caractere `'.'` como delimitador: a string `inteira` e a string `fracionaria`.
  * **Parte Inteira:** Processada de forma análoga aos métodos polinomiais com expoentes positivos crescentes.
  * **Parte Fracionária:** Cada dígito na posição $i$ (indexada a partir de 0) é multiplicado pela base elevada a um expoente negativo: $\text{digito} \times \text{base}^{-(i + 1)}$. Ambos os resultados são somados e retornados como um `double`.

---

### 1.6 Funções de Rastreamento (Modo Trace / Passo-a-Passo)

#### As funções terminadas em `Trace` (`converterBinarioTrace`, `biDecimalTrace`, etc.)
* **Lógica:** São réplicas exatas dos algoritmos internos de conversão descritos acima, porém enriquecidas com comandos de saída (`cout`). Elas imprimem cabeçalhos formatados, linhas divisórias e tabelas textuais simulando planilhas estruturadas (`Dividendo | Divisor | Quociente | Resto` ou `Posicao | Digito | Multiplicador | Resultado`). Isso permite ao usuário final visualizar a execução da matemática discreta passo a passo no terminal.

---

### 1.7 Execução em Lote (Modo Batch)

#### `void processarBatch()`
* **Lógica:** Implementa persistência e leitura de dados em arquivos através das streams `ifstream` e `ofstream`. Busca um arquivo chamado `entrada.csv`. Lê o arquivo linha por linha usando `getline`. Para cada linha, realiza uma varredura manual com `.find(';')` para quebrar o texto nos três campos obrigatórios: `valor`, `baseOrigem` e `baseDestino`. Converte as strings das bases em números inteiros, executa a conversão chamando `converterEntreBases` e salva os dados computados no arquivo `saida.csv` no formato estruturado `valor_original;base_origem;valor_convertido;base_destino`. Possui tratamento de exceções genérico (`try/catch (...)`) para evitar travamento do programa por dados corrompidos.

---

## 2. Mapa de Conexões e Fluxo de Execução

O sistema funciona como uma árvore direcionada orientada pelo Menu Principal na função `main()`. A hierarquia abaixo ilustra o fluxo de conexões quando um usuário ou arquivo solicita uma conversão:

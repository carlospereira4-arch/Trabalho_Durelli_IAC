===============================================================================
       GUIA DE LEITURA SEQUENCIAL DO CÓDIGO - CONVERSOR DE BASES
===============================================================================

Este documento explica a estrutura do código-fonte de forma linear, exatamente
na ordem em que as funções aparecem no arquivo, de cima para baixo. Use este 
guia para acompanhar a leitura do código junto com o seu colaborador.

-------------------------------------------------------------------------------
1. DIRETIVAS DE INCLUSÃO E PROTÓTIPOS
-------------------------------------------------------------------------------
* Linhas Iniciais: O código começa importando as bibliotecas necessárias:
  - <iostream>: Para entrada e saída de dados no terminal (cin/cout).
  - <string>: Para manipulação de textos.
  - <cmath>: Para operações matemáticas (como a função pow() de potência).
  - <fstream>: Para ler e gravar arquivos externos (modo Batch).
* Protótipos: Declarações rápidas de 'stringParaInt' e 'validar' apenas para 
  que o compilador saiba que elas existem antes de serem chamadas.

-------------------------------------------------------------------------------
2. FUNÇÃO UTILITÁRIA DE INVERSÃO
-------------------------------------------------------------------------------
* void reverterString(string &str)
  - O que faz: Inverte o texto de uma string diretamente na memória.
  - Como funciona: Usa dois ponteiros (um no início e um no fim do texto) que 
    vão caminhando para o centro e trocando os caracteres de lugar.
  - Importância: É a base que limpa o resultado das conversões inteiras abaixo.

-------------------------------------------------------------------------------
3. TRATAMENTO DE FRAÇÕES (PONTO FLUTUANTE)
-------------------------------------------------------------------------------
* string converterFracionario(double parteFracionaria, int base)
  - O que faz: Converte apenas a parte quebrada (depois da vírgula) de um número.
  - Como funciona: Multiplica a fração sucessivamente pela base destino. A parte
    inteira vira o dígito (ou letra A-F) e o resto continua multiplicando. Tem
    uma trava de segurança de 16 casas decimais para não entrar em loop infinito.

-------------------------------------------------------------------------------
4. CONVERSÕES INTEIRAS (DECIMAL -> OUTRAS BASES)
-------------------------------------------------------------------------------
As três funções abaixo pegam um número decimal inteiro e aplicam o método de 
divisões sucessivas pela base de destino:
* string converterBinario(int valor)       -> Divide por 2 sucessivamente.
* string converterOctal(int valor)         -> Divide por 8 sucessivamente.
* string converterHexadecimal(int valor)   -> Divide por 16 e converte restos 
                                              maiores que 9 em letras (A-F).
Nota: Todas elas jogam os restos na string e chamam 'reverterString' no final.

-------------------------------------------------------------------------------
5. CONVERSÕES FRACIONÁRIAS COMPLETA (DECIMAL COM VÍRGULA -> OUTRAS BASES)
-------------------------------------------------------------------------------
As três funções seguintes tratam números reais (com ponto flutuante), separando
o número em duas partes:
* string converterBinarioF(double valor)
* string converterOctalF(double valor)
* string converterHexadecimalF(double valor)
  - Como funcionam: Isolam a parte inteira (fazendo um cast para long long) e a
    parte fracionária. Convertem a parte inteira usando divisões, chamam a 
    'reverterString', e no final grudam o ponto decimal com o resultado retornado 
    pela função 'converterFracionario'.

-------------------------------------------------------------------------------
6. CONVERSÃO FRACIONÁRIA INVERSA (QUALQUER BASE COM VÍRGULA -> DECIMAL)
-------------------------------------------------------------------------------
* double converterParaDecimalF(string valor, int base)
  - O que faz: Pega um número em qualquer base (ex: "101.101" ou "C.8") e o 
    transforma de volta em um double decimal.
  - Como funciona: Limpa o texto mudando vírgulas por pontos, quebra a string no 
    caractere '.' em duas metades (inteira e fracionária). A inteira é multiplicada
    pela base com expoentes positivos (base^2, base^1...) e a fracionária é 
    multiplicada por expoentes negativos (base^-1, base^-2...).

-------------------------------------------------------------------------------
7. CONVERSÕES DE BASES INTEIRAS PARA DECIMAL
-------------------------------------------------------------------------------
Estas funções pegam textos em bases específicas e transformam em inteiros decimais
usando o somatório posicional (Polinômio de Leibniz):
* int biDecimal(string valorInicial)  -> Converte binário para decimal.
* int octDecimal(string valorInicial) -> Converte octal para decimal.
* int hexDecimal(string valorInicial) -> Converte hexadecimal para decimal.
  - Como funcionam: Varrem a string da direita para a esquerda. Cada caractere é
    transformado em seu valor numérico real (removendo o peso ASCII ou tratando 
    letras) e multiplicado pela base elevada à posição do dígito.

-------------------------------------------------------------------------------
8. CONVERSÕES DIRETAS ENTRE BASES (SEM PASSAR POR DECIMAL)
-------------------------------------------------------------------------------
* string ajustarBits(string binario, int grupo)
  - Preenche o binário com '0's à esquerda para que o tamanho vire múltiplo do 
    grupo (3 para octal, 4 para hexadecimal).
* string binarioParaOctal(string bin) e string binarioParaHexa(string bin)
  - Separam o binário em blocos (de 3 ou 4 bits) e fazem uma busca de padrão em 
    uma tabela estática (vetor) para traduzir direto para o caractere final.
* string octalParaBinario(string oct)
  - Traduz cada dígito do octal diretamente para o seu bloco correspondente de 
    3 bits usando uma tabela de busca.

-------------------------------------------------------------------------------
9. GERENCIADORES E VALIDATÓRIOS
-------------------------------------------------------------------------------
* bool validar(string valor, int base)
  - Garante que o usuário não digitou, por exemplo, o número '2' em um binário, 
    ou '9' em um octal. Retorna falso se achar caracteres ilegais.
* int stringParaInt(string str)
  - Converte uma string numérica simples em um int matemático puro.
* int converterParaDecimal(...) e string converterDeDecimal(...)
  - São funções "roteadoras". Elas apenas recebem a base desejada e usam ifs 
    para decidir qual das funções específicas criadas acima devem chamar.
* string converterEntreBases(string valor, int baseOrigem, int baseDestino)
  - A função ponte: Valida os dados, transforma a origem em decimal e depois 
    transforma esse decimal na base de destino.

-------------------------------------------------------------------------------
10. FUNÇÕES DE TRACE (PASSO-A-PASSO NO TERMINAL)
-------------------------------------------------------------------------------
* Todas as funções terminadas com o sufixo 'Trace'
  - O que são: São cópias exatas dos algoritmos de conversão explicados acima.
  - Diferencial: Elas possuem comandos 'cout' espalhados por dentro dos loops. 
    Em vez de apenas entregar o resultado, elas desenham tabelas textuais no 
    terminal mostrando o dividendo, divisor, quociente e resto de cada etapa, 
    servindo como uma ferramenta educacional.

-------------------------------------------------------------------------------
11. PROCESSAMENTO EM LOTE (MODO BATCH)
-------------------------------------------------------------------------------
* void processarBatch()
  - O que faz: Executa conversões automáticas em massa.
  - Como funciona: Abre um arquivo chamado 'entrada.csv', lê linha por linha, 
    fatia o texto onde encontra os pontos e vírgulas (';') para descobrir o 
    valor, a base de origem e a base de destino. Processa a conversão e janta 
    tudo formatado para dentro de um arquivo de saída chamado 'saida.csv'.

-------------------------------------------------------------------------------
12. FUNÇÃO PRINCIPAL (O MOTOR DO SISTEMA)
-------------------------------------------------------------------------------
* int main()
  - É o ponto de entrada do programa. Imprime o menu principal na tela, captura 
    a opção do usuário e usa uma árvore de condições (if/else) para direcionar o 
    fluxo para a opção escolhida (Batch, Conversão Direta, Fracionária ou Trace), 
    gerenciando as entradas de teclado (cin) e saídas de tela (cout).
===============================================================================
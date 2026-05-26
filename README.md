# Trabalho_Durelli_IAC

Trabalho em duplas da dsiciplina Introdução a Computação com o professor RAFAEL SERAPILHA DURELLI; Grupo: Carlos Henrique Pereira, Gabriel Augusto de Moura Veloso Murta;
---
Link do Vídeo Explicativo no Youtube: [https://youtu.be/IJHiqxAaGAY]
---

## 📋 Descrição do Projeto

**Conversor de Bases Numérico Otimizado** é uma aplicação em C++ que realiza conversões entre diferentes sistemas numéricos (binário, octal, decimal e hexadecimal) com suporte a números inteiros e fracionários.

Este projeto foi desenvolvido como trabalho prático da disciplina de Introdução à Computação, demonstrando conceitos fundamentais de estruturas de dados, algoritmos de conversão e processamento de arquivos.

---

## ✨ Funcionalidades Principais

- **Conversões Numéricas Diretas**: Decimal ↔ Binário, Octal, Hexadecimal
- **Conversões Bidirecionais**: Entre qualquer par de bases (2, 8, 10, 16)
- **Suporte a Números Fracionários**: Conversão precisa de partes inteiras e fracionárias
- **Trace/Rastreamento**: Visualização passo-a-passo do algoritmo de conversão
- **Modo Batch**: Processamento em lote via arquivo CSV (`entrada.csv` → `saida.csv`)
- **Modo Quiz**: Desafio interativo com 5 níveis de dificuldade
- **Calculadora de Máximos**: Cálculo de maior valor representável com k bits (2^k - 1)

---

## 🛠️ Requisitos

- Compilador C++ (GCC, Clang ou MSVC)
- C++11 ou superior
- Sistema operacional: Linux, macOS ou Windows

---

## 📦 Compilação e Execução

### Compilação
```bash
g++ final_function.cpp -o final_function
```

### Execução
```bash
./final_function
```

Ou diretamente:
```bash
g++ final_function.cpp -o final_function && ./final_function
```

---

## 🎮 Menu de Opções

O programa oferece as seguintes opções após iniciar:

```
1: Decimal → (Binário, Octal ou Hexadecimal)
2: (Binário, Octal ou Hexadecimal) → Decimal
3: Binário ↔ (Octal ou Hexadecimal) Direto
4: Octal → Hexadecimal (via Binário)
5: Modo Passo-a-Passo (com trace do algoritmo)
6: Conversão com Números Fracionários
7: MODO QUIZ (Desafio aleatório)
8: CALCULADORA DE MÁXIMOS (2^k - 1)
0: Modo Batch (arquivo entrada.csv → saida.csv)
```

---

## 📁 Estrutura do Projeto

```
.
├── final_function.cpp              # Código-fonte principal (versão otimizada)
├── final_function                  # Executável compilado
├── entrada.csv                     # Arquivo de entrada para modo batch
├── saida.csv                       # Arquivo de saída (gerado pelo modo batch)
├── main.cpp                        # Arquivo de testes/desenvolvimento
├── main                            # Executável de testes
├── README.md                       # Este arquivo
├── explicação.md                   # Documentação técnica detalhada
├── guia_leitura.md                # Guia de leitura do código
└── [function1-9].cpp              # Funções de conversão (desenvolvimento)
```

---

## 📝 Modo Batch - Entrada e Saída

### Formato de Entrada (`entrada.csv`)
```
valor;base_origem;base_destino
1010;2;10
FF;16;10
123;10;2
```

### Formato de Saída (`saida.csv`)
```
valor;base_origem;resultado;base_destino
1010;2;10;10
FF;16;255;10
123;10;1111011;2
```

---

## 🔍 Exemplos de Uso

### Conversão Simples
- Converter `255` (decimal) para hexadecimal: `FF`
- Converter `1010` (binário) para decimal: `10`
- Converterter `77` (octal) para binário: `111111`

### Números Fracionários
- `3.5` em base 10 para binário: `11.1`
- `A.8` em base 16 para decimal: `10.5`

### Modo Quiz
Teste seus conhecimentos respondendo perguntas aleatórias sobre conversão de bases!

---

## 🧪 Validação

O programa realiza validações robustas:
- ✓ Verificação de dígitos válidos para cada base
- ✓ Detecção de formato inválido em modo batch
- ✓ Tratamento de números fracionários com ponto ou vírgula
- ✓ Tratamento especial para conversões envolvendo Base 10
- ✓ Relatório de erros com número da linha

---

## 💡 Funcionalidades Destacadas

### Processamento em Lote
O modo batch permite processar múltiplas conversões simultaneamente, ideal para validação em massa e processamento automatizado.

### Trace Educacional
Visualize cada etapa do algoritmo de conversão com uma tabela detalhada de divisões/multiplicações.

### Suporte a Bases Fracionárias
Conversão precisa de números com partes fracionárias utilizando aritmética de ponto flutuante otimizada.

---

## 📊 Arquivos de Desenvolvimento

- `function1.cpp` a `function9.cpp`: Versões anteriores com diferentes abordagens
- `original_united_functions.cpp`: Versão consolidada antes das otimizações
- `united_functions.cpp`: Versão intermediária com funções unificadas

---

## 👥 Autores

- **Carlos Henrique Pereira**
- **Gabriel Augusto de Moura Veloso Murta**

**Professor**: RAFAEL SERAPILHA DURELLI  
**Disciplina**: Introdução à Computação (IAC)

---

## 📄 Documentação Adicional

Para informações técnicas detalhadas, consulte:
- `explicação.md` - Explicação completa dos algoritmos
- `guia_leitura.md` - Guia para compreender o código

---

## 🔧 Possíveis Melhorias Futuras

- [ ] Interface gráfica (GUI)
- [ ] Suporte a mais bases numéricas
- [ ] Otimização de performance para números muito grandes
- [ ] Exportação em múltiplos formatos
- [ ] Validação de entrada em tempo real

---

## 📜 Licença

Este projeto é fornecido como trabalho acadêmico.

---
# Suíte de Testes - Conversor de Bases Otimizado

Este documento contém 30 casos de teste estruturados para validar todas as funcionalidades (F1 a F10) do sistema, cobrindo casos nominais, limites e tratamento de erros.

## Tabela de Casos de Teste

| ID | Função | Entrada | Saída Esperada | Tipo de Teste |
|:---|:---|:---|:---|:---|
| 01 | **F1** (Dec → Bin) | 0 | "0" | Limite Zero |
| 02 | **F1** (Dec → Oct) | 255 | "377" | Valor Médio |
| 03 | **F1** (Dec → Hex) | 4095 | "FFF" | Valor Limite Hex |
| 04 | **F2** (Bin → Dec) | "1010" | 10 | Conversão Simples |
| 05 | **F2** (Hex → Dec) | "1A3" | 419 | Alfanumérico |
| 06 | **F3** (Bin → Oct) | "111111" | "77" | Agrupamento (3 em 3) |
| 07 | **F3** (Bin → Hex) | "10110" | "16" | Padding Automático |
| 08 | **F4** (Oct → Hex) | "777" | "1FF" | Ponte Binária |
| 09 | **F5** (Validar) | "102", Base 2 | `false` | Caractere Inválido |
| 10 | **F5** (Validar) | "G1", Base 16 | `false` | Fora do Intervalo A-F |
| 11 | **F6** (Frac → Bin) | 0.5 | "0.1" | Fração Exata |
| 12 | **F6** (Frac → Bin) | 0.1 | "0.0001100..." | Dízima (Truncado) |
| 13 | **F6** (Hex.F → Dec) | "1.A" | 1.625 | Fracionário Complexo |
| 14 | **F7** (Trace) | 13 (Dec → Bin) | Tabela completa | Visual/Didático |
| 15 | **F8** (Batch) | Linha vazia | Pular linha | Robustez |
| 16 | **F8** (Batch) | "ABC;10;2" | ERRO (Linha inválida) | Tratamento Exceção |
| 17 | **F9** (Quiz) | Nível 1 | Números até 15 | Dificuldade |
| 18 | **F9** (Quiz) | "ff" (Entrada) | CORRETO (Case Insensitive) | UX/Normalização |
| 19 | **F10** (Max) | 8 bits | 255 (FF, 377, 11111111) | Limite de Arquitetura |
| 20 | **F10** (Max) | 16 bits | 65535 | Limite Inteiro Curto |
| 21 | **Util** (Reverter) | "ABC" | "CBA" | Manipulação Memória |
| 22 | **Util** (Ajustar) | "1", Tamanho 4 | "0001" | Padding de Bits |
| 23 | **F1** (Dec → Bin) | 1024 | "10000000000" | Potência de 2 |
| 24 | **F2** (Oct → Dec) | "007" | 7 | Zeros à Esquerda |
| 25 | **F5** (Validar) | "", Base 10 | `false` | String Vazia |
| 26 | **F6** (Dec → Oct) | 0.125 | "0.1" | Fração Octal |
| 27 | **F8** (Batch) | Arquivo inexistente | Mensagem de Erro | File Handling |
| 28 | **F9** (Quiz) | Semente "XPTO" | Perguntas novas | Aleatoriedade |
| 29 | **F1** (Dec → Hex) | 10 | "A" | Conversão de Letra |
| 30 | **F10** (Max) | 32 bits | 4294967295 | Limite Unsigned Int |

## Instruções para Execução dos Testes

1. **Testes Unitários:** Insira os valores de entrada manualmente nas opções do menu correspondentes.
2. **Teste de Stress (Batch):** Crie um arquivo `entrada.csv` com os casos das funções F1, F2, F3 e F4 para validar o processamento em massa.
3. **Validação de Erros:** Tente inserir caracteres proibidos em bases específicas para confirmar o funcionamento da funcionalidade **F5 (Fail-Fast)**.

**Última atualização**: Maio de 2026

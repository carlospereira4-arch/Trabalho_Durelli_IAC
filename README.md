# Trabalho_Durelli_IAC

Trabalho em duplas da dsiciplina Introdução a Computação com o professor RAFAEL SERAPILHA DURELLI; Grupo: Carlos Henrique Pereira, Gabriel Augusto de Moura Veloso Murta;

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

**Última atualização**: Maio de 2026

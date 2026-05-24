#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

int stringParaInt(string str);
bool validar(string valor, int base);

void reverterString(string &str) {
    int inicio = 0, fim = str.length() - 1;
    while (inicio < fim) {
        char temp = str[inicio];
        str[inicio] = str[fim];
        str[fim] = temp;
        inicio++;
        fim--;
    }
}

string converterFracionario(double parteFracionaria, int base) {
    if (parteFracionaria == 0) return "";
    string resultado = ".";
    int casas = 0;
    bool truncado = false;

    while (parteFracionaria > 0 && casas < 16) {
        parteFracionaria *= base;
        int digito = (int)parteFracionaria;

        if (digito < 10) resultado += (digito + '0');
        else resultado += (digito - 10 + 'A');

        parteFracionaria -= digito;
        casas++;
        if (casas == 16 && parteFracionaria > 0) truncado = true;
    }

    if (truncado) resultado += " (TRUNCADO)";
    return resultado;
}


string converterBinario(int valor) {
    if (valor == 0) return "0";
    string resultado = "";
    while (valor > 0) {
        resultado += (valor % 2) + '0';
        valor = valor / 2;
    }
    reverterString(resultado);
    return resultado;
}

string converterOctal(int valor) {
    if (valor == 0) return "0";
    string resultado = "";
    while (valor > 0) {
        resultado += (valor % 8) + '0';
        valor = valor / 8;
    }
    reverterString(resultado);
    return resultado;
}

string converterHexadecimal(int valor) {
    if (valor == 0) return "0";
    string resultado = "";
    while (valor > 0) {
        int resto = valor % 16;
        if (resto < 10) resultado += (resto + '0');
        else resultado += (resto - 10) + 'A';
        valor = valor / 16;
    }
    reverterString(resultado);
    return resultado;
}


string converterBinarioF(double valor) {
    long long parteInteira = (long long)valor;
    double parteFrac = valor - parteInteira;

    if (valor == 0) return "0";
    string resultado = "";

    if (parteInteira == 0) resultado = "0";
    else {
        long long temp = parteInteira;
        while (temp > 0) {
            resultado += (temp % 2) + '0';
            temp = temp / 2;
        }
        reverterString(resultado);
    }
    return resultado + converterFracionario(parteFrac, 2);
}

string converterOctalF(double valor) {
    long long parteInteira = (long long)valor;
    double parteFrac = valor - parteInteira;

    if (valor == 0) return "0";
    string resultado = "";

    if (parteInteira == 0) resultado = "0";
    else {
        long long temp = parteInteira;
        while (temp > 0) {
            resultado += (temp % 8) + '0';
            temp = temp / 8;
        }
        reverterString(resultado);
    }
    return resultado + converterFracionario(parteFrac, 8);
}

string converterHexadecimalF(double valor) {
    long long parteInteira = (long long)valor;
    double parteFrac = valor - parteInteira;

    if (valor == 0) return "0";
    string resultado = "";

    if (parteInteira == 0) resultado = "0";
    else {
        long long temp = parteInteira;
        while (temp > 0) {
            int resto = temp % 16;
            if (resto < 10) resultado += resto + '0';
            else resultado += (resto - 10) + 'A';
            temp = temp / 16;
        }
        reverterString(resultado);
    }
    return resultado + converterFracionario(parteFrac, 16);
}

double converterParaDecimalF(string valor, int base) {
    for (int i = 0; i < valor.length(); i++) {
        if (valor[i] == ',') valor[i] = '.';
    }

    int pontoPos = -1;
    for (int i = 0; i < valor.length(); i++) {
        if (valor[i] == '.') {
            pontoPos = i;
            break;
        }
    }

    string inteira = (pontoPos == -1) ? valor : valor.substr(0, pontoPos);
    string fracionaria = (pontoPos == -1) ? "" : valor.substr(pontoPos + 1);

    double decimal = 0;

    for (int i = 0; i < inteira.length(); i++) {
        int digito;
        char c = inteira[i];
        if (c >= 'A' && c <= 'F') digito = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') digito = c - 'a' + 10;
        else digito = c - '0';
        decimal += digito * pow(base, inteira.length() - 1 - i);
    }

    for (int i = 0; i < fracionaria.length(); i++) {
        int digito;
        char c = fracionaria[i];
        if (c >= 'A' && c <= 'F') digito = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') digito = c - 'a' + 10;
        else digito = c - '0';
        decimal += digito * pow(base, -(i + 1));
    }

    return decimal;
}


int biDecimal(string valorInicial) {
    int decimal = 0;
    int tamanho = valorInicial.length();
    for (int i = 0; i < tamanho; i++) {
        int digito = valorInicial[tamanho - 1 - i] - '0';
        decimal += digito * pow(2, i);
    }
    return decimal;
}

int octDecimal(string valorInicial) {
    int decimal = 0;
    int tamanho = valorInicial.length();
    for (int i = 0; i < tamanho; i++) {
        int digito = valorInicial[tamanho - 1 - i] - '0';
        decimal += digito * pow(8, i);
    }
    return decimal;
}

int hexDecimal(string valorInicial) {
    int tamanho = valorInicial.length();
    int decimal = 0;
    int expoente = 0;
    for (int i = tamanho - 1; i >= 0; i--) {
        int digito;
        char c = valorInicial[i];
        if (c >= 'A' && c <= 'F') digito = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') digito = c - 'a' + 10;
        else digito = c - '0';

        decimal += digito * pow(16, expoente);
        expoente++;
    }
    return decimal;
}


string ajustarBits(string binario, int grupo) {
    while (binario.length() % grupo != 0) {
        binario = "0" + binario;
    }
    return binario;
}

string binarioParaOctal(string bin) {
    bin = ajustarBits(bin, 3);
    string resultado = "";
    string tabelaOctal[] = {"000", "001", "010", "011", "100", "101", "110", "111"};
    for (int i = 0; i < bin.length(); i += 3) {
        string grupo = bin.substr(i, 3);
        for (int j = 0; j < 8; j++) {
            if (grupo == tabelaOctal[j]) resultado += (j + '0');
        }
    }
    return resultado;
}

string binarioParaHexa(string bin) {
    bin = ajustarBits(bin, 4);
    string resultado = "";
    string tabelaHexa[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    char simbolosHexa[] = "0123456789ABCDEF";
    for (int i = 0; i < bin.length(); i += 4) {
        string group = bin.substr(i, 4);
        for (int j = 0; j < 16; j++) {
            if (group == tabelaHexa[j]) resultado += simbolosHexa[j];
        }
    }
    return resultado;
}

string octalParaBinario(string oct) {
    string resultado = "";
    string tabelaOctal[] = {"000", "001", "010", "011", "100", "101", "110", "111"};
    for (int i = 0; i < oct.length(); i++) {
        int digito = oct[i] - '0';
        if (digito >= 0 && digito <= 7) resultado += tabelaOctal[digito];
    }
    return resultado;
}

bool validar(string valor, int base) {
    for (int i = 0; i < valor.length(); i++) {
        char c = valor[i];
        if (base == 2 && (c != '0' && c != '1')) return false;
        if (base == 8 && (c < '0' || c > '7')) return false;
        if (base == 16) {
            if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) return false;
        }
    }
    return true;
}

int stringParaInt(string str) {
    int resultado = 0;
    for (int i = 0; i < str.length(); i++) {
        resultado = resultado * 10 + (str[i] - '0');
    }
    return resultado;
}

int converterParaDecimal(string valor, int base) {
    if (base == 2) return biDecimal(valor);
    else if (base == 8) return octDecimal(valor);
    else if (base == 16) return hexDecimal(valor);
    return 0;
}

string converterDeDecimal(int valor, int base) {
    if (base == 2) return converterBinario(valor);
    else if (base == 8) return converterOctal(valor);
    else if (base == 16) return converterHexadecimal(valor);
    return "0";
}

string converterEntreBases(string valor, int baseOrigem, int baseDestino) {
    if (!validar(valor, baseOrigem)) return "ERRO";
    if (baseOrigem == baseDestino) return valor;

    int decimal = converterParaDecimal(valor, baseOrigem);
    return converterDeDecimal(decimal, baseDestino);
}


void converterBinarioTrace(int valor) {
    cout << "\n=== CONVERSAO DECIMAL -> BINARIO ===" << endl;
    cout << "Valor: " << valor << endl;
    cout << "\nTabela de Divisoes:" << endl;
    cout << "Dividendo | Divisor | Quociente | Resto" << endl;
    cout << "----------|---------|-----------|-------" << endl;

    if (valor == 0) {
        cout << "Resultado: 0" << endl;
        return;
    }

    string restos = "";
    int temp = valor;

    while (temp > 0) {
        int quociente = temp / 2;
        int resto = temp % 2;
        restos += (resto + '0');
        cout << "   " << temp << "    |    2    |    " << quociente << "     |  " << resto << endl;
        temp = quociente;
    }

    cout << "\nLer restos de baixo para cima: ";
    string resultadoFinal = restos;
    reverterString(resultadoFinal);
    cout << resultadoFinal << endl;
    cout << "Resultado: " << converterBinario(valor) << endl;
}

void converterOctalTrace(int valor) {
    cout << "\n=== CONVERSAO DECIMAL -> OCTAL ===" << endl;
    cout << "Valor: " << valor << endl;
    cout << "\nTabela de Divisoes:" << endl;
    cout << "Dividendo | Divisor | Quociente | Resto" << endl;
    cout << "----------|---------|-----------|-------" << endl;

    if (valor == 0) {
        cout << "Resultado: 0" << endl;
        return;
    }

    string restos = "";
    int temp = valor;

    while (temp > 0) {
        int quociente = temp / 8;
        int resto = temp % 8;
        restos += (resto + '0');
        cout << "   " << temp << "    |    8    |    " << quociente << "     |  " << resto << endl;
        temp = quociente;
    }

    cout << "\nLer restos de baixo para cima: ";
    string resultadoFinal = restos;
    reverterString(resultadoFinal);
    cout << resultadoFinal << endl;
    cout << "Resultado: " << converterOctal(valor) << endl;
}

void converterHexadecimalTrace(int valor) {
    cout << "\n=== CONVERSAO DECIMAL -> HEXADECIMAL ===" << endl;
    cout << "Valor: " << valor << endl;
    cout << "\nTabela de Divisoes:" << endl;
    cout << "Dividendo | Divisor | Quociente | Resto" << endl;
    cout << "----------|---------|-----------|-------" << endl;

    if (valor == 0) {
        cout << "Resultado: 0" << endl;
        return;
    }

    string restos = "";
    int temp = valor;

    while (temp > 0) {
        int quociente = temp / 16;
        int resto = temp % 16;

        char restoChar = (resto < 10) ? (resto + '0') : (resto - 10 + 'A');
        restos += restoChar;

        cout << "   " << temp << "    |   16    |    " << quociente << "     |  " << restoChar << endl;
        temp = quociente;
    }

    cout << "\nLer restos de baixo para cima: ";
    string resultadoFinal = restos;
    reverterString(resultadoFinal);
    cout << resultadoFinal << endl;
    cout << "Resultado: " << converterHexadecimal(valor) << endl;
}

void biDecimalTrace(string valorInicial) {
    cout << "\n=== CONVERSAO BINARIO -> DECIMAL ===" << endl;
    cout << "Valor: " << valorInicial << endl;
    cout << "\nSomatorio Posicional (da direita para esquerda):" << endl;
    cout << "Posicao |  Digito  | Multiplicador | Resultado" << endl;
    cout << "--------|----------|---------------|----------" << endl;

    int tamanho = valorInicial.length();
    int decimal = 0;
    for (int i = 0; i < tamanho; i++) {
        int digito = valorInicial[tamanho - 1 - i] - '0';
        int parcela = digito * pow(2, i);
        decimal += parcela;
        cout << "   " << i << "    |    " << digito << "     |    2^" << i << "      |    " << parcela << endl;
    }
    cout << "\nResultado: " << decimal << endl;
}

void octDecimalTrace(string valorInicial) {
    cout << "\n=== CONVERSAO OCTAL -> DECIMAL ===" << endl;
    cout << "Valor: " << valorInicial << endl;
    cout << "\nSomatorio Posicional (da direita para esquerda):" << endl;
    cout << "Posicao |  Digito  | Multiplicador | Resultado" << endl;
    cout << "--------|----------|---------------|----------" << endl;

    int tamanho = valorInicial.length();
    int decimal = 0;
    for (int i = 0; i < tamanho; i++) {
        int digito = valorInicial[tamanho - 1 - i] - '0';
        int parcela = digito * pow(8, i);
        decimal += parcela;
        cout << "   " << i << "    |    " << digito << "     |    8^" << i << "      |    " << parcela << endl;
    }
    cout << "\nResultado: " << decimal << endl;
}

void hexDecimalTrace(string valorInicial) {
    cout << "\n=== CONVERSAO HEXADECIMAL -> DECIMAL ===" << endl;
    cout << "Valor: " << valorInicial << endl;
    cout << "\nSomatorio Posicional (da direita para esquerda):" << endl;
    cout << "Posicao | Digito | Valor | Multiplicador | Resultado" << endl;
    cout << "--------|--------|-------|---------------|----------" << endl;

    int tamanho = valorInicial.length();
    int decimal = 0;
    int expoente = 0;
    for (int i = tamanho - 1; i >= 0; i--) {
        int digito;
        char c = valorInicial[i];
        if (c >= 'A' && c <= 'F') digito = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') digito = c - 'a' + 10;
        else digito = c - '0';

        int parcela = digito * pow(16, expoente);
        decimal += parcela;
        cout << "   " << expoente << "    |   " << c << "    |  " << digito << "   |   16^" << expoente << "    |    " << parcela << endl;
        expoente++;
    }
    cout << "\nResultado: " << decimal << endl;
}

void binarioParaOctalTrace(string bin) {
    cout << "\n=== CONVERSAO BINARIO -> OCTAL ===" << endl;
    cout << "Valor original: " << bin << endl;

    string binAjustado = ajustarBits(bin, 3);
    cout << "Valor ajustado (grupos de 3): " << binAjustado << endl;

    cout << "\nAgrupamento de bits:" << endl;
    string tabelaOctal[] = {"000", "001", "010", "011", "100", "101", "110", "111"};
    string resultado = "";

    for (int i = 0; i < binAjustado.length(); i += 3) {
        string grupo = binAjustado.substr(i, 3);
        for (int j = 0; j < 8; j++) {
            if (grupo == tabelaOctal[j]) {
                cout << grupo << " -> " << j << endl;
                resultado += (j + '0');
            }
        }
    }
    cout << "\nResultado: " << resultado << endl;
}

void binarioParaHexaTrace(string bin) {
    cout << "\n=== CONVERSAO BINARIO -> HEXADECIMAL ===" << endl;
    cout << "Valor original: " << bin << endl;

    string binAjustado = ajustarBits(bin, 4);
    cout << "Valor ajustado (grupos de 4): " << binAjustado << endl;

    cout << "\nAgrupamento de bits:" << endl;
    string tabelaHexa[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    char simbolosHexa[] = "0123456789ABCDEF";
    string resultado = "";

    for (int i = 0; i < binAjustado.length(); i += 4) {
        string grupo = binAjustado.substr(i, 4);
        for (int j = 0; j < 16; j++) {
            if (grupo == tabelaHexa[j]) {
                cout << grupo << " -> " << simbolosHexa[j] << endl;
                resultado += simbolosHexa[j];
            }
        }
    }
    cout << "\nResultado: " << resultado << endl;
}

void octalParaBinarioTrace(string oct) {
    cout << "\n=== CONVERSAO OCTAL -> BINARIO ===" << endl;
    cout << "Valor: " << oct << endl;

    cout << "\nConversao de cada digito:" << endl;
    string tabelaOctal[] = {"000", "001", "010", "011", "100", "101", "110", "111"};
    string resultado = "";

    for (int i = 0; i < oct.length(); i++) {
        int digito = oct[i] - '0';
        if (digito >= 0 && digito <= 7) {
            cout << oct[i] << " -> " << tabelaOctal[digito] << endl;
            resultado += tabelaOctal[digito];
        }
    }
    cout << "\nResultado: " << resultado << endl;
}


void processarBatch() {
    string nomeArqEntrada = "entrada.csv";
    string nomeArqSaida = "saida.csv";

    ifstream entrada(nomeArqEntrada);
    ofstream saida(nomeArqSaida);

    if (!entrada.is_open()) {
        cout << "ERRO: Nao foi possivel abrir " << nomeArqEntrada << endl;
        return;
    }
    if (!saida.is_open()) {
        cout << "ERRO: Nao foi possivel criar " << nomeArqSaida << endl;
        entrada.close();
        return;
    }

    string linha;
    int contador = 0;
    int erros = 0;

    while (getline(entrada, linha)) {
        if (linha.empty()) continue;

        int pos1 = linha.find(';');
        int pos2 = linha.find(';', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos) {
            cout << "Linha " << contador + 1 << ": Formato invalido" << endl;
            erros++; contador++; continue;
        }

        string valor = linha.substr(0, pos1);
        string baseOrigemStr = linha.substr(pos1 + 1, pos2 - pos1 - 1);
        string baseDestinoStr = linha.substr(pos2 + 1);

        try {
            int baseOrigem = stringParaInt(baseOrigemStr);
            int baseDestino = stringParaInt(baseDestinoStr);

            string resultado = converterEntreBases(valor, baseOrigem, baseDestino);

            if (resultado == "ERRO") {
                cout << "Linha " << contador + 1 << ": Valor invalido" << endl;
                erros++;
            } else {
                saida << valor << ";" << baseOrigem << ";" << resultado << ";" << baseDestino << endl;
            }
        } catch (...) {
            cout << "Linha " << contador + 1 << ": Erro ao processar" << endl;
            erros++;
        }
        contador++;
    }

    entrada.close(); saida.close();
    cout << "Processamento concluido! Total: " << contador << " | Erros: " << erros << endl;
}


void modoQuiz() {
    string sementeInput;
    cout << "\n### MODO QUIZ (5 NIVEIS) ###" << endl;
    cout << "Digite qualquer palavra e ENTER para iniciar: ";
    cin >> sementeInput;

    int semente = 0;
    for (int i = 0; i < sementeInput.length(); i++) semente += sementeInput[i];

    int acertos = 0;
    int bases[] = {2, 8, 10, 16};

    for (int nivel = 1; nivel <= 5; nivel++) {
        int valorDecimal = (semente * nivel * 13) % (int)pow(2, nivel + 3) + (nivel * 5);

        int baseOrigem = bases[(semente + nivel) % 4];
        int baseDestino = bases[(semente + nivel + 1) % 4];

        string pergunta = (baseOrigem == 10) ? to_string(valorDecimal) : converterDeDecimal(valorDecimal, baseOrigem);
        string respostaCorreta = (baseDestino == 10) ? to_string(valorDecimal) : converterDeDecimal(valorDecimal, baseDestino);

        cout << "\nNivel " << nivel << " | Converta " << pergunta << " (Base " << baseOrigem << ") para a Base " << baseDestino << ": ";
        string respostaUsuario;
        cin >> respostaUsuario;

        for(int i=0; i < respostaUsuario.length(); i++)
            if(respostaUsuario[i] >= 'a' && respostaUsuario[i] <= 'z') respostaUsuario[i] -= 32;

        if (respostaUsuario == respostaCorreta) {
            cout << "CORRETO!" << endl;
            acertos++;
        } else {
            cout << "ERRO! A resposta era: " << respostaCorreta << endl;
        }
    }
    cout << "\nSua pontuacao final: " << acertos << "/5" << endl;
}


int main() {
    int menu;
    cout << "### CONVERSOR DE BASES OTIMIZADO ###" << endl;
    cout << "1: Decimal -> (Binario, Octal ou Hexadecimal)" << endl;
    cout << "2: (Binario, Octal ou Hexadecimal) -> Decimal" << endl;
    cout << "3: Binario <-> (Octal ou Hexadecimal) Direto" << endl;
    cout << "4: Octal -> Hexadecimal (via Binario)" << endl;
    cout << "5: Modo Passo-a-Passo (com trace do algoritmo)" << endl;
    cout << "6: Conversao com Numeros Fracionarios" << endl;
    cout << "7: MODO QUIZ (Desafio aleatorio)" << endl;
    cout << "0: Modo Batch (arquivo entrada.csv -> saida.csv)" << endl;
    cout << "Escolha a opcao: ";
    cin >> menu;

    if (menu == 1) {
        int valor, base;
        cout << "Valor decimal: "; cin >> valor;
        cout << "Base destino (2, 8, 16): "; cin >> base;
        if (base == 2) cout << "Binario: " << converterBinario(valor) << endl;
        else if (base == 8) cout << "Octal: " << converterOctal(valor) << endl;
        else if (base == 16) cout << "Hexadecimal: " << converterHexadecimal(valor) << endl;
        else cout << "ERRO: Base invalida." << endl;
    }
    else if (menu == 0) {
        processarBatch();
    }
    else if (menu == 2) {
        int tipo; string valor;
        cout << "Base origem (1:Bin, 2:Oct, 3:Hex): "; cin >> tipo;
        cout << "Digite o valor: "; cin >> valor;
        if (tipo == 1) {
            if (validar(valor, 2)) cout << "Decimal: " << biDecimal(valor) << endl;
            else cout << "ERRO: Digito invalido para Binario." << endl;
        }
        else if (tipo == 2) {
            if (validar(valor, 8)) cout << "Decimal: " << octDecimal(valor) << endl;
            else cout << "ERRO: Digito invalido para Octal." << endl;
        }
        else if (tipo == 3) {
            if (validar(valor, 16)) cout << "Decimal: " << hexDecimal(valor) << endl;
            else cout << "ERRO: Digito invalido para Hexadecimal." << endl;
        }
    }
    else if (menu == 3) {
        int b1, b2; string valor;
        cout << "Base inicial, Base final e Valor: "; cin >> b1 >> b2 >> valor;
        if (validar(valor, b1)) {
            if (b1 == 2 && b2 == 8) cout << "Resultado: " << binarioParaOctal(valor) << endl;
            else if (b1 == 2 && b2 == 16) cout << "Resultado: " << binarioParaHexa(valor) << endl;
            else if (b1 == 8 && b2 == 2) cout << "Resultado: " << octalParaBinario(valor) << endl;
            else cout << "ERRO: Essa conversao direta nao esta programada." << endl;
        } else cout << "ERRO: Valor invalido para a base " << b1 << endl;
    }
    else if (menu == 4) {
        string octal, bin;
        cout << "Valor Octal: "; cin >> octal;
        if (validar(octal, 8)) {
            bin = octalParaBinario(octal);
            cout << "Passagem Binaria: " << bin << endl;
            cout << "Resultado Hexadecimal: " << binarioParaHexa(bin) << endl;
        } else cout << "ERRO: Digito invalido para Octal." << endl;
    }
    else if (menu == 5) {
        int submenu;
        cout << "\n### MODO PASSO-A-PASSO ###" << endl;
        cout << "1: Decimal -> Binario (com divisoes)" << endl;
        cout << "2: Decimal -> Octal (com divisoes)" << endl;
        cout << "3: Decimal -> Hexadecimal (com divisoes)" << endl;
        cout << "4: Binario -> Decimal (com somatorio)" << endl;
        cout << "5: Octal -> Decimal (com somatorio)" << endl;
        cout << "6: Hexadecimal -> Decimal (com somatorio)" << endl;
        cout << "7: Binario -> Octal (com agrupamento)" << endl;
        cout << "8: Binario -> Hexadecimal (com agrupamento)" << endl;
        cout << "9: Octal -> Binario (com agrupamento)" << endl;
        cout << "Escolha a opcao: ";
        cin >> submenu;

        if (submenu == 1) { int valor; cout << "Valor decimal: "; cin >> valor; converterBinarioTrace(valor); }
        else if (submenu == 2) { int valor; cout << "Valor decimal: "; cin >> valor; converterOctalTrace(valor); }
        else if (submenu == 3) { int valor; cout << "Valor decimal: "; cin >> valor; converterHexadecimalTrace(valor); }
        else if (submenu == 4) { string valor; cout << "Valor binario: "; cin >> valor; if (validar(valor, 2)) biDecimalTrace(valor); else cout << "ERRO: Invalido." << endl; }
        else if (submenu == 5) { string valor; cout << "Valor octal: "; cin >> valor; if (validar(valor, 8)) octDecimalTrace(valor); else cout << "ERRO: Invalido." << endl; }
        else if (submenu == 6) { string valor; cout << "Valor hexadecimal: "; cin >> valor; if (validar(valor, 16)) hexDecimalTrace(valor); else cout << "ERRO: Invalido." << endl; }
        else if (submenu == 7) { string valor; cout << "Valor binario: "; cin >> valor; if (validar(valor, 2)) binarioParaOctalTrace(valor); else cout << "ERRO: Invalido." << endl; }
        else if (submenu == 8) { string valor; cout << "Valor binario: "; cin >> valor; if (validar(valor, 2)) binarioParaHexaTrace(valor); else cout << "ERRO: Invalido." << endl; }
        else if (submenu == 9) { string valor; cout << "Valor octal: "; cin >> valor; if (validar(valor, 8)) octalParaBinarioTrace(valor); else cout << "ERRO: Invalido." << endl; }
    }
    else if (menu == 6) {
        int submenu;
        cout << "\n### CONVERSAO COM NUMEROS FRACIONARIOS ###" << endl;
        cout << "1: Decimal (fracionario) -> Binario" << endl;
        cout << "2: Decimal (fracionario) -> Octal" << endl;
        cout << "3: Decimal (fracionario) -> Hexadecimal" << endl;
        cout << "4: Binario (com fracao) -> Decimal" << endl;
        cout << "5: Octal (com fracao) -> Decimal" << endl;
        cout << "6: Hexadecimal (com fracao) -> Decimal" << endl;
        cout << "Escolha a opcao: ";
        cin >> submenu;

        if (submenu == 1) { double valor; cout << "Valor decimal: "; cin >> valor; cout << "Binario: " << converterBinarioF(valor) << endl; }
        else if (submenu == 2) { double valor; cout << "Valor decimal: "; cin >> valor; cout << "Octal: " << converterOctalF(valor) << endl; }
        else if (submenu == 3) { double valor; cout << "Valor decimal: "; cin >> valor; cout << "Hexadecimal: " << converterHexadecimalF(valor) << endl; }
        else if (submenu == 4) { string valor; cout << "Valor binario: "; cin >> valor; cout << "Decimal: " << converterParaDecimalF(valor, 2) << endl; }
        else if (submenu == 5) { string valor; cout << "Valor octal: "; cin >> valor; cout << "Decimal: " << converterParaDecimalF(valor, 8) << endl; }
        else if (submenu == 6) { string valor; cout << "Valor hexadecimal: "; cin >> valor; cout << "Decimal: " << converterParaDecimalF(valor, 16) << endl; }
    }
    else if (menu == 7) {
        modoQuiz();
    }
    return 0;
}

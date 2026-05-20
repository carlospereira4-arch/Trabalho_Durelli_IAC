#include <iostream>
#include <string>
#include <cmath>

using namespace std;


string converterBinario(int valor) {
    if (valor == 0) return "0";
    int binario[32];
    int i = 0;
    string resultado = "";
    while (valor > 0) {
        binario[i] = valor % 2;
        valor = valor / 2;
        i++;
    }
    for (int j = i - 1; j >= 0; j--) {
        resultado += (binario[j] + '0');
    }
    return resultado;
}

string converterOctal(int valor) {
    if (valor == 0) return "0";
    int octal[32];
    int i = 0;
    string resultado = "";
    while (valor > 0) {
        octal[i] = valor % 8;
        valor = valor / 8;
        i++;
    }
    for (int j = i - 1; j >= 0; j--) {
        resultado += (octal[j] + '0');
    }
    return resultado;
}

string converterHexadecimal(int valor) {
    if (valor == 0) return "0";
    char hexa[32];
    int i = 0;
    string resultado = "";
    while (valor > 0) {
        int resto = valor % 16;
        if (resto < 10) {
            hexa[i] = resto + '0';
        } else {
            hexa[i] = (resto - 10) + 'A';
        }
        valor = valor / 16;
        i++;
    }
    for (int j = i - 1; j >= 0; j--) {
        resultado += hexa[j];
    }
    return resultado;
}


int biDecimal(string valorInicial) {
    int valor = stoi(valorInicial);
    int tamanho;
    if (valor == 0) tamanho = 1;
    else {
        int valorPositivo = abs(valor);
        int log = log10(valorPositivo);
        tamanho = log + 1;
    }
    int *valorIn = new int[tamanho];
    for (int j = 0; j < tamanho; j++) {
        valorIn[j] = valor % 10;
        valor /= 10;
    }
    int decimal = 0;
    for (int i = 0; i < tamanho; i++) {
        decimal += valorIn[i] * pow(2, i);
    }
    delete[] valorIn;
    return decimal;
}

int octDecimal(string valorInicial) {
    int valor = stoi(valorInicial);
    int tamanho;
    if (valor == 0) tamanho = 1;
    else {
        int valorPositivo = abs(valor);
        int log = log10(valorPositivo);
        tamanho = log + 1;
    }
    int *valorIn = new int[tamanho];
    for (int j = 0; j < tamanho; j++) {
        valorIn[j] = valor % 10;
        valor /= 10;
    }
    int decimal = 0;
    for (int i = 0; i < tamanho; i++) {
        decimal += valorIn[i] * pow(8, i);
    }
    delete[] valorIn;
    return decimal;
}

int hexDecimal(string valorInicial) {
    int tamanho = valorInicial.length();
    int *valorT = new int[tamanho];
    for (int i = 0; i < tamanho; i++) {
        if (valorInicial[i] == 'A' || valorInicial[i] == 'a') valorT[i] = 10;
        else if (valorInicial[i] == 'B' || valorInicial[i] == 'b') valorT[i] = 11;
        else if (valorInicial[i] == 'C' || valorInicial[i] == 'c') valorT[i] = 12;
        else if (valorInicial[i] == 'D' || valorInicial[i] == 'd') valorT[i] = 13;
        else if (valorInicial[i] == 'E' || valorInicial[i] == 'e') valorT[i] = 14;
        else if (valorInicial[i] == 'F' || valorInicial[i] == 'f') valorT[i] = 15;
        else valorT[i] = valorInicial[i] - '0';
    }
    int decimal = 0;
    int expoente = 0;
    for (int i = tamanho - 1; i >= 0; i--) {
        decimal += valorT[i] * pow(16, expoente);
        expoente++;
    }
    delete[] valorT;
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
        string grupo = bin.substr(i, 4);
        for (int j = 0; j < 16; j++) {
            if (grupo == tabelaHexa[j]) resultado += simbolosHexa[j];
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


int main() {
    int menu;
    cout << "### CONVERSOR DE BASES UNIFICADO ###" << endl;
    cout << "1: Decimal -> (Binario, Octal ou Hexadecimal)" << endl;
    cout << "2: (Binario, Octal ou Hexadecimal) -> Decimal" << endl;
    cout << "3: Binario <-> (Octal ou Hexadecimal) Direto" << endl;
    cout << "4: Octal -> Hexadecimal (via Binario)" << endl;
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
    else {
        cout << "Opcao de menu invalida." << endl;
    }

    return 0;
}

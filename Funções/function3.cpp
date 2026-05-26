#include <iostream>
#include <string>

using namespace std;

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
            if (grupo == tabelaOctal[j]) {
                resultado += (j + '0');
            }
        }
    }
    return resultado;
}

string binarioParaHexa(string bin) {
    bin = ajustarBits(bin, 4);
    string resultado = "";
    string tabelaHexa[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
                           "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    char simbolosHexa[] = "0123456789ABCDEF";

    for (int i = 0; i < bin.length(); i += 4) {
        string grupo = bin.substr(i, 4);
        for (int j = 0; j < 16; j++) {
            if (grupo == tabelaHexa[j]) {
                resultado += simbolosHexa[j];
            }
        }
    }
    return resultado;
}

string octalParaBinario(string oct) {
    string resultado = "";
    string tabelaOctal[] = {"000", "001", "010", "011", "100", "101", "110", "111"};

    for (int i = 0; i < oct.length(); i++) {
        int digito = oct[i] - '0';
        if (digito >= 0 && digito <= 7) {
            resultado += tabelaOctal[digito];
        }
    }
    return resultado;
}

string hexaParaBinario(string hex) {
    string resultado = "";
    string tabelaHexa[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
                           "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

    for (int i = 0; i < hex.length(); i++) {
        char c = hex[i];
        int indice = -1;

        if (c >= '0' && c <= '9') indice = c - '0';
        else if (c >= 'A' && c <= 'F') indice = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') indice = c - 'a' + 10;

        if (indice != -1) {
            resultado += tabelaHexa[indice];
        }
    }
    return resultado;
}

int main() {
    int b1, b2;
    string valor;

    cout << "Bases aceitas: 2, 8, 16" << endl;
    cout << "Digite base origem, base destino e o valor: " << endl;

    if (!(cin >> b1 >> b2 >> valor)) return 0;

    string res = "";

    if (b1 == 2 && b2 == 8) res = binarioParaOctal(valor);
    else if (b1 == 2 && b2 == 16) res = binarioParaHexa(valor);
    else if (b1 == 8 && b2 == 2) res = octalParaBinario(valor);
    else if (b1 == 16 && b2 == 2) res = hexaParaBinario(valor);

    if (res != "") cout << "Resultado: " << res << endl;
    else cout << "Conversao invalida para este metodo direto." << endl;

    return 0;
}


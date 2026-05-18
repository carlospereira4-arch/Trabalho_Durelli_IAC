#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int biDecimal(const string& valorInicial) {
    int valor = stoi(valorInicial);
    int tamanho;

    if (valor == 0) {
        tamanho = 1;
    } else {
        int valorPositivo = abs(valor);
        int log = log10(valorPositivo);
        tamanho = log + 1;
    }

    int* valorIn = new int[tamanho];
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

int octDecimal(const string& valorInicial) {
    int valor = stoi(valorInicial);
    int tamanho;

    if (valor == 0) {
        tamanho = 1;
    } else {
        int valorPositivo = abs(valor);
        int log = log10(valorPositivo);
        tamanho = log + 1;
    }

    int* valorIn = new int[tamanho];
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

int hexDecimal(const string& valorInicial) {
    int tamanho = static_cast<int>(valorInicial.length());
    int* valorT = new int[tamanho];

    for (int i = 0; i < tamanho; i++) {
        char c = valorInicial[i];
        if (c == 'A' || c == 'a') {
            valorT[i] = 10;
        } else if (c == 'B' || c == 'b') {
            valorT[i] = 11;
        } else if (c == 'C' || c == 'c') {
            valorT[i] = 12;
        } else if (c == 'D' || c == 'd') {
            valorT[i] = 13;
        } else if (c == 'E' || c == 'e') {
            valorT[i] = 14;
        } else if (c == 'F' || c == 'f') {
            valorT[i] = 15;
        } else {
            valorT[i] = c - '0';
        }
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

const string TABELA_OCTAL_BIN[] = {
    "000", "001", "010", "011", "100", "101", "110", "111"
};
const string TABELA_HEXA = "0123456789ABCDEF";

int binarioParaDecimal(const string& bin) {
    int decimal = 0;
    for (char bit : bin) {
        decimal = (decimal * 2) + (bit - '0');
    }
    return decimal;
}

string octalParaBinario(const string& octal) {
    string binario;
    for (char d : octal) {
        int indice = d - '0';
        if (indice < 0 || indice > 7) {
            return "";
        }
        binario += TABELA_OCTAL_BIN[indice];
    }
    return binario;
}

string binarioParaHexadecimal(string binario) {
    string hexadecimal;
    while (binario.length() % 4 != 0) {
        binario = "0" + binario;
    }
    for (size_t i = 0; i < binario.length(); i += 4) {
        string grupoDeQuatro = binario.substr(i, 4);
        int valorDecimal = binarioParaDecimal(grupoDeQuatro);
        hexadecimal += TABELA_HEXA[valorDecimal];
    }
    return hexadecimal;
}

int main() {
    cout << "Escolha a operacao:\n";
    cout << "1- Converter para decimal (binario/octal/hexadecimal)\n";
    cout << "2- Converter octal para binario e hexadecimal\n";
    cout << "Opcao: ";

    int modo;
    cin >> modo;

    if (modo == 1) {
        string valorInicial;
        cout << "Coloque o Valor Inicial: ";
        cin >> valorInicial;

        cout << "Base Inicial:\n";
        cout << "1- Binario\n";
        cout << "2- Octal\n";
        cout << "3- Hexadecimal\n";

        int option;
        cin >> option;

        int resultado = 0;
        if (option == 1) {
            resultado = biDecimal(valorInicial);
        } else if (option == 2) {
            resultado = octDecimal(valorInicial);
        } else if (option == 3) {
            resultado = hexDecimal(valorInicial);
        } else {
            cout << "Opcao invalida." << endl;
            return 1;
        }

        cout << "Resultado em decimal: " << resultado << endl;
    } else if (modo == 2) {
        string octal;
        cout << "Digite um numero na base 8 (Octal): ";
        cin >> octal;

        string binario = octalParaBinario(octal);
        if (binario.empty()) {
            cout << "Octal invalido." << endl;
            return 1;
        }

        string hexadecimal = binarioParaHexadecimal(binario);

        cout << "-> Em binario: " << binario << endl;
        cout << "-> Em hexadecimal: " << hexadecimal << endl;
    } else {
        cout << "Modo invalido." << endl;
        return 1;
    }

    return 0;
}

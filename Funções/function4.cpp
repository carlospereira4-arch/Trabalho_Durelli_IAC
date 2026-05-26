#include <iostream>
#include <string>

using namespace std;

// Array estático tradicional de strings para o Octal
const string TABELA_OCTAL_BIN[] = {
    "000", "001", "010", "011", "100", "101", "110", "111"
};

// String constante para consulta do Hexadecimal
const string TABELA_HEXA = "0123456789ABCDEF";

// Função para converter 4 bits binários para um valor inteiro (0 a 15)
int binarioParaDecimal(string bin) {
    int decimal = 0;
    for (char bit : bin) {
        // Multiplica o acumulado por 2 e soma o novo bit (0 ou 1)
        decimal = (decimal * 2) + (bit - '0');
    }
    return decimal;
}

int main() {
    string octal, binario = "", hexadecimal = "";

    cout << "Digite um numero na base 8 (Octal): ";
    cin >> octal;

    // 1. Octal para Binário usando Array Tradicional
    for (char d : octal) {
        int indice = d - '0'; // Converte caractere '0'-'7' para inteiro 0-7
        binario += TABELA_OCTAL_BIN[indice];
    }

    cout << "-> Em binario (ponte): " << binario << endl;

    // 2. Ajuste de tamanho para múltiplos de 4
    while (binario.length() % 4 != 0) {
        binario = "0" + binario;
    }

    // 3. Binário para Hexadecimal
    for (size_t i = 0; i < binario.length(); i += 4) {
        string grupoDeQuatro = binario.substr(i, 4);
        
        // Convertemos o grupo de 4 bits para um número (0 a 15)
        int valorDecimal = binarioParaDecimal(grupoDeQuatro);
        
        // Pega o caractere correspondente na string de consulta
        hexadecimal += TABELA_HEXA[valorDecimal];
    }

    cout << "-> Em hexadecimal (Base 16): " << hexadecimal << endl;

    return 0;
}
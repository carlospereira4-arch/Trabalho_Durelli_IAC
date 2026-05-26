#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

void reverterString(string &str) {
    int i = 0, j = str.length() - 1;
    while (i < j) swap(str[i++], str[j--]);
}

int stringParaInt(string str) {
    int res = 0;
    for (char c : str) res = res * 10 + (c - '0');
    return res;
}

string converterBinario(int val) {
    if (val == 0) return "0";
    string res = "";
    while (val > 0) { res += (val % 2) + '0'; val /= 2; }
    reverterString(res);
    return res;
}

string converterOctal(int val) {
    if (val == 0) return "0";
    string res = "";
    while (val > 0) { res += (val % 8) + '0'; val /= 8; }
    reverterString(res);
    return res;
}

string converterHexadecimal(int val) {
    if (val == 0) return "0";
    string res = "";
    while (val > 0) {
        int r = val % 16;
        res += (r < 10) ? (r + '0') : (r - 10 + 'A');
        val /= 16;
    }
    reverterString(res);
    return res;
}

int biDecimal(string s) {
    int res = 0;
    for (int i = 0; i < (int)s.length(); i++)
        res += (s[s.length()-1-i] - '0') * pow(2, i);
    return res;
}

int octDecimal(string s) {
    int res = 0;
    for (int i = 0; i < (int)s.length(); i++)
        res += (s[s.length()-1-i] - '0') * pow(8, i);
    return res;
}

int hexDecimal(string s) {
    int res = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        char c = s[s.length()-1-i];
        int d = (c >= 'A' && c <= 'F') ? (c - 'A' + 10) : (c - '0');
        res += d * pow(16, i);
    }
    return res;
}

int converterParaDecimal(string val, int base) {
    if (base == 2) return biDecimal(val);
    if (base == 8) return octDecimal(val);
    if (base == 16) return hexDecimal(val);
    return stringParaInt(val);
}

string converterDeDecimal(int val, int base) {
    if (base == 2) return converterBinario(val);
    if (base == 8) return converterOctal(val);
    if (base == 16) return converterHexadecimal(val);
    return to_string(val);
}
bool validarDigitos(string valor, int base) {
    for (char c : valor) {
        if (c == ',' || c == '.') continue;
        if (base == 2 && (c != '0' && c != '1')) return false;
        if (base == 8 && (c < '0' || c > '7')) return false;
        if (base == 10 && (c < '0' || c > '9')) return false;
        if (base == 16) {
            if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) 
                return false;
        }
    }
    return true;
}
int main() {
    ifstream entrada("entrada.csv");
    ofstream saida("saida.csv");

    string linha;
    int contador = 0, erros = 0;
    
    while (getline(entrada, linha)) {
        contador++;
        if (linha.empty()) continue;

        int pos1 = linha.find(';');
        int pos2 = linha.find(';', pos1 + 1);

        if (pos1 == (int)string::npos || pos2 == (int)string::npos) {
            cout << "Linha " << contador << ": Formato invalido" << endl;
            erros++;
            continue;
        }

        string valor = linha.substr(0, pos1);
        int baseOrig = stringParaInt(linha.substr(pos1 + 1, pos2 - pos1 - 1));
        int baseDest = stringParaInt(linha.substr(pos2 + 1));

        if (!validarDigitos(valor, baseOrig)) {
            cout << "Linha " << contador << ": Valor invalido para a base " << baseOrig << endl;
            erros++;
            continue;
        }

        int decimal = converterParaDecimal(valor, baseOrig);
        string resultado = converterDeDecimal(decimal, baseDest);

        saida << valor << ";" << baseOrig << ";" << resultado << ";" << baseDest << "\n";
    }

    entrada.close();
    saida.close();
    cout << "Processamento concluido! Total: " << (contador-1) << " | Erros: " << erros << endl;
    return 0;
}

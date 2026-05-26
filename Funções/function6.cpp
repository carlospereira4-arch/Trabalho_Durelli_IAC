#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Função para reverter uma string sem usar biblioteca
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

// Função para substituir caracteres sem usar biblioteca
void substituirChar(string &str, char antigo, char novo) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == antigo) {
            str[i] = novo;
        }
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


string converterBinario(double valor) {
    long long parteInteira = (long long)valor;
    double parteFrac = valor - parteInteira;
    
    if (valor == 0) return "0";
    string resultado = "";
    
    if (parteInteira == 0) resultado = "0";
    else {
        while (parteInteira > 0) {
            resultado += (parteInteira % 2 + '0');
            parteInteira /= 2;
        }
        reverterString(resultado);
    }
    return resultado + converterFracionario(parteFrac, 2);
}

string converterOctal(double valor) {
    long long parteInteira = (long long)valor;
    double parteFrac = valor - parteInteira;
    
    if (valor == 0) return "0";
    string resultado = "";
    
    if (parteInteira == 0) resultado = "0";
    else {
        while (parteInteira > 0) {
            resultado += (parteInteira % 8 + '0');
            parteInteira /= 8;
        }
        reverterString(resultado);
    }
    return resultado + converterFracionario(parteFrac, 8);
}

string converterHexadecimal(double valor) {
    long long parteInteira = (long long)valor;
    double parteFrac = valor - parteInteira;
    
    if (valor == 0) return "0";
    string resultado = "";
    
    if (parteInteira == 0) resultado = "0";
    else {
        while (parteInteira > 0) {
            int resto = parteInteira % 16;
            if (resto < 10) resultado += (resto + '0');
            else resultado += (resto - 10 + 'A');
            parteInteira /= 16;
        }
        reverterString(resultado);
    }
    return resultado + converterFracionario(parteFrac, 16);
}


double converterQualquerParaDecimal(string valor, int base) {
    substituirChar(valor, ',', '.');
    
    size_t pontoPos = valor.find('.');
    string inteira = (pontoPos == string::npos) ? valor : valor.substr(0, pontoPos);
    string fracionaria = (pontoPos == string::npos) ? "" : valor.substr(pontoPos + 1);

    double decimal = 0;
    
    for (int i = 0; i < inteira.length(); i++) {
        int digito;
        char c = toupper(inteira[i]);
        if (c >= 'A') digito = c - 'A' + 10;
        else digito = c - '0';
        decimal += digito * pow(base, inteira.length() - 1 - i);
    }

    for (int i = 0; i < fracionaria.length(); i++) {
        int digito;
        char c = toupper(fracionaria[i]);
        if (c >= 'A') digito = c - 'A' + 10;
        else digito = c - '0';
        decimal += digito * pow(base, -(i + 1));
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
    substituirChar(bin, ',', '.');
    size_t pontoPos = bin.find('.');
    string inteira = (pontoPos == string::npos) ? bin : bin.substr(0, pontoPos);
    string frac = (pontoPos == string::npos) ? "" : bin.substr(pontoPos + 1);

    inteira = ajustarBits(inteira, 3);
    string res = "";
    for (int i = 0; i < inteira.length(); i += 3) {
        int val = (inteira[i]-'0')*4 + (inteira[i+1]-'0')*2 + (inteira[i+2]-'0')*1;
        res += (val + '0');
    }

    if (frac != "") {
        res += ".";
        while (frac.length() % 3 != 0) frac += "0";
        for (int i = 0; i < frac.length(); i += 3) {
            int val = (frac[i]-'0')*4 + (frac[i+1]-'0')*2 + (frac[i+2]-'0')*1;
            res += (val + '0');
        }
    }
    return res;
}

string binarioParaHexa(string bin) {
    substituirChar(bin, ',', '.');
    size_t pontoPos = bin.find('.');
    string inteira = (pontoPos == string::npos) ? bin : bin.substr(0, pontoPos);
    string frac = (pontoPos == string::npos) ? "" : bin.substr(pontoPos + 1);
    char simbolos[] = "0123456789ABCDEF";

    inteira = ajustarBits(inteira, 4);
    string res = "";
    for (int i = 0; i < inteira.length(); i += 4) {
        int val = (inteira[i]-'0')*8 + (inteira[i+1]-'0')*4 + (inteira[i+2]-'0')*2 + (inteira[i+3]-'0')*1;
        res += simbolos[val];
    }

    if (frac != "") {
        res += ".";
        while (frac.length() % 4 != 0) frac += "0";
        for (int i = 0; i < frac.length(); i += 4) {
            int val = (frac[i]-'0')*8 + (frac[i+1]-'0')*4 + (frac[i+2]-'0')*2 + (frac[i+3]-'0')*1;
            res += simbolos[val];
        }
    }
    return res;
}

string octalParaBinario(string oct) {
    substituirChar(oct, ',', '.');
    string res = "";
    string tab[] = {"000", "001", "010", "011", "100", "101", "110", "111"};
    for (char c : oct) {
        if (c == '.') res += ".";
        else res += tab[c - '0'];
    }
    return res;
}

bool validar(string valor, int base) {
    int pontos = 0;
    for (char c : valor) {
        if (c == '.' || c == ',') {
            pontos++;
            if (pontos > 1) return false;
            continue;
        }
        if (base == 2 && (c != '0' && c != '1')) return false;
        if (base == 8 && (c < '0' || c > '7')) return false;
        if (base == 16) {
            char up = toupper(c);
            if (!((up >= '0' && up <= '9') || (up >= 'A' && up <= 'F'))) return false;
        }
    }
    return true;
}

int main() {
    int menu;
    cout << "### CONVERSOR DE BASES UNIFICADO (SUPORTE FRACIONARIO) ###" << endl;
    cout << "1: Decimal -> (Binario, Octal ou Hexadecimal)" << endl;
    cout << "2: (Binario, Octal ou Hexadecimal) -> Decimal" << endl;
    cout << "3: Binario <-> (Octal ou Hexadecimal) Direto" << endl;
    cout << "4: Octal -> Hexadecimal (via Binario)" << endl;
    cout << "Escolha a opcao: ";
    cin >> menu;

    if (menu == 1) {
        string entrada;
        int base;
        cout << "Valor decimal: "; cin >> entrada;
        substituirChar(entrada, ',', '.');
        double valor = stod(entrada);
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
        int b = (tipo == 1) ? 2 : (tipo == 2) ? 8 : 16;
        if (validar(valor, b)) cout << "Decimal: " << converterQualquerParaDecimal(valor, b) << endl;
        else cout << "ERRO: Digitos invalidos." << endl;
    }
    else if (menu == 3) {
        int b1, b2; string valor;
        cout << "Base inicial, Base final e Valor: "; cin >> b1 >> b2 >> valor;
        if (validar(valor, b1)) {
            if (b1 == 2 && b2 == 8) cout << "Resultado: " << binarioParaOctal(valor) << endl;
            else if (b1 == 2 && b2 == 16) cout << "Resultado: " << binarioParaHexa(valor) << endl;
            else if (b1 == 8 && b2 == 2) cout << "Resultado: " << octalParaBinario(valor) << endl;
            else cout << "ERRO: Conversao nao programada." << endl;
        } else cout << "ERRO: Valor invalido." << endl;
    }
    else if (menu == 4) {
        string octal, bin;
        cout << "Valor Octal: "; cin >> octal;
        if (validar(octal, 8)) {
            bin = octalParaBinario(octal);
            cout << "Passagem Binaria: " << bin << endl;
            cout << "Resultado Hexadecimal: " << binarioParaHexa(bin) << endl;
        } else cout << "ERRO: Digito invalido." << endl;
    }
    return 0;
}
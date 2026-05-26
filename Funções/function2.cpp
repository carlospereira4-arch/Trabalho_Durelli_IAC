#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int biDecimal(string valorInicial){ //Função que transforma binario em Decimal
    int valor = stoi(valorInicial);
    int tamanho;

    if (valor == 0){
        tamanho = 1;
    }
    else { 
        int valorPositivo = abs(valor); 
        int log = log10(valorPositivo);
        tamanho = log + 1;
    }
    int *valorIn = new int[tamanho];
    for (int j = 0; j < tamanho; j++){  // Laço de repetição para inverter um numero inteiro
        valorIn[j] = valor % 10;
        valor /= 10;
    }

    int decimal = 0;
    for (int i = 0; i < tamanho; i++){
        decimal += valorIn[i] * pow(2, i);
    }

    delete[] valorIn;
    return decimal;
}

int octDecimal(string valorInicial){ // Função que transforma octal em Decimal
    int valor = stoi(valorInicial);
    int tamanho;
    if (valor == 0){
        tamanho = 1;
    }
    else {
        int valorPositivo = abs(valor);
        int log = log10(valorPositivo);
        tamanho = log + 1;
    }
    int *valorIn = new int[tamanho];
    for (int j = 0; j < tamanho; j++){
        valorIn[j] = valor % 10;
        valor /= 10;
    }

    int decimal = 0;
    for (int i = 0; i < tamanho; i++){
        decimal += valorIn[i] * pow(8, i);
    }

    delete[] valorIn;
    return decimal;
}

int hexDecimal(string valorInicial) { // Função que transforma Hexadecimal em Decimal
    int tamanho = valorInicial.length();
    int *valorT = new int[tamanho];

    
    for (int i = 0; i < tamanho; i++) {
        if (valorInicial[i] == 'A' || valorInicial[i] == 'a') {
            valorT[i] = 10;
        }
        else if (valorInicial[i] == 'B' || valorInicial[i] == 'b') {
            valorT[i] = 11;
        }
        else if (valorInicial[i] == 'C' || valorInicial[i] == 'c') {
            valorT[i] = 12;
        }
        else if (valorInicial[i] == 'D' || valorInicial[i] == 'd') {
            valorT[i] = 13;
        }
        else if (valorInicial[i] == 'E' || valorInicial[i] == 'e') {
            valorT[i] = 14;
        }
        else if (valorInicial[i] == 'F' || valorInicial[i] == 'f') {
            valorT[i] = 15;
        }
        else {

            valorT[i] = valorInicial[i] - '0';
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

int main(){
    string valorInicial;
    int resultado;
    cout << "Coloque o Valor Inicial" << endl;
    cin >> valorInicial;
    cout << "Base Inical" << endl; 
    cout << "1- Binario;" << endl;
    cout << "2- Octal;" << endl;
    cout << "3- Hexadecimal;" << endl;
    int option;
    cin >> option;

    if (option == 1){
        resultado = biDecimal(valorInicial);
        cout << resultado << endl;
    }
    else if (option == 2){
        resultado = octDecimal(valorInicial);
        cout << resultado << endl;
    }
    else if (option == 3){
        resultado = hexDecimal(valorInicial);
        cout << resultado << endl;
    }
    
    return 0;
}
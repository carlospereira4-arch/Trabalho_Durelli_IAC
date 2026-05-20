#include <iostream>
#include <string>

using namespace std;

string converterBinario(int valor){
   if(valor == 0) return "0";
   int binario[32];
   int i = 0;
   string resultado = "";

        while(valor > 0){
    binario[i] = valor % 2;
    valor = valor / 2;
    i++;
        }
  for(int j = i - 1; j >= 0; j--){
    resultado += (binario[j] + '0');
  }
  return resultado;
}

string converterOctal(int valor){
   if(valor == 0) return "0";
   int octal[32];
   int i = 0;
   string resultado = "";

        while(valor > 0){
    octal[i] = valor % 8;
    valor = valor / 8;
    i++;
        }
  for(int j = i - 1; j >= 0; j--){
    resultado += (octal[j] + '0');
  }
  return resultado;
}

   string converterHexadecimal(int valor){
   if(valor == 0) return "0";
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
            if (j > 0) resultado += " ";
        }
        return resultado;
    }





int main() {
    int base1, base2, valor1;

    cout << "Digite a base inicial, a base desejada (2, 8 ou 16) e o valor: " << endl;
    cout << "2: Binario | 8: Octal | 16: Hexadecimal" << endl;

    if (!(cin >> base1 >> base2 >> valor1)) return 0;

    string resposta = "";

    if (base2 == 2) {
        resposta = converterBinario(valor1);
    }
    else if (base2 == 8) {
        resposta = converterOctal(valor1);
    }
    else if (base2 == 16) {
        resposta = converterHexadecimal(valor1);
    }

    if (resposta != "") {
        cout << "Resultado: " << resposta << endl;
    }

    return 0;
}


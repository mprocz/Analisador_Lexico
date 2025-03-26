#include <iostream> 
#include <fstream>

using namespace std;

enum TokenClass {
    INTEIRO, REAL, OPERADOR, ABRE_PARENTESES, FECHA_PARENTESES, INVALIDO
};

void print_token(string * lexema, TokenClass * token) {
    string tokenNames[] = {"INTEIRO", "REAL", "OPERADOR", "ABRE_PARENTESES", "FECHA_PARENTESES", "INVALIDO"};
    cout << (*lexema) << " - " << tokenNames[(*token)] << '\n';
    (*lexema).clear();
    (*token) = INVALIDO;
}

int main() {
    ifstream input("../input.txt");
    if(!input){cout<<"Erro ao abrir arquivo\n"; return -1;}
    
    string lexema = "";
    TokenClass token = INVALIDO ;
    char atom;
    while (input.get(atom)) {
        if (atom != ' ') {
            if (atom == '+' || atom == '-' || atom == '*' || atom == '/' || atom == '-') {
                if (!lexema.empty()) {
                    print_token(&lexema, &token);
                }
                lexema += atom;
                token = OPERADOR;
                print_token(&lexema, &token);
            }else if (atom == '(') {
                if (!lexema.empty()) {
                    print_token(&lexema, &token);
                }
                lexema += atom;
                token = ABRE_PARENTESES;
                print_token(&lexema, &token);
            }else if (atom == ')') {
                if (!lexema.empty()) {
                    print_token(&lexema, &token);
                }
                lexema += atom;
                token = FECHA_PARENTESES;
                print_token(&lexema, &token);
            }else if (atom == '.') {
                if (!lexema.empty() && token == INVALIDO) {
                    print_token(&lexema, &token);
                    lexema += atom;
                    token = INVALIDO;
                    print_token(&lexema, &token);
                } else if (token == INTEIRO) {
                    lexema += atom;
                    token = REAL;
                } else if (token == REAL) {
                    print_token(&lexema, &token);
                    lexema += atom;
                    token = INVALIDO;
                    print_token(&lexema, &token);
                }else {
                    lexema += atom;
                    token = INVALIDO;
                    print_token(&lexema, &token);
                }
            }else if (isdigit(atom)) {
                if (!lexema.empty() && token == INVALIDO) {
                    print_token(&lexema, &token);
                    lexema = atom;
                    token = INTEIRO;
                }else if (token == INVALIDO) {
                    lexema = atom;
                    token = INTEIRO;
                }else {
                    lexema += atom;
                }
            } else {
                if (!lexema.empty() && token != INVALIDO) {
                    print_token(&lexema, &token);
                    lexema = atom;
                } else {
                    lexema += atom;
                }
            }
        }
    }
    if (!lexema.empty()) {
        print_token(&lexema, &token);
    }
    return 0;
}

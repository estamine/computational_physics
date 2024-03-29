/*

Programa que calcula o declive e a ordenada na origem de uma recta ajustada a
dados introduzidos pelo utilizador atrav�s de um ficheiro de texto. Os dados sao
coordenadas de pontos a duas dimensoes.

Requere-se que o ficheiro de dados tenha:
                      
           - Duas (2) colunas separadas por tabulacao (TAB)
           - A primeira coluna correspondente 'as coordenadas x e a segunda coluna
             correspondente 'as y.
                      
Para o ajuste da recta utiliza-se o metodo dos minimos quadrados.

Rui Caldeira, aluno numero 32046, Engenharia Fisica

rui@estamine.net

Maio de 2007, FCUL

*/

#include <iostream>
#include <math.h>    //necessaria para a funcao potencia pow()
#include <string.h>
#include <fstream>

using namespace std;

int main()

{

// iniciar variaveis

int linhas=0;                 // numero de linhas do ficheiro
double valoresX, valoresY;    // valores das colunas X e Y

double somaX = 0.0;           // soma dos valores X
double somaY = 0.0;           // soma dos valores Y
double produtoXY= 0.0;       // soma dos produtos dos valores de X e Y

double mediaX = 0.0;          // media dos valores de X
double mediaY = 0.0;          // media dos valores de Y

double somatorio = 0.0;
double declive = 0.0;         	// declive da recta
double ordenada = 0.0;        // ordenada na origem

string nome="valores.txt";    	// string utilizada para obter nome do ficheiro
string strdump;               	// string utilizada para dump do getline
int iter;                     		// iterador
    
cout << "\nAproximacao de uma recta a valores de uma funcao linear pelo metodo dos minimos quadrados.\n\n";

cout << "Introduza nome do ficheiro ou 0 (zero) para manter nome default (valores.txt):\n";
cin >> nome;
if (nome == "0") { nome ="valores.txt"; };

ifstream ficheiro(nome.c_str());

if (!ficheiro.is_open()) { cout << "\n\nFicheiro nao encontrado!\n\n"; main(); };

// contar linhas do ficheiro introduzido e mostrar ficheiro
cout << "\n\nValores do ficheiro " << nome << "\n\nX       Y\n" << "---------\n\n";
while (! ficheiro.eof())
{
     getline(ficheiro,strdump);
     
     cout << strdump << endl;

     linhas++;
}

double coordX[linhas], coordY[linhas];        // arrays dos varios valores de X e Y

ifstream ficheiroinput;                       // define classe de leitura

ficheiroinput.open (nome.c_str(),ios::out);  // abre o ficheiro

for (iter = 0; iter<linhas; iter++)
    {
	ficheiroinput >> valoresX >> valoresY;    // associa a primeira coluna de cada linha ao double valoresX e a segunda coluna ao double valoresY

	coordX[iter] = valoresX;                  // coloca os valores da primeira coluna no array coordX
	coordY[iter] = valoresY;                  // coloca os valores da seguinda coluna no array coordY
	
    }

// calcula medias de coordX e coordY e o somatorio do produto de X por Y
    for(iter = 0; iter < linhas; iter++)
    {
	somaX+= coordX[iter];

	somaY+= coordY[iter];

	produtoXY+= (coordX[iter]*coordY[iter]);
    }

  	mediaX = somaX / linhas;

	mediaY = somaY / linhas;


// calcular somatorio de (coordX - mediaX)^2
	for(iter = 0; iter < linhas; iter++)

        {
          somatorio+= pow(coordX[iter] - mediaX,2);
        }


// calcular declive e ordenada

	declive = (produtoXY - (linhas * mediaX * mediaY)) / somatorio;


    ordenada = mediaY - (declive * mediaX);

// printout dos resultados
cout << "\n\nValores calculados:\n\n" << "Ordenada na origem: " << ordenada << "\nDeclive: " << declive << "\n\nY = " << declive << "*X + " << ordenada;
	
// confirmacao de repeticao de programa
cout << "\n\nSair do programa (s/n)? ";
cin >> strdump;

if (strdump != "s") { main(); };

    return 0;

}
                                                                                                                                                                                                                                                                   
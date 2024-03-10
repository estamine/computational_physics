/*

Programa que interpola um valor dado pelo utilizador a outros provenientes de um ficheiro de texto com duas colunas separadas por tabulacao.
Estas duas colunas sao os varios valores X e Y.

Requere-se que o ficheiro de dados tenha:
                      
           - Duas (2) colunas separadas por tabulacao (TAB)
           - A primeira coluna correspondente 'as coordenadas x e a segunda coluna
             correspondente 'as y.
	     
Requere-se que o utilizador introduza o valor X a interpolar.
	     
O programa utiliza o metodo de lagrange.

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
int linhas=0;             		// numero de linhas do ficheiro
double valoresX, valoresY;    // valores das colunas X e Y
string nome="valores.txt";    	// string utilizada para obter nome do ficheiro
string strdump;               	// string utilizada para dump do getline
int iter;                     		// iterador
int iter2;				// iterador 2
    
cout << "\nAproximacao de uma recta a valores de uma funcao linear pelo metodo dos minimos quadrados.\n\n";

cout << "Introduza nome do ficheiro ou 0 (zero) para manter ''valores.txt'':\n";
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
 
double X=0.0;	// valor a interpolar
double polinomioX=0.0 ,numerador=1.0, denominador=1.0;
    
cout << "Insira o valor que pretende interpolar: ";	// pede ao utilizador que insira o valor que deseja interpolar  
cin >> X;


// metodo de lagrange
for(iter=0; iter<linhas-1; iter++)
 { 
    for(iter2=0; iter2<s-1; iter2++)
    { 
      if (iter!=iter2)
      {
        numerador = numerador * (X - coordX[iter2]);
        denominador = denominador * (coordX[iter] - coordX[iter2]);
      }
      
    }
   
   numerador=numerador*coordY[iter];
   polinomioX+= numerador/denominador;
   numerador=denominador=1;
  
 }
	
cout << "\nResultado para " << s-1 << " polinomios "<< "e': " << polinomioX << "\n\n";

// confirmacao de repeticao de programa
cout << "\n\nSair do programa (s/n)? ";
cin >> strdump;

if (strdump != "s") { main(); };

    return 0; 

}

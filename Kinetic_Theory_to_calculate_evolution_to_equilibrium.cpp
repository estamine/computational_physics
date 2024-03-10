/*

Programa usa RNGs para estudar a Evolução para o equilíbrio usando a
teoria cinética dos gases

Requere-se que o utilizador introduza:
           
           - Número de partículas na caixa da esquerda (M)
           - Número de iterações (tfinal)
           - Número de partículas na caixa da esquerda (opcional) (ni)
           
Rui Caldeira, aluno numero 32046, Engenharia Física
 
rui@estamine.net

03 de Março de 2009, FCUL

*/

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include "libnum/libnum.h"
#include "libnum/displot.h"
using namespace std;

// iniciar variaveis globais
int t=0;					// Variável de iteração (tempo)
int tfinal;					// Número máximo de iterações
double M;					// Número total de partículas no sistema (double por causa da divisão)
double r;					// Variável usada para receber o valor da randomização
double n;					// Número de partículas na caixa da esquerda (double por causa da divisão)
string filename="";

int main(){
	
cout << "\nEvolução para o Equilíbrio\n\n";
cout << "Introduza 0 (zero) para manter valor (default) ou responder nao (n)\n\n"; // practico e evita introducao de valores nulos ou negativos

cout << "Número de partículas (100)? "; cin >> M;
if (M <= 0) { M = 100; };

cout << "\n";

cout << "Iterações/tempo (1000)? "; cin >> tfinal;
if (tfinal <= 0) { tfinal = 1000; };

cout << "\n";

cout << "Número de partículas na caixa da esquerda (" << M << ")? "; cin >> n;
if (n <= 0) { n = M; };

cout << "\n";

LIBNUM::RngInit();					// inicializa o randomizer

  ofstream myfile;						

  myfile.open ("output.txt");			// abre ficheiro com nome "output.txt"

PlotInit(0,tfinal,0,M,"xwin");			// inicializar a plot

for (t=0 ; t<= tfinal ; t++){			// enquanto durar o tempo
	
r = LIBNUM::RngDouble();			// gera o r

//r = 0.5;

if (r <= n/M) {						// se r inferior vai uma para a direita
	
	if (n > 0) { n--;};				// mas claro que só vai se ainda houver partículas na esquerda
	
} else {							// se não, vai para a esquerda
	
	if (n < M) { n++;};			// mas só se não estiverem lá todas já

}
/*
cout << "\n" << "Tempo: " << t << "\n";
cout << "\n" << "Número de partículas à esquerda: " << n << "\n";  // para irmos vendo
cout << "Número de partículas à direita: " << M-n << "\n";
*/

if (t < 50000) {
  myfile << t << "," << n << "," << M-n << "\n";	// mete tempo, número à esquerda, número à direita
}

DrawPoint(t,n,"Circle","Red","S");	// desenhar o ponto n

DrawPoint(t,M-n,"Square","Blue","S");	// desenhar o ponto M-n


} 									// acaba o for

PlotEnd();

 myfile.close();
return 0;			// acabou

}

/*

Programa usa RNGs para estudar a Refraccao, Lei de Snell e principio de Fermat

Requere-se que o utilizador introduza:
	
	- Numero de separacoes/materiais (M)
	- Ordenadas dos pontos inicial e final (p[0] e p[M+1])
	- Variacao de coeficiente de refraccao (fi)
	- Resolucao (resol)
	
Rui Caldeira, aluno numero 32046, Engenharia Fisica

rui@estamine.net

10 de Marco de 2009, FCUL

*/

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include "libnum/libnum.h"
#include "libnum/displot.h"
using namespace std;

// iniciar variaveis globais

// calculo das ordenadas partindo dos pf e p0 e sabendo que as "alturas" sao iguais

void calcord(double p[], int M) {

	int i;

	for ( i=1 ; i<M ; i++ ) {

		p[i] = p[i-1] + (p[M] - p[0]) / M;
		
		
		cout << "\n p de " << i << ": " << p[i] << "\n"; 

	} 

}

// calculo dos indices de refraccao ns todos para construir o arrary n[]

void calcn(double n[] , double fi, int M) {

	int i;

	n[0] = 1;

	for ( i=1 ; i<M+1 ; i++ ) {

		n[i]=n[i-1]*(fi/100 +1);

		cout << "\n n de " << i << ": " << n[i] << " fi: " << (fi/100 +1) << "\n"; 
		
	} 

}


// calculo do tempo que a luz demora a percorrer o percurso

double tactual (double n[], double p[], int M) {

	int i;

	double tt=0.0;		// tempo total

	for ( i=0 ; i<M ; i++ ) {

		tt = tt + n[i] * sqrt( (p[i+1]-p[i])*(p[i+1]-p[i]) + 1 );

	}

	return tt;
	
}

// testa se os valores obtidos coincidem com a lei de snell: n1 sin(teta1) = n2 sin(teta2)

double snell (double n[], double p[], int M) {
	
	int i;
	
	for ( i=0 ; i<M ; i++ ) {

	cout << "\nsnell de " << i << ": " << n[i]* ((p[i+1]-p[i])  / sqrt( (p[i+1]-p[i])*(p[i+1]-p[i]) + 1 )) << "\n";
	
	}
}

// mother-function - chamada assim: aula2.exe num_de_meios(M) ordenada_p0(p[0]) ordenada_pf(p[M+1]) fi(saltofi) resolucao(resol)

int main(int argc, char **argv){

// Variaveis

	int M=atoi(argv[1]);	        // numero de separacoes/materiais

	double p[M+1];		        // array com abcissas (posicao no array) e ordenadas (valor no array)

	p[0]=atoi(argv[2]);	        // ordenada do p0

	p[M]=atoi(argv[3]);	        // ordenada do pf

	double saltofi=atoi(argv[4]);	// fi introduzido em percentagem de crescimento

	double n[M];		        // array com indices de refraccao

	int resol=atoi(argv[5]);	// resolucao requerida 

	double delta;                   // teste da resolucao requerida
	
	double deltamin;		// guarda valor do delta minimo pretendido

	double tvelho;			// guarda o t anterior
	
	double tinicial;		// guarda o t da recta
	
	int r;				// variavel aleatoria
	
	int maisoumenos=0;		// variavel para somar ou subtrair o delta
	
	double base=-1.0;		// base para o mais ou menos (tinha de ser double)

	double pantigo;			// p antes de alterar
	
	int rejeicoes=0;		// numero de rejeicoes do tempo actual

// Inicializacoes
	
	LIBNUM::RngInit();			// inicializa o randomizer
	
	calcord(p,M);        			// calcula as coordenadas da recta inicial

	calcn(n,saltofi,M);    			// calcula o array de indices de refraccao

	tvelho=tactual(n,p,M);
	
	tinicial=tvelho;
		
	delta=(p[M] - p[0]) / (2*M);     	// calcula o delta zero

	deltamin= delta / (resol*M);
	
	//cout << "\nt de agora: " << tvelho << "\ndelta: " << delta << "\ndeltamin: " << deltamin << "\n";
	

	while (delta > deltamin) {
		
		//cout << "\ntempo: " << tactual(n,p,M) << " tempo inicial: " << tinicial << " delta: " << delta << "\n";
		
		r = LIBNUM::RngInt(M-1) + 1;		// gera inteiro aleatorio de 1 a M-1	
		maisoumenos = LIBNUM::RngInt(2);	// gera inteiro aleatorio 0 ou 1	

		pantigo = p[r];					// guarda valor
		p[r] = p[r] + pow(base, maisoumenos)*delta;	// soma ou subtrai delta ao valor de p escolhido
		
		double tteste;
		
		tteste = tactual(n,p,M);			// calcula tempo com novos parametros
		
		// se tempo melhor guarda novo tempo. reinicia as rejeicoes e recomeca o while
		if (tteste < tvelho) { tvelho=tteste; rejeicoes=0; continue; } 
		
		else { 	// se tempo pior, repoe p[r] antigo, incrementa rejeicoes...
			
			p[r]=pantigo;
			
			rejeicoes++;
			
			if ( rejeicoes < 10*M ) { continue; }	// ...se ainda nao temos muitas rejeicoes, recomeca o while
		
			else { rejeicoes=0; delta = delta / 2; } // se ja temos muitas rejeicoes seguidas, reinicia as rejeicoes e diminui o delta
		
		}
			
	}
	
	cout << "\ntempo: " << tactual(n,p,M) << " tempo inicial: " << tinicial << " delta: " << delta << "\n";

	snell(n,p,M);
	
	int i=0;					// variavel de iteracao

	double xx[M];
	
	for ( i = 0; i<M+1 ; i++) { 
		
		xx[i]=i;
		
		//cout << "\n" << xx[i] << "\n";
	
	}
	
	PlotInit(0,M,p[0],p[M],"xwin");
	
	DrawLine(M+1,xx,p, "Solid" , "Blue" , "S");	
		
	PlotEnd();

	return 0;

}

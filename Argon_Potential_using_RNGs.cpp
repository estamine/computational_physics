/*

Programa usa RNGs para estudar Potencial do Argon

Requere-se que o utilizador introduza:
	
	- Numero de atomos
	- Futuramente: coordenadas
	
	Raio de energia minima para 2 atomos de Argon: 3.82 Angström
	
Rui Caldeira, aluno numero 32046, Engenharia Fisica

rui@estamine.net

28 de Abril de 2009, FCUL

*/

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#include <vector>
#include "libnum/libnum.h"
#include "libnum/displot.h"
using namespace std;

// Classes

	class cvector
{
	public:
		double x;
		double y;
		double z;
			
		double norma() { return sqrt(x*x+y*y+z*z); }
};
	
	class catomo
{
	public:
		cvector coord;
};

	class cgas
{
	public:
		catomo *atomo;
		int size;		// tamanho do gas, numero de atomos
		int i;			// iteracao
			
		cgas(int n)          // constructor 
		{ 
			size = n; 
			atomo = new catomo[size]; 
			
		} 
 
		~cgas()            // destructor 
		{ 
			delete[] atomo; 
		} 
		
		// cria coordenadas aleatoriamente
		
		void criacoords() {
			
			for ( i=0 ; i<size ; i++) {
				
				
				atomo[i].coord.x = LIBNUM::RngDouble()*10-5;
				atomo[i].coord.y = LIBNUM::RngDouble()*10-5;
				atomo[i].coord.z = LIBNUM::RngDouble()*10-5;
				
			}
				
		}
		
		// mostra as coordenadas aleatorias
		
		void mostracoords() {
			
			cout << endl << "*** Coordenadas iniciais ***" << endl;

			for ( i=0 ; i<size ; i++) {
				
				cout << endl << "Atomo numero: " << i+1 << endl;
	
				cout << endl << "x: " << atomo[i].coord.x;
				cout << endl << "y: " << atomo[i].coord.y;
				cout << endl << "z: " << atomo[i].coord.z << endl;
				
			}
			
			cout << endl << "**************************" << endl;
		}
			
		// calculo da distancia entre atomos
		
		double distancia(int i, int j) {
			
		return sqrt((atomo[j].coord.x-atomo[i].coord.x)*(atomo[j].coord.x-atomo[i].coord.x)+(atomo[j].coord.y-atomo[i].coord.y)*(atomo[j].coord.y-atomo[i].coord.y)+(atomo[j].coord.z-atomo[i].coord.z)*(atomo[j].coord.z-atomo[i].coord.z));	

		}
		
		// calculo do potencial
		
		double potencial(double dist) {
	
		double epsilon=0.0104;
		double sigma=3.4;		// 3.4 angstrom
	
		return 4*epsilon*(pow((sigma/dist),12)-pow((sigma/dist),6));
		
		}
		
		// calculo da energia
		
		double energia() {
	
			double en=0; 		// variavel de guardadura da energia
			int i;			// iteracao i
			int j;			// iteracao j
			
			for (i = 0 ; i < size ; i++) {
		
				for (j = 0 ; j < i ; j++) {
					
					en+=potencial(distancia(i,j));		// calcula a energia entre os 2 atomos i e j
		
				}		
		
			}
	
			return en;
	
		}
		
		void desenharpotencial() {
			
			double r;	// incremento do raio
			
			PlotInit(2,5,-0.1,0,"xwin");
			
			for( r=2; r < 5; r+=0.1) {
			
			DrawPoint(r,potencial(r),"Circle","Red","XS");
			
			}
			
			PlotEnd();
		}
		
};


// mother-function - chamada assim: aula6.exe numero_de_atomos(N) limite resolucao temperatura

int main(int argc, char **argv){
	
// Variaveis

	int N=atoi(argv[1]);

	int limite=atoi(argv[2]);		// insistencia de recalculo
	
	int contas=0;				// iteracao para limite
	
	int contasr=0;				// iteracao para contas de reijeicao
	
	double resolucao=atof(argv[3]);		// 1/resolucao
	
	double T=atof(argv[4]);			// temperatura a que e' calculada a configuracao
	
	double enold;			// energia antiga
	double enteste;			// energia teste
	double deltaen;			// delta energia
	
	double xold;			// coordenada x antiga
	double yold;			// coordenada y antiga
	double zold;			// coordenada z antiga
	
	int rejeicoes=0;		// quantos recalculos deram piores
	
	int i=0;			// iteracao dos atomos
	int j=0;			// iteracao dos atomos
	
//	vector<double> distancias; 	// vector com as varias distancias
	
	double distancia=0;		// valor da distancia
	
	double kb=1.38e-23;		// constante de boltzmann
	
	double r=0.0;			// teste de rejeicao
	double w=0.0;			// w calculado com a exponencial
	
// Inicializacoes
	
	LIBNUM::RngInit();					// inicializar LIBNUM

	cgas argon(N);						// definir classe gas... argon com 2 atomos

	argon.criacoords();					// usar funcao da classe para criar coords aleatorias

// coordenadas da posição de menor energia para duas!!! particulas a T=0
/*
	argon.atomo[0].coord.x = -4.47058;
	argon.atomo[0].coord.y = -0.441903;
	argon.atomo[0].coord.z = -0.540487;
	
	argon.atomo[1].coord.x = -3.25203;
	argon.atomo[1].coord.y = -2.96865;
	argon.atomo[1].coord.z = -3.12806;
*/	

	argon.mostracoords();			// mostrar essas coordenadas
	
	enold=argon.energia();			// guardar a energia antiga	
	
	cout << endl << "Energia de coesão inicial: " << argon.energia() << endl;	
	
	
	while ( contas < limite ) {
		
		contas++;
		
		i = LIBNUM::RngInt(N);		// gera inteiro aleatorio de 0 e N-1
			
		xold = argon.atomo[i].coord.x;	// guardar coordenadas antigas
		yold = argon.atomo[i].coord.y;
		zold = argon.atomo[i].coord.z;
		
		argon.atomo[i].coord.x += LIBNUM::RngDouble()*resolucao-(resolucao/2);	// mudar coordenadas com incremento
		argon.atomo[i].coord.y += LIBNUM::RngDouble()*resolucao-(resolucao/2);	// entre [-resolucao,resolucao]
		argon.atomo[i].coord.z += LIBNUM::RngDouble()*resolucao-(resolucao/2);
		
		enteste=argon.energia();				// guardar energia nova para teste
		
		if (enteste < enold) { enold=enteste; continue; }
		
		else { 	// se energia maior, repoe coordenadas antigas, incrementa rejeicoes...
			
		deltaen=enteste-enold;			// calcular delta energia
		
		r=LIBNUM::RngDouble();			// calcular probabilidade de rejeicao
		w=exp(-deltaen*(1/(kb*T)));		// calcular w
	
		if ( r > w ) {
			
			argon.atomo[i].coord.x = xold;
			argon.atomo[i].coord.y = yold;
			argon.atomo[i].coord.z = zold;
			
			rejeicoes++;
			
			contasr++;
			
			if (contasr == 100 && (double) rejeicoes / (double) contasr > 0.5) { 
				
			resolucao*=(1 - 1/(double)limite);
			
			contasr=0;
			
			cout << endl << "% de rejeicoes: " << (double) rejeicoes / (double) contas << endl;
			
			cout << endl << "nova resolucao: " << resolucao << endl;
			
			
			}
			
		}
		else { enold=enteste; continue; }
		}
	
	}
	
	cout << endl << "Energia de coesão final: " << argon.energia() << endl;

/*	
	string line;
	ifstream myfile (argv[2]);
	if (myfile.is_open())
	{	
		int i=0;
				
		while (! myfile.eof() )
		{
			getline (myfile,line);
			
			coord[i]=atof(line);
			
			cout << coord[i] << endl;
			
			i++;
		
		}
		myfile.close();
	}

	else cout << "Unable to open file"; 

		
// Loop de construcao

	PlotInit(-rmax,rmax,-rmax,rmax,"xwin");
		
	DrawPoints(N,X,Y, "Circle" , "Blue" , "XS");

	PlotEnd();
	*/
	return 0;

}

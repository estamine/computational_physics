/*

Programa usa RNGs para estudar Fractais

Requere-se que o utilizador introduza:
	
	-
	-
	-
	-
	
Rui Caldeira, aluno numero 32046, Engenharia Fisica

rui@estamine.net

31 de Marco de 2009, FCUL

*/

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#include "libnum/libnum.h"
#include "libnum/displot.h"
using namespace std;

// iniciar variaveis globais

// norma do numero

double Abs(double num)
{
	if ( num >= 0 )
		return num;
	else
		return -num;
}

// calculo de distancia
// array_de_xs(X[]) array_de_ys(Y[]) num_de_particulas_actual(N) coord_x_partic_actual(xi) coord_y_partic_actual(yi) rmin rmax

bool distancia(double X[], double Y[], int N, double xi, double yi, double rmin, double rmax) {
	
	int iter=0;		// inteiro de iteracao para percorrer as coordenadas
	
	double dist;		// double para a distancia
	
	for ( iter = 0; iter < N ; iter++) {
	
	dist=sqrt((X[iter]-xi)*(X[iter]-xi) + (Y[iter]-yi)*(Y[iter]-yi));
	
	if ( dist <= rmin ) { return false; iter=N; }	// se já está perto de uma particula para
	
	}
	
	return true;
}

// mother-function - chamada assim: aula4.exe num_de_particulas(N) raio_max(rmax) raio_min(rmin) salto_dr(dr)

int main(int argc, char **argv){

// Variaveis
	
	int N=atoi(argv[1]);		// numero de particulas pretendidas
	double X[N];			// array de coordenadas X de cada particula
	double Y[N];			// array de coordenadas Y de cada particula
	double rmax=atof(argv[2]);	// variavel para raio maximo
	double rmin=atof(argv[3]);	// variavel para raio minimo
	double dr=atof(argv[4]);	// variavel para salto pequenino	
	double xi=0.0;			// coordenada x random do novo ponto
	double yi=0.0;			// coordenada y random do novo ponto
	double teta;			// angulo a gerar
	
	
//	int controlo=0;
//	cout << "\nrmin: " << rmin << "\nrmax: " << rmax << "\n"; cin >> controlo;
	
	
// Inicializações
	
	LIBNUM::RngInit();		// inicializa o randomizer
	X[0]=0; Y[0]=0;			// coordenada de primeira partícula: (0,0)
	
// Loop de construcao
	
	int iterN=1;			// variavel de iteracao que percorrera N coordenadas
	
	while ( iterN < N ) {		// loop que calcula para TODAS as particulas
		
		teta = 2*M_PI*LIBNUM::RngDouble();
		
		xi = rmax*cos(teta);
		yi = rmax*sin(teta);
		
		//cout << "\nINIT\nxi: " << xi << "\nyi: " << yi << "\nteta: " << teta;
		
		//DrawPoint(xi,yi, "Circle" , "Blue" , "XL");
		
		//controlo++; if (controlo > 100 ) {goto fim;}
		
		while ( distancia(X,Y,iterN,xi,yi,rmin,rmax) ) {	// loop que coloca e testa a particula no sitio
		
		if ( sqrt((xi)*(xi) + (yi)*(yi)) <= rmax+0.5 ) {
		
		teta = 2*M_PI*LIBNUM::RngDouble();
			
		xi += dr*cos(teta);
		yi += dr*sin(teta);
		
		//cout << "\nIF < rmax\nxi: " << xi << "\nyi: " << yi << "\ndr*cos: " << dr*cos(teta) << "\nteta: " << teta;
		
		//DrawPoint(xi,yi, "Circle" , "Red" , "XS");
		
		//controlo++; if (controlo > 100 ) {goto fim;}
		
		}
		
		else { 
		
		teta = 2*M_PI*LIBNUM::RngDouble();
			
		xi = rmax*cos(teta);
		yi = rmax*sin(teta);
		
		//cout << "\nELSE\nxi: " << xi << "\nyi: " << yi << "\nteta: " << teta;
		
		//DrawPoint(xi,yi, "Circle" , "Green" , "XS");
		
		//controlo++; if (controlo > 100 ) {goto fim;}
		
		}
		
		}
		
		if ( sqrt(Abs(xi)*Abs(xi) + Abs(yi)*Abs(yi)) < rmax ) {
		
		X[iterN]=xi;	// como saiu do while da distancia mete os novos valores
		Y[iterN]=yi;	//
		
		int cor=0;
		string color;
		
		cor=LIBNUM::RngInt(3);
		
		switch ( cor )
		{
			case 0:
				color="Blue";
				break;
			case 1:
				color="Red";
				break;
			case 2:
				color="Green";
				break;
				
			case 3:
				color="Orange";
				break;	
			
			default:
				color="Blue";
		}

		PlotInit(-rmax,rmax,-rmax,rmax,"xwin");
		
		DrawPoints(N,X,Y, "Circle" , "Blue" , "XS");
		
		iterN++;
		
		}
		
	}
	

	PlotEnd();
	
		
	//fim:
	
	//cin >> controlo; 
	
	
	return 0;

}

#include <iostream>
#include <string>
#include <cmath>
#include <libnum/libnum.h>
#include <libnum/displot.h>
using namespace std;
void Derivs(double x, double y[], double dy[])
{
	double r = 0.8;
	dy[0] = -r*y[0]*y[1]+y[0];
	dy[1] = r*y[0]*y[1]-y[1];
}

int main()
{
	int i , NV=2 , NP=10000 ;
	double yin[NV], ypin[NV], yout[NV], xpp[NP], ypp[NP], zpp[NP];
	double h , x;
	h = 0.2 ; x = 0.0 ; yin[0]=0.5; yin[1]=0.5;
	
	PlotInit(0,100,0,10,"xwin");			// inicializar a plot
	
	Derivs(x,yin,ypin);
	for (i = 0; i< NP; i++)
	{
		xpp[i] = x;
		LIBNUM::RungeKutta4(NV,yin,ypin,x,h,yout,Derivs);
		ypp[i] = yout[0]; x += h; yin[0] = yout[0];
		zpp[i] = yout[1]; x += h; yin[1] = yout[1];
	}
	DrawLine(NP,xpp,ypp,"Solid" , "Red" , "S"); // raposas
	DrawLine(NP,xpp,zpp, "Solid" , "Blue" , "S"); //coelhos
	PlotEnd();
	
	return(0);
}
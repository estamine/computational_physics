/*

Programa que calcula raizes reais de polinomios dados pelo utilizador.

Requere-se que o utilizador introduza:
           
           - Grau do polinomio (com um maximo teorico de 100)
           - Coeficientes do polinomio
           - Máximo de iteracoes (Metodo de Newton)
           - Valor de tolerancia (Metodo de Newton)
           - Raiz aproximada (Metodo de Newton)
           
Para se proceder ao calculo das raizes utilizar-se-a' o Metodo de Newton para
achar raizes e a Regra de Rufini para decompor o polinomio.

Rui Caldeira, aluno numero 32046, Engenharia Fisica

rui@estamine.net

Abril de 2007, FCUL

*/

#include <iostream>
#include <math.h>    //necessaria para a funcao potencia pow()
using namespace std;

// iniciar variaveis globais
int n=4;                    // grau de polinomio
int icoef=0;                // iterador do array de coeficientes
int imax=1000000;           // numero maximo de iteracoes
double tol=0.000001;        // tolerancia da aproximacao
double coefglobal[101];     // array global de coeficientes com limite de grau 100
double raizaprox=1;         // raiz aproximada

// pol() funcao que calcula o resultado do polinomio para um dado valor
double pol(double coef1[],double valor, int grau)
{
double resultado=0;        // resultado da funcao

for(icoef = grau; icoef >= 0; icoef--) 
{

resultado+=pow(valor,icoef)*coef1[icoef];

}

return resultado;
}

// pol1() funcao que calcula o resultado do polinomio derivado para um dado valor
double pol1(double coef1[],double valor, int grau)
{
double resultado=0;        // resultado da funcao
double coefderiv[grau-1];  // array de coeficientes do polinomio derivado

// encher o array com os coeficientes multiplicados pelas potencias derivadas
for(icoef = grau; icoef >= 1; icoef--) 
{

coefderiv[icoef-1]=coef1[icoef]*icoef;

}

// calcular o resultado
for(icoef = grau; icoef >= 0; icoef--) 
{

resultado+=pow(valor,icoef)*coefderiv[icoef];

}

return resultado;
}

// ruf() funcao que aplica a regra de rufini
void ruf (double coef1[],double raiz, int grau)
{
double coefruf[grau-1];         // array dos coeficientes do polinomio decomposto

coefruf[grau-1]=coef1[grau];

// ciclo que aplica a regra de rufini
for(icoef = grau-1; icoef >= 1; icoef--) 
{

coefruf[icoef-1]=coef1[icoef]+coefruf[icoef]*raiz;

}    

// ciclo que transfere resultado da aplicacao da regra de rufini para array geral 
for (icoef = grau-1; icoef>=0; icoef--)
{
    
    coefglobal[icoef]=coefruf[icoef];
    
}

    return;
}

// newt () funcao que aplica o metodo de newton
bool newt (double coef1[], double raiz, int grau)
{
int iter=imax;         // iterador interno inicializado com o mesmo valor do maximo de iteracoes introduzido pelo utilizador
double tolcheck=0;     // variavel de verificacao da tolerancia
double tolcheckabs=0;  // valor absoluto da variavel de verificacao da tolerancia

// ciclo que aplica o metodo de newton
      while(iter > 0) 
{
      tolcheck=(-pol(coef1,raiz,grau)/pol1(coef1,raiz,grau));
      
      raiz+= tolcheck;    
    
    iter--;
    
    tolcheckabs=fabs(tolcheck);
    if (tolcheckabs < tol) { break; }; // condicao que verifica tolerancia e que termina o ciclo em caso TRUE
}

// condicao que verifica se a tolerancia foi ou nao atingida. para iter > 0, foi atingida. para iter == 0, nao foi atingida.
    if (iter == 0) {      
                       
    cout << "\nRaiz " << grau << " e restantes nao sao reais ou nao existem.";

// retorno que comunica 'a funcao rufnewt (que controla ruf e newt) que ja nao existem mais raizes reais.
    return true;

    }
    else 
    {

// condicao que verifica se o valor absoluto da raiz achada e' menor do que a tolerancia. se for considera-se zero, mostrando na mesma o valor obtido.
// esta condicao pode falhar, embora raramente
    if ( fabs(raiz) <= tol && raiz != 0 ) {
    
    cout << "\nRaiz " << grau << ": 0 (valor nao arredondado: " << raiz << ")";
    
    }
    else
    {

    cout << "\nRaiz " << grau << ": " << raiz;
    
    };

// atribuicao do valor da raiz obtida 'a variavel global raizaprox
    raizaprox = raiz;

// retorno que comunica 'a funcao rufnewt que (controla ruf e newt ) que ainda podera0 existir mais raizes reais.    
    return false;

    };
    
}

// rufnewt () funcao que controla Rufini e Newton
void rufnewt (double coef1[], int grau)
{
       
int iter = grau;     // iterador inicializado com valor do grau do polinomio de entrada
bool falhou=false;   // booleano que controla a existencia de raizes reais

for (icoef = grau; icoef>=0; icoef--)
{
    coefglobal[icoef]=coef1[icoef];   //copia do array de coeficientes de entrada para o array de coeficientes global
    
}

// ciclo que aplica as funcoes ruf e newt n vezes. sendo n o grau do polinomio.
       while (iter>0)
       {
 
            falhou = newt(coefglobal,raizaprox,iter);
            
            if (falhou) { return; };            
            
            ruf(coefglobal,raizaprox,iter);
                         
            iter--;
                   
       }

       return;

}

// funcao main
int main ()
{ 

// iniciar variaveis locais
string simnao;         // string de confirmacao de polinomio

cout << "\nCalculo das raizes de um polinomio (grau maximo 100) usando Metodo de Newton e Regra de Rufini\n\n";
cout << "Introduza 0 (zero) para manter valor (default) ou responder nao (n)\n\n"; // practico e evita introducao de valores nulos ou negativos

cout << "Ordem do polinomio (4)? "; cin >> n;
if (n <= 0) { n = 4; };
if (n > 100) { main();};

cout << "\n";

double coef[n];   // declaracao do array dos coeficientes do polinomio

// encher o array com os coeficientes
for(icoef = n; icoef >= 0; icoef--) 
{

           cout << "Coeficiente a" << icoef << ": "; cin >> coef[icoef];

}

cout << "\n";

// mostrar polinomio para confirmacao
for(icoef = n; icoef >= 1; icoef--) 
{
           cout << coef[icoef] << "x^" << icoef << " + ";
}

cout << coef[0] << " = 0\n";

// confirmacao de polinomio
cout << "\n\nPretende alterar (s/n)? ";
cin >> simnao;

if (simnao == "s") { main(); };

// pedido de tolerancia, numero maximo de iteracoes e sugestao de raiz
cout << "\nTolerancia de aproximacao (0.000001)? ";
cin >> tol;
if (tol <= 0) { tol = 0.000001; };

cout << "\nNumero maximo de iteracoes (1000000)? ";
cin >> imax;
if (imax <= 0) { imax = 1000000; };

cout << "\nRaiz aproximada (1)? ";
cin >> raizaprox;
if (raizaprox <= 0) { raizaprox = 1; };

// output do resumo dos valores introduzidos
cout << "\n*** Resumo dos valores introduzidos ***\n";
cout << "\nPolinomio: ";
// mostrar polinomio para confirmacao
for(icoef = n; icoef >= 1; icoef--) 
{
           cout << coef[icoef] << "x^" << icoef << " + ";
}

cout << coef[0] << " = 0\n";
cout << "\nTolerancia de aproximacao: " << tol;
cout << "\nNumero maximo de iteracoes: " << imax;
cout << "\nRaiz aproximada: " << raizaprox;
cout << "\n\n*** Raizes calculadas ***\n";

// inicializacao da funcao rufnewt que controla ruf e newt e o numero de vezes que devem ser aplicadas
rufnewt (coef,n);  

// confirmacao de repeticao de programa
cout << "\n\nSair do programa (s/n)? ";
cin >> simnao;

if (simnao != "s") { main(); };

    return 0;

}

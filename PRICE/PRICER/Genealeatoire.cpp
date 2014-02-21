//  Genealeatoire.cpp


#include "Genealeatoire.h"
#include <cstdlib>
#include <cmath>
#include "math.h"
#include "time.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////
// Constructeur:
Random::Random() : i(0)
{};

////////////////////////////////////////////////////////////////////////////////////
// Classe mère:
////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////// UNIFORME (0,1) //////////////////////////////////////
double Random::uRand()
  {
     return (rand()/static_cast<double>(RAND_MAX));
 }


////////////////////////////////// LOI NORMALE (0,1)  //////////////////////////////////////
// Permet de simuler une loi normale centrée réduite:

double Random::GNormale()
    {
            double result=0;
            for (unsigned long j=0; j < 12; j++)
            result += rand()/static_cast<double>(RAND_MAX);
            result -= 6.0;
            return result;

    }

////////////////////////////////// LOI LOGNORMALE (m, vega2)  //////////////////////////////////////
// Génère, à partir de la loi normale centrée réduite, une loi lognormale de paramètre m et vega2:

double Random::GLogNormale(double m, double vega2)
{
      Random loi;
      double normal=sqrt(vega2)*loi.GNormale()+m;
      double lognormal=exp(normal);
      return lognormal;
}

////////////////////////////////// LOI POISSON (lambda)  //////////////////////////////////////
// Permet de générer une loi de Poisson:

        double Random::GPoisson(double lambda)
{
    double L=exp(-lambda);
    double p(1);
    int k(1);
    Random Uniforme;
    while (p>L)
    {
        p=p*Uniforme.uRand();
        k+=1;
    }
    return (k-1);
}

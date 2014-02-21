/*
CLASSES PAYOFF
Les sous-classes disposent d'une méthode, sous forme d'opérateur, qui génère le PayOff selon le type d'option dont on cherche le prix
*/

#include "PayOff.h"
#include "Option.h"
#include "StatGatherer.h"

using namespace std;

////////////////////////////////// CALCUL MIN / MAX //////////////////////////////////////

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)


////////////////////////////////// CONSTRUCTEUR MERE //////////////////////////////////////

PayOff::PayOff()
{}

////////////////////////////////// CONSTRUCTEUR FILLE CALL //////////////////////////////////////

PayOffCall::PayOffCall(double Strike) : m_Strike(Strike)
{}

////////////////////////////////// PAY OFF CALL ////////////////////////////////////////

double PayOffCall::operator()(double Spot) const
{
    return max(Spot-m_Strike,0);
}

////////////////////////////////// CONSTRUCTEUR FILLE PUT //////////////////////////////////////

PayOffPut::PayOffPut(double Strike) : m_Strike(Strike)
{}

////////////////////////////////// PAY OFF PUT ////////////////////////////////////////


double PayOffPut::operator()(double Spot) const
{
    return max(m_Strike-Spot,0);
}

/*

Possibilité d'ajouter des Pay-Offs différents comme asiatiques
Souci : très chronophaque de tracer des graphes pour des options path dependent (gestion des QVectors, calcul de moyennes à chaque cloture...)
Le calcul du prix lui fonctionne en revanche très bien.
////////////////////////////////// CONSTRUCTEUR FILLE CALL ASIATIQUE //////////////////////////////////////

PayOffCallA::PayOffCallA(double Strike, double Expiry, double Spot, double Vol, double r, double lambda, double m, double vega2) :  m_Strike(Strike), m_Expiry(Expiry), m_Spot(Spot), m_Vol(Vol), m_r(r), m_lambda(lambda), m_m(m), m_vega2(vega2)
{}

////////////////////////////////// PAY OFF CALL ASIATIQUE ////////////////////////////////////////

double PayOffCallA::operator()(double Spot) const
{
    PayOffCall PO(m_Strike);
    OptionB pSimuB(m_Strike,m_Expiry,m_Spot,m_Vol,m_r,PO);
    OptionL pSimuL(m_Strike,m_Expiry,m_Spot,m_Vol,m_r, m_lambda, m_m, m_vega2, PO);
    StatGatherer CoursB(pSimuB, m_Expiry*250, m_Expiry);
    StatGatherer CoursL(pSimuL, m_Expiry*250, m_Expiry);
    QVector<double> A;
   // if (Type==1)
          A=CoursB.SimuCoursB();
   // else if (Type==0)
    //      A=CoursL.SimuCoursB();
    double runningsum(0);
    for (int i=0;i<A.size()-1;i++)
    {
    cout << A[i] << endl;
        runningsum+=max(A[i]-m_Strike,0);
    }
    cout << "FIN SIMU" << endl;
    return runningsum/(A.size());
}
    */












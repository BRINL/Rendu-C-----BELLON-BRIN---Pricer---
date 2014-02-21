#ifndef FUNVECT_H
#define FUNVECT_H

#include "PayOff.h"
#include <QVector>
using namespace  std;

// Ce template à pour but d'appliquer une Opérateur de classe fille de la classe PayOff
// à chaque élément d'un QVector. Ceci est utile compte tenu du faite que nous utilisons l'antithetic sampling.
// Pour chaque simulation, deux simulations de cours sont générées, il faut appliquer l'opérateur Pay-Off sur un QVector.
// Il est possible d'utiliser ce template pour n'importe quel Pay-Off.

template<class PayOff>
QVector <double> FVect(QVector<double> A, PayOff& F)
{
QVector <double> B(A.size(),0);
for (int i(0);i<A.size();i++)
{
    B[i]=F(A[i]);
}
return B;
}



#endif // FUNVECT_H

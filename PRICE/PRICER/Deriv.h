#ifndef DERIV_H
#define DERIV_H

#include "Greeks.h"
#include <iostream>
#include <QVector>
#include <cmath>

using namespace std;

// Ce header contient des templates pour la classe Greeks. Cette dernière ayant 4 classes filles, ayant chacune un opérateur renvoyant le prix selon une des
// quatre paramètres suivants (Spot, Strike, Expiry, Vol)

//////////////////////////////////////////// DERIVATION /////////////////////////////////////////////////
// Ce template approche la valeur de la dérivée avec la méthode d'Euler.
// Elle reçoit en paramètre, le centre (qui correspond au point en lequel on souhaite obtenir la dérivée)
// l'écart, qui correspond à la taille du segment sur lequel on décide de calculer le taux d'accroissement.
// Et enfin un objet d'une des classes filles. Ainsi Object(point), grâce aux opérateurs de chaque classe fille
// renvoie le prix en le point. Selon, la classe fille à laquelle l'objet appartient, le point correspond à un Spot
// un Strike, une Maturité ou une Volatilité


template<class Greeks>
double Deriv(double centre, double ecart, Greeks& Function)
{
double av(centre-ecart);
double ap(centre+ecart) ;
return (Function(ap)-Function(av))/(ap-av);
}


//////////////////////////////////////////// DERIVATION SECONDE /////////////////////////////////////////////////
// Même principe avec la dérivé seconde. On utilise toujours la méthode d'Euler. Elle est appliquée deux fois.



template<class Greeks>
double Deriv2(double centre, double ecart, Greeks& Function)
{
double av2(centre-2*ecart);
double av(centre-ecart);
double ap(centre+ecart);
double ap2(centre+2*ecart) ;
return -(((Function(av)-Function(av2))/(av-av2))-((Function(ap2)-Function(ap))/(ap2-ap)))/(3*ecart);
}

//////////////////////////////////////////// TRACER GRAPHES /////////////////////////////////////////////////
// Ce template sert à récuperer dans un QVector les prix selon un paramètre qui dépend de l'appartenance de l'objet Function
// à une classe fille de Greeks.
// L'utilisateur entre début / fin qui correspondent au début et fin du segment d'appartenance au paramètre, sur lequel on souhaite obtenir le prix.
// Enfin, prec correspond au nombre de points calculés sur ce segment. Il en dépend la précision du graphe.


template<class Greeks>
QVector <double> Tfunc(double debut, double fin, int prec, Greeks& Function)
{
QVector<double> A(prec);
double pas=(fin-debut)/prec;
double axe=debut;
for (int i(0); i<prec; i++)
{
    A[i]=Function(axe);
    axe+=pas;
}
return A;
}


//////////////////////////////////////////// AXE /////////////////////////////////////////////////
// Ces quelques lignes de code servent simplement à créer un QVector découpant le segment [debut;fin] en prec parties
// En effet, QCustomPlot demande deux vecteurs pour tracer une courbe. Axe correspondant à x et le QVector précendent à y dans une fonction y=f(x)


template<class Greeks>
QVector <double> TfuncAxis(double debut, double fin, int prec, Greeks& Function)
{
QVector<double> A(prec);
double pas=(fin-debut)/prec;
double axe=debut;
for (int i(0); i<prec; i++)
{
    A[i]=axe;
    axe+=pas;
}
return A;
}

//////////////////////////////////////////// ROOT /////////////////////////////////////////////////
// Le but de Root est de calculer les racines d'une fonction. On utilise ici la méthode par Dichotomie
// (celle utilisant la dérivée (Newton) étant moins bonne dès lors que l'on ne dispose pas d'écriture explicite des dérivées).
// L'intérêt de ce template est de pouvoir calculer la volatilité implicite.
// Les modèles sur lesquels nous travaillons ici, donne pour des paramètres un prix. L'idée ici est de procéder dans l'autre sens
// A partir du prix du marché, renvoyer un paramètre en soi. Notamment la volatilité.
// Si l'on appelle P notre fonction qui renvoie le prix selon Vol, on a P(vol)=prix, on cherche donc P^-1(prixdumarché) qui est une volatilité.
// ce qui équivaut à chercher pour quelle Vol, P(Vol)-prix=0 et donc à trouver une racine de P. D'où l'intéret de ces lignes.



template<class Greeks>
double Root(double a, double b, double prec, double Prix, Greeks& Function)
{
while (b-a>prec)
{
if (Function(a+0.5*(b-a))-Prix<0)
    a=a+0.5*(b-a);
else if (Function(a+0.5*(b-a))-Prix>0)
    b=a+0.5*(b-a);
}
return b;
}



#endif // DERIV_H

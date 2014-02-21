#include "Greeks.h"
#include "Option.h"
#include "MC.h"
#include "Deriv.h"

// Pour calculer les grecques. Une classe mère Greeks, et des classes filles Deltac, Thetac, Vegac, Rhoc munie chacune d'un opérateur qui retourne le prix selon un paramètre.
// Ce paramètre est respectivement, le Spot, la Maturité, la Volatilité et le taux sans risque r.
// Ainsi, ces opérateurs sont tous des fonctions qui renvoient le prix de l'option selon un paramètre.
// L'avantage de cette technique est que l'on peut ainsi facilement tracer la fonction du prix selon les paramètres (onglet variation des paramètres)
// et calculer les grecques qui correspondent à la dérivée de chacune de ces fonctions en le paramètres entré par l'utilisateur (cf. le template Deriv.h)

////////////////////////////////////// CLASSE MERE /////////////////////////////////////////////////

Greeks::Greeks()
{}

Deltac::Deltac(Option& MonOption, unsigned long prec) : m_Option(MonOption), m_prec(prec)
{
}

////////////////////////////////////// CLASSE DELTA : PAR RAPPORT AU SPOT /////////////////////////////////////////////////

double Deltac::operator()(double Spot) const
{
    MC maMC;
    return maMC.PrixAc(m_prec,m_Option, Spot, m_Option.getExpiry(), m_Option.getr(), m_Option.getSigma()) ;
}

Thetac::Thetac(Option& MonOption, unsigned long prec) : m_Option(MonOption), m_prec(prec)
{
}


////////////////////////////////////// CLASSE TETHA : PAR RAPPORT A LA MATURITE /////////////////////////////////////////////////


double Thetac::operator()(double Expiry) const
{
    MC maMC;
    return maMC.PrixAc(m_prec,m_Option, m_Option.getSpot(), Expiry, m_Option.getr(), m_Option.getSigma()) ;
}


Vegac::Vegac(Option& MonOption, unsigned long prec) : m_Option(MonOption), m_prec(prec)
{
}

////////////////////////////////////// CLASSE VEGA : PAR RAPPORT A LA VOLATILITE /////////////////////////////////////////////////


double Vegac::operator()(double sigma) const
{
    MC maMC;
    return maMC.PrixAc(m_prec,m_Option, m_Option.getSpot(), m_Option.getExpiry(), m_Option.getr(), sigma) ;
}

Rhoc::Rhoc(Option& MonOption, unsigned long prec) : m_Option(MonOption), m_prec(prec)
{
}

////////////////////////////////////// CLASSE RHO : PAR RAPPORT AU TAUX SANS RISQUE /////////////////////////////////////////////////

double Rhoc::operator()(double r) const
{
    MC maMC;
    return maMC.PrixAc(m_prec,m_Option, m_Option.getSpot(), m_Option.getExpiry(), r, m_Option.getSigma()) ;
}

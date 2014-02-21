#include "Option.h"
#include "StatGatherer.h"
#include "MC.h"
#include <QVector>

// Classe crée dans le but de récuperer des vecteurs contenant les résultats des méthodes d'Option.cpp et MC.cpp
// en différentes valeurs. Ces vecteurs sont ensuite utilisés pour tracer les graphes dans MainWindow.cpp

StatGatherer::StatGatherer(Option& MonOption, int taille, double fin) : m_taille(taille), m_fin(fin), m_MonOption(MonOption)
{
}

//////////////////////////////////////////////////////////// VECTEUR DE SIMULATION DE COURS /////////////////////////////////////////////////////////////
// Utilise la méthode Simu (et non l'opérateur dans lequel il n'est pas possible de changer les paramètres) pour générer un QVecteur qui contient,
// la trajectoire d'une simulation de cours. Ceci fonctionne de manière récursive. Pour une maturité de 1 an par exemple, on divise l'année par taille (attribut
// hérité de la classe mère) par exemple par 365. On simule ensuite le cours du jour 1 au 2, puis du 2 au 3...


QVector<double> StatGatherer :: SimuCoursB()
{
    QVector<double> StatG(m_taille);
    double pas=m_fin/m_taille;
    double rec=m_MonOption.Simu(m_MonOption.getSpot(), pas, m_MonOption.getr(), m_MonOption.getSigma());
    double axe(0);
    for (int i=0;i<m_taille;++i)
    {
        axe+=pas;
        rec=m_MonOption.Simu(rec, pas, m_MonOption.getr(), m_MonOption.getSigma());
        StatG[i]=rec;
    }
    return StatG;
}

//////////////////////////////////////////// AXE /////////////////////////////////////////////////
// Ces quelques lignes de code servent simplement à créer un QVector découpant le segment [0;fin] en taille (attribut de la classe mère) parties
// En effet, QCustomPlot demande deux vecteurs pour tracer une courbe. Axe correspondant à x et le QVector précendent à y dans une fonction y=f(x)


QVector<double> StatGatherer :: Axis()
{
    QVector<double> Axis(m_taille);
    double pas=m_fin/m_taille;
    double axe(0);
    for (int i=0;i<m_taille;++i)
    {
        Axis[i]=axe;
        axe+=pas;
    }
    return Axis;
}

//////////////////////////////////////////// VECTEUR PAYOFF /////////////////////////////////////////////////
// Cette méthode calcule le prix de l'option pour des Spots différents. Elle génère ainsi un QVector qui sert
// à tracer le graphe de l'onglet (graphe des Pay-Offs).


QVector<double> StatGatherer :: GPO()
{
    QVector<double> GPO(m_taille);
    MC maMC;
    double pas=m_fin/m_taille;
    double axe(0);
    for (int i=0;i<m_taille;++i)
    {
        axe+=pas;
        GPO[i]=maMC.PrixAc(10000,m_MonOption, axe, m_MonOption.getExpiry(), m_MonOption.getr(), m_MonOption.getSigma());
    }
    return GPO;
}

//////////////////////////////////////////// VECTEUR PAYOFF A LA MATURITE /////////////////////////////////////////////////
// Cette méthode calcule le pay-off d'une option à la maturité, sur un segment de spots.
// Ce vecteur permet de visualiser la valeur intrinsèque de l'option sur les graphes de l'onglet (graphe des Pay-Offs).

QVector<double> StatGatherer :: GPOT()
{
    QVector<double> GPO(m_taille);
    double pas=m_fin/m_taille;
    double axe(0);
    for (int i=0;i<m_taille;++i)
    {
        GPO[i]=m_MonOption.getPayOffgT(axe);
        axe+=pas;
    }
    return GPO;
}

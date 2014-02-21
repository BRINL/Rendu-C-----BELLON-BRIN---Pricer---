#include "MC.h"
#include <QVector>
#include "Option.h"
#include <cmath>
using namespace std;

// On va calcuer le prix de notre option par Monte-Carlo.
// De la classe mère MC, héritent toutes les classes filles qui génèrent les Monte-Carlo s'arrêtant selon des critères différents.
// Le temps de calcul, le nombre d'itérations...
// On procede à du "Antithetic sampling" pour économiser du temps de calcul. Pour chaque variable générée,
// On prend son opposée et on le rajoute dans les valeurs consistuants le Monte-Carlo.

MC::MC() : i(0)
{   
}

//////////////////////////////////////////////// ARRET MONTE CARLO = NOMBRE D'ITERATIONS /////////////////////////////////////////
// Cette première classe fille calcule le prix par MC et s'arrêtent lorsque le nombre d'itérations entrée par l'utilisateur est atteint.
// (i, compteur, atteint la valeur NumberOfPaths dans le while).

QVector <double> MC::PrixA(unsigned long NumberOfPaths, Option& Option)
{
    QVector <double> PrixAV(NumberOfPaths);
    double runningSum(0);
    unsigned long i(0);
    while (i<NumberOfPaths-1)
 {
     QVector <double> A=Option.getPayOff(Option);
        i+=1;
     runningSum+=0.5*(A[0]+A[1]);
     PrixAV[i]=(runningSum/i)*exp(-Option.getExpiry()*Option.getr());
 }
    return PrixAV;
 }

//////////////////////////////////////////////// ARRET MONTE CARLO = LE TEMPS /////////////////////////////////////////
// On utilise time.h pour que le calcule ne dure que le temps impartie par l'utilisateur.


double MC::PrixT(int secondes, Option& Option)
{
    time_t tbegin,tend;
    unsigned long k=0;
    double texec=0.;
    double runningSum(0);
    tbegin=time(NULL);              // Date du debut
    while (texec<secondes)
    {
        tend=time(NULL);                // Date de fin
        k+=1;
        QVector <double> A=Option.getPayOff(Option);
        runningSum+=0.5*(A[0]+A[1]);
        texec=difftime(tend,tbegin); // tend-tbegin (resultat en secondes)
    }
    double resultat=(runningSum/k)*exp(-Option.getExpiry()*Option.getr());
    return resultat;
}

//////////////////////////////////////////////// ARRET MONTE CARLO = L'ECART-TYPE EMPIRIQUE /////////////////////////////////////////
// Fonctionne mais est très très long car il faut calculer l'écart-type à chaque boule, pas mis en place dans le programme.


QVector <double> MC::PrixSE(int SE, Option& Option)
{
    unsigned long k=0;
    double runningSum(0);
    double runningSumCarre(0);
    double VarianceEmpirique(100);
    double resultatSansEscompte(0);
    QVector <double> resultat(2);
    resultat[0]=0;
    double resultataucarre(0);
    while ((SE<VarianceEmpirique) || (k<10) )
    {
        k+=1;
        double VAR=Option.getPayOff(Option)[1];
        runningSum+=VAR;
        runningSumCarre+=VAR*VAR;
        if (k==1) {
            runningSum+=Option.getPayOff(Option)[1];
            runningSumCarre+=Option.getPayOff(Option)[1]*Option.getPayOff(Option)[1];
            k=2;
     }

        resultatSansEscompte=(runningSum/k);
        resultataucarre=(runningSumCarre/k);
        VarianceEmpirique=sqrt(((resultataucarre-resultatSansEscompte*resultatSansEscompte)/k));
  }
    resultat[0]=resultatSansEscompte*exp(-Option.getExpiry()*Option.getr());
    resultat[1]=sqrt(VarianceEmpirique);
        return resultat;
}

//////////////////////////////////////////////// ARRET MONTE CARLO = LA CONVEXITE /////////////////////////////////////////
// Arret avec la convexite: quand une valeur supplementaire n'apporte plus d'information, on arrêt la boucle (on regarde la différence du résultat entre deux boucles consécutives).
// Ne fonctionne pas, donc pas implémenté. En effet, les méthodes de Monte-Carlo s'appuyant sur des simulations, ils arrivent
// un nombre assez important de fois, que deux simulations successives sont suffisament proches pour que la variation du prix soit
// faible et que la méthode s'arrête. Ceci n'est bien sûr du qu'au hasard, et ne reflète en rien la précision du prix
// calculé jusqu'à l'heure.

double MC::PrixCV(double secondes, Option& Option)
{
    unsigned long k(1);
        double runningSum(0);
        double resultat(0);
        double resultatancien(100);
     // Date du debut
    while (fabs(resultat-resultatancien)>secondes)
    {
        resultatancien=(runningSum/k)*exp(-Option.getExpiry()*Option.getr());
        runningSum+=0.5*(Option.getPayOff(Option)[0]+Option.getPayOff(Option)[1]);
        resultat=(runningSum/k)*exp(-Option.getExpiry()*Option.getr());
           k+=1;
    }

    return resultat;
}

//////////////////////////////////////////////// ARRET MONTE CARLO = POUR GRAPHE /////////////////////////////////////////
// Classe qui calcule par Monte-Carlo selon le même procédé que la première classe (nombre d'itérations), la seule différence
// est que l'on surcharge beaucoup plus le constructeur dans cette classe fille.
// Ainsi, on a plus de flexibilité sur les paramètres. Le but est de pouvoir tracer un certain nombre de graphiques (notamment les celui
// des prix selon le spot price) en simulant des Monte-Carlo mais en faisant varier un paramètre (par exemple le spot price).
// Cette classe offre donc plus de flexibilité.


double MC::PrixAc(unsigned long NumberOfPaths, Option& Simu, double Spot, double Expiry, double r, double sigma)
{
    double runningSum(0);
    for(int i=1;i<NumberOfPaths;i++)
    {
        runningSum+=Simu.getPayOffg(Simu, Spot, Expiry, r, sigma);
    }
    double mean = runningSum/NumberOfPaths;
    double resultat=mean*exp(-(Expiry*r));
    return resultat;
}


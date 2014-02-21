#ifndef GENEALEATOIRE_H
#define GENEALEATOIRE_H

// Header de génération des lois aléatoires

class Random
{
public:
    Random();
    double uRand();
    double GNormale();
    double GLogNormale(double m, double vega2);
    double GPoisson (double lambda);
private:
 int i;
};

#endif // GENEALEATOIRE_H

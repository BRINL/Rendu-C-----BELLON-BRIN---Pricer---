#ifndef PAYOFF_H
#define PAYOFF_H

class PayOff
{
    public :
    PayOff();
    virtual double operator()(double Spot) const=0;
private :
    int i;
};


class PayOffCall : public PayOff
{
    public :
        PayOffCall(double Strike);
        virtual double operator()(double Spot) const;
    private :
        double m_Strike;
};


class PayOffPut : public PayOff
{
    public :
        PayOffPut(double Strike);
        virtual double operator()(double Spot) const;
    private :
    double m_Strike;
  };


/*
 * Possibilité d'étendre à d'autres Pay-Offs (cf Option.cpp)
class PayOffCallA : public PayOff
{
    public :
        PayOffCallA(double Strike, double Expiry, double Spot, double Vol, double r, double lambda, double m, double vega2);
        virtual double operator()(double Spot) const;
    private :
    double m_Strike;
    double m_Expiry;
    double m_Spot;
    double m_Vol;
    double m_r;
    double m_lambda;
    double m_m;
    double m_vega2;
  };
*/


#endif // PAYOFF_H

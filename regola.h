#ifndef REGOLA_H
#define REGOLA_H

class Regola
{
private:
    unsigned int distanzaPosti;
    bool mustMascherina;
public:
    Regola(unsigned int dP=0, bool m=false);
    virtual void getRegole(unsigned int& distP, bool& m) = 0;
    virtual bool getMustMascherina() const;
    virtual void setMustMascherina(bool value);
    virtual unsigned int getDistanzaPosti() const;
    virtual void setDistanzaPosti(unsigned int value);
};

#endif // REGOLA_H

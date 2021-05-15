#include "AbbonamentoFamigliare.h"

AbbonamentoFamigliare::AbbonamentoFamigliare(Data* d, Utente* u, Famiglia* f, double p, string c, int e)
    :Abbonamento(d, u, p, c, e), famiglia(f)
    {}

AbbonamentoFamigliare::~AbbonamentoFamigliare(){
    delete famiglia;
}

/*int AbbonamentoFamigliare::GetNumeroMembri() const{
    return numero_membri;
}*/

double AbbonamentoFamigliare::GetPrezzo() const{

    return EntrataFilm::GetPrezzo()*GetEntrate();//*GetNumeroMembri();

}

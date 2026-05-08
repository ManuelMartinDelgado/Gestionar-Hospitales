#include <Hospital.h>
#include <Cola.h>
#define maxColaEspera 20 // Valor máximo de la cola de espera (siempre 20).

Hospital::Hospital(cadena nom, int id, int mC, int cP, cadena tH)
{
    strcpy(nombreHospital, nom);
    idHospital = id;
    maxCamas=mC;
    codigoPostal=cP;
    strcpy(tipoHospital, tH);
    strcpy (estado, "INACTIVO");
}

void Hospital::getNombreHospital(cadena &nH)
{
    strcpy(nH, nombreHospital);
}



Hospital::~Hospital()
{
    //dtor
}

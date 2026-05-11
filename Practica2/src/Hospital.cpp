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

int Hospital::getIdHospital()
{
    return idHospital;
}

int Hospital::getMaxCamas()
{
    return maxCamas;
}

int Hospital::getNumPacientesIngresados()

{

    return pacientesIngresados.longitud();
}

int Hospital::getNumPacientesEnEspera()
{
    return pacientesEnEspera.longitud();
}

//HACER-------------------
Hospital* getSiguienteHospital();

//HACER-------------------
void setSiguienteHospital(Hospital *pH);



bool Hospital::setMaxCamas(int camas)
{
    bool cambiado = false;

    if (strcmp(estado, "INACTIVO")!= 0)
    {
        cout<<"el hospital debe estar inactivo" << endl;
    }

    else
    {
        maxCamas= camas;

        cambiado=true;

        cout<< "Camas actualizadas" << endl;
    }

    return cambiado;
}
//HACER-------------------
    bool buscarPaciente(int idPaciente);

//HACER-------------------
    bool ingresarPaciente(Paciente p);

//HACER-------------------
    bool bajaPaciente(int idPaciente);

//HACER-------------------
    void exportarPacientesIngresados(Paciente *ingresados);

//HACER-------------------
    void exportarPacientesEnEspera(Paciente *enEspera);


bool Hospital::estaActivo()
{
    bool activo = false;

    if (strcmp(estado,"INACTIVO")==0)
    {
        cout<< "El hospital esta inactivo" << endl;
    }
    else
    {
        activo=true;
    }
    return activo;
}

bool Hospital::estaInactivo()
{
    bool activo = false;

    if (strcmp(estado,"ACTIVO")==0)
    {
        cout<< "El hospital esta activo" << endl;
    }
    else
    {
        activo=true;
    }
    return activo;
}



Hospital::~Hospital()
{
    //dtor
}

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

    if ((strcmp(estado, "INACTIVO")!= 0)&& camas < 5)
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
    bool bajaPaciente(int idPaciente)
    {
        bool eliminado = false;



    }

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

bool Hospital::activar()
{
    bool cambiado =false;
    if (strcmp(estado, "ACTIVO")== 0)
    {
        cout<< "El hospital debe de estar inactivo." << endl;
    }
    else
    {
        strcpy(estado,"ACTIVO");
        cout<< "Estado cambiado"<< endl;
        cambiado=true;
    }
    return cambiado;
}

bool Hospital::desactivar()
{
    bool cambiado =false;
    if (strcmp(estado, "INACTIVO")== 0 || strcmp(estado, "SIN SANGRE")== 0 )
    {
        cout<< "El hospital debe de estar activo." << endl;
    }
    else
    {
        strcpy(estado,"INACTIVO");
        cout<< "Estado cambiado"<< endl;

        int long_lista=pacientesIngresados.longitud();
        int long_cola=pacientesEnEspera.longitud();
        if(!pacientesIngresados.esvacia())
        {
            for (int i=1; i<=long_lista; i++)
            {
                pacientesIngresados.eliminarIzq();
            }
        }

        if (!pacientesEnEspera.esvacia())
        {
            for(int i = 0; i <= long_cola; i++)
            {
                pacientesEnEspera.desencolar();
            }
        }
        cambiado=true;
    }
    return cambiado;
}

bool Hospital::faltaSangre()
{
    bool cambiado = false;

    if (strcmp(estado , "ACTIVO")== 0)
    {
        strcpy(estado,"SIN SANGRE");

        cout<< "Estado cambiado" << endl;

        int long_cola=pacientesEnEspera.longitud();

        if (!pacientesEnEspera.esvacia())
        {
            for(int i = 0; i <= long_cola; i++)
            {
                pacientesEnEspera.desencolar();
            }
        }

        cambiado=true;

    }
    return cambiado;
}

void Hospital::mostrarPacientesIngresados()
{
    Paciente pac;
    for (int i = 1; i<pacientesIngresados.longitud(); i++)
    {
        pac=pacientesIngresados.observar(i+1);
        cout<<"Nombre del paciente: "<< " "<< pac.nombreCompleto<< endl;
        cout<<"Historial clínico: "<< " "<< pac.historialClinico<< endl;
        cout<<"Tipo de sangre: "<< " "<< pac.tipoSangre<< endl;
        cout<<"Gravedad: "<< " " << pac.gravedad<< endl;
        cout<<"Patologia: "<< " "<< pac.patologia<< endl;

    }
}

void Hospital::mostrarPacientesEnEspera()
{
    Paciente pac;
	int lon = pacientesEnEspera.longitud();

    for (int i=0 ; i< lon; i++)
    {
        Paciente temporal = pacientesEnEspera.primero();
        pacientesEnEspera.desencolar();

        if (temporal.nombreCompleto == pac.nombreCompleto)
        {
        cout<<"Nombre del paciente: "<< " "<< pac.nombreCompleto<< endl;
        cout<<"Historial clínico: "<< " "<< pac.historialClinico<< endl;
        cout<<"Tipo de sangre: "<< " "<< pac.tipoSangre<< endl;
        cout<<"Gravedad: "<< " " << pac.gravedad<< endl;
        cout<<"Patologia: "<< " "<< pac.patologia<< endl;
        }
    }
}


Hospital::~Hospital()
{
    //dtor
}

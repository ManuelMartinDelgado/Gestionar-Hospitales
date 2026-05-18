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
    siguienteHospital = NULL;
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

Hospital* Hospital::getSiguienteHospital()
{
    return siguienteHospital;
}

void Hospital::setSiguienteHospital(Hospital *pH)
{
    siguienteHospital=pH;
}



bool Hospital::setMaxCamas(int camas)
{
    bool cambiado = false;

    if ((strcmp(estado, "INACTIVO")!= 0)|| camas < 5)
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


bool Hospital::buscarPaciente(int idPaciente)
{

    bool encontrado=false;
    int long_lista=pacientesIngresados.longitud();
    int i=1;

    if(pacientesIngresados.esvacia())
    {
        cout<< "La lista de pacientes esta vacia" << endl;
    }
    else
    {

        while (i<=long_lista && !encontrado )
        {
            Paciente pac_temporal = pacientesIngresados.observar(i);
            if (pac_temporal.historialClinico == idPaciente)
            {
                encontrado=true;
            }
            else
            {
                i++;
            }
        }
    }

    if (!encontrado)
    {
        if (pacientesEnEspera.esvacia())
        {
            cout<< "La cola esta vacia" << endl;
        }
        else
        {
            int long_cola = pacientesEnEspera.longitud();
            for (int j = 0 ; j< long_cola; j++)
            {
                Paciente pac_tem=pacientesEnEspera.primero();
                pacientesEnEspera.desencolar();

                if (pac_tem.historialClinico == idPaciente)
                {
                    encontrado = true;
                }
                pacientesEnEspera.encolar(pac_tem);
            }
        }
    }

    return encontrado;
}

//HACER-------------------
bool Hospital::ingresarPaciente(Paciente p)
{
    bool ingresado = false;
    if (strcmp (estado, "ACTIVO")!= 0)
    {
        cout << "Solo se puede ingresar pacientes en hospitales Activos"<< endl;
    }

    else
    {

    }

}

//HACER-------------------
bool Hospital::bajaPaciente(int idPaciente)
{
    bool eliminado = false;

    Paciente pac;





}

//HACER-------------------
void Hospital::exportarPacientesIngresados(Paciente *ingresados)
{

}

//HACER-------------------
void Hospital::exportarPacientesEnEspera(Paciente *enEspera)
{

}


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
            for (int i=1; i<long_lista; i++)
            {
                pacientesIngresados.eliminarIzq();
            }
        }

        if (!pacientesEnEspera.esvacia())
        {
            while(!pacientesEnEspera.esvacia())
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

    if (strcmp(estado, "ACTIVO")== 0)
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
    for (int i = 0; i<pacientesIngresados.longitud(); i++)
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



        cout<<"Nombre del paciente: "<< " "<< temporal.nombreCompleto<< endl;
        cout<<"Historial clínico: "<< " "<< temporal.historialClinico<< endl;
        cout<<"Tipo de sangre: "<< " "<< temporal.tipoSangre<< endl;
        cout<<"Gravedad: "<< " " << temporal.gravedad<< endl;
        cout<<"Patologia: "<< " "<< temporal.patologia<< endl;

    }
}


Hospital::~Hospital()
{
    //dtor
}

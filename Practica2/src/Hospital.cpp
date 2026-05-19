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
        Cola colaAuxiliar; // Creamos una cola auxiliar para no romper la prioridad

        while (!pacientesEnEspera.esvacia())
        {
            Paciente pac_tem = pacientesEnEspera.primero();
            pacientesEnEspera.desencolar();

            if (pac_tem.historialClinico == idPaciente)
            {
                encontrado = true;
            }

            colaAuxiliar.encolar(pac_tem); // Lo guardamos a salvo en la auxiliar
        }

        // Devolvemos todos los pacientes a la cola de espera original
        while (!colaAuxiliar.esvacia())
        {
            pacientesEnEspera.encolar(colaAuxiliar.primero());
            colaAuxiliar.desencolar();
        }
    }

    return encontrado;
}

bool Hospital::ingresarPaciente(Paciente p)
{
    bool ingresado = false;

    if (strcmp(estado, "ACTIVO") != 0)
    {
        cout << "Solo se puede ingresar pacientes en hospitales Activos" << endl;
    }
    else
    {
        // 1. Si hay camas, ingresa en la lista ORDENADO por historial (Enunciado)
        if (pacientesIngresados.longitud() < maxCamas)
        {
            int pos = 1;
            bool posEncontrada = false;
            int len = pacientesIngresados.longitud();

            while (pos <= len && !posEncontrada)
            {
                if (pacientesIngresados.observar(pos).historialClinico >= p.historialClinico)
                {
                    posEncontrada = true;
                }
                else
                {
                    pos++;
                }
            }
            pacientesIngresados.insertar(pos, p);
            ingresado = true;
        }
        // 2. Si no hay camas, lo mandamos a la cola
        else if (pacientesEnEspera.longitud() < maxColaEspera)
        {
            pacientesEnEspera.encolar(p);
            ingresado = true;
        }
    }

    return ingresado;
}

bool Hospital::bajaPaciente(int idPaciente)
{
    bool eliminado = false;
    int i = 1;
    int lenLista = pacientesIngresados.longitud();

    // 1. Buscar y eliminar de ingresados
    while (i <= lenLista && !eliminado)
    {
        if (pacientesIngresados.observar(i).historialClinico == idPaciente)
        {
            pacientesIngresados.eliminar(i);

            eliminado = true;
        }
        else
        {
            i++;
        }
    }
    // 2. Si hubo baja, entra el más grave de la cola de prioridad
    if (eliminado)
    {
        if (!pacientesEnEspera.esvacia())
        {
            Paciente p = pacientesEnEspera.primero(); // Saca al más grave por defecto
            pacientesEnEspera.desencolar();

            int pos = 1;
            bool posEncontrada = false;
            int long_list = pacientesIngresados.longitud();

            while (pos <= long_list && !posEncontrada)
            {
                if (pacientesIngresados.observar(pos).historialClinico >= p.historialClinico)
                {
                    posEncontrada = true;
                }
                else
                {
                    pos++;
                }
            }
            pacientesIngresados.insertar(pos, p);
        }
    }

    else
    {
        // 3. Buscar para eliminar en la COLA DE PRIORIDAD usando auxiliar
        Cola colaAuxiliar;

        while (!pacientesEnEspera.esvacia())
        {
            Paciente pac_tem = pacientesEnEspera.primero();
            pacientesEnEspera.desencolar();

            if (pac_tem.historialClinico == idPaciente && !eliminado)
            {
                eliminado = true; // Lo marcamos y NO lo metemos en la auxiliar
            }
            else
            {
                colaAuxiliar.encolar(pac_tem); // Guardamos a los demás
            }
        }

        // Restauramos la cola original
        while (!colaAuxiliar.esvacia())
        {
            pacientesEnEspera.encolar(colaAuxiliar.primero());
            colaAuxiliar.desencolar();
        }
    }



    return eliminado;

}

void Hospital::exportarPacientesIngresados(Paciente *ingresados)
{
    int len = pacientesIngresados.longitud();

    // Según el TAD Lista del Tema 4, las posiciones van de 1 a la longitud total
    for (int i = 1; i <= len; i++)
    {
        ingresados[i - 1] = pacientesIngresados.observar(i);
    }
}

void Hospital::exportarPacientesEnEspera(Paciente *enEspera)
{
    Cola colaAuxiliar;
    int i = 0;

    // Vaciamos temporalmente la original mediante desencolar() (Tema 4)
    while (!pacientesEnEspera.esvacia())
    {
        Paciente p = pacientesEnEspera.primero();
        pacientesEnEspera.desencolar();

        enEspera[i] = p; // Copiamos el paciente al array
        colaAuxiliar.encolar(p); // Lo guardamos en la cola auxiliar
        i++;
    }

    // Restauramos la cola original volcando de nuevo los datos
    while (!colaAuxiliar.esvacia())
    {
        pacientesEnEspera.encolar(colaAuxiliar.primero());
        colaAuxiliar.desencolar();
    }
}


bool Hospital::estaActivo()
{
    bool activo = false;
    if (strcmp(estado, "ACTIVO") == 0)
    {
        activo = true;
    }
    return activo;
}

bool Hospital::estaInactivo()
{
    bool inactivo = false;
    if (strcmp(estado, "INACTIVO") == 0)
    {
        inactivo = true;
    }
    return inactivo;
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
    bool cambiado = false;
    if (strcmp(estado, "INACTIVO") == 0 || strcmp(estado, "SIN SANGRE") == 0)
    {
        cout << "El hospital debe de estar activo." << endl;
    }
    else
    {
        strcpy(estado, "INACTIVO");
        cout << "Estado cambiado" << endl;

        // Vaciado CORRECTO usando while
        while (!pacientesIngresados.esvacia())
        {
            pacientesIngresados.eliminarIzq();
        }

        while (!pacientesEnEspera.esvacia())
        {
            pacientesEnEspera.desencolar();
        }
        cambiado = true;
    }
    return cambiado;
}

bool Hospital::faltaSangre()
{
    bool cambiado = false;
    if (strcmp(estado, "ACTIVO") == 0)
    {
        strcpy(estado, "SIN SANGRE");
        cout << "Estado cambiado" << endl;

        // Vaciado CORRECTO usando while
        while (!pacientesEnEspera.esvacia())
        {
            pacientesEnEspera.desencolar();
        }
        cambiado = true;
    }
    return cambiado;
}

void Hospital::mostrarPacientesIngresados()
{
    Paciente pac;
    int len = pacientesIngresados.longitud();

    for (int i = 1; i <= len; i++)
    {
        pac = pacientesIngresados.observar(i);
        cout << "Nombre del paciente: " << pac.nombreCompleto << endl;
        cout << "Historial clínico: " << pac.historialClinico << endl;
        cout << "Tipo de sangre: " << pac.tipoSangre << endl;
        cout << "Gravedad: " << pac.gravedad << endl;
        cout << "Patologia: " << pac.patologia << endl;
        cout << "-----------------------------------" << endl;
    }
}

void Hospital::mostrarPacientesEnEspera()
{
    Cola colaAuxiliar;

    while (!pacientesEnEspera.esvacia())
    {
        Paciente temporal = pacientesEnEspera.primero();
        pacientesEnEspera.desencolar();

        cout << "Nombre del paciente: " << temporal.nombreCompleto << endl;
        cout << "Historial clínico: " << temporal.historialClinico << endl;
        cout << "Tipo de sangre: " << temporal.tipoSangre << endl;
        cout << "Gravedad: " << temporal.gravedad << endl;
        cout << "Patologia: " << temporal.patologia << endl;
        cout << "-----------------------------------" << endl;

        colaAuxiliar.encolar(temporal);
    }

    // Volvemos a meterlos en la original para no destruirla
    while (!colaAuxiliar.esvacia())
    {
        pacientesEnEspera.encolar(colaAuxiliar.primero());
        colaAuxiliar.desencolar();
    }
}

void Hospital::mostrarInformacion()
{
    cout << "--- Hospital: " << nombreHospital << " ---" << endl;
    cout << "ID: " << idHospital << " | Estado: " << estado << endl;
    cout << "Ocupación: " << pacientesIngresados.longitud() << "/" << maxCamas << " camas" << endl;
    cout << "Pacientes en espera: " << pacientesEnEspera.longitud() << endl;
}


Hospital::~Hospital()
{
    //dtor
}

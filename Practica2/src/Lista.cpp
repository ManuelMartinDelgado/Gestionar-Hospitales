#include <Lista.h>




Lista::Lista()
{
    {
        elementos=new Paciente[INCREMENTO];
        if (elementos!=NULL)
        {
            Tama=INCREMENTO;
            n=0;
        }
        else
        {
            Tama=n=-1;
        }
    }
}

Lista::~Lista()
{
    if (elementos!=NULL)
        delete [] elementos;
    elementos=NULL;
    Tama=n=0;
}

void Lista::insertar(int i, Paciente e)
{
    int pos;
    if (n==Tama)
    {
        Paciente *NuevaZona=new Paciente[Tama+INCREMENTO];
        if (NuevaZona!=NULL)
        {
            for (int i=0; i<n; i++)
                NuevaZona[i]=elementos[i];
            Tama+=INCREMENTO;
            delete [] elementos;
            elementos=NuevaZona;
        }
    };

    if (n<Tama)
    {
        for (pos=n-1; pos>=i-1; pos--)
            elementos[pos+1]=elementos[pos]; // Desplazamiento
        elementos[i-1]=e;
        n++;
    }
}
void Lista::modificar(int i, Paciente e)
{
    elementos[i-1]=e;
}
Paciente Lista::observar(int i)
{
    return(elementos[i-1]);
}
bool Lista::esvacia()
{
    return (n == 0);
}

void Lista::eliminar(int i)
{
    while (i<n)
    {
        elementos[i-1]=elementos[i]; // Desplazamiento
        i++;
    }
    n--;
    if (Tama-n>=INCREMENTO && Tama>INCREMENTO)
    {
        Paciente *NuevaZona=new Paciente[Tama-INCREMENTO];
        if (NuevaZona!=NULL)
        {
            Tama-=INCREMENTO;
            for (int i=0; i<Tama; i++)
                NuevaZona[i]=elementos[i];
            delete [] elementos;
            elementos=NuevaZona;
        };
    };
}
int Lista::posicion(Paciente e)
{
    int i=0;
    while (elementos[i].historialClinico==e.historialClinico && i < n)
        i++;
    return (i == n ? -1 : i+1);
}
int Lista::longitud()
{
    return n;
}
Lista::Lista(Paciente e)
{
    elementos=new Paciente[INCREMENTO];
    if (elementos!=NULL)
    {
        Tama=INCREMENTO;
        n=1;
        elementos[0]=e;
    }
    else
    {
        Tama=n=-1;
    }
}
void Lista::anadirIzq(Paciente e)
{
    insertar(1, e);
}
void Lista::anadirDch(Paciente e)
{
    insertar(n+1, e);
}
void Lista::eliminarIzq()
{
    eliminar(1);
}
void Lista::eliminarDch()
{
    eliminar(n);
}
Paciente Lista::observarIzq()
{
    return(observar(1));
}
Paciente Lista::observarDch()
{
    return(observar(n));
}
void Lista::concatenar(Lista l)
{
    int lon = l.longitud();
    for (int i=1; i<=lon; i++)
        insertar(n+1, l.observar(i));
}
bool Lista::pertenece(Paciente e)
{
    return (posicion(e) != -1);
}

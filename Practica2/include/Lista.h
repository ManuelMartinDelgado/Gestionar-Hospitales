#ifndef LISTA_H
#define LISTA_H
#include <iostream>
#include <cstdlib>
#include <cstring>
#define INCREMENTO 4
using namespace std;
typedef char cadena[50];

struct Paciente
    {
        cadena nombreCompleto; // Nombre completo de la persona registrada.
        int historialClinico;
// Identificador númerico único del paciente utilizado para identificar a los
// pacientes.
        char tipoSangre[2];
// Cadena que guarda los valores de la sangre de los usuarios,
// valores posibles: "A"; "AB"; "O".
        int gravedad; // Nivel de gravedad de la patología del paciente (escala de 1 a 5,
// donde 1 indica menor gravedad y 5 mayor gravedad).
        cadena patologia; // Nombre de la enfermedad o problema que presenta el paciente.
    };

class Lista
{
    Paciente *elementos; // elementos de la lista
 int n; // nº de elementos que tiene la lista
 int Tama;

    public:
        Lista(); // constructor de la clase
 ~Lista(); // destructor de la clase
 Lista(Paciente e);
 bool esvacia();
 int longitud();
 void anadirIzq(Paciente e);
 void anadirDch(Paciente e);
 void eliminarIzq();
 void eliminarDch();
 Paciente observarIzq();
 Paciente observarDch();
 void concatenar(Lista l);
 bool pertenece(Paciente e);
 void insertar(int i, Paciente e);
 void eliminar(int i);
 void modificar(int i, Paciente e);
 Paciente observar(int i);
 int posicion(Paciente e);

    protected:

    private:
};

#endif // LISTA_H

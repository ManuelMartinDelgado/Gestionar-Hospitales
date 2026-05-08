#ifndef Cola_H
#define Cola_H
#include <iostream>
#define INCREMENTO 4
#include <Lista.h>

class Cola
{

    Paciente *elementos; //elementos de la Cola
    int inicio, fin;    //principio y fin de la Cola
    int Tama;           //Capacidad de la tabla
    int ne;             //Nº de elementos
public:
    Cola();             // constructor de la clase
    ~Cola();            // destructor de la clase
    void encolar(Paciente e);
    void desencolar();
    bool esvacia();
    Paciente primero() ;
    int longitud();
};







#endif // COLA_H

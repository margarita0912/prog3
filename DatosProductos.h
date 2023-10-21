//
// Created by COTYS on 20/10/2023.
//

#ifndef PROG3_DATOSPRODUCTOS_H
#define PROG3_DATOSPRODUCTOS_H

#include <iostream>

using namespace std;

class DatosProductos {
protected:
    string grupo;
    string codigo;
    char nombre[60];
    int stockTotal;
    int depositos[20];

public:

    DatosProductos();
    DatosProductos(string, string, char[60], int, int[20]);

    void setgrupo(string grupot);
    string getgrupo();
    void setcodigo(string codigot);
    string getcodigo();
    void setnombre(char nombret[60]);
    char* getnombre();
    void setstockTotal(int stockTotalt);
    int getstockTotal();
    void setdepositos(int depositost[20]);
    int* getdepositos();


    void probador();
};


#endif //PROG3_DATOSPRODUCTOS_H

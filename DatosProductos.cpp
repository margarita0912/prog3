#include "DatosProductos.h"
#include <iostream>

using namespace std;


DatosProductos::DatosProductos() {
    grupo="";
    codigo="";
    for(int i=0; i<60; i++){
        nombre[i] = '\0';
    }
    stockTotal=0;
    for(int i=0; i<20; i++) {
        depositos[i] = 0;
    }
}

DatosProductos::DatosProductos(string grupot, string codigot, char nombret[60], int stockTotalt, int depositost[20]) {
    grupo=grupot;
    codigo=codigot;
    for(int i=0; i<60; i++){
        nombre[i] = nombret[i];
    }
    stockTotal=stockTotalt;
    for(int i=0; i<20; i++){
        depositos[i] = depositost[i];
    }

}

void DatosProductos::setgrupo(string grupot) {
    grupo = grupot;
}

string DatosProductos::getgrupo(){
    return grupo;
}

void DatosProductos::setcodigo(string codigot) {
    codigo = codigot;
}

string DatosProductos::getcodigo() {
    return codigo;
}

void DatosProductos::setnombre(char nombret[60]) {
    for(int i=0; i<60; i++){
        nombre[i] = nombret[i];
    }
}

char* DatosProductos::getnombre(){
    return nombre;
}

void DatosProductos::setstockTotal(int stockTotalt) {
    stockTotal = stockTotalt;
}

int DatosProductos::getstockTotal(){
    return stockTotal;
}

void DatosProductos::setdepositos(int depositost[20]) {
    for(int i=0; i<20; i++){
        depositos[i] = depositost[i];
    }
}

int* DatosProductos::getdepositos(){
    return depositos;
}

void DatosProductos::probador() {
    cout << "GRUPO: " << grupo << endl;
    cout << "CODIGO: " << codigo << endl;
    cout << "NOMBRE: " << nombre << endl;
    cout << "Stock total: " << stockTotal << endl;
    cout << "DEPOSITO 1: " << depositos[0] << endl;

}

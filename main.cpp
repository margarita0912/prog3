#include <iostream>
#include "DatosProductos.h"
#include "ArbolBinario.h"
#include <fstream>
#include <iomanip>
#include "string.h"
#include <stdexcept>
#include <string>
#include <sstream>
#include <limits>
#include <cstring>
#include "Lista.h"
#include <vector>
using namespace std;


void quickSort(DatosProductos *base_de_datos[400], int inicio, int fin){

    int medio=(inicio+fin)/2;

    int pivot = base_de_datos[medio]->getstockTotal();
    int i=inicio, j=fin;
    DatosProductos* aux;
    do{
        while(base_de_datos[i]->getstockTotal()<pivot) i++;
        while(base_de_datos[j]->getstockTotal()>pivot) j--;

        if(i<=j){
            aux = base_de_datos[i];
            base_de_datos[i] = base_de_datos[j];
            base_de_datos[j] = aux;
            i++;
            j--;

        }
    }while(i<=j);

    if(j>inicio) quickSort(base_de_datos, inicio, j);
    if(i<fin) quickSort(base_de_datos, i, fin);
}


void leerArchivo(DatosProductos* base_de_datos[400], int &ubicProducto, int &stockGeneral, int &cantdepositos) {
    ifstream archivoProductos("Inventariado Fisico.csv");
    string linea, dato, primeraLinea;
    stringstream s;

    getline(archivoProductos, primeraLinea);

    int numColumnas = 0;
    s.str(primeraLinea);
    while (getline(s, dato, ',')) {
        numColumnas++;
    }
    s.clear();  // Limpiar el stringstream
    cantdepositos=numColumnas-3;

    while (getline(archivoProductos, linea, '\n')) {

        s.str(linea);

        int cont = 0;
        int depositos[20]={0};

        while (getline(s, dato, ',')) {
           if (dato.front() == '"' && dato.back() == '"') {
                dato = dato.substr(1, dato.length() - 2);
           }
           switch (cont) {
                case 0: {

                    if(dato.empty()){
                        dato=base_de_datos[ubicProducto-1]->getgrupo();
                    }
                    base_de_datos[ubicProducto]->setgrupo(dato);
                    break;
                }
                case 1: {

                    base_de_datos[ubicProducto]->setcodigo(dato);
                    break;
                }
                case 2: {
                    string nombre = dato;
                    int len = nombre.length();
                    char nombreCharArray[40] = {0}; // Crear un arreglo de caracteres temporal
                    for (int i = 0; i < len; i++) {
                        nombreCharArray[i] = nombre[i]; // Copiar cada carácter a nombreCharArray
                    }
                    // Usar la función setnombre para establecer el nombre en la instancia de DatosProductos
                    base_de_datos[ubicProducto]->setnombre(nombreCharArray);
                    break;
                }
                case 3: {
                    if (dato.front() == '"' && dato.back() == '"') {
                        dato = dato.substr(1, dato.length() - 2);
                    }
                    int total = 0;
                    // Leer los valores de depósitos y almacenarlos en el arreglo temporal
                    for(int i=0; i<cantdepositos; i++){
                        if(dato.empty()){
                            depositos[i]=0;
                            total += depositos[i];
                        } else {
                            depositos[i] = stoi(dato); // Convierte el valor a entero
                            total = total + depositos[i];
                        }
                        getline(s, dato, ',');
                    }
                    base_de_datos[ubicProducto]->setdepositos(depositos);
                    base_de_datos[ubicProducto]->setstockTotal(total);
                    stockGeneral=stockGeneral+total;
                    break;
                }
           }
           cont++;
        }
        s.clear();
        ubicProducto++;      //en este while me voy elevando a uno en la ubic del cliente
    }
    archivoProductos.close();
    quickSort(base_de_datos, 0, ubicProducto);
}


void crearArbol(DatosProductos* base_de_datos[400], ArbolBinario<DatosProductos*> &arbol, int ubicProducto){//modificar para elegir un pivote adecuado
    int medio = ubicProducto / 2;
    int cuarto_izquierda = ubicProducto / 4;
    int cuarto_derecha = 3 * ubicProducto / 4;

    arbol.put(base_de_datos[medio]);
    arbol.put(base_de_datos[cuarto_izquierda]);
    arbol.put(base_de_datos[cuarto_derecha]);

    for(int i=1; i<ubicProducto+1; i++){
        if (i!=medio && i!=cuarto_derecha && i!=cuarto_izquierda){
            arbol.put(base_de_datos[i]);
        }

    }

}

void arbolPorDeposito(DatosProductos* base_de_datos[400], int ubicProducto, Lista<ArbolBinario<DatosProductos*>>& porDeposito, int cantDepositos) {
    for (int i = 1; i < cantDepositos+1; ++i) {
        ArbolBinario<DatosProductos*> arbolDeposito;
        for (int j = 0; j < ubicProducto; ++j) {
            arbolDeposito.put(base_de_datos[j]);
        }
        porDeposito.insertarUltimo(arbolDeposito);
    }
}

void minStock(ArbolBinario<DatosProductos*> &arbol, int n){
    bool band=false;
    arbol.minStock(n,band);
    if(!band){
        cout << "No hay productos con su stock por debajo del valor ingresado" << endl;
    }
}

void maxStock(ArbolBinario<DatosProductos*> &arbol, int n){
    bool band = false;
    arbol.maxStock(n, band);
    if(!band){
        cout << "No hay productos con stock mayor al numero ingresado." << endl;
    }
}

void stock(DatosProductos* base_de_datos[400], int ubicProducto, int i) {
    cout << "-----------------------------------------------------" << endl;
    cout << "STOCK TOTAL DEL PRODUCTO: " << base_de_datos[i]->getstockTotal() << endl;
    cout << "-----------------------------------------------------" << endl;
}

void stockMinPorDep(Lista<ArbolBinario<DatosProductos*>>& porDeposito, int n, int deposito){
    bool band=false;
    ArbolBinario<DatosProductos*> arbolDeposito = porDeposito.getDato(deposito-1);
    arbolDeposito.buscarProductosStockMenor(n, band, deposito-1);

    if(!band){
        cout<<"No existen productos por debajo de ese valor en stock"<<endl;
    }
}

void stockDeArtEnDep(DatosProductos* base_de_datos[400], int ubicProducto, int dep, int k){
    cout << "-----------------------------------------------------" << endl;
    cout << "STOCK DEL PRODUCTO EN DEPOSITO "<<dep<<": " << base_de_datos[k]->getdepositos()[dep-1] << endl;
    cout << "-----------------------------------------------------" << endl;
}


int main(int argc, char **argv){

    DatosProductos *base_de_datos[400];
    ArbolBinario<DatosProductos*> arbol;
    Lista<ArbolBinario<DatosProductos*>>porDeposito;
    int n, deposito=-1, ubicProducto=0, stockGeneral=0, cantDep;

    for(int i = 0; i<400; i++){
        base_de_datos[i] = new DatosProductos();
    }

    leerArchivo(base_de_datos, ubicProducto, stockGeneral, cantDep);

    crearArbol(base_de_datos, arbol, ubicProducto);
    arbolPorDeposito(base_de_datos, ubicProducto, porDeposito, cantDep);

    for (int i=0; i<argc; i++){
        if (strcmp(argv[i], "-tot_art_dif")==0){
            cout << "El total de articulos diferentes es: ";
            cout << ubicProducto << endl;
            cout << endl << "" << endl;
            break;
        }
        if (strcmp(argv[i], "-total_art")==0){
            cout << "La cantidad total de articulos es: ";
            cout << stockGeneral << endl;
            cout << endl << "" << endl;
            break;
        }
        if (strcmp(argv[i], "-min_stock")==0){
            try{
                n = stoi(argv[i+1]);
                if(n < 0){
                    throw std::invalid_argument("N menor a 0");
                }
            }catch(std::exception &e){
                cerr<<"Leer manual de uso"<<endl;
                return 1;
            }
            try{
                if(stoi(argv[i+2]) <= 0 || stoi(argv[i+2]) > cantDep){
                    throw std::invalid_argument("Leer manual de uso, o deposito no existe");
                }
                deposito = stoi(argv[i+2]);
            }catch(std::invalid_argument &e){
                cout<<e.what()<<endl;
                cout<<"Ejecutando sin deposito"<<endl;
            }
            if(deposito < 0){
                cout << "El listado de articulos con cantidad menor o igual a " << n << " de stock es: " << endl;
                minStock(arbol, n);
                cout << endl << "" << endl;
            }else{
                cout << "El listado de articulos con cantidad menor o igual a " << n << " de stock en el deposito "<<deposito<<" es: " << endl;
                stockMinPorDep(porDeposito, n, deposito);
            }
            break;
        }

        if (strcmp(argv[i], "-stock")==0){
            bool band=false;
            int a;
            cout << endl << "" << endl;
            try {
                for (int k = 0; k < ubicProducto; k++) {
                    if (strcmp(argv[i + 1],base_de_datos[k]->getnombre())==0) {
                        a = k;
                        band = true;
                        break;
                    }
                }
                if(!band){
                    cout<<"El producto no existe"<<endl;
                }
            }catch(std::exception &e){
                cerr<<"Leer manual de uso"<<endl;
                return 1;
            }
            try{
                if(stoi(argv[i+2]) <= 0 || stoi(argv[i+2]) > cantDep){
                    throw std::invalid_argument("Leer manual de uso, o deposito no existe");
                }
                deposito = stoi(argv[i+2]);
            }catch(std::invalid_argument &e){
                cout<<e.what()<<endl;
                cout<<"Ejecutando sin deposito"<<endl;
            }
            if(deposito < 0 && band){
                stock(base_de_datos, ubicProducto, a);
                cout << endl << "" << endl;
            }else if (deposito<cantDep && band){
                stockDeArtEnDep(base_de_datos, ubicProducto, deposito, a);
            }
            break;
        }

        if (strcmp(argv[i], "-max_stock")==0){
            try{
                n = stoi(argv[i+1]);
                if(n < 0){
                    throw std::invalid_argument("N menor a 0");
                }
            }catch(std::exception &e){
                cerr<<"Leer manual de uso"<<endl;
                return 1;
            }
            cout << "El listado de articulos con cantidad mayor o igual a " << n << " de stock es: " << endl;
            maxStock(arbol, n);
            cout << endl << "" << endl;
            break;
        }
    }
}

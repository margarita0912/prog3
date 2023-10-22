#include <iostream>
#include "DatosProductos.h"
#include "ArbolBinario.h"
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <sstream>
#include <limits>
#include <cstring>
using namespace std;

DatosProductos base_de_datos[400];
ArbolBinario<int> arbol;

int ubicProducto=0;
int stockGeneral=0;
int cantdepositos=0;

void leerArchivo() {
    ifstream archivoProductos("inventarioo.txt");
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
                        dato=base_de_datos[ubicProducto-1].getgrupo();
                    }
                        base_de_datos[ubicProducto].setgrupo(dato);



                    break;
                }
                case 1: {
                    base_de_datos[ubicProducto].setcodigo(dato);
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
                    base_de_datos[ubicProducto].setnombre(nombreCharArray);
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

                    base_de_datos[ubicProducto].setdepositos(depositos);
                    base_de_datos[ubicProducto].setstockTotal(total);
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

}

void crearArbol(){
    for(int i=0; i<ubicProducto; i++){
        arbol.put(base_de_datos[i].getstockTotal());
    }
    arbol.print();
}

void minStock(int n){
    for(int i=0; i<ubicProducto; i++) {
        if (base_de_datos[i].getstockTotal() <= n) {
            base_de_datos[i].probador();
            cout<<"-----------------------------------------------------"<<endl;
        }
    }
}

void maxStock(int n){
    for(int i=0; i<ubicProducto; i++) {
        if (base_de_datos[i].getstockTotal() >= n) {
            base_de_datos[i].probador();
            cout<<"-----------------------------------------------------"<<endl;
        }
    }
}

void stock() {
    char argumento[60];
    char p;
    int i = 0;

    cout << "Ingrese el producto a buscar, finalice con un punto: ";
    cin >> ws; // Elimina espacios en blanco iniciales si los hubiera.
    while (i < 59 && (cin.get(p) && p != '.' && p != '\n')) {
        argumento[i] = p;
        i++;
    }
    argumento[i] = '\0'; // Agrega el carácter nulo al final de la cadena.

    for (int j = 0; j < ubicProducto; j++) {
        if (strcmp(base_de_datos[j].getnombre(), argumento) == 0) {
            cout << "-----------------------------------------------------" << endl;
            cout << "STOCK TOTAL DEL PRODUCTO: " << base_de_datos[j].getstockTotal() << endl;
            cout << "-----------------------------------------------------" << endl;
        }
    }
}


int main() {

    int opcswitch, n, deposito;
    string opc;


    leerArchivo();

    crearArbol();

    while(opc!="salir") {
        cout << "INGRESE POR TECLADO LO QUE QUIERE REALIZAR" << endl;
        cout << "'total_art_dif' Cantidad total de articulos diferentes." << endl
             << "'total_art' Cantidad total de articulos" << endl
             << "'min_stock' Listado de articulos con cantidad n o menos de stock." << endl
             << "'min_stock_deposito' Listado de articulos con cantidad n o menos de stock segun un deposito" << endl
             << "'stock' El stock total del articulo ingresado como argumento." << endl
             << "'stock_deposito' El stock del articulo en un deposito." << endl
             << "'max_stock' Listado de aquellos articulos cuyo stock es igual o supera el numero n." << endl
             << "'salir' Salir del programa" << endl;
        cout << "OPCION: ";
        cin >> opc;

        while (opc != "total_art_dif" && opc != "total_art" && opc != "min_stock" && opc != "min_stock_deposito" &&
               opc != "stock" && opc != "stock_deposito" && opc != "max_stock" && opc != "salir") {
            cout << "La opcion ingresada no es valida, reingrese la opcion: ";
            cin >> opc;
        }

        if (opc == "total_art_dif") {
            opcswitch = 1;
        }
        if (opc == "total_art") {
            opcswitch = 2;
        }
        if (opc == "min_stock") {
            opcswitch = 3;
        }
        if (opc == "min_stock_deposito") {
            opcswitch = 4;
        }
        if (opc == "stock") {
            opcswitch = 5;
        }
        if (opc == "stock_deposito") {
            opcswitch = 6;
        }
        if (opc == "max_stock") {
            opcswitch = 7;
        }

        switch (opcswitch) {
            case 1:
                cout<<"El total de articulos diferentes es: ";
                cout<<ubicProducto<<endl;
                cout<<endl<<""<<endl;
                break;
            case 2:
                cout<< "La cantidad total de articulos es: ";
                cout<<stockGeneral<<endl;
                cout<<endl<<""<<endl;
                break;
            case 3:
                cout<< "ingrese la cantidad de stock a analizar menor o igual: ";
                cin >> n;
                cout<<"El listado de articulos con cantidad menor o igual a "<< n << " de stock es: "<<endl;
                cout<<endl;
                minStock(n);
                cout<<endl<<""<<endl;
                break;
            case 4:
                cout<< "ingrese la cantidad minima de stock: ";
                cin >> n;
                cout<< "ingrese el deposito que quiere ver: ";
                cin >> deposito;
                cout<<"El listado de articulos en el deposito "<< deposito<< " con cantidad menor o igual a "<< n << " de stock es: ";

                cout<<endl<<""<<endl;
                break;
            case 5:
                stock();
                cout<<endl<<""<<endl;
                break;
            case 6:

                cout<< "ingrese el deposito que quiere ver: ";
                cin >> deposito;
                cout << "el stock del articulo en el deposito "<< deposito << " es: ";

                cout<<endl<<""<<endl;
                break;
            case 7:
                cout<< "ingrese la cantidad de stock a analizar mayor o igual: ";
                cin >> n;
                cout<<"El listado de articulos con cantidad mayor o igual a "<< n << " de stock es: "<<endl;
                maxStock(n);
                cout<<endl<<""<<endl;
                break;
        }
    }
}

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
#include "Lista.h"
#include <vector>
using namespace std;


void quickSort(DatosProductos *base_de_datos[400], int inicio, int fin){ //pasar por parametro incio=0 y fin=ubicProductos;

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
    for(int i=1; i<ubicProducto+1; i++){
        arbol.put(base_de_datos[i]);
    }
  // arbol.print();
}

void arbolPorDeposito(DatosProductos* base_de_datos[400], int ubicProducto, Lista<ArbolBinario<DatosProductos*>>& porDeposito, int cantDepositos) {
    for (int i = 1; i < cantDepositos+1; ++i) { //ver ese mas 1
        ArbolBinario<DatosProductos*> arbolDeposito;
        for (int j = 0; j < ubicProducto; ++j) {
            arbolDeposito.put(base_de_datos[j]);
        }
        porDeposito.insertarUltimo(arbolDeposito);
    }
}

void minStock(ArbolBinario<DatosProductos*> &arbol, DatosProductos* base_de_datos[400], int n, int ubicProducto=0){
    bool band=false;
    /*cout << "ingrese la cantidad de stock a analizar menor o igual: ";
    cin >> n;*/

    for(int i=0; i<ubicProducto+1; i++) {
        if (base_de_datos[i]->getstockTotal() <= n) {
            base_de_datos[i]->probador();
            cout<<"-----------------------------------------------------"<<endl;
            band = true;
        }
    }
    if(!band){
        cout << "El stock ingresado no es valido." << endl;
    }
}

void maxStock(DatosProductos* base_de_datos[400], ArbolBinario<DatosProductos*> &arbol, int n, int ubicProducto=0){
    bool band = false;
    for(int i=0; i<ubicProducto+1; i++) {
        if (base_de_datos[i]->getstockTotal() >= n) {
            base_de_datos[i]->probador();
            cout<<"-----------------------------------------------------"<<endl;
            band = true;

        }
    }

    if(!band){
        cout << "El stock ingresado no es valido." << endl;
    }
}

void stock(DatosProductos* base_de_datos[400], int ubicProducto) {
    char argumento[60];
    char p;
    int i = 0;
    bool coincidencia=false;

    cout << "Ingrese el producto a buscar, finalice con un punto: ";
    cin >> ws; // Elimina espacios en blanco iniciales si los hubiera.
    while (i < 59 && (cin.get(p) && p != '.' && p != '\n')) {
        argumento[i] = p;
        i++;
    }
    argumento[i] = '\0'; // Agrega el carácter nulo al final de la cadena.

    for (int j = 0; j < ubicProducto+1; j++) {
        if (strcmp(base_de_datos[j]->getnombre(), argumento) == 0) {
            cout << "-----------------------------------------------------" << endl;
            cout << "STOCK TOTAL DEL PRODUCTO: " << base_de_datos[j]->getstockTotal() << endl;
            cout << "-----------------------------------------------------" << endl;
            coincidencia=true;
        }
    }
    if (!coincidencia){
        cout<<"El articulo ingresado no existe en la base de datos"<<endl;
    }
}

void stockMinPorDep(Lista<ArbolBinario<DatosProductos*>>& porDeposito){
    int deposito, n;
    cout << "ingrese la cantidad minima de stock: ";
    cin >> n;
    cout << "ingrese el deposito que quiere ver: ";
    cin >> deposito;
    ArbolBinario<DatosProductos*> arbolDeposito = porDeposito.getDato(deposito-1);
    cout << "Productos en el depósito " << deposito << " con stock menor que " << n << ":" << endl; //modificar esta impresion
    arbolDeposito.buscarProductosStockMenor(n);
}

void stockDeArtEnDep(DatosProductos* base_de_datos[400], int ubicProducto, int dep){
    char argumento[60];
    char p;
    int i = 0;
    bool coincidencia=false;

    cout << "Ingrese el producto a buscar, finalice con un punto: ";
    cin >> ws; // Elimina espacios en blanco iniciales si los hubiera.
    while (i < 59 && (cin.get(p) && p != '.' && p != '\n')) {
        argumento[i] = p;
        i++;
    }
    argumento[i] = '\0'; // Agrega el carácter nulo al final de la cadena.

    for (int j = 0; j < ubicProducto+1; j++) {
        if (strcmp(base_de_datos[j]->getnombre(), argumento) == 0) {
            cout << "-----------------------------------------------------" << endl;
            cout << "STOCK DEL PRODUCTO EN DEPOSITO "<<dep<<": " << base_de_datos[j]->getdepositos()[dep-1] << endl;
            cout << "-----------------------------------------------------" << endl;
            coincidencia=true;
        }
    }

    if (!coincidencia){
        cout<<"El articulo ingresado no se encuentra en la base de datos"<<endl;
    }
}

/*void exploreCSV(string fileName, int lines){

    fstream fin;
    fin.open("./" + fileName, ios::in);

    vector<string> row;
    string line, word;
    int confirmed=0;
    int total=-1;

    while (getline(fin, line)){
        total++;
        row.clear();
        stringstream s(line);
        while(getline(s, word, ',')){
            if(word.size()>0){
                word = word.substr(1, word.size()-2);
            }else{
                word = "NA";
            }
            row.push_back(word);
        }
    }
}

void exploreHeaders (string fileName){
    fstream fin;
    fin.open("../cmake-build-debug/" + fileName, ios::in);

    string header, headers;
    getline(fin, headers);
    stringstream s(headers);
    while (getline(s, header, ',')) {
        cout<< header << endl;
    }
}*/

int main(int argc, char **argv){

    DatosProductos *base_de_datos[400];
    ArbolBinario<DatosProductos*> arbol;
    Lista<ArbolBinario<DatosProductos*>>porDeposito;
    int opcswitch, n, deposito;
    string opc;
    int ubicProducto=0;
    int stockGeneral=0;
    int cantDep;

    for(int i = 0; i<400; i++){
        base_de_datos[i] = new DatosProductos();
    }

    leerArchivo(base_de_datos, ubicProducto, stockGeneral, cantDep);


    crearArbol(base_de_datos, arbol, ubicProducto);
    arbolPorDeposito(base_de_datos, ubicProducto, porDeposito, cantDep);


   // cout<< "cantidad de argumentos: "<<argc<<endl;
    for (int i=0; i<argc; i++){
       // cout<< "ARGUMENTO "<< i << ": "<<argv[i]<<endl;
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
        if (strcmp(argv[i], "-min_stock")==0){ //hacer try catch que lea si hay argumentos despues y cuantos y en base a eso decida que hacer (verlo en el proy de juan)
            cout << "ingrese la cantidad de stock a analizar menor o igual: ";
            cin >> n;
            cout << "El listado de articulos con cantidad menor o igual a " << n << " de stock es: " << endl;
            cout << endl;
            minStock(arbol, base_de_datos, n, ubicProducto);
            cout << endl << "" << endl;
            break;
        }
        if (strcmp(argv[i], "-min_stock_deposito")==0){
            stockMinPorDep(porDeposito);
            cout << endl << "" << endl;
            break;
        }
        if (strcmp(argv[i], "-stock")==0){
            stock(base_de_datos, ubicProducto);
            cout << endl << "" << endl;
            break;
        }
        if (strcmp(argv[i], "-stock_deposito")==0){
            cout << "ingrese el deposito que quiere ver: ";
            cin >> deposito;
            stockDeArtEnDep(base_de_datos, ubicProducto, deposito);
            cout << endl << "" << endl;
            break;
        }
        if (strcmp(argv[i], "-max_stock")==0){
            cout << "ingrese la cantidad de stock a analizar mayor o igual: ";
            cin >> n;
            cout << "El listado de articulos con cantidad mayor o igual a " << n << " de stock es: " << endl;
            maxStock(base_de_datos, arbol, n, ubicProducto);
            cout << endl << "" << endl;
            break;
        }
    }

   /* while (opc != "salir") {
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
                cout << "El total de articulos diferentes es: ";
                cout << ubicProducto << endl;
                cout << endl << "" << endl;
                break;
            case 2:
                cout << "La cantidad total de articulos es: ";
                cout << stockGeneral << endl;
                cout << endl << "" << endl;
                break;
            case 3:
                cout << "ingrese la cantidad de stock a analizar menor o igual: ";
                cin >> n;
                cout << "El listado de articulos con cantidad menor o igual a " << n << " de stock es: " << endl;
                cout << endl;
                minStock(arbol, base_de_datos, n, ubicProducto);
                cout << endl << "" << endl;
                break;
            case 4:
                stockMinPorDep(porDeposito);
                cout << endl << "" << endl;
                break;
            case 5:
                stock(base_de_datos, ubicProducto);
                cout << endl << "" << endl;
                break;
            case 6:

                cout << "ingrese el deposito que quiere ver: ";
                cin >> deposito;
                stockDeArtEnDep(base_de_datos, ubicProducto, deposito);
                cout << endl << "" << endl;
                break;
            case 7:
                cout << "ingrese la cantidad de stock a analizar mayor o igual: ";
                cin >> n;
                cout << "El listado de articulos con cantidad mayor o igual a " << n << " de stock es: " << endl;
                maxStock(base_de_datos, arbol, n, ubicProducto);
                cout << endl << "" << endl;
                break;
        }
    }*/
}

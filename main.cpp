#include <iostream>
#include "Productos.cpp"

using namespace std;

int main() {
    int opcswitch, n, deposito;
    string opc;
    Productos archivoProductos;
    vector<Productos::Producto> productos; // Declare un vector para almacenar los productos
    archivoProductos.leerArchivo(); // Cargar los productos desde el archivo
    productos = archivoProductos.obtenerProductos();
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
                cout<<archivoProductos.total_art_dif();
                cout<<endl<<""<<endl;
                break;
            case 2:
                cout<< "La cantidad total de articulos es: ";
                archivoProductos.total_art();
                cout<<endl<<""<<endl;
                break;
            case 3:
                cout<< "ingrese la cantidad de stock a analizar menor o igual: ";
                cin >> n;
                cout<<"El listado de articulos con cantidad menor o igual a "<< n << " de stock es: ";

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

                cout << "el stock del articulo es: ";

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
                cout<<"El listado de articulos con cantidad mayor o igual a "<< n << " de stock es: ";

                cout<<endl<<""<<endl;
                break;
        }
    }
}

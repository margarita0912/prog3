#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "lista.h"
using namespace std;

class Productos {

public:
    Lista<string>clasProductos;
    struct depositos {
        string nombre;
        int cantidad;
    };

    struct Producto {
        string grupo;
        string codigo;
        string nombre;
        vector<depositos> deposito;
        int stockTotal;
    };

    vector<Producto> productos;

    int partition(vector<Producto>& arr, int low, int high) {
        int pivot = productos[high].stockTotal;
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (productos[j].stockTotal > pivot) {
                i++;
                swap(productos[i], productos[j]);
            }
        }

        swap(productos[i + 1], productos[high]);
        return (i + 1);
    }

    // Función Quicksort
    void quicksort(vector<Producto>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(productos, low, high);

            quicksort(productos, low, pi - 1);
            quicksort(productos, pi + 1, high);
        }
    }

    void leerArchivo() {
        ifstream archivo("inventario1.txt");
        string linea;

        getline(archivo, linea);

        while (getline(archivo, linea)) {
            Producto producto;
            stringstream ss(linea);

            getline(ss, producto.grupo, ';');
            getline(ss, producto.codigo, ';');
            getline(ss, producto.nombre, ';');

            string depositoInfo;
            while (getline(ss, depositoInfo, ';')) {
                stringstream depositoStream(depositoInfo);
                depositos deposito;
                getline(depositoStream, deposito.nombre, ';');
                depositoStream >> deposito.cantidad;
                producto.deposito.push_back(deposito);
                producto.stockTotal += deposito.cantidad;
            }

            productos.push_back(producto);

        }
        quicksort(productos, 0, productos.size() - 1);
    }

    vector<Producto> obtenerProductos() {
        return productos;
    }

    int total_art_dif() {
        return productos.size();
    }

    int total_art(){
        int total = 0;
        size_t i = 0;

        while (i < productos.size()) {
            total += productos[i].stockTotal;
            i++;
        }

        return total;
    }

    void min_stock(){

    }
};

#endif // PRODUCTOS_H
//
// Created by COTYS on 17/8/2023.
//

#ifndef EJEMPLO_NODO_H
#define EJEMPLO_NODO_H


template <class T> class Nodo { //creamos la clase nodo
private:
    T dato;
    Nodo<T> *siguiente;
public:
    T getDato(){
        return dato;
    }

    void setDato(T d){
        dato=d;
    }
    Nodo<T> *getSiguiente(){
        return siguiente;
    }

    void setSiguiente (Nodo<T> *s) {
        this -> siguiente=s;  //puntero que señala a la misma clase en si
    }

};


#endif //EJEMPLO_NODO_H

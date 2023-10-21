#ifndef U05_ARBOL_ARBOL_ARBOLBINARIO_H_
#define U05_ARBOL_ARBOL_ARBOLBINARIO_H_
#include <iostream>
#include "NodoArbol.h"

using namespace std;

template <class T> class ArbolBinario {
protected:
    NodoArbol<T> *root;
private:
    T search(T data, NodoArbol<T> *r);
    void buscarMenores(T data, NodoArbol<T> *r );
    NodoArbol<T> *put(T data, NodoArbol<T> *r);
    NodoArbol<T> *remove(T data, NodoArbol<T> *r);
    void preorder (NodoArbol<T> *r);
    void inorder (NodoArbol<T> *r);
    void postorder (NodoArbol<T> *r);
    void print(NodoArbol<T> *node, string indent);

public:
    ArbolBinario();

    void put(T dato);

    T search(T dato);
    void buscarMenores(T dato);

    void remove(T dato);

    void preorder();

    void inorder();

    void postorder();

    ~ArbolBinario();

    bool esVacio();

    void print();


};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
template <class T> ArbolBinario<T>::ArbolBinario() {
    root = nullptr;
}

/**
 * Destructor del Arbol
 */
template <class T> ArbolBinario<T>::~ArbolBinario() {}

/**
 * Busca un dato en el árbol. Si no esta el dato en el árbol
 * tira una excepción
 * @param clave Valor a buscar
 * @return el valor buscado
 */
template <class T> T ArbolBinario<T>::search(T dato) {
    return search(dato, root);
}

template <class T> T ArbolBinario<T>::search(T data, NodoArbol<T> *r) { //buscamos un arbol, pero no sabemos bien que tiene, solo que tiene hijos a la derecha e izquierda
    if(r==nullptr){ //condicion base
        encontrado(false, data);
        throw 404;
    }


    if(r->getData() > data){ //si la raiz es mayor al dato que busco, buscamos por la izq
        return search(data, r->getLeft());
    } else { //si la raiz es menor al dato que busco, buscamos por la der
        return search(data, r->getRight());
    }

}

template <class T> void ArbolBinario<T>::buscarMenores(T dato) {
    return buscarMenores(dato, root);
}

template <class T> void ArbolBinario<T>::buscarMenores(T data, NodoArbol<T> *r) { //buscamos un arbol, pero no sabemos bien que tiene, solo que tiene hijos a la derecha e izquierda
    if(r==nullptr){ //condicion base
        encontrado(false, data);
        throw 404;
    }

    if(r->getData() > data){ //si la raiz es mayor al dato que busco, buscamos por la izq
        return buscarMenores(data, r->getLeft());
    } else { //si la raiz es menor al dato que busco, buscamos por la der
        return buscarMenores(data, r->getRight());
    }

}




/**
 * Agrega un dato al árbol
 * @param clave Clave para agregar el dato
 * @param dato Dato a agregar
 */
template <class T> void ArbolBinario<T>::put(T dato) {
    root = put(dato, root);
}

template <class T> NodoArbol<T> *ArbolBinario<T>::put(T data, NodoArbol<T> *r) {
    if(r==nullptr){
        return new NodoArbol<T>(data); //creamos nuevo nodo porque esta vacio y retornamos el dato
    }

    if(r->getData() >= data){
        r->setLeft(put(data, r->getLeft()));
    } else {
        r->setRight(put(data, r->getRight()));
    }

    return r;
}

/**
 * Elimina un dato del árbol
 * @param clave Clave para identificar el nodo a borrar
 */
template <class T> void ArbolBinario<T>::remove(T dato) {
    root= remove(dato, root);
}

template <class T> NodoArbol<T> *ArbolBinario<T>::remove(T data, NodoArbol<T> *r) {
    NodoArbol<T> *aux;

    if(r==nullptr){
        throw 404;
    }

    if(r->getData()==data){
        delete r;
        return nullptr;
    } else {
        if(r->getLeft() != nullptr && r->getRight() == nullptr){
            aux = r->getLeft();
            delete r;
            return aux;
        } else {
            if(r->getLeft() == nullptr && r->getRight() != nullptr) {
                aux = r->getRight();
                delete r;
                return aux;
            } else {
                if(r->getLeft() != nullptr && r->getRight() != nullptr){
                    if(r->getLeft()->getRight() != nullptr){
                        //buscamos el valor maximo
                        bool found;
                        aux = findMaxAndRemove(r->getLeft(), &found);
                        aux->setRight(r->getRight());
                        aux->setLeft(r->getLeft());
                    } else {
                        aux = r->getLeft();
                        r->getLeft()->setRight(r->getRight());
                    }
                    delete r;
                    return aux;
                } else {
                    if(r->getData()>data){
                        r->setLeft(remove(data, r->getLeft()));
                    } else {
                        r->setRight(remove(data, r->getRight()));
                    }
                }
            }
        }
    }
}



/**
 * Informa si un árbol esta vacío
 * @return
 */
template <class T> bool ArbolBinario<T>::esVacio() {
    return root == nullptr;
}

/**
 * Recorre un árbol en preorden
 */
template <class T> void ArbolBinario<T>::preorder() {
    preorder(root);

}

template <class T> void ArbolBinario<T>::preorder(NodoArbol<T> *r) {
    if (r==nullptr){
        return;
    }
    cout<<r->getData()<<endl;
    preorder(r->getLeft());
    preorder(r->getRight());

}

/**
 * Recorre un árbol en orden
 */
template <class T> void ArbolBinario<T>::inorder() {
    inorder(root);
}


template <class T> void ArbolBinario<T>::inorder(NodoArbol<T> *r) {
    if (r==nullptr){
        return;
    }
    inorder (r->getLeft());
    cout<<r->getData()<<endl;
    inorder(r->getRight());
}

/**
 * Recorre un árbol en postorden
 */
template <class T> void ArbolBinario<T>::postorder() {
    postorder(root);
}

template <class T> void ArbolBinario<T>::postorder(NodoArbol<T> *r) {
    if (r==nullptr){
        return;
    }
    inorder (r->getLeft());
    inorder (r->getRight());
    cout<<r->getData()<<endl;
}

/**
 * Muestra un árbol por consola
 */
template <class T>
void ArbolBinario<T>::print() {
    print(root, "");
}

template <class T>
void ArbolBinario<T>::print(NodoArbol<T> *node, string indent) {
    if (root != NULL)
        root->print(false, "");
}



#endif // U05_ARBOL_ARBOL_ARBOLBINARIO_H_
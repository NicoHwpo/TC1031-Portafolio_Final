#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Registro.h"
#include "DLinkedList.h"

class Bitacora {

  private:
    //std::vector<Registro> listaRegistros;
    DLinkedList<Registro> listaRegistros;
    
    int elementos;

  public:
    std::vector<int> lista;
    //Constructor, destructor y funcion print
    Bitacora();
    Bitacora(std::string fileName);
    void print();
    void ordenaIntercambio(std::vector<int> &array, int &ord_swaps, int &ord_compara);

    void printBus(int a, int b);
    void printOrd();
    // Ordenamiento: bubleSort, QuickSortRecursive, QuickSortStack
    void bubbleSort();
    void print(int a, int b);
    void swap(Registro *a, Registro *b);

    template <class T>
    void _quickSortRecursive(DLLNode<T> *l, DLLNode<T> *h);
    
    void quickSortRecursive();

    template <class T>
    DLLNode<T>* partition(DLLNode<T> *l, DLLNode<T> *h);

    template<class T>
    DLLNode<T>* lastNode(DLLNode<T> *root);

    
    template <class T>
    void _quickSortStack(DLLNode<T> *l, DLLNode<T> *h);
    void quickSortStack();
    

    // Busqueda: Binary
    int binarySearch(int busq);

    int getLenght();//

};



#endif  // _BITACORA_H_
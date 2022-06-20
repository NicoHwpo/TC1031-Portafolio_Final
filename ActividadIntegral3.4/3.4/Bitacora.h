#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Registro.h"
#include "MaxHeap.h"
#include "MaxHeap1.h"


class Bitacora{

    private:
        std::vector<Registro> listaRegistros;

    public:
        
        //Constuctores
        Bitacora();
        Bitacora(std::string bitHeap);

        //Print
        void print();
        void printOutOrd();
        void printOutIpsMasAcces();

        //ordenamiento
        void heapify(std::vector<Registro> &arr, int n, int i);
        void heapSort();
        std::vector<int> listaIps;
        int listSize();
        
};

#endif  // _BITACORA_H_
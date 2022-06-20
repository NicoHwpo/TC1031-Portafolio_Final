// Actividad 3.4 Evidencia
// Samuel Acosta Ugarte A00833547
// Nicolas Aguirre Villafane
//g++ -std=c++17 *.cpp -o main
//./main

#include <iostream>
#include <vector>
#include "Bitacora.h"
#include "MaxHeap.h"
#include "MaxHeap1.h"

int main() {
    std::vector<int> e;
    std::vector<std::string> ef;
    Bitacora miBitacora("bitacoraHeap.txt"); //abrir archivo y darle formato
    MaxHeap<int> ma(30);
    MaxHeap1<int> ma1(30); //crear bst MaxHeap de tamaño listSize
    miBitacora.heapSort(); //ordenar los registros segun ip 
    miBitacora.printOutOrd(); //almacenar archivo en txt "bitacora_ordenada.txt"
    e = miBitacora.listaIps; 
    ma.cuentaRepes(e); //mandar las ips para contar las repetidas
    ma1.cuentaRepes(e);
    ma1.printOutIpsMasAcces(); //imprimir todas las ips sin repetirse y sus veces repetidas
    ef=ma.CincoIpsMasAcces();
    //imprimir 5 ips con mas acceso
    std::cout<<"5 ips con mas acceso:"<<std::endl;
    for (int i = 0; i < 5; i++)
    {
        std::cout <<ef[i]<<std::endl;
        
    }
}
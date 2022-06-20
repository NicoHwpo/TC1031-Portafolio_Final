#include "Bitacora.h"
#include "MaxHeap.h"
#include "MaxHeap1.h"

using namespace std;

Bitacora::Bitacora() {
}

//Complejidad O(n) - Visita cada linea de un archivo size n
Bitacora::Bitacora(std::string bitHeap) {
    std::string month, day, time, ipa1, ipa2, ipa3, ipa4, port, message;
    std::ifstream file(bitHeap);
    if (!file.good()) {
        file.close();
        throw std::invalid_argument("File not found");
    }
    else {
        while (!file.eof()) {
            std::getline(file, month, ' ');
            std::getline(file, day, ' ');
            std::getline(file, time, ' ');
            std::getline(file, ipa1, '.');
            std::getline(file, ipa2, '.');
            std::getline(file, ipa3, '.');
            std::getline(file, ipa4, ':');
            std::getline(file, port, ' ');
            std::getline(file, message);
            // Crear un objeto de la clase Registro
            Registro tmpRegistro(month, day, time, ipa1, ipa2, ipa3,ipa4,port,message);
            //Agregar al vector de registross
            listaRegistros.push_back(tmpRegistro);

            
        }
    }
}

//Complejidad O(n) - visita una lista size n para imprimir cada una
void Bitacora::print() {

    std::cout<< "----------------------------------" << std::endl;
    std::cout<< "La bitacora contiene lo siguiente:" << std::endl;
    std::cout<< "----------------------------------" << std::endl;

    for (int i=0; i<listaRegistros.size(); i++){
        std::cout<<listaRegistros[i].getAll()<<std::endl;    
    }
    
}


int Bitacora::listSize(){
    return listaRegistros.size();
}

//Complejidad O(n) - visita cada elemento de una lista size n para escribirla en un txt
void Bitacora::printOutOrd() {
    std::fstream bitHeap;
    bitHeap.open("bitacora_ordenada.txt",ios::out);

    if (bitHeap.is_open()) {
        for(int i=0; i<listaRegistros.size(); i++) {
            bitHeap<<listaRegistros[i].getAll()<<std::endl;
        }
    }
    else {
        bitHeap.close();
        throw std::invalid_argument("File not found");
    }
}



//Codigo basado en Geeks for Geeks
// Complejidad O(logn) - Divide and conquer
void Bitacora::heapify(std::vector<Registro> &arr, int n, int i) {

    //Inicializar el elemento mas grande como raiz
    int largest = i;

    //Izquierdo = 2*i + 1
    int l = 2 * i + 1;

    //Derecho = 2*i + 2
    int r = 2 * i + 2;

    //Si el hijo izquiero es mas grande que la raiz
    if  (l < n && arr[l] > arr[largest])
        largest = l;

    //Si el hijo derecho es mas grande que el mas grande actual
    if (r < n && arr[r] > arr[largest])
        largest = r;

    //Si el elemento mas grande no es la raiz
    if (largest != i) { 
        swap(arr[i], arr[largest]);

        // Recursivamente aplicar heapify al subarbol afectado
        heapify(arr, n, largest);
    }
}


//Codigo basado en Geeks for Geeks
//Complejidad O(nLogn) - Por cada reduccion de trabajo se trabaja n veces
void Bitacora::heapSort() {
    int i;
    int n = listaRegistros.size();

    //Construir heap (reacomodar vector)
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(listaRegistros, n, i);

    //Extraer elemento por elemento del heap
    for (int i = n - 1; i > 0; i--) {

        //Mover el elemento raiz actual hacia el final
        swap(listaRegistros[0], listaRegistros[i]);

        //Llamar heapify en el heap reducido
        heapify(listaRegistros,i,0);
    }
    for (int i = 0; i < listaRegistros.size(); i++)
        {
            listaIps.push_back(listaRegistros[i].getIp());
        }
}


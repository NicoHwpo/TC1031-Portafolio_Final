#include <vector>
#include <fstream>
#include <ostream>
#include "Bitacora.h"
#include "dateTime.h"


Bitacora::Bitacora() {
  
}

Bitacora::Bitacora(std::string fileName) {
  elementos=0;//
  std::string month, day, hours, minutes, seconds, ipAdd, port, error;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    while (!file.eof()) {
        std::getline(file, month, ' ');
        std::getline(file, day, ' ');
        std::getline(file, hours, ':');
        std::getline(file, minutes, ':');
        std::getline(file, seconds, ' ');
        std::getline(file, ipAdd, ':');
        std::getline(file, port, ' ');
        std::getline(file, error);
        // Crear un objeto de la clase Registro
        Registro tmpRegistro(month, day, hours, minutes, seconds, ipAdd, port, error);
        
        
        // Agregar al vector de regisrros
        listaRegistros.addLast(tmpRegistro);
        dateTime listado(month, day, hours, minutes, seconds);
        //std::vector<int> lista;
        lista.push_back(listado.getDate());
      }
  }
  int swapsR=0, comparaR=0;
  ordenaIntercambio(lista,swapsR,comparaR);
}



void Bitacora::print() {
  std::cout << "La bitacora contiene lo siguiente:" << std::endl;
  for (int i=0; i < listaRegistros.getNumElements(); i++){
    std::cout << listaRegistros[i].getAll() << std::endl;
    elementos++;
  }
    
}
void Bitacora::print(int a, int b){
  std::cout << "Elementos encontrados entre las 2 fechas" << std::endl;
  for (int i=a; i <= b; i++){
    std::cout << listaRegistros[i].getAll() << std::endl;
    
  }
    
}

void Bitacora::printBus(int a, int b){
  std::cout<< "Txt con datos de la busqueda creado."<< std::endl;
  int counter=0;
  int lineas=0;
  std::ifstream inFile;
  std::fstream myFile;
    myFile.open("resultado_busqueda.txt",std::ios::out);//escribir
    if(myFile.is_open()){
        for (int i=a; i <= b; i++){
    myFile<< listaRegistros[i].getAll() <<std::endl;
    
  }
      }
      myFile.close();
}

void Bitacora::printOrd(){
  std::cout<< "Txt con bitacora ordenada creado."<< std::endl;
  int counter=0;
  int lineas=0;
  std::ifstream inFile;
  std::fstream myFile;
    myFile.open("bitacora_ordenada.txt",std::ios::out);//escribir
    if(myFile.is_open()){
        for (int i=0; i < listaRegistros.getNumElements(); i++){
    myFile<< listaRegistros[i].getAll() <<std::endl;
    
  }
      }
      myFile.close();
}



void Bitacora::ordenaIntercambio(std::vector<int> &array, int &ord_swaps, int &ord_compara){

    for(int i=0; i<array.size()-1; i++){
        for(int j=i+1; j<array.size(); j++){
            if(array[i]>array[j]){
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                ord_swaps++;
            }
            ord_compara++;
        }
    }
}

void Bitacora::bubbleSort() {
  int i, j;
  int n = listaRegistros.getNumElements();
  Registro tmp;
  for (i = 0; i < n-1; i++) {
    for (j = 0; j < n-i-1; j++) {
      if (listaRegistros[j] > listaRegistros[j+1]){
        tmp = listaRegistros[j];
        listaRegistros[j] = listaRegistros[j+1];
        listaRegistros[j+1] = tmp;
      }
    }
  }
}

template <class T>
DLLNode<T>* Bitacora::partition(DLLNode<T> *l, DLLNode<T> *h) {
    DLLNode<T> pi = h->data;
    DLLNode<T>* i = l->prev;

    for(DLLNode<T>* j = l; j != h; j = j->next) {
        if (j->data <= pi.data) {
            i = (i == NULL)? l : i->next;
            swap(&(i->data), &(j->data));
        }
    }
    i = (i == NULL)? l : i->next;
    swap(&(i->data), &(h->data));
    return i;
}

template <class T>
void Bitacora::_quickSortRecursive(DLLNode<T> *l, DLLNode<T> *h) {
    if (h != NULL && l != h && l != h->next) {
        DLLNode<T> *p = partition(l,h);
        _quickSortRecursive(l, p->prev);
        _quickSortRecursive(p->next, h);
    }

}

void Bitacora::quickSortRecursive() {
    _quickSortRecursive(listaRegistros.getHead(),listaRegistros.getTail());
}

void Bitacora::swap(Registro *a, Registro *b) {
    Registro t = *a;//
    *a = *b;
    *b = t;
}

template <class T>
void Bitacora::_quickSortStack(DLLNode<T> *l, DLLNode<T> *h) {
    int stack[h - l + 1];

    int top = -1;

    stack[++top] = l;
    stack[++top] = h;

    while(top >= 0) {
        h = stack[top--];
        l = stack[top--];

        int p = partition(l, h);

        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}
void Bitacora::quickSortStack() {
    _quickSortRecursive(listaRegistros.getHead(),listaRegistros.getTail());
}

/*int Bitacora::binarySearch(int n, Registro k) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int m = low + (high - low) / 2;
        if (k == listaRegistros[m]) return m;
        else if (k < listaRegistros[m])
            high = m - 1;
        else
            low = m + 1;
    }
    return -1;
}*/

int Bitacora::binarySearch(int busq) {
  std::vector<int> array;
  array=lista;
  int size;
  size=lista.size();
  int low = 0;
  int high = size - 1;
  int mid;
  while(low<=high){
    mid = low + (high - low) / 2;
    if (busq==array[mid])
    {
      return mid;
    }
    else if (busq > array[mid])
    {
      low = mid+1;
    }
    else{
      high = mid -1;
    }
  }
  
  return -1; 
}

int Bitacora::getLenght() {
    return elementos;
}


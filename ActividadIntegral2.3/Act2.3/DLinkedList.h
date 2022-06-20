#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_
  
  #include<iostream>
  #include <stdexcept>
  #include "DLLNode.h"

  template <class T>
  class DLinkedList {
      private:
        DLLNode<T> *head;
        DLLNode<T> *tail;
        int numElements;

      public:
        DLinkedList();
        ~DLinkedList();
        DLLNode<T>* getHead();
        DLLNode<T>* getTail();
        int getNumElements();
        void printList();
        void printLastNode();
        void addFirst(T value);
        void addLast(T value);
        bool deleteData(T value);
        bool deleteAt(int position);
        T getData(int position);
        //nuevas implementaciones--------------------------------------
        void updateData(T value, T newValue);
        void updateAt(int index, T value);
        int findData(T value);
        T& operator [] (int index);
        void operator=(DLinkedList<T> &list);
        void clear();
        void sort(int low, int high); //mergeSort
        void merge(DLinkedList<T> &list, int low, int m, int high);
        void duplicate();
        void removeDuplicates();
  };

  template <class T>
  DLLNode<T>* DLinkedList<T>::getHead() {
      DLLNode<T> *p = head;
      return p;
  }

  template <class T>
  DLLNode<T>* DLinkedList<T>::getTail() {
      DLLNode<T> *q = tail;
      return q;
  }

  template<class T>
  DLinkedList<T>::DLinkedList() {
      std::cout << "--->Creando una lista vacia" << std::endl;
      head = nullptr;
      tail = nullptr;
      numElements = 0;
  }

  template<class T>
  DLinkedList<T>::~DLinkedList() {
      std::cout << "--->Liberando memoria de la lista ligada" << std::endl;
    DLLNode<T> *p, *q;
    p = head;
    while (p != nullptr) {
      q = p->next;
      delete p;
      p = q;
    }
    head = nullptr;
    tail = nullptr;
    numElements = 0;
  }

  template<class T>
  int DLinkedList<T>::getNumElements() {
    return numElements;
  }

  template<class T>
  void DLinkedList<T>::printList() {
    DLLNode<T> *ptr = head;
    if(numElements == 0){
        std::cout<<"La lista esta vacia..."<<std::endl;
        return;
    }
    while (ptr != nullptr) {
        std::cout << ptr->data << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;
  }

  template<class T>
  void DLinkedList<T>::printLastNode() {
    std::cout << tail->data << std::endl;
  }

  template<class T>
  void DLinkedList<T>::addFirst(T value) {
    DLLNode<T> *newDLLNode = new DLLNode<T>(value);
    // Si la lista está vacia
    if (head == nullptr && tail == nullptr) {
      head = newDLLNode;
      tail = newDLLNode;
    }
    else {
      newDLLNode->next = head;
      head->prev = newDLLNode;
      head = newDLLNode;
    }
    numElements++;
  }

  template<class T>
  void DLinkedList<T>::addLast(T value) {
    if (head == nullptr && tail == nullptr) {
      addFirst(value);
    }
    else {
      DLLNode<T> *newDLLNode = new DLLNode<T>(value);
      tail->next = newDLLNode;
      newDLLNode->prev = tail; 
      tail = newDLLNode;
      numElements++;
    }
  }

  template<class T>
  bool DLinkedList<T>::deleteData(T value) {
    // Si la lista esta vacia 
    if (head == nullptr && tail == nullptr) {
      return false;
    }
    else {
      DLLNode<T> *p, *q;
      p = head;
      q = nullptr;
      // buscar value en la lista
      while (p != nullptr && p->data != value) {
        q = p;
        p = p->next;
      }
      // Si no existe value en la lista
      if (p == nullptr)
        return false;
      // Si debe borrarse el primer elemento
      if (p->prev == nullptr) {
        head = p->next;
        if (head != nullptr)
          head->prev = nullptr;
      }
      else if (p->next == nullptr) { 
        // Si debe borrarse el último elemento
        q->next = nullptr;
        tail = q;
      }
      else {
        // Cualquier otro elemento entre la lista 
        q->next = p->next;
        p->next->prev = q;
      }
      delete p;
      numElements--;
      return true;
    }
  }

  template<class T>
  bool DLinkedList<T>::deleteAt(int position) {
    if (position < 0 || position >= numElements) {
      throw std::out_of_range("Indice fuera de rango");
    }
    else if (position == 0) { // Si debe borrarse el primer elemento
      DLLNode<T> *p = head;
      // Si la lista contiene solo un nodo
      if (head != nullptr && head->next == nullptr) {
        head = tail = nullptr;  
      }
      else {
        head = p->next;
        head->prev = nullptr;
      }
      delete p;
      numElements--;
      return true; 
    }
    else { // Si la lista contiene mas de un nodo
      DLLNode<T> *p = head, *q = nullptr;
      int index = 0;
      // Se busca el indice del elemento a borrar
      while (index != position) {
        q = p;
        p = p->next;
        index++;
      }
      // Si debe borrarse el último elemento
      if (p->next == nullptr) {
        q->next = nullptr;
        tail = q;
      }
      else { // Cualquier otro elemento en medio de la lista 
        q->next = p->next;
        p->next->prev = q;
      }
      delete p;
      numElements--;
      return true;
    }
  }

  template<class T>
  T DLinkedList<T>::getData(int position) {
    if (position < 0 || position >= numElements) {
      throw std::out_of_range("Indice fuera de rango");
    }
    else {
      if (position == 0)
        return head->data;
      DLLNode<T> *p = head;
      int index = 0;
      while (p != nullptr) {
        if (index == position)
          return p->data;
        index++;
        p = p->next;
      }
      return -1;
    }
  }

template<class T>
void DLinkedList<T>::updateData(T value, T newValue){
    DLLNode<T> *p = head;

    //buscar value en la lista
    while(p != nullptr){
        if(p->data == value){
            p->data = newValue;
            break;
        }
        p = p->next;
    }

    //Si value no existe en la lista
    if(p == nullptr){
        throw std::out_of_range("Valor no encontrado en la lista");
    }
}

template<class T>
void DLinkedList<T>::updateAt(int index, T value) {
    if (index < 0 || index>= numElements) {
        throw std::out_of_range("Indice fuera de rango");
    }
    else if (index == 0) {
        //si se debe actualizar el primer elemento-----------------------------
        DLLNode<T> *p = head;
        //si la lista tiene solo un nodo
        if (head != nullptr && head->next == nullptr) {
            head = tail = nullptr;
        }
        //si tiene mas de un nodo
        else {
            head = p->next;
            head->prev = nullptr;
        }
        delete p;
        addFirst(value);
    }
    else {
        //si se quiere actualizar cualquier otro que no sea el primero ---------
        DLLNode<T> *p = head, *q = nullptr;
        int pos = 0;
        //buscar el indice del elemento a actualizar
        while(pos != index) {
            q = p;
            p = p->next;
            pos++;
        }
        //si debe actualizarse el ultimo elemento
        if(p->next == nullptr) {
            q->next = nullptr;
            tail = q;
            delete p;
            addLast(value);
            return;
        }
        //si se debe actualizar otro elemento en medio de la lista
        else {
            q->next = p->next;
            p->next->prev = q;
        }
        delete p;
        DLLNode<T> *newDLLNode = new DLLNode<T>(value);
        newDLLNode->prev = q;
        newDLLNode->next = q->next;
        q->next->prev = newDLLNode;
        q->next = newDLLNode;
    }
}

template<class T>
int DLinkedList<T>::findData(T value){
    DLLNode<T> *p = head;                          //crear un puntero que recorra la lista
    int position=0;                             //generar un valor para el indice, este se retornara al finalizar la busqueda

    if(p==nullptr)                              //verificar que la lista no este vacia
        throw std::out_of_range("La lista esta vacia, no hay elementos que buscar...");                              

    else if(p->data == value)                   //retornar indice 0 si el primer elemento es el que se quiere encontrar
        return position;

    else{
        while(p != nullptr){                    //de otra manera se recorrera la lista, checando cada vez si encontro el valor o si llego al final
            p = p->next;                        //si llego hasta el final, se retorna un -1, si se encuentra se retorna la posicion
            position++;                         //la posicion se incrementa cada vez que checa el valor de un nodo.
            if(p == nullptr){                   //best: O(1)        Prom: O(n)      Worst: O(n)
                return -1;
            }
            else if(p->data == value){
                return position;
            }
        }
    }
    return -1;                                          //para evitar un warning
}

template<class T>
T& DLinkedList<T>::operator[](int index) {
    DLLNode<T> *p = head;
    int counter = 0;

    //mandar un error en caso de ser un indice menor que 0
    if (index<0)
        throw std::out_of_range("Indice invalido");
    else {
        //encontrar el valor dentro de la posicion
        while(counter<index && p != nullptr) {
            p = p->next;
            counter++;
        }
      //en caso de no haber encontrado la posicion dentro de la lista, mandar un error
      if (p == nullptr)
          throw std::out_of_range("Indice fuera de rango");
      //en caso de si haber encontrado el valor dentro de la posicion, regresarlo
      else
          return p->data;
  }
  //tener un throw para evitar un warning.
  throw std::out_of_range("Error");
}

template<class T>
void DLinkedList<T>::operator=(DLinkedList<T> &list) {
    int numE = 0;

    //encontrar cual es la lista mas grande, para actualizar el numero de veces correcta
    //de ser iguales no importa que numero de elementos sea ya que es el mismo
    if (this->getNumElements() >= list.getNumElements()) {
        numE = list.getNumElements();
    }
    else {
        numE = this->getNumElements();
    }
    for (int i =0; i<numE; i++) {
        this->updateAt(i, list.getData(i));
    }
}

template<class T>
void DLinkedList<T>::clear() {
    DLLNode<T> *p = head, *q = nullptr;
    //verificar si la lista esta vacia, sin elementos que borrar
    if (numElements == 0){
        throw std::out_of_range("La lista esta vacia...");
    }
    //si solo es un elemento el que tenemos que borrar llamar a deleteAt(0)
    else if (numElements == 1) {
        deleteAt(0);
    }
    else  {
        //borrar 1 elemento por iteracion hasta llegar a 1
        while (numElements > 1){
            p = p->next;
            q = p->prev;
            head = p;
            p->prev = nullptr;
            delete q;
            q = nullptr;
            numElements--;
        }
        //cuando llegamos al ultimo llamara deleteAt(0)
        deleteAt(0);
        p=nullptr;
        //mandar un mensaje de exito
        std::cout<<"La lista se limpio exitosamente"<<std::endl;
    }
}

template<class T>
void DLinkedList<T>::sort(int low, int high) {
    if (low < high) {
      //encontrar el punto medio
      int m = low + (high - low)/2;
      //Ordenar las dos mitades
      sort(low, m);
      sort(m+1, high);
      //Fusionar ambas mitades
      merge(*this, low, m, high);
    }
}

template<class T>
void DLinkedList<T>::merge(DLinkedList<T> &list, int low, int m, int high){
    int i, j, k;
    int n1 = m - low + 1;
    int n2 = high - m;
    //crear listas L y R
    DLinkedList<T> L, R;
    //copiar datos a L y R
    for (i=0; i<n1; i++)  L.addLast(list[low + i]);
    for (j=0; j<n2; j++)  R.addLast(list[m + 1 + j]);
    //Fusionar los arreglos L y R
    i = j = 0; k= low;
    while (i<n1 && j <n2) {
        if(L[i] <= R[j]){   //intentar & para comparar
            list[k] = L[i];
            i++;
        }
        else {
            list[k] = R[j];
            j++;
        }
        k++;
    }
    //Copia los elementos restantes
    while (i < n1) {
        list[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        list[k] = R[j];
        j++;
        k++;
    }
}

template<class T>
void DLinkedList<T>::duplicate() {
    DLLNode<T> *p = head;
    //verificar primeramente si existen elementos por duplicar
    if (p == nullptr) {
        std::cout<<"La lista esta vacia, no hay elementos que duplicar..."<<std::endl;
        return;
    }
    //duplicar cada elemento de la lista hasta el penultimo
    
    while (p->next != nullptr) {
        DLLNode<T> *newNode = new DLLNode<T>(p->data);
        newNode->prev = p;
        newNode->next = p->next;
        p->next->prev = newNode;
        p->next = newNode;
        p = newNode->next;
        numElements++;
    }
    //duplicar el ultimo elemento o si solo tiene un elemento la lista
    DLLNode<T> *newNode = new DLLNode<T>(p->data);
    newNode->prev = p;
    p->next = newNode;
    numElements++;
}

template<class T>
void DLinkedList<T>::removeDuplicates(){
    int duplicates = 0;
    DLLNode<T> *p = head;
    //verificar si hay elementos en la lista
    if (p == nullptr) {
        std::cout<<"No hay elementos en la lista..."<<std::endl;
        return;
    }

    //contar el numero de duplicados, recorriendo la lista
    while(p->next != nullptr) {
        if (p->data == p->next->data) {
            duplicates++;
            //verificar si es el ultimo elemento duplicado
            if (p->next->next == nullptr) {
                p = p->next;
            }
            //si no recorrer hasta el siguiente elemento duplicado
            else {
                p = p->next->next;
            }
        }
        //checar si llegamos al final de la lista antes de salirnos del while
        //es decir que ya tenemos contadas todas las duplicaciones
        if (p->next == nullptr) {
            DLLNode<T> *q = p->next;
            p = head;
            //eliminar todos los elementos duplicados
            while(duplicates > 0) {
                //si es el primer elemento
                if (p==head) {
                    deleteData(p->data);
                    q = q->next->next;
                    p = q->prev;
                }
                //si es un elemento de en medio
                else if (q->next->next != nullptr) {
                    deleteData(p->data);
                    q = q->next->next;
                    p = q->prev;
                }
                //si es el ultimo elemento
                else {
                    deleteData(q->data);
                    q = nullptr;
                }
            }
        }
    }
}


#endif // _DLINKEDLIST_H_
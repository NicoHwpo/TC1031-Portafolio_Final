#ifndef __MAXHEAP_H_
#define __MAXHEAP_H_

#include <unordered_set>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Bitacora.h"

template <class T>
class MaxHeap
{
private:
    // contiene los elementos del heap
    std::vector<T> data, data1;
    std::vector<int> vvalor, vrepes, vrepes1;
    
    ;
    // capacidad maxima del heap
    int maxSize;
    // tamaño actual del heap
    int size;
    int parent(int i);
    int left(int i);
    int right(int i);
    int getIndex(std::vector<int> v, int K);
    void remove(std::vector<int> &v);
    std::vector<int> findItems(std::vector<T> const &v, int target);
    void binToIp(std::vector<int> &v);
    std::vector<int> decToBinaryToIp(int a);

public:
    MaxHeap(int capacity);
    ~MaxHeap();
    bool isEmpty();
    int getCapacity();
    void printMaxHeap();
    void push(T key);
    int top();
    void pop();
    int getSize();
    void cuentaRepes(std::vector<int> u);
    void ConoValRep(int i);
    std::vector<std::string> CincoIpsMasAcces();
    std::vector<std::string> IpMasAcces();
    void printOutIpsMasAcces();
};

template <class T>
MaxHeap<T>::MaxHeap(int capacity)
{
    std::cout << "--->Creando un MaxHeap: " << this << std::endl;
    size = 0;
    maxSize = capacity;
    data.resize(maxSize);
}

template <class T>
MaxHeap<T>::~MaxHeap()
{
    std::cout << "--->Liberando memoria del MaxHeap: " << this << std::endl;
    data.clear();
}

template <class T>
int MaxHeap<T>::getCapacity()
{
    return maxSize;
}

template <class T>
void MaxHeap<T>::printMaxHeap()
{
    for (int i = 0; i < size; i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;
}

template <class T>
int MaxHeap<T>::parent(int i)
{
    return (i - 1) / 2;
}

template <class T>
int MaxHeap<T>::left(int i)
{
    return (2 * i + 1);
}

template <class T>
int MaxHeap<T>::right(int i)
{
    return (2 * i + 2);
}

template <class T>
void MaxHeap<T>::push(T key)
{
    if (size == maxSize)
    {
        throw std::out_of_range("Overflow: no se puede insertar la llave: " + key);
    }
    // Insertamos la nueva llave al final del vector
    int i = size;
    data[i] = key;
    size++;
    // Reparar las propiedades del max heap si son violadas
    while (i != 0 && data[parent(i)] < data[i])
    {
        std::swap(data[i], data[parent(i)]);
        i = parent(i);
    }
}

template <class T>
void MaxHeap<T>::pop()
{

    data[0] = data[size - 1];
    size -= 1;
    int s1 = 1;
    int i = size;
    // Reparar las propiedades del max heap si son violadas
    while (s1 <= size)
    {
        if (data[parent(s1)] < data[s1])
        {
            std::swap(data[s1], data[parent(s1)]);
            i = parent(s1);
        }
        s1++;
    }
}

template <class T>
int MaxHeap<T>::top()
{
    if (size == 0)
    {
        std::cout << "Heap vacio" << std::endl; // precondicion
    }
    else
    {
        int top = data[0]; // data es el vector con todos los valores del heap; solo se imprime el primero (priorizado) [0]
        // std::cout<<top<<std::endl;
        return top;
    }
}

template <class T>
bool MaxHeap<T>::isEmpty()
{
    return (size <= 0);
}

 template <class T>
 int MaxHeap<T>::getSize() {
   return size;          //size contiene el tamaño actual del heap; solo se imprime "size"
 }


template <class T>
void MaxHeap<T>::cuentaRepes(std::vector<int> u)
{
    int sz, sz1, temp = u[0], count = 1, max = 1, curmax = 0;
    sz = u.size();
    data1 = data;

    for (int i = 0; i < sz; i++)
    {
        if (temp == u[i + 1])
        {
            count = count + 1;
            curmax = count;
        }
        else if (temp != u[i + 1] && temp != u[i - 1])
        {
            // cout << "Valor " <<u[i] <<" repetido: 1 vez" << endl;
            vvalor.push_back(u[i]);
            vrepes.push_back(1);
            temp = u[i + 1];
            count = 1;
        }
        else if (temp != u[i + 1])
        {
            // cout << "Valor " <<temp <<" repetido: " <<curmax<<" veces" << endl;
            vvalor.push_back(temp);
            vrepes.push_back(curmax);
            if (curmax > max)
            {
                max = curmax;
            }
            temp = u[i + 1];
            count = 1;
        }
    }

    vrepes1 = vrepes;
    remove(vrepes1);
    for (int i = 0; i < vrepes1.size(); i++)
    {
        push(vrepes1[i]);
    }
}

// codigo de techie delight
template <class T>
void MaxHeap<T>::remove(std::vector<int> &v)
{
    std::vector<int>::iterator itr = v.begin();
    std::unordered_set<int> s;

    for (auto curr = v.begin(); curr != v.end(); ++curr)
    {
        if (s.insert(*curr).second)
        {
            *itr++ = *curr;
        }
    }
    v.erase(itr, v.end());
}

template <class T>
std::vector<std::string> MaxHeap<T>::CincoIpsMasAcces()
{
    int in, a = 0;
    std::vector<std::string> h;
    int s = 0, i = 0, y = 0;
    while (s == 0 && y < 5)
    {
        if (data[0] == vrepes1[i])
        {
            std::vector<int> indi = findItems(vrepes, vrepes1.at(i)), g;
            if (indi.size() > 1)
            {
                for (int k = 0; k < indi.size(); k++)
                {
                    if (y < 5)
                    {
                        in = vvalor.at(indi[k]);
                        std::string p,p1,p2,p3,p4,p5,p6,p7,p8,p9,pg;
                        p = "(";
                        //std::cout << "(";
                        
                        g = decToBinaryToIp(in);
                        p1= std::to_string(g[0]);
                        p2= std::to_string(g[1]);
                        p3= std::to_string(g[2]);
                        p4= std::to_string(g[3]);
                        p9 = std::to_string(data[0]);
                        p5= ".";
                        p6=",";
                        p7= ")";
                        p8=" ";
                        pg= p+p1+p5+p2+p5+p3+p5+p4+p6+p8+p9+p7;
                        h.push_back(pg);

                       /* for (int l = 0; l < 3; l++)
                        { 
                            std::cout <<g[l]<<".";
                        }
                        std::cout << g[3]<< ", " << data[0] << ")"<< std::endl;*/
                        i = 0;
                        y++;
                    }
                }
                pop();
            }
            else
            {
                a = getIndex(vrepes, vrepes1.at(i));
                in = vvalor.at(a);
                std::string p,p1,p2,p3,p4,p5,p6,p7,p8,p9,pg;
                        p = "(";
                        //std::cout << "(";
                        
                        g = decToBinaryToIp(in);
                        p1= std::to_string(g[0]);
                        p2= std::to_string(g[1]);
                        p3= std::to_string(g[2]);
                        p4= std::to_string(g[3]);
                        p9 = std::to_string(data[0]);
                        p5= ".";
                        p6=",";
                        p7= ")";
                        p8=" ";
                        pg= p+p1+p5+p2+p5+p3+p5+p4+p6+p8+p9+p7;
                        //std::cout <<pg<<std::endl;
                        h.push_back(pg);
                pop();
                i = 0;
                y++;
            }
        }
        else
        {
            i++;
        }
        
    }
    
    return h;
}


template <class T>
int MaxHeap<T>::getIndex(std::vector<int> v, int K)
{
    auto it = find(v.begin(), v.end(), K);

    // If element was found
    if (it != v.end())
    {

        // calculating the index
        // of K
        int index = it - v.begin();
        return index;
    }
    else
    {
        // If the element is not
        // present in the vector
        return -1;
    }
}

template <class T>
std::vector<int> MaxHeap<T>::findItems(std::vector<T> const &v, int target)
{
    std::vector<int> indices;

    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == target)
        {
            indices.push_back(i);
        }
    }

    return indices;
}

template <class T>
std::vector<int> MaxHeap<T>::decToBinaryToIp(int a)
{
    std::vector<int> g;
    short bin[32];
    for (int i = 0; i < 32; i++)
    {
        bin[i] = a % 2;
        a /= 2;
    }
    a = 0;
    std::vector<int> f;
    for (int i = 31; i >= 0; i--)
    {
        f.push_back(bin[i]);
    }


    int b = 0, b1 = 0, b2 = 0, b3 = 0, s = 128;
    for (int i = 0; i < 8; i++)
    {
        a = f.at(i) * s;
        s /= 2;
        b += a;
    }
    g.push_back(b);
    //std::cout << b << ".";
    s = 128;
    for (int i = 8; i < 16; i++)
    {
        a = f.at(i) * s;
        s /= 2;
        b1 += a;
    }
    g.push_back(b1);
    //std::cout << b1 << ".";
    s = 128;
    for (int i = 16; i < 24; i++)
    {
        a = f.at(i) * s;
        s /= 2;
        b2 += a;
    }
    g.push_back(b2);
    //std::cout << b2 << ".";
    s = 128;
    for (int i = 24; i < 32; i++)
    {
        a = f.at(i) * s;
        s /= 2;
        b3 += a;
    }
    g.push_back(b3);
    //std::cout << b3;
    
    return g;
}

#endif // __MAXHEAP_H_
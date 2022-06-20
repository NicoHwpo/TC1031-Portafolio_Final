
#ifndef __GRAPH_H_
#define __GRAPH_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include "LinkedList.h"
#include "ipAddress.h"
#include "HashTable.h"
# define INF 0x3f3f3f3f

class Graph {
  private:
    int numNodes;
    int numEdges;

    std::pair<int, std::string> bootMaster;
    // Lista de adyacencia (vector de listas)
    std::vector<LinkedList<std::pair<int,int>>> adjList;
    // mapea IPs a un numero entero de orden
    std::map<unsigned int, ipAddress> mapIP;
    // vector de objetos ipAddress para contar los grados
    std::vector<ipAddress> ips; //valores de entrada y salida 
    // MaxHeap de pares (grado, ipString)
    std::priority_queue<std::pair<int, std::string>> maxHeapIPs;
    //agregar hash table (replit profe, cuadratic proving)
    void split(std::string line, std::vector<int> & res);
  	
    HashTable<unsigned int, ipAddress> hash;
  
  public:
    Graph();
    ~Graph();
    void loadGraphList(std::string fileName);
    void printGraph();
    void printIpGrado();
    void printTop5();
    void printDistance();
    void outDegrees(std::string fileName);
    void maxDegrees(std::string fileName);
    std::pair<int, std::string> getBootMaster();
    int findIpIndex(std::string ipString);
    void shortestPath(int src);
    void getIpSummary(std::string ipString);
    void buildHashTable();
    void ipSummary();
    
};




#endif // __GRAPH_H_
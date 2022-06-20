#include "Graph.h"


Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
}

Graph::~Graph() {
  adjList.clear();
  ips.clear();
}

void Graph::loadGraphList(std::string fileName) {
  std::string line, ip1, ip2, peso; 
  int i = 0;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    // (V log V) + (E log V)
    while(std::getline(file,line)) { 
      if (i == 0) {
        std::cout<<"---------------------------------------------------"<<std::endl;
        std::cout << "(Numero de IPs, Numero de incidencias): " << line << std::endl;
        std::cout<<"---------------------------------------------------"<<std::endl<<std::endl;
        std::vector<int> res;
        split(line, res);
        numNodes = res[0];
        numEdges = res[1];
        //std::cout << "numNodes " << numNodes << std::endl;
        //std::cout << "numEdges " << numEdges << std::endl;
        // Reservar memoria para los renglones de la lista de adyacencia (renglon 0 no utilizado) 
        adjList.resize(numNodes+1);
        ips.resize(numNodes+1);
        // Declara una lista vacia para cada renglon y la almacena en el vector
        for (int k = 1; k <= numNodes; k++) {
          LinkedList<std::pair<int,int>> tmpList; // en ponderado lista de pares
          adjList[k] = tmpList; 
        }
      }
      else if (i > 0 && i <= numNodes) {
        ipAddress tmpIP(line, "", i);
        ips[i] = tmpIP;
        mapIP.insert({tmpIP.getIpValue(), tmpIP}); // {string ip, int}
        //std::cout << "i: " << i << " IP: " << line << std::endl;
      } 
      else if (i > numNodes) {
        std::size_t found = line.find(":", 15);
        ip1 = line.substr(15, found-15);
        std::size_t found2 = line.find(" ", found+1);
        std::size_t found3 = line.find(":", found2+1);
        ip2 = line.substr(found2, found3-found2);
        std::size_t found4 = line.find(" ", found3+1);
        std::size_t found5 = line.find(" ", found4+1);
        peso = line.substr(found4, found5-found4);
        // Crear arista ip1 a ip2 con un peso
        ipAddress tmpIP1(ip1, "", 0);
        ipAddress tmpIP2(ip2, "", 0);
        std::map<unsigned int, ipAddress>::iterator it;
        int ip1Index, ip2Index;
        it = mapIP.find(tmpIP1.getIpValue());     
        if(it != mapIP.end())
          ip1Index = it->second.getIpIndex();
        it = mapIP.find(tmpIP2.getIpValue());     
        if(it != mapIP.end())
          ip2Index = it->second.getIpIndex();
        adjList[ip1Index].addLast({ip2Index, stoi(peso)});
        ips[ip1Index].addToDegree();
      }
      i++;
    }
    file.close();
  }
}

void Graph::split(std::string line, std::vector<int> & res) {
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
      res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
      lastPos = strPos + 1;
      strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}
// O(V + E)
void Graph::printGraph() {
  std::fstream printG;
  printG.open("grafo_impreso.txt");
  printG<<"Impresion del grafo: "<<std::endl;
  if(!printG.good()) {
    printG.close();
    throw std::invalid_argument("File not found");
  }
  else {
    for (int u = 1; u <= numNodes; u++){
      printG << "vertex " << u << ": ";
      for (int j = 0; j < adjList[u].getNumElements(); j++) {
        std::pair<int, int> p = adjList[u].getData(j);
        printG << "{" << p.first << ", " << p.second << "} ";
      }
      printG << std::endl;
    }
    printG.close();
  }
}
// O(V log V)
void Graph::printIpGrado() {
  std::fstream ipGrado;
  ipGrado.open("grados_ips.txt");
  ipGrado<<"Grado de salida de cada IP (Grado de salida, Ip)"<<std::endl;
  std::pair<int, std::string> p;
  if (!ipGrado.good()) {
    ipGrado.close();
    throw std::invalid_argument("File not found");
  }
  else {
    //imprimir cada ip y su respectivo grado de salida
    //a su vez construir un maxheap con base a grado de saldida.
    for(int i = 1; i <= numNodes; i++) {
      p.second = ips[i].getIp();
      p.first = ips[i].getDegree();
      maxHeapIPs.push(p); // O(log V)
      ipGrado<<p.first<<" \t\t"<<p.second<<std::endl;
    }
    ipGrado.close();
  }
}
// O(log V)
void Graph::printTop5() {
  std::fstream topFive;
  topFive.open("mayores_grados_ips.txt");
  topFive<<"Las IPs con mayor grado de salida (conexiones):"<<std::endl;
  std::pair<int, std::string> temp;
  if (!topFive.good()) {
    topFive.close();
    throw std::invalid_argument("File not found");
  }
  else {
    for (int i = 1; i <= 5; i++) {
      if (i == 1) {
        bootMaster = maxHeapIPs.top(); // O(1)
        std::cout<<"Ip de posible boot master: "<<bootMaster.second<<" con un grado de salida de: "<<bootMaster.first<<std::endl<<std::endl;
      }
      temp = maxHeapIPs.top(); // O(1)
      topFive<<temp.first<<"  "<<temp.second<<std::endl;
      maxHeapIPs.pop(); // O(log V)
    }
    topFive.close();
  }
}

std::pair<int, std::string> Graph::getBootMaster() {
  return bootMaster;
}
//O(ElogV)
void Graph::printDistance() {
  std::pair<int, std::string> tmp;
  tmp = getBootMaster(); //O(1)
  int tmpIndex = findIpIndex(tmp.second); //O(logv)
  shortestPath(tmpIndex); //O(ElogV)
}

// Codigo basado de de Geeks for Geeks - Dijkstras shortest path algorithm.
//https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
// Complejidad O(E log V)
void Graph::shortestPath(int src)
{
    //crear heap
    std::priority_queue< std::pair<int,int>, std::vector <std::pair<int,int>> , std::greater<std::pair<int,int>> > pq;
 
    //crear vector de distancias e inicializar todas en infinito
    std::vector<int> dist(numNodes+1, INF);
 
    //insertar nodo de partida e inicializar su distancia como 0
    pq.push(std::make_pair(0, src));
    dist[src] = 0;
 
    //Repetir hasta que el heap este vacio
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
 
        // recorrer nodos vecinos
        for (int j = 0; j < adjList[u].getNumElements(); j++) {
            std::pair<int,int> p = adjList[u].getData(j);
            // Get vertex label and weight of current adjacent
            // of u.
            int v = p.first;
            int weight = p.second;
 
            //  Encontrar si hay un camino mas corto atraves de u
            if (dist[v] > dist[u] + weight)
            {
                // Actualizar la distancia v
                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    }
 
    // Imprimir la distancia desde el bootmaster
    std::fstream distance;
    std::pair<int, std::string> max;
    max.first = 0;
    max.second = "";
    distance.open("distancia_bootmaster.txt");
    distance<<"Distancias con respecto al boot master (distancia, IP):"<<std::endl;
    if (!distance.good()) {
      distance.close();
      throw std::invalid_argument("File not found");
    }
    else {
      for (int i = 1; i <= numNodes; ++i){
        distance<<dist[i]<<" \t\t"<<ips[i].getIp()<<std::endl;
        if (dist[i] > max.first){
          max.first = dist[i];
          max.second = ips[i].getIp();
        }
        if (i == numNodes) {
          std::cout<<"La direccion IP mas lejana del boot master tiene una distancia de "<<max.first<<std::endl<<"La direccion de esta IP es: "<<max.second<<std::endl;
        }
      }
      distance.close();
    }
}

int Graph::findIpIndex(std::string ipString) {
  ipAddress tmpIp(ipString, "", 0);
  std::map<unsigned int, ipAddress>::iterator it;
  int ipIndex;
  it = mapIP.find(tmpIp.getIpValue());
  if(it != mapIP.end())
    ipIndex = it->second.getIpIndex();
  return ipIndex;
}
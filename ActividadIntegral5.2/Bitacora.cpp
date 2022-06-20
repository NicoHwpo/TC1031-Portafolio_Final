#include "Bitacora.h"

//Constructor
Bitacora::Bitacora() {

}

//Agregando metodos de graph para cargar los archivos
Bitacora::Bitacora(std::string fileName) {
  graph.loadGraphList(fileName);
  graph.buildHashTable();
  graph.ipSummary();
}

//Destructor
Bitacora::~Bitacora() {

}


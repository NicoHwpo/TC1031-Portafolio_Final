/** 
* 
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main 
*
* Actividad 4.3 - Actividad Integral de Grafos
* Samuel Acosta Ugarte A00833547
* Nicolas Aguirre V. A00832772
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main 
**/

#include <iostream>
#include "Bitacora.h"

int main() {
  Bitacora myBitacora("bitacoraGrafos.txt");

  return 0;
}
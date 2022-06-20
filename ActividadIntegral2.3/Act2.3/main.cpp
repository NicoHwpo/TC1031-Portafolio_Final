#include <iostream>
#include <vector>
#include <fstream>
#include "Bitacora.h"
#include "dateTime.h"

using std::cout;
using std::endl;
//g++ -std=c++17 *.cpp -o main

//Main
int main () {
  Bitacora miBitacora("bitacora.txt");
  //miBitacora.print();
  std::cout << "Bitacora ordenada" << std::endl;
  miBitacora.quickSortStack();
  //miBitacora.print();
  miBitacora.printOrd();
  

  //Registro efe("Jul", "04", "18", "49", "57", "80.169.79.65", "1150", "Failed password for illegal user root");
  //Registro efe1("Jul", "09", "16", "19", "58", "80.169.79.65", "1150", "Failed password for illegal user root");
  //cout<< efe.getDate() << endl;
  //cout << efe1.getDate() << endl;

  cout<<"FORMATO DE BUSQUEDA (mes dia hora minuto segundo)EJEMPLO: Jun 01 00 22 36"<<endl;
  cout<<"Digite la primer fecha: ";
  std::string mes, dia, hora, min, seg;
  std::cin>> mes>> dia>> hora>> min>> seg;
  dateTime fech1(mes,dia,hora,min,seg);

  cout<<"Digite la segunda fecha: ";
  std::string mes1, dia1, hora1, min1, seg1;
  std::cin>> mes1>> dia1>> hora1>> min1>> seg1;
  dateTime fech2(mes1,dia1,hora1,min1,seg1);
  int a, b, a1, b1;
  a=fech1.getDate();
  a1=fech2.getDate();
  b=miBitacora.binarySearch(a);
  b1=miBitacora.binarySearch(a1);
  
  if (b == -1|| b1 == -1)
  {
    cout<< "No se encontro la fecha" <<endl;
  }
  else{
    
    //miBitacora.print(b,b1);
    miBitacora.printBus(b,b1);
    
  }
    
  

  return 0;
}

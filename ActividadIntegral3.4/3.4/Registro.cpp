#include <cmath>
#include <vector>
#include "Registro.h"
#include "MaxHeap.h"

Registro::Registro() {
    mes = "";
    dia = "";
    tiempo = "";
    ip1 = "";
    ip2 = "";
    ip3 = "";
    ip4 = "";
    puerto = "";
    mensaje = "";
}

Registro::Registro(std::string MES, std::string DIA, std::string TIEMPO, std::string IP1, std::string IP2, std::string IP3, std::string IP4, std::string PUERTO, std::string MENSAJE) {
    mes = MES;
    dia = DIA;
    tiempo = TIEMPO;
    ip1 = IP1;
    ip2 = IP2;
    ip3 = IP3;
    ip4 = IP4;
    puerto = PUERTO;
    mensaje = MENSAJE;

    //representar el IP como un unsigned int para comparar usando sobrecarga de operadores
    ipr = stoi(ip4)*pow(256,0)+stoi(ip3)*pow(256,1)+stoi(ip2)*pow(256,2)+stoi(ip1)*pow(256,3);

}

unsigned int Registro::getIp() {
    return ipr;
}

std::string Registro::getAll() {
    return mes + " " + dia + " " + tiempo + " " + ip1 + "." + ip2 + "." + ip3 + "." + ip4 + ":" + puerto + " " + mensaje;
}


bool Registro::operator==(const Registro &other) {
  return this->ipr == other.ipr;
}

bool Registro::operator!=(const Registro &other) {
  return this->ipr != other.ipr;
}

bool Registro::operator>(const Registro &other) {
  return this->ipr > other.ipr;
}

bool Registro::operator<(const Registro &other) {
  return this->ipr < other.ipr;
}

bool Registro::operator<=(const Registro &other) {
  return this->ipr <= other.ipr;
}

bool Registro::operator>=(const Registro &other) {
  return this->ipr >= other.ipr;
}
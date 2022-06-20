#include "dateTime.h"


dateTime::dateTime() {
  mes = "";
  dia = "";
  hora = "";
  minutos = "";
  segundos = "";
  ip = "";
  puerto = "";
  RazonDeFalla = "";
}

dateTime::dateTime(std::string MES, std::string DIA, std::string HORA, std::string MINUTOS, std::string SEGUNDOS) {
  mes = MES;
  dia = DIA;
  hora = HORA;
  minutos = MINUTOS;
  segundos = SEGUNDOS;
  /*ip = IP;
  puerto = PUERTO;
  RazonDeFalla = RAZON_DE_FALLA;*/

  // Almacenar los campos de la fecha-hora en el struct tm
  dateStruct.tm_sec = std::stoi(segundos);
  dateStruct.tm_min = std::stoi(minutos);
  dateStruct.tm_hour = std::stoi(hora);
  dateStruct.tm_mday = std::stoi(dia);
  // Agregado para resolver problema de compatibilidad en Windows
  dateStruct.tm_isdst = 0;
  for (int i=0; i < meses.size(); i++) {
    if (meses[i]==mes)
      dateStruct.tm_mon = i;
  }
  dateStruct.tm_year = 2022 - 1900;  // Asumimos el año 2022
  // Obtener el Unix timestamp a partir del struct tm anterior 
  // Numero de segundos desde el 1 de enero de 1970
  date = mktime(&dateStruct);
}



time_t dateTime::getDate() {
  //std::cout<<date;   //lo imprime 2 veces si se descomenta
  return date;
}



std::string dateTime::getAll() {
  return mes +" " + dia + " " + hora + ":" + minutos + ":" + segundos + " " + ip + ":" + puerto + " " + RazonDeFalla;
}
bool dateTime::operator==(const dateTime &other) {
  return this->date == other.date;
}

bool dateTime::operator!=(const dateTime &other) {
  return this->date != other.date;
}

bool dateTime::operator>(const dateTime &other) {
  return this->date > other.date;
}

bool dateTime::operator<(const dateTime &other) {
  return this->date < other.date;
}

bool dateTime::operator<=(const dateTime &other) {
  return this->date <= other.date;
}

bool dateTime::operator>=(const dateTime &other) {
  return this->date >= other.date;
}
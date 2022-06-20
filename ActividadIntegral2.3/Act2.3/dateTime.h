#ifndef _DATETIME_H_
#define _DATETIME_H_

#include <ctime>
#include <iostream>
#include <vector>

class dateTime 
{
  public:
      //El constructor por default todo vacio 
      dateTime();
      //El constructor que le define los atributos del objeto.
      dateTime(std::string MES, std::string DIA, std::string HORA, std::string MINUTOS, std::string SEGUNDOS );
      time_t getDate();
      std::string getAll();
      //std::string dateTime(std::string MES, std::string DIA, std::string HORA, std::string MINUTOS, std::string SEGUNDOS);
      bool operator ==(const dateTime&);
      bool operator !=(const dateTime&);
      bool operator >(const dateTime&);
      bool operator <(const dateTime&);
      bool operator <=(const dateTime&);
      bool operator >=(const dateTime&);

      std::string mes, dia, hora, minutos, segundos, ip, puerto, RazonDeFalla;
      std::vector<std::string> meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; 
      // Struct que contiene todos los datos de la fecha-hora
      struct tm dateStruct;
      // Unix timestamp (segundos transcurridos desde 00:00 hrs, Jan 1, 1970 UTC)
      time_t date;
};
#endif
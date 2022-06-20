#ifndef _REGISTRO_H_
#define _REGISTRO_H_

#include <iostream>
#include <vector>

class Registro {

    public:
        Registro();
        Registro(std::string MES, std::string DIA, std::string TIEMPO, std::string IP1, std::string IP2, std::string IP3, std::string IP4, std::string PUERTO, std::string MENSAJE);
        
        unsigned int getIp();
        std::string getAll();

        bool operator ==(const Registro&);
        bool operator !=(const Registro&);
        bool operator >(const Registro&);
        bool operator <(const Registro&);
        bool operator <=(const Registro&);
        bool operator >=(const Registro&);

    private:
        std::string mes, dia, tiempo, ip1, ip2, ip3, ip4, puerto, mensaje;
        unsigned int ipr;
};

#endif  // _REGISTRO_H_
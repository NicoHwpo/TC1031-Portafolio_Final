#ifndef _IPADDRESS_H_
#define _IPADDRESS_H_

#include <cmath>
#include <iostream>
#include <vector>

class ipAddress {
    private:
      std::string ipString;
      std::string ipPort;
      int ipIndex;
      unsigned int ipValue;
      int degree;
      int degreeIn;

    public:
      ipAddress();
      ipAddress(std::string _ip, std::string _port, int idx);
      std::string getIp();
      std::string getIpPort();
      unsigned int getIpValue();
      int getIpIndex();
      void setDegree(int g);
      void setDegreeIn(int g);
      void addToDegree();
      void addToDegreeIn();
      int getDegree();
      int getDegreeIn();

      bool operator ==(const ipAddress&);
      bool operator !=(const ipAddress&);
      bool operator >(const ipAddress&);
      bool operator >=(const ipAddress&);
      bool operator <(const ipAddress&);
      bool operator <=(const ipAddress&);
};


#endif

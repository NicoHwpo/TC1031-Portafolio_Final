//Tarea 1.3 
//Samuel Acosta Ugarte 
//Nicolas Aguirre V. A00832772
//03/04/2022

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "dateTime.h"

using namespace std;

void ordenaIntercambio(vector<int> &array, int &ord_swaps, int &ord_compara){

    for(int i=0; i<array.size()-1; i++){
        for(int j=i+1; j<array.size(); j++){
            if(array[i]>array[j]){
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                ord_swaps++;
            }
            ord_compara++;
        }
    }
}

int busquedaBinaria(vector<int> &array, int k, int &bq_compara){

    int low = 0;
    int high = array.size() - 1;
    while (low <= high) {
        int m = low + (high - low) / 2;
        bq_compara++;
        if (k == array[m]) return m;
        else if (k < array[m]) 
            high = m - 1;
        else 
            low = m + 1;
    }
    return -1;
}

int secuentialSearch(vector<int> values, int n, int k, int &compara) {
  compara = 0;
  int i = 0;
  while (i < n && values[i] != k){
    i ++;
    compara++;
  }
  if (i < n)
    return i;
  else
    return -1;
}

int main(){
   
    int swapsR=0, comparaR=0;
    int bq_compara=0;
    int lineas=0; //cantidad de lineas
    ifstream inFile;

    inFile.open("bitacora.txt"); //abrir el archivo

    //checar por error de abrir el archivo
    if(inFile.fail()){
        cerr<<"Error al abrir el archivo";
        exit(1);
    }
  
    //contar el numero de lineas de la bitacora
    string line; //variable temporal: Para contar las lineas y para asignar valores al vector de strings
    vector<string> renglones;
    while(!inFile.eof()) { //mientras no este al final del archivo leer y almacenar las lineas usando getline()
        getline(inFile, line);
        renglones.push_back(line); //insertar nuevo elemento line 
        lineas++; //contador para el numero de lineas en el txt
    }

    inFile.close(); //cerrar el archivo para liberar espacio

    //crear los vectores de cada parametro de registro -----------------------------------------------------------

    vector<string> mes; //crear un vector donde se almacene solo los meses
    for (int i=0; i<=lineas-1; i++){
        mes.push_back(renglones[i].substr(0,3));
    }

    vector<int> dia; //crear un vector donde se almacenen los dias en formato entero
    for (int i=0; i<=lineas-1; i++){
        dia.push_back(stoi(renglones[i].substr(4,2)));
    }

    vector<int> hora; //crear un vector donde se almacenen las horas en formato entero
    for (int i=0; i<=lineas-1; i++){
        hora.push_back(stoi(renglones[i].substr(7,2)));
    }

    vector<int> minuto; //crear un vector donde se almacenen los minutos en formato entero
    for (int i=0; i<=lineas-1; i++){
        minuto.push_back(stoi(renglones[i].substr(10,2)));
    }

    vector<int> segundo; //crear un vector donde se almacenen los segundos en formato entero
    for (int i=0; i<=lineas-1; i++){
        segundo.push_back(stoi(renglones[i].substr(13,2)));
    }

    vector<string> ip; //crear un vector donde se almacenen las direcciones ip y mesnajes.
    for (int i=0; i<=lineas-1; i++){
        ip.push_back(renglones[i].substr(16));
    }

    vector<vector<string>> fechaComp;
    
    vector<int> fecha;
    for (int i=0; i<=lineas-1;i++){
        string mesT = mes[i];
        int diaT = dia[i];
        int horaT = hora[i];
        int minutoT = minuto[i];
        int segT = segundo[i];
        dateTime date(mesT, diaT, horaT, minutoT, segT);
        time_t fechSegs = date.getDate();
        fecha.push_back(fechSegs);
    }
    
    vector<int> fechaOrd = fecha;
    int a, b;
    ordenaIntercambio(fechaOrd, swapsR, comparaR);
    //Escribir bitacora ordenada en bitacora_ordenada.txt

    int counter=0;
    fstream myFile;
    myFile.open("bitacora_ordenada.txt",ios::out);//escribir
    if(myFile.is_open()){
      for(int i=0; i<=lineas-1; i++){
        int temp=0;
        int x=0;
        int comp=0;
        counter++;
        temp = fechaOrd[i];
        x = secuentialSearch(fecha, lineas, temp, comp);
        myFile<<mes[x]<<" "<<dia[x]<<" "<<hora[x]<<":"<<minuto[x]<<":"<<segundo[x]<<" "<<ip[x]<<endl;
      }
      myFile.close();
    }
  
    //peguntar al usuario por las 2 fechas para buscar en esos intervalos
    
    string mesU1, mesU2;
    int diaU1, horaU1, minutoU1, segundoU1, diaU2, horaU2, minutoU2, segundoU2;
    
    cout<<"FORMATO: Mmm dd hh mm ss "<<endl<<"Ejemplo: Jul 04 18 49 57"<<endl<<"Digite la primera fecha: "<<endl;
    cout<<"Fecha 1: ";
    cin>>mesU1>>diaU1>>horaU1>>minutoU1>>segundoU1;
    cout<<"Fecha 2: ";
    cin>>mesU2>>diaU2>>horaU2>>minutoU2>>segundoU2;
    cout<<endl;

    dateTime date1(mesU1, diaU1, horaU1, minutoU1, segundoU1);
    time_t fech1segs = date1.getDate();
    dateTime date2(mesU2, diaU2, horaU2, minutoU2, segundoU2);
    time_t fech2segs = date2.getDate();
  
    a = busquedaBinaria(fechaOrd, fech1segs, bq_compara);
    b = busquedaBinaria(fechaOrd, fech2segs, bq_compara);

    if((a==-1) || (b==-1)){
      cout<<"Error: Fecha no encontrada."<<endl;
      return 0;
    }

    counter =0; //contar el numero de registros
    for(int i=a; i<=b; i++){
      counter++;
    }
  
    cout<<"Resultado: "<<counter<<" Registros"<<endl;
    
    for(int i=a;i<=b;i++){
      int temp=0;
      int x=0;
      int comp=0;
      temp = fechaOrd[i];
      x = secuentialSearch(fecha, lineas, temp, comp);
      cout<<mes[x]<<" "<<dia[x]<<" "<<hora[x]<<":"<<minuto[x]<<":"<<segundo[x]<<" "<<ip[x]<<endl;
    }
  
    return 0;
}

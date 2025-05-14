#include <iostream>
using namespace std;

#include "Examen.h"
#include "ServicioMesa.h"
#include "ArchivoServicioMesa.h"

void Examen::EjemploDeListado(){
   ArchivoServicioMesa archivo("restaurant.dat");
   ServicioMesa registro;

   int i, cantidadRegistros = archivo.CantidadRegistros();
   for(i = 0; i < cantidadRegistros; i++){
      registro = archivo.Leer(i);
      cout << registro.toCSV() << endl;
   }
}

/**
1) Listar la cantidad de servicios de mesa que fueron valorados con un puntaje mayor al puntaje promedio

2) Listar el número de plato que recaudó mayor cantidad de dinero

3) Listar el número de mozo que recibió mayor cantidad total de propinas en el año 2024
*/

void Examen::Punto1(){

    ArchivoServicioMesa archivo("restaurant.dat");

    int cantidad = archivo.CantidadRegistros();

    ServicioMesa *vecRegistros = new ServicioMesa[cantidad];

    if(vecRegistros == nullptr){
        cout << " ERROR AL PEDIR MEMORIA" << endl;
        return;
    }

    float acumulador = 0;

    for(int i = 0; i < cantidad; i++){

        vecRegistros[i] = archivo.Leer(i);
        acumulador += vecRegistros[i].getPuntajeObtenido();

    }

    float promedio = acumulador/cantidad;

    int contadorServicios;

    for (int i = 0; i < cantidad; i++){

        if(vecRegistros[i].getPuntajeObtenido() > promedio){

            contadorServicios++;

        }

    }

    cout << endl << " LA CANTIDAD DE SERVICIOS DE MESA QUE FUERON VALORADOS CON UN PROMEDIO MAYOR AL PROMEDIO: " << contadorServicios << endl;

    delete [] vecRegistros;
}

void Examen::Punto2(){

    ArchivoServicioMesa archivo("restaurant.dat");

    int cantidad = archivo.CantidadRegistros();

    ServicioMesa registro;

    float vecPlatoRecaud[70] = {0};

    for(int i = 0; i < cantidad; i++){

        registro = archivo.Leer(i);
        vecPlatoRecaud[registro.getIDPlato() - 1] += registro.getImporte();

    }

    int maxPlato = 0;

    for(int i = 1; i < 70; i++){

        if(vecPlatoRecaud[maxPlato] < vecPlatoRecaud[i]){

            maxPlato = i;
        }

    }

    cout << endl << " EL PLATO CON MAYOR RECAUDACION DE DINERO ES: " << maxPlato + 1<< endl;

}

void Examen::Punto3(){

    ArchivoServicioMesa archivo("restaurant.dat");

    int cantidad = archivo.CantidadRegistros();

    ServicioMesa registro;

    float vecMozosPropinas[20] = {0};

    for(int i = 0; i < cantidad; i++){

        registro = archivo.Leer(i);
        if(registro.getFecha().getAnio() == 2024){

            vecMozosPropinas[registro.getIDMozo() - 1] += registro.getPropina();

        }

    }

    float maxPropina = vecMozosPropinas[0];
    int maxMozo = 1;

    for(int i = 1; i < 20; i++){

        if(maxPropina < vecMozosPropinas[i]){

            maxPropina = vecMozosPropinas[i];
            maxMozo = i + 1;
        }
    }

    cout << endl << " EL MOZO CON MAYOR CANTIDAD DE RECAUDACION DE PROPINAS EN 2024 ES: " << maxMozo << endl;

}

/**
LISTAR EL ID DE LOS PLATOS CUYA RECAUDACION EN EL 2024 SEA MAYOR A LA RECAUDACION EN EL 2023
*/

void Examen::Punto4(){

    ArchivoServicioMesa archivo("restaurant.dat");

    int cantidad = archivo.CantidadRegistros();

    ServicioMesa registro;

    float recaudacion2024[70] = {0};
    float recaudacion2023[70] = {0};

    for (int i = 0; i < cantidad; i++){

        registro = archivo.Leer(i);

        if(registro.getFecha().getAnio() == 2024){

            recaudacion2024[registro.getIDPlato() - 1] += registro.getImporte();

        } else if (registro.getFecha().getAnio() == 2023){

            recaudacion2023[registro.getIDPlato() - 1] += registro.getImporte();

        }

    }

    cout << endl << " ID DE LOS PLATOS CUYA RECAUDACION EN EL 2024 FUE MAYOR A LA RECAUDACION EN EL 2023" << endl;

    for (int i = 0; i < 70; i++){

        if(recaudacion2024[i] > recaudacion2023[i]){

            cout << " " << i + 1<< endl;
        }
    }
}

/**
Mostrar el n£mero de mozo con mayor cantidad de servicios de mesa realizados.
*/

void Examen::Punto5(){
    
    ArchivoServicioMesa archivo("restaurant.dat");

    int cantidad = archivo.CantidadRegistros();

    ServicioMesa registro;
    
    int vecCantServMozos[20] = {0};
    
    for (int i = 0; i < cantidad; i++){
        
        registro = archivo.Leer(i);
        
        vecCantServMozos[registro.getIDMozo() - 1] ++;
        
    }
    
    int indiceMax = 0;
    
    for (int i = 1; i < 20; i++){
        
        if(vecCantServMozos[indiceMax] < vecCantServMozos[i]){
            
            indiceMax = i;
            
        }
        
    }
    
    cout << endl << " EL MOZO CON MAYOR CANTIDAD DE SERVICIOS DE MESA ES: " << indiceMax + 1 << endl;
    
}

/**
Promedio de propinas en diciembre de 2023
*/

void Examen::Punto6(){
    
    ArchivoServicioMesa archivo("restaurant.dat");

    int cantidad = archivo.CantidadRegistros();

    ServicioMesa registro;
    
    float propinasDic = 0;
    int cantPropinas = 0;
    
    for (int i = 0; i < cantidad; i++){
        
        registro = archivo.Leer(i);
        
        if(registro.getFecha().getMes() == 12 && registro.getFecha().getAnio() == 2023){
            
            propinasDic += registro.getPropina();
            
            cantPropinas ++;
            
        } 
        
    }
    
    if(cantPropinas > 0){
        
        float promedioDic = propinasDic/cantPropinas;
    
        cout << endl << " PROMEDIO DE PROPINAS DEL MES DE DICIEMBRE EN EL 2023: " << promedioDic << endl;
        
    } else {
        
        cout << endl << " NO HUBIERON SERVICIOS EN DICIMBRE DEL 2023" << endl;
        
    }
}

/**
Cantidad de platos distintos que recibieron al menos una propina
*/

void Examen::Punto7(){
    
    ArchivoServicioMesa archivo("restaurant.dat");

    int cantidad = archivo.CantidadRegistros();

    ServicioMesa registro;  
    
    int vecPlatos[70] = {0};
    int cantPlatosPropina = 0;
    
    for (int i  = 0; i < cantidad; i++){
            
        registro = archivo.Leer(i);
        
        if (registro.getPropina() > 0){
            
            if(vecPlatos[registro.getIDPlato() - 1] == 0){
                
                vecPlatos[registro.getIDPlato() - 1] = 1;
                
                cantPlatosPropina ++;
                
            }
            
        }
        
    }
    
    cout << endl << " LA CANTIDAD DE PLATO DISTINTOS QUE RECIBIERON AL MENOS UNA PROPINA ES: "  << cantPlatosPropina << endl;
    
}

/**
Total recaudado por mozo n£mero 5
*/

void Examen::Punto8(){

    ArchivoServicioMesa archivo("restaurant.dat");

    int cantidad = archivo.CantidadRegistros();

    ServicioMesa registro;
    
    float totRecaud = 0;
    
    for (int i = 0; i < cantidad; i++){
        
        registro = archivo.Leer(i);
        
        if(registro.getIDMozo() == 5){
            
            totRecaud += registro.getImporte();
            
        }
        
    }
    
    cout << endl << " TOTAL RECAUDADO POR EL MOZO 5: $" << totRecaud << endl;
    
}

/**
D¡a/s (si es que hay un empate) con m s servicios realizados
*/
void Examen::Punto9(){

    ArchivoServicioMesa archivo("restaurant.dat");
    
    int cantidadRegistros = archivo.CantidadRegistros();
    
    ServicioMesa registro;

    const int MAX_FECHAS = 1000; // suponemos como m ximo 1000 fechas distintas
    
    Fecha fechas[MAX_FECHAS];
    
    int conteo[MAX_FECHAS];
    
    int totalFechas = 0;

    // Inicializar el contador
    for (int i = 0; i < MAX_FECHAS; i++) {
        conteo[i] = 0;
    }

    // Recorremos el archivo
    for (int i = 0; i < cantidadRegistros; i++) {
            
        registro = archivo.Leer(i);
    
        Fecha f = registro.getFecha();

        // Buscar si la fecha ya existe en el array
        bool encontrada = false;
        for (int j = 0; j < totalFechas; j++) {
            if (fechas[j].getDia() == f.getDia() &&
                fechas[j].getMes() == f.getMes() &&
                fechas[j].getAnio() == f.getAnio()) {
                conteo[j]++;
                encontrada = true;
                break;
            }
        }

        // Si no se encontr¢, agregarla
        if (!encontrada) {
            fechas[totalFechas] = f;
            conteo[totalFechas] = 1;
            totalFechas++;
        }
    }

    // Buscar el m ximo
    int maxServicios = 0;
    for (int i = 0; i < totalFechas; i++) {
        if (conteo[i] > maxServicios) {
            maxServicios = conteo[i];
        }
    }

    // Mostrar fechas con m s servicios
    cout << endl << " DIA/S CON MAS SERVICIOS REALIZADOS (" << maxServicios << " SERVICIOS):" << endl;
    for (int i = 0; i < totalFechas; i++) {
        if (conteo[i] == maxServicios) {
            cout << " " << fechas[i].toString() << endl;
        }
    }
}

///Listar todas las fechas en las que no se recibi¢ ninguna propina.

void Examen::Punto10(){
    
    ArchivoServicioMesa archivo("restaurant.dat");
    
    int cantidadRegistros = archivo.CantidadRegistros();
    
    ServicioMesa registro;

    const int MAX_FECHAS = 1000; // suponemos como m ximo 1000 fechas distintas
    
    Fecha fechas[MAX_FECHAS];
    
    int totPropinas[MAX_FECHAS] = {0};
    
    int totalFechas = 0;
    
    bool encontrada;
    
    for(int i = 0; i < cantidadRegistros; i++){
            
        registro = archivo.Leer(i);
    
        Fecha f = registro.getFecha();
        
        encontrada = false;
        
        for (int j = 0; j < totalFechas; j++){
            
            if( fechas[j].getDia() == f.getDia() &&
                fechas[j].getMes() == f.getMes() &&
                fechas[j].getAnio() == f.getAnio()){
                
                totPropinas[j] += registro.getPropina();
                encontrada = true;
                break;
            }
            
        }
        
        if(!encontrada){
            
            fechas[totalFechas] = f;
            totPropinas[totalFechas] = registro.getPropina();
            totalFechas ++;
            
        }
        
    }
    
    cout << endl << " FECHAS EN LAS QUE NO SE RECIBIERON PROPINAS: " << endl;
    
    for (int i = 0; i < totalFechas; i++){
        
        if(totPropinas[i] == 0){
            
            cout << " " << fechas[i].toString() << endl;
            
        }
        
    }
    
}

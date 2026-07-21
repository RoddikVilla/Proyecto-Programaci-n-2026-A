#ifndef CANCION_H
#define CANCION_H

#include <iostream>
#include <string>
using namespace std;

struct Cancion {
    string codigo;
    string titulo;
    string artista;
    string genero;
    int anioLanzamiento = 0;
    double duracionMinutos = 0.0;
    bool favorita = false;
};

// Guarda una cancion en una linea del archivo, separada por ";"
inline ostream& operator<<(ostream& salida, const Cancion& c) {
    salida << c.codigo << ";"
           << c.titulo << ";"
           << c.artista << ";"
           << c.genero << ";"
           << c.anioLanzamiento << ";"
           << c.duracionMinutos << ";"
           << c.favorita;
    return salida;
}

// Lee una cancion desde una linea del archivo
inline istream& operator>>(istream& entrada, Cancion& c) {
    string anio, duracion, favorita;

    if (getline(entrada, c.codigo, ';') &&
        getline(entrada, c.titulo, ';') &&
        getline(entrada, c.artista, ';') &&
        getline(entrada, c.genero, ';') &&
        getline(entrada, anio, ';') &&
        getline(entrada, duracion, ';') &&
        getline(entrada, favorita))
    {
        c.anioLanzamiento = stoi(anio);
        c.duracionMinutos = stod(duracion);
        c.favorita = stoi(favorita);
    }

    return entrada;
}

#endif
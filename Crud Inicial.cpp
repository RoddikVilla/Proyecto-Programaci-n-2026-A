//Proyecto Programacion MUSICA
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct Cancion {
	int id;
	string titulo;
	string artista;
};

vector<Cancion> canciones;
const string ARCHIVO = "canciones.txt"; 

void cargarDesdeArchivo() {
	canciones.clear();
	ifstream file(ARCHIVO);
	string linea;
	
	while (getline(file, linea)) {
		if (linea.empty()) continue;
		
		stringstream ss(linea);
		string idStr, titulo, artista;
		getline(ss, idStr, ';');
		getline(ss, titulo, ';');
		getline(ss, artista, ';');
		
		Cancion c;
		c.id = stoi(idStr);
		c.titulo = titulo;
		c.artista = artista;
		canciones.push_back(c);
	}
	file.close();
}


void guardarEnArchivo() {
	ofstream file(ARCHIVO, ios::trunc);
	for (const auto& c : canciones) {
		file << c.id << ";" << c.titulo << ";" << c.artista << "\n";
	}
	file.close();
}


int siguienteId() {
	int maxId = 0;
	for (const auto& c : canciones) {
		if (c.id > maxId) maxId = c.id;
	}
	return maxId + 1;
}

void crear() {
	Cancion c;
	c.id = siguienteId();
	
	cout << "Titulo: ";
	getline(cin, c.titulo);
	cout << "Artista: ";
	getline(cin, c.artista);
	
	canciones.push_back(c);
	guardarEnArchivo();
	
	cout << "Cancion creada con id " << c.id << "\n";
}

void listar() {
	if (canciones.empty()) {
		cout << "No hay canciones registradas.\n";
		return;
	}
	for (const auto& c : canciones) {
		cout << "[" << c.id << "] " << c.titulo << " - " << c.artista << "\n";
	}
}

void actualizar() {
	cout << "Id de la cancion a editar: ";
	int id;
	cin >> id;
	cin.ignore();
	
	for (auto& c : canciones) {
		if (c.id == id) {
			cout << "Nuevo titulo: ";
			getline(cin, c.titulo);
			cout << "Nuevo artista: ";
			getline(cin, c.artista);
			
			guardarEnArchivo();
			cout << "Cancion actualizada.\n";
			return;
		}
	}
	cout << "No se encontro una cancion con ese id.\n";
}

void eliminar() {
	cout << "Id de la cancion a eliminar: ";
	int id;
	cin >> id;
	cin.ignore();
	
	for (size_t i = 0; i < canciones.size(); i++) {
		if (canciones[i].id == id) {
			canciones.erase(canciones.begin() + i);
			guardarEnArchivo();
			cout << "Cancion eliminada.\n";
			return;
		}
	}
	cout << "No se encontro una cancion con ese id.\n";
}

int main() {
	cargarDesdeArchivo();
	
	int opcion;
	do {
		cout << "\n--- MENU CANCIONES ---\n";
		cout << "1. Crear cancion\n";
		cout << "2. Listar canciones\n";
		cout << "3. Actualizar cancion\n";
		cout << "4. Eliminar cancion\n";
		cout << "0. Salir\n";
		cout << "Opcion: ";
		cin >> opcion;
		cin.ignore();
		
		switch (opcion) {
			case 1: crear(); break;
			case 2: listar(); break;
			case 3: actualizar(); break;
			case 4: eliminar(); break;
			case 0: cout << "Chao!\n"; break;
			default: cout << "Opcion invalida.\n";
		}
	} while (opcion != 0);
	
	return 0;
}

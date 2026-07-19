//Proyecto Programacion Musica
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Cancion{
	string codigo;
	string titulo;
	string artista;
	string genero;
	int anioLanzamiento;
	double duracionMinutos;
	bool favorita;
};

vector<Cancion> canciones;

const string ARCHIVO = "canciones.txt";

ostream& operator<<(ostream& salida,const Cancion& c){
	salida<<c.codigo<<";"
	<<c.titulo<<";"
	<<c.artista<<";"
	<<c.genero<<";"
	<<c.anioLanzamiento<<";"
	<<c.duracionMinutos<<";"
	<<c.favorita;
	return salida;
}

istream& operator>>(istream& entrada,Cancion& c){
	
	string anio;
	string duracion;
	string favorita;
	
	if(getline(entrada,c.codigo,';') &&
	   getline(entrada,c.titulo,';') &&
	   getline(entrada,c.artista,';') &&
	   getline(entrada,c.genero,';') &&
	   getline(entrada,anio,';') &&
	   getline(entrada,duracion,';') &&
	   getline(entrada,favorita))
	{
		c.anioLanzamiento=stoi(anio);
		c.duracionMinutos=stod(duracion);
		c.favorita=stoi(favorita);
	}
	
	return entrada;
}

void cargarDesdeArchivo(){
	
	canciones.clear();
	
	ifstream archivo(ARCHIVO);
	
	Cancion c;
	
	if(archivo.is_open()){
		
		while(archivo>>c){
			canciones.push_back(c);
		}
		
		archivo.close();
	}
}

void guardarEnArchivo(){
	
	ofstream archivo(ARCHIVO);
	
	if(archivo.is_open()){
		
		for(int i=0;i<canciones.size();i++){
			archivo<<canciones[i]<<endl;
		}
		
		archivo.close();
	}
}

int buscarPorCodigo(string codigo){
	
	for(int i=0;i<canciones.size();i++){
		
		if(canciones[i].codigo==codigo){
			return i;
		}
		
	}
	
	return -1;
}

void crear(){
	
	Cancion c;
	
	cin.ignore();
	
	cout<<"Codigo: ";
	getline(cin,c.codigo);
	
	if(buscarPorCodigo(c.codigo)!=-1){
		cout<<"Ya existe una cancion con ese codigo.\n";
		return;
	}
	
	cout<<"Titulo: ";
	getline(cin,c.titulo);
	
	cout<<"Artista: ";
	getline(cin,c.artista);
	
	cout<<"Genero: ";
	getline(cin,c.genero);
	
	cout<<"Anio de lanzamiento: ";
	cin>>c.anioLanzamiento;
	
	cout<<"Duracion (minutos): ";
	cin>>c.duracionMinutos;
	
	cout<<"Es favorita? (1=Si, 0=No): ";
	cin>>c.favorita;
	
	canciones.push_back(c);
	
	guardarEnArchivo();
	
	cout<<"Cancion registrada correctamente.\n";
}

void listar(){
	
	cargarDesdeArchivo();
	
	if(canciones.empty()){
		cout<<"No hay canciones registradas.\n";
		return;
	}
	
	cout<<"\n===== LISTA DE CANCIONES =====\n";
	
	for(int i=0;i<canciones.size();i++){
		
		cout<<"\nCodigo: "<<canciones[i].codigo<<endl;
		cout<<"Titulo: "<<canciones[i].titulo<<endl;
		cout<<"Artista: "<<canciones[i].artista<<endl;
		cout<<"Genero: "<<canciones[i].genero<<endl;
		cout<<"Anio: "<<canciones[i].anioLanzamiento<<endl;
		cout<<"Duracion: "<<canciones[i].duracionMinutos<<endl;
		cout<<"Favorita: ";
		
		if(canciones[i].favorita)
			cout<<"Si"<<endl;
		else
			cout<<"No"<<endl;
	}
}

void buscar(){
	
	cargarDesdeArchivo();
	
	string codigo;
	
	cin.ignore();
	
	cout<<"Ingrese el codigo: ";
	getline(cin,codigo);
	
	int pos=buscarPorCodigo(codigo);
	
	if(pos==-1){
		
		cout<<"Cancion no encontrada.\n";
		return;
		
	}
	
	cout<<"\nCodigo: "<<canciones[pos].codigo<<endl;
	cout<<"Titulo: "<<canciones[pos].titulo<<endl;
	cout<<"Artista: "<<canciones[pos].artista<<endl;
	cout<<"Genero: "<<canciones[pos].genero<<endl;
	cout<<"Anio: "<<canciones[pos].anioLanzamiento<<endl;
	cout<<"Duracion: "<<canciones[pos].duracionMinutos<<endl;
	cout<<"Favorita: ";
	
	if(canciones[pos].favorita)
		cout<<"Si"<<endl;
	else
		cout<<"No"<<endl;
}

void actualizar(){
	
	cargarDesdeArchivo();
	
	string codigo;
	
	cin.ignore();
	
	cout<<"Codigo de la cancion: ";
	getline(cin,codigo);
	
	int pos=buscarPorCodigo(codigo);
	
	if(pos==-1){
		
		cout<<"Cancion no encontrada.\n";
		return;
	}
	
	cout<<"Nuevo titulo: ";
	getline(cin,canciones[pos].titulo);
	
	cout<<"Nuevo artista: ";
	getline(cin,canciones[pos].artista);
	
	cout<<"Nuevo genero: ";
	getline(cin,canciones[pos].genero);
	
	cout<<"Nuevo anio: ";
	cin>>canciones[pos].anioLanzamiento;
	
	cout<<"Nueva duracion: ";
	cin>>canciones[pos].duracionMinutos;
	
	cout<<"Favorita (1=Si,0=No): ";
	cin>>canciones[pos].favorita;
	
	guardarEnArchivo();
	
	cout<<"Cancion actualizada correctamente.\n";
}

void eliminar(){
	
	cargarDesdeArchivo();
	
	string codigo;
	
	cin.ignore();
	
	cout<<"Codigo de la cancion: ";
	getline(cin,codigo);
	
	int pos=buscarPorCodigo(codigo);
	
	if(pos==-1){
		
		cout<<"Cancion no encontrada.\n";
		return;
	}
	
	canciones.erase(canciones.begin()+pos);
	
	guardarEnArchivo();
	
	cout<<"Cancion eliminada correctamente.\n";
}

int main(){
	
	cargarDesdeArchivo();
	
	int opcion;
	
	do{
		
		cout<<"\n===== MENU ====="<<endl;
		cout<<"1. Crear Cancion"<<endl;
		cout<<"2. Listar Canciones"<<endl;
		cout<<"3. Buscar Cancion"<<endl;
		cout<<"4. Actualizar Cancion"<<endl;
		cout<<"5. Eliminar Cancion"<<endl;
		cout<<"6. Salir"<<endl;
		cout<<"Seleccione una opcion: ";
		cin>>opcion;
		
		switch(opcion){
			
		case 1:
			crear();
			break;
			
		case 2:
			listar();
			break;
			
		case 3:
			buscar();
			break;
			
		case 4:
			actualizar();
			break;
			
		case 5:
			eliminar();
			break;
			
		case 6:
			cout<<"Saliendo..."<<endl;
			break;
			
		default:
			cout<<"Opcion invalida.\n";
			break;
		}
		
	}while(opcion!=6);
	
	return 0;
}

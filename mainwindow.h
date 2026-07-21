#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include "cancion.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //CRUD Numero 1: Canciones
    void onCrearCancion();
    void onActualizarCancion();
    void onEliminarCancion();
    void onLimpiarFormulario();
    void onFilaCancionSeleccionada(int fila, int columna);

    // CRUD Numero 2: Categorias
    //Navegacion entre las pestañas
    void onIrACategorias();
    void onCrearCategoria();
    void onActualizarCategoria();
    void onEliminarCategoria();
    void onUsarCategoriaSeleccionada();

private:
    Ui::MainWindow *ui;

    //Datos en memoria
    std::vector<Cancion> canciones;
    std::vector<std::string> categorias;
    const std::string archivoCanciones = "canciones.txt";
    const std::string archivoCategorias = "categorias.txt";

    //Persistencia
    void cargarCanciones();
    void guardarCanciones();
    int buscarCancionPorCodigo(const std::string &codigo);

    void cargarCategorias();
    void guardarCategorias();
    int buscarCategoriaPorNombre(const std::string &nombre);

    // UI
    void configurarTabla();
    void refrescarTablaCanciones();
    void refrescarListaCategorias();
    void limpiarFormularioCancion();
};

#endif

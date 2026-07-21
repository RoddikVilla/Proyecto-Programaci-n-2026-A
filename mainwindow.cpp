#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QHeaderView>
#include <fstream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    configurarTabla();

    cargarCanciones();
    cargarCategorias();

    refrescarTablaCanciones();
    refrescarListaCategorias();

    connect(ui->btnElegirCategoria, &QPushButton::clicked, this, &MainWindow::onIrACategorias);
    connect(ui->btnCrearCancion, &QPushButton::clicked, this, &MainWindow::onCrearCancion);
    connect(ui->btnActualizarCancion, &QPushButton::clicked, this, &MainWindow::onActualizarCancion);
    connect(ui->btnEliminarCancion, &QPushButton::clicked, this, &MainWindow::onEliminarCancion);
    connect(ui->btnLimpiarCancion, &QPushButton::clicked, this, &MainWindow::onLimpiarFormulario);
    connect(ui->tablaCanciones, &QTableWidget::cellClicked, this, &MainWindow::onFilaCancionSeleccionada);

    connect(ui->btnCrearCategoria, &QPushButton::clicked, this, &MainWindow::onCrearCategoria);
    connect(ui->btnActualizarCategoria, &QPushButton::clicked, this, &MainWindow::onActualizarCategoria);
    connect(ui->btnEliminarCategoria, &QPushButton::clicked, this, &MainWindow::onEliminarCategoria);
    connect(ui->btnUsarCategoria, &QPushButton::clicked, this, &MainWindow::onUsarCategoriaSeleccionada);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::configurarTabla() {
    ui->tablaCanciones->horizontalHeader()->setStretchLastSection(true);
}


//Persistencia en el archivo.txt
void MainWindow::cargarCanciones() {
    canciones.clear();
    ifstream archivo(archivoCanciones);
    Cancion c;

    if (archivo.is_open()) {
        while (archivo >> c) {
            canciones.push_back(c);
        }
        archivo.close();
    }
}

void MainWindow::guardarCanciones() {
    ofstream archivo(archivoCanciones);
    if (archivo.is_open()) {
        for (size_t i = 0; i < canciones.size(); i++) {
            archivo << canciones[i] << endl;
        }
        archivo.close();
    }
}

int MainWindow::buscarCancionPorCodigo(const string &codigo) {
    for (size_t i = 0; i < canciones.size(); i++) {
        if (canciones[i].codigo == codigo) return static_cast<int>(i);
    }
    return -1;
}

void MainWindow::cargarCategorias() {
    categorias.clear();
    ifstream archivo(archivoCategorias);
    string linea;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (!linea.empty()) categorias.push_back(linea);
        }
        archivo.close();
    }
}

void MainWindow::guardarCategorias() {
    ofstream archivo(archivoCategorias);
    if (archivo.is_open()) {
        for (size_t i = 0; i < categorias.size(); i++) {
            archivo << categorias[i] << endl;
        }
        archivo.close();
    }
}

int MainWindow::buscarCategoriaPorNombre(const string &nombre) {
    for (size_t i = 0; i < categorias.size(); i++) {
        if (categorias[i] == nombre) return static_cast<int>(i);
    }
    return -1;
}


//Refresca la tabla del Ui
void MainWindow::refrescarTablaCanciones() {
    ui->tablaCanciones->setRowCount(0);

    for (size_t i = 0; i < canciones.size(); i++) {
        int fila = ui->tablaCanciones->rowCount();
        ui->tablaCanciones->insertRow(fila);

        const Cancion &c = canciones[i];
        ui->tablaCanciones->setItem(fila, 0, new QTableWidgetItem(QString::fromStdString(c.codigo)));
        ui->tablaCanciones->setItem(fila, 1, new QTableWidgetItem(QString::fromStdString(c.titulo)));
        ui->tablaCanciones->setItem(fila, 2, new QTableWidgetItem(QString::fromStdString(c.artista)));
        ui->tablaCanciones->setItem(fila, 3, new QTableWidgetItem(QString::fromStdString(c.genero)));
        ui->tablaCanciones->setItem(fila, 4, new QTableWidgetItem(QString::number(c.anioLanzamiento)));
        ui->tablaCanciones->setItem(fila, 5, new QTableWidgetItem(QString::number(c.duracionMinutos)));
        ui->tablaCanciones->setItem(fila, 6, new QTableWidgetItem(c.favorita ? "Si" : "No"));
    }
}

void MainWindow::refrescarListaCategorias() {
    ui->listaCategorias->clear();
    for (size_t i = 0; i < categorias.size(); i++) {
        ui->listaCategorias->addItem(QString::fromStdString(categorias[i]));
    }
}

void MainWindow::limpiarFormularioCancion() {
    ui->leCodigo->clear();
    ui->leTitulo->clear();
    ui->leArtista->clear();
    ui->leGenero->clear();
    ui->leAnio->clear();
    ui->leDuracion->clear();
    ui->chkFavorita->setChecked(false);
    ui->leCodigo->setEnabled(true);
}


//Slots: CRUD CANCIONES
void MainWindow::onCrearCancion() {
    string codigo = ui->leCodigo->text().toStdString();

    if (codigo.empty()) {
        QMessageBox::warning(this, "Falta el codigo", "Debes escribir un codigo para la cancion.");
        return;
    }

    if (buscarCancionPorCodigo(codigo) != -1) {
        QMessageBox::warning(this, "Codigo repetido", "Ya existe una cancion con ese codigo.");
        return;
    }

    Cancion c;
    c.codigo = codigo;
    c.titulo = ui->leTitulo->text().toStdString();
    c.artista = ui->leArtista->text().toStdString();
    c.genero = ui->leGenero->text().toStdString();
    c.anioLanzamiento = ui->leAnio->text().toInt();
    c.duracionMinutos = ui->leDuracion->text().toDouble();
    c.favorita = ui->chkFavorita->isChecked();

    canciones.push_back(c);
    guardarCanciones();
    refrescarTablaCanciones();
    limpiarFormularioCancion();

    QMessageBox::information(this, "Listo", "Cancion registrada correctamente.");
}

void MainWindow::onActualizarCancion() {
    string codigo = ui->leCodigo->text().toStdString();
    int pos = buscarCancionPorCodigo(codigo);

    if (pos == -1) {
        QMessageBox::warning(this, "No encontrada",
                             "Selecciona una cancion existente de la tabla para actualizarla.");
        return;
    }

    canciones[pos].titulo = ui->leTitulo->text().toStdString();
    canciones[pos].artista = ui->leArtista->text().toStdString();
    canciones[pos].genero = ui->leGenero->text().toStdString();
    canciones[pos].anioLanzamiento = ui->leAnio->text().toInt();
    canciones[pos].duracionMinutos = ui->leDuracion->text().toDouble();
    canciones[pos].favorita = ui->chkFavorita->isChecked();

    guardarCanciones();
    refrescarTablaCanciones();

    QMessageBox::information(this, "Listo", "Cancion actualizada correctamente.");
}

void MainWindow::onEliminarCancion() {
    string codigo = ui->leCodigo->text().toStdString();
    int pos = buscarCancionPorCodigo(codigo);

    if (pos == -1) {
        QMessageBox::warning(this, "No encontrada",
                             "Selecciona una cancion existente de la tabla para eliminarla.");
        return;
    }

    canciones.erase(canciones.begin() + pos);
    guardarCanciones();
    refrescarTablaCanciones();
    limpiarFormularioCancion();

    QMessageBox::information(this, "Listo", "Cancion eliminada correctamente.");
}

void MainWindow::onLimpiarFormulario() {
    limpiarFormularioCancion();
}

void MainWindow::onFilaCancionSeleccionada(int fila, int columna) {
    Q_UNUSED(columna);

    if (fila < 0 || fila >= static_cast<int>(canciones.size())) return;

    const Cancion &c = canciones[fila];
    ui->leCodigo->setText(QString::fromStdString(c.codigo));
    ui->leTitulo->setText(QString::fromStdString(c.titulo));
    ui->leArtista->setText(QString::fromStdString(c.artista));
    ui->leGenero->setText(QString::fromStdString(c.genero));
    ui->leAnio->setText(QString::number(c.anioLanzamiento));
    ui->leDuracion->setText(QString::number(c.duracionMinutos));
    ui->chkFavorita->setChecked(c.favorita);
}


//Slost: Crud 2: Categorias
//Navegacion entre Tablas
void MainWindow::onIrACategorias() {
    ui->tabs->setCurrentWidget(ui->tabCategorias);
}

void MainWindow::onCrearCategoria() {
    string nombre = ui->leNombreCategoria->text().toStdString();

    if (nombre.empty()) {
        QMessageBox::warning(this, "Falta el nombre", "Escribe un nombre para la categoria.");
        return;
    }

    if (buscarCategoriaPorNombre(nombre) != -1) {
        QMessageBox::warning(this, "Repetida", "Esa categoria ya existe.");
        return;
    }

    categorias.push_back(nombre);
    guardarCategorias();
    refrescarListaCategorias();
    ui->leNombreCategoria->clear();
}

void MainWindow::onActualizarCategoria() {
    int fila = ui->listaCategorias->currentRow();

    if (fila < 0) {
        QMessageBox::warning(this, "Nada seleccionado", "Selecciona una categoria de la lista.");
        return;
    }

    string nuevoNombre = ui->leNombreCategoria->text().toStdString();

    if (nuevoNombre.empty()) {
        QMessageBox::warning(this, "Falta el nombre", "Escribe el nuevo nombre en el cuadro de texto.");
        return;
    }

    categorias[fila] = nuevoNombre;
    guardarCategorias();
    refrescarListaCategorias();
    ui->leNombreCategoria->clear();
}

void MainWindow::onEliminarCategoria() {
    int fila = ui->listaCategorias->currentRow();

    if (fila < 0) {
        QMessageBox::warning(this, "Nada seleccionado", "Selecciona una categoria de la lista.");
        return;
    }

    categorias.erase(categorias.begin() + fila);
    guardarCategorias();
    refrescarListaCategorias();
}

void MainWindow::onUsarCategoriaSeleccionada() {
    int fila = ui->listaCategorias->currentRow();

    if (fila < 0) {
        QMessageBox::warning(this, "Nada seleccionado", "Selecciona una categoria de la lista primero.");
        return;
    }

    QString nombre = ui->listaCategorias->item(fila)->text();
    ui->leGenero->setText(nombre);

    ui->tabs->setCurrentWidget(ui->tabCanciones);
}
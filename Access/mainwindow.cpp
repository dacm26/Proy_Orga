#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setFixedSize(1370,710);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNuevo_triggered()
{

}


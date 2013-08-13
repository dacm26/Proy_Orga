/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNuevo;
    QAction *actionAbrir;
    QAction *actionGuardar;
    QAction *actionImprimir;
    QAction *actionCerrar;
    QAction *actionSalir;
    QAction *actionCrear;
    QAction *actionModificar;
    QAction *actionListar;
    QAction *actionIntroducir;
    QAction *actionBuscar;
    QAction *actionBorrar;
    QAction *actionListar_2;
    QAction *action;
    QAction *actionImportar_XML;
    QAction *actionExportar_XML;
    QAction *actionImportal_Json;
    QAction *actionExportar_Json;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuArchivos;
    QMenu *menuCampos;
    QMenu *menuRegistros;
    QMenu *menuIndices;
    QMenu *menuUtilidades;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(713, 375);
        actionNuevo = new QAction(MainWindow);
        actionNuevo->setObjectName(QStringLiteral("actionNuevo"));
        actionAbrir = new QAction(MainWindow);
        actionAbrir->setObjectName(QStringLiteral("actionAbrir"));
        actionGuardar = new QAction(MainWindow);
        actionGuardar->setObjectName(QStringLiteral("actionGuardar"));
        actionImprimir = new QAction(MainWindow);
        actionImprimir->setObjectName(QStringLiteral("actionImprimir"));
        actionCerrar = new QAction(MainWindow);
        actionCerrar->setObjectName(QStringLiteral("actionCerrar"));
        actionSalir = new QAction(MainWindow);
        actionSalir->setObjectName(QStringLiteral("actionSalir"));
        actionCrear = new QAction(MainWindow);
        actionCrear->setObjectName(QStringLiteral("actionCrear"));
        actionModificar = new QAction(MainWindow);
        actionModificar->setObjectName(QStringLiteral("actionModificar"));
        actionListar = new QAction(MainWindow);
        actionListar->setObjectName(QStringLiteral("actionListar"));
        actionIntroducir = new QAction(MainWindow);
        actionIntroducir->setObjectName(QStringLiteral("actionIntroducir"));
        actionBuscar = new QAction(MainWindow);
        actionBuscar->setObjectName(QStringLiteral("actionBuscar"));
        actionBorrar = new QAction(MainWindow);
        actionBorrar->setObjectName(QStringLiteral("actionBorrar"));
        actionListar_2 = new QAction(MainWindow);
        actionListar_2->setObjectName(QStringLiteral("actionListar_2"));
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        actionImportar_XML = new QAction(MainWindow);
        actionImportar_XML->setObjectName(QStringLiteral("actionImportar_XML"));
        actionExportar_XML = new QAction(MainWindow);
        actionExportar_XML->setObjectName(QStringLiteral("actionExportar_XML"));
        actionImportal_Json = new QAction(MainWindow);
        actionImportal_Json->setObjectName(QStringLiteral("actionImportal_Json"));
        actionExportar_Json = new QAction(MainWindow);
        actionExportar_Json->setObjectName(QStringLiteral("actionExportar_Json"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 713, 20));
        menuArchivos = new QMenu(menuBar);
        menuArchivos->setObjectName(QStringLiteral("menuArchivos"));
        menuCampos = new QMenu(menuBar);
        menuCampos->setObjectName(QStringLiteral("menuCampos"));
        menuRegistros = new QMenu(menuBar);
        menuRegistros->setObjectName(QStringLiteral("menuRegistros"));
        menuIndices = new QMenu(menuBar);
        menuIndices->setObjectName(QStringLiteral("menuIndices"));
        menuUtilidades = new QMenu(menuBar);
        menuUtilidades->setObjectName(QStringLiteral("menuUtilidades"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuArchivos->menuAction());
        menuBar->addAction(menuCampos->menuAction());
        menuBar->addAction(menuRegistros->menuAction());
        menuBar->addAction(menuUtilidades->menuAction());
        menuBar->addAction(menuIndices->menuAction());
        menuArchivos->addAction(actionNuevo);
        menuArchivos->addAction(actionAbrir);
        menuArchivos->addAction(actionGuardar);
        menuArchivos->addAction(actionImprimir);
        menuArchivos->addAction(actionCerrar);
        menuArchivos->addAction(actionSalir);
        menuCampos->addAction(actionCrear);
        menuCampos->addAction(actionModificar);
        menuCampos->addAction(actionListar);
        menuRegistros->addAction(actionIntroducir);
        menuRegistros->addAction(actionBuscar);
        menuRegistros->addAction(actionBorrar);
        menuRegistros->addAction(actionListar_2);
        menuRegistros->addAction(action);
        menuUtilidades->addAction(actionImportar_XML);
        menuUtilidades->addAction(actionExportar_XML);
        menuUtilidades->addAction(actionImportal_Json);
        menuUtilidades->addAction(actionExportar_Json);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Access dacm26", 0));
        actionNuevo->setText(QApplication::translate("MainWindow", "Nuevo", 0));
        actionAbrir->setText(QApplication::translate("MainWindow", "Abrir", 0));
        actionGuardar->setText(QApplication::translate("MainWindow", "Guardar", 0));
        actionImprimir->setText(QApplication::translate("MainWindow", "Imprimir", 0));
        actionCerrar->setText(QApplication::translate("MainWindow", "Cerrar ", 0));
        actionSalir->setText(QApplication::translate("MainWindow", "Salir", 0));
        actionCrear->setText(QApplication::translate("MainWindow", "Crear", 0));
        actionModificar->setText(QApplication::translate("MainWindow", "Modificar", 0));
        actionListar->setText(QApplication::translate("MainWindow", "Listar", 0));
        actionIntroducir->setText(QApplication::translate("MainWindow", "Introducir", 0));
        actionBuscar->setText(QApplication::translate("MainWindow", "Buscar", 0));
        actionBorrar->setText(QApplication::translate("MainWindow", "Borrar", 0));
        actionListar_2->setText(QApplication::translate("MainWindow", "Listar", 0));
        action->setText(QApplication::translate("MainWindow", "Cruzar", 0));
        actionImportar_XML->setText(QApplication::translate("MainWindow", "Importar XML", 0));
        actionExportar_XML->setText(QApplication::translate("MainWindow", "Exportar XML", 0));
        actionImportal_Json->setText(QApplication::translate("MainWindow", "Importar Json", 0));
        actionExportar_Json->setText(QApplication::translate("MainWindow", "Exportar Json", 0));
        menuArchivos->setTitle(QApplication::translate("MainWindow", "Archivos", 0));
        menuCampos->setTitle(QApplication::translate("MainWindow", "Campos", 0));
        menuRegistros->setTitle(QApplication::translate("MainWindow", "Registros", 0));
        menuIndices->setTitle(QApplication::translate("MainWindow", "Indices", 0));
        menuUtilidades->setTitle(QApplication::translate("MainWindow", "Utilidades", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

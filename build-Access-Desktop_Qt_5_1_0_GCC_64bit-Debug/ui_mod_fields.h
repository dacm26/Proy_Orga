/********************************************************************************
** Form generated from reading UI file 'mod_fields.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOD_FIELDS_H
#define UI_MOD_FIELDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mod_fields
{
public:
    QLabel *mod_label;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *mod_ok;
    QSpinBox *sp_mod;

    void setupUi(QDialog *mod_fields)
    {
        if (mod_fields->objectName().isEmpty())
            mod_fields->setObjectName(QStringLiteral("mod_fields"));
        mod_fields->resize(255, 445);
        mod_label = new QLabel(mod_fields);
        mod_label->setObjectName(QStringLiteral("mod_label"));
        mod_label->setGeometry(QRect(40, 10, 181, 361));
        widget = new QWidget(mod_fields);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 390, 201, 41));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        mod_ok = new QPushButton(widget);
        mod_ok->setObjectName(QStringLiteral("mod_ok"));

        horizontalLayout->addWidget(mod_ok);

        sp_mod = new QSpinBox(widget);
        sp_mod->setObjectName(QStringLiteral("sp_mod"));

        horizontalLayout->addWidget(sp_mod);


        retranslateUi(mod_fields);

        QMetaObject::connectSlotsByName(mod_fields);
    } // setupUi

    void retranslateUi(QDialog *mod_fields)
    {
        mod_fields->setWindowTitle(QApplication::translate("mod_fields", "Seleccione el Campo a Modificar", 0));
        mod_label->setText(QString());
        mod_ok->setText(QApplication::translate("mod_fields", "Ok", 0));
    } // retranslateUi

};

namespace Ui {
    class mod_fields: public Ui_mod_fields {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOD_FIELDS_H

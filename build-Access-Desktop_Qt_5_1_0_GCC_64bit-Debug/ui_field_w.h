/********************************************************************************
** Form generated from reading UI file 'field_w.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIELD_W_H
#define UI_FIELD_W_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_field_W
{
public:
    QCheckBox *field_key;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *field_add;
    QPushButton *field_clear;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *field_name;
    QComboBox *field_type;
    QSpinBox *field_length;
    QSpinBox *field_decimal;

    void setupUi(QDialog *field_W)
    {
        if (field_W->objectName().isEmpty())
            field_W->setObjectName(QStringLiteral("field_W"));
        field_W->resize(416, 365);
        field_key = new QCheckBox(field_W);
        field_key->setObjectName(QStringLiteral("field_key"));
        field_key->setGeometry(QRect(150, 240, 85, 21));
        layoutWidget = new QWidget(field_W);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 20, 91, 251));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        layoutWidget1 = new QWidget(field_W);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(50, 310, 301, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        field_add = new QPushButton(layoutWidget1);
        field_add->setObjectName(QStringLiteral("field_add"));

        horizontalLayout->addWidget(field_add);

        field_clear = new QPushButton(layoutWidget1);
        field_clear->setObjectName(QStringLiteral("field_clear"));

        horizontalLayout->addWidget(field_clear);

        layoutWidget2 = new QWidget(field_W);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(150, 20, 181, 211));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        field_name = new QLineEdit(layoutWidget2);
        field_name->setObjectName(QStringLiteral("field_name"));

        verticalLayout_2->addWidget(field_name);

        field_type = new QComboBox(layoutWidget2);
        field_type->setObjectName(QStringLiteral("field_type"));

        verticalLayout_2->addWidget(field_type);

        field_length = new QSpinBox(layoutWidget2);
        field_length->setObjectName(QStringLiteral("field_length"));
        field_length->setMinimum(1);

        verticalLayout_2->addWidget(field_length);

        field_decimal = new QSpinBox(layoutWidget2);
        field_decimal->setObjectName(QStringLiteral("field_decimal"));
        field_decimal->setMinimum(1);

        verticalLayout_2->addWidget(field_decimal);

        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        field_key->raise();

        retranslateUi(field_W);

        QMetaObject::connectSlotsByName(field_W);
    } // setupUi

    void retranslateUi(QDialog *field_W)
    {
        field_W->setWindowTitle(QApplication::translate("field_W", "Add Fields", 0));
        field_key->setText(QString());
        label->setText(QApplication::translate("field_W", "Nombre", 0));
        label_2->setText(QApplication::translate("field_W", "Tipo", 0));
        label_3->setText(QApplication::translate("field_W", "Longitud", 0));
        label_4->setText(QApplication::translate("field_W", "Decimal", 0));
        label_5->setText(QApplication::translate("field_W", "Llave", 0));
        field_add->setText(QApplication::translate("field_W", "Agregar Campo", 0));
        field_clear->setText(QApplication::translate("field_W", "Limpiar", 0));
    } // retranslateUi

};

namespace Ui {
    class field_W: public Ui_field_W {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIELD_W_H

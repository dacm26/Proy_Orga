/********************************************************************************
** Form generated from reading UI file 'mfields_w.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MFIELDS_W_H
#define UI_MFIELDS_W_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mFields_w
{
public:
    QPushButton *mod_ok;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *mod_nombre;
    QComboBox *mod_tipo;
    QSpinBox *mod_length;
    QSpinBox *mod_decimal;
    QCheckBox *mod_key;

    void setupUi(QDialog *mFields_w)
    {
        if (mFields_w->objectName().isEmpty())
            mFields_w->setObjectName(QStringLiteral("mFields_w"));
        mFields_w->resize(398, 427);
        mod_ok = new QPushButton(mFields_w);
        mod_ok->setObjectName(QStringLiteral("mod_ok"));
        mod_ok->setGeometry(QRect(60, 360, 259, 23));
        widget = new QWidget(mFields_w);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(60, 70, 111, 261));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        widget1 = new QWidget(mFields_w);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(170, 70, 161, 261));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        mod_nombre = new QLineEdit(widget1);
        mod_nombre->setObjectName(QStringLiteral("mod_nombre"));

        verticalLayout_2->addWidget(mod_nombre);

        mod_tipo = new QComboBox(widget1);
        mod_tipo->setObjectName(QStringLiteral("mod_tipo"));

        verticalLayout_2->addWidget(mod_tipo);

        mod_length = new QSpinBox(widget1);
        mod_length->setObjectName(QStringLiteral("mod_length"));
        mod_length->setMinimum(1);

        verticalLayout_2->addWidget(mod_length);

        mod_decimal = new QSpinBox(widget1);
        mod_decimal->setObjectName(QStringLiteral("mod_decimal"));
        mod_decimal->setMinimum(1);

        verticalLayout_2->addWidget(mod_decimal);

        mod_key = new QCheckBox(widget1);
        mod_key->setObjectName(QStringLiteral("mod_key"));

        verticalLayout_2->addWidget(mod_key);


        retranslateUi(mFields_w);

        QMetaObject::connectSlotsByName(mFields_w);
    } // setupUi

    void retranslateUi(QDialog *mFields_w)
    {
        mFields_w->setWindowTitle(QApplication::translate("mFields_w", "Modificar Campos", 0));
        mod_ok->setText(QApplication::translate("mFields_w", "Hecho", 0));
        label->setText(QApplication::translate("mFields_w", "Nombre", 0));
        label_2->setText(QApplication::translate("mFields_w", "Tipo", 0));
        label_3->setText(QApplication::translate("mFields_w", "Longitud", 0));
        label_4->setText(QApplication::translate("mFields_w", "Decimal", 0));
        label_5->setText(QApplication::translate("mFields_w", "Key", 0));
        mod_key->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class mFields_w: public Ui_mFields_w {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MFIELDS_W_H

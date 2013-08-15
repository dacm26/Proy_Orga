/****************************************************************************
** Meta object code from reading C++ file 'mfields_w.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Access/mfields_w.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mfields_w.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_mFields_w_t {
    QByteArrayData data[8];
    char stringdata[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_mFields_w_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_mFields_w_t qt_meta_stringdata_mFields_w = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 31),
QT_MOC_LITERAL(2, 42, 0),
QT_MOC_LITERAL(3, 43, 5),
QT_MOC_LITERAL(4, 49, 26),
QT_MOC_LITERAL(5, 76, 4),
QT_MOC_LITERAL(6, 81, 29),
QT_MOC_LITERAL(7, 111, 17)
    },
    "mFields_w\0on_mod_tipo_currentIndexChanged\0"
    "\0index\0on_mod_length_valueChanged\0"
    "arg1\0on_mod_nombre_editingFinished\0"
    "on_mod_ok_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mFields_w[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08,
       4,    1,   37,    2, 0x08,
       6,    0,   40,    2, 0x08,
       7,    0,   41,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void mFields_w::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mFields_w *_t = static_cast<mFields_w *>(_o);
        switch (_id) {
        case 0: _t->on_mod_tipo_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_mod_length_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_mod_nombre_editingFinished(); break;
        case 3: _t->on_mod_ok_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject mFields_w::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_mFields_w.data,
      qt_meta_data_mFields_w,  qt_static_metacall, 0, 0}
};


const QMetaObject *mFields_w::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mFields_w::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mFields_w.stringdata))
        return static_cast<void*>(const_cast< mFields_w*>(this));
    return QDialog::qt_metacast(_clname);
}

int mFields_w::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'field_w.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Access/field_w.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'field_w.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_field_W_t {
    QByteArrayData data[8];
    char stringdata[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_field_W_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_field_W_t qt_meta_stringdata_field_W = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 33),
QT_MOC_LITERAL(2, 42, 0),
QT_MOC_LITERAL(3, 43, 5),
QT_MOC_LITERAL(4, 49, 22),
QT_MOC_LITERAL(5, 72, 20),
QT_MOC_LITERAL(6, 93, 28),
QT_MOC_LITERAL(7, 122, 4)
    },
    "field_W\0on_field_type_currentIndexChanged\0"
    "\0index\0on_field_clear_clicked\0"
    "on_field_add_clicked\0on_field_length_valueChanged\0"
    "arg1\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_field_W[] = {

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
       4,    0,   37,    2, 0x08,
       5,    0,   38,    2, 0x08,
       6,    1,   39,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void field_W::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        field_W *_t = static_cast<field_W *>(_o);
        switch (_id) {
        case 0: _t->on_field_type_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_field_clear_clicked(); break;
        case 2: _t->on_field_add_clicked(); break;
        case 3: _t->on_field_length_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject field_W::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_field_W.data,
      qt_meta_data_field_W,  qt_static_metacall, 0, 0}
};


const QMetaObject *field_W::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *field_W::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_field_W.stringdata))
        return static_cast<void*>(const_cast< field_W*>(this));
    return QDialog::qt_metacast(_clname);
}

int field_W::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

/****************************************************************************
** Meta object code from reading C++ file 'biglietto_view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "biglietto_view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'biglietto_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Biglietto_View_t {
    QByteArrayData data[15];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Biglietto_View_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Biglietto_View_t qt_meta_stringdata_Biglietto_View = {
    {
QT_MOC_LITERAL(0, 0, 14), // "Biglietto_View"
QT_MOC_LITERAL(1, 15, 10), // "showSearch"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "showSalaView"
QT_MOC_LITERAL(4, 40, 13), // "getNameSelect"
QT_MOC_LITERAL(5, 54, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(6, 71, 4), // "item"
QT_MOC_LITERAL(7, 76, 11), // "popolaLista"
QT_MOC_LITERAL(8, 88, 5), // "index"
QT_MOC_LITERAL(9, 94, 20), // "selectFromListSearch"
QT_MOC_LITERAL(10, 115, 10), // "resizeSala"
QT_MOC_LITERAL(11, 126, 8), // "resizeMe"
QT_MOC_LITERAL(12, 135, 12), // "hideSalaView"
QT_MOC_LITERAL(13, 148, 20), // "setUtilitySearchText"
QT_MOC_LITERAL(14, 169, 1) // "s"

    },
    "Biglietto_View\0showSearch\0\0showSalaView\0"
    "getNameSelect\0QListWidgetItem*\0item\0"
    "popolaLista\0index\0selectFromListSearch\0"
    "resizeSala\0resizeMe\0hideSalaView\0"
    "setUtilitySearchText\0s"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Biglietto_View[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    1,   61,    2, 0x08 /* Private */,
       7,    1,   64,    2, 0x08 /* Private */,
       9,    1,   67,    2, 0x08 /* Private */,
      10,    0,   70,    2, 0x0a /* Public */,
      11,    0,   71,    2, 0x0a /* Public */,
      12,    0,   72,    2, 0x0a /* Public */,
      13,    1,   73,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,

       0        // eod
};

void Biglietto_View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Biglietto_View *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showSearch(); break;
        case 1: _t->showSalaView(); break;
        case 2: _t->getNameSelect((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->popolaLista((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->selectFromListSearch((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->resizeSala(); break;
        case 6: _t->resizeMe(); break;
        case 7: _t->hideSalaView(); break;
        case 8: _t->setUtilitySearchText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Biglietto_View::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Biglietto_View.data,
    qt_meta_data_Biglietto_View,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Biglietto_View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Biglietto_View::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Biglietto_View.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Biglietto_View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

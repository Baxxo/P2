/****************************************************************************
** Meta object code from reading C++ file 'famiglia_view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "famiglia_view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'famiglia_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Famiglia_View_t {
    QByteArrayData data[9];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Famiglia_View_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Famiglia_View_t qt_meta_stringdata_Famiglia_View = {
    {
QT_MOC_LITERAL(0, 0, 13), // "Famiglia_View"
QT_MOC_LITERAL(1, 14, 8), // "resizeMe"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 16), // "cleanUtilityText"
QT_MOC_LITERAL(4, 41, 15), // "cleanTextFamily"
QT_MOC_LITERAL(5, 57, 15), // "cleanTextSearch"
QT_MOC_LITERAL(6, 73, 19), // "addUtenteToFamiglia"
QT_MOC_LITERAL(7, 93, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(8, 110, 4) // "item"

    },
    "Famiglia_View\0resizeMe\0\0cleanUtilityText\0"
    "cleanTextFamily\0cleanTextSearch\0"
    "addUtenteToFamiglia\0QListWidgetItem*\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Famiglia_View[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    1,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void Famiglia_View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Famiglia_View *_t = static_cast<Famiglia_View *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resizeMe(); break;
        case 1: _t->cleanUtilityText(); break;
        case 2: _t->cleanTextFamily(); break;
        case 3: _t->cleanTextSearch(); break;
        case 4: _t->addUtenteToFamiglia((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Famiglia_View::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Famiglia_View.data,
      qt_meta_data_Famiglia_View,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Famiglia_View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Famiglia_View::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Famiglia_View.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Famiglia_View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

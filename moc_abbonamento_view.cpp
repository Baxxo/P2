/****************************************************************************
** Meta object code from reading C++ file 'abbonamento_view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "abbonamento_view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abbonamento_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Abbonamento_view_t {
    QByteArrayData data[11];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Abbonamento_view_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Abbonamento_view_t qt_meta_stringdata_Abbonamento_view = {
    {
QT_MOC_LITERAL(0, 0, 16), // "Abbonamento_view"
QT_MOC_LITERAL(1, 17, 15), // "showAbbonamento"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 17), // "showAbbFamiglaire"
QT_MOC_LITERAL(4, 52, 17), // "createAbbonamento"
QT_MOC_LITERAL(5, 70, 8), // "resizeMe"
QT_MOC_LITERAL(6, 79, 15), // "clickListUtenti"
QT_MOC_LITERAL(7, 95, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(8, 112, 4), // "item"
QT_MOC_LITERAL(9, 117, 17), // "clickListFamiglie"
QT_MOC_LITERAL(10, 135, 16) // "clearUtilityText"

    },
    "Abbonamento_view\0showAbbonamento\0\0"
    "showAbbFamiglaire\0createAbbonamento\0"
    "resizeMe\0clickListUtenti\0QListWidgetItem*\0"
    "item\0clickListFamiglie\0clearUtilityText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Abbonamento_view[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    1,   53,    2, 0x08 /* Private */,
       9,    1,   56,    2, 0x08 /* Private */,
      10,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

       0        // eod
};

void Abbonamento_view::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Abbonamento_view *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showAbbonamento(); break;
        case 1: _t->showAbbFamiglaire(); break;
        case 2: _t->createAbbonamento(); break;
        case 3: _t->resizeMe(); break;
        case 4: _t->clickListUtenti((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->clickListFamiglie((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->clearUtilityText(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Abbonamento_view::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Abbonamento_view.data,
    qt_meta_data_Abbonamento_view,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Abbonamento_view::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Abbonamento_view::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Abbonamento_view.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Abbonamento_view::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

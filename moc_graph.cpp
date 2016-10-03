/****************************************************************************
** Meta object code from reading C++ file 'graph.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Wiring/graph.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graph.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Graph_t {
    QByteArrayData data[25];
    char stringdata[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Graph_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Graph_t qt_meta_stringdata_Graph = {
    {
QT_MOC_LITERAL(0, 0, 5),
QT_MOC_LITERAL(1, 6, 17),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 14),
QT_MOC_LITERAL(4, 40, 11),
QT_MOC_LITERAL(5, 52, 14),
QT_MOC_LITERAL(6, 67, 9),
QT_MOC_LITERAL(7, 77, 11),
QT_MOC_LITERAL(8, 89, 7),
QT_MOC_LITERAL(9, 97, 3),
QT_MOC_LITERAL(10, 101, 3),
QT_MOC_LITERAL(11, 105, 4),
QT_MOC_LITERAL(12, 110, 5),
QT_MOC_LITERAL(13, 116, 12),
QT_MOC_LITERAL(14, 129, 10),
QT_MOC_LITERAL(15, 140, 10),
QT_MOC_LITERAL(16, 151, 4),
QT_MOC_LITERAL(17, 156, 13),
QT_MOC_LITERAL(18, 170, 11),
QT_MOC_LITERAL(19, 182, 21),
QT_MOC_LITERAL(20, 204, 5),
QT_MOC_LITERAL(21, 210, 14),
QT_MOC_LITERAL(22, 225, 12),
QT_MOC_LITERAL(23, 238, 16),
QT_MOC_LITERAL(24, 255, 17)
    },
    "Graph\0animationFinished\0\0loadVertexFile\0"
    "loadAdjFile\0saveVertexFile\0addVertex\0"
    "addBackEdge\0addEdge\0del\0cut\0copy\0paste\0"
    "bringToFront\0sendToBack\0properties\0"
    "help\0updateActions\0isQualified\0"
    "prepareEulerAnimation\0reset\0completeDialog\0"
    "connectGraph\0prepareEulerTour\0"
    "allAlgorithmsDone\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Graph[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  129,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       3,    0,  130,    2, 0x08,
       4,    0,  131,    2, 0x08,
       5,    0,  132,    2, 0x08,
       6,    0,  133,    2, 0x08,
       7,    0,  134,    2, 0x08,
       8,    0,  135,    2, 0x08,
       9,    0,  136,    2, 0x08,
      10,    0,  137,    2, 0x08,
      11,    0,  138,    2, 0x08,
      12,    0,  139,    2, 0x08,
      13,    0,  140,    2, 0x08,
      14,    0,  141,    2, 0x08,
      15,    0,  142,    2, 0x08,
      16,    0,  143,    2, 0x08,
      17,    0,  144,    2, 0x08,
      18,    0,  145,    2, 0x08,
      19,    0,  146,    2, 0x08,
      20,    0,  147,    2, 0x08,
      21,    0,  148,    2, 0x08,
      22,    0,  149,    2, 0x08,
      23,    0,  150,    2, 0x08,
      24,    0,  151,    2, 0x08,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Graph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Graph *_t = static_cast<Graph *>(_o);
        switch (_id) {
        case 0: _t->animationFinished(); break;
        case 1: _t->loadVertexFile(); break;
        case 2: _t->loadAdjFile(); break;
        case 3: _t->saveVertexFile(); break;
        case 4: _t->addVertex(); break;
        case 5: _t->addBackEdge(); break;
        case 6: _t->addEdge(); break;
        case 7: _t->del(); break;
        case 8: _t->cut(); break;
        case 9: _t->copy(); break;
        case 10: _t->paste(); break;
        case 11: _t->bringToFront(); break;
        case 12: _t->sendToBack(); break;
        case 13: _t->properties(); break;
        case 14: _t->help(); break;
        case 15: _t->updateActions(); break;
        case 16: _t->isQualified(); break;
        case 17: _t->prepareEulerAnimation(); break;
        case 18: _t->reset(); break;
        case 19: _t->completeDialog(); break;
        case 20: _t->connectGraph(); break;
        case 21: _t->prepareEulerTour(); break;
        case 22: _t->allAlgorithmsDone(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Graph::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Graph::animationFinished)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Graph::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Graph.data,
      qt_meta_data_Graph,  qt_static_metacall, 0, 0}
};


const QMetaObject *Graph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Graph::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Graph.stringdata))
        return static_cast<void*>(const_cast< Graph*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Graph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void Graph::animationFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

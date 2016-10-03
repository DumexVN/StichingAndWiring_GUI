/****************************************************************************
** Meta object code from reading C++ file 'algorithmthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Wiring/algorithmthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'algorithmthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AlgorithmThread_t {
    QByteArrayData data[5];
    char stringdata[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AlgorithmThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AlgorithmThread_t qt_meta_stringdata_AlgorithmThread = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 16),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 7),
QT_MOC_LITERAL(4, 42, 17)
    },
    "AlgorithmThread\0algorithmStarted\0\0"
    "message\0allAlgorithmsDone\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AlgorithmThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x05,
       4,    0,   27,    2, 0x05,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

       0        // eod
};

void AlgorithmThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AlgorithmThread *_t = static_cast<AlgorithmThread *>(_o);
        switch (_id) {
        case 0: _t->algorithmStarted((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->allAlgorithmsDone(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AlgorithmThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AlgorithmThread::algorithmStarted)) {
                *result = 0;
            }
        }
        {
            typedef void (AlgorithmThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AlgorithmThread::allAlgorithmsDone)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject AlgorithmThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_AlgorithmThread.data,
      qt_meta_data_AlgorithmThread,  qt_static_metacall, 0, 0}
};


const QMetaObject *AlgorithmThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AlgorithmThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AlgorithmThread.stringdata))
        return static_cast<void*>(const_cast< AlgorithmThread*>(this));
    return QThread::qt_metacast(_clname);
}

int AlgorithmThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void AlgorithmThread::algorithmStarted(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AlgorithmThread::allAlgorithmsDone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE

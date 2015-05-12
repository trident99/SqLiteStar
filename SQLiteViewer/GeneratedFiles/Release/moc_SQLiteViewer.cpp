/****************************************************************************
** Meta object code from reading C++ file 'SQLiteViewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SQLiteViewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SQLiteViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SQLiteViewer_t {
    QByteArrayData data[19];
    char stringdata[318];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SQLiteViewer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SQLiteViewer_t qt_meta_stringdata_SQLiteViewer = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SQLiteViewer"
QT_MOC_LITERAL(1, 13, 10), // "OnFileOpen"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "OnFileClose"
QT_MOC_LITERAL(4, 37, 17), // "OnShowTable_Click"
QT_MOC_LITERAL(5, 55, 17), // "OnHideTable_Click"
QT_MOC_LITERAL(6, 73, 17), // "OnUpdateAll_Click"
QT_MOC_LITERAL(7, 91, 17), // "OnCommitAll_Click"
QT_MOC_LITERAL(8, 109, 16), // "OnCreateDemoDB01"
QT_MOC_LITERAL(9, 126, 16), // "OnCreateDemoDB02"
QT_MOC_LITERAL(10, 143, 16), // "OnCreateDemoDB03"
QT_MOC_LITERAL(11, 160, 13), // "OnSelectTable"
QT_MOC_LITERAL(12, 174, 5), // "index"
QT_MOC_LITERAL(13, 180, 17), // "OnAddRecord_Click"
QT_MOC_LITERAL(14, 198, 20), // "OnDeleteRecord_Click"
QT_MOC_LITERAL(15, 219, 24), // "OnDeleteAllRecords_Click"
QT_MOC_LITERAL(16, 244, 22), // "OnUnDeleteRecord_Click"
QT_MOC_LITERAL(17, 267, 26), // "OnUnDeleteAllRecords_Click"
QT_MOC_LITERAL(18, 294, 23) // "OnEditField_DoubleClick"

    },
    "SQLiteViewer\0OnFileOpen\0\0OnFileClose\0"
    "OnShowTable_Click\0OnHideTable_Click\0"
    "OnUpdateAll_Click\0OnCommitAll_Click\0"
    "OnCreateDemoDB01\0OnCreateDemoDB02\0"
    "OnCreateDemoDB03\0OnSelectTable\0index\0"
    "OnAddRecord_Click\0OnDeleteRecord_Click\0"
    "OnDeleteAllRecords_Click\0"
    "OnUnDeleteRecord_Click\0"
    "OnUnDeleteAllRecords_Click\0"
    "OnEditField_DoubleClick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SQLiteViewer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    0,   95,    2, 0x0a /* Public */,
       4,    0,   96,    2, 0x0a /* Public */,
       5,    0,   97,    2, 0x0a /* Public */,
       6,    0,   98,    2, 0x0a /* Public */,
       7,    0,   99,    2, 0x0a /* Public */,
       8,    0,  100,    2, 0x0a /* Public */,
       9,    0,  101,    2, 0x0a /* Public */,
      10,    0,  102,    2, 0x0a /* Public */,
      11,    1,  103,    2, 0x0a /* Public */,
      13,    0,  106,    2, 0x0a /* Public */,
      14,    0,  107,    2, 0x0a /* Public */,
      15,    0,  108,    2, 0x0a /* Public */,
      16,    0,  109,    2, 0x0a /* Public */,
      17,    0,  110,    2, 0x0a /* Public */,
      18,    1,  111,    2, 0x0a /* Public */,

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
    QMetaType::Void, QMetaType::QModelIndex,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   12,

       0        // eod
};

void SQLiteViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SQLiteViewer *_t = static_cast<SQLiteViewer *>(_o);
        switch (_id) {
        case 0: _t->OnFileOpen(); break;
        case 1: _t->OnFileClose(); break;
        case 2: _t->OnShowTable_Click(); break;
        case 3: _t->OnHideTable_Click(); break;
        case 4: _t->OnUpdateAll_Click(); break;
        case 5: _t->OnCommitAll_Click(); break;
        case 6: _t->OnCreateDemoDB01(); break;
        case 7: _t->OnCreateDemoDB02(); break;
        case 8: _t->OnCreateDemoDB03(); break;
        case 9: _t->OnSelectTable((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 10: _t->OnAddRecord_Click(); break;
        case 11: _t->OnDeleteRecord_Click(); break;
        case 12: _t->OnDeleteAllRecords_Click(); break;
        case 13: _t->OnUnDeleteRecord_Click(); break;
        case 14: _t->OnUnDeleteAllRecords_Click(); break;
        case 15: _t->OnEditField_DoubleClick((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject SQLiteViewer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SQLiteViewer.data,
      qt_meta_data_SQLiteViewer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SQLiteViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SQLiteViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SQLiteViewer.stringdata))
        return static_cast<void*>(const_cast< SQLiteViewer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SQLiteViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

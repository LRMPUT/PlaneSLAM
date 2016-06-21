/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../g2o/apps/g2o_viewer/main_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      42,   11,   11,   11, 0x0a,
      72,   11,   11,   11, 0x0a,
     102,   11,   11,   11, 0x0a,
     144,   11,   11,   11, 0x0a,
     188,   11,   11,   11, 0x0a,
     224,   11,   11,   11, 0x0a,
     265,   11,   11,   11, 0x0a,
     308,   11,   11,   11, 0x0a,
     351,   11,   11,   11, 0x0a,
     376,   11,   11,   11, 0x0a,
     405,   11,   11,   11, 0x0a,
     429,   11,   11,   11, 0x0a,
     455,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_actionLoad_triggered(bool)\0"
    "on_actionSave_triggered(bool)\0"
    "on_actionQuit_triggered(bool)\0"
    "on_actionWhite_Background_triggered(bool)\0"
    "on_actionDefault_Background_triggered(bool)\0"
    "on_actionProperties_triggered(bool)\0"
    "on_actionSave_Screenshot_triggered(bool)\0"
    "on_actionLoad_Viewer_State_triggered(bool)\0"
    "on_actionSave_Viewer_State_triggered(bool)\0"
    "on_btnOptimize_clicked()\0"
    "on_btnInitialGuess_clicked()\0"
    "on_btnSetZero_clicked()\0"
    "on_btnForceStop_clicked()\0"
    "on_btnOptimizerParamaters_clicked()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_actionLoad_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_actionSave_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_actionQuit_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_actionWhite_Background_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_actionDefault_Background_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_actionProperties_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_actionSave_Screenshot_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_actionLoad_Viewer_State_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_actionSave_Viewer_State_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_btnOptimize_clicked(); break;
        case 10: _t->on_btnInitialGuess_clicked(); break;
        case 11: _t->on_btnSetZero_clicked(); break;
        case 12: _t->on_btnForceStop_clicked(); break;
        case 13: _t->on_btnOptimizerParamaters_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Ui::BaseMainWindow"))
        return static_cast< Ui::BaseMainWindow*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'ExecutionEngine.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/controllers/ExecutionEngine.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ExecutionEngine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15ExecutionEngineE_t {};
} // unnamed namespace

template <> constexpr inline auto ExecutionEngine::qt_create_metaobjectdata<qt_meta_tag_ZN15ExecutionEngineE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ExecutionEngine",
        "runningChanged",
        "",
        "progressChanged",
        "taskFinished",
        "filePath",
        "actionName",
        "success",
        "message",
        "executionFinished",
        "startExecution",
        "QList<FileItem>",
        "items",
        "QVariantMap",
        "customCommandsMap",
        "cancelExecution",
        "exportLogToCsv",
        "targetCsvPath",
        "isRunning",
        "totalTasks",
        "completedTasks",
        "progressFraction"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'runningChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'progressChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'taskFinished'
        QtMocHelpers::SignalData<void(const QString &, const QString &, bool, const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 }, { QMetaType::QString, 6 }, { QMetaType::Bool, 7 }, { QMetaType::QString, 8 },
        }}),
        // Signal 'executionFinished'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'startExecution'
        QtMocHelpers::MethodData<void(const QList<FileItem> &, const QVariantMap &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 12 }, { 0x80000000 | 13, 14 },
        }}),
        // Method 'cancelExecution'
        QtMocHelpers::MethodData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'exportLogToCsv'
        QtMocHelpers::MethodData<bool(const QString &)>(16, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 17 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'isRunning'
        QtMocHelpers::PropertyData<bool>(18, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'totalTasks'
        QtMocHelpers::PropertyData<int>(19, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'completedTasks'
        QtMocHelpers::PropertyData<int>(20, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'progressFraction'
        QtMocHelpers::PropertyData<double>(21, QMetaType::Double, QMC::DefaultPropertyFlags, 1),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ExecutionEngine, qt_meta_tag_ZN15ExecutionEngineE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ExecutionEngine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15ExecutionEngineE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15ExecutionEngineE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15ExecutionEngineE_t>.metaTypes,
    nullptr
} };

void ExecutionEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ExecutionEngine *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->runningChanged(); break;
        case 1: _t->progressChanged(); break;
        case 2: _t->taskFinished((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4]))); break;
        case 3: _t->executionFinished(); break;
        case 4: _t->startExecution((*reinterpret_cast<std::add_pointer_t<QList<FileItem>>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[2]))); break;
        case 5: _t->cancelExecution(); break;
        case 6: { bool _r = _t->exportLogToCsv((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ExecutionEngine::*)()>(_a, &ExecutionEngine::runningChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExecutionEngine::*)()>(_a, &ExecutionEngine::progressChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExecutionEngine::*)(const QString & , const QString & , bool , const QString & )>(_a, &ExecutionEngine::taskFinished, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExecutionEngine::*)()>(_a, &ExecutionEngine::executionFinished, 3))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->isRunning(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->totalTasks(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->completedTasks(); break;
        case 3: *reinterpret_cast<double*>(_v) = _t->progressFraction(); break;
        default: break;
        }
    }
}

const QMetaObject *ExecutionEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExecutionEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15ExecutionEngineE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ExecutionEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ExecutionEngine::runningChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ExecutionEngine::progressChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ExecutionEngine::taskFinished(const QString & _t1, const QString & _t2, bool _t3, const QString & _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3, _t4);
}

// SIGNAL 3
void ExecutionEngine::executionFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP

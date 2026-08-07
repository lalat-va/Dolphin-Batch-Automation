/****************************************************************************
** Meta object code from reading C++ file 'CustomCommandManager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/controllers/CustomCommandManager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CustomCommandManager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN20CustomCommandManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto CustomCommandManager::qt_create_metaobjectdata<qt_meta_tag_ZN20CustomCommandManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CustomCommandManager",
        "commandsChanged",
        "",
        "savedCommandNames",
        "getCommandDetails",
        "QVariantMap",
        "name",
        "saveCustomCommand",
        "title",
        "commandStr",
        "createAsNewIfModified",
        "deleteCustomCommand",
        "composeOptionA",
        "cmd",
        "attrs",
        "dest",
        "composeOptionB",
        "templateStr",
        "allCommands"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'commandsChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'savedCommandNames'
        QtMocHelpers::MethodData<QStringList() const>(3, 2, QMC::AccessPublic, QMetaType::QStringList),
        // Method 'getCommandDetails'
        QtMocHelpers::MethodData<QVariantMap(const QString &) const>(4, 2, QMC::AccessPublic, 0x80000000 | 5, {{
            { QMetaType::QString, 6 },
        }}),
        // Method 'saveCustomCommand'
        QtMocHelpers::MethodData<bool(const QString &, const QString &, bool)>(7, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 8 }, { QMetaType::QString, 9 }, { QMetaType::Bool, 10 },
        }}),
        // Method 'saveCustomCommand'
        QtMocHelpers::MethodData<bool(const QString &, const QString &)>(7, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Bool, {{
            { QMetaType::QString, 8 }, { QMetaType::QString, 9 },
        }}),
        // Method 'deleteCustomCommand'
        QtMocHelpers::MethodData<bool(const QString &)>(11, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 8 },
        }}),
        // Method 'composeOptionA'
        QtMocHelpers::MethodData<QString(const QString &, const QString &, const QString &) const>(12, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 13 }, { QMetaType::QString, 14 }, { QMetaType::QString, 15 },
        }}),
        // Method 'composeOptionB'
        QtMocHelpers::MethodData<QString(const QString &) const>(16, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 17 },
        }}),
        // Method 'allCommands'
        QtMocHelpers::MethodData<QVariantMap() const>(18, 2, QMC::AccessPublic, 0x80000000 | 5),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CustomCommandManager, qt_meta_tag_ZN20CustomCommandManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CustomCommandManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20CustomCommandManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20CustomCommandManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN20CustomCommandManagerE_t>.metaTypes,
    nullptr
} };

void CustomCommandManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CustomCommandManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->commandsChanged(); break;
        case 1: { QStringList _r = _t->savedCommandNames();
            if (_a[0]) *reinterpret_cast<QStringList*>(_a[0]) = std::move(_r); }  break;
        case 2: { QVariantMap _r = _t->getCommandDetails((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->saveCustomCommand((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->saveCustomCommand((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->deleteCustomCommand((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { QString _r = _t->composeOptionA((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 7: { QString _r = _t->composeOptionB((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 8: { QVariantMap _r = _t->allCommands();
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (CustomCommandManager::*)()>(_a, &CustomCommandManager::commandsChanged, 0))
            return;
    }
}

const QMetaObject *CustomCommandManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomCommandManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20CustomCommandManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CustomCommandManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CustomCommandManager::commandsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP

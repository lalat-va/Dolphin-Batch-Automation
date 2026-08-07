/****************************************************************************
** Meta object code from reading C++ file 'FileAutomationController.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/controllers/FileAutomationController.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileAutomationController.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN24FileAutomationControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto FileAutomationController::qt_create_metaobjectdata<qt_meta_tag_ZN24FileAutomationControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "FileAutomationController",
        "currentDirectoryChanged",
        "",
        "recursiveChanged",
        "groupsChanged",
        "scanDirectory",
        "dirPath",
        "setGroupRule",
        "rule",
        "createCustomGroup",
        "groupName",
        "applyGroupPipelineToFiles",
        "groupIndex",
        "pipeline",
        "clearAllActions",
        "reloadView",
        "currentDirectory",
        "isRecursive",
        "fileModel",
        "FileListModel*",
        "tagManager",
        "TagManager*",
        "customCommandManager",
        "CustomCommandManager*",
        "executionEngine",
        "ExecutionEngine*",
        "groups",
        "QVariantList"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'currentDirectoryChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'recursiveChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'groupsChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'scanDirectory'
        QtMocHelpers::MethodData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Method 'scanDirectory'
        QtMocHelpers::MethodData<void()>(5, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void),
        // Method 'setGroupRule'
        QtMocHelpers::MethodData<void(const QString &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Method 'createCustomGroup'
        QtMocHelpers::MethodData<bool(const QString &)>(9, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 10 },
        }}),
        // Method 'applyGroupPipelineToFiles'
        QtMocHelpers::MethodData<void(int, const QString &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 12 }, { QMetaType::QString, 13 },
        }}),
        // Method 'clearAllActions'
        QtMocHelpers::MethodData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'reloadView'
        QtMocHelpers::MethodData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'currentDirectory'
        QtMocHelpers::PropertyData<QString>(16, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'isRecursive'
        QtMocHelpers::PropertyData<bool>(17, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable, 1),
        // property 'fileModel'
        QtMocHelpers::PropertyData<FileListModel*>(18, 0x80000000 | 19, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'tagManager'
        QtMocHelpers::PropertyData<TagManager*>(20, 0x80000000 | 21, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'customCommandManager'
        QtMocHelpers::PropertyData<CustomCommandManager*>(22, 0x80000000 | 23, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'executionEngine'
        QtMocHelpers::PropertyData<ExecutionEngine*>(24, 0x80000000 | 25, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'groups'
        QtMocHelpers::PropertyData<QVariantList>(26, 0x80000000 | 27, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 2),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<FileAutomationController, qt_meta_tag_ZN24FileAutomationControllerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject FileAutomationController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN24FileAutomationControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN24FileAutomationControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN24FileAutomationControllerE_t>.metaTypes,
    nullptr
} };

void FileAutomationController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FileAutomationController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->currentDirectoryChanged(); break;
        case 1: _t->recursiveChanged(); break;
        case 2: _t->groupsChanged(); break;
        case 3: _t->scanDirectory((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->scanDirectory(); break;
        case 5: _t->setGroupRule((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: { bool _r = _t->createCustomGroup((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->applyGroupPipelineToFiles((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 8: _t->clearAllActions(); break;
        case 9: _t->reloadView(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (FileAutomationController::*)()>(_a, &FileAutomationController::currentDirectoryChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (FileAutomationController::*)()>(_a, &FileAutomationController::recursiveChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (FileAutomationController::*)()>(_a, &FileAutomationController::groupsChanged, 2))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CustomCommandManager* >(); break;
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ExecutionEngine* >(); break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FileListModel* >(); break;
        case 3:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TagManager* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->currentDirectory(); break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->isRecursive(); break;
        case 2: *reinterpret_cast<FileListModel**>(_v) = _t->fileModel(); break;
        case 3: *reinterpret_cast<TagManager**>(_v) = _t->tagManager(); break;
        case 4: *reinterpret_cast<CustomCommandManager**>(_v) = _t->customCommandManager(); break;
        case 5: *reinterpret_cast<ExecutionEngine**>(_v) = _t->executionEngine(); break;
        case 6: *reinterpret_cast<QVariantList*>(_v) = _t->groups(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCurrentDirectory(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setRecursive(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *FileAutomationController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileAutomationController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN24FileAutomationControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FileAutomationController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void FileAutomationController::currentDirectoryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FileAutomationController::recursiveChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FileAutomationController::groupsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP

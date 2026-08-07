cmake_minimum_required(VERSION 3.20)

project(dolphin-batch-automation VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(ECM 6.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

# Dipendenze Qt6
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Quick
    QuickControls2
    Widgets
)

# Dipendenze KDE Frameworks 6 (KF6)
find_package(KF6 REQUIRED COMPONENTS
    CoreAddons
    I18n
    Kirigami
    KIO
    Config
    FileMetaData
)

# Sorgenti dell'applicazione C++ e file risorse QRC
set(SRCS
    src/main.cpp
    src/models/FileItem.cpp
    src/models/FileGroup.cpp
    src/models/FileListModel.cpp
    src/models/ActionPipeline.cpp
    src/controllers/TagManager.cpp
    src/controllers/CustomCommandManager.cpp
    src/controllers/ExecutionEngine.cpp
    src/controllers/FileAutomationController.cpp
    resources.qrc
)

add_executable(dolphin-batch-automation ${SRCS})

target_link_libraries(dolphin-batch-automation PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Widgets
    KF6::CoreAddons
    KF6::I18n
    KF6::Kirigami
    KF6::KIOCore
    KF6::KIOFileWidgets
    KF6::ConfigCore
    KF6::FileMetaData
)

# Compilazione e installazione traduzioni (.po -> .mo)
find_package(Gettext REQUIRED)
file(GLOB PO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/po/*.po")
set(MO_FILES "")
foreach(PO_FILE ${PO_FILES})
    get_filename_component(LANG ${PO_FILE} NAME_WE)
    set(MO_DIR "${CMAKE_CURRENT_BINARY_DIR}/locale/${LANG}/LC_MESSAGES")
    file(MAKE_DIRECTORY ${MO_DIR})
    set(MO_FILE "${MO_DIR}/dolphin-batch-automation.mo")
    add_custom_command(
        OUTPUT ${MO_FILE}
        COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} -o ${MO_FILE} ${PO_FILE}
        DEPENDS ${PO_FILE}
    )
    list(APPEND MO_FILES ${MO_FILE})
    install(FILES ${MO_FILE} DESTINATION ${KDE_INSTALL_LOCALEDIR}/${LANG}/LC_MESSAGES)
endforeach()
add_custom_target(translations ALL DEPENDS ${MO_FILES})

install(TARGETS dolphin-batch-automation ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES servicemenu/dolphin-batch-automation.desktop DESTINATION ${KDE_INSTALL_DATADIR}/kio/servicemenus)

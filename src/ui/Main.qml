import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.20 as Kirigami

Kirigami.ApplicationWindow {
    id: root
    title: "Dolphin Batch Automation"
    width: 1100
    height: 750
    visible: true

    // Stato modali
    property string activeTargetFilePath: ""
    property int activeTargetIndex: -1
    property bool activeTargetIsGroup: false
    property int activeGroupIndex: -1

    pageStack.initialPage: FileListView {}

    // Modali condivisi
    ActionEditor {
        id: actionEditorDialog
    }

    TagDialog {
        id: tagDialog
    }

    CustomCommandDialog {
        id: customCommandDialog
    }

    ExecutionDialog {
        id: executionDialog
    }

    // Helper per aprire l'editor azioni su un file
    function openActionMenuForFile(index, filePath) {
        activeTargetIndex = index
        activeTargetFilePath = filePath
        activeTargetIsGroup = false
        actionEditorDialog.open()
    }

    // Helper per aprire l'editor azioni su un gruppo
    function openActionMenuForGroup(groupIndex) {
        activeGroupIndex = groupIndex
        activeTargetIsGroup = true
        actionEditorDialog.open()
    }

    // Helper per applicare un'azione alla pipeline
    function applyActionToActiveTarget(actionStr) {
        if (activeTargetIsGroup) {
            controller.applyGroupPipelineToFiles(activeGroupIndex, actionStr)
        } else {
            fileModel.appendPipelineAt(activeTargetIndex, actionStr)
        }
    }
}

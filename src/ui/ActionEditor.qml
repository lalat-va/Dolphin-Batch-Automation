import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import QtQuick.Dialogs as QtDialogs
import org.kde.kirigami 2.20 as Kirigami

Controls.Dialog {
    id: dialog
    title: "Seleziona Azione da Aggiungere"
    modal: true
    standardButtons: Controls.Dialog.Close
    anchors.centerIn: parent
    width: 450

    ColumnLayout {
        spacing: 12
        width: parent.width

        Controls.Label {
            text: "Scegli l'operazione da concatenare nella sequenza:"
            font.bold: true
        }

        Controls.Button {
            text: "📁 Copia..."
            Layout.fillWidth: true
            onClicked: {
                copyFolderDialog.open()
                dialog.close()
            }
        }

        Controls.Button {
            text: "📦 Sposta..."
            Layout.fillWidth: true
            onClicked: {
                moveFolderDialog.open()
                dialog.close()
            }
        }

        Controls.Button {
            text: "🗑️ Cancella (Invia al Cestino via trash-cli)"
            Layout.fillWidth: true
            onClicked: {
                root.applyActionToActiveTarget("Cancella")
                dialog.close()
            }
        }

        Controls.Button {
            text: "🏷️ Tagga..."
            Layout.fillWidth: true
            onClicked: {
                tagDialog.openForTarget(root.activeTargetFilePath)
                dialog.close()
            }
        }

        Controls.Button {
            text: "⚙️ Comando Personalizzato..."
            Layout.fillWidth: true
            onClicked: {
                customCommandDialog.openDialog()
                dialog.close()
            }
        }
    }

    QtDialogs.FolderDialog {
        id: copyFolderDialog
        title: "Seleziona Cartella di Destinazione per Copia"
        onAccepted: {
            var path = selectedFolder.toString().replace("file://", "")
            root.applyActionToActiveTarget("Copia (" + path + ")")
        }
    }

    QtDialogs.FolderDialog {
        id: moveFolderDialog
        title: "Seleziona Cartella di Destinazione per Sposta"
        onAccepted: {
            var path = selectedFolder.toString().replace("file://", "")
            root.applyActionToActiveTarget("Sposta (" + path + ")")
        }
    }
}

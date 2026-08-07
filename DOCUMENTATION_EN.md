# Detailed Technical Documentation - Dolphin Batch Automation

This document provides a comprehensive technical overview of the architecture, internal logic, and tools used by **Dolphin Batch Automation**.

---

## 1. System Architecture & Tech Stack

The application is built as a native component for **KDE Plasma 6**:
- **Language**: C++20.
- **GUI Framework**: Qt6 + Kirigami 3 (KDE Frameworks 6).
- **KDE Integration**: KF6 (KIO, KConfig, KCoreAddons, KFileMetaData, KI18n).
- **Dolphin Integration**: ServiceMenu desktop file (`.desktop`) located in `~/.local/share/kio/servicemenus/`, which invokes the binary passing selected files or directories from Dolphin.

---

## 2. File Listing & Grouping Logic

### Recursive Scanning
The application utilizes `QDirIterator` to list all items within the selected folder. When the **Recursive** option is enabled, the iterator scans subdirectories, including nested files while listing subfolders as individual items in the model.

### File Grouping Rules
The view allows organizing files into groups:
1. **By MIME Type**: Groups files according to their MIME type (e.g., `image/png`, `audio/flac`, `application/pdf`).
2. **By Folder / Subfolder**: Groups files according to their parent filesystem path.
3. **By Modification Date**: Groups files based on their last modified timestamp (`yyyy-MM-dd`).

#### Custom Groups
Users can manually select files via checkboxes and click **"Create Custom Group"**.
- **Exclusion Rule**: Files assigned to a custom group are **automatically excluded** from rule-based standard groups.
- Multiple custom groups can be created simultaneously.

---

## 3. Action Pipelines & `AND` Syntax

Every file and group contains an action sequence stored as a string pipeline.
- Actions are concatenated using the syntax:
  `action 1 AND action 2 AND action 3`
- **Action Order Significance**: The exact order of actions in the string determines the execution sequence on each file.
- Users can append actions via the `+` action picker or **edit the string pipeline directly**.

---

## 4. In-Depth Tagging Logic (Baloo / Extended Attributes)

### Native Plasma 6 Tagging Mechanism
In KDE Plasma 6 and Dolphin, file tags are not stored in isolated proprietary databases; they use **XDG Extended Attributes on the filesystem** (`user.xdg.tags`).

The `TagManager` controller communicates with the system via:
- **`xattr` Read / Write**:
  - Writing tags: `setfattr -n user.xdg.tags -v "tag1,tag2" <PATH/TO/FILE>`
  - Reading tags: `getfattr -n user.xdg.tags --only-values <PATH/TO/FILE>`
- **Baloo Indexer Integration**:
  - Upon initialization, the application executes `balootag --list` to fetch all tags registered in the KDE Plasma system indexer.

### Nested Tags & "Nest in" Feature
Plasma 6 tags support hierarchical structures using slashes (`/`).
- **Example**: `MUSIC/rock` or `DOCUMENTS/work/2026`.
- The **TagDialog** UI allows creating new tags while selecting an existing parent tag via **"Nest in"**. The system concatenates the parent tag and the new tag (e.g., Parent `MUSIC`, New `artist` -> `MUSIC/artist`) and updates the UI instantly.

### Metadata Extraction
Using KDE's native **`KFileMetaData`** library (`ExtractorCollection` & `Extractor`), the application extracts embedded metadata from audio files, documents, and images (Author, Title, Genre, Year).
- Extracted items are displayed in a selectable dialog window.
- Upon user confirmation, selected metadata values are converted into tags and applied to the file.

---

## 5. Custom Command Manager (Option A & Option B)

The `CustomCommandManager` module manages custom shell command creation and persistence.

### Command Composition Modes
Users can choose between two modes to define how file references are inserted:

#### Option A — Fixed Structure Schema (Simple)
Structured with 3 distinct input fields: **Command**, **Attributes**, **Destination**.
- The plugin generates the command using the schema:
  `<Command> <Attributes> <FILE> <Destination>`
- *Example*: Command=`ffmpeg -i`, Attributes=`-b:a 192k`, Destination=`audio.mp3`  
  -> Composed command: `ffmpeg -i -b:a 192k <FILE> audio.mp3`

#### Option B — Advanced Placeholder Template
Offers complete flexibility for complex commands using dynamic placeholders:
- `{file}`: Full quoted file path (`"/path/to/file.wav"`).
- `{name}`: File name without extension.
- `{ext}`: File extension.
- `{dir}`: Parent folder directory path.
- `{date}`: Last modified date.
- `{dest}`: Output target destination path.
- *Example*: `ffmpeg -i {file} -b:a 192k {dir}/{name}.mp3`

### Validation & Persistence Logic
- **Pipeline Display**: When a custom command is added to a file's action pipeline, it appears identified by its **Title** (e.g., `convert to mp3`) rather than the raw shell string.
- **"Create new command from changes" Checkbox**: If an existing command is edited, checking this box saves it as a brand new command entry.
- **Duplicate Name Validation**: If the title matches an existing command name, the UI blocks saving and displays an error message.
- **Persistence**: Saved custom commands are persisted in JSON format at:
  `~/.config/dolphin-batch-automation/custom_commands.json`

---

## 6. Asynchronous Execution Engine & CSV Logging

The `ExecutionEngine` module processes operations file-by-file:
1. **Safety Warning**: Prior to execution, an explicit warning dialog reminds the user that commands will run in the exact order organized in the pipeline.
2. **Error Tolerance**: Execution runs via `QProcess` for each file. If an action fails for a single file, the error is recorded, and execution continues for remaining files.
3. **Trash Action**: Sends files to the native Desktop trash using `trash-cli` (`trash-put`).
4. **CSV Log Export**: Upon completion or on request, exports a CSV report formatted as:
   `"Timestamp","FilePath","ActionName","ExecutedShellCommand","Status","ErrorMessage"`
5. **View Auto-Reload**: After execution finishes, the file list view re-scans automatically to reflect updated file positions, names, or tags.

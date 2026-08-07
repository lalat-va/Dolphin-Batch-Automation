# ATTENZIONE
Codice totalmente generato con AI; autore non ha competenze per gestire eventuali correzzioni; se siete interessati al progetto NON CONTRIBUITE ma forkate o scaricate.

# Dolphin Batch Automation

**Dolphin Batch Automation** è un componente aggiuntivo nativo per **KDE Dolphin** (realizzato in C++20, Qt6, Kirigami e KDE Frameworks 6) orientato all'automazione ed esecuzione di azioni massive sui file.

---

## 🚀 Caratteristiche Principali

- **Visualizzazione & Scansione Ricorsiva**: Mostra l'elenco dei file e delle sottocartelle della cartella corrente con opzione di scansione ricorsiva.
- **Organizzazione & Gruppi**:
  - Raggruppamento automatico per **MIME Type**, **Cartella/Sottocartella** e **Data di modifica**.
  - **Gruppi Personalizzati**: Selezione manuale dei file per la creazione di gruppi dedicati (con esclusione automatica dai gruppi standard).
- **Sequenza Ordinata di Azioni (`AND`)**:
  - Aggiunta guidata di azioni sui singoli file o sui gruppi via pulsante `+`.
  - Sintassi editabile in formato `azione 1 AND azione 2 AND azione 3`. L'ordine determina la sequenza esatta di esecuzione.
- **Gestione Tag Nativi Plasma 6 (Baloo / XDG Extended Attributes)**:
  - Supporto a tag singoli e annidati (`MUSICA/autore`).
  - Creazione con opzione **"Innesta in"** per definire tag padri.
  - Estrazione metadati da file audio/documenti (`KFileMetaData`) e conversione in tag.
- **Comandi Personalizzati Salvati**:
  - **Opzione A (Semplice)**: `<Comando> <Attributi> <FILE> <Destinazione>`.
  - **Opzione B (Avanzata)**: Segnaposto dinamici (`{file}`, `{name}`, `{ext}`, `{dir}`, `{date}`, `{dest}`).
  - Persistenza automatica tra le sessioni in `~/.config/dolphin-batch-automation/custom_commands.json`.
- **Multilingua Nativi (i18n)**:
  - Supporto automatico per **Italiano** e **Inglese**, attivati dinamicamente in base alla lingua del sistema (`gettext` / `ki18n`).
- **Motore di Esecuzione & Logging CSV**:
  - Esecuzione asincrona file-per-file con tolleranza agli errori.
  - Avviso di sicurezza con conferma prima dell'avvio.
  - Esportazione dei log di esecuzione in formato CSV (`Timestamp`, `FilePath`, `ActionName`, `ExecutedShellCommand`, `Status`, `ErrorMessage`).

---

## 📋 Dipendenze di Sistema

### Dipendenze di Compilazione (Build Dependencies)
- **CMake** >= 3.20
- **Extra CMake Modules (ECM)** >= 6.0
- **Gettext** (`msgfmt`)
- **Compilatore C++20** (GCC >= 11 o Clang >= 13)
- **Qt 6** (Core, Gui, Qml, Quick, QuickControls2, Widgets)
- **KDE Frameworks 6 (KF6)**:
  - `Kirigami`
  - `KIO`
  - `KConfig`
  - `KCoreAddons`
  - `KFileMetaData`
  - `KI18n`

### Dipendenze Forti di Esecuzione (Runtime Dependencies)
- **`trash-cli`** *(Dipendenza Forte)*: Necessario per l'esecuzione del comando da riga di comando dell'azione **Cancella** (`trash-put`). In assenza di `trash-cli`, l'azione di invio al cestino restituirà errore nel log.
- **`attr` / `setfattr` / `getfattr`**: Utilizzati per la lettura e scrittura degli attributi estesi XDG dei tag (`user.xdg.tags`).

---

## ⚡ Installazione Automatica via Script (`install.sh`)

È fornito uno script `install.sh` per automatizzare l'intero processo di verifica dipendenze, compilazione, traduzioni e posizionamento dei binari e del file `.desktop`.

```bash
# Installazione Utente Locale (~/.local/bin e ~/.local/share/kio/servicemenus)
./install.sh

# Oppure installazione di sistema (richiede sudo)
./install.sh --system
```

---

## 🛠️ Istruzioni Manuali di Build

1. **Configurare ed eseguire la build con CMake**:
   ```bash
   cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
   cmake --build build -j$(nproc)
   ```

2. **Installare l'eseguibile, le traduzioni ed il Service Menu di Dolphin**:
   ```bash
   sudo cmake --install build
   ```

---

## 🐬 Integrazione in KDE Dolphin

Dopo l'esecuzione di `install.sh` (o installazione manuale):
1. Apri **Dolphin**.
2. Fai clic con il tasto destro del mouse su qualsiasi cartella o selezione di file.
3. Nel menu contestuale, seleziona la voce **"Automazione File Massiva..."** / **"Massive Batch Automation..."**.
4. Verrà aperta la finestra nativa Kirigami di **Dolphin Batch Automation** impostata direttamente sulla cartella selezionata.

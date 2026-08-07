# Documentazione Dettagliata - Dolphin Batch Automation

Questo documento fornisce una descrizione approfondita dell'architettura tecnica, della logica interna e degli strumenti utilizzati da **Dolphin Batch Automation**.

---

## 1. Architettura Generale e Stack Tecnologico

L'applicazione è sviluppata come componente nativo per **KDE Plasma 6**:
- **Linguaggio**: C++20.
- **Interfaccia Grafica**: Qt6 + Kirigami 3 (KDE Frameworks 6).
- **Integrazione KDE**: KF6 (KIO, KConfig, KCoreAddons, KFileMetaData, KI18n).
- **Integrazione Dolphin**: File ServiceMenu (`.desktop`) posizionato in `~/.local/share/kio/servicemenus/`, che invoca l'applicazione passando i file o le cartelle selezionate in Dolphin.

---

## 2. Elenco dei File e Logica di Raggruppamento

### Scansione Ricorsiva
L'applicazione utilizza `QDirIterator` per elencare i file della cartella aperta. Quando l'opzione **Ricorsivo** è attiva, la scansione scende in tutte le sottocartelle includendo i file e mostrando le sottocartelle come elementi singoli.

### Raggruppamento dei File
La vista permette di organizzare i file in gruppi:
1. **Per MIME Type**: Raggruppa i file in base alla loro tipologia (es. `image/png`, `audio/flac`, `application/pdf`).
2. **Per Cartella / Sottocartella**: Raggruppa i file in base alla cartella fisica di appartenenza.
3. **Per Data**: Raggruppa i file in base alla data di ultima modifica (`yyyy-MM-dd`).

#### Gruppi Personalizzati (Custom Groups)
L'utente può selezionare manualmente uno o più file tramite checkbox ed invocare la funzione **"Crea Gruppo Personalizzato"**.
- **Regola di Esclusione**: I file inseriti in un gruppo personalizzato vengono **automaticamente esclusi** dai gruppi standard generati dalle regole automatiche.
- È possibile creare molteplici gruppi personalizzati.

---

## 3. Logica delle Azioni e Sintassi `AND`

Ogni file e ciascun gruppo possiedono una sequenza di azioni salvata come stringa.
- Le azioni vengono concatenate con la sintassi:
  `azione 1 AND azione 2 AND azione 3`
- **L'ordine delle azioni nella stringa è significativo**: determina l'ordine esatto in cui i comandi verranno eseguiti sul file.
- L'utente può aggiungere azioni tramite il menu guidato `+` oppure **modificare direttamente la casella di testo**.

---

## 4. Gestione Approfondita dei Tag (Baloo / Extended Attributes)

### Meccanismo di Tagging Nativo in Plasma 6
In KDE Plasma 6 e nel file manager Dolphin, i tag non sono memorizzati in database proprietari isolati, ma utilizzano gli **attributi estesi XDG del file system** (`user.xdg.tags`).

Il controller `TagManager` interagisce con il sistema operativo mediante:
- **Lettura e Scrittura attributi `xattr`**:
  - Scrittura: `setfattr -n user.xdg.tags -v "tag1,tag2" <PATH/TO/FILE>`
  - Lettura: `getfattr -n user.xdg.tags --only-values <PATH/TO/FILE>`
- **Indicizzazione Baloo**:
  - In fase di avvio, l'applicazione invoca `balootag --list` per recuperare l'elenco dei tag già presenti e registrati nell'indicizzatore di sistema KDE Plasma.

### Tag Annidati e Funzione "Innesta in"
I tag in Plasma 6 supportano la gerarchia attraverso il carattere slash (`/`).
- **Esempio**: `MUSICA/rock` o `DOCUMENTI/lavoro/2026`.
- La finestra **TagDialog** permette di creare un nuovo tag ed al contempo scegliere un tag padre tramite il selettore **"Innesta in"**. Il sistema concatena il padre ed il nuovo tag (es. Padre `MUSICA`, Nuovo Tag `autore` -> `MUSICA/autore`) aggiornando immediatamente l'interfaccia.

### Estrazione Metadati
Tramite la libreria nativa **`KFileMetaData`** (`ExtractorCollection` ed `Extractor`), l'applicazione consente di estrarre metadati da brani audio, documenti o immagini (Autore, Titolo, Genere, Anno).
- I metadati estratti vengono mostrati in una sotto-finestra selezionabile.
- Dopo la conferma dell'utente, gli elementi selezionati vengono convertiti in tag ed applicati al file.

---

## 5. Editor Comandi Personalizzati (Opzioni A & B)

Il modulo `CustomCommandManager` gestisce la creazione e la persistenza dei comandi shell personalizzati.

### Modalità di Composizione del Comando
L'utente dispone di due modalità per definire come il riferimento al file viene inserito nel comando:

#### Opzione A — Schema a Struttura Fissa (Semplice)
Strutturata con 3 campi distinti: **Comando**, **Attributi**, **Destinazione**.
- Il plugin genera il comando componendolo secondo lo schema:
  `<Comando> <Attributi> <FILE> <Destinazione>`
- *Esempio*: Comando=`ffmpeg -i`, Attributi=`-b:a 192k`, Destinazione=`brano.mp3`  
  -> Comando generato: `ffmpeg -i -b:a 192k <FILE> brano.mp3`

#### Opzione B — Template Avanzato con Segnaposto
Fornisce massima flessibilità per comandi complessi o articolati, permettendo l'uso di variabili dinamiche:
- `{file}`: Rappresenta il file selezionato corrente su cui viene applicata l'azione/script (inserisce il percorso completo tra virgolette, es. `"/path/al/file.wav"`).
- `{name}`: Nome del file selezionato corrente senza estensione (es. `"brano"`).
- `{ext}`: Estensione del file selezionato corrente (es. `"wav"`).
- `{dir}`: Percorso della cartella contenitore del file selezionato corrente.
- `{date}`: Data di ultima modifica del file selezionato corrente.
- `{dest}`: Percorso della cartella di destinazione specificata.
- *Esempio*: `ffmpeg -i {file} -b:a 192k {dir}/{name}.mp3`

### Logica di Validazione e Salvataggio
- **Visualizzazione nella Pipeline**: Quando un comando personalizzato viene aggiunto alla stringa di azioni di un file, compare identificato dal suo **Titolo** (es. `converti in mp3`) e non dalla sintassi shell completa.
- **Checkbox "Crea nuovo comando da modifiche"**: Se l'utente seleziona un comando esistente e ne modifica il titolo o la sintassi, attivando questa checkbox il comando viene salvato come nuovo.
- **Validazione Nomi Duplicati**: Se il nome inserito coincide con un comando già esistente, l'interfaccia blocca il salvataggio e mostra un messaggio d'errore.
- **Persistenza**: I comandi vengono salvati in formato JSON nel file:
  `~/.config/dolphin-batch-automation/custom_commands.json`

---

## 6. Motore di Esecuzione e Logging CSV

Il modulo `ExecutionEngine` esegue le operazioni in modo asincrono file-per-file:
1. **Avviso di Sicurezza**: Prima dell'avvio, viene mostrato un avviso esplicito che ricorda all'utente che i comandi verranno eseguiti rigorosamente nell'ordine configurato.
2. **Esecuzione Tollerante agli Errori**: L'esecuzione avviene tramite `QProcess` per ciascun file. Se un'azione fallisce su un file, l'errore viene registrato e l'esecuzione prosegue sui file successivi.
3. **Azione Cancella**: Invia i file al cestino nativo utilizzando `trash-cli` (`trash-put`).
4. **Esportazione Log CSV**: Al termine o su richiesta, genera un file CSV contenente:
   `"Timestamp","FilePath","ActionName","ExecutedShellCommand","Status","ErrorMessage"`
5. **Aggiornamento della Vista**: Al termine dell'esecuzione, la vista dei file viene automaticamente riaggiornata per riflettere le nuove posizioni o attributi.

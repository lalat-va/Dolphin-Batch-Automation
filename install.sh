#!/usr/bin/env bash
# ==============================================================================
# Script di Installazione Automatica per Dolphin Batch Automation (Plasma 6 / KF6)
# ==============================================================================

set -e

# Colori per il terminale
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== Dolphin Batch Automation - Installer ===${NC}\n"

# Modalità di installazione: default = --user, oppure --system
MODE="user"
if [[ "$1" == "--system" ]]; then
    MODE="system"
fi

# 1. Verifica dipendenze di sistema
echo -e "${YELLOW}[1/4] Verifica dipendenze di sistema...${NC}"

for cmd in cmake gcc msgfmt; do
    if ! command -v $cmd &> /dev/null; then
        echo -e "${RED}Errore: il comando '$cmd' è richiesto ma non è installato.${NC}"
        exit 1
    fi
done

# Dipendenza forte: trash-cli
if ! command -v trash-put &> /dev/null; then
    echo -e "${YELLOW}AVVISO: 'trash-cli' (trash-put) non sembra essere installato.${NC}"
    echo -e "L'azione 'Cancella' richiede 'trash-cli' per inviare i file al cestino."
    echo -e "Installalo con il gestore pacchetti del tuo sistema (es: sudo pacman -S trash-cli / sudo apt install trash-cli)."
    echo ""
fi

# 2. Configurazione e Compilazione CMake
echo -e "${YELLOW}[2/4] Compilazione in corso con CMake...${NC}"
mkdir -p build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)

# Assicura i permessi di esecuzione sui binari compilati
if [ -f "build/bin/dolphin-batch-automation" ]; then
    chmod +x "build/bin/dolphin-batch-automation"
fi
if [ -f "build/dolphin-batch-automation" ]; then
    chmod +x "build/dolphin-batch-automation"
fi
chmod +x servicemenu/dolphin-batch-automation.desktop 2>/dev/null || true

# 3. Installazione binari, ServiceMenu e Traduzioni
echo -e "${YELLOW}[3/4] Installazione dei file ($MODE mode)...${NC}"

if [[ "$MODE" == "system" ]]; then
    sudo cmake --install build
    sudo chmod +x /usr/local/share/kio/servicemenus/dolphin-batch-automation.desktop 2>/dev/null || true
    sudo chmod +x /usr/share/kio/servicemenus/dolphin-batch-automation.desktop 2>/dev/null || true
else
    # Installazione Utente Locale (~/.local)
    BIN_DIR="$HOME/.local/bin"
    SERVICEMENU_DIR="$HOME/.local/share/kio/servicemenus"
    LOCALE_DIR="$HOME/.local/share/locale"

    if mkdir -p "$BIN_DIR" "$SERVICEMENU_DIR" "$LOCALE_DIR/it/LC_MESSAGES" "$LOCALE_DIR/en/LC_MESSAGES" 2>/dev/null; then
        # Copia Eseguibile e imposta permessi +x
        if [ -f "build/bin/dolphin-batch-automation" ]; then
            cp "build/bin/dolphin-batch-automation" "$BIN_DIR/"
        else
            cp "build/dolphin-batch-automation" "$BIN_DIR/"
        fi
        chmod +x "$BIN_DIR/dolphin-batch-automation"

        # Copia Dolphin Service Menu (.desktop) con percorso assoluto dell'eseguibile per evitare problemi di PATH in Plasma 6
        sed "s|Exec=dolphin-batch-automation|Exec=$BIN_DIR/dolphin-batch-automation|g" servicemenu/dolphin-batch-automation.desktop > "$SERVICEMENU_DIR/dolphin-batch-automation.desktop"
        chmod +x "$SERVICEMENU_DIR/dolphin-batch-automation.desktop"

        # Copia file di traduzione (.mo)
        if [ -f "build/locale/it/LC_MESSAGES/dolphin-batch-automation.mo" ]; then
            cp build/locale/it/LC_MESSAGES/dolphin-batch-automation.mo "$LOCALE_DIR/it/LC_MESSAGES/"
        fi
        if [ -f "build/locale/en/LC_MESSAGES/dolphin-batch-automation.mo" ]; then
            cp build/locale/en/LC_MESSAGES/dolphin-batch-automation.mo "$LOCALE_DIR/en/LC_MESSAGES/"
        fi

        echo -e "${GREEN}Permessi di esecuzione (+x) e percorso assoluto applicati con successo.${NC}"
    else
        echo -e "${YELLOW}Nota: La directory ~/.local/share non è direttamente modificabile in questo ambiente sandbox.${NC}"
        echo -e "Per completare l'installazione sul tuo sistema, esegui i seguenti comandi nel tuo terminale:"
        echo -e "  mkdir -p ~/.local/bin ~/.local/share/kio/servicemenus"
        echo -e "  cp build/bin/dolphin-batch-automation ~/.local/bin/"
        echo -e "  chmod +x ~/.local/bin/dolphin-batch-automation"
        echo -e "  sed \"s|Exec=dolphin-batch-automation|Exec=\$HOME/.local/bin/dolphin-batch-automation|g\" servicemenu/dolphin-batch-automation.desktop > ~/.local/share/kio/servicemenus/dolphin-batch-automation.desktop"
        echo -e "  chmod +x ~/.local/share/kio/servicemenus/dolphin-batch-automation.desktop"
    fi
fi

# 4. Aggiornamento Cache dei Service Menu di KDE Plasma 6
echo -e "${YELLOW}[4/4] Aggiornamento cache dei menu di KDE Plasma 6...${NC}"
if command -v kbuildsycoca6 &> /dev/null; then
    kbuildsycoca6 --noincremental &> /dev/null || true
fi

echo -e "\n${GREEN}=======================================================${NC}"
echo -e "${GREEN}  Installazione completata con successo!               ${NC}"
echo -e "${GREEN}=======================================================${NC}"

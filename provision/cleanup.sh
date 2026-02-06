#!/usr/bin/env bash

# Default venv path (relative to this script)
VENV_PATH="../venv"

# Get the directory of this script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

FULL_VENV_PATH="$SCRIPT_DIR/$VENV_PATH"

# Deactivate if a venv is currently active
if [[ -n "$VIRTUAL_ENV" ]]; then
    deactivate
fi

if [[ -d "$FULL_VENV_PATH" ]]; then
    echo "Removing virtual environment directory: $FULL_VENV_PATH"
    rm -rf "$FULL_VENV_PATH"
    echo "Virtual environment directory removed."
else
    echo "The specified path does not exist: $FULL_VENV_PATH"
fi

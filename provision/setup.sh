#!/usr/bin/env bash

# Default paths (relative to this script)
REQUIREMENTS_PATH="../requirements.txt"
ACTIVATE_PATH="../venv/bin/activate"

# Get the directory of this script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

FULL_REQUIREMENTS_PATH="$SCRIPT_DIR/$REQUIREMENTS_PATH"
FULL_ACTIVATE_PATH="$SCRIPT_DIR/$ACTIVATE_PATH"

# Create virtual environment
python3 -m venv "$SCRIPT_DIR/../venv"

# Activate virtual environment
source "$FULL_ACTIVATE_PATH"

# Upgrade pip and install dependencies
python -m pip install --upgrade pip
python -m pip install -r "$FULL_REQUIREMENTS_PATH"

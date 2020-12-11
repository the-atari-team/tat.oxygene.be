#!/bin/bash

# . ${MACRO_N_RUNTIME}/os.sh
if [[ "$OS" == "Windows_NT" ]]; then
  echo "Windows_NT" 
elif [[ "$OSTYPE" == "linux" ]]; then
  echo "Linux"
else
  echo "unbekannt"
fi

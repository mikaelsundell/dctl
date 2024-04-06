#!/bin/bash
##  Copyright 2022-present Contributors to the dctl project.
##  SPDX-License-Identifier: BSD-3-Clause
##  https://github.com/mikaelsundell/dctl

open_log() {
    local log_file="$HOME/Library/Application Support/Blackmagic Design/DaVinci Resolve/logs/davinci_resolve.log"
    if [ -f "$log_file" ]; then
        clear
        echo "Starting to trace the log file..."
        tail -f "$log_file"
    else
        echo "Log file does not exist, make sure Davinci Resolve is installed."
        exit 1
    fi
}

open_readme() {
    local readme_file="/Library/Application Support/Blackmagic Design/DaVinci Resolve/Developer/DaVinciCTL/README.txt"
    if [ -f "$readme_file" ]; then
        open "$readme_file"
    else
        echo "README file does not exist."
        exit 1
    fi
}

open_examples() {
    local examples_dir="/Library/Application Support/Blackmagic Design/DaVinci Resolve/Developer/DaVinciCTL"
    if [ -d "$examples_dir" ]; then
        open "$examples_dir"
    else
        echo "Examples directory does not exist."
        exit 1
    fi
}

case "$1" in
    log) open_log ;;
    readme) open_readme ;;
    examples) open_examples ;;
    *) echo "Usage: $0 {log|readme|examples}"
       exit 1 ;;
esac

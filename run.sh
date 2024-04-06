#!/bin/bash
##  Copyright 2022-present Contributors to the dctl project.
##  SPDX-License-Identifier: BSD-3-Clause
##  https://github.com/mikaelsundell/dctl

run_log() {
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

run_readme() {
    local readme_file="/Library/Application Support/Blackmagic Design/DaVinci Resolve/Developer/DaVinciCTL/README.txt"
    if [ -f "$readme_file" ]; then
        open "$readme_file"
    else
        echo "README file does not exist."
        exit 1
    fi
}

run_examples() {
    local examples_dir="/Library/Application Support/Blackmagic Design/DaVinci Resolve/Developer/DaVinciCTL"
    if [ -d "$examples_dir" ]; then
        open "$examples_dir"
    else
        echo "Examples directory does not exist."
        exit 1
    fi
}

run_snapshot() {
    local target_dir="/Library/Application Support/Blackmagic Design/DaVinci Resolve/LUT/DCTL"
    local date_time=$(date "+%Y%m%d_%H%M%S")
    local archive_name="DCTL_${date_time}.tar.gz"
    if [ -d "$target_dir" ]; then
        echo "Creating snapshot of $target_dir..."
        tar -czf "$archive_name" -C "$(dirname "$target_dir")" "$(basename "$target_dir")"
        echo "Snapshot saved as $archive_name"
    else
        echo "Target directory does not exist."
        exit 1
    fi
}

case "$1" in
    log) run_log ;;
    readme) run_readme ;;
    examples) run_examples ;;
    snapshot) run_snapshot ;;
    *) echo "Usage: $0 {log|readme|examples|snapshot}"
       exit 1 ;;
esac

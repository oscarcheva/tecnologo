#!/bin/bash

## Author: Oscar Echeverria
## Date Created: Jan 28, 2026
## Last Modified: Jan 28, 2026
## Description: Script to organize files according to the extension.
## Usage: Run ./folder_organizer.sh

readarray -t files < <(ls)

for file in "${files[@]}" ; do
        case $file  in
        *.jpg | *.jepg | *.png) destination=images ;;
        *.doc | *.docs | *.txt | *.pdf) destination=documents ;;
        *.xls | *.xlsx | *.csv) destination=spreadsheets ;;
        *.sh) destination=scripts ;;
        *.zip | *.tar | *.tar.gz | *.tar.bz2) destination=archives ;;
        *.ppt | *.pptx) destination=presentations ;;
        *.mp3) destination=audio ;;
        *.mp4) destination=video ;;
        *) echo "File $file not moved"
        esac
	mv $file "../$destination"
done

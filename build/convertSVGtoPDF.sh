#!/bin/bash
mkdir "$PWD"/files/png
for file in $PWD/files/finalFiles/*.svg
    do
        filename=$(basename "$file")
        inkscape "$file" -e "$PWD"/files/png/"${filename%.svg}.png"
    done

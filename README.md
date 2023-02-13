# QRcardGenerator

```bash

sudo ./QR_CardGenerator
cd files/finalFiles
mkdir png
for file in *.svg; do inkscape "$file" -e "png/${file%svg}png"; done

```

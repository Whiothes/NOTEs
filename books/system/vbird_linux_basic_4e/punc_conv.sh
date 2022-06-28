#/bin/bash
sed -ir 's/，\ */, /g' $@
sed -ir 's/。\ */. /g' $@
sed -ir 's/[“”]/"/g' $@
sed -ir 's/[：]/: /g' $@
sed -ir 's/,\ */, /g' $@
sed -ir 's/\.\ */./g' $@
sed -i 's/（/ (/g' $@
sed -i 's/）/) /g' $@
sed -ir 's/\ *\(\ */(/g' $@
sed -ir 's/\ *\)\ */)/g' $@

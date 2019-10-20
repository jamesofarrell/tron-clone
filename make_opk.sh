#!/bin/sh
NAME=tron-clone
OPK_NAME=${NAME}.opk

echo ${OPK_NAME}

# create default.gcw0.desktop
cat > default.gcw0.desktop <<EOF
[Desktop Entry]
Name=Tron Clone
Comment=2 Player Light Cycle Game
Exec=tron-clone.elf
Terminal=false
Type=Application
StartupNotify=true
Icon=tron-clone
Categories=games;
EOF

FLIST="tron-clone.png tron-clone.elf Resources default.gcw0.desktop"

# create opk

rm -f ${OPK_NAME}
mksquashfs ${FLIST} ${OPK_NAME} -all-root -no-xattrs -noappend -no-exports

cat default.gcw0.desktop
rm -f default.gcw0.desktop

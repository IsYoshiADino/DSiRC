#!/usr/bin/env bash
make >> /dev/null
rm -rf DSiRC.elf build >> /dev/null
mkdir title >> /dev/null
mkdir title/00030015 >> /dev/null
mkdir title/00030015/44535243 >> /dev/null
mkdir title/00030015/44535243/content >> /dev/null
mv DSiRC.nds title/00030015/44535243/content/00000000.app >> /dev/null
maketmd title/00030015/44535243/content/00000000.app title/00030015/44535243/content/title.tmd >> /dev/null
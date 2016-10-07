#!/bin/sh
dot $1.dot | gvpr -c -ftree.gv | neato -n -Tpng -o $1.png

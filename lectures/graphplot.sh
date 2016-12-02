#!/bin/sh
dot $1.dot |    neato -n -Tpng -o $1.png

#!/bin/bash

#script converts a hexadecimal colour code into rgb, and then into unit rgb
#values. Very useful for graphics branch

hexcode=$1
hex_int=$((16#$hexcode))
r=$(((hex_int >> 16) & 0xFF))
g=$(((hex_int >> 8) & 0xFF))
b=$(((hex_int) & 0xFF))
echo "rgb: ($r, $g, $b)"

r2=$(bc <<< "scale=3; ${r}/255")
g2=$(bc <<< "scale=3; ${g}/255")
b2=$(bc <<< "scale=3; ${b}/255")
echo "unit rgb: ($r2, $g2, $b2)"

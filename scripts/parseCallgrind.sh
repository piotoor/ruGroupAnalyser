#!/bin/bash
for file in `ls -tU callgrind*.out`; do
  echo "--------------" $file  "--------------"
  callgrind_annotate $file | grep -iE "function|$1" | grep -vi test
  echo
done

#!/bin/bash
for file in `ls -tU callgrind*.out`; do
  echo "--------------" $file  "--------------"
  callgrind_annotate $file | grep -iE "function|index" | grep -vi test
  echo
done

#!/bin/bash
for file in `ls -tU callgrind*.out`; do
  echo "--------------" $file  "--------------"
  callgrind_annotate $file | grep -iE "function|index" | grep -vi test
  echo
done
# callgrind_annotate $1 | grep -i function
# callgrind_annotate $1 | grep -i index | grep -vi test

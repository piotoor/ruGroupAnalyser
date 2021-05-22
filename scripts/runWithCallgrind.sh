#!/bin/bash
output_file=callgrind_$(date +%Y%m%d_%H%M).out
valgrind --tool=callgrind --simulate-cache=yes --collect-atstart=no --callgrind-out-file=$output_file ./ruGroupAnalyser_tst

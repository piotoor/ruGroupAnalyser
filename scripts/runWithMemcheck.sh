#!/bin/bash
valgrind --leak-check=full --track-origins=yes --verbose ./ruGroupAnalyser_tst

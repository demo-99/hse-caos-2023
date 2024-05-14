#!/bin/bash

current_time=$(date +%s)
current_time=$((current_time + 1))

nanoseconds=500000000

echo $current_time $nanoseconds | ./a.out

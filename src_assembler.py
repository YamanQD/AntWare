#!/usr/bin/env python3
from glob import glob

for file in glob('src/**/*.c', recursive=True):
    print(file)

for file in glob('src/**/*.cpp', recursive=True):
    print(file)

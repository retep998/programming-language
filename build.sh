#! /bin/bash

# note: switch-enum means *explicit* handling of each thing

clang -g -std=c89 -Wall -Wextra -Weverything -Werror -pedantic \
  -Wno-undef -Wno-padded -Wno-switch-enum \ 
  src/driver.c -I src -o pink

#! /bin/bash
clang -std=c89 -Wall -Wextra -Wno-comment -Werror -pedantic -g \
  src/driver.c -I src -o pink

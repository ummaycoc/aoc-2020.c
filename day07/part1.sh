#!/usr/bin/env bash

target='shiny gold'

result=""
while [ -n "$target" ] ; do
  target="$(
    < input.raw grep "$target" |
      grep -v "^\($target\)" |
      sed -e 's/[[:space:]]bags.*//' |
      tr '\n' '|' |
      sed -e 's/|$//' -e 's/|/\\|/g'
  )"
  [ -n "$target" ] && result="${result}\\|${target}"
done
<<< "$result" sed -e 's/\\|/|/g' -e 's/^|//' |
  tr '|' '\n' |
  sort -u |
  wc -l |
  xargs

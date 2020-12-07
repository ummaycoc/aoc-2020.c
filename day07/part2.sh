#!/usr/bin/env bash

function countContained {
  while read; do
    [ "$REPLY" = 'no other' ] && continue
    count="$( <<< "$REPLY" cut -d' ' -f1 )"
    color="$( <<< "$REPLY" cut -d' ' -f2,3 )"
    recurse="$( countContained "$color" )" 
    echo $(( count * (recurse + 1) ))
  done < <(
    < input.normalized grep "^$1" |
      sed -e 's/^.*contain[[:space:]]*//' |
      tr , '\n' 
  ) | paste -s -d+ -
}

countContained 'shiny gold'

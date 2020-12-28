#!/usr/bin/env bash

todo="$( < input.raw grep -F ':' | tr -d '"' | sed -e 's/$/ /' -e 's/ /  /g' )"
while true ; do
  done="$( <<< "$todo" grep ':[ ()|ab]*$' )"
  todo="$( <<< "$todo" grep ':.*[0-9]' )"
  [ -z "$todo" ] && break
  commands=()
  while read ; do
    IFS=':' read field repl <<< "$REPLY"
    <<< "$repl" grep -qF '|' && repl="( $repl )"
    commands+=( -e "s/ ${field} / ${repl} /g" )
  done <<< "$done"
  todo="$( <<< "$todo" sed "${commands[@]}" | tr -s ' ' | sed -e 's/ /  /g' )"
done

IFS=':' read _ pattern <<< "$done"
pattern="$( <<< "$pattern" tr -d ' ' | sed -e 's/\([()|]\)/\\\1/g' )"
< input.raw grep -vF ':' | grep "^$pattern$" | wc -l

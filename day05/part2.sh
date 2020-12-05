< input.raw tr 'FLBR' '0011' |
  ( echo 'ibase=2'; cat - ) |
  bc |
  sort -n |
  sed 'p' |
  tail -n +2 |
  tail -r |
  tail -n +2 |
  paste -d- - - |
  sed 'p' |
  sed -e 's/^/="; /' |
  paste -d'\0' - - |
  cut -c 5- |
  sed -e 's/^/print "/' |
  bc |
  grep '=2' |
  cut -d- -f1 |
  sed -e 's/$/-1/' |
  bc

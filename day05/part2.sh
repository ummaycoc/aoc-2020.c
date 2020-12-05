< input.raw tr 'FLBR' '0011' | # FBFBFLRL -> 01010010
  ( echo 'ibase=2'; cat - ) | # prepend line with 'ibase=2'
  bc | # binary to decimal
  sort -n | # sort by numeric value
  sed 'p' | # duplicate each line
  tail -n +2 | # drop the first line
  tail -r | # reverse the lines
  tail -n +2 | # drop the first (originally last) line
  paste -d- - - | # combine to line[2i] - line[2i+1], e.g. 55-43
  sed -e 's/^/="; /' | # prepend '="; ' to each line, e.g. '="; 55-43'
  sed 'p' | # duplicate each line
  paste -d'\0' - - | # combine line[2i][line[2i+], e.g. '="; 55-43="; 55-43'
  cut -c 5- | # drop prefix, e.g. '55-43="; 55-43'
  sed -e 's/^/print "/' | # add print command, e.g. 'print "55-43="; 55-43'
  bc | # calculate, e.g. '55-43=12'
  grep '=2$' | # find where sorted items differed by 2, e.g. '65-63=2'
  cut -d- -f1 | # get number before minus sign, e.g. '65'
  sed -e 's/$/-1/' | # add -1 to that line, e.g. '65-1'
  bc # calculate that result -- what was between the two items differing by 2.

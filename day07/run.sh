< input.raw sed -e 's/bags/bag/g' -e 's/[[:space:]]bag//g' -e 's/\.$//g' -e 's/,[[:space:]]/,/g' > input.normalized

echo -n 'Part 1: '
./part1.sh
echo -n 'Part 2: '
./part2.sh
rm -f input.normalized

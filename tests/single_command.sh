#!/bin/sh

# Single Commands
# 2 simple commands, command with many arguments, command with no arguments, invalid command

cd ../
make

bin/rshell <<'EOF'
echo hello world
echo hello ||
echo hello commander &&
|| echo hello world
ls -l
echo one two three four five six 7 eight nine ten
echo
exit
EOF

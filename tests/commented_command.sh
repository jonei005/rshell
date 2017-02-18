#!/bin/sh

# Commented Commands
# comment with space/no space after, with connector, at beginning/end of input

cd ../
make

bin/rshell <<'EOF'
ls #-l
ls # -l
echo hello # world
echo hello world && ls # -l
echo hello world && #
#echo hello world
# echo hello world
exit
EOF
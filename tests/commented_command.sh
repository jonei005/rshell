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
echo hello world &&#
echo u && echo b  #############a 
echo tests #uausuau echo tests
echo a 
(echo a) || echo b# echo asdasdasdasdasd
(echo a || (echo b && echo c))
#echo hello world
# echo hello world
echo a # echo b 
exit
EOF

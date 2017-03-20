#!/bin/sh

cd ../
make

bin/rshell <<'EOF'
echo This is the first line. > text.txt
echo This is the second line. >> text.txt
echo This is the 3rd line. >> text.txt
cat < text.txt
echo Word Count: && cat < text.txt | wc -c
echo First Two Lines: ; cat < text.txt | head -2
echo Hello world! > hello.txt
echo I am a robot. >> hello.txt
cat < hello.txt | wc -c
cat < hello.txt | head -1
ls -l | wc -l >> numFiles.txt
echo Number of characters in ls command: && ls | wc -c 
exit
EOF

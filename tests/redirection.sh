#!/bin/sh

cd ../
make

#Output -------------------------
bin/rshell <<'EOF'


ls -l > fileInfo.txt
echo Give us an A >> lastRequest.txt
touch hello.txt
echo Hello world! > hello.txt
echo I am a robot. >> hello.txt
echo Beep boop. >> hello.txt
[ hello.txt ] && echo hello.txt exists > exists.txt
[ goodbye.txt ] || echo goodbye.txt doesn't exist >> exists.txt
exit
EOF

#Input --------------------------
bin/rshell <<'EOF'
cat < hello.txt
cat < hello.txt | wc -c
cat < hello.txt | head -1
cat < hello.txt > hello2.txt
cat < lastRequest.txt >> hello2.txt

echo Lines: > wordcount.txt
cat < hello.txt | wc -l >> wordcount.txt

echo Characters: >> wordcount.txt && cat < hello.txt | wc -c >> wordcount.txt
cat < wordcount.txt
exit
EOF

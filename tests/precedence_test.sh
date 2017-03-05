#!/bin/sh


cd ../
make

bin/rshell <<'EOF'

(echo a) && (echo b)
(echo a && echo b)
(echo a || echo b)
( echo a || echo b )
(echo a || (echo b || echo c)) || echo d
(echo a) || (echo b)
(echo a || echo b)

((echo a && echo b) && echo c)
(([ -f bin/rshell ] && echo path exists) || echo path doesn't exist)
exit
EOF

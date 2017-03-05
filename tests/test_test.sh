#!/bin/sh

#Tests test commands

cd ../
make

bin/rshell <<'EOF'
[ -f bin/rshell ]
[ -e bin/rshell ]
[ -d bin/rshell ]
[ bin/rshell ]

test -f bin/rshell
test -e bin/rshell
test -d bin/rshell
test bin/rshell

([ -f bin/rshell ] && echo path exists)
(echo checking if "bin" folder exists... ; [ -d bin ] && echo it exists || echo it doesn't)
(echo checking if "foo" folder exists... ; [ -d foo ] && echo it exists || echo it doesn't)
exit
EOF

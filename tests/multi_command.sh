#!/bin/sh

# Multiple Commands (with connectors)
# commands with 1 of each connector, commands with 2 of each connector,
# commands with multiple different connectors, commands with connectors and invalid commands

cd ../
make

bin/rshell <<'EOF'
echo hello world && echo hi there
invalid command && echo hi there
echo hello world && echo hi there && ls
echo hello world && invalid command && echo hi there
echo hello world || echo hi there
invalid command || echo hi there
echo hello world || echo hi there || ls
echo hello world || invalid command || echo hi there
echo hello world ; echo hi there
invalid command ; echo hi there
echo hello world ; echo hi there ; ls
echo hello world ; invalid command ; echo hi there
echo hello world || echo hi there ; ls -l
invalid command || echo hi there && ls -l
echo hello world && echo hi there || ls -l
echo hello world && invalid command ; another invalid command || echo hi there && ls
exit
EOF
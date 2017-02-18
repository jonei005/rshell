#!/bin/sh

# Commands with Exit
# Note: so far, seems like after running through statements with comments,
#  exit has strange behavior (not exiting, outputting old echoes, etc)      
# Note: after some changes, haven't been able to recreate bug where exit() 
#  causes Putty to close, but that does not mean its gone

cd ../
make

bin/rshell <<<'exit hello world'
bin/rshell <<<'echo hello world && exit'
bin/rshell <<<'echo hello world || echo lets exit || exit'
bin/rshell <<<'echo hello world ; exit ; echo hi there'
bin/rshell <<<'echo hello world || exit || echo hi there && exit'





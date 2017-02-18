RSHELL
======

Overview
--------
The goal of rshell is to act as a command line. It works by executing commands from the /usr/bin directory, which can be chained together with "&&", "||" or ";". Comments can be made by using the "#" symbol.  

How To Run
----------
To download and run rshell, run these commands:
```
1. git clone https://github.com/jonei005/rshell.git

2. cd rshell

3. git checkout hw2

4. make

5. bin/rshell
```
Test scripts must be run from inside the /tests directory

Bugs
----
- There is occasional undefined behavior with the "exit" command:
	- Exit sometimes will close the terminal that is running rshell 
	- Exit will sometimes output old echoes
	- This is usually the result of running 1 or more invalid commands before "exit"
- In multi_command.sh will sometimes keep iterating previous arguments until it reads EOF
    - This occurs only after chaining multiple connectors and running 1 or more invalid commands.
- Semicolon must have whitespace before and after, or it wont read the semicolon

Authors
-------
Jeremy O'Neill

Justin Miranda

License
-------
Licensed under the terms of the GNU General Public License
View LICENSE file for more details.





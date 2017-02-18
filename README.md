RSHELL
======

Overview
--------
The goal of rshell is to output commands from /usr/bin. Essentially we are trying to simulate the command prompt in hammer with additional commands called connectors, ";","||",and "&&".
Using these additional commands in tandum with /bin commands. Semicolon will execute the next set of commands no matter what. "||" will execute the next set of commands
if the previous commands before "||" are false. "&&" will do that opposite of "||" it will execute the next commands if the previous commands. Similar to the command prompt if the user types exit
anywhere in the command prompt, rshell will quit. Also we implemented "#" that will comment anything after out of the string or arguments. 

How To Run
----------
```
1. git clone https://github.com/jonei005/rshell.git

2. cd rshell

3. git checkout hw2

4. make

5. bin/rshell
```
Testing scripts must be run from inside the /tests directory

Bugs
----
- exit sometimes will close the terminal that is running rshell 
- exit will sometimes output old echoes
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





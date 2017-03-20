#include <iostream>
#include "Shell.h"
#include "Command.h"
#include "Connector.h"
#include "And.h"
#include "Or.h"
#include "Semicolon.h"
#include "TestCommand.h"
#include "Parentheses.h"
#include "Redirector.h"
#include "OutputRedirector.h"
#include "InputRedirector.h"
#include "DoubleRedirector.h"
#include "Pipe.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <stack>

void ccFunction(char** & command_args, Command* & command,int  col_size);
Shell* findShell(char** newArray);
bool connectorFound(char** arr, int i);


// Abstract base class for RShell
#ifndef SHELL_H
#define SHELL_H

class Shell {

	public:
		
		// Constructor
		Shell() {}
		
		// Abstract
		virtual void evaluate() = 0;
		
		virtual bool getExecute() = 0;
		
		virtual void setExecute(bool newExecute) {}
		
		virtual bool succeeded() = 0;
		
		virtual bool getAnySuccess() = 0;
		
		virtual void setRightChild(Shell* newChild) {};
		
		virtual Shell* getChild() {}
		
		virtual char** getArgs() {}
		
		virtual bool is_parentheses() {}
		
		virtual Shell* getRightChild() {}
		
		virtual int pipeEvaluate() {}

};

#endif

// Abstract base class for RShell

class Shell {

	public:
		
		// Constructor
		Shell() {}
		
		// Abstract
		virtual void evaluate() = 0;
		
		virtual bool getExecute() = 0;
		
		virtual void setExecute(bool newExecute) {}
		
		virtual bool succeeded() = 0;

};

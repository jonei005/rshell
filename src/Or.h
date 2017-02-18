

class Or : public Connector {

	// Inherited from Connector:
	// Command* leftChild, Shell* rightChild, bool execute

	public: 
		
		// Constructors
		Or() {}
		
		Or(Command* left)
		 : Connector(left) {}
		
		Or(Command* left, Shell* right)
		 : Connector(left, right) {}
		
		Or(Command* left, Shell* right, bool execute)
		 : Connector(left, right, execute) {}

		void evaluate() {
			// check if left child succeeded (using leftChild->success())
			// if succeeded, rightChild->execute = 0, evaluate 
			// if not, rightChild->execute = 1, evaluate

			leftChild->setExecute(execute);
			leftChild->evaluate();	
			
			// check if leftChild->evaluate() succeeded or not
			if (leftChild->succeeded()) {
				// if leftChild succeeded, set right->execute to 0
				rightChild->setExecute(0);
				rightChild->evaluate();
			}
			else {
				// if leftChild failed, set right->execute to 1, then evaluate
				rightChild->setExecute(1);				
				rightChild->evaluate();
			}

		}

		void setLeftChild(Command* newChild) {
			leftChild = newChild;
		}

		void setRightChild(Shell* newChild) {
			rightChild = newChild;
		}

		void setExecute(bool newExecute) {
			execute = newExecute;
		}	
		
		Command* getLeftChild() {
			return leftChild;
		}

		Shell* getRightChild() {
			return rightChild;
		}

		bool getExecute() {
			return execute;
		}
};

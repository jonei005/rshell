
class Semicolon : public Connector {

	// Inherited from Connector:
	// Command* leftChild, Shell* rightChild, bool execute

	public: 
		
		// Constructors
		Semicolon() {}
		
		Semicolon(Command* left)
		 : Connector(left) {}
		
		Semicolon(Command* left, Shell* right)
		 : Connector(left, right) {}
		
		Semicolon(Command* left, Shell* right, bool execute)
		 : Connector(left, right, execute) {}

		void evaluate() {
			// no matter what left child does, evaluate right child

			leftChild->setExecute(execute);
			leftChild->evaluate();		
			
			// regardless of leftChild->execute(), execute rightChild
			rightChild->setExecute(1);			
			rightChild->evaluate();
			
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

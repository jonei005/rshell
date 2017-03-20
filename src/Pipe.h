#ifndef PIPE_H
#define PIPE_H

class Pipe : public Connector {
    
    // Inherited from Connector
    // Shell* leftChild
    // Shell* rightChild
    // bool execute
    // bool anySuccess
    
  
  
  public:
    
        Pipe() : Connector() {}
		
		Pipe(Shell* left)
		 : Connector(left) {}
		
		Pipe(Shell* left, Shell* right) 
		 : Connector(left, right) {}
		
		Pipe(Shell* left, Shell* right, bool execute)
		 : Connector(left, right, execute) {}
        
        void evaluate() {
            
            int pipe1[2];
            int pipe2[2];
            
            pipe(pipe1);
            
            pid_t pid;
            
            pid = fork();
            
            int execStatus = 0;
            int execStatus2 = 0;
            
	        if(pid == -1) {
	            perror("fork");
	        } 
	        else if (pid == 0) {
	            // child
	            
	            pipe(pipe2);
	            pid_t pid2;
	            pid2 = fork();
	            
	            if (pid2 == -1) {
					perror("second fork");
				}
				else if (pid2 == 0) {
					//child
					close(pipe2[0]);
	            
					dup2(pipe2[1], 1);
					//close(pipe2[1]);
				   
					execStatus = leftChild->pipeEvaluate();
					
					//char** command_args = leftChild->getArgs();
					//execStatus = execvp(command_args[0], command_args);
				}
				else {
					//parent
					waitpid(pid2, 0, 0);
					
					close(pipe2[1]);
					dup2(pipe2[0], 0);
					close(pipe2[0]);
					
					execStatus2 = rightChild->pipeEvaluate();
					
					//char** command_args = rightChild->getArgs();
					//execvp(command_args[0], command_args);
				}
	           
	        }
	        else {
	            waitpid(pid, 0, 0);
	            //cout << "main parent, finished both processes" << endl;
	            // parent
                
	        }
		
        }
    
        bool getExecute() {
            return execute;
        };
		
		void setExecute(bool newExecute) {
		    execute = newExecute;
		    return;
		}
		void setLeftChild(Shell* newChild) {
			leftChild = newChild;
		}

		void setRightChild(Shell* newChild) {
			rightChild = newChild;
		}
		
		Shell* getLeftChild() {
			return leftChild;
		}

		Shell* getRightChild() {
			return rightChild;
		}
	
		

		

};





#endif
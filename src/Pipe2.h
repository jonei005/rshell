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
            pipe(pipe2);
            
            int execStatus = 0;
            int execStatus2 = 0;
            
            pid_t child1;
            pid_t child2;
            child1 = fork();
            if (child1 <= -1) {
            	perror("fork");
            }
            else if (child1 == 0) {
            	// we're in child1
            	dup2(pipe1[1],STDOUT_FILENO);
            	close(pipe1[1]);
            	close(pipe1[0]);
            	
            	dup2(pipe2[0],STDIN_FILENO);
            	close(pipe2[1]);
            	close(pipe2[0]);
            	
            	char** command_args = leftChild->getArgs();
					
			    execStatus = execvp(command_args[0], command_args);
			    perror("execvp child 1");
			    free(command_args);
            }
            else {
                
            	child2 = fork();
            	if (child2 <= -1) {
            		perror("fork");
            	}
            	else if (child2 == 0) {
            		// we're in child2
                	dup2(pipe1[0],STDIN_FILENO);
                	close(pipe1[1]);
                	close(pipe1[0]);
                	
                	dup2(pipe2[1],STDOUT_FILENO);
                	close(pipe2[1]);
                	close(pipe2[0]);
                	
                	char** command_args = rightChild->getArgs();
					
					execStatus2 = execvp(command_args[0], command_args);
					perror("execvp child 2");
					free(command_args);
            	}
            	else {
            		//In Parent Waiting for Child 2
            		waitpid(child2, 0, 0);
            	}
            	
            	
            	//In Parent Waiting for Child 1
            	waitpid(child1, 0, 0);
            	
            }
         //   int execStatus = 0;
            
	        // if(pid == -1) {
	        //     perror("fork");
	        // } 
	        // else if (pid == 0) {
	        //     // child
	        //     int stdout = dup(1);
	        //     int stdin = dup(0);
	            
	        //     // change stdout to pipe1 write
	        //     dup2(pipe1[1], 1);
	            
	        //     close(pipe1[0]);
	        //     close(pipe1[1]);
	            
	        //     leftChild->evaluate();
	            
	        // }
	        // else {
	        //     waitpid(pid, 0, 0);
	        //     // parent
                
         //       close(pipe1[1]);
         //       dup2(pipe1[0], 0);
         //       close(pipe1[0]);
         //       rightChild->evaluate();
                
	        // }
	        
	        
            
            
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
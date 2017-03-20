#ifndef REDIRECTOR_H
#define REDIRECTOR_H

using namespace std;

class Redirector : public Shell {
    
    protected:
        bool execute;
        bool success;
        char** command;
        char* filename;
        
    public:
        Redirector() {}
            
        Redirector(char** command, char* filename) 
            : execute(1), command(command), filename(filename) {}
            
        virtual void evaluate() = 0;
        
        virtual int pipeEvaluate() {}
    
};

#endif
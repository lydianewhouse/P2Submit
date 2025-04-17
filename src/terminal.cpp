#include "terminal.h"
#include "mypipe.h"
#include "utility.h"

// run_cmd:
// Takes a vector of C-style strings (char*), representing the command and its arguments.
// Forks a child process, redirects its standard output, and executes the command.
// Captures the output using a custom pipe (mypipe) and prints it to the terminal.
// Returns 0 on success, non-zero on failure.
int run_cmd(std::vector<char*> argv)
{
    //Creates the pipe
    mypipe pipe;

    //Forks into a child process
    auto pid{fork()};

    //Checks if fork failed
    if (pid < 0)
    {
        perror("Fork Failed");
        return -1;
    }

    

    if (pid == 0) //Child process
    {
        //Redirects the standard output
        pipe.redirect();

        //Executes the command using input arguments
        //Change to execv??
        //First argument is command, then following arguments
        execvp(argv[0], argv.data());

        //Throws error if execution doesn't work
        exit(1);
    }
    else //Parent process
    {
        
        int status;


        //First waits for child to finish
        
        waitpid(pid, &status, 0);

        //Check if the exec() failed in the child process (wrong command)
        if (WEXITSTATUS(status) != 0) {
            std::cout << "Unrecognized command" << std::endl << std::endl;
            return 0;
        }
        

        

        //Then read from pipe
        std::cout << pipe.read() << "\n";
    }
    
    return 0;
}


// terminal_app:
// Implements a simple interactive terminal loop.
// Continuously prompts the user for input, parses it into command and arguments,
// and executes the command using run_cmd().
// Exits the loop when the user types "exit".

void terminal_app()
{
    auto loop{true};
    while(loop)
    {
        //Get input as a single string

        std::cout << "$";

        std::string inputarg;
        std::getline(std::cin, inputarg);

        //Check if input is exit
        if (inputarg == "exit")
        {
            return;
        }

        //Then convert it to a vector of strings
        std::vector<std::string> inputvector = cmd2vec(inputarg);


        //Then convert it to vector of c style strings
        std::vector<char*> argv = castArgs(inputvector);


        //Then executes the command
        run_cmd(argv);
    }

    return;
}
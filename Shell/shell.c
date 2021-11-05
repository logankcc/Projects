/*
File: shell.c
Author: Logan Copeland
Description: Basic shell program
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <pwd.h>

#define CMD_BUFFSIZE 1024
#define MAXARGS 10

int splitCommandLine(char* commandBuffer, char* args[], int maxargs);
void doCommand(char* args[], int numArgs);
int dotCharFilter(const struct dirent* d);

int main() {
    char commandBuffer[CMD_BUFFSIZE];
    char *args[MAXARGS];
    int numArgs;

    // print prompt
    printf("%%> ");
    fflush(stdout);

    while (fgets(commandBuffer, CMD_BUFFSIZE, stdin) != NULL) {

        // remove newline from the end of command line input
        *strchr(commandBuffer, '\n') = '\0';

        // split command line input into individual words
        numArgs = splitCommandLine(commandBuffer, args, MAXARGS);

        // splitCommandLine function testing
        /*
        printf("%d\n", numArgs);
        int i;
        for (i = 0; i < numArgs; i++){
        printf("%d: %s\n",i,args[i]);
        }
        */

        // execute a command if a command was entered
        if (numArgs > 0) {
            doCommand(args, numArgs);
        }

        // print prompt
        printf("%%> ");
        fflush(stdout);
    }
}

////////////////////////////// String Handling //////////////////////////////

//+
// Function:	skipChar
//
// Purpose:	This function skips over a given character in a string.
//		    For security, the function will not skip null characters.
//
// Parameters:
//          charPtr     pointer to string
//          skip	    character to skip
//
// Returns: A pointer to the first character after the given skipped character is returned.
//          If the first character of the string is not the given skip character or the 
//          given skip character is the null charcter, the passed pointer is returned
//-

char* skipChar(char *charPtr, char skip) {

    // protect the user from accessing elements outside of a string
    if (skip == '\0') {
        return charPtr;
    } else {
        // skip over instances of the char skip
        while (*charPtr == skip) {
            charPtr++;
        }

        return charPtr;
    }
}

//+
// Function:    splitCommandLine
//
// Purpose:	This function splits a string into an array of strings (words).
//          The array is passed as an argument. The string is modified by
//          replacing select space characters with null characters to
//          terminate each internal string.
//
// Parameters:
//          commandBuffer    string to split
//          args             array of char pointers
//          maxargs          size of array args & max number of arguments
//
// Returns:	The number of arguments < maxargs is returned.
//-

// NOTE: splitCommandLine does not recognize escape character ('\')
int splitCommandLine(char* commandBuffer, char* args[], int maxargs) {
    int numArgs = 0;

    while (1) {
        // find the pointer to the next word
        commandBuffer = skipChar(commandBuffer, ' ');
        // check for a null character
        if (*commandBuffer == '\0') {
            return numArgs;
        } else {
            // store the pointer in the arguments array
            args[numArgs] = commandBuffer;
            // increment the number of arguments
            numArgs++;
            // check that the number of arguments is less than the maximum allowable number of arguments
            if (numArgs > maxargs) {
                fprintf(stderr, "ERROR: Maximum number of arguments exceeded!\n");
                return -1;
            }
            // check for a space character
            if (strchr(commandBuffer, ' ') == NULL)
            {
                return numArgs;
            }
            // move to the next space character
            commandBuffer = strchr(commandBuffer, ' ');
            // replace the space character with a null character
            *commandBuffer = '\0';
            // increment the pointer
            commandBuffer++;
        }
    }
}

////////////////////////////// Command Handling //////////////////////////////

// typedef for pointer to command handling functions
typedef void (*cmdPtr)(char* args[], int numArgs);

// cmdStruct type associates a command name with a command handling function
typedef struct {
    char* cmdNamePtr;
    cmdPtr cmdFuncPtr;
} cmdStruct;

// prototypes for command handling functions
void exitFunc(char* args[], int numArgs);
void pwdFunc(char* args[], int numArgs);
void cdFunc(char* args[], int numArgs);
void lsFunc(char* args[], int numArgs);

// dispatch array contains each command name and the associated command handling function name
cmdStruct dispatchArray[] = {
    {"exit", exitFunc},
    {"pwd", pwdFunc},
    {"cd", cdFunc},
    {"ls", lsFunc},
    {NULL, NULL}
};

//+
// Function:	doCommand
//
// Purpose:	This function calls a command handling function from
//		    the command dispatch array based on the first argument passed
//		    in the args array.
//
// Parameters:
//          args	    command and parameters (array of pointers to strings)
//          numArgs	    number of elements in the args array
//
// Returns:	Nothing is returned (void).
//-

void doCommand(char* args[], int numArgs) {
    int i = 0;
    // compre the input command which each command within the dispatch table
    while (dispatchArray[i].cmdNamePtr != NULL) {
        if (strcmp(dispatchArray[i].cmdNamePtr, args[0]) == 0) {
            // call the command function associated with input command
            dispatchArray[i].cmdFuncPtr(args, numArgs);
            break;
        } else {
            i++;
        }
    }
    // if the command does not exist within the dispatch table print an error
    if (dispatchArray[i].cmdNamePtr == NULL) {
        fprintf(stderr, "ERROR: Command not recognized!\n");
    }
}

////////////////////////////// Command Handling Functions //////////////////////////////

//+
// Function:	all command handling functions
//
// Purpose:	These functions implement the functionality of each command.
//		    The name of the command is the first argument of the args array.
//          As the associated function is called by doCommand, it is known
//		    that args is at least one element long. All command handling 
//          functions have the same signature.
//
// Parameters:
//          args	    command and parameters (array of pointers to strings)
//          numArgs	    number of entries in the args array
//
// Returns:	Nothing is returned (void).
//-

// exit command function
void exitFunc(char *args[], int numArgs) {
    // exit the shell with and exit code of 0
    exit(0);
};

// pwd command function
void pwdFunc(char* args[], int numArgs) {
    // print current directory
    if (numArgs == 1) {
        char* cwd = getcwd(NULL, 0);
        printf("%s\n", cwd);
        // free dynamically allocated memory
        free(NULL);
        // print an error if multiple arguments were inputted
    } else {
        fprintf(stderr, "ERROR: Too many arguments!\n");
    }
}

// cd command function
void cdFunc(char* args[], int numArgs) {
    // retrieve a pointer to the password file entry of a user
    struct passwd* pw = getpwuid(getuid());

    if (numArgs == 1) {
        // check for password entry
        if (pw == NULL) {
            fprintf(stderr, "ERROR: No password entry!\n");
        } else {
            // change current directory to home directory
            chdir(pw->pw_dir);
        }
    } else if (numArgs == 2) {
        // check for password entry
        if (pw == NULL) {
            fprintf(stderr, "ERROR: No password entry!\n");
            // check if directory exists
        } else if (chdir(args[1]) != 0) {
            fprintf(stderr, "ERROR: Directory does not exist!\n");
        } else {
            // change current directory to target directory specfied by input argument
            chdir(args[1]);
        }
    } else {
        fprintf(stderr, "ERROR: Too many arguments!\n");
    }
}

// ls command function
void lsFunc(char* args[], int numArgs) {
    struct dirent** namelist;

    if (numArgs == 1) {
        // return the number of contents within the directory
        int numEnts = scandir(".", &namelist, dotCharFilter, alphasort);

        // print contents of directory excluding hidden files
        int i;
        for (i = 0; i < numEnts; i++) {
            printf("%s\n", namelist[i]->d_name);
        }
        // print all contents of directory
    } else if (numArgs == 2) {
        if (strcmp(args[1], "-a") == 0) {
            int numEnts = scandir(".", &namelist, NULL, alphasort);

            int i;
            for (i = 0; i < numEnts; i++) {
                printf("%s\n", namelist[i]->d_name);
            }
        } else {
            fprintf(stderr, "ERROR: Unrecognized argument!\n");
        }
    } else {
        fprintf(stderr, "ERROR: Too many arguments!\n");
    }
    // free dynamically allocated memory
    free(namelist);
}

// dot character ('.') filter function used for excluding hidden files
int dotCharFilter(const struct dirent* d) {
    // if file name begins with the dot character return 0
    if (d->d_name[0] == '.') {
        return 0;
    } else {
        return 1;
    }
}
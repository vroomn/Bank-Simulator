#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

void startGame();

int main(void) {
    //TODO: Retrieve username from disk
    bool usernameStored = false; //Temporary to fool the system

    //The username of the owner of the program
    char username[30];
    if (!usernameStored)
    {
        printf("Your new username (Max 25 chars)-> ");
        fgets(username, 30, stdin); //Grabs input from the command line
    }

    //Should the command-execute loop end
    bool endLoop = false;
    while (!endLoop)
    {
        //Holds the current command passed to the program
        char command[16];
        printf("Don' forget \"Help\"\n-> ");
        fgets(command, 16, stdin);
        int cmdLen = strlen(command)-1; //For removal of the newline
        command[cmdLen] = '\0';
        //Turns command into lowercase form for standardization
        for (size_t i = 0; i < cmdLen; i++)
        {
            command[i] = tolower(command[i]);
        }

        //Checks if the command is known and executes accordingly
        //The ! is necessary because "true" to strcmp is zero, not one
        if (!strncmp(command, "help", 16))
        {
            printf(
                "All commands are not case sensitive\n"
                "Start Game -> Begins a new game\n"
                "Exit -> Ends the program\n");
        }
        else if (!strncmp(command, "start game", 16))
        {
            printf("Starting Game\n");
        }
        else if (!strncmp(command, "exit", 16))
        {
            printf("Exiting!\n");
            endLoop = true;
        }
        else {
            printf("Invalid command!\n");
        }
        
    }
    
    return 0;
}

void startGame() {
    return;
}
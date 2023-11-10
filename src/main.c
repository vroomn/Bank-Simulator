#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void startGame();

void terminatorRemove(char* msg);

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
        printf("\e[1;1H\e[2J");//Clears the screen (https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c)
        //Holds the current command passed to the program
        char command[16];
        printf("Don't forget \"Help\"\n-> ");
        fgets(command, 16, stdin);
        //int cmdLen = strlen(command)-1; //For removal of the newline
        //command[cmdLen] = '\0';
        terminatorRemove(command);
        //Turns command into lowercase form for standardization
        for (size_t i = 0; i < strlen(command); i++)
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
            startGame();
            endLoop = true;
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

//Takes in char array and removes the last character, designed to be \n
void terminatorRemove(char* msg) {
    int len = strlen(msg)-1; //For removal of the newline
    msg[len] = '\0';
}

/*Get response from the command line
* @param message: The message to output to the command line, note final message is structured [yourMessage] (max 2 digits) ->
* @return The unsigned integer representation of the input from the CLI, if negative error in execution
*/
int getInt(char* message) {
    char num[2];//Max 2 digits
    printf("%s (max 2 digits) -> ", message);
    fgets(num, 2, stdin);
    fseek(stdin, 0, SEEK_END); //Moves to end of stdin buffer (https://stackoverflow.com/questions/7898215/how-can-i-clear-an-input-buffer-in-c)
    return strtol(num, (char**)NULL, 10);
}

void startGame() {
    //Number of other players in the game
    int numOfPlayers = getInt("Number of other players");

    //Names of each player
    char playerNames[numOfPlayers][25];
    for (size_t i = 0; i < numOfPlayers; i++)
    {
        printf("Player %d what is your name (25 chars) -> ", i+1);
        fgets(playerNames[i], 25, stdin);
        terminatorRemove(playerNames[i]); //TODO: Confirm name
    }
    return;
}
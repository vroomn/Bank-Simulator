#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#define EMPTYSCR printf("\e[1;1H\e[2J") //Clears the screen [less to type] (https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c)

typedef struct
{
    char name[25];
    int score;
}Player;

void startGame(Player user);

void terminatorRemove(char* msg);

void zeroPlayer(Player* player);

int main(void) {
    //TODO: Retrieve username from disk
    bool usernameStored = false; //Temporary to fool the system

    //The username of the owner of the program
    Player user;
    zeroPlayer(&user);
    if (!usernameStored)
    {
        printf("Your new username (Max 25 chars)-> ");
        fgets(user.name, 25, stdin); //Grabs input from the command line
        terminatorRemove(user.name);
    }

    //Should the command-execute loop end
    bool endLoop = false;
    while (!endLoop)
    {
        EMPTYSCR;
        //Holds the current command passed to the program
        char command[16];
        printf("Don't forget \"Help\"\n-> ");
        fgets(command, 16, stdin);
        //int cmdLen = strlen(command)-1; //For removal of the newline
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
            startGame(user);
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

void zeroPlayer(Player* player) {
    memset(player->name, 0, sizeof(player->name));
    player->score = 0;
    return;
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
    char num[3];//Max 2 digits
    printf("%s (max 2 digits) -> ", message);
    fgets(num, 3, stdin);
    fseek(stdin, 0, SEEK_END); //Moves to end of stdin buffer (https://stackoverflow.com/questions/7898215/how-can-i-clear-an-input-buffer-in-c)
    return strtol(num, (char**)NULL, 10);
}

//Primary game loop
void startGame(Player user) {
    //Number of other players in the game
    int numOfPlayers = getInt("Number of other players");

    //Names of each player
    Player players[numOfPlayers+1];
    for (size_t i = 0; i < numOfPlayers; i++)
    {
        printf("Player %d what is your name (25 chars) -> ", i+1);
        zeroPlayer(&players[i]);
        fgets(players[i].name, 25, stdin);
        terminatorRemove(players[i].name); //TODO: Confirm name
    }

    /*Insert main user at random location within the array*/
    //Offset of where the main user will be placed
    int userOffset = rand() % numOfPlayers;// (https://stackoverflow.com/questions/822323/how-to-generate-a-random-int-in-c)
    for (size_t i = 0; i < numOfPlayers; i++)
    {
        int current = numOfPlayers-(i+1);
        if (current >= userOffset)
        {
            players[(numOfPlayers-i)] = players[current];
        }   
    }
    players[userOffset] = user;
    numOfPlayers++;

    EMPTYSCR;
    //Number of holes
    int holeCount = getInt("How many holes on the course");
    for (size_t i = 0; i < holeCount; i++)
    {
        EMPTYSCR;
        for (size_t j = 0; j < numOfPlayers; j++)
        {
            printf("(HOLE %d) What did %s (Player %d) get", i+1, players[j].name, j+1);
            players[j].score += getInt("");
        }
        
        //Sort the array(using inverted quicksort)
        for (size_t t = 1; i < numOfPlayers; t++)
        {
            int j = t;
            while (j > 0 && players[j-1].score > players[j].score)
            {
                Player swapHolder = players[j];
                players[j] = players[j-1];
                players[j-1] = swapHolder;
                j--;
            }
        }

        if ((i+1) < numOfPlayers) {
            //Display the sorted array
            EMPTYSCR;
            printf("THE CURRENT STANDINGS (WAIT 10 SECS)\n");
            for (size_t i = 0; i < numOfPlayers; i++)
            {
                printf("In position %d is %s with %d points!\n", i+1, players[i].name, players[i].score);
            }
            sleep(10); //Ten second delay
        }
    }

    EMPTYSCR;
    printf("THE FINAL SCORES ARE (PRESS ENTER TO EXIT):\n");
    for (size_t i = 0; i < numOfPlayers; i++)
    {
        printf("In position %d is %s with %d points!\n", i+1, players[i].name, players[i].score);
    }
    getchar();

    return;
}
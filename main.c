﻿//
//  main.c
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include <time.h>
#include <string.h>
#include "smm_object.h"
#include "smm_database.h"
#include "smm_common.h"

#define BOARDFILEPATH "marbleBoardConfig.txt"
#define FOODFILEPATH "marbleFoodConfig.txt"
#define FESTFILEPATH "marbleFestivalConfig.txt"



//board configuration parameters
static int board_nr;
static int food_nr;
static int festival_nr;

static int player_nr;


typedef struct player {
    int energy;
    int position;
    char name[MAX_CHARNAME];
    int accumCredit;
    int flag_graduate;
} player_t;


static player_t cur_player[MAX_PLAYER];

#if 0
static int player_energy[MAX_PLAYER];
static int player_position[MAX_PLAYER];
static char player_name[MAX_PLAYER][MAX_CHARNAME];
#endif

//function prototypes
#if 0
int isGraduated(void); //check if any player is graduated
void printGrades(int player); //print grade history of the player
void goForward(int player, int step); //make player go "step" steps on the board (check if player is graduated)
void printPlayerStatus(void); //print all player status at the beginning of each turn
float calcAverageGrade(int player); //calculate average grade of the player
smmGrade_e takeLecture(int player, char* lectureName, int credit); //take the lecture (insert a grade of the player)
void* findGrade(int player, char* lectureName); //find the grade from the player's grade history
void printGrades(int player); //print all the grade history of the player
#endif


void printPlayerStatus(void)
{
    int i;

    for (i = 0; i < player_nr; i++)
    {
        printf("%s : credit %i, energy %i, position %i\n",
            cur_player[i].name,
            cur_player[i].accumCredit,
            cur_player[i].energy,
            cur_player[i].position);
    }
}

void generatePlayers(int n, int initEnergy) //generate a new player
{
    int i;
    //n time loop
    for (i = 0; i < n; i++)
    {
        //input name
        printf("Input player %i's name:", i); //¾È³» ¹®±¸ 
        scanf("%s", cur_player[i].name);
        fflush(stdin);

        //set position
        //player_position[i] = 0;
        cur_player[i].position = 0;

        //set energy
        //player_energy[i] = initEnergy;
        cur_player[i].energy = initEnergy;
        cur_player[i].accumCredit = 0;
        cur_player[i].flag_graduate = 0;
    }
}


int rolldie(int player)
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar();
    fflush(stdin);

#if 0
    if (c == 'g')
        printGrades(player);
#endif

    return (rand() % MAX_DIE + 1);
}

//action code when a player stays at a node
void actionNode(int player)
{
    int type = smmObj_getNodeType(cur_player[player].position);

    switch (type)
    {
        //case lecture:
    case SMMNODE_TYPE_LECTURE:
        if
            cur_player[player].accumCredit += smmObj_getNodeCredit(cur_player[player].position);
        cur_player[player].energy -= smmObj_getNodeEnergy(cur_player[player].position);
        break;

    default:
        break;
    }
}

void goForward(int player, int step)
{
    cur_player[player].position += step;

    printf("%s go to node %i (name: %s)\n",
        cur_player[player].name, cur_player[player].position,
        smmObj_getNodeName(cur_player[player].position));
}

// # 게임 종료 조건
boolean isGraduated() {
    for(int i=0; i<MAX_PLAYER;i++){
        if (cur_player[i].flag_graduate == 1) {
            return true;
        }
        
    }
    

}



int main(int argc, const char* argv[]) {

    FILE* fp;
    char name[MAX_CHARNAME];
    int type;
    int credit;
    int energy;
    int i;
    int initEnergy;
    int turn = 0;

    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;

    srand(time(NULL));


    //1. import parameters ---------------------------------------------------------------------------------
    //1-1. boardConfig 
    if ((fp = fopen(BOARDFILEPATH, "r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar();
        return -1;
    }

    printf("Reading board component......\n");
    while (fscanf(fp, "%s %i %i %i", name, &type, &credit, &energy) == 4) //read a node parameter set
    {
        //store the parameter set
        smmObj_genNode(name, type, credit, energy);
        if (type == SMMNODE_TYPE_HOME)
            initEnergy = energy;
        board_nr++;
    }
    fclose(fp);
    printf("Total number of board nodes : %i\n", board_nr);


    for (i = 0; i < board_nr; i++)
        printf("node %i : %s, %i(%s), credit %i, energy %i\n",
            i, smmObj_getNodeName(i),
            smmObj_getNodeType(i), smmObj_getTypeName(smmObj_getNodeType(i)),
            smmObj_getNodeCredit(i), smmObj_getNodeEnergy(i));

    printf("(%s)", smmObj_getTypeName(SMMNODE_TYPE_LECTURE));

#if 0
    //2. food card config 
    if ((fp = fopen(FOODFILEPATH, "r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        return -1;
    }

    printf("\n\nReading food card component......\n");
    while () //read a food parameter set
    {
        //store the parameter set
    }
    fclose(fp);
    printf("Total number of food cards : %i\n", food_nr);



    //3. festival card config 
    if ((fp = fopen(FESTFILEPATH, "r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        return -1;
    }

    printf("\n\nReading festival card component......\n");
    while () //read a festival card string
    {
        //store the parameter set
    }
    fclose(fp);
    printf("Total number of festival cards : %i\n", festival_nr);
#endif


    //2. Player configuration ---------------------------------------------------------------------------------

    do
    {
        //input player number to player_nr
        printf("input player no.:");
        scanf("%d", &player_nr);
        fflush(stdin);
    } while (player_nr < 0 || player_nr >  MAX_PLAYER);

    generatePlayers(player_nr, initEnergy);





    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while (1) //is anybody graduated?
    {
        int die_result;


        //4-1. initial printing
        printPlayerStatus();

        //4-2. die rolling (if not in experiment)        
        die_result = rolldie(turn);

        //4-3. go forward
        goForward(turn, die_result);

        //4-4. take action at the destination node of the board
        actionNode(turn);

        //4-5. next turn
        turn = (turn + 1) % player_nr;
        //종료조건
        if (isGraduated() == true) break;//graduated시 반복문 종료 
    }

    system("PAUSE");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "art.h"

#define NO_OF_CREATED_CHOICES 15

//=======================================================
//                    TYPEDEF SHIT
//=======================================================
typedef enum {
    STATE_MENU,
    STATE_CRAFT,
    STATE_MINE,
    STATE_WOOD,
    STATE_IRON,
    STATE_DIAMONDS,
    STATE_FIGHT,
    STATE_INVENTORY,
    STATE_HEAL,
    STATE_BASE,
    STATE_LEAVE,
    STATE_ERR
} State;

typedef struct {
    const char *label;
} Choice;

typedef struct {
    const char *main_label;
    Choice     choices[NO_OF_CREATED_CHOICES];
    int        total;
    int        pos_menu;
} Menu;

//=======================================================
//                 FUNCTIONS DECLARATION
//=======================================================

int kets();
int move_in_menu(Menu * menu);
State handle_MAIN_menu();
State handle_mine_menu();
void clean_buffer();
int input_int(int min, int max);
int input_string(char inputed_str[], int inputed_str_size,char outputed_text[]);
void set_cursor_to_zero();
void clear_screen_CONTINUE();
void print_menu(Menu printed_MENU);

//=======================================================
//                     MENU CREATION 
//            TODO: crafting & encounter menu
//=======================================================

Menu main_menu = {
    "main menu",
    { {"0. LEAVE"}, {"1. CRAFT"}, {"2. MINE"}, {"3. FIGHT"}, {"4. INVENTORY"}, {"5. HEAL"}, {"6. BASE"} },
    7,
    0 //pos
};
Menu mine_menu = {
    "mining menu",
    { {"0. BACK"}, {"1. MINING WOOD"}, {"2. MINING IRON"}, {"3. MINING DIAMONDS"} },
    4,
    0 //pos
};
Menu fighting_menu = {
    "fighting menu",
    { {"0. BACK"}, {"1. BOSS FIGHT"}, {"2. EXPLORE (plains)"}, {"3. EXPLORE (caves)(WIP)"}},
    4,
    0 //pos
};
Menu boss_menu = {
    "BOSS menu",
    { {"0. BACK"}, {"1. LEVEL - 1 Samurai"}, {"2. LEVEL - 2 Mage"}, {"3. LEVEL - 3 Tank"}, {"4. LEVEL - 4 Assasin"}, {"5. RANDOM LEVEL"} },
    6,
    0 //pos
};
Menu base_menu = {
    "base menu",
    { {"0. BACK"}, {"1. VILLAGERS (WIP)"}, {"2. STORAGE"}, {"3. PETS"} },
    4,
    0 //pos
};


//=======================================================
//                        MAIN
//=======================================================

int main(){
    //###################
    //      CONSOLE
    //###################
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);//ai schovani kurzoru
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = FALSE; 
    SetConsoleCursorInfo(out, &cursorInfo);

    system("cls");

    srand(time(NULL));
	SetConsoleOutputCP(65001); //nastaveni UTF-8 pro windows, aby se zobrazovaly tyhle hezký kostičky :D (holy shit tohle napsalo vs za me)
    
    //###################
    //     VARIABLES
    //###################
    State current_status = STATE_MENU;


    //###################
    // MAIN CYCLE START
    //###################

    while(current_status != STATE_LEAVE){
        switch(current_status){
            case STATE_MENU:
                current_status = handle_MAIN_menu();
            break;

            case STATE_CRAFT:
                system("cls");
                printf("CRAFT\n");
                clear_screen_CONTINUE();
                current_status = STATE_MENU;
            break;

            case STATE_MINE:
                current_status = handle_mine_menu();
            break;

            case STATE_FIGHT:
                system("cls");
                printf("FIGHT\n");
                clear_screen_CONTINUE();
                current_status = STATE_MENU;
            break;

            case STATE_INVENTORY:
                system("cls");
                printf("INVENTORY\n");
                clear_screen_CONTINUE();
                current_status = STATE_MENU;
            break;

            case STATE_HEAL:
                system("cls");
                printf("HEAL\n");
                clear_screen_CONTINUE();
                current_status = STATE_MENU;
            break;

            case STATE_BASE:
                system("cls");
                printf("BASE\n");
                clear_screen_CONTINUE();
                current_status = STATE_MENU;
            break;

            case STATE_LEAVE:
                system("cls");
                printf("leaving\n");
                clear_screen_CONTINUE();
            break;

            case STATE_ERR:
                system("cls");
                printf("ERROR??? idk\n");
                clear_screen_CONTINUE();
            break;
            
        }
    }
    
    //###################
    //   MAIN CYCLE END
    //###################
    system("cls");


    return 0;
}

//=======================================================
//                      FUNCTIONS 
//=======================================================


void clean_buffer(){
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

int input_int(int min, int max) {
	int tmp = 0;
	while(1) {
		printf("\n CHOOSE: " );
		int is_input_valid = scanf("%d", &tmp);
		clean_buffer();
		if(is_input_valid == 0 || tmp <min || tmp >max) {
			printf(RED "\n ##failed to load number##" RESET);
			continue;
		}
		else {
			return tmp;
		}
	}
}

int kets(){
    int inputed_key = _getch();
    if(inputed_key == 0 || inputed_key == 224){
        inputed_key = _getch();
        inputed_key += 1000;
    }
    return inputed_key;
}

int move_in_menu(Menu * menu){
    int input = kets();
    switch(input){
        case 1080:
            if(menu->pos_menu == menu->total -1){
                menu->pos_menu = 0;
            }
            else{
                menu->pos_menu++;
            }
        break;
        case 1072:
            if(menu->pos_menu == 0){
                menu->pos_menu = menu->total -1;
            }
            else{
                menu->pos_menu--;
            }
        break;
        case 13:
            return 1;
        break;

        default:
            return 0;
        break;
    }
    return 0;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//               menu HANDLERS
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


State handle_MAIN_menu(){ //prints then checks for input using move in menu
    print_menu(main_menu); 
    if(move_in_menu(&main_menu)){
        system("cls");
        switch(main_menu.pos_menu){
            case 0:
                return STATE_LEAVE;
            break;

            case 1:
                return STATE_CRAFT;
            break;

            case 2:
                return STATE_MINE;
            break;

            case 3:
                return STATE_FIGHT;
            break;

            case 4:
                return STATE_INVENTORY;
            break;

            case 5:
                return STATE_HEAL;
            break;

            case 6:
                return STATE_BASE;
            break;

            default:
                return STATE_ERR;
            break;
        }
    }
    else{
        return STATE_MENU;
    }
}

State handle_mine_menu(){
    print_menu(mine_menu);
    if(move_in_menu(&mine_menu)){
        system("cls");
        switch(main_menu.pos_menu){
            case 0:
                return STATE_MENU;
            break;

            case 1:
                return STATE_IRON;
            break;

            case 2:
                return STATE_DIAMONDS;
            break;

            default:
                return STATE_ERR;
            break;
        }
    }
    else{
        return STATE_MINE;
    }
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//               BASIC FUNCTIONS
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


int input_string(char inputed_str[], int inputed_str_size, char outputed_text[]){
    while(1){
        printf("%s", outputed_text);
        if (fgets(inputed_str, inputed_str_size, stdin) == NULL){
            printf("\n ##failed to load string##");
            continue;
        }
        break;
    }
    int position = strcspn(inputed_str, "\n");
    if(inputed_str[position] == '\n'){
        inputed_str[position] = '\0';
    }
    else{
        clean_buffer();
    }
    return 0;
}

void set_cursor_to_zero(){
	COORD cursorPosition;// ts is highkey ai
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
void clear_screen_CONTINUE(){
	printf(BLUE "\n CONTINUE? (press enter)" RESET);
	getchar();
	system("cls");
}

void print_menu(Menu printed_MENU){
    printf(" ======%s======\n", printed_MENU.main_label);
    for(int i = 0; i < printed_MENU.total; i++){
        if(i == printed_MENU.pos_menu){printf(RED " >%s\n" RESET, printed_MENU.choices[i].label);}
        else{printf("  %s\n", printed_MENU.choices[i].label);}
    }
    set_cursor_to_zero();
}
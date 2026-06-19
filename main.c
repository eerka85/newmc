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
        STATE_HELMET,
        STATE_CHESTPLATE,
        STATE_LEGGINS,
        STATE_BOOTS,
        STATE_SWORD,
        STATE_PICKAXE,
        STATE_AXE,
        STATE_BACKPACK,
    STATE_MINE,
        STATE_WOOD,
        STATE_IRON,
        STATE_DIAMONDS,
    STATE_FIGHT,
        STATE_BOSS,
            STATE_SAMURAI,
            STATE_MAGE,
            STATE_TANK,
            STATE_ASSASSIN,
            STATE_RANDOM_BOSS,
        STATE_EXPLORE_PLAINS,
        STATE_EXPLORE_CAVES,
    STATE_INVENTORY,
    STATE_HEAL,
    STATE_BASE,
        STATE_VILLAGERS,
        STATE_STORAGE,
        STATE_PETS,
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

typedef struct {
    int no_of_TANKs_defeated;
	int player_hp_fighting;
	int bones;
	int leather;
	int wool;
	int wood;
	int iron;
	int diamonds;
	int i_helmet;
	int d_helmet;
	int i_chestplate;
	int d_chestplate;
	int i_leggings;
	int d_leggings; 
	int i_boots;
	int d_boots ;
	int d_sword; 
	int i_sword;
	int i_pickaxe;
	int d_pickaxe;
	int i_axe;
	int d_axe;
	int pet_doggos;
} Resources;

//=======================================================
//                 FUNCTIONS DECLARATION
//=======================================================

int kets();
int move_in_menu(Menu * menu);

State handle_MAIN_menu();
State handle_craft_menu();
State handle_mine_menu();
State handle_fighting_menu();
    State handle_boss_menu();
State handle_base_menu();

void clean_buffer();
int input_int(int min, int max);
int input_string(char inputed_str[], int inputed_str_size,char outputed_text[]);
void set_cursor_to_zero();
void clear_screen_CONTINUE();
void print_menu(Menu printed_MENU);

void print_craft_menu(Menu printed_MENU);
void print_inventory();

void wood_mine();
void iron_mine();
void diamond_mine();

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
Menu craft_menu = {
    "crafting table",
    { {"0. LEAVE"}, {"1. HELMET (5 iron/dia)"}, {"2. CHESTPLATE (8 iron/dia)"}, {"3. LEGGINS (6 iron/dia)"}, {"4. BOOTS (4 iron/dia)"}, {"5. SWORD (2 iron/dia) + (2 wood)"}, {"6. PICKAXE (3 iron/dia) + (2 wood)"}, {"7. AXE (3 iron/dia) + (2 wood)"}, {"8. BACKPACK (5 leather)"} },
    9,
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

Resources materials = {
    0, //no_of_TANKs_defeated
    10, //player_hp_fighting
    0, //bones
    0, //leather
    0, //wool
    0, //wood
    0, //iron
    0, //diamonds
    0, //i_helmet
    0, //d_helmet
    0, //i_chestplate
    0, //d_chestplate
    0, //i_leggings
    0, //d_leggings
    0, //i_boots
    0,  //d_boots
    0, //d_sword
    0, //i_sword
    0, //i_pickaxe
    0, //d_pickaxe
    0, //i_axe
    0, //d_axe
    0  //pet_doggos
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

            //   CRAFT      CRAFT      CRAFT      CRAFT      CRAFT      CRAFT

            case STATE_CRAFT:
                current_status = handle_craft_menu();
            break;
                case STATE_HELMET:
                    system("cls");
                    printf("HELMET\n");
                    clear_screen_CONTINUE();
                    current_status = STATE_CRAFT;
                break;
                case STATE_CHESTPLATE:
                    system("cls");
                    printf("CHESTPLATE\n");
                    clear_screen_CONTINUE();
                    current_status = STATE_CRAFT;
                break;
                case STATE_LEGGINS:
                    system("cls");
                    printf("LEGGINS\n");
                    clear_screen_CONTINUE();
                    current_status = STATE_CRAFT;
                break;
                case STATE_BOOTS:
                    system("cls");
                    printf("BOOTS\n");
                    clear_screen_CONTINUE();
                    current_status = STATE_CRAFT;
                break;
                case STATE_SWORD:
                    system("cls");
                    printf("SWORD\n");
                    clear_screen_CONTINUE();
                    current_status = STATE_CRAFT;
                break;
                case STATE_PICKAXE:
                    system("cls");
                    printf("PICKAXE\n");
                    clear_screen_CONTINUE();
                    current_status = STATE_CRAFT;
                break;
                case STATE_AXE:
                    system("cls");
                    printf("AXE\n");
                    clear_screen_CONTINUE();
                    current_status = STATE_CRAFT;
                break;
                case STATE_BACKPACK:
                    system("cls");
                    printf("BACKPACK\n");
                    clear_screen_CONTINUE();
                    current_status = STATE_CRAFT;
                break;

            //   MINE      MINE      MINE      MINE      MINE      MINE   

            case STATE_MINE:
                current_status = handle_mine_menu();
            break;

                case STATE_WOOD:
                    system("cls");
                    wood_mine();
                    clear_screen_CONTINUE();
                    current_status = STATE_MINE;
                break;

                case STATE_IRON:
                    system("cls");
                    iron_mine();
                    clear_screen_CONTINUE();
                    current_status = STATE_MINE;
                break;

                case STATE_DIAMONDS:
                    system("cls");
                    diamond_mine();
                    clear_screen_CONTINUE();
                    current_status = STATE_MINE;
                break;
            
            //   FIGHT      FIGHT      FIGHT      FIGHT      FIGHT      FIGHT   

            case STATE_FIGHT:
                current_status = handle_fighting_menu();
            break;
                case STATE_BOSS:
                    current_status = handle_boss_menu();
                break;
                    case STATE_SAMURAI:
                        system("cls");
                        printf("SAMURAI\n");
                        clear_screen_CONTINUE();
                        current_status = STATE_BOSS;
                    break;
                    case STATE_MAGE:
                        system("cls");
                        printf("MAGE\n");
                        clear_screen_CONTINUE();
                        current_status = STATE_BOSS;
                    break;
                    case STATE_TANK:
                        system("cls");
                        printf("TANK\n");
                        clear_screen_CONTINUE();
                        current_status = STATE_BOSS;
                    break;
                    case STATE_ASSASSIN:
                        system("cls");
                        printf("ASSASSIN\n");
                        clear_screen_CONTINUE();
                        current_status = STATE_BOSS;
                    break;
                    case STATE_RANDOM_BOSS:
                        system("cls");
                        printf("RANDOM BOSS\n");
                        clear_screen_CONTINUE();
                        current_status = STATE_BOSS;
                    break;
                case STATE_EXPLORE_PLAINS:
                    system("cls");
                    printf("EXPLORE PLAINS\n");
                    clear_screen_CONTINUE();
                    current_status = STATE_FIGHT;
                break;
                case STATE_EXPLORE_CAVES:
                    system("cls");
                    printf("EXPLORE CAVES IS WORK IN PROGRESS\n");
                    clear_screen_CONTINUE();
                    current_status = STATE_FIGHT;
                break;

            case STATE_INVENTORY:
                system("cls");
                print_inventory();
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
                current_status = handle_base_menu();
            break;
                case STATE_VILLAGERS:
                    system("cls");
                    printf("VILLAGERS IN PROGRESS\n");
                    clear_screen_CONTINUE();
                    current_status = STATE_BASE;
                break;
                case STATE_STORAGE:
                    system("cls");
                    printf("STORAGE\n");
                    clear_screen_CONTINUE();
                    current_status = STATE_BASE;
                break;
                case STATE_PETS:
                    system("cls");
                    printf("PETS\n");
                    clear_screen_CONTINUE();
                    current_status = STATE_BASE;
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
State handle_craft_menu(){ //prints then checks for input using move in menu
    print_craft_menu(craft_menu); 
    if(move_in_menu(&craft_menu)){
        system("cls");
        switch(craft_menu.pos_menu){
            case 0:
                return STATE_MENU;
            break;

            case 1:
                return STATE_HELMET;
            break;

            case 2:
                return STATE_CHESTPLATE;
            break;

            case 3:
                return STATE_LEGGINS;
            break;

            case 4:
                return STATE_BOOTS;
            break;

            case 5:
                return STATE_SWORD;
            break;

            case 6:
                return STATE_PICKAXE;
            break;

            case 7:
                return STATE_AXE;
            break;

            case 8:
                return STATE_BACKPACK;
            break;

            default:
                return STATE_ERR;
            break;
        }
    }
    else{
        return STATE_CRAFT;
    }
}

State handle_mine_menu(){
    print_menu(mine_menu);
    if(move_in_menu(&mine_menu)){
        system("cls");
        switch(mine_menu.pos_menu){
            case 0:
                return STATE_MENU;
            break;

            case 1:
                return STATE_WOOD;
            break;

            case 2:
                return STATE_IRON;
            break;

            case 3:
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
State handle_fighting_menu(){
    print_menu(fighting_menu);
    if(move_in_menu(&fighting_menu)){
        system("cls");
        switch(fighting_menu.pos_menu){
            case 0:
                return STATE_MENU;
            break;

            case 1:
                return STATE_BOSS;
            break;

            case 2:
                return STATE_EXPLORE_PLAINS;
            break;

            case 3:
                return STATE_EXPLORE_CAVES;
            break;

            default:
                return STATE_ERR;
            break;
        }
    }
    else{
        return STATE_FIGHT;
    }
}

State handle_boss_menu(){
    print_menu(boss_menu);
    if(move_in_menu(&boss_menu)){
        system("cls");
        switch(boss_menu.pos_menu){
            case 0:
                return STATE_FIGHT;
            break;

            case 1:
                return STATE_SAMURAI;
            break;

            case 2:
                return STATE_MAGE;
            break;

            case 3:
                return STATE_TANK;
            break;

            case 4:
                return STATE_ASSASSIN;
            break;

            case 5:
                return STATE_RANDOM_BOSS;
            break;

            default:
                return STATE_ERR;
            break;
        }
    }
    else{
        return STATE_BOSS;
    }
}

State handle_base_menu(){
    print_menu(base_menu);
    if(move_in_menu(&base_menu)){
        system("cls");
        switch(base_menu.pos_menu){
            case 0:
                return STATE_MENU;
            break;

            case 1:
                return STATE_VILLAGERS;
            break;

            case 2:
                return STATE_STORAGE;
            break;

            case 3:
                return STATE_PETS;
            break;

            default:
                return STATE_ERR;
            break;
        }
    }
    else{
        return STATE_BASE;
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

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//              MENU PRINTING
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void print_menu(Menu printed_MENU){
    printf(" ======%s======\n", printed_MENU.main_label);
    for(int i = 0; i < printed_MENU.total; i++){
        if(i == printed_MENU.pos_menu){printf(RED " >%s\n" RESET, printed_MENU.choices[i].label);}
        else{printf("  %s\n", printed_MENU.choices[i].label);}
    }
    set_cursor_to_zero();
}
void print_craft_menu(Menu printed_MENU){
    printf(" ======%s======\n", printed_MENU.main_label);
    for(int i = 0; i < printed_MENU.total; i++){
        if(i == printed_MENU.pos_menu){printf(RED " >%s\n" RESET, printed_MENU.choices[i].label);}
        else{
            switch(i){
                case 0:
                    printf("  %s\n", printed_MENU.choices[i].label);
                break;

                case 1:
                    if(materials.diamonds >= 5){
                        printf(COLOR_DIAMOND "  %s\n" RESET, printed_MENU.choices[i].label);
                    }
                    else if(materials.iron >= 5){
                        printf(COLOR_IRON "  %s\n" RESET, printed_MENU.choices[i].label);
                    }
                    else{
                        printf("  %s\n", printed_MENU.choices[i].label);
                    }
                break;

                case 2:
                    if(materials.diamonds >= 8){
                        printf(COLOR_DIAMOND "  %s\n" RESET, printed_MENU.choices[i].label);
                    }
                    else if(materials.iron >= 8){
                        printf(COLOR_IRON "  %s\n" RESET, printed_MENU.choices[i].label);
                    }
                    else{
                        printf("  %s\n", printed_MENU.choices[i].label);
                    }
                break;

                case 3:
                    if(materials.diamonds >= 6){
                        printf(COLOR_DIAMOND "  %s\n" RESET, printed_MENU.choices[i].label);
                    }
                    else if(materials.iron >= 6){
                        printf(COLOR_IRON "  %s\n" RESET, printed_MENU.choices[i].label);
                    }
                    else{
                        printf("  %s\n", printed_MENU.choices[i].label);
                    }
                break;

                case 4:
                    if(materials.diamonds >= 4){
                        printf(COLOR_DIAMOND "  %s\n" RESET, printed_MENU.choices[i].label);
                    }
                    else if(materials.iron >= 4){
                        printf(COLOR_IRON "  %s\n" RESET, printed_MENU.choices[i].label);
                    }
                    else{
                        printf("  %s\n", printed_MENU.choices[i].label);
                    }
                break;

                case 5:
                    if(materials.diamonds >= 2 && materials.wood >= 2){
                        printf(COLOR_DIAMOND "  %s\n" RESET, printed_MENU.choices[i].label);
                    }
                    else if(materials.iron >= 2 && materials.wood >= 2){
                        printf(COLOR_IRON "  %s\n" RESET, printed_MENU.choices[i].label);
                    }
                    else{
                        printf("  %s\n", printed_MENU.choices[i].label);
                    }
                break;

                case 6:
                    if(materials.diamonds >= 3 && materials.wood >= 2){
                        printf(COLOR_DIAMOND "  %s\n" RESET, printed_MENU.choices[i].label);
                    }
                    else if(materials.iron >= 3 && materials.wood >= 2){
                        printf(COLOR_IRON "  %s\n" RESET, printed_MENU.choices[i].label);
                    }
                    else{
                        printf("  %s\n", printed_MENU.choices[i].label);
                    }
                break;

                case 7:
                    if(materials.diamonds >= 3 && materials.wood >= 2){
                        printf(COLOR_DIAMOND "  %s\n" RESET, printed_MENU.choices[i].label);
                    }
                    else if(materials.iron >= 3 && materials.wood >= 2){
                        printf(COLOR_IRON "  %s\n" RESET, printed_MENU.choices[i].label);
                    }
                    else{
                        printf("  %s\n", printed_MENU.choices[i].label);
                    }
                break;

                case 8:
                    if(materials.leather > 5){
                        printf(DOG_BROWN_1 "  %s\n" RESET, printed_MENU.choices[i].label);
                    }
                    else{
                        printf("  %s\n", printed_MENU.choices[i].label);
                    }
                break;
            }
        }
    }
    set_cursor_to_zero();
}

void print_inventory(){
    printf(BOLD CYAN "\n=== INVENTORY ===\n" RESET);
    printf(RED    " Health:           %d/10\n" RESET, materials.player_hp_fighting);
    printf(YELLOW " Logs:             %d\n" RESET, materials.wood);
    printf(YELLOW " Iron:             %d\n" RESET, materials.iron);
    printf(YELLOW " Diamonds:         %d\n" RESET, materials.diamonds);
    printf(YELLOW " Bones:            %d\n" RESET, materials.bones);
    printf(YELLOW " Leather:          %d\n" RESET, materials.leather);
    printf(YELLOW " Wool:             %d\n" RESET, materials.wool);
    printf(CYAN " diamond sword:      %d\n" RESET, materials.d_sword);
    printf(GRAY " iron sword:         %d\n" RESET, materials.i_sword);
    printf(CYAN " diamond pickaxe:    %d\n" RESET, materials.d_pickaxe);
    printf(GRAY " iron pickaxe:       %d\n" RESET, materials.i_pickaxe);
    printf(CYAN " diamond axe:        %d\n" RESET, materials.d_axe);
    printf(GRAY " iron axe:           %d\n" RESET, materials.i_axe);
    printf(CYAN " diamond helmet:     %d\n" RESET, materials.d_helmet);
    printf(GRAY	" iron helmet:        %d\n" RESET, materials.i_helmet);
    printf(CYAN " diamond chestplate: %d\n" RESET, materials.d_chestplate);
    printf(GRAY " iron chestplate:    %d\n" RESET, materials.i_chestplate);
    printf(CYAN " diamond leggings:   %d\n" RESET, materials.d_leggings);
    printf(GRAY " iron leggings:      %d\n" RESET, materials.i_leggings);
    printf(CYAN " diamond boots:      %d\n" RESET, materials.d_boots);
    printf(GRAY " iron boots:         %d\n" RESET, materials.i_boots);

    printf(BOLD YELLOW " TANKS DEFEATED:         %d\n" RESET, materials.no_of_TANKs_defeated);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//                 THE MINES
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void wood_mine(){
	int chance_wood = rand () % 100;
	if(materials.d_axe >= 1){
		chance_wood = chance_wood - 20;
	}
    else if(materials.i_axe >= 1){
		chance_wood = chance_wood - 10;
	}
	
	if (chance_wood <= 20) {
		materials.wood += 3;
		printf(GREEN "Jackpot! You mined 3 logs!" RESET);
	}
	else if (chance_wood > 20 && chance_wood <= 50) {
		materials.wood += 2;
		printf(GREEN "Congratulations! You mined 2 logs" RESET);
	}
	else if (chance_wood > 50 && chance_wood <= 100) {
		if (materials.wood == 0) {
			materials.wood += 2;
			printf(GREEN "Congratulations! You mined 2 logs" RESET);
		}
		else {
			materials.wood += 1;
			printf(YELLOW "You got 1 log" RESET);
		}
	}
}

void iron_mine () {
	int chance_iron = rand () % 100;
	if(materials.d_pickaxe >= 1){
		chance_iron = chance_iron - 20;
	}
    else if(materials.i_pickaxe >= 1){
		chance_iron = chance_iron - 10;
	}
	
	if (chance_iron <= 20) {
		materials.iron += 2;
		printf(GREEN "Jackpot! You found 2 iron" RESET);
	}
	else if (chance_iron > 20 && chance_iron <= 50) {
		materials.iron += 1;
		printf(YELLOW "You got 1 iron" RESET);
	}
	else if (chance_iron > 50 && chance_iron <= 100) {
		materials.iron += 0;
		printf(RED "You got unlucky... 0 iron" RESET);
	}
}

void diamond_mine() {
	int chance_diamonds = rand () % 100;
	if(materials.d_pickaxe >= 1){
		chance_diamonds = chance_diamonds - 20;
	}
    else if(materials.i_pickaxe >= 1){
		chance_diamonds = chance_diamonds - 10;
	}
	

	if (chance_diamonds <= 20) {
		materials.diamonds += 1;
		printf(GREEN "Jackpot! You found a diamond!" RESET);
	}
	else if (chance_diamonds > 20 && chance_diamonds <= 50) {
		materials.diamonds += 0;
		printf(YELLOW "No Diamonds, just some stone... you should try again :)" RESET);
	}
	else if (chance_diamonds > 50 && chance_diamonds <= 100) {
		materials.diamonds += 0;
		printf(RED "You got unlucky... you should give it one more shot!" RESET);
	}
}
//TODO: death + coins, save, storage + pets
//ai writing counter ----2.5---- (stinky)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <sys/time.h>
#include <conio.h>
#include <time.h>

#include "art.h"

#define NO_OF_CREATED_CHOICES 15
#define MAX_PALYER_HP_FIGHTING 10.0f



#define D_SWORD_DMG    2.5f
#define I_SWORD_DMG    2.0f
#define BAREHANDED_DMG 1.5f

#define D_ARMOR_PIECE 1.0f
#define I_ARMOR_PIECE 0.5f



#define TANK_DAMAGE_TRESHOLD 2

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
    STATE_SAVE_AND_LEAVE,
    STATE_LEAVE,
    STATE_SAVE,
    STATE_LOAD,
    STATE_ENTER_GAME,
    STATE_ERR
} State;

typedef enum {
    F_STATE_MENU,
    F_STATE_RUN,
    F_STATE_ATTACK,
    F_STATE_TAME,
    F_STATE_LEAVE,
    F_STATE_WIN 
} Fighting_state;

typedef enum {
    I_HELMET,
    D_HELMET,
    I_CHESTPLATE,
    D_CHESTPLATE,
    I_LEGGINS,
    D_LEGGINS,
    I_BOOTS,
    D_BOOTS,
    I_SWORD,
    D_SWORD,
    I_PICKAXE,
    D_PICKAXE,
    I_AXE,
    D_AXE,
    BACKPACK,
    TOTAL_CRAFTING_ITEMS
} What_do_i_craft_please;

typedef struct {
    int bones;
	int leather;
	int wool;
	int wood;
	int iron;
	int diamonds;
} Crafting_materials;


typedef struct {
    What_do_i_craft_please Crafting_item_name;
    Crafting_materials needed_materials;
} Crafting_item;

Crafting_item recipe_book[] = {
    [0] =  { .Crafting_item_name = I_HELMET,       .needed_materials = { .iron = 5 } },      
    [1] =  { .Crafting_item_name = D_HELMET,       .needed_materials = { .diamonds = 5 } },  
    [2] =  { .Crafting_item_name = I_CHESTPLATE,   .needed_materials = { .iron = 8 } },      
    [3] =  { .Crafting_item_name = D_CHESTPLATE,   .needed_materials = { .diamonds = 8 } },  
    [4] =  { .Crafting_item_name = I_LEGGINS,      .needed_materials = { .iron = 7 } },      
    [5] =  { .Crafting_item_name = D_LEGGINS,      .needed_materials = { .diamonds = 7 } },  
    [6] =  { .Crafting_item_name = I_BOOTS,        .needed_materials = { .iron = 7 } },      
    [7] =  { .Crafting_item_name = D_BOOTS,        .needed_materials = { .diamonds = 7 } },
    [8] =  { .Crafting_item_name = I_SWORD,        .needed_materials = { .iron = 2, .wood = 1} },
    [9] =  { .Crafting_item_name = D_SWORD,        .needed_materials = { .diamonds = 2, .wood = 1} },
    [10] = { .Crafting_item_name = I_PICKAXE,      .needed_materials = { .iron = 3, .wood = 2} },
    [11] = { .Crafting_item_name = D_PICKAXE,      .needed_materials = { .diamonds = 3, .wood = 2} },
    [12] = { .Crafting_item_name = I_AXE,          .needed_materials = { .iron = 3, .wood = 2} },
    [13] = { .Crafting_item_name = D_AXE,          .needed_materials = { .diamonds = 3, .wood = 2} },
    [14] = { .Crafting_item_name = BACKPACK,       .needed_materials = {.leather = 5} }
};  


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
    char P_name[32];
    int no_of_TANKs_defeated;
	float player_hp_fighting;
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
	int d_boots;
	int d_sword; 
	int i_sword;
	int i_pickaxe;
	int d_pickaxe;
	int i_axe;
	int d_axe;
    int backpack;
	int pet_doggos;
    float attack_dmg;
    float protection_armor;
    int call_of_the_night;
    Fighting_state current_F_state;
    State current_status;
} Materials;

typedef struct {
    const char * name;
    int running_resistance;
    int hitting_resistance;
    float hp_mon;
    float max_hp;
    float attack_dmg;
    int xtra_accuracy;
    void (*print_monster)();
    Crafting_materials loottable;
} Monster;

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
State handle_D_or_I_menu(State where_am_i_state, What_do_i_craft_please variant);
State handle_enter_game_menu();
State handle_save_and_leave();
Fighting_state handle_encounter_menu(Monster chosen_monster);
int handle_tank_menu(int MAUS_lives, int max_MAUS_lives, int PLAYER_lives, int max_PLAYER_lives);

void clean_buffer();
int input_int(int min, int max);
int input_string(char inputed_str[], int inputed_str_size,char outputed_text[]);
void set_cursor_to_zero();
void clear_screen_CONTINUE();
void print_menu(Menu printed_MENU);

void print_craft_menu(Menu printed_MENU);
void print_inventory();

int * map_craft_enum_to_struct(What_do_i_craft_please variant);
void ARMOR_AND_TOOLS_check_craftability_and_print_line(What_do_i_craft_please i_variant, What_do_i_craft_please d_variant, Menu printed_MENU, int i);
Crafting_item what_recipe(What_do_i_craft_please searched_name);
int check_resources_for_crafting(Crafting_item recipe);
void crafting_jew(Crafting_item recipe);
void craft_me_pls(What_do_i_craft_please variant);


void wood_mine();
void iron_mine();
void diamond_mine();


void plains();

int is_death();

void encounter(Monster chosen_monster);
Fighting_state can_i_leave(Monster chosen_monster);
Fighting_state can_i_attack(Monster * chosen_monster);
void i_would_like_to_add_loot(int *inventory_ptr, int max_amount, const char *item_name);
Fighting_state can_i_win(Monster chosen_mon);
Fighting_state tameing(Monster chosen_mon);
void calc_equipment();
float better_armor(int d_variant, int i_variant);
void monster_attack(Monster chosen_monster);

int dodge_TANK();
int dmg_TANK();
void TANK_dmges_u(int decide_chance, int i_armor_count, int * PLAYER_lives, int tank_attack_dmg);
void praying(int * PLAYER_lives);
State tank_fight();


void resolve_unnamed();
int saving();
int loading();



//=======================================================
//                     MENU CREATION
//=======================================================

Menu main_menu = {
    "main menu",
    { {"0. LEAVE"}, {"1. CRAFT"}, {"2. MINE"}, {"3. FIGHT"}, {"4. INVENTORY"}, {"5. HEAL"}, {"6. BASE"} },
    7,
    0 //pos
};
Menu craft_menu = {
    "crafting table",
    { {"0. LEAVE"}, {"1. HELMET (5 iron/dia)"}, {"2. CHESTPLATE (8 iron/dia)"}, {"3. LEGGINS (7 iron/dia)"}, {"4. BOOTS (4 iron/dia)"}, {"5. SWORD (2 iron/dia) + (1 wood)"}, {"6. PICKAXE (3 iron/dia) + (2 wood)"}, {"7. AXE (3 iron/dia) + (2 wood)"}, {"8. BACKPACK (5 leather)"} },
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
Menu D_or_I_menu = {
    "base menu",
    { {"0. BACK"}, {"1. IRON"}, {"2. DIAMOND"} },
    3,
    0 //pos
};
Menu encounter_menu = {
    "what will you do?",
    { {"0. TRY TO RUN"}, {"1. ATTACK"}, {"2. TRY TO TAME WITH BONES"} },
    2,
    0
};
Menu start_tank_menu = {
    "Take a closer look?",
    { {"0. NAH (I'd win)"}, {"1. YEA"} },
    2,
    0
};
Menu tank_menu = {
    "Your turn - what will you do?",
    { {"1. ATTACK twice"}, {"2. try to DODGE and then ATTACK"}, {"3. PRAY"} },
    3,
    0
};

Menu enter_game = {
    "MINECRAFT ADVENTURE IN C",
    { {"1. Start new game"}, {"2. Load existing game"}, {"3. Quit"} },
    3,
    0
};

Menu save_and_leave_game = {
    "LEAVE GAME?",
    { {"1. Save and leave"}, {"2. leave"}, {"3. Go back"} },
    3,
    0
};

//=======================================================
//                   typedef CREATION
//=======================================================

Materials materials = {
    .P_name = "unnamed one",
    .no_of_TANKs_defeated = 0,
    .player_hp_fighting = 10.0f,
    .bones = 50,
    .leather = 0,
    .wool = 0,
    .wood = 0,
    .iron = 0,
    .diamonds = 0,
    .i_helmet = 0,
    .d_helmet = 0,
    .i_chestplate = 0,
    .d_chestplate = 0,
    .i_leggings = 0,
    .d_leggings = 0,
    .i_boots = 0,
    .d_boots = 0,
    .d_sword = 0,
    .i_sword = 0,
    .i_pickaxe = 0,
    .d_pickaxe = 0,
    .i_axe = 0,
    .d_axe = 0,
    .backpack = 0,
    .pet_doggos = 0,
    .attack_dmg = BAREHANDED_DMG,
    .protection_armor = 0.0f,
    .call_of_the_night = 5,
    .current_F_state = F_STATE_MENU,
    .current_status = STATE_MENU
};

Monster zombie = {
    .hp_mon = 8.0f,
    .max_hp = 8.0f,
    .running_resistance = 6,
    .name = "Zombie",
    .attack_dmg = 1.0f,
    .xtra_accuracy = 1,
    .hitting_resistance = 3,
    .loottable = { .iron = 1 },
    .print_monster = print_zom
};

Monster skeleton = {
    .hp_mon = 5.0f,
    .max_hp = 5.0f,
    .running_resistance = 7,
    .name = "Skeleton",
    .attack_dmg = 2.0f,
    .xtra_accuracy = 1,
    .hitting_resistance = 4,
    .loottable = { .bones = 2 },
    .print_monster = print_skel
};

Monster sheep ={
    .hp_mon = 3.0f,
    .max_hp = 3.0f,
    .running_resistance = 1,
    .name = "Sheep",
    .attack_dmg = 0.1f,
    .hitting_resistance = 5,
    .loottable = { .wool = 1 },
    .print_monster = print_sheep
};

Monster wolf ={
    .hp_mon = 5.0f,
    .max_hp = 5.0f,
    .running_resistance = 3,                
    .name = "Wolf",
    .attack_dmg = 0.5f,
    .hitting_resistance = 5,
    .loottable = { .bones = 1 },
    .print_monster = print_wolf
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
    materials.current_status = STATE_ENTER_GAME;


    //###################
    // MAIN CYCLE START
    //###################

    while(materials.current_status != STATE_LEAVE){
        switch(materials.current_status){

            case STATE_ENTER_GAME:
                materials.current_status = handle_enter_game_menu();
            break;

            case STATE_LOAD:
                if(loading()) return 1;
                materials.current_status = STATE_MENU;
            break;

            case STATE_MENU:
                materials.current_status = handle_MAIN_menu();
            break;

            //   CRAFT      CRAFT      CRAFT      CRAFT      CRAFT      CRAFT

            case STATE_CRAFT:
                materials.current_status = handle_craft_menu();
            break;
                case STATE_HELMET:
                    materials.current_status = handle_D_or_I_menu(STATE_HELMET, I_HELMET);
                break;
                case STATE_CHESTPLATE:
                    materials.current_status = handle_D_or_I_menu(STATE_CHESTPLATE, I_CHESTPLATE);
                break;
                case STATE_LEGGINS:
                    materials.current_status = handle_D_or_I_menu(STATE_LEGGINS, I_LEGGINS);
                break;
                case STATE_BOOTS:
                    materials.current_status = handle_D_or_I_menu(STATE_BOOTS, I_BOOTS);
                break;
                case STATE_SWORD:
                    materials.current_status = handle_D_or_I_menu(STATE_SWORD, I_SWORD);
                break;
                case STATE_PICKAXE:
                    materials.current_status = handle_D_or_I_menu(STATE_PICKAXE, I_PICKAXE);
                break;
                case STATE_AXE:
                    materials.current_status = handle_D_or_I_menu(STATE_AXE, I_AXE);
                break;
                case STATE_BACKPACK:
                    craft_me_pls(BACKPACK);
                    materials.current_status = STATE_CRAFT;
                break;

            //   MINE      MINE      MINE      MINE      MINE      MINE   

            case STATE_MINE:
                materials.current_status = handle_mine_menu();
            break;

                case STATE_WOOD:
                    system("cls");
                    wood_mine();
                    clear_screen_CONTINUE();
                    materials.current_status = STATE_MINE;
                break;

                case STATE_IRON:
                    system("cls");
                    iron_mine();
                    clear_screen_CONTINUE();
                    materials.current_status = STATE_MINE;
                break;

                case STATE_DIAMONDS:
                    system("cls");
                    diamond_mine();
                    clear_screen_CONTINUE();
                    materials.current_status = STATE_MINE;
                break;
            
            //   FIGHT      FIGHT      FIGHT      FIGHT      FIGHT      FIGHT   

            case STATE_FIGHT:
                materials.current_status = handle_fighting_menu();
            break;
                case STATE_BOSS:
                    materials.current_status = handle_boss_menu();
                break;
                    case STATE_SAMURAI:
                        system("cls");
                        printf("SAMURAI\n");
                        clear_screen_CONTINUE();
                        materials.current_status = STATE_BOSS;
                    break;
                    case STATE_MAGE:
                        system("cls");
                        printf("MAGE\n");
                        clear_screen_CONTINUE();
                        materials.current_status = STATE_BOSS;
                    break;
                    case STATE_TANK:
                        materials.current_status = tank_fight();
                        system("cls"); //cuz if u chicken out
                    break;
                    case STATE_ASSASSIN:
                        system("cls");
                        printf("ASSASSIN\n");
                        clear_screen_CONTINUE();
                        materials.current_status = STATE_BOSS;
                    break;
                    case STATE_RANDOM_BOSS:
                        system("cls");
                        printf("RANDOM BOSS\n");
                        clear_screen_CONTINUE();
                        materials.current_status = STATE_BOSS;
                    break;
                case STATE_EXPLORE_PLAINS:
                    system("cls");
                    plains();
                    materials.current_status = STATE_FIGHT;
                break;
                case STATE_EXPLORE_CAVES:
                    system("cls");
                    printf("EXPLORE CAVES IS WORK IN PROGRESS\n");
                    clear_screen_CONTINUE();
                    materials.current_status = STATE_FIGHT;
                break;

            //   INVENTORY      INVENTORY      INVENTORY      INVENTORY      INVENTORY      INVENTORY   

            case STATE_INVENTORY:
                print_inventory();
                materials.current_status = STATE_MENU;
            break;

            case STATE_HEAL:
                system("cls");

                clear_screen_CONTINUE();
                materials.current_status = STATE_MENU;
            break;

            case STATE_BASE:
                materials.current_status = handle_base_menu();
            break;
                case STATE_VILLAGERS:
                    system("cls");
                    printf("VILLAGERS IN PROGRESS\n");
                    clear_screen_CONTINUE();
                    materials.current_status = STATE_BASE;
                break;
                case STATE_STORAGE:
                    system("cls");
                    printf("STORAGE\n");
                    clear_screen_CONTINUE();
                    materials.current_status = STATE_BASE;
                break;
                case STATE_PETS:
                    system("cls");
                    printf("PETS\n");
                    clear_screen_CONTINUE();
                    materials.current_status = STATE_BASE;
                break;
            
            case STATE_SAVE_AND_LEAVE:
                materials.current_status = handle_save_and_leave();
            break;
    
            case STATE_LEAVE:
                system("cls");
                printf("leaving\n");
                clean_buffer();
                clear_screen_CONTINUE();
            break;

            case STATE_SAVE:
                if(saving()) return 1;
                materials.current_status = STATE_LEAVE;
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
                return STATE_SAVE_AND_LEAVE;
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

State handle_D_or_I_menu(State where_am_i_state, What_do_i_craft_please variant){
    print_menu(D_or_I_menu);
    if(move_in_menu(&D_or_I_menu)){
        switch(D_or_I_menu.pos_menu){
            case 0:
                return STATE_CRAFT;
            break;

            case 1: //craft iron variant
                craft_me_pls(variant);
                return STATE_CRAFT;
            break;

            case 2: //craft diamond variant
                craft_me_pls(variant +1);
                return STATE_CRAFT;
            break;

            default:
                return STATE_ERR;
            break;
        }
    }
    else{
        return where_am_i_state;
    }
}

State handle_enter_game_menu(){
    print_menu(enter_game);
    if(move_in_menu(&enter_game)){
        system("cls");
        switch(enter_game.pos_menu){
            case 0:
                return STATE_MENU;
            break;

            case 1:
                return STATE_LOAD;
            break;

            case 2:
                return STATE_LEAVE;
            break;
        }
    }
    else{
        return STATE_ENTER_GAME;
    }
}

State handle_save_and_leave(){
    print_menu(save_and_leave_game);
    if(move_in_menu(&save_and_leave_game)){
        system("cls");
        switch(save_and_leave_game.pos_menu){
            case 0:
                return STATE_SAVE;
            break;

            case 1:
                return STATE_LEAVE;
            break;

            case 2:
                return STATE_MENU;
            break;
        }
    }
    else{
        return STATE_SAVE_AND_LEAVE;
    }
}

Fighting_state handle_encounter_menu(Monster chosen_monster){
    chosen_monster.print_monster();
    printf("A wild %s has appeared!\n", chosen_monster.name);
    printf(GREEN "Your HP: %.1f/%.1f    " RESET, materials.player_hp_fighting, MAX_PALYER_HP_FIGHTING);
    printf(RED "Enemy HP: %.1f/%.1f\n" RESET, chosen_monster.hp_mon, chosen_monster.max_hp);
    print_menu(encounter_menu);

    if(move_in_menu(&encounter_menu)){
        switch(encounter_menu.pos_menu){
            case 0:
                return F_STATE_RUN;
            break;

            case 1:
                return F_STATE_ATTACK;
            break;

            case 2:
                return F_STATE_TAME;
            break;

            default:
                exit(21);
            break;
        }
    }
    else{
        return F_STATE_MENU;
    }
}

int handle_starter_tank_menu(){
    while(1){
        printf(YELLOW "\n You walk around hilly plains and suddenly you hear a strange soud...\n" RESET);
        print_menu(start_tank_menu);
        if(move_in_menu(&start_tank_menu)){
            switch(start_tank_menu.pos_menu){
                case 0:
                    return 1;
                break;

                case 1:
                    return 0;
                break;
                
                default:
                    return 1;
                break;
            }
        }
    }
}

int handle_tank_menu(int MAUS_lives, int max_MAUS_lives, int PLAYER_lives, int max_PLAYER_lives){
    system("cls");
    while(1){
        printf(RED "\n MAUS HP = %d/%d" RESET, MAUS_lives, max_MAUS_lives);
		printf(GREEN "\n YOUR HP = %d/%d\n" RESET, PLAYER_lives, max_PLAYER_lives);
        print_menu(tank_menu);
        if(move_in_menu(&tank_menu)){
            switch(tank_menu.pos_menu){
                case 0:
                    system("cls");
                    return 1;
                break;

                case 1:
                    system("cls");
                    return 2;
                break;

                case 2:
                    system("cls");
                    return 3;
                break;
                
                default:
                    exit(1);
                break;
            }
        }
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

void print_inventory(){
    system("cls");
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
    clear_screen_CONTINUE();

}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//                 CRAFTING 
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void print_craft_menu(Menu printed_MENU){
    Crafting_item current_recipe;

    printf(" ======%s======\n", printed_MENU.main_label);
    for(int i = 0; i < printed_MENU.total; i++){
        if(i == printed_MENU.pos_menu){printf(RED " >%s\n" RESET, printed_MENU.choices[i].label);}
        else{
            switch(i){
                case 0:
                    printf("  %s\n", printed_MENU.choices[i].label);
                break;

                case 1:
                    ARMOR_AND_TOOLS_check_craftability_and_print_line(I_HELMET, D_HELMET, printed_MENU, i);
                break;

                case 2:
                    ARMOR_AND_TOOLS_check_craftability_and_print_line(I_CHESTPLATE, D_CHESTPLATE, printed_MENU, i);
                break;

                case 3:
                    ARMOR_AND_TOOLS_check_craftability_and_print_line(I_LEGGINS, D_LEGGINS, printed_MENU, i);
                break;

                case 4:
                    ARMOR_AND_TOOLS_check_craftability_and_print_line(I_BOOTS, D_BOOTS, printed_MENU, i);
                break;

                case 5:
                    ARMOR_AND_TOOLS_check_craftability_and_print_line(I_SWORD, D_SWORD, printed_MENU, i);
                break;

                case 6:
                    ARMOR_AND_TOOLS_check_craftability_and_print_line(I_PICKAXE, D_PICKAXE, printed_MENU, i);
                break;

                case 7:
                    ARMOR_AND_TOOLS_check_craftability_and_print_line(I_AXE, D_AXE, printed_MENU, i);
                break;

                case 8:
                    if(check_resources_for_crafting(what_recipe(BACKPACK))){
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

void ARMOR_AND_TOOLS_check_craftability_and_print_line(What_do_i_craft_please i_variant, What_do_i_craft_please d_variant, Menu printed_MENU, int i){
    if(check_resources_for_crafting(what_recipe(d_variant))){
        printf(COLOR_DIAMOND "  %s\n" RESET, printed_MENU.choices[i].label);
    }
    else if(check_resources_for_crafting(what_recipe(i_variant))){
        printf(COLOR_IRON "  %s\n" RESET, printed_MENU.choices[i].label);
    }
    else{
        printf("  %s\n", printed_MENU.choices[i].label);
    }
}   

Crafting_item what_recipe(What_do_i_craft_please searched_name){
    for(int i = 0; i < TOTAL_CRAFTING_ITEMS; i++){
        if(recipe_book[i].Crafting_item_name == searched_name){
            return recipe_book[i];
        }
    }

    return(Crafting_item){0};
}

int check_resources_for_crafting(Crafting_item recipe){
    return (materials.bones >= recipe.needed_materials.bones) &&
           (materials.leather >= recipe.needed_materials.leather) &&
           (materials.wool >= recipe.needed_materials.wool) &&
           (materials.wood >= recipe.needed_materials.wood) &&
           (materials.iron >= recipe.needed_materials.iron) &&
           (materials.diamonds >= recipe.needed_materials.diamonds);
}

int * map_craft_enum_to_struct(What_do_i_craft_please variant){
    switch(variant){
        case I_HELMET:       return &materials.i_helmet;     break;
        case D_HELMET:       return &materials.d_helmet;     break;
        case I_CHESTPLATE:   return &materials.i_chestplate; break;
        case D_CHESTPLATE:   return &materials.d_chestplate; break;
        case I_LEGGINS:      return &materials.i_leggings;   break;
        case D_LEGGINS:      return &materials.d_leggings;   break;
        case I_BOOTS:        return &materials.i_boots;      break;
        case D_BOOTS:        return &materials.d_boots;      break;
        case I_SWORD:        return &materials.i_sword;      break;
        case D_SWORD:        return &materials.d_sword;      break;
        case I_PICKAXE:      return &materials.i_pickaxe;    break;
        case D_PICKAXE:      return &materials.d_pickaxe;    break;
        case I_AXE:          return &materials.i_axe;        break;
        case D_AXE:          return &materials.d_axe;        break;
        case BACKPACK:       return &materials.backpack;     break;
        default:
            return NULL;
        break;
    }
}

void craft_me_pls(What_do_i_craft_please variant){
    system("cls");
    if(!check_resources_for_crafting(what_recipe(variant))){
        printf(RED " Insufficient materials to craft" RESET);
    }
    else{
        int * P_item_in_inv = map_craft_enum_to_struct(variant);
        if(*P_item_in_inv >=1){
            printf(RED " Already have one..." RESET);
        }
        else{
            crafting_jew(what_recipe(variant));
            (*P_item_in_inv)++;
            printf(GREEN " Succesfully crafted!" RESET);
        }
    }
    clear_screen_CONTINUE();
}
    
void crafting_jew(Crafting_item recipe){
    materials.bones     -= recipe.needed_materials.bones;
    materials.leather   -= recipe.needed_materials.leather;
    materials.wool      -= recipe.needed_materials.wool;
    materials.wood      -= recipe.needed_materials.wood;
    materials.iron      -= recipe.needed_materials.iron;
    materials.diamonds  -= recipe.needed_materials.diamonds;
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

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//                   FIGTING
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void plains(){

    if(materials.call_of_the_night >0){
        printf( YELLOW " Its a brand new day!" RESET);
        Sleep(50);
        clear_screen_CONTINUE();
        if(rand() %10 > 3) encounter(sheep);
        else encounter(wolf);
    }
    else{
        printf( RED " The night calls for you (yea you're screwed...)" RESET);
        Sleep(50);
        clear_screen_CONTINUE();
        if(rand() %10 > 3) encounter(zombie);
        else encounter(skeleton);
    }

    if(materials.call_of_the_night == -4) materials.call_of_the_night = 5;
    else materials.call_of_the_night --;

}

void encounter(Monster chosen_monster){
    calc_equipment();
    materials.current_F_state = F_STATE_MENU;

    system("cls");
    if(strcmp(chosen_monster.name, "Wolf") == 0){ //make tame avalible
        encounter_menu.total = 3;
    }
    else{
        encounter_menu.total = 2;
    }

    while(materials.player_hp_fighting >0 ){

        if(chosen_monster.hp_mon <=0){
            materials.current_F_state = F_STATE_WIN;
        }

        switch(materials.current_F_state){

            case F_STATE_MENU:
                materials.current_F_state = handle_encounter_menu(chosen_monster);
            break;

            case F_STATE_RUN:
                materials.current_F_state = can_i_leave(chosen_monster); 
            break;

            case F_STATE_ATTACK:
                materials.current_F_state = can_i_attack(&chosen_monster);
            break;

            case F_STATE_TAME:
                materials.current_F_state = tameing(chosen_monster);
                clear_screen_CONTINUE();
            break;

            case F_STATE_WIN:
                materials.current_F_state = can_i_win(chosen_monster);
            break;

            case F_STATE_LEAVE:
                system("cls");
            break;
        }
        if(materials.current_F_state == F_STATE_LEAVE) return; 
    }
}

Fighting_state can_i_leave(Monster chosen_monster){
    system("cls");
    int tmp = rand() % 11;
    tmp = tmp - chosen_monster.running_resistance;
    if(tmp >= 0){
        printf(GREEN " ESCASPED SUCCEFULLY\n" RESET);
        clear_screen_CONTINUE();
        return F_STATE_LEAVE;
    }
    else{
        printf(RED " XXX COULDNT ESCAPE... XXX\n" RESET);
        clear_screen_CONTINUE();
        monster_attack(chosen_monster);
        return F_STATE_MENU;
    }
    clear_screen_CONTINUE();
}

Fighting_state can_i_attack(Monster * chosen_monster){
    system("cls");

    int tmp = rand() %11;
    tmp -= chosen_monster->hitting_resistance;
    if(tmp > 0){
        chosen_monster->hp_mon -= materials.attack_dmg;
        printf(BOLD " ATTACK HIT for %.1f\n" RESET, materials.attack_dmg);
        clear_screen_CONTINUE();
        monster_attack(*chosen_monster);
    }
    else{
        printf(BOLD " ATTACK MISSED\n" RESET);
        clear_screen_CONTINUE();
        monster_attack(*chosen_monster);
    }

    clear_screen_CONTINUE();
    return F_STATE_MENU;
}

Fighting_state can_i_win(Monster chosen_mon){
    system("cls");

    i_would_like_to_add_loot(&materials.bones,    chosen_mon.loottable.bones, "bones");
    i_would_like_to_add_loot(&materials.leather,  chosen_mon.loottable.leather, "leather");
    i_would_like_to_add_loot(&materials.wool,     chosen_mon.loottable.wool, "wool");
    i_would_like_to_add_loot(&materials.wood,     chosen_mon.loottable.wood, "wood");
    i_would_like_to_add_loot(&materials.iron,     chosen_mon.loottable.iron, "iron");
    i_would_like_to_add_loot(&materials.diamonds, chosen_mon.loottable.diamonds, "diamonds");

    clear_screen_CONTINUE();
    return F_STATE_LEAVE;
}

void i_would_like_to_add_loot(int *inventory_ptr, int max_amount, const char *item_name){ //ai cuz na tohlecto uz nemam
    if (max_amount <= 0) return;

    int amount; //int amount = (rand() % 11 > 5) ? max_amount : (max_amount - 1);
    if(rand() %10 > 5){
        amount = max_amount;
    }
    else{
        amount = max_amount -1;
    }
    
    // Safety check: don't add negative loot
    if (amount < 0) amount = 0;

    if (amount > 0) {
        *inventory_ptr += amount;
        printf("Gained %d %s\n", amount, item_name);
    }
}

Fighting_state tameing(Monster chosen_mon){
    system("cls");
    if(materials.bones >0){
        int doitame = 10;
        printf(YELLOW " YOU TRY TAMEING THE WILD WOLF\n" RESET);
        printf(" .\n");
        Sleep(500);
        printf(" .\n");
        Sleep(500);
        printf(" .\n");
        Sleep(500);
        printf(" .\n");
        Sleep(500);
        printf(" .\n");
        Sleep(500);
        printf(" .\n");
        Sleep(500);
        doitame = doitame - rand() %10;
        if(doitame > 6){
            printf(GREEN " YOU SUCCESFULLY TAMED THE WOLF\n CONSUMED 1 BONES\n" RESET);
            materials.pet_doggos = materials.pet_doggos +1;
            materials.bones = materials.bones -1;
            return F_STATE_LEAVE;
        }
        else{
            printf(RED " WOLF NOT TAMED. TRY AGAIN?\n CONSUMED 1 BONES\n" RESET);
            materials.bones = materials.bones -1;
            clear_screen_CONTINUE();
            monster_attack(chosen_mon);
            return F_STATE_MENU;  
        }   
    }
    else{
        printf(RED " NOT ENOUGH BONES\n" RESET);
        return F_STATE_MENU;
    }
}

void calc_equipment(){
    if(materials.d_sword > 0){
        materials.attack_dmg = D_SWORD_DMG;
    }
    else if(materials.i_sword > 0){
        materials.attack_dmg = I_SWORD_DMG;
    }
    else{
        materials.attack_dmg = BAREHANDED_DMG;
    }

    materials.protection_armor = 0.0f;
    materials.protection_armor += better_armor(materials.d_helmet, materials.i_helmet);
    materials.protection_armor += better_armor(materials.d_chestplate, materials.i_chestplate);
    materials.protection_armor += better_armor(materials.d_leggings, materials.i_leggings);
    materials.protection_armor += better_armor(materials.d_boots, materials.i_boots);
}

float better_armor(int d_variant, int i_variant){
    return (d_variant) ? D_ARMOR_PIECE : (i_variant) ? I_ARMOR_PIECE : 0.0f;
}

void monster_attack(Monster chosen_monster){
    printf(" %s attacks back!\n", chosen_monster.name);
    int tmp = rand() %10;
    tmp -= materials.protection_armor;
    tmp += chosen_monster.xtra_accuracy;

    if(tmp > 5){
        materials.player_hp_fighting -= chosen_monster.attack_dmg;
        printf( RED" Took %.1f damage from %s" RESET, chosen_monster.attack_dmg, chosen_monster.name);
    }
    else{
        printf( GREEN " %s's attack didnt even hurt" RESET, chosen_monster.name);
    }

    is_death();

}

int is_death(){
    if(materials.player_hp_fighting <= 0){
        system("cls");
        printf( BOLD RED" YOU DIED\n %s dont give up just yet!" RESET, materials.P_name);

            clear_screen_CONTINUE(); //redo later
            exit(0);

        materials.current_F_state = F_STATE_LEAVE;
        materials.current_status = STATE_MENU;
        return 1;
    }
    else{
        return 0;
    }
    
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//(from old code)   BOSSES    (kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me kill me )
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int dodge_TANK(){
	//zapamatovani beatu? 
	//vygeneruje beat a b b a
	struct timeval start, stop;
	int size_abarr = 7; 
	char abarr[size_abarr];
	char input_arr[size_abarr];
	int computar = 0;
	for(int i = 0; i < size_abarr-1; i++){ //generovani ababbababbabab
		abarr[i] = rand() % (98-97 +1) +97;
	}
	abarr[size_abarr-1] = '\0';
	printf(YELLOW "\n You get ready for a dodge\n (repeat this 6*a or b sequence after 321 go)");
	printf(RED "\n Show sequence?" RESET);
	getchar();
	printf("\n");
	for(int i = 0; i < size_abarr-1; i++){
		printf("%c ", abarr[i]);
	}
	printf("\n Hiding sequence in 3");
	Sleep(750);
	printf("\n Hiding sequence in 2");
	Sleep(750);
	printf("\n Hiding sequence in 1");
	Sleep(750);
	system("cls");

	//uzivatel musi zopakovat
	printf(RED "\n Start inputing sequence?" RESET);
	clean_buffer();
	gettimeofday(&start, NULL);
	while(_kbhit()){ //_kbhit vraci tru nebo false jestli je neco v bufferu? myslim idk
		_getch(); //mrdne vec z bufferu dopici
	}
	while(1){
	input_string(input_arr, size_abarr, "\ntype: ");
		computar = strcmp(input_arr, abarr);
		printf("%s ", abarr);
		printf("%s ", input_arr);
		if(computar == 0){
			break;
		}
		else{
			printf("\n Try again");
		}
	}
	gettimeofday(&stop, NULL);
	//podle ryvhlosti vetsi sance na dodge?
	// Calculate total elapsed time in microseconds
    long long start_usec = (long long)start.tv_sec * 1000000 + start.tv_usec;
    long long stop_usec = (long long)stop.tv_sec * 1000000 + stop.tv_usec;
    long long elapsed_usec = stop_usec - start_usec;

	// Convert to seconds and remaining milliseconds
    long seconds = elapsed_usec / 1000000;
    long milliseconds = (elapsed_usec % 1000000) / 1000;

	printf("Ended at %ld seconds and %ld milliseconds\n", seconds, milliseconds);
	if(elapsed_usec < 3000000){
		printf(BOLD GREEN "\n YOU DODGED!");
		return 1;
	}
	else{
		printf(RED "\n YOU GOT HIT" RESET);
		return 0;
	}	
	
}

int dmg_TANK(){ //vracet dmg
	//pocitat milisekundy od 321 ted?
	struct timeval start, stop;
	char write_attack[100] = {0};
	int factcheck = 0;
	printf(YELLOW "\n You get ready for an attack\n (type 4862 4862 after 321 go)" RESET);
	printf(RED "\n Are you ready?" RESET);
	getchar();
	printf(BOLD CYAN "\n type 48624862 in\n" RESET);
	printf(RED "3\n" RESET);
	Sleep(1000);
	printf(RED "2\n" RESET);
	Sleep(1000);
	printf(RED "1\n" RESET);
	Sleep(1050); 
	
	while(_kbhit()){ //_kbhit vraci tru nebo false jestli je neco v bufferu? myslim idk
		_getch(); //mrdne vec z bufferu dopici
	}
	gettimeofday(&start, NULL);
	printf(GREEN "GO! : " RESET);
	do{
		input_string(write_attack, sizeof(write_attack), "");
		factcheck = strcmp("48624862", write_attack);
		if(factcheck != 0){
			printf(BOLD RED "\n wrong input\n Try again: " RESET);
		}
		else{
			break;
		}
	}while(factcheck != 0);

	gettimeofday(&stop, NULL);
	// Calculate total elapsed time in microseconds
    long long start_usec = (long long)start.tv_sec * 1000000 + start.tv_usec;
    long long stop_usec = (long long)stop.tv_sec * 1000000 + stop.tv_usec;
    long long elapsed_usec = stop_usec - start_usec;

	// Convert to seconds and remaining milliseconds
    long seconds = elapsed_usec / 1000000;
    long milliseconds = (elapsed_usec % 1000000) / 1000;

	printf("Ended at %ld seconds and %ld milliseconds\n", seconds, milliseconds);
	printf("%lld", elapsed_usec);
	if(elapsed_usec < 1000000){
		printf(BOLD GREEN "\n CRITICAL HIT!");
		return 2;
	}
	else if(elapsed_usec < 3000000){
		printf(GREEN "\n ATTACK HIT" RESET);
		return 1;
	}
	else{
		printf(GREEN "\n ATTACK MISSED" RESET);
		return 0;
	}
	
	
}

void TANK_dmges_u(int decide_chance, int i_armor_count, int * PLAYER_lives, int tank_attack_dmg){
    printf(YELLOW"\n The tank fires at you");
    Sleep(500);
    decide_chance = rand() % 100;
    decide_chance = decide_chance - (i_armor_count*10); //idk jesti fachci - melo by zmensut sanci na hit
    if(decide_chance >30){
        printf(RED "\n The tank round hits you and you scream in pain!"RESET);
        if(materials.protection_armor < TANK_DAMAGE_TRESHOLD){ //new
            printf(RED "\n You lose %dhp"RESET, tank_attack_dmg);
            *PLAYER_lives = *PLAYER_lives - tank_attack_dmg;
        }
        else{ 
            printf(RED "\n You lose %dhp"RESET, tank_attack_dmg / 2);
            *PLAYER_lives = *PLAYER_lives - tank_attack_dmg / 2;
        }
    }
    else{
        printf("\n The tanks attack didnt hurt");
    }
    Sleep(500);
}

void praying(int * PLAYER_lives){
    printf(YELLOW "\n You use this chance to pray to BENJAMIN NETENYAHU" RESET);
    printf("\n.");
    Sleep(500);
    printf("\n.");
    Sleep(500);
    printf("\n.");
    Sleep(500);
    printf("\n.");
    Sleep(500);

    int decide_chance = rand() % 100;
    if(decide_chance > 65){
        printf(GREEN "\n The jewish spirit within you blooms\n Healed 1 HP!" RESET); //hava nagila or sum shit
        (*PLAYER_lives)++;
    }
    else{
        printf(RED "\n Nothing happends..." RESET);
    }
}


State tank_fight(){  // old code from minecraft.c I am NOT REMAKING THIS FUCKING SHIT ASS CODE
	int PLAYER_lives = 4;				//PLAYER
	int max_PLAYER_lives = PLAYER_lives;
	int PLAYER_decision_roud = 0;

	int MAUS_lives = 10;				//MOOSE xd
	int max_MAUS_lives = MAUS_lives;
	int MAUS_decision_roud = 0;
	
	int decide_chance = 0;
	int tank_attack_dmg = 2; 
	int dodge = 0;

    int i_armor_count = materials.i_helmet + materials.i_chestplate + materials.i_leggings + materials.i_boots;
    int d_armor_count = materials.d_helmet + materials.d_chestplate + materials.d_leggings + materials.d_boots;
    calc_equipment();

	system("cls");


    if(handle_starter_tank_menu()) return STATE_BOSS;	

    system("cls"); //uvod 
	printf(YELLOW "\n Behind one of the hills appears.... " RESET);
	Sleep(2000);
	printf(RED "A 128mm long cannon???" RESET);
	Sleep(1000);
	printf(BOLD RED "\n\n === A MAUS tank appeared to have noticed you! ===\n" RESET);
    clear_screen_CONTINUE();
	
	do{
		if(MAUS_lives <=0){ //win
			printf(BOLD GREEN "\n You managed to defeat the TANK boss, congratulations..." RESET);
            materials.no_of_TANKs_defeated++;
            clear_screen_CONTINUE();
			return STATE_MENU;
		}
		if(PLAYER_lives > 4){ //too much HP 
			PLAYER_lives = 4;
		}
		

		//PLAYER decides what to do
		//1 - attack 2x 
		//2 - try dodge and attack
		//3 - pray +1 hp - can be disrupted by an attack (godess art?)
		
		PLAYER_decision_roud = handle_tank_menu(MAUS_lives, max_MAUS_lives, PLAYER_lives, max_PLAYER_lives);


		//tank decides what to do
		//1 - heal
		//2 - attack
		if(MAUS_lives < max_MAUS_lives){
			decide_chance = rand() % 100;
			if(decide_chance > 75){
				MAUS_decision_roud = 1;
			}
			else{
				MAUS_decision_roud = 2;
			}
		}
		else{
			MAUS_decision_roud = 2;
		}

		//stuff happens
		switch(MAUS_decision_roud){
			case 1://heal
				printf(YELLOW "\n The tank tries to reinforce its hull" RESET);
                Sleep(500);
				decide_chance = rand() % 100;
				if(decide_chance > 60){
					MAUS_lives++;
					printf("\n TANK healed 1 hp");
                    Sleep(500);
				}

				switch(PLAYER_decision_roud){
					case 1://attacked
						printf(GREEN "\n Ambush it while its distracted!" RESET);
                        Sleep(500);
						MAUS_lives = MAUS_lives - dmg_TANK(); 
						clear_screen_CONTINUE();
						printf(GREEN "\n Attack it again!" RESET);
                        Sleep(500);
						MAUS_lives = MAUS_lives - dmg_TANK(); 
					break;
					case 2://do a at
						printf(YELLOW "\n Theres nothing to dodge..." RESET);
                        Sleep(500);
						printf(GREEN "\n Ambush it while its distracted!" RESET);
                        Sleep(500);
						MAUS_lives = MAUS_lives - dmg_TANK(); 
					break;
					case 3://pray
						printf(YELLOW "\n You use this chance to pray to BENJAMIN NETENYAHU" RESET);
						printf("\n.");
						Sleep(500);
						printf("\n.");
						Sleep(500);
						printf("\n.");
						Sleep(500);
						printf("\n.");
						Sleep(500);

						decide_chance = rand() % 100;
						if(decide_chance > 65){ //vtipny by bylo kdyby vic zlata znamenalo lepsi sance
							printf(GREEN "\n The jewish spirit within you blooms\n Healed 1 HP!" RESET);
							PLAYER_lives++;
						}
						else{
							printf(RED "\n Nothing happends..." RESET);
						}
					break;
				}
                clear_screen_CONTINUE();
			break;
			case 2://at
				printf(YELLOW "\n The tank aims its cannon in your direction" RESET);
                Sleep(500);
				if(MAUS_lives < max_MAUS_lives/2){
					printf(RED " angrily" RESET);
                    Sleep(100);
				}

				switch(PLAYER_decision_roud){
					case 1:
						TANK_dmges_u(decide_chance, i_armor_count, &PLAYER_lives, tank_attack_dmg);

						printf("\n Your turn to attack! give him back what he deserves!");
                        Sleep(500);
						MAUS_lives = MAUS_lives - dmg_TANK(); 
						clear_screen_CONTINUE();

						printf("\n Attack again once more!");
                        Sleep(500);
						MAUS_lives = MAUS_lives - dmg_TANK(); 
						clear_screen_CONTINUE();
					break;
					case 2:
						printf(YELLOW"\n The tank attempts to fire at you");
                        Sleep(500);
						dodge = dodge_TANK();
						if(dodge == 1){
							printf("\n The TANKs attack just barely missed you!");
						}
						else if(dodge == 0){
							TANK_dmges_u(decide_chance, i_armor_count, &PLAYER_lives, tank_attack_dmg);
						}
                        Sleep(500);
						printf("\n Your turn to attack! give him back what he deserves!");
						MAUS_lives = MAUS_lives - dmg_TANK(); 
						clear_screen_CONTINUE();
					break;
					case 3:
						TANK_dmges_u(decide_chance, i_armor_count, &PLAYER_lives, tank_attack_dmg);
                        praying(&PLAYER_lives);
					break;
				}
                clear_screen_CONTINUE();
			break;
		}


	} while(PLAYER_lives > 0); //main do while cycyle end
	materials.player_hp_fighting = 0;
    is_death();
}



void resolve_unnamed(){
    if(strcmp(materials.P_name, "unnamed one") == 0){
        printf("Dont have a name yet? (pathetic)\nPlease chose your name: ");
        while(1){
            input_string(materials.P_name, sizeof(materials.P_name), "");
            if(strcmp(materials.P_name, "unnamed one") != 0) break;
        }
    }
}

int saving() {
    system("cls"); 
    resolve_unnamed();

    // Fixed array large enough to hold Name (32) + ".bin" (4) + Null terminator (1)
    char actual_file_name[37]; 


    strcpy(actual_file_name, materials.P_name);
    strcat(actual_file_name, ".bin");


    FILE * P_saving_file = fopen(actual_file_name, "wb");
    if (P_saving_file == NULL) {
        perror("Failed to make save");
        return 1; 
    }


    fwrite(&materials, sizeof(Materials), 1, P_saving_file);
    fclose(P_saving_file);
    
    printf("Game saved successfully as %s!\n", actual_file_name);
    clear_screen_CONTINUE();
    return 0; 
}

int loading(){
    system("cls");
    char actual_file_name[37]; 

    while(1){
        input_string(actual_file_name, 32, "Enter your save name: ");

        if(strcmp(actual_file_name, "unnamed")== 0){
            printf("defaulting to a new game");
            return 0;
        }

        strcat(actual_file_name, ".bin");

        FILE * P_loading_save = fopen(actual_file_name, "rb");
        if(P_loading_save == NULL){
            printf("Unable to open save...\ntry again or write 'unnamed' if you dont have one");
            clear_screen_CONTINUE();
            fclose(P_loading_save);
            continue;
        }

        fread(&materials, sizeof(materials), 1, P_loading_save);

        fclose(P_loading_save);

        printf("succesfully loaded save %s", materials.P_name);

        clear_screen_CONTINUE();
        system("cls");
        return 0;
    }

    return 0;
}


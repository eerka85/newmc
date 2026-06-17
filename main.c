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
    STATE_FIGHT,
    STATE_INVENTORY,
    STATE_HEAL,
    STATE_BASE,
    STATE_LEAVE
} main_State;

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
void clean_buffer();
int input_int(int min, int max);
int input_string(char inputed_str[], int inputed_str_size,char outputed_text[]);
void set_cursor_to_zero();
void clear_screen_CONTINUE();
void print_menu(Menu printed_MENU);

//=======================================================
//                     MENU CREATION 
//=======================================================

Menu main_menu = {
    "main menu",
    { {"0. LEAVE"}, {"1. CRAFT"}, {"2. MINE"}, {"3. FIGHT"}, {"4. INVENTORY"}, {"5. HEAL"}, {"6. BASE"} },
    7,
    0
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
    //       TEST
    //###################
    print_menu(main_menu);
    getchar();
    main_menu.pos_menu++;
    print_menu(main_menu);
    getchar();
    main_menu.pos_menu++;
    print_menu(main_menu);
    getchar();
    main_menu.pos_menu++;
    print_menu(main_menu);
    getchar();
    main_menu.pos_menu++;
    print_menu(main_menu);


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
    }
    return inputed_key;
}

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
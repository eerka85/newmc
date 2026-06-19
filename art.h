#define RED     "\033[31m" //gud thing
#define GREEN   "\033[32m" //bad thing
#define YELLOW  "\033[33m" //text
#define CYAN    "\033[36m" //rozhodnuti, titles
#define BOLD    "\033[1m"
#define RESET   "\033[0m"
#define BLUE    "\x1b[34m"
#define GRAY	"\x1b[90m"
#define PURPLE  "\033[35m"
#define ORANGE  "\033[38;2;227;121;23m"

#define COLOR_IRON   "\033[38;2;139;126;110m"
#define COLOR_DIAMOND "\033[38;2;100;200;255m"

//zom//
#define BLACK   "\033[30m"
#define FOREST_GREEN    "\033[38;5;22m"     // A deep, dark green
#define LIME_GREEN      "\033[38;5;118m"    // A very bright, vivid green


//skel//
// The deep dark voids for the eyes and mouth 
#define SKEL_EYE_DARK    "\033[38;2;76;76;76m"   // Dark charcoal

// The shading/texture colors
#define SKEL_SHADOW      "\033[38;2;145;145;145m" // Deep shadow gray
#define SKEL_MEDIUM      "\033[38;2;172;172;172m" // Mid-tone gray

// The main "bone" colors
#define SKEL_BONE        "\033[38;2;193;193;193m" // Standard bone gray
#define SKEL_HIGHLIGHT   "\033[38;2;215;215;215m" // Lightest highlights


//sheep//
#define WHITE    "\033[38;2;255;255;255m" // Pure white highlights
#define SHEEP_WOOL_SHADOW   "\033[38;2;230;230;230m" // Light grey wool texture
//#define SHEEP_WOOL_DARK     "\033[38;2;213;213;213m" // Deep wool shadow - too lazy for ts rn

// Face/Skin Colors
#define SHEEP_SKIN          "\033[38;2;223;166;137m" // The main tan face color
//#define SHEEP_SKIN_SHADOW   "\033[38;2;184;133;106m" // Darker tan for the chin/edges - too lazy for ts rn

// Features
#define SHEEP_EYE_BLACK     "\033[38;2;0;0;0m"       // Pupil
#define SHEEP_NOSE_PINK     "\033[38;2;251;153;192m" // The pink nose/mouth area
#define SHEEP_NOSE_LIGHT    "\033[38;2;254;206;222m" // Highlight on the nose

// dog
#define DOG_GRAY_1 "\033[38;2;180;180;180m"
#define DOG_GRAY_2 "\033[38;2;163;155;163m"
#define DOG_GRAY_3 "\033[38;2;128;121;128m"
#define DOG_RED "\033[38;2;237;28;36m"
#define DOG_BROWN_1 "\033[38;2;156;90;60m"
#define DOG_BROWN_2 "\033[38;2;89;51;34m"


void print_sheep(){
	int pole[8][8];
	for(int i = 0; i<8; i++){ //all white wool
		for(int o = 0; o<8; o++){
			pole[i][o] = 5;
		}
	}
	for(int i = 1; i<7; i++){ //3. line
		pole[2][i] = 6;
	}
	pole[3][1] = 2; //4. line
	pole[3][2] = 1;
	pole[3][3] = 6;
	pole[3][4] = 6;
	pole[3][5] = 1;
	pole[3][6] = 2;
	for(int i = 1; i<7; i++){ //5. line
		pole[4][i] = 6;
	}
	pole[5][2] = 6; //6. line
	pole[5][3] = 4;
	pole[5][4] = 4;
	pole[5][5] = 6;

	pole[6][2] = 6; //7. line
	pole[6][3] = 3;
	pole[6][4] = 3;
	pole[6][5] = 6;


	for(int i = 0; i<8; i++){ //print
		for(int o = 0; o<8; o++){
			if(pole[i][o] == 1){
				printf(WHITE "\xE2\x96\x88" RESET);
				printf(WHITE "\xE2\x96\x88" RESET);
			}
			else if(pole[i][o] == 2){
				printf(SHEEP_EYE_BLACK "\xE2\x96\x88" RESET);
				printf(SHEEP_EYE_BLACK "\xE2\x96\x88" RESET);
			}
			else if(pole[i][o] == 3){
				printf(SHEEP_NOSE_LIGHT "\xE2\x96\x88" RESET);
				printf(SHEEP_NOSE_LIGHT "\xE2\x96\x88" RESET);
			}
			else if(pole[i][o] == 4){
				printf(SHEEP_NOSE_PINK "\xE2\x96\x88" RESET);
				printf(SHEEP_NOSE_PINK "\xE2\x96\x88" RESET);
			}
			else if(pole[i][o] == 5){
				printf(SHEEP_WOOL_SHADOW "\xE2\x96\x88" RESET);
				printf(SHEEP_WOOL_SHADOW "\xE2\x96\x88" RESET);
			}
			else if(pole[i][o] == 6){
				printf(SHEEP_SKIN "\xE2\x96\x88" RESET);
				printf(SHEEP_SKIN "\xE2\x96\x88" RESET);
			}
			else{
				printf(GREEN "\xE2\x96\x88" RESET);
				printf(GREEN "\xE2\x96\x88" RESET);
			}
		}
		printf("\n");
	}
}
void print_zom(){
    int pole[8][8];
    for(int i = 0; i<8; i++){ //all dark zel
        for(int o = 0; o<8; o++){
            pole[i][o] = 1;
        }
    }
    pole[1][4] = 2;  //2. line
    pole[1][5] = 2;

    for(int i = 1; i<7; i++){// 3. line
        pole[2][i] = 2;
    }
    for(int i = 0; i<7; i++){// 4. line
        pole[3][i] = 2;
    }
    for(int i = 0; i<8; i++){// 5. line
        pole[4][i] = 2;
    }
    pole[4][1] = 3;
    pole[4][2] = 3;
    pole[4][5] = 3;
    pole[4][6] = 3;

    pole[5][1] = 2; //6. line
    pole[5][2] = 2;
    pole[5][5] = 2;
    pole[5][6] = 2;

    pole[6][1] = 2; //7. line
    pole[6][3] = 2;
    pole[6][4] = 2;
    pole[6][6] = 2;

    for(int i = 0; i<8; i++){ //print
        for(int o = 0; o<8; o++){
            if(pole[i][o] == 1){
                printf(FOREST_GREEN "\xE2\x96\x88" RESET);
				printf(FOREST_GREEN "\xE2\x96\x88" RESET);
            }
            else if(pole[i][o] == 2){
                printf(LIME_GREEN "\xE2\x96\x88" RESET);
				printf(LIME_GREEN "\xE2\x96\x88" RESET);
            }
            else{
                printf(BLACK "\xE2\x96\x88" RESET);
				printf(BLACK "\xE2\x96\x88" RESET);
            }
        }
        printf("\n");
    }

}
void print_skel(){
	int pole[8][8];
	for(int i = 0; i<8; i++){ //all dark gray
		for(int o = 0; o<8; o++){
			pole[i][o] = 2;
		}
	}
	for(int i = 0; i<8; i++){ //hair 1. line
		pole[0][i] = 1; 
	}
	for(int i = 0; i<8; i++){ //hair 2. line
		pole[1][i] = 1; 
	}
	pole[1][4] = 2; //celo 2. line
	pole[1][5] = 2;
	
	for(int i = 0; i<8; i++){ //bone 3. line
		pole[2][i] = 2; 
	}
	pole[2][0] = 1; //3. line hair

	for(int i = 0; i<8; i++){ //bone 4. line
		pole[3][i] = 2; 
	}

	for(int i = 0; i<8; i++){ //bone 5. line
		pole[4][i] = 2; 
	}
	pole[4][1] = 4; //eyes 5. line
	pole[4][2] = 4;
	pole[4][5] = 4;
	pole[4][6] = 4;

	for(int i = 0; i<8; i++){ //bone 6. line
		pole[5][i] = 2; 
	}
	pole[5][3] = 1; //nose 6. line
	pole[5][4] = 1;

	pole[6][0] = 1; //mid 7. line
	for(int i = 1; i<7; i++){ //mouth 7. line
		pole[6][i] = 4; 
	}
	pole[6][7] = 1; //shadow 7. line
	for(int i = 0; i<8; i++){ //shadow 8. line
		pole[7][i] = 5; 
	}

	for(int i = 0; i<8; i++){ //print
		for(int o = 0; o<8; o++){
			if(pole[i][o] == 1){
				printf(SKEL_MEDIUM "\xE2\x96\x88" RESET);
				printf(SKEL_MEDIUM "\xE2\x96\x88" RESET);
			}
			else if(pole[i][o] == 2){
				printf(SKEL_BONE "\xE2\x96\x88" RESET);
				printf(SKEL_BONE "\xE2\x96\x88" RESET);
			}
			else if(pole[i][o] == 3){
				printf(SKEL_HIGHLIGHT "\xE2\x96\x88" RESET);
				printf(SKEL_HIGHLIGHT "\xE2\x96\x88" RESET);
			}
			else if(pole[i][o] == 4){
				printf(SKEL_EYE_DARK "\xE2\x96\x88" RESET);
				printf(SKEL_EYE_DARK "\xE2\x96\x88" RESET);
			}
			else if(pole[i][o] == 5){
				printf(SKEL_SHADOW "\xE2\x96\x88" RESET);
				printf(SKEL_SHADOW "\xE2\x96\x88" RESET);
			}
			else{
				printf(GREEN "\xE2\x96\x88" RESET);
				printf(GREEN "\xE2\x96\x88" RESET);
			}
		}
		printf("\n");
	}
}
void matika_dice(int kos_1, int d_1[7][7]){
	switch (kos_1){
		case 1:
			d_1[3][3] = 2;
		break;
		case 2:
			d_1[3][1] = 2;
			d_1[3][5] = 2;
		break;
		case 3:
			d_1[1][1] = 2;
			d_1[3][3] = 2;
			d_1[5][5] = 2;
		break;
		case 4:
			d_1[1][1] = 2;
			d_1[5][1] = 2;
			d_1[1][5] = 2;
			d_1[5][5] = 2;
		break;
		case 5:
			d_1[1][1] = 2;
			d_1[5][1] = 2;
			d_1[1][5] = 2;
			d_1[5][5] = 2;
			d_1[3][3] = 2;
		break;
		case 6:
			d_1[1][1] = 2;
			d_1[5][1] = 2;
			d_1[1][5] = 2;
			d_1[5][5] = 2;
			d_1[1][3] = 2;
			d_1[5][3] = 2;			
		break;
	}
}
void dice(int kos_1, int kos_2){
	int d_1[7][7];
	int d_2[7][7];
	for(int i = 0; i < 7; i++){
		for(int j = 0; j <7; j++){
			d_1[i][j] = 1;
		}
	}
	for(int i = 0; i < 7; i++){
		for(int j = 0; j <7; j++){
			d_2[i][j] = 1;
		}
	}
	
	matika_dice(kos_1, d_1);
	matika_dice(kos_2, d_2);
	

	//tisk
	for(int i = 0; i < 7; i++){
		for(int j = 0; j <7; j++){
			if(d_1[i][j] == 1){
				printf(WHITE "\xE2\x96\x88" RESET);
				printf(WHITE "\xE2\x96\x88" RESET);
			}
			else if(d_1[i][j] == 2){
				printf(BLACK "\xE2\x96\x88" RESET);
				printf(BLACK "\xE2\x96\x88" RESET);
			}
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
	for(int i = 0; i < 7; i++){
		for(int j = 0; j <7; j++){
			if(d_2[i][j] == 1){
				printf(WHITE "\xE2\x96\x88" RESET);
				printf(WHITE "\xE2\x96\x88" RESET);
			}
			else if(d_2[i][j] == 2){
				printf(BLACK "\xE2\x96\x88" RESET);
				printf(BLACK "\xE2\x96\x88" RESET);
			}
		}
		printf("\n");
	}

}
void print_doggo(int volba_barva){
	const char * chosen_color;
	switch(volba_barva){
		case 1:
			chosen_color = RED;
		break;
		case 2:
			chosen_color = BLUE;
		break;
		case 3:
			chosen_color = GREEN;
		break;
		case 4:
			chosen_color = YELLOW;
		break;
		case 5:
			chosen_color = ORANGE;
		break;
		case 6:
			chosen_color = PURPLE;
		break;
		default:
			chosen_color = BLACK;
		break;
	}


	printf("\n "); //new line
	printf(" ");
	for(int i = 0; i<4; i++){
		printf(DOG_GRAY_1 "\xE2\x96\x88" RESET);
	}
	for(int i = 0; i<4; i++){
		printf(" ");
	}
	for(int i = 0; i<4; i++){
		printf(DOG_GRAY_1 "\xE2\x96\x88" RESET);
	}
	printf("\n "); //new line
	printf(" ");
	for(int i = 0; i<4; i++){
		printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);
	}
	for(int i = 0; i<4; i++){
		printf(" ");
	}
	for(int i = 0; i<4; i++){
		printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);
	}	
	printf("\n "); //new line
	printf("%s\xE2\x96\x88" RESET, chosen_color);

	printf(DOG_GRAY_3 "\xE2\x96\x88" RESET);
	printf(DOG_GRAY_3 "\xE2\x96\x88" RESET);

	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);
	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);
	for(int i = 0; i<4; i++){
		printf(DOG_GRAY_1 "\xE2\x96\x88" RESET);
	}
	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);
	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);

	printf(DOG_GRAY_3 "\xE2\x96\x88" RESET);
	printf(DOG_GRAY_3 "\xE2\x96\x88" RESET);

	printf("%s\xE2\x96\x88" RESET, chosen_color);
	printf("\n "); //new line
	printf("%s\xE2\x96\x88" RESET, chosen_color);

	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);
	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);	

	printf(WHITE "\xE2\x96\x88" RESET);
	printf(WHITE "\xE2\x96\x88" RESET);
	for(int i = 0; i<4; i++){
		printf(DOG_GRAY_1 "\xE2\x96\x88" RESET);
	}
	printf(WHITE "\xE2\x96\x88" RESET);
	printf(WHITE "\xE2\x96\x88" RESET);

	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);
	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);

	printf("%s\xE2\x96\x88" RESET, chosen_color);
	printf("\n "); //new line
	printf("%s\xE2\x96\x88" RESET, chosen_color);
	
	printf(WHITE "\xE2\x96\x88" RESET);
	printf(WHITE "\xE2\x96\x88" RESET);
	printf(" ");
	printf(" ");
	for(int i = 0; i<4; i++){
		printf(DOG_BROWN_1 "\xE2\x96\x88" RESET);
	}
	printf(" ");
	printf(" ");
	printf(WHITE "\xE2\x96\x88" RESET);
	printf(WHITE "\xE2\x96\x88" RESET);

	printf("%s\xE2\x96\x88" RESET, chosen_color);
	printf("\n "); //new line
	printf("%s\xE2\x96\x88" RESET, chosen_color);

	printf(DOG_BROWN_1 "\xE2\x96\x88" RESET);
	printf(DOG_BROWN_1 "\xE2\x96\x88" RESET);	

	printf(DOG_BROWN_2 "\xE2\x96\x88" RESET);
	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);
	printf(DOG_GRAY_1 "\xE2\x96\x88" RESET);
	printf(" ");
	printf(" ");
	printf(DOG_GRAY_1 "\xE2\x96\x88" RESET);
	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);
	printf(DOG_BROWN_2 "\xE2\x96\x88" RESET);

	printf(DOG_BROWN_1 "\xE2\x96\x88" RESET);
	printf(DOG_BROWN_1 "\xE2\x96\x88" RESET);

	printf("%s\xE2\x96\x88" RESET, chosen_color);
	printf("\n "); //new line
	printf("%s\xE2\x96\x88" RESET, chosen_color);

	printf(DOG_BROWN_2 "\xE2\x96\x88" RESET);
	printf(DOG_BROWN_2 "\xE2\x96\x88" RESET);

	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);

	for(int i = 0; i<6; i++){
		printf(DOG_GRAY_1 "\xE2\x96\x88" RESET);
	}
	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);

	printf(DOG_BROWN_2 "\xE2\x96\x88" RESET);
	printf(DOG_BROWN_2 "\xE2\x96\x88" RESET);

	printf("%s\xE2\x96\x88" RESET, chosen_color);
	printf("\n "); //new line
	printf("%s\xE2\x96\x88" RESET, chosen_color);

	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);
	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);
	printf(DOG_GRAY_1 "\xE2\x96\x88" RESET);

	for(int i = 0; i<6; i++){
		printf(" ");
	}

	printf(DOG_GRAY_1 "\xE2\x96\x88" RESET);
	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);
	printf(DOG_GRAY_2 "\xE2\x96\x88" RESET);

	printf("%s\xE2\x96\x88" RESET, chosen_color);
	printf("\n "); //new line

	for(int i = 0; i<14; i++){
		printf("%s\xE2\x96\x88" RESET, chosen_color);
	}
	printf("\n");

}


#define MODE_BTN     9          // mode button pin
#define CHECK        2          // pin of check button input
#define LOWER_BUTTON 3          // braille button with the lowest pin number
#define BRAILLE_BTNS 6          // quantity of buttons

#define COLUMNS 7
#define RAWS    33

// BEGIN - scopes of search of each MODE
#define ALPH_FRST_RW   0 
#define ALPH_LST_RW   25

#define NUM_FRST_RW    0
#define NUM_LST_RW     9

#define PUNCT_FRST_RW 26
#define PUNCT_LST_RW  32
// END

#define MODES 3                // quantity of implemented modes
#define ALPHA 0
#define NUM   1
#define PONCT 2

int mode = ALPHA;

// braille alphabet
int alphabet[RAWS][COLUMNS] = {
    {1, 0, 0, 0, 0, 0, 'A'},
    {1, 1, 0, 0, 0, 0, 'B'},
    {1, 0, 0, 1, 0, 0, 'C'},
    {1, 0, 0, 1, 1, 0, 'D'},
    {1, 0, 0, 0, 1, 0, 'E'},
    {1, 1, 0, 1, 0, 0, 'F'},
    {1, 1, 0, 1, 1, 0, 'G'},
    {1, 1, 0, 0, 1, 0, 'H'},
    {0, 1, 0, 1, 0, 0, 'I'},
    {0, 1, 0, 1, 1, 0, 'J'},
    {1, 0, 1, 0, 0, 0, 'K'},
    {1, 1, 1, 0, 0, 0, 'L'},
    {1, 0, 1, 1, 0, 0, 'M'},
    {1, 0, 1, 1, 1, 0, 'N'},
    {1, 0, 1, 0, 1, 0, 'O'},
    {1, 1, 1, 1, 0, 0, 'P'},
    {1, 1, 1, 1, 1, 0, 'Q'},
    {1, 1, 1, 0, 1, 0, 'R'},
    {0, 1, 1, 1, 0, 0, 'S'},
    {0, 1, 1, 1, 1, 0, 'T'},
    {1, 0, 1, 0, 0, 1, 'U'},
    {1, 1, 1, 0, 0, 1, 'V'},
    {0, 1, 0, 1, 1, 1, 'W'},
    {1, 0, 1, 1, 0, 1, 'X'},
    {1, 0, 1, 1, 1, 1, 'Y'},
    {1, 0, 1, 0, 1, 1, 'Z'},
    {0, 1, 0, 0, 0, 0, ','},
    {0, 1, 1, 0, 0, 0, ';'},
    {0, 1, 0, 0, 1, 0, ':'},
    {0, 0, 1, 0, 0, 0, '.'},
    {0, 1, 0, 0, 0, 1, '?'},
    {0, 1, 1, 0, 1, 0, '!'},
    {0, 0, 1, 0, 0, 1, '-'}
};

int input[BRAILLE_BTNS] = {0, 0, 0, 0, 0, 0};

char alphabet_to_num(char*);
bool change_mode(bool);
int keyboard_input(int);
void find_character(int);

void setup(){
    pinMode(2, INPUT);  // checkButton
    // braille input buttons
    pinMode(3, INPUT);  // 0th BTN
    pinMode(4, INPUT);  // 1st BTN
    pinMode(5, INPUT);  // 2nd BTN
    pinMode(6, INPUT);  // 3rd BTN
    pinMode(7, INPUT);  // 4th BTN
    pinMode(8, INPUT);  // 5th BTN
    pinMode(9, INPUT);  // Mode BTN

    Serial.begin(9600);
    Serial.println("[+] Current Input Mode: Alphabetic");
}

void loop(){
    int check_button = digitalRead(CHECK);
    bool mode_button = digitalRead(MODE_BTN);
    int input_state = 0;

    change_mode(mode_button);
    input_state = keyboard_input(check_button);
    find_character(input_state);     
}

int keyboard_input(int check_button){

    if(check_button){
        delay(500);

        Serial.print("[+] Keyboard Input:\t\t");
        for(int i = 0; i <  BRAILLE_BTNS; i++){

            // input values inversion 
            if(digitalRead(LOWER_BUTTON + i)){
                input[i] = 0;
            }else 
                input[i] = 1;

            Serial.print(input[i]);
        }

        Serial.println(';');

        return 1;
    }
}

void find_character(int state){
    int flag;
    // search scope
    int first_raw, last_raw;
    char chrt;


    if(state){

        switch(mode){
            case ALPHA:  // 0
                first_raw = ALPH_FRST_RW;
                last_raw = ALPH_LST_RW;
                break;
            case NUM:    // 1
                first_raw = NUM_FRST_RW;
                last_raw = NUM_LST_RW;
                break;
            case PONCT:  // 2
                first_raw = PUNCT_FRST_RW;
                last_raw = PUNCT_LST_RW;
            default:
                break;
        }

        for(int i = first_raw; i <= last_raw; i++){
            flag = 1;

            for(int j = 0; j < COLUMNS - 1; j++){
                if(alphabet[i][j] != input[j]){
                    flag = 0;
                    break;
                }
            }

            if(flag){
                // matched character
                chrt = alphabet[i][COLUMNS - 1];

                // if numeric mode
                if(mode == NUM)
                    alphabet_to_num(&chrt);

                // monitor print
                Serial.println("[+] Corresponding character:\t'" + (String)chrt + "';");                
                Serial.println("[+] Outputing character sound...\n");
                return;
            }
        }

        Serial.println("[!] Error message:\t\tCharacter not found;\n"
                "[+] Outputing Sound...\t\t\"Hmm, ainda nao conheco essa letrinha.\";\n");
    }       
}

bool change_mode(bool state){

    if(state){
        delay(150);
        mode++;

        if(mode >= MODES)
            mode = 0;

        Serial.print("[+] Current Input Mode: ");
        switch(mode){
            case ALPHA:
                Serial.println("Alphabetic");
                break;
            case NUM:
                Serial.println("Numeric");
                break;
            case PONCT:
                Serial.println("Punctuation");
            default:
                break;
        }

    }
}

char alphabet_to_num(char *letter){
    char *num;

    num = letter;

    *num -= 'A';
    *num += '0';
    *num += 1;

    if(*num > '9')
        *num = '0';
}

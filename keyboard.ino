#define CHECK        2          // pin of check button input
#define LOWER_BUTTON 3          // braille button with the lowest pin number

#define COLUMNS 7
#define RAWS    26

#define BRAILLE_BTNS 6


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
    {1, 0, 1, 0, 1, 1, 'Z'}
};

int input[BRAILLE_BTNS] = {0, 0, 0, 0, 0, 0};

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
    Serial.begin(9600);
}

void loop(){
    int check_button = digitalRead(CHECK);
    int input_state = 0;
    
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
    char chrt;
    
    if(state){
        for(int i = 0; i < RAWS; i++){
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
                Serial.println("[+] Corresponding character:\t'" + (String)chrt + "';");                
                Serial.println("[+] Outputing character sound...\n");
                return;
            }
        }
        //monitor error messages 
        Serial.println("[!] Error message:\t\tCharacter not found;\n"
                       "[+] Outputing Sound...\t\t\"Hmm, ainda nao conheco essa letrinha.\";\n");
    }   
}


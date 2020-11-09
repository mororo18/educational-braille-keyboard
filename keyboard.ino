
#define CHECK        2                         // porta do botao de checagem
#define LOWER_BUTTON 3          // porta de menor valor numerico de um botao

#define COLUMNS 7
#define RAWS    26


// braille shapes
int character[RAWS][COLUMNS] = {
    {1, 0, 0, 0, 0, 0, ‘A’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’},
    {1, 0, 1, 0, 0, 0, ‘B’}
};

int input[6] = {0, 0, 0, 0, 0, 0};

void keyboard_input(int);

void setup(){
    pinMode(2, INPUT);   // checkButton
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    pinMode(8, INPUT);
    Serial.begin(9600);

void loop(){
    int check_button = digitalRead(CHECK);
    
    //input state
    keyboard_input(check_button);
}

void keyboard_input(int check_button){

    if(check_button){
        delay(500);
        for(int i = 0; i <  6; i++){

            // input values inversion 
            if(digitalRead(LOWER_BUTTON + i)){
                input[i] = 0;
            }else 
                input[i] = 1;

        Serial.print(input[i]);
        }
    
    Serial.println(';');
    }
}

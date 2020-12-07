from selenium import webdriver
from webdriver_manager.chrome import ChromeDriverManager
from time import sleep
from playsound import playsound

monitor_button_ID = 'SERIAL_MONITOR_ID'
monitor_CSS_SELECTOR = 'div.code_panel__serial__content__text.js-code_panel__serial__text.js-code_editor__serial-monitor__content'
code_button_XPATH = '/html/body/div[2]/div/div/div[4]/div/div/div/div[1]/div[3]/a'
clear_button_CSS_SELECTOR = 'a.circ_btn.circ_btn--m.circ_btn--none_accent_accent.code_panel__serial__button.js-code_panel__serial__clear.js-analytics'

punct = {
    ',' : "comma",
    ';' : "semicolon",
    ':' : "colon",
    '.' : "dot",
    '?' : "question",
    '!' : "exclamation",
    '-' : "hyphen"
}

driver = webdriver.Chrome(ChromeDriverManager().install())
driver.maximize_window()

def monitor_observe_mode():
    mode_message = "[+] Current Input Mode:"
    MODE_POS = 24

    content = driver.find_element_by_css_selector(monitor_CSS_SELECTOR)
    content = content.text
    pos = content.rfind(mode_message)

    if pos != -1:
        mode = content[(MODE_POS+pos):]
        
        filename = "sounds/" + mode +".wav"
        message = "\nOutputing \'" + mode + " Mode\' Sound..."
        print(message)
        playsound(filename)


def symb_to_word(symb):

    if ('A' <= symb and symb <= 'Z') or ('0' <= symb and symb <= '9') :
        return str(symb)
    
    else:
        return punct[symb]


def monitor_observe_char():
    char_message = "[+] Corresponding character:"
    error_message = "[!] Error message:"
    CHAR_POS = 30

    content = driver.find_element_by_css_selector(monitor_CSS_SELECTOR)
    content = content.text
    # in case of mode change
    if content == "":
        return

    pos_c = content.rfind(char_message)
    pos_e = content.rfind(error_message)

    if(pos_c != -1):
        char = content[pos_c + CHAR_POS]
        char = symb_to_word(char)
        filename = "sounds/" + char + ".wav"
        message = "\nOutputing \'" + char + "\' Sound..."

        print(message)
        playsound(filename)

    elif pos_e != -1:
        print("\nOutputing Error Sound..\n")
        playsound("sounds\error.wav")

def monitor_observe():

    while(1):
        # serial monitor content
        content = driver.find_element_by_css_selector(monitor_CSS_SELECTOR)
        content = content.text

        if (content != ""):
            sleep(2)

            monitor_observe_mode()
            monitor_observe_char()

            clear_button = driver.find_element_by_css_selector(clear_button_CSS_SELECTOR)
            clear_button.click()

def start():
    
    driver.get('https://www.tinkercad.com/things/ktPH2wSIrIG/viewel')
    sleep(6)
    
    code_button = driver.find_element_by_xpath(code_button_XPATH)
    code_button.click()
    sleep(1)
    
    monitor_button = driver.find_element_by_id(monitor_button_ID)
    monitor_button.click()

    monitor_observe()
        
start()

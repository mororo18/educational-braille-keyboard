from selenium import webdriver
from webdriver_manager.chrome import ChromeDriverManager
from time import sleep
from playsound import playsound

monitor_button_ID = 'SERIAL_MONITOR_ID'
monitor_CSS_SELECTOR = 'div.code_panel__serial__content__text.js-code_panel__serial__text.js-code_editor__serial-monitor__content'
code_button_XPATH = '/html/body/div[2]/div/div/div[4]/div/div/div/div[1]/div[3]/a'
clear_button_CSS_SELECTOR = 'a.circ_btn.circ_btn--m.circ_btn--none_accent_accent.code_panel__serial__button.js-code_panel__serial__clear.js-analytics'

driver = webdriver.Chrome(ChromeDriverManager().install())
driver.maximize_window()

def get_char():
    char_message = "[+] Corresponding character:"
    CHAR_POS = 30

    content = driver.find_element_by_css_selector(monitor_CSS_SELECTOR)
    content = content.text
    pos = content.rfind(char_message)

    if(pos != -1):
        char = content[pos + CHAR_POS]
        filename = "sounds/" + str(char) + ".wav"
        message = "\nOutputing \'" + str(char) + "\' Sound..."

        print(message)
        playsound(filename)

    else:
        print("\nOutputing Error Sound..\n")

def monitor_observer():

    while(1):
        # serial monitor content
        content = driver.find_element_by_css_selector(monitor_CSS_SELECTOR)
        content = content.text

        if (content != ""):
            sleep(2)

            get_char()

            clear_button = driver.find_element_by_css_selector(clear_button_CSS_SELECTOR)
            clear_button.click()

def start_simulation():
    
    driver.get('https://www.tinkercad.com/things/6Vrjlavkf2A/viewel')
    sleep(6)
    
    code_button = driver.find_element_by_xpath(code_button_XPATH)
    code_button.click()
    sleep(1)
    
    monitor_button = driver.find_element_by_id(monitor_button_ID)
    monitor_button.click()

    monitor_observer()
        
start_simulation()

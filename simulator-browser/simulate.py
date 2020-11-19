from selenium import webdriver
from webdriver_manager.chrome import ChromeDriverManager

from time import sleep
from playsound import playsound

b = webdriver.Chrome(ChromeDriverManager().install())

b.get('https://www.tinkercad.com/things/6Vrjlavkf2A/viewel')
sleep(8)

# code button
b.find_element_by_xpath('/html/body/div[2]/div/div/div[4]/div/div/div/div[1]/div[3]/a').click()
sleep(1)

# monitor-serial button
b.find_element_by_id('SERIAL_MONITOR_ID').click()

find_message = "[+] Corresponding character:"
CHAR_POS = 30

while(1):
    # serial monitor content
    content = b.find_element_by_css_selector('div.code_panel__serial__content__text.js-code_panel__serial__text.js-code_editor__serial-monitor__content').text

    if (content != ""):
        sleep(2)

        content = b.find_element_by_css_selector('div.code_panel__serial__content__text.js-code_panel__serial__text.js-code_editor__serial-monitor__content').text
        pos = content.rfind(find_message)

        if(pos != -1):
            # char position on the string
            char = content[pos + CHAR_POS]
            filename = "sounds/" + str(char) + ".wav"
            message = "Outputing \'" + str(char) + "\' Sound...\n"

            print(message)
            playsound(filename)

        else:
            print("Outputing Error Sound..\n")

        # clear button
        b.find_element_by_css_selector('a.circ_btn.circ_btn--m.circ_btn--none_accent_accent.code_panel__serial__button.js-code_panel__serial__clear.js-analytics').click()


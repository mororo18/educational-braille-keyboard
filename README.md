# Educational Braille-keyboard Arduino based

The purpose of making this keyboard is turn more easy and funny the alphabetization of children with blindness or some level of visual impairment. 
It basically works by translating the inserted braille cell to the sound of its respective character in the Latin alphabet.

Model
------
![Model](/imgs/model.png)

Usage
------
The six on/off front buttons represents a custom braille cell that can be written by changing the input state of the buttons. 
The 'confirm' button, at the top, takes this current cell and makes that the corresponding character be emitted.

![Usage](/imgs/example.jpg)

Online Simulation 
------------------
The simulation is available on [Tinkercad](https://www.tinkercad.com/things/6Vrjlavkf2A/viewel).

![Schematics](/imgs/schematics.png)


Simulation With Sound Response
---------------------
### Setup
* To simulate in the browser with sound response, a web driver for Chrome is required - [ChromeDriver](https://chromedriver.chromium.org/downloads).

       pip3 install selenium
       pip3 install playsound
       pip3 install webdriver_manager 

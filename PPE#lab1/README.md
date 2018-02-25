# Report
## Laboratory work Nr. 1
### Title : Window. Window handling. Basic window’s form elements

### Purpose of the laboratory:
Gain knowledge about basics of event-driven programming about main elements and possibilities of Win32 API. To understand how message processing, window class and window procedure works.

###Laboratory Work requirements
#### Mandatory Objectives:
* Choose a Programming Style Guideline that you'll follow
* Create a Windows application
* Add 2 buttons to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
* Add 2 text elements to window: one with default styles, one with custom styles (size, background, text color, font family, font size) [one of them should be something funny]
* On windows resize, one of the texts should "reflow" and be in window's center (vertically and horizontally)

#### Objectives with points
* Add 2 text inputs to window: one with default styles, one with custom styles (size, background, text color, font family, font size) (1pt)
* Make elements to fit window on resize (1 pt) (hint: you can limit minimal window width and height)
* Make elements to interact or change other elements (1 pt each different interactions) (0-2 pt) (ex. on button click, change text element color or position)
* Change behavior of different window actions (at least 3). For ex.: on clicking close button, move window to a random location on display's working space (1 pt)
* Write your own PSG (you can take existent one and modify it) and argue why it is better (for you) (1 pt)

Laboratory work implementation
#### The functionality:
* A button (with my own style) that changes the background image.
* Text (with my own style) that represents the name of the application and flow in the center of the window on resize
* Text entries where you should introduce the name, surname, and age
* Generate button, that will generate a sentence in the edit box
* When pressing the close button, the windows is resized several times, then it is closed.
* Music should be playing on the background

An interesting task was to make buttons, text entries and static text boxes with our own style, due to this objectives I found out how to use WM_CLTCOLOREDIT, WM_CLTCOLORSTATIC and WM_DRAWITEM messages, also it was  interesting for me how music and background images can be added, so I used PlaySoundW() and BitBlt() functions.
#### Result
![Alt text] (result1.png)

#### Conclusion
In this laboratory work, I gained the basic knowledge how to make a windows application and how to handle the basic elements such as MessageBoxes, Button, Texts, Text Entries, I learned how the messages are processed how we can add some new functionalities to our application using WM_COMMAND, WM_PAINT and other standart messages and how the bitmap images can be processed.

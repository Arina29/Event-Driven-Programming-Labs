# Laboratory Work nr.2
## Subject
_Advanced Form Elements. Child Windows. Basics of Working With Keyboard._

## Mandatory Objectives
* Display a dialog box on some event (ex. on clicking some button)
* Add a system menu to your application with at least 3 items (add actions to that items)
* Add a scroll bar that will change any visible parameter of any other element (color of a text)
* Hook keyboard input. Add 2 custom events for 2 different keyboard combinations (ex. change window background on ctrl+space)

## Bonus Objectives
* Add a listbox and attach some events when any element is accessed (clicked) (2 pt)
* Add 2 scroll bars that will manage main window size or position
* Customize your application by adding an icon and using different cursor in application (1 pt)
* Use a scroll bar to scroll through application working space. Scroll should appear only when necessary (eg. when window width is smaller than 300px) (1 pt)

## Result
* When "Change Background" button is clicked, a dialog box appears
* There is a menu with some items
  - File(New) starts the music
  - File(Open) opens the dialog box
  - File(Quit) exits the application
  - Help(About) displays a Message Box
  - View(Toolbar) a Color picker window appears (PS just appears :D)
 * In dialog Box there is a Scroll Bar that changes window background
 * Hook keyboard input
  1. [Ctrl + Down arrow]  changes text color
  2. [Shift + Up arrow] displays a MessageBox
 * There is a list box , you can add some text to it, you can delete some items, when you click on an item , a message box is displayed
 * The application has 2 scroll bars in the main wondow, responsible for window size
 * It uses the hand cursor and a custom icon.
 * A scroll bar to the listbox is added and a vertical scroll bar appears in the main window when it is smaller than 400px. 
  
  ## Conclusion
  In this laboratory work, I've learned some new basic features used in event driven programming as, dialog boxes, list boxes, menus, scroll bars,
  icons, cursors and others. A little bit confusing was the process of making the dialog box, because it needs another procedure and their structures
  can be made using resources. Another challenge were the scrollbars, especially the case when you have multiple horizontal scroll bars,
  responsible for different processes, but you can use only one window message: WM_HSCROLL.
  In general by solving all tasks, my skills in EDP has increased, so that now I understand how to use all these basic elements. 
  
    

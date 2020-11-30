Screenwriting
===============

This is an application which simulates the writing of a television episode by professional screenwriters. It is written using C++ and the Qt framework. 

The application has the following functionalities:
  * at the start, it opens a window for each writer and shows all the ideas lauched so far using QTableView and sorting them by the act
  * any writer can add an idea
  * senior writers can revise ideas and accept them
  * the score for a certain participant is shown in their window
  * when a modification is done by any writer, all the writers will see it
  * update the files when the application is done
  
Therefore, I used the Observer pattern. I made used of QTableView to show the data. I also used files to read the data from/ to write the data to.
The widgets are automatically resized and repositioned. I also used a layered architecture and I created my own exceptions. And I tested some functionalities.

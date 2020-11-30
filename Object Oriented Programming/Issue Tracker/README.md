Issue Tracker
===============

This is an application which simulates the development and testing of a software application. It is written using C++ and the Qt framework. 

The application has the following functionalities:
  * at the start, it opens a window for each user, showing all the issues
  * only testers can report issues by pressing a button
  * both programmers and testers can remove issues, but only if the status is closed
  * only programmers can resolve issues, by pressing a button
  * all the users will see any modification done
  * update the files when the application is done
  
Therefore, I used the Observer pattern. I also used files to read the data from/ to write the data to.
The widgets are automatically resized and repositioned. I also used a layered architecture and I created my own exceptions.

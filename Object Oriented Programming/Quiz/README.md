Quiz
===============

This is an application which simulates a quiz. It is written using C++ and the Qt framework. 

The application has the following functionalities:
  * at the start, it opens a window for the presenter and also for each participant, showing different things for each of them
  * only the presenter can add questions by pressing a button
  * the participants can answer questions by pressing them and typing the answer
  * the score for a certain participant is shown in their window
  * when a modification is done by the presenter all the participants will see it
  * update the files when the application is done
  
Therefore, I used the Observer pattern. I also used files to read the data from/ to write the data to.
The widgets are automatically resized and repositioned. I also used a layered architecture and I created my own exceptions. And I tested some functionalities.

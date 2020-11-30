Question and Answer Site
===============

This is an application which simulates a question and answer site(e.g. StackOverflow). It is written using C++ and the Qt framework. 

The application has the following functionalities:
  * at the start, it opens a window for each user, showing all the questions
  * another window will allow any user to search for a question, and the list updates as the user types in the search bar
  * any user can add a new question by pressing a button
  * when a question is clicked, all the answer to that question will be shown
  * any user can add an answer
  * users can upvote and downvote a selected answer
  * when a modification is done, all the users will see it and also the search window will be updated
  
Therefore, I used the Observer pattern. I made of QSpinBox for the voting part. I also used files to read the data from/ to write the data to.
The widgets are automatically resized and repositioned. I also used a layered architecture and I created my own exceptions.

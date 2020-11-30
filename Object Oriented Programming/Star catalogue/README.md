Star catalogue
===============

This is an application which helps astronomers catalogue stars. It is written using C++ and the Qt framework. 

The application has the following functionalities:
  * at the start, it opens a window for each astronomer and contains a QTableView which displays the data for all stars
  * a chechbox allows the astronomer to see only the stars they are studying
  * any astronomer can add a new star
  * an astronomer can search stars, the list being modified as the astronomer types in
  * when a modification is done by an astronomer, everyone will see it
  * there will be a button which opens a new window that shows all stars in the current constellation
  
What I used while developing this application:
  * STL
  * layered architecture
  * layouts for automatically resizing and repositiong the widgets
  * created my own exceptions
  * Observer pattern
  * MVC pattern
  * QPainter
  * QCheckBox
  * files to read/ write the data

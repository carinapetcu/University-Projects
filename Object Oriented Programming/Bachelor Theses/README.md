Bachelor Theses
===============

This is an application for the management of bachelor theses in the faculty. It is written using C++ and the Qt framework. 

The application has the following functionalities:
  * at the start, it opens a window for each teacher, having the students coordinated by that teacher
  * the teacher can search for any student, the list being updated as the teacher types
  * teacher can edit the students' data
  * a new window will show visual statistics
  * when a modification is done, all the teachers can see it
  
Therefore, the Observer pattern for updating the updates for each teacher. I also used files to read the data from.
The widgets are automatically resized and repositioned. I also used QtCharts for creating the statistics chart.


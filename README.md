Alexey Panchenko
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Description:TODOManager (like trello)

Implement TODOManager application. 

Application should:
- Have an ability to create a board and navigate between them
- Have an ability to create a task and attach it to the specific board
- Task should have next properties:

        a. Description of task
        b. Time the user work on this task
        b. Time to remind about task
- Each task should have a field that show countdown time of it.
- Each task should have a field that show time the user work on this task
- The user is able to add time entry to the task (from 1pm to 3 pm etc)
- The user is able to see work history on any task and total time for each task.
- The user is able to add a reminder to the task.
- Application should make a notification to remind about tasks.
- Documentation: requirements specification, software design documentation (application modules description, UML diagrams).
    
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Instructions for building:

1) Download QtCreator from the official website at the link (preferably the latest version)

https://www.qt.io/

2) Clone to your folder the contents of the folder code:

 `git init`

 `git clone https://github.com/AlexeyLK/GL_Task2/tree/main/TODOManager.git`

3) Open this folder as project in QtCreator

4) Press start in the left bottom corner: startProject.png

https://github.com/AlexeyLK/GL_Task2/tree/main/Images

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Description of all application features:
- user can add the task using "+" button in the upper left corner of the main window
  - when adding a task, the user must fill in 3 fields: the name of the task, the description of the task and set the number of hours for its completion
- user can delete the task using "-" button in the upper left corner of the main window
- user can edit the task using "edit" button in the upper left corner of the main window
- user can switch to the history window to view the history of deleted completed/uncompleted task using the "history" button in the upper left corner of the main window 
  - completed tasks are marked with a green checkmark, and not completed tasks are marked with a red cross
- user can return to main window  using "back" button in the upper left corner of the history window
- user can clear history using "clear" button in the upper right corner of the history window(be careful with this button, data cannot be restored after deletion)

All these buttons can be viewed at the link:
https://github.com/AlexeyLK/GL_Task2/tree/main/Images

- for the convenience of using the program, the system time is available in the upper right corner

- time for the task will be updated every hour

- screenshots of the program can be viewed at the link:

https://github.com/AlexeyLK/GL_Task2/tree/main/Screenshots

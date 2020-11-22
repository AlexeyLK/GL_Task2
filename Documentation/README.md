In file Task.h:

`class Task` - for storing information about one task


fields:

  `long id;` - task ID
  
  `std::string name;` - task name 
  
  `std::string description;` - task description
  
  `long sTime;` - time when tasks were added (in unix time)
  
  `long timeForTask;` - time for work on task  
  
  `long totalTime;` - total work time   
  
  `int status;` - can be 2 - not started (default), 1 - done, 0 - unfulfilled  
  
  `long sWorkSec;`- timer for *start* button  
  
  `long finTime;` - timer for *finish* button
  
  
 methods:

`Task(long id_, std::string name_, std::string description_, long sTime_, long timeForTask_, long totalTime_, int status_, long finTime_)` -
constructor with 8 parameters, used to save tasks to info.txt file

`Task(std::string name_, std::string description_, long timeForTask_)` - constructor with 3 parameters, for  creation task object 

Settes and getters implemented for all fields in a standard way

`void startWork();` - starts the countdown of the work time on the task

`void finishWork();` - stops the countdown of the work time on the task

`void bell();` - function not used (to be implemented and used in the future)

-------------------------------------------------------------------------------------------------------------------------------------

`class Storage` - for storing information about all tasks


fields:

`std::vector<Task> array;` - array of tasks that are in main window

`std::vector<Task> historyArray;` - array of tasks that moved into history window

methods:

 `void Save()` 
 
 `void SaveMain()` - 
to save the tasks to the appropriate files at the time of the program termination in order to save the progress on the tasks. 
These 2 methods could be combined into one(like in UML), but this is more visual.

 `void getHisFromFile()` - reads data from file *historyInfo.txt* and saves to vector *historyArray*
 
 `void getFromFile()` - reads data from file *info.txt* and saves to vector *array*
 
 `void clearForStart()` - clear file *info.txt* after reads (after void getFromFile())
 
 `void clearHForStart()` - clear file *historyInfo.txt** after reads (after void getHisFromFile())
 
 `void addTask(Task R)` - add task object to the vector *array*
 
 `void delTask(long ID)` - delete task from the vector *array* and add to the vector *historyArray*
 
 `void delHistoryTask()` - delete all tasks from the vector *historyArray* and clear file *historyInfo.txt*
   
 `std::vector<Task> *getTasks()` - for display
 
 `std::vector<Task> getHTasks()` -  for display
 
 `void RemoveTask(Task task)` - for display

  ----------------------------------------------------------------------------------------------------------------------------
in file mainwindow.h:

`class MainWindow : public QMainWindow`

`signals: void task_edit(Task *t);` - for edit tasks

private slots:

    // UI
    
    void on_pbEdit_clicked(); - button *Edit* action
    
    void on_pbHistory_clicked(); - button *Edit* action
    
    void on_pbAdd_clicked(); - button *+* action
    
    void on_pbRemove_clicked(); - button *-* action
    

    // logic
    
    void timeout(); - to display the system time at the top right of the project
    
    void addNewTask(Task task); - for add new task
    
    void changeTask(Task task); - for change task(name, description, time for task)
    
    void on_twTaskTable_itemSelectionChanged(); - action when you change the start button to the finish button 
    
    void on_pbStartStop_clicked(); - action when *start* / *stop* pressed
    
    
   `void clearList();` - used in updateList()
   
   `void updateList();` update list with tasks
   
   `void showStorage();` - to display current tasks on the main window
   `void showTask(long id);` 
   
   -------------------------------------------------------------------------------------------------------------------------

in file dlghistory.h:

`class DlgHistory : public QDialog`


 `void on_pbBack_clicked();` - return to the main window
  
 `void on_pbClear_clicked();` - for clear history list and file historyInfo.txt
  
 `void updateList();`
 
 `void clearList();` - like in *mainwindow.h*
 
 
    ---------------------------------------------------------------------------------------------------------------------------
    
in file dlghistory.h:

`class DlgAddTask : public QDialog`

signals:
    void task_add(Task newTask); 
    void task_edit(Task task);
    
slots:
    void on_buttonBox_accepted(); - accepted box 
    void on_buttonBox_rejected(); - for close accepted box 

--------------------------------------------------------------------------------------------------------------------------------

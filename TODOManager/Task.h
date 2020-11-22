//V.L. include guard
#ifndef _TASK_H_
#define _TASK_H_

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <iterator>
#include <list>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <dos.h>

#include <QDebug>

#ifdef __linux__
// #include ...
#elif _WIN32
#include <windows.h>
#else
#endif

const long unitFactor = 1; // secs //3600; // hours

static long NUM = 0;  //for id

class Task {
private:
	long id;
	std::string name;
    std::string description;
    long sTime;
    long timeForTask;
	long totalTime;
	int status;
	long sWorkSec;
    long finTime;

public:

    Task(long id_, std::string name_, std::string description_, long sTime_, long timeForTask_, long totalTime_, int status_, long finTime_) {
		id = id_;
		name = name_;
		description = description_;
		sTime = sTime_;
		timeForTask = timeForTask_;
		totalTime = totalTime_;
		status = status_;
        finTime = finTime_;
	}
    Task(std::string name_, std::string description_, long timeForTask_) {
        name = name_;
        description = description_;
        timeForTask = timeForTask_;
        id = NUM++;                     // static ID counter
        sTime = time(NULL);             // current time
        finTime = 0;
        totalTime = 0;                  // will be calculated by startTask/finishTask
        status = 2;                     // status "new" or whatever
    }

	void setName(std::string n) { name = n; }
    void setDescription(std::string n) { description = n; } //V.L. name instead of description
	void setTotalTime(long tT) { totalTime = tT; }
	void setStatus(int s) { status = s; }
	void setTimeForTask(long tft) { timeForTask = tft; }
	void setSTime(long st) { sTime = st; }
	void setSWorkSec(long sws) { sWorkSec = sws; }
	void setId(long i_d) { id = i_d; }
    void setFinTime(long ft) {finTime = ft;}

	std::string getName() { return name; }
	std::string getDescription() { return description; }
	long getTotalTime() { return totalTime; }
	int getStatus() { return status; }
	long getTimeForTask() { return timeForTask; }
	long getSTime() { return sTime; }
	long getSWorkSec() { return sWorkSec; }
	long getId() { return id; }
    long getFinTime() { return finTime; }

    bool timeExpired() { qDebug() << sTime << timeForTask << time(NULL); return ( (sTime + timeForTask) < time(NULL) ); }

	Task addNewTask();
	void startWork();
	void finishWork();
	void bell();
};


class Storage {
private:
	std::vector<Task> array;
	std::vector<Task> historyArray;

    bool openTasksLoaded;
    bool histTasksLoaded;

public:
	Storage(Task array_) {
		array.push_back(array_);
	}
    Storage(Task historyArray_, int) {
		historyArray.push_back(historyArray_);
	}
    Storage() {};

	void setArray(std::vector<Task> arr) { array = arr; }
	void setHistArray(std::vector<Task> hisArr) { historyArray = hisArr; }
	
    bool updateTaskList();

    void Save() {
        clearHForStart();
		std::ofstream out;
		out.open("historyInfo.txt", std::ios::app);
		for (auto& i : this->historyArray) {
			if (out.is_open()) 
			{
				if (i.getId() >= 0)
                out << i.getId() << std::endl << i.getName() << std::endl << i.getDescription() << std::endl << i.getSTime() << std::endl << i.getTimeForTask() << std::endl << i.getTotalTime() << std::endl << i.getStatus() << std::endl << i.getSWorkSec() << std::endl<< i.getFinTime() << std::endl << std::endl;
			}
        }
    }

    void SaveMain() {
        clearForStart();
        std::ofstream out;
        out.open("info.txt", std::ios::app);
        for (auto& i : this->array) {
            if (out.is_open())
            {
                if (i.getId() >= 0)
                out << i.getId() << std::endl << i.getName() << std::endl << i.getDescription() << std::endl << i.getSTime() << std::endl << i.getTimeForTask() << std::endl << i.getTotalTime() << std::endl << i.getStatus() << std::endl << i.getSWorkSec() << std::endl<< i.getFinTime() << std::endl << std::endl;
            }
        }
    }

	void getHisFromFile();
	void getFromFile();
	void clearForStart();
	void clearHForStart();
	void addTask(Task R);
	void delTask(long ID);
	void delHistoryTask();

    //get items for display
    std::vector<Task> *getTasks() { return &array; }
    std::vector<Task> getHTasks() { return historyArray; }
    void RemoveTask(Task task);
};
	



#endif

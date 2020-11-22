#include "Task.h"

#include <QDebug>

void Task::startWork() {
	time_t seconds;
	seconds = time(NULL);
	setSWorkSec(seconds);
	setStatus(1);
}


void Task::finishWork() {
	time_t seconds;
	seconds = time(NULL);
	setTotalTime(getTotalTime() + (seconds - getSWorkSec()));
	setStatus(0);
}


void Task::bell() {
#ifdef __linux__
// TODO
#elif _WIN32
	if ((getTimeForTask() - (getTimeForTask() / 10)) < getTotalTime())
		Beep(500, 500);
#else
#endif
}


void Storage::addTask(Task R) {
	this->array.push_back(R);
}


void Storage::delTask(long ID) {
	for (std::vector<Task>::iterator i = this->array.begin(); i != this->array.end(); i++)
	{
		if ((*i).getId() == ID) {
			
			long Idd = (*i).getId();
			
			std::string name = (*i).getName();

			std::string description = (*i).getDescription();

			long stime = (*i).getSTime();

			long tfortask = (*i).getTimeForTask();

			long totaltime = (*i).getTotalTime();

			int status = (*i).getStatus();

            long  finTime = (*i).getFinTime();
            if (finTime == 0)
                finTime = time(NULL);

            Task historyObj(Idd, name, description, stime, tfortask, totaltime, status, finTime);

            time_t seconds = time(NULL);
             historyObj.setFinTime(seconds);

			this->historyArray.push_back(historyObj);
             this->array.erase(i);
            return;
		}
	}
}


void Storage::RemoveTask(Task task)
{
    for (std::vector<Task>::iterator i = this->array.begin(); i != this->array.end(); i++)
    {
        if ((*i).getId() == task.getId())
        {

            this->historyArray.push_back(task);       
            this->array.erase(i);
            break;
        }
    }
}


void Storage::getHisFromFile() {

    if (!histTasksLoaded)
    {
        std::ifstream in("historyInfo.txt");

        if (in.is_open())
        {
            char tmp[256];
            long Id;
            std::string name;
            std::string description;
            long stime;
            long tfortask;
            long totaltime;
            int status;
            long sWorkSec;
            long finTime;
            std::string endline;

            while(!in.eof())
            {
                in >> Id;
                in.getline(tmp, 256);   // dummy
                in.getline(tmp, 256);
                name = (std::string)tmp;
                in.getline(tmp, 256);
                description = (std::string)tmp;
                in >> stime;
                in >> tfortask;
                in >> totaltime;
                in >> status;
                in >> sWorkSec;
                in >> finTime;
                in.getline(tmp, 256);   // dummy: empty line between 2 tasks

                if (name.empty() || description.empty())
                    continue;
                Task historyObj(Id, name, description, stime, tfortask, totaltime, status, finTime);
                this->historyArray.push_back(historyObj);

                if (!in.peek())
                    break;
            }
        }
        histTasksLoaded = true;
    }
}


void Storage::getFromFile() {

    if (!openTasksLoaded)
    {
        std::ifstream in("info.txt");

        if (in.is_open())
        {
            char tmp[256];
            long Id;
            std::string name;
            std::string description;
            long stime;
            long tfortask;
            long totaltime;
            int status;
            long sWorkSec;
            long finTime;
            std::string endline;

            while(!in.eof())
            {
                in >> Id;
                in.getline(tmp, 256);   // dummy
                in.getline(tmp, 256);
                name = (std::string)tmp;
                in.getline(tmp, 256);
                description = (std::string)tmp;
                in >> stime;
                in >> tfortask;
                in >> totaltime;
                in >> status;
                in >> sWorkSec;
                in >> finTime;
                in.getline(tmp, 256);   // dummy: empty line between 2 tasks

                if (name.empty() || description.empty())
                    continue;
                Task historyObj(Id, name, description, stime, tfortask, totaltime, status, finTime);
                this->array.push_back(historyObj);

                if (!in.peek())
                    break;
            }
        }
        openTasksLoaded = true;
    }
}

bool Storage::updateTaskList() {
    bool ret = false;
    std::vector<int> IdToRemove;
    for (std::vector<Task>::iterator i = this->array.begin(); i != this->array.end(); i++)
    {
        if ((*i).timeExpired())
        {
            qDebug() << "moved";
            IdToRemove.push_back((*i).getId());
            ret = true;
        }
    }

    for (size_t i = 0; i < IdToRemove.size(); i++)
        delTask(IdToRemove[i]);

    return ret;
}

void Storage::delHistoryTask() {
	this->historyArray.clear();
	std::ofstream rrewrite("historyInfo.txt");
	rrewrite.write("", 0);
	rrewrite.close();
}


void saveH(Storage historyList) {
	
    historyList.Save();
};


void Storage :: clearForStart() {
	
	std::ofstream rewrite("info.txt");
	rewrite.write("", 0);
	rewrite.close();
}


void Storage::clearHForStart() {
	std::ofstream rewritee("historyInfo.txt");
	rewritee.write("", 0);
	rewritee.close();
}


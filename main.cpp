#include <iostream>
#include <string>
using namespace std;

// class customer
class Customer
{
private:
    int customerID;
    string customerName;
    string homeAddress;
    string customerPhoneNumber;

public:
    static int noOfCustomers;
    Customer()
    {
        noOfCustomers++;
        customerID = 10000 + noOfCustomers;
    }
    void setInfo()
    {
        cout << "Enter your name: ";
        getline(cin, customerName);
        cout << "Enter your home address: ";
        getline(cin, homeAddress);
        cout << "Enter your phone number: ";
        cin >> customerPhoneNumber;
    }
    void displayInfo()
    {
        cout << "Here are customer details: " << endl
             << "ID: " << customerID << endl
             << "Name: " << customerName << endl
             << "Home address: " << homeAddress << endl
             << "Phone number: " << customerPhoneNumber << endl;
    }
};

// class technician
class Technician
{
private:
    int technicianID;
    string technicianName;
    // string technicianPhoneNumber;
    bool workingDays[7];

public:

string technicianPhoneNumber;

    static int noOfTechnicians;
    Technician()
    {
        noOfTechnicians++;
        technicianID = 1000 + noOfTechnicians;
    }
    void setInfo()
    {
        cout << "Enter your name: ";
        getline(cin, technicianName);
        cout << "Enter your phone number: ";
        cin >> technicianPhoneNumber;
    }
    void updateWorkingDays()
    {
        int input;
        string daysOfWeek[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

        cout << "Which days do you prefer to work on?" << endl
             << "Enter 1 for yes, 2 for no" << endl;

        for (int i = 0; i < 7; i++)
        {
            startOfLoop:
            cout << "Do you work on " << daysOfWeek[i] << ": ";
            cin >> input;
            if (input == 1)
            {
                workingDays[i] = true;
            }
            else if (input == 2)
            {
                workingDays[i] = false;
            }
            else
            {
                cout << "Wrong input" << endl;
                goto startOfLoop;
            }
        }
    }
    void displayInfo()
    {
        cout << "Here are technician details: " << endl
             << "ID: " << technicianID << endl
             << "Name: " << technicianName << endl
             << "Phone number: " << technicianPhoneNumber << endl;
    }
};

// class task
class Task
{
private:
    int taskID;
    string taskName;
    string taskDescription;
    double taskAmount;

public:
    static int noOfTasks;
    Task()
    {
        noOfTasks++;
        taskID = 100 + noOfTasks;
    }
    void setTask()
    {
        cout << "Enter task name: ";
        getline(cin, taskName);
        cout << "Enter task description: ";
        getline(cin, taskDescription);
        cout << "Enter task amount: ";
        cin >> taskAmount;
    }
    void displayInfo()
    {
        cout << "Here are task details: " << endl
             << "ID: " << taskID << endl
             << "Name: " << taskName << endl
             << "Description: " << taskDescription << endl
             << "Amount: " << taskAmount << endl;
    }
};

// class job
class Job
{
private:
    int jobID;
    string jobStatus;
    Customer customer;
    Technician technician;
    Task task;

public:
};

// class manager
class Manager
{
private:
public:
};

// functions
void validatePhoneNumber(string phoneNumber)
{
    if (phoneNumber.length() != 10)
    {
        cout << "Phone number must be 10 digits long" << endl;
    }
    for (char ch : phoneNumber)
    {
        if (!(ch >= 48 && ch <= 57))
        {
            cout << "Each character must be a digit" << endl;
        }
    }
}

// initialising static members
int Customer::noOfCustomers = 0;
int Technician::noOfTechnicians = 0;
int Task::noOfTasks = 0;

// main function
int main()
{
    

    return 0;
}
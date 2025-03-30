/*
    TODO
    1. menu driven
    2. schedule job
    3. add/remove constructors for testing
    4. show task details on booking
    5. modify access specifier according to need
    6. add spacing/decoration during I/O
    7. add option to view booked task in customer view
*/

// cin.ignore

/*
    SIMPLIFY:
    1. validate phoneno functionality within customer getInfo()
    2. remove technician view
    3. only one customer
    4.
*/

#include <iostream>
#include <string>
using namespace std;

// global variables
const string daysOfWeek[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

// function prototyping & definition
// function to validate phone number
bool validatePhoneNumber(string phoneNumber)
{
    bool isValid = true;
    if (phoneNumber.length() != 10)
    {
        isValid = false;
        cout << "Phone number must be 10 digits long" << endl;
    }
    for (int i = 0; i < phoneNumber.length(); i++)
    {
        char ch = phoneNumber[i];
        if (!(ch >= 48 && ch <= 57))
        {
            isValid = false;
            cout << "Each character must be a digit" << endl;
        }
    }
    return isValid;
}

// class task
class Task
{
private:
    string taskName;
    string taskDescription;
    double taskAmount;

public:
    int taskID;
    static int noOfTasks;
    Task(string taskName, string taskDescription, double taskAmount)
    {
        noOfTasks++;
        taskID = 100 + noOfTasks;
        Task::taskName = taskName;
        Task::taskDescription = taskDescription;
        Task::taskAmount = taskAmount;
    }

    void setTask()
    {
        cin.ignore();
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

// class technician
class Technician
{
private:
    string technicianName;
    string technicianPhoneNumber;

public:
    int technicianID;
    bool workingDays[7];
    static int noOfTechnicians;
    Technician(string technicianName, string technicianPhoneNumber)
    {
        noOfTechnicians++;
        technicianID = 1000 + noOfTechnicians;
        Technician::technicianName = technicianName;
        Technician::technicianPhoneNumber = technicianPhoneNumber;
    }

    // void setInfo()
    // {
    //     cout << "Enter your name: ";
    //     getline(cin, technicianName);
    //     // validating phone number input
    //     do
    //     {
    //         cout << "Enter your phone number: ";
    //         cin >> technicianPhoneNumber;

    //     } while (!validatePhoneNumber(technicianPhoneNumber));
    // }
    // void updateWorkingDays()
    // {
    //     int input;

    //     cout << "-----------------------" << endl;
    //     cout << "Hello " << technicianName << endl
    //          << "Which days do you prefer to work on?" << endl;

    //     for (int i = 0; i < 7; i++)
    //     {
    //         do
    //         {
    //             cout << "Do you work on " << daysOfWeek[i] << "[1 = yes, 2 = no]: ";
    //             cin >> input;
    //             if (input == 1)
    //             {
    //                 workingDays[i] = true;
    //             }
    //             else if (input == 2)
    //             {
    //                 workingDays[i] = false;
    //             }
    //             else
    //             {
    //                 cout << "Wrong input" << endl;
    //             }
    //         } while (input != 1 && input != 2);
    //     }
    // }
    void displayInfo()
    {
        cout << "Here are technician details: " << endl
             << "ID: " << technicianID << endl
             << "Name: " << technicianName << endl
             << "Phone number: " << technicianPhoneNumber << endl;
    }
};

// class customer
class Customer
{
private:
    string customerName;
    string homeAddress;
    string customerPhoneNumber;

public:
    int customerID;
    int bookedTaskID;
    int bookedDay;
    int bookedTechnicianID;
    static int noOfCustomers;
    Customer()
    {
        noOfCustomers++;
        customerID = 10000 + noOfCustomers;
    }

    // // for testing
    // Customer(string name, string address, string phoneno)
    // {
    //     noOfCustomers++;
    //     customerID = 10000 + noOfCustomers;
    //     customerName = name;
    //     customerPhoneNumber = phoneno;
    //     homeAddress = address;
    // }

    void setInfo()
    {
        cin.ignore();
        cout << "Enter your name: ";
        getline(cin, customerName);
        cout << "Enter your home address: ";
        getline(cin, homeAddress);

        // validating phone number input
        do
        {
            cout << "Enter your phone number: ";
            cin >> customerPhoneNumber;

        } while (!validatePhoneNumber(customerPhoneNumber));
    }
    void displayInfo()
    {
        cout << "Here are customer details: " << endl
             << "ID: " << customerID << endl
             << "Name: " << customerName << endl
             << "Home address: " << homeAddress << endl
             << "Phone number: " << customerPhoneNumber << endl;
    }
    void bookDay(Technician techncians[])
    {
        int userDayInput;
        bool technicianAvailable = false;

        do
        {
            // asking for day of task
            do
            {
                cout << endl
                     << "-----------------------" << endl;
                cout << "Which day do you want to book?" << endl;

                // displaying days
                for (int i = 0; i < 7; i++)
                {
                    cout << i << ". " << daysOfWeek[i] << endl;
                }

                // getting input
                cin >> userDayInput;

                // validating input
                if (!(userDayInput >= 0 && userDayInput <= 6))
                {
                    cout << "Invalid input. Enter a number between 0 and 6" << endl;
                }
            } while (!(userDayInput >= 0 && userDayInput <= 6));

            bookedDay = userDayInput;

            // checking for available technician
            for (int i = 0; i < Technician::noOfTechnicians; i++)
            {
                if (techncians[i].workingDays[userDayInput])
                {
                    technicianAvailable = true;
                    bookedTechnicianID = techncians[i].technicianID;
                    cout << "Technician available. " << daysOfWeek[userDayInput] << " booked" << endl;
                    break;
                }
            }

            // if technician not available on that day
            if (!technicianAvailable)
            {
                cout << "Sorry no technician available on " << daysOfWeek[userDayInput] << endl
                     << "Please try again" << endl;
            }
        } while (!technicianAvailable);
    }

    void bookTask(Task tasks[])
    {
        int userTaskInput;
        bool taskFound = false;

        cout << endl
             << "-----------------------" << endl;
        do
        {
            // displaying all tasks to customer
            for (int i = 0; i < Task::noOfTasks; i++)
            {
                tasks[i].displayInfo();
                cout << "-----------------------" << endl;
            }

            // asking customer to choose task
            cout << "Which task do you want?" << endl
                 << "Enter task ID: ";
            cin >> userTaskInput;

            // checking for entered task
            for (int i = 0; i < Task::noOfTasks; i++)
            {
                if (tasks[i].taskID == userTaskInput)
                {
                    taskFound = true;
                    bookedTaskID = tasks[i].taskID;
                }
            }
            if (!taskFound)
            {
                cout << "Task not found" << endl;
            }
        } while (!taskFound);
    }
};

// class job
// class Job
// {
// private:
//     int jobID;
//     string jobStatus;
//     // Customer customer;
//     // Technician technician;
//     // Task task;
// public:
//     static int noOfJobs;
//     Job()
//     {
//         noOfJobs++;
//         jobID = 1100 + noOfJobs;
//     }
// };

// class manager
// class Manager
// {
// private:
// public:
// };

// initialising static members
// int Customer::noOfCustomers = 0;
int Technician::noOfTechnicians = 0;
int Task::noOfTasks = 0;

// main function
int main()
{
    int choice;
    Customer customer;

    // predefined tasks
    Task t1("Plumbing", "Fixing leaking pipes and taps", 1500.00);
    Task t2("Electrical Wiring", "Repair and installation of electrical wiring", 3000.00);
    Task t3("Carpentry", "Furniture repair and woodwork", 2500.00);
    Task t4("Painting", "Wall painting and touch-ups", 5000.00);
    Task t5("Roof Repair", "Fixing roof leaks and damages", 7000.00);
    Task t6("Flooring", "Tile and marble installation and repair", 8000.00);
    Task t7("Pest Control", "Termite and insect treatment", 3500.00);
    Task t8("Appliance Repair", "Fixing home appliances like refrigerators and washing machines", 4000.00);

    Task tasks[] = {t1, t2, t3, t4, t5, t6, t7, t8};

    // predefined technicians
    Technician tech1("Amit Kumar", "9876543210");
    Technician tech2("Ravi Sharma", "9123456789");

    // assigning working days for tech1
    bool tech1Days[] = {true, true, true, true, false, false, false}; // Works Monday-Thursday
    for (int i = 0; i < 7; i++)
    {
        tech1.workingDays[i] = tech1Days[i];
    }

    // assigning working days for tech2
    bool tech2Days[] = {false, true, true, true, true, true, false}; // Works Tuesday-Saturday
    for (int i = 0; i < 7; i++)
    {
        tech2.workingDays[i] = tech2Days[i];
    }

    Technician technicians[] = {tech1, tech2};

    // menu-driven system for user interaction
    do
    {
        cout << endl
             << "-----------------------" << endl
             << "*** Welcome to HomeCare Scheduling System ***" << endl
             << "Welcome. How can we help you?" << endl
             << "Choices:\n1. Set Details\n2. View Details\n3. Book Task\n4. Book day of task\n5. Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            customer.setInfo();
            break;

        case 2:
            customer.displayInfo();
            break;

        case 3:
            customer.bookTask(tasks);
            break;

        case 4:
            customer.bookDay(technicians);
            break;

        case 5:
            cout << "Thank you for using HomeCare Scheduling System" << endl
                 << "Exiting program" << endl
                 << "-----------------------" << endl;
            break;

        default:
            cout << "Invalid input. Enter a number between 1 to 5" << endl;
            break;
        }
    } while (choice != 5);

    return 0;
}
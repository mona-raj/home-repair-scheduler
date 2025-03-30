// Home Care: Smart Scheduling System for Home Repair and Maintenance

#include <iostream>
#include <string> // we include this to access length() property of strings
using namespace std;

// global variable
const string daysOfWeek[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

// defining core classes and their attributes
class Task
{
private:
    string taskName;
    string taskDescription;
    double taskAmount;

public:
    int taskID;
    static int noOfTasks;
    Task(string taskName, string taskDescription, double taskAmount) // implementing constructor and assigning a unique task ID
    {
        noOfTasks++;
        taskID = 100 + noOfTasks;
        Task::taskName = taskName; // use scope resolution operator to access members of class
        Task::taskDescription = taskDescription;
        Task::taskAmount = taskAmount;
    }
    void displayInfo()
    {
        cout << "-----------------------" << endl
             << "Here are task details: " << endl
             << "Task ID: " << taskID << endl
             << "Task Name: " << taskName << endl
             << "Task Description: " << taskDescription << endl
             << "Amount: " << taskAmount << endl;
    }
};

class Technician
{
private:
    string technicianName;
    string technicianPhoneNumber;
    bool workingDays[7];

public:
    int technicianID;
    static int noOfTechnicians;
    Technician(string technicianName, string technicianPhoneNumber) // implementing constructor and assigning a unique technician ID
    {
        noOfTechnicians++;
        technicianID = 1000 + noOfTechnicians;
        Technician::technicianName = technicianName;
        Technician::technicianPhoneNumber = technicianPhoneNumber;
    }
    void displayInfo()
    {
        cout << "-----------------------" << endl
             << "Here are technician details: " << endl
             << "Technician ID: " << technicianID << endl
             << "Technician Name: " << technicianName << endl
             << "Technician Phone number: " << technicianPhoneNumber << endl;
    }
    void setWorkingDays(bool days[]) // sets the working days of technician based on given boolean array
    {
        for (int i = 0; i < 7; i++)
        {
            workingDays[i] = days[i];
        }
    }
    bool isAvailableOn(int day) // returns true if technician is available on given day else false
    {
        return workingDays[day];
    }
};

class Customer
{
private:
    int customerID;
    string customerName;
    string customerAddress;
    string customerPhoneNumber;

public:
    int bookedTaskID;
    int bookedDay;
    int bookedTechnicianID;
    static int noOfCustomers;
    Customer() // implementing constructor and assigning a unique customer ID
    {
        noOfCustomers++;
        customerID = 10000 + noOfCustomers;
    }
    void setInfo()
    {
        cin.ignore();
        cout << "Enter your name: ";
        getline(cin, customerName);
        cout << "Enter your home address: ";
        getline(cin, customerAddress);

        // validating phone number input
        bool isValid;
        do
        {
            cout << "Enter your phone number: ";
            cin >> customerPhoneNumber;
            isValid = true;

            // checking for 10 character
            if (customerPhoneNumber.length() != 10)
            {
                isValid = false;
            }

            // checking that each character is a digit
            for (int i = 0; i < customerPhoneNumber.length(); i++)
            {
                char ch = customerPhoneNumber[i];
                if (!(ch >= 48 && ch <= 57)) // comparing agains ASCII values of 0-9
                {
                    isValid = false;
                    break;
                }
            }
            if (!isValid)
            {
                cout << "Phone number must be 10 digits long" << endl; // displaying error message
            }
        } while (!isValid);
    }
    void displayInfo()
    {
        cout << "-----------------------" << endl
             << "Here are customer details: " << endl
             << "Customer ID: " << customerID << endl
             << "Customer Name: " << customerName << endl
             << "Customer Address: " << customerAddress << endl
             << "Customer Phone number: " << customerPhoneNumber << endl;
    }

    void bookTask(Task tasks[]) // allows customer to choose a task from available options
    {
        bool taskFound = false;

        // displaying all tasks to customer
        for (int i = 0; i < Task::noOfTasks; i++)
        {
            tasks[i].displayInfo();
        }
        do // this loop executes until user enters correct taskID
        {
            // asking customer to choose task
            cout << "-----------------------" << endl
                 << "Which task do you want?" << endl
                 << "Enter task ID: ";
            cin >> bookedTaskID;

            // checking if entered bookedTaskID matches any taskID
            for (int i = 0; i < Task::noOfTasks; i++)
            {
                if (tasks[i].taskID == bookedTaskID)
                {
                    taskFound = true;
                }
            }
            if (!taskFound)
            {
                cout << "Task not found. Enter correct task ID" << endl; // displaying error message
            }
        } while (!taskFound);
    }

    void bookDay(Technician techncians[]) // allows customer to book a task on an available day with a technician
    {
        bool technicianAvailable = false;
        do // outer loop executes till technician is not available on booked day
        {
            do // inner loop executes until user enters correct day of week
            {
                cout << endl
                     << "-----------------------" << endl;
                cout << "Which day do you want to book?" << endl;

                // displaying days of week and getting input
                for (int i = 0; i < 7; i++)
                {
                    cout << i << ". " << daysOfWeek[i] << endl;
                }
                cin >> bookedDay;

                if (!(bookedDay >= 0 && bookedDay <= 6))
                {
                    cout << "Invalid input. Enter a number between 0 and 6" << endl;
                }
            } while (!(bookedDay >= 0 && bookedDay <= 6));

            // checking if any technician works on booked day
            for (int i = 0; i < Technician::noOfTechnicians; i++)
            {
                if (techncians[i].isAvailableOn(bookedDay))
                {
                    technicianAvailable = true;
                    bookedTechnicianID = techncians[i].technicianID;
                    cout << "Technician available. " << daysOfWeek[bookedDay] << " booked" << endl;
                    break;
                }
            }
            if (!technicianAvailable)
            {
                cout << "Sorry no technician available on " << daysOfWeek[bookedDay] << endl
                     << "Please try again" << endl; // displaying error message
            }
        } while (!technicianAvailable);
    }

    void displayBookingDetails(Task tasks[], Technician technicians[]) // displays details of booked task and assigned technician
    {
        // displaying booked task details
        bool taskFound;
        for (int i = 0; i < Task::noOfTasks; i++)
        {
            taskFound = false;
            if (tasks[i].taskID == bookedTaskID)
            {
                taskFound = true;
                tasks[i].displayInfo();
                break;
            }
        }
        if (!taskFound)
        {
            cout << "Task details not found" << endl;
        }

        // displaying assigned technician details and booked day
        bool technicianFound;
        for (int i = 0; i < Technician::noOfTechnicians; i++)
        {
            technicianFound = false;
            if (technicians[i].technicianID == bookedTechnicianID)
            {
                technicianFound = true;
                technicians[i].displayInfo();
                cout << "Day booked: " << daysOfWeek[bookedDay] << endl;
                break;
            }
        }
        if (!technicianFound)
        {
            cout << "Technician details not found" << endl;
        }
    }
};

// initialising static data members of class
int Customer::noOfCustomers = 0;
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
    Task t5("Flooring", "Tile and marble installation and repair", 8000.00);

    // creating an array of Task objects
    Task tasks[] = {t1, t2, t3, t4, t5};

    // predefined technicians
    Technician tech1("Amit Kumar", "9876543210");
    Technician tech2("Ravi Sharma", "9123456789");

    // assigning working days for each technician
    bool tech1Days[] = {true, true, true, true, false, false, false}; // Works Monday-Thursday
    tech1.setWorkingDays(tech1Days);

    bool tech2Days[] = {false, true, true, true, true, true, false}; // Works Tuesday-Saturday
    tech2.setWorkingDays(tech2Days);

    // creating an array of Technician objects
    Technician technicians[] = {tech1, tech2};

    // menu-driven system for user interaction
    do
    {
        cout << endl
             << "-----------------------" << endl
             << "*** Welcome to Home Care Scheduler ***" << endl
             << "How can we help you?" << endl
             << "Choices:\n1. Set Customer Details\n2. View Customer Details\n3. Book Task\n4. Book day of task\n5. View booking details\n6. Exit" << endl;
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
            customer.displayBookingDetails(tasks, technicians);
            break;
        case 6:
            cout << "Thank you for using Home Care Scheduler" << endl
                 << "Exiting program" << endl
                 << "-----------------------" << endl;
            break;
        default:
            cout << "Invalid input. Enter a number between 1 to 6" << endl;
            break;
        }
    } while (choice != 6);

    return 0;
}
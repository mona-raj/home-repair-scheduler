// Home Care: Smart Scheduling System for Home Repair and Maintenance

#include <iostream>
#include <fstream> // we include this to read and write file
#include <string>  // we include this to access length() property of strings
using namespace std;

// global variables
const string daysOfWeek[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
const string filePath = "file.txt";

// defining core classes and their attributes
class Task
{
private:
    string taskName;
    string taskDescription;

public:
    double taskAmount;
    int taskID;
    static int noOfTasks;

    Task(string name, string description, double amount) // implementing constructor and assigning a unique task ID
    {
        noOfTasks++;
        taskID = 100 + noOfTasks;
        taskName = name;
        taskDescription = description;
        taskAmount = amount;
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

class User
{
protected:
    string name;
    string phoneNumber;

public:
    void displayInfo()
    {
        cout << "Name: " << name << endl
             << "Phone number: " << phoneNumber << endl;
    }
};

class Technician : public User
{
private:
    bool workingDays[7];

public:
    int technicianID;
    static int noOfTechnicians;

    Technician(string technicianName, string technicianPhoneNumber) // implementing constructor and assigning a unique technician ID
    {
        noOfTechnicians++;
        technicianID = 1000 + noOfTechnicians;
        name = technicianName;
        phoneNumber = technicianPhoneNumber;
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

class Customer : public User
{
protected:
    int customerID;
    string address;

public:
    int bookedTechnicianID;
    int bookedTaskID;
    int bookedDay;

    void setInfo()
    {
        cin.ignore(); // used to clear input buffer
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your address: ";
        getline(cin, address);

        // validating phone number input
        bool isValid;
        do
        {
            cout << "Enter your phone number: ";
            cin >> phoneNumber;
            isValid = true;
            if (phoneNumber.length() != 10) // checking for 10 characters
            {
                isValid = false;
            }            
            for (int i = 0; i < phoneNumber.length(); i++)
            {
                char ch = phoneNumber[i];
                if (!(ch >= 48 && ch <= 57)) // checking that each character is a digit
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

    void displayCustomerInfo()
    {
        displayInfo();
        cout << "Address: " << address << endl;
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
            cout << "-----------------------" << endl
                 << "Which task do you want?" << endl
                 << "Enter task ID: ";
            cin >> bookedTaskID;

            // checking if bookedTaskID matches any taskID
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
                for (int i = 0; i < 7; i++)
                {
                    cout << i << ". " << daysOfWeek[i] << endl; // displaying days of week
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
                cout << "-----------------------" << endl
                     << "Here are technician details:" << endl;
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

    friend void writeFile(string filePath, Customer customer);
};

class PremiumCustomer : public Customer
{
private:
    double discountedAmount;

public:
    int countOfBookings;
    int *bookedTechnicianIDList;
    int *bookedTaskIDList;
    int *bookedDaysList;

    PremiumCustomer(int count = 3) // dynamic constructor with default argument
    {
        countOfBookings = count;
        bookedTechnicianIDList = new int[countOfBookings];
        bookedTaskIDList = new int[countOfBookings];
        bookedDaysList = new int[countOfBookings];
    }

    void premiumDiscount(Task tasks[], int id)
    {
        for (int i = 0; i < Task::noOfTasks; i++)
        {
            if (tasks[i].taskID == id)
            {
                discountedAmount = tasks[i].taskAmount * 0.9;
            }
        }
        cout << "-----------------------" << endl
             << "Premium benefit amount: " << discountedAmount << endl;
    }

    ~PremiumCustomer() // destructor
    {
        delete[] bookedTechnicianIDList;
        delete[] bookedTaskIDList;
        delete[] bookedDaysList;
    }

    friend void writeFile(string filePath, PremiumCustomer premium);
};

// initialising static data members of class
int Technician::noOfTechnicians = 0;
int Task::noOfTasks = 0;

// functions to write data in file
void writeFile(string filePath, Customer customer)
{
    ofstream writer(filePath);
    if (!writer)
    {
        cout << "File not found" << endl;
    }
    writer << "**Customer Details**" << endl
           << "Name: " << customer.name << endl
           << "Phone number: " << customer.phoneNumber << endl
           << "Address: " << customer.address << endl
           << "**Booking Details**" << endl
           << "Technician ID: " << customer.bookedTechnicianID << endl
           << "Task ID: " << customer.bookedTaskID << endl
           << "Booked day: " << daysOfWeek[customer.bookedDay] << endl;
    writer.close();
}

void writeFile(string filePath, PremiumCustomer premium) // function overloading with different data type
{
    ofstream writer(filePath);
    if (!writer)
    {
        cout << "File not found" << endl;
    }
    writer << "**Customer Details**" << endl
           << "Name: " << premium.name << endl
           << "Phone number: " << premium.phoneNumber << endl
           << "Address: " << premium.address << endl
           << "**Booking Details**" << endl;
    for (int i = 0; i < premium.countOfBookings; i++)
    {
        writer << "Booking " << (i + 1) << endl
               << "Technician ID: " << premium.bookedTechnicianIDList[i] << endl
               << "Task ID: " << premium.bookedTaskIDList[i] << endl
               << "Booked day: " << daysOfWeek[premium.bookedDaysList[i]] << endl;
    }
    writer.close();
}

// function to read data stored in file
void readFile(string filePath)
{
    ifstream reader(filePath);
    if (!reader)
    {
        cout << "File not found" << endl;
    }
    string line;
    while (!reader.eof())
    {
        getline(reader, line);
        cout << line << endl;
    }
    reader.close();
}

// main function
int main()
{
    int firstChoice, secondChoice;

    Task t1("Plumbing", "Fixing leaking pipes and taps", 1500.00);
    Task t2("Electrical Wiring", "Repair and installation of electrical wiring", 3000.00);
    Task t3("Carpentry", "Furniture repair and woodwork", 2500.00);
    Task t4("Painting", "Wall painting and touch-ups", 5000.00);
    Task t5("Flooring", "Tile and marble installation and repair", 8000.00);
    Task tasks[] = {t1, t2, t3, t4, t5}; // creating an array of Task objects

    Technician tech1("Amit Kumar", "9876543210");
    Technician tech2("Ravi Sharma", "9123456789");
    bool tech1Days[] = {true, true, true, true, false, false, false}; // Works Monday-Thursday
    tech1.setWorkingDays(tech1Days);
    bool tech2Days[] = {false, true, true, true, true, true, false}; // Works Tuesday-Saturday
    tech2.setWorkingDays(tech2Days);
    Technician technicians[] = {tech1, tech2}; // creating an array of Technician objects

    Customer customer;
    PremiumCustomer premium(2);

    // menu-driven system for user interaction
    do
    {
        cout << endl
             << "-----------------------" << endl
             << "*** Welcome to Home Care Scheduler ***" << endl
             << "Identify yourself" << endl
             << "Choices:\n1. Regular Customer\n2. Premium Customer\n3. Admin\n4. Exit" << endl;
        cin >> firstChoice;

        switch (firstChoice)
        {
        case 1:
            // regular customer view
            do
            {
                cout << endl
                     << "-----------------------" << endl
                     << "How can we help you?" << endl
                     << "Choices:\n1. Set Customer Details\n2. View Customer Details\n3. Book Task\n4. Book day of task\n5. View booking details\n6. Exit" << endl;
                cin >> secondChoice;
                switch (secondChoice)
                {
                case 1:
                    customer.setInfo();
                    break;
                case 2:
                    customer.displayCustomerInfo();
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
                    writeFile(filePath, customer); // storing data in file before exiting
                    cout << "Exiting" << endl
                         << "-----------------------" << endl;
                    break;
                default:
                    cout << "Invalid input. Enter a number between 1 to 6" << endl;
                    break;
                }
            } while (secondChoice != 6);
            break;

        case 2:
            // premium customer view
            do
            {
                cout << endl
                     << "-----------------------" << endl
                     << "How can we help you?" << endl
                     << "Choices:\n1. Set Customer Details\n2. View Customer Details\n3. Book Task\n4. Exit" << endl;
                cin >> secondChoice;
                switch (secondChoice)
                {
                case 1:
                    premium.setInfo();
                    break;
                case 2:
                    premium.displayCustomerInfo();
                    break;
                case 3:
                    for (int i = 0; i < premium.countOfBookings; i++)
                    {
                        premium.bookDay(technicians);
                        premium.bookTask(tasks);
                        premium.premiumDiscount(tasks, premium.bookedTaskID);
                        premium.bookedTechnicianIDList[i] = premium.bookedTechnicianID;
                        premium.bookedTaskIDList[i] = premium.bookedTaskID;
                        premium.bookedDaysList[i] = premium.bookedDay;
                    }
                    break;
                case 4:
                    writeFile(filePath, premium); // storing data in file before exiting
                    cout << "Exiting" << endl
                         << "-----------------------" << endl;
                    break;
                default:
                    cout << "Invalid input. Enter a number between 1 to 4" << endl;
                    break;
                }
            } while (secondChoice != 4);
            break;

        case 3:
            // admin view
            cout << "Here are all the booking details:" << endl;
            readFile(filePath);
            break;

        case 4:
            cout << "Exiting program" << endl
                 << "-----------------------" << endl;
            break;

        default:
            cout << "Invalid input. Enter a number between 1 to 4" << endl;
            break;
        }
    } while (firstChoice != 4);
    return 0;
}
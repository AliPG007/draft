#include <iostream>
#include <string>
#include <vector>
using namespace std;
// Struct: allows you to group together different data types into a single unit. (By default, all members are public.)
// Initializing struct
struct User {
    string name;
    int id;
};
// using struct method in employee class
class employee : public User
{
    friend class worker;
    //friend ostream& operator << (ostream&, employee&);

public:
    employee();
    void input(const string& name, const string& id);
    //void show();
protected:
    string Name;
    string idNum;
};

employee::employee()
{
    Name = "NULL";
    idNum = "NULL";
}

void employee::input(const string& name, const string& id)
{
    //Name = name;
    //idNum = id;
    this->Name = name;
    this->idNum = id;
}

// << overload
/*ostream& operator << (ostream& out, employee& obj)
{
    out << "================================" << endl;
    out << "Employee Name: " << obj.Name << endl;
    out << "Employee ID: " << obj.idNum << endl;
    return out;
}*/

// input
/*void employee::show()
{
    cout << "================================" << endl;
    cout << "Employee Name: " << Name << endl;
    cout << "Employee ID: " << idNum << endl;
}*/

////////////////////////////////////////////////////////////////////////////////////////////////////////

class worker : public employee
{
    friend ostream& operator << (ostream&, const worker&);
public:
    worker();
    void input(const string& name, const string& id);
    void Salary(bool, int);
    
private:
    int entrance_hr, entrance_min;
    int exit_hr, exit_min;
    int totalWorkTime;
    const int paymentRatio = 2;
    float payment;
    int absence;
};

worker::worker()
{
    entrance_hr = 0;
    entrance_min = 0;
    exit_hr = 0;
    exit_min = 0;
    totalWorkTime = 0;
    payment = 0;
    absence = 0;
}

void worker::input(const string& name, const string& id)
{
    // geting the name and ID
    employee::input(name, id);

    // getting arrival time
    bool timeFormat = false;
    while (!timeFormat)
    {
        try
        {
            cout << "\nEnter your arrival time (hour:min): \n";
            cin >> entrance_hr >> entrance_min;
            
            if (!entrance_hr)
            {
                absence++;
                worker::Salary(0, 0);
                return;
            }
            else if ((entrance_hr >= 6 && entrance_hr <= 17) && (entrance_min >= 0 && entrance_min <= 59))
            {
                if (entrance_hr > 6) cout << "You're Late..";
                timeFormat = 1;
            }
            else
            {
                timeFormat = 0;
                throw "InvalidTimeFormat";
                throw(&entrance_hr, &entrance_min);
            }
        }
        catch (...)
        {
            cout << "The time format is wrong. Please try again.\a\n";
            cin.clear(); // clear the error state flags that might be set on the cin stream
            cin.ignore(); // clear the input buffer of the cin stream
            
        }
    }
    // getting exit time
    timeFormat = false;
    while (!timeFormat)
    {
        try
        {
            cout << "\nEnter your exit time (hour:min): ";
            cin >> exit_hr >> exit_min;
            if ((exit_hr >= 6 && exit_hr <= 17) && (exit_min >= 0 && exit_min <= 59))
            {
                if (exit_hr < 17) cout << "You're Exiting Early..";
                    timeFormat = 1;
            }
            else
            {
                timeFormat = 0;
                throw "InvalidTimeFormat";
                throw(&exit_hr, &exit_min);
            }
        }
        catch (...)
        {
            cout << "The time format is wrong. Please try again.\n";
            cin.clear(); // clear the error state flags that might be set on the cin stream
            cin.ignore(); // clear the input buffer of the cin stream
        }
    }

    // weekend
    bool weekend;
    cout << "\nIs it weekend? (1 for Yes / 0 for No): ";
    cin >> weekend;

    // total work time
    if (exit_min > entrance_min)
        totalWorkTime = ((exit_hr - entrance_hr) * 60) + (exit_min - entrance_min);
    else
        totalWorkTime = ((exit_hr - entrance_hr) * 60) + (entrance_min - exit_min);

    worker::Salary(weekend, totalWorkTime);
}

void worker::Salary(bool weekend, int totalWorktime)
{
    if (totalWorkTime > 0)
    {
        if (!weekend)
            payment += totalWorkTime * paymentRatio;
        else
            payment += totalWorkTime * paymentRatio * 2;
    }
}

ostream& operator << (ostream& out, const worker& obj)
{
    out << "================================\n";
    out << "Employee's Name: " << obj.Name << endl;
    //out << "Employee's Name: " << user1.name << endl;

    
    out << "Employee ID: " << obj.idNum << endl;
    out << "Your payment for this month: " << obj.payment << " Toman" << endl;
    out << "Your absences: " << obj.absence << endl;
    out << "================================\n";
    return out;
}

// input
/*void worker::show()
{
    employee::show();
    cout << "Your payment for this month: " << payment << endl;
    cout << "your absences: " << absence << endl;
    cout << "================================" << endl;
}*/

////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    cout << "Enter the number of employees: ";
    int n;
    cin >> n;
    vector<worker> employees(n);
    
    for (int i = 0; i < 2; i++)
    {
        cout << "\n Day " << i + 1 << " :";
        for (int j = 0; j < n; j++)
        {
            cout << "\n ========== Employee no." << j + 1 << "========== \n";

            string name, id;
            cout << "Enter your full name: \n";
            cin.ignore();
            getline(cin, name);

            cout << "Enter your ID: \n";
            getline(cin, id);

            employees[j].input(name, id);
        }
    }
    for (int i = 0; i < n; i++)
        cout << employees[i];

    return 0;
}

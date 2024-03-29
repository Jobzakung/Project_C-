#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Date
{
    int d, m, y;
};

const int monthDays[12] = {31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};

void menu();
void pawn(string fn);
void display(string fn);
void search(string fn);
void del(const char *filename, int n);
void delinput();
int getDifference(Date dt1, Date dt2);
int countLeapYears(Date d);

int main()
{
    string password;
    string user;
    cout << "Enter Username : ";
    cin >> user;
    cout << "Enter Password : ";
    cin >> password;

    if (password == "admin")
    {
        if (user == "admin")
        {
            while (true)
            {
                menu();
            }
        }
        else
            cout << "Incorrect Input : ";
    }
    else
        cout << "Incorrect Input : ";
}

void menu()
{
    string Filename = "Receipt.txt";
    ofstream OutFile;
    ifstream InFile;
    int choice;
    std::cout << "##########################" << std::endl;
    std::cout << "#  Welcome to  Pawnshop  #" << std::endl;
    std::cout << "#   Please Select Menu   #" << std::endl;
    std::cout << "##########################" << std::endl;
    std::cout << "1. ReceiptPawn" << std::endl;
    std::cout << "2. Display" << std::endl;
    std::cout << "3. Search" << std::endl;
    std::cout << "4. Delete Line" << std::endl;
    std::cout << "5. exit Program" << std::endl;
    std::cout << "Please choice in range 1 - 5 : ";
    cin >> choice;

    if (choice == 1)
    {
        pawn(Filename);
    }
    if (choice == 2)
    {
        display(Filename);
    }
    if (choice == 3)
    {
        search(Filename);
    }
    if (choice == 4)
    {
        delinput();
    }
    if (choice == 5)
    {
        exit(0);
    }
    else
        cout << "Please seclect in range 1 - 5 !!";
}

void pawn(string fn)
{
    ofstream OutFile(fn.c_str(), ios_base::out | ios_base::app);

    if (OutFile.is_open())
    {
        string ID, Product, Price;

        int Day_Input, Month_Input, Year_Input;

        int Day_Expired, Month_Expired, Year_Expired;

        std::cout << "\n Add Object \n";
        std::cout << "Enter Id (ex:1xxx) : ";
        std::cin >> ID;
        std::cout << "Enter Prodect Name : ";
        std::cin >> Product;

        char slash_dummy = '/';
        double Interest;

        std::cout << "Enter Date (dd/mm/yyyy) : ";
        std::cin >> Day_Input;
        if (std::cin.get() != '/')
        {
            std::cout << "expected /\n";
        }
        std::cin >> Month_Input;
        if (std::cin.get() != '/')
        {
            std::cout << "expected /\n";
        }
        std::cin >> Year_Input;

        std::cout << "Enter Expired Date (dd/mm/yyyy) : ";
        std::cin >> Day_Expired;
        if (std::cin.get() != '/')
        {
            std::cout << "expected /\n";
        }
        std::cin >> Month_Expired;
        if (std::cin.get() != '/')
        {
            std::cout << "expected /\n";
        }
        std::cin >> Year_Expired;

        cout << "Enter your Price : ";
        cin >> Price;

        Date dt1 = {Day_Input, Month_Input, Year_Input};
        Date dt2 = {Day_Expired, Month_Expired, Year_Expired};

        double y = getDifference(dt1, dt2) / 365;
        double m = 0;
        double d = 0;

        if (y != 0)
        {
            m = (getDifference(dt1, dt2) % 365 / 30);
        }
        else
        {
            m = (getDifference(dt1, dt2) / 30);
        }
        if (m != 0)
        {
            d = (getDifference(dt1, dt2) % 365) % 30;
        }
        else
        {
            if (y != 0)
            {
                (d = getDifference(dt1, dt2) % 365);
            }
            else
            {
                d = getDifference(dt1, dt2);
            }
        }
        if (getDifference(dt1, dt2) >= 365)
        {
            Interest = stod(Price) * 0.03;
            Interest += stod(Price);
        }
        else if (getDifference(dt1, dt2) >= 28 || getDifference(dt1, dt2) >= 30 || getDifference(dt1, dt2) >= 31)
        {
            Interest = stod(Price) * 0.265;
            Interest += stod(Price);
        }
        else if (getDifference(dt1, dt2) <= 27)
        {
            Interest += stod(Price);
        }

        OutFile << ID << "\t" << Product << "\t" << Interest << "\t" << Day_Input << slash_dummy << Month_Input << slash_dummy << Year_Input << "\t" << Day_Expired << slash_dummy << Month_Expired << slash_dummy << Year_Expired << "\t" << std::endl;

        OutFile.close();
        char Wait;
        cin.get(Wait);
        cout << "\nPress Enter to continue";
        cin.get(Wait);
    }
}
void display(string fn)
{
    ifstream InFile(fn.c_str(), ios_base::in);
    if (InFile.is_open())
    {
        string ID, Product, interest, date, exdate;
        string ln(58, '=');
        string ln2(58, '-');
        int line = 1;

        InFile >> ID >> Product >> interest >> date >> exdate;
        cout << ln << endl;
        cout << "# "
             << " "
             << "ID"
             << "\t"
             << "Product"
             << "\t"
             << "Interest"
             << "\t"
             << "Date"
             << "\t\t"
             << "ExDate"
             << "   #" << endl;
        cout << ln << endl;
        while (!InFile.eof())
        {
            cout << line << " :" << ID << "\t" << Product << "\t" << interest << "\t\t" << date << "\t" << exdate << endl;
            cout << ln2 << endl;
            InFile >> ID >> Product >> interest >> date >> exdate;
            line++;
        }
        InFile.close();
        char Wait;
        cin.get(Wait);
        cout << "\nPress Enter to continue";
        cin.get(Wait);
    }
}

void search(string fn)
{
    ifstream InFile(fn.c_str(), ios_base::in);
    string find;
    cout << "Input ID to Search : ";
    cin >> find;
    if (InFile.is_open())
    {
        string ID, Product, interest, date, Expired_date;
        string ln(58, '=');
        string ln2(58, '-');
        int line = 1;

        cout << ln << endl;
        cout << "* "
             << " "
             << "ID "
             << "\t"
             << "Product"
             << "\t"
             << "Interest"
             << "\t"
             << "Date"
             << "\t\t"
             << "ExDate"
             << " *" << endl;
        cout << ln << endl;
        while (!InFile.eof())
        {
            InFile >> ID >> Product >> interest >> date >> Expired_date;
            if (find == ID)
            {
                cout << line << " :" << ID << "\t" << Product << "\t" << interest << "\t\t" << date << "\t" << Expired_date << endl;
                cout << ln2 << endl;
                InFile >> ID >> Product >> interest >> date >> Expired_date;
            }
        }
        InFile.close();
        char Wait;
        cin.get(Wait);
        cout << "\nPress Enter to continue";
        cin.get(Wait);
    }
}

void delinput()
{
    int line; // line numbers
    cout << "Which line do you want to remove :  ";
    cin >> line;
    del("Receipt.txt", line);
}

void del(const char *filename, int n)
{

    ifstream file(filename);
    ofstream temp;
    temp.open("temp.txt", ofstream::out);

    char c;
    int line = 1;
    while (file.get(c))
    {
        if (c == '\n')
            line++;
        if (line != n)
            temp << c;
    }
    file.close();
    temp.close();
    remove(filename);
    rename("temp.txt", filename);
}

int countLeapYears(Date d)
{
    int years = d.y;

    if (d.m <= 2)
        years--;
    return years / 4 - years / 100 + years / 400;
}

int getDifference(Date dt1, Date dt2)
{

    long int n1 = dt1.y * 365 + dt1.d;

    for (int i = 0; i < dt1.m - 1; i++)
        n1 += monthDays[i];

    n1 += countLeapYears(dt1);

    long int n2 = dt2.y * 365 + dt2.d;
    for (int i = 0; i < dt2.m - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);

    return (n2 - n1);
}

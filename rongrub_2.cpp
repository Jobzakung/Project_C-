#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;
void menu();
void pawn(string fn);
void display(string fn);
void search(string fn);
void del(const char *filename, int n);
void delinput();
void date();
void caldate();

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
    }
    else
        cout << "Incorrect Input : ";
}

void menu()
{
    string Filename = "Receipt.txt";
    ofstream OutFile;
    ifstream InFile;
    int c;
    std::cout << "##########################" << std::endl;
    std::cout << "#  Welcome to  Pawnshop  #" << std::endl;
    std::cout << "#   Please Select Menu   #" << std::endl;
    std::cout << "##########################" << std::endl;
    std::cout << "1. ReceiptPawn"             << std::endl;
    std::cout << "2. Display"                 << std::endl;
    std::cout << "3. Search"                  << std::endl;
    std::cout << "4. Delete Line"             << std::endl;
    std::cout << "5. exit Program"            << std::endl;
    std::cout << "Please choice in range 1 - 5 : ";
    cin >> c;
    if (c == 1)
    {
        pawn(Filename);
    }
    if (c == 2)
    {
        display(Filename);
    }
    if (c == 3)
    {
        search(Filename);
    }
    if (c == 4)
    {
        delinput();
    }
    if (c == 5)
    {
        exit(0);
    }
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
        int Interest;

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
        int sum_date, sum_month, sum_year;
        sum_date = abs(Day_Input - Day_Expired);
        sum_month = abs(Month_Input - Day_Expired);
        sum_year = abs(Year_Input - Year_Expired);

        if (sum_year >= 1)
        {
            Interest = stoi(Price) * 0.03;
            Interest += stoi(Price);
        }
        else if (sum_month >= 1)
        {
            Interest = stoi(Price) * 0.265;
            Interest += stoi(Price);
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
        cout << "# " << " " << "ID" << "\t" << "Product" << "\t" << "Interest" << "\t" << "Date" << "\t\t" << "ExDate" << "   #" << endl;
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
    cout << "Input Word to Search";
    cin >> find;
    if (InFile.is_open())
    {
        ifstream InFile(fn.c_str(), ios_base::in);
        if (InFile.is_open())
        {
            string ID, Product, interest, date, Expired_date;
            string ln(58, '=');
            string ln2(58, '-');
            int line = 1;

            cout << ln << endl;
            cout << "* " << " " << "ID "<< "\t" << "Product" << "\t" << "Interest" << "\t" << "Date" << "\t\t" << "ExDate" << " *" << endl;
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

    ifstream fin(filename);
    ofstream temp;
    temp.open("temp.txt", ofstream::out);

    char c;
    int line = 1;
    while (fin.get(c))
    {
        if (c == '\n')
            line++;
        if (line != n)
            temp << c;
    }
    fin.close();
    temp.close();
    remove(filename);
    rename("temp.txt", filename);
}

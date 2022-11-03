#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
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
        string id, mod, Price;
        int dayr, mounthr, yearr;                                  // use to input date mouthn year
        int exdayr, exmounthr, exyearr, Inter, Inter1, d, m, y, p; // use to inpute exdate,mounth,year and d,m,y born for save value after calculated ,p is price after become string,Inter is calculate iclude date mounth year,inter1 is a final result of Interest.
        std::cout << "\n Add Object \n";
        std::cout << "Enter Id (ex:1xxx) : ";
        std::cin >> id;
        std::cout << "Enter Prodect Name : ";
        std::cin >> mod;
        std::cout << "Enter Date (dd mm yyyy) : ";
        cin >> dayr >> mounthr >> yearr;
        std::cout << "Enter Expired Date (dd mm yyyy) : ";
        cin >> exdayr >> exmounthr >> exyearr;
        std::cout << "Enter Price : ";
        std::cin >> Price;
        d = dayr - exdayr;
        m = mounthr - exmounthr;
        y = yearr - exyearr;
        p = stoi(Price);
        Inter = abs(d * m * y * 0.265);
        Inter1 = Inter + p;
        OutFile << id << "\t" << mod << "\t" << Inter1 << "\t" << dayr << "/" << mounthr << "/" << yearr << "\t" << exdayr << "/" << exmounthr << "/" << exyearr << "\t" << std::endl;

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
        string id, mod, interest, date, exdate;
        string ln(58, '=');
        string ln2(58, '-');
        int line = 1;

        InFile >> id >> mod >> interest >> date >> exdate;
        cout << ln << endl;
        cout << "* " << " " << "ID" << "\t" << "Model" << "\t" << "Interest" << "\t" << "Date" << "\t\t" << "ExDate" << " *" << endl;
        cout << ln << endl;
        while (!InFile.eof())
        {
            cout << line << " :" << id << "\t" << mod << "\t" << interest << "\t\t" << date << "\t" << exdate << endl;
            cout << ln2 << endl;
            InFile >> id >> mod >> interest >> date >> exdate;
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
            string id, mod, interest, date, exdate;
            string ln(58, '=');
            string ln2(58, '-');
            int line = 1;

            cout << ln << endl;
            cout << "* " << " " << "ID" << "\t" << "Model" << "\t" << "Interest" << "\t" << "Date" << "\t\t" << "ExDate" << " *" << endl;
            cout << ln << endl;
            while (!InFile.eof())
            {
                InFile >> id >> mod >> interest >> date >> exdate;
                if (find == id)
                {
                    cout << line << " :" << id << "\t" << mod << "\t" << interest << "\t\t" << date << "\t" << exdate << endl;
                    cout << ln2 << endl;
                    InFile >> id >> mod >> interest >> date >> exdate;
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
    int n; // line numbers
    cout << "Which line do you want to remove? ";
    cin >> n;
    del("Receipt.txt", n);
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

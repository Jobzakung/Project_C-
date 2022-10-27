#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
void menu();
void pawn(string fn);
void display(string fn);
void search();
void del();
int p = 0;
int main()
{


    while(true){
        menu();
    }
}

void menu()
{
    string Filename = "Receipt.txt";
    ofstream OutFile;
    ifstream InFile;
    int c;
    std::cout << "#########################" << std::endl;
    std::cout << "  Welcome to  Pawnshop    " << std::endl;
    std::cout << "  Please Select Menu  " << std::endl;
    std::cout << "#########################" << std::endl;
    std::cout << "1. ReceiptPawn" << std::endl;
    std::cout << "2. Display" << std::endl;
    std::cout << "3. Search" << std::endl;
    std::cout << "4. Delete Line" << std::endl;
    std::cout << "5. exit Program" << std::endl;
    std::cout << "Please choice in range 1 - 5 : " ;
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
        search();
    }
    if (c == 4)
    {
        del();
    }
    if (c == 5){
        exit(0);
    }
}

void pawn(string fn)
{
    ofstream OutFile(fn.c_str(), ios_base::out | ios_base::app);
    if (OutFile.is_open())
    {
        string id, mod, date, exdate, Price, Interest;
        std::cout << "\n Add Object \n";
        std::cout << "Enter Id : ";
        std::cin >> id;
        std::cout << "Enter Prodect Name : ";
        std::cin >> mod;
        std::cout << "Enter Date : ";
        std::cin >> date;
        std::cout << "Enter Expire Date : ";
        std::cin >> exdate;
        std::cout << "Enter Price : ";
        std::cin >> Price;
        Interest += Price;
        OutFile << id << "\t" << mod << "\t" << date << "\t" << exdate << "\t"<< Price << "\t" << stoi(Interest) * 0.03 << std::endl 
                << endl;
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
        string id, mod, date, exdate, Price, Interest;
        int line = 1;

        InFile >> id >> mod >> date >> exdate >> Price >> Interest;
        cout << "####################################################################################################" << std::endl;
        cout << "#  ID          Prodect Name            Date        Expire Date          Price          Interest    #" << std::endl;
        cout << "####################################################################################################" << std::endl;

        while (!InFile.eof())
        {
            cout << line << " :" << id << "\t\t   " << mod << "\t\t    " << date << "\t   " << exdate << "\t\t" << Price << "\t\t " << Interest << endl;
            InFile >> id >> mod >> date >> exdate >> Price >> Interest;
            line++;
        }
        InFile.close();
        char Wait;
        cin.get(Wait);
        cout << "\nPress Enter to continue";
        cin.get(Wait);
    }
}
void search()
{
    ifstream MyFile;
    MyFile.open("Receipt.txt");

    string search;
    int offset;
    string line;

    cout << "Enter the word to search: ";
    cin >> search;

    if (MyFile.is_open())
    {
        while (!MyFile.eof())
        {
            getline(MyFile, line);
            if ((offset = line.find(search, 0)) != string::npos)
            {
                cout << "the word has been found" << search << endl;
            }
        }
        MyFile.close();
    }
    else
    {
        cout << "File opening error" << endl;
    }
}

void del()
{
    string deleteline;
    string line;

    ifstream fin;
    fin.open("Receipt.txt");
    ofstream temp;
    temp.open("temp.txt");

    cout << "Which line do you want to remove? ";
    cin >> deleteline;

    while (getline(fin, line))
    {
        if (line.substr(0, deleteline.size()) != deleteline)
            temp << line << endl;
    }

    temp.close();
    fin.close();
    remove("Receipt.txt");
    rename("temp.txt", "Receipt.txt");
}

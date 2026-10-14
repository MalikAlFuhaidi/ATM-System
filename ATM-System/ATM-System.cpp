#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

enum enATMMainMenueOptions { eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalances = 4, Logout = 5 };
enum enQuickWithdrawOptions { eQWithdraw20 = 1, eQWithdraw50 = 2, eQWithdraw100 = 3, eQWithdraw200 = 4, eQWithdraw400 = 5, eQWithdraw600 = 6, eQWithdraw800 = 7, eQWithdraw1000 = 8 };

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0.0;
    bool MarkForDelete = false;
};

const string ClientsFileName = "Clients.txt";
sClient CurrentClient;

void ShowATMMainMenue();
void ShowQuickWithDrawScreen();
void Login();


string ReadAccountNumber()
{
    string AccountNumber = "";
    cout << "Enter AccountNumber? ";
    getline(cin >> ws, AccountNumber);

    return AccountNumber;
}

string ReadPinCode()
{
    string PinCode = "";
    cout << "Enter Pin? ";
    getline(cin >> ws, PinCode);

    return PinCode;
}

short ReadQuickWithdrawOption()
{
    cout << "Choose what to withdraw from [1] to [8]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

short ReadATMMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable

    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double

    return Client;

}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{
    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, sClient& CurrentClient)
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
        {
            CurrentClient = C;
            return true;
        }

    }
    return false;

}

bool LoadClientInfo(string AccountNumber, string PinCode)
{
    if (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient))
        return true;
    else
        return false;
}

double ValidateAmountExceeds(double Amount)
{
    //Validate that the amount does not exceeds the balance
    while (Amount > CurrentClient.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << CurrentClient.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }
    return Amount;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount)
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                CurrentClient = C;
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
                return true;
            }
        }

        return false;
    }
    else
    {
        return false;
    }

}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    double Amount = 0.0;
    cout << "\nPlease enter Positve deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, Amount);
}

void ShowCheckBalanceScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tCheck Balance Screen";
    cout << "\n-----------------------------------\n";

    cout << "\n\nYour Balance is " << CurrentClient.AccountBalance << endl;

}

void ShowNormalWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tNormal Withdraw Screen";
    cout << "\n-----------------------------------\n";

    //double Amount = 0;
    int Amount = 0;
    do
    {
        cout << "\nEnter an amount multiple of 5's ? ";
        cin >> Amount;

    } while (Amount % 5 != 0);

    //Validate that the amount does not exceeds the balance
    ValidateAmountExceeds(Amount);

    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, Amount * -1);

}

void QuickWithdraw(double Amount)
{
    ValidateAmountExceeds(Amount);

    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, (-1 * Amount));
}

void GoBackToATMMenue()
{
    cout << "\n\nPress any key to go back to ATM Main Menue...";
    system("pause>0");
    ShowATMMainMenue();

}

void GoBackToQuickWithdrawMenu()
{
    cout << "\n\nPress any key to go back to Quick Withdraw Menue...";
    system("pause>0");
    ShowQuickWithDrawScreen();
}

void PerfromQuickWithdrawOption(enQuickWithdrawOptions QuickWithdrawOption)
{
    switch (QuickWithdrawOption)
    {
    case enQuickWithdrawOptions::eQWithdraw20:
        QuickWithdraw(20);
        GoBackToATMMenue();
        break;
    case enQuickWithdrawOptions::eQWithdraw50:
        QuickWithdraw(50);
        GoBackToATMMenue();
        break;
    case enQuickWithdrawOptions::eQWithdraw100:
        QuickWithdraw(100);
        GoBackToATMMenue();
        break;
    case enQuickWithdrawOptions::eQWithdraw200:
        QuickWithdraw(200);
        GoBackToATMMenue();
        break;
    case enQuickWithdrawOptions::eQWithdraw400:
        QuickWithdraw(400);
        GoBackToATMMenue();
        break;
    case enQuickWithdrawOptions::eQWithdraw600:
        QuickWithdraw(600);
        GoBackToATMMenue();
        break;
    case enQuickWithdrawOptions::eQWithdraw800:
        QuickWithdraw(800);
        GoBackToATMMenue();
        break;
    case enQuickWithdrawOptions::eQWithdraw1000:
        QuickWithdraw(1000);
        GoBackToATMMenue();
        break;
    default:
        if ((short)QuickWithdrawOption == 9)
        {
            GoBackToATMMenue();
            return;
        }

        system("cls");
        cout << "\nInvalid option.\n";
        GoBackToQuickWithdrawMenu();
        return;
    }
}

void ShowQuickWithDrawScreen()
{
    system("cls");
    cout << "\n=============================================\n";
    cout << "\tQuick Withdraw ";
    cout << "\n=============================================\n";
    cout << "\t[1] 20  \t\t [2] 50 \n";
    cout << "\t[3] 100 \t\t [4] 200 \n";
    cout << "\t[5] 400 \t\t [6] 600 \n";
    cout << "\t[7] 800 \t\t [8] 1000 \n";
    cout << "\t[9]Exit ";
    cout << "\n=============================================\n";

    cout << "Your Balance is " << CurrentClient.AccountBalance << endl;

    PerfromQuickWithdrawOption((enQuickWithdrawOptions)ReadQuickWithdrawOption());
}

void PerfromATMMenueOption(enATMMainMenueOptions ATMMenueOption)
{
    switch (ATMMenueOption)
    {
    case enATMMainMenueOptions::eQuickWithdraw:
    {
        system("cls");
        ShowQuickWithDrawScreen();
        GoBackToATMMenue();
        break;
    }
    case enATMMainMenueOptions::eNormalWithdraw:
    {
        system("cls");
        ShowNormalWithDrawScreen();
        GoBackToATMMenue();
        break;
    }
    case enATMMainMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
       GoBackToATMMenue();
        break;
    }
    case enATMMainMenueOptions::eCheckBalances:
    {
        system("cls");
        ShowCheckBalanceScreen();
       GoBackToATMMenue();
        break;
    }
    case enATMMainMenueOptions::Logout:
    {
        system("cls");
        Login();
        break;
    }
    }

}

void ShowATMMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tShow ATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balances.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";
    PerfromATMMenueOption((enATMMainMenueOptions)ReadATMMainMenueOption());
}

void Login()
{
    bool LoginFaild = false;

    do
    {
        system("cls");
        cout << "\n-----------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n-----------------------------------\n";

        if (LoginFaild)
        {
            cout << "\nInvalid AccountNumber/Pin!\n\n";
        }

        string AccountNumber = ReadAccountNumber();
        string PinCode = ReadPinCode();

        LoginFaild = !LoadClientInfo(AccountNumber, PinCode);
    } while (LoginFaild);

    ShowATMMainMenue();
}

int main()
{
    Login();

    system("pause>0");
    return 0;
}
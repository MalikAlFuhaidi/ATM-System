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

//void ShowATMMainMenue();
//void ShowQuickWithDrawScreen();
void Login();


void Login()
{

}

int main()
{
    Login();

    system("pause>0");
    return 0;
}
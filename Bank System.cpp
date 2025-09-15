#include<iostream>
#include <cstdlib>
#include<iomanip>
#include<string>
#include<cctype>
#include<vector>
#include<fstream>
using namespace std;

// first project -BANK-
// Copyright (c) 2025 Anas Ali Chafai. All rights reserved.
// Contact: anaschafai04gmail.com

const string ClientsFileName = "Bank.txt";
void StartMain();
void GoBackToMainMenu()
{
	cout << "\nPress any key to go back to Main Menu...";
	system("pause>nul");
	cout << endl;
	StartMain();
}
string ReadString(string msg) {
	string s;
	cout << msg;
	getline(cin >> ws, s);
	return s;
}
short ReadNum(string msg) {
	short n;
	cout << msg;
	cin >> n;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
		cout << "please enter a validate num";
		cin >> n;
	}
	return n;
}
struct stAccount {
	string accountNumber;
	string pinCode;
	string name;
	string phone;
	float accountBalance = 0;
	bool mark = false;
};
vector <string> SplitString(string S, string delim)
{
	vector <string> vs;
	short pos;
	string word;
	while ((pos = S.find(delim)) != string::npos)
	{
		word = S.substr(0, pos);
		if (word != "")
		{
			vs.push_back(word);
		}
		S.erase(0, pos + delim.length());
	}
	if (S != "")
	{
		vs.push_back(S);
	}
	return vs;
}
stAccount ConvertLineToRecord(string Line, string sperator = "#//#")
{
	vector <string> StringDevided = SplitString(Line, sperator);
	stAccount Acc;
	Acc.accountNumber = StringDevided[0];
	Acc.pinCode = StringDevided[1];
	Acc.name = StringDevided[2];
	Acc.phone = StringDevided[3];
	Acc.accountBalance = stof(StringDevided[4]);
	return Acc;

}
string ConvertRecordToLine(stAccount Account, string sperator = "#//#")
{
	string s = Account.accountNumber + sperator +
		Account.pinCode + sperator + Account.name +
		sperator + Account.phone + sperator +
		to_string(Account.accountBalance);
	return s;
}
void LoadDataFromFile(string FileName, vector <stAccount>& vAcc)
{
	fstream f;
	string line;
	stAccount Acc;
	f.open(FileName, ios::in);
	if (f.is_open())
	{
		while (getline(f, line))
		{
			if (line != "")
			{
				Acc = ConvertLineToRecord(line);
				vAcc.push_back(Acc);
			}
		}
		f.close();
	}
}
void SaveVectorToFile(string FileName, vector <stAccount> vAcc)
{
	fstream f;
	string s;
	f.open(FileName, ios::out);
	if (f.is_open())
	{
		for (stAccount& Account : vAcc)
		{
			s = ConvertRecordToLine(Account);
			f << s << endl;
		}
		f.close();
	}
}
enum enSelection {
	eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 3,
	eUpdateClientInfo = 4, eFindClient = 5, eExit = 6
};
void ShowClientList()
{
	system("cls");
	vector <stAccount> vFile;
	LoadDataFromFile(ClientsFileName, vFile);
	cout << "\t\tClient List " << vFile.size() << " Client(s)." << endl;
	cout << "---------------------------------------------------------------------------------------------------------\n\n";
	cout << "| " << left << setw(15) << "Account Number"
		<< "| " << setw(10) << "pin code"
		<< "| " << setw(30) << "Client Name"
		<< "| " << setw(12) << "Phone"
		<< "| " << setw(12) << "balance" << endl;
	cout << "\n---------------------------------------------------------------------------------------------------------\n";
	for (stAccount& a : vFile)
	{
		cout << "| " << left << setw(15) << a.accountNumber;
		cout << "| " << left << setw(10) << a.pinCode;
		cout << "| " << left << setw(30) << a.name;
		cout << "| " << left << setw(12) << a.phone;
		cout << "| " << left << setw(12) << a.accountBalance;
		cout << endl;
	}
	GoBackToMainMenu();
}
void SaveClientToFile(const stAccount& client)
{
	fstream File;
	File.open(ClientsFileName, ios::out | ios::app);
	if (File.is_open())
	{
		File << ConvertRecordToLine(client) << endl;
		File.close();
	}
}
bool CheckIfClientExist(vector < stAccount>& vAcc, string AccountNumber)
{
	bool R = false;
	for (stAccount& A : vAcc)
	{
		if (A.accountNumber == AccountNumber)
		{
			R = true;
			break;
		}
	}
	return R;
}
bool CheckIfClientExist(vector < stAccount>& vAcc, string AccountNumber, stAccount& ACC)
{
	bool R = false;
	for (stAccount& A : vAcc)
	{
		if (A.accountNumber == AccountNumber)
		{
			A.mark = true;
			ACC = A;
			R = true;
			break;
		}
	}
	return R;
}
void AddClient()
{
	vector <stAccount> vacc;
	stAccount NewAccount;
	string AccountNumber;
	bool Retur = false;
	char Again = 'y';
	LoadDataFromFile(ClientsFileName, vacc);
	while (tolower(Again) == 'y') {
		AccountNumber = ReadString("Enter Acccount Number : ");
		while (CheckIfClientExist(vacc, AccountNumber))
		{
			cout << "Enter Another Account Number : ";
			getline(cin, AccountNumber);
		}

		NewAccount.accountNumber = AccountNumber;
		cout << "Enter PinCode ? ";
		getline(cin >> ws, NewAccount.pinCode);
		cout << "Enter Name ? ";
		getline(cin, NewAccount.name);
		cout << "Enter Phone ? ";
		getline(cin, NewAccount.phone);
		cout << "Enter Account Balance ? ";
		cin >> NewAccount.accountBalance;
		cin.ignore();
		vacc.push_back(NewAccount);
		SaveClientToFile(NewAccount);
		cout << "Client Add Successfully,";
		cout << "Do you want to add more client ? ";
		cin >> Again;
		AccountNumber = "";
	}
}
void AddNewClient()
{
	system("cls");
	cout << "------------------------------------------\n"
		<< "\t\tAdding New Client\n"
		<< "------------------------------------------\n";
	cout << "Adding New Client :\n";
	AddClient();
	GoBackToMainMenu();
}
void PrintClientDetails(stAccount client) {
	cout << "Account Number : " << client.accountNumber << endl;
	cout << "Pin Code       : " << client.pinCode << endl;
	cout << "Name           : " << client.name << endl;
	cout << "Phone          : " << client.phone << endl;
	cout << "Account Balance: " << client.accountBalance << endl;
}
void DeleteClient(string FileName, vector <stAccount> vAcc)
{
	fstream f;
	string line;
	f.open(FileName, ios::out);
	if (f.is_open())
	{
		for (stAccount& A : vAcc)
		{
			if (A.mark == false)
			{
				line = ConvertRecordToLine(A);
				f << line << endl;
			}
		}
		f.close();
	}
}
void DeleteClientScreen()
{
	char y;
	system("cls");
	cout << "------------------------------------------\n"
		<< "\t\tDelete Client Screen\n"
		<< "------------------------------------------\n";
	string AccountNumber = ReadString("Please Enter Account Number : ");
	stAccount acc;
	vector <stAccount> vAcc;
	LoadDataFromFile(ClientsFileName, vAcc);
	if (CheckIfClientExist(vAcc, AccountNumber, acc))
	{
		cout << "\nThe Following Are The Client Details \n"
			<< "-------------------------------------------\n";
		PrintClientDetails(acc);
		cout << "-------------------------------------------";
		cout << "\n\nAre You Sure You Want To Delete This Client ? ";
		cin >> y;
		if (tolower(y) == 'y')
		{
			DeleteClient(ClientsFileName, vAcc);
			cout << "\nClient Delte Successfully";
		}
	}
	else
	{
		cout << "Client With Number Account (" << AccountNumber << ") is Not Found!";
	}
	GoBackToMainMenu();
}
stAccount UpdateClientInformation(string AccountNumber)
{
	stAccount Account;
	Account.accountNumber = AccountNumber;

	cout << "Enter PinCode ? ";
	getline(cin >> ws, Account.pinCode);
	cout << "Enter Name ? ";
	getline(cin, Account.name);
	cout << "Enter Phone ? ";
	getline(cin, Account.phone);
	cout << "Enter Account Balance ? ";
	cin >> Account.accountBalance;
	cin.ignore();

	return Account;
}
void UpdateClient(string FileName, vector <stAccount> vAcc)
{
	fstream f;
	string line;
	f.open(FileName, ios::out);
	if (f.is_open())
	{
		for (stAccount& A : vAcc)
		{
			if (A.mark == false)
			{
				line = ConvertRecordToLine(A);
				f << line << endl;
			}
			else
			{
				line = ConvertRecordToLine(UpdateClientInformation(A.accountNumber));
				f << line << endl;
			}
		}
		f.close();
	}
}
void UpdateClientScreen()
{
	char y;
	system("cls");
	cout << "------------------------------------------\n"
		<< "\t\tUpdate Client Screen\n"
		<< "------------------------------------------\n";
	string AccountNumber = ReadString("Please Enter Account Number : ");
	stAccount acc;
	vector <stAccount> vAcc;
	LoadDataFromFile(ClientsFileName, vAcc);
	if (CheckIfClientExist(vAcc, AccountNumber, acc))
	{
		cout << "\nThe Following Are The Client Details \n"
			<< "-------------------------------------------\n";
		PrintClientDetails(acc);
		cout << "-------------------------------------------";
		cout << "\n\nAre You Sure You Want To Update This Client ? ";
		cin >> y;
		if (tolower(y) == 'y')
		{
			UpdateClient(ClientsFileName, vAcc);
			cout << "\nClient Updated Successfully";
		}
	}
	else
	{
		cout << "Client With Number Account (" << AccountNumber << ") is Not Found!";
	}
	GoBackToMainMenu();
}
void FindClientScreen()
{
	system("cls");
	cout << "------------------------------------------\n"
		<< "\t\tUpdate Client Screen\n"
		<< "------------------------------------------\n";
	string AccountNumber = ReadString("Please Enter Account Number : ");
	stAccount acc;
	vector <stAccount> vAcc;
	LoadDataFromFile(ClientsFileName, vAcc);
	if (CheckIfClientExist(vAcc, AccountNumber, acc))
	{
		cout << "\nThe Following Are The Client Details \n"
			<< "-------------------------------------------\n";
		PrintClientDetails(acc);
		cout << "-------------------------------------------";
	}
	else
	{
		cout << "Client With Number Account (" << AccountNumber << ") is Not Found!";
	}
	GoBackToMainMenu();
}
void ExitScreen()
{
	system("cls");
	cout << "\n\n----------------------------------------\n"
		<< "\tProgram Ends :-)\n"
		<< "----------------------------------------";
	system("pause>nul");

}
void MenueDesign()
{
	cout << "=====================================\n";
	cout << "         Main Menu Screen            \n";
	cout << "=====================================\n";
	cout << "[1] Show Client List\n";
	cout << "[2] Add New Client\n";
	cout << "[3] Delete Client\n";
	cout << "[4] Update Client Info\n";
	cout << "[5] Find Client\n";
	cout << "[6] Exit\n";
	cout << "=====================================\n";
	cout << "Choose What do you want to do ? [1 to 6]  ";
}
void StartMain()
{
	system("cls");
	MenueDesign();
	short Select = ReadNum("");
	switch (Select)
	{
	case enSelection::eShowClientList: ShowClientList();
		break;
	case enSelection::eAddNewClient: AddNewClient();
		break;
	case enSelection::eDeleteClient: DeleteClientScreen();
		break;
	case enSelection::eUpdateClientInfo: UpdateClientScreen();
		break;
	case enSelection::eFindClient: FindClientScreen();
		break;
	case enSelection::eExit: ExitScreen();
	}
}
int main()
{
	StartMain();
}
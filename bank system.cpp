#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<vector>
using namespace std;
const string myfile = "bank2.txt";
void choose_item_from_menue();
void choose_item_from_manue_tran();
string readstring()
{
	string account_number;
	cout << "enter account number:";
	getline(cin, account_number);
	return account_number;
}
struct infoaccount
{
	string account_number;
	string bin_code_number;
	string your_name;
	string phone_number;
	double account_balanc;
	bool mark_for_delete = false;
};
vector<string>splitstr(string x, string delim)
{
	vector<string>vword;
	short pos = 0;
	string sword;

	while ((pos = x.find(delim)) != std::string::npos)
	{
		sword = x.substr(0, pos);
		if (sword != "")
		{
			vword.push_back(sword);

		}
		x.erase(0, pos + delim.length());

	}
	if (x != delim)
	{
		vword.push_back(x);

	}


	return vword;
}
infoaccount  ConvertLinetoRecord(string line, string seperator = "#//#")
{
	infoaccount myinfo;
	vector<string>vword;
	vword = splitstr(line, seperator);
	myinfo.account_number = vword[0];

	myinfo.bin_code_number = vword[1];
	myinfo.your_name = vword[2];
	myinfo.phone_number = vword[3];
	myinfo.account_balanc = stod(vword[4]);
	return myinfo;
}
vector<infoaccount>LoadCleintsDataFromFile(string myfile)
{
	vector<infoaccount>vinfo;
	fstream koko;
	koko.open(myfile, ios::in);
	if (koko.is_open())
	{
		string line;

		while (getline(koko, line))
		{
			infoaccount myinfo;
			myinfo = ConvertLinetoRecord(line);
			vinfo.push_back(myinfo);




		}
		koko.close();
	}
	return vinfo;

}
void  PrintClientRecord(infoaccount myinfo)
{

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << "Accout Number=" << myinfo.account_number << endl;
	cout << "| " << "Pin Code=" << myinfo.bin_code_number << endl;
	cout << "| " << "Client Name=" << myinfo.your_name << endl;
	cout << "| " << "Phone=" << myinfo.phone_number << endl;
	cout << "| " << "Balance=" << myinfo.account_balanc << endl;
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}
string convert_record_to_line(infoaccount myinfo, string delim = "#//#")
{
	string collactioninfo;
	collactioninfo += myinfo.account_number + delim;
	collactioninfo += myinfo.bin_code_number + delim;
	collactioninfo += myinfo.your_name + delim;
	collactioninfo += myinfo.phone_number + delim;
	collactioninfo += to_string(myinfo.account_balanc);
	return collactioninfo;
}
bool find_clint_by_account_number(string account_number, vector<infoaccount>vinfo, infoaccount& myinfo)
{
	for (infoaccount c : vinfo)
	{
		if (c.account_number == account_number)
		{
			myinfo = c;
			//ÑÇÍ íÎÒä in my info ÝÞØ ÇáÚäÕÑ ÇáÐí = account 
			//by refrinc ÊÓÊÎÏã ááÊÎÒíä ÇáÚäÕÑ ÇáæÇÍÏ ÝÞØ 
			//ÞíãÊåÇ ÓæÝ Êßæä Çá ÓÊÑíßÊÌÑ Çáí ÓÇæå ÇßÇæä äãÈÑ 
			return true;

		}

	}
	return false;
}
vector<infoaccount>saveclaintdatatofile(string myfile, vector<infoaccount>vinfo)
{

	fstream sajjad;
	sajjad.open(myfile, ios::out);
	string dataline;
	if (sajjad.is_open())
	{
		for (infoaccount c : vinfo)
		{
			if (c.mark_for_delete == false)
			{
				dataline = convert_record_to_line(c);
				sajjad << dataline << endl;
			}
		}
		sajjad.close();
	}
	return vinfo;
}
bool mark_clint_for_delete_by_account_number(string account_number, vector<infoaccount>& vinfo)
{
	for (infoaccount& c : vinfo)
	{
		if (c.account_number == account_number)
		{
			c.mark_for_delete = true;
			return true;
		}
	}return false;

}
bool clintexistsbyaccountnumber(string account_number, string myflie)
{
	vector<infoaccount>vinfo;
	infoaccount myinfo;
	fstream proj;
	proj.open(myfile, ios::in);
	if (proj.is_open())
	{
		string line;

		while (getline(proj, line))
		{
			myinfo = ConvertLinetoRecord(line);
			if (myinfo.account_number == account_number)
			{

				proj.close();
				return true;

			}
			vinfo.push_back(myinfo);




		}
		proj.close();
	}
	return false;

}
infoaccount readnewclint()
{
	infoaccount myinfo;
	cout << "\n\n enter your account number? ";
	getline(cin >> ws, myinfo.account_number);
	while (clintexistsbyaccountnumber(myinfo.account_number, myfile))
	{
		cout << "clint with[" << myinfo.account_number << "]already exists,Enter another account number?" << endl;
		getline(cin >> ws, myinfo.account_number);


	}

	cout << "\n\n enter your bin_code? ";
	getline(cin, myinfo.bin_code_number);

	cout << "\n\n enter your name? ";
	getline(cin, myinfo.your_name);

	cout << "\n\n enter your phone number? ";
	getline(cin, myinfo.phone_number);


	cout << "\n\n enter your account balanc? ";
	cin >> myinfo.account_balanc;





	return myinfo;
}
infoaccount read_stract_infoaccount(vector<infoaccount>vinfo)
{
	infoaccount myinfo;
	cout << "\n\n enter your account number? ";
	getline(cin >> ws, myinfo.account_number);
	for (infoaccount chakacc : vinfo)
	{
		if (chakacc.account_number == myinfo.account_number)
		{
			cout << "clint with[" << myinfo.account_number << "]already exists,Enter another account number?" << endl;
			getline(cin >> ws, myinfo.account_number);
		}

	}

	cout << "\n\n enter your bin_code? ";
	getline(cin, myinfo.bin_code_number);

	cout << "\n\n enter your name? ";
	getline(cin, myinfo.your_name);

	cout << "\n\n enter your phone number? ";
	getline(cin, myinfo.phone_number);


	cout << "\n\n enter your account balanc? ";
	cin >> myinfo.account_balanc;





	return myinfo;
}
infoaccount read_stract_infoaccount_to_update(string account_number)
{
	infoaccount myinfo;
	myinfo.account_number = account_number;
	cout << "\n\n enter your bin_code? ";
	getline(cin >> ws, myinfo.bin_code_number);
	cout << "\n\n enter your name? ";
	getline(cin, myinfo.your_name);

	cout << "\n\n enter your phone number? ";
	getline(cin, myinfo.phone_number);


	cout << "\n\n enter your account balanc? ";
	cin >> myinfo.account_balanc;

	return myinfo;
}
void adddatanewline(string myfile, infoaccount myinfo)//to stor and append info about new clint in file 
{

	fstream sajjad;

	sajjad.open(myfile, ios::out | ios::app);

	if (sajjad.is_open())
	{
		sajjad << "\n";
		sajjad << convert_record_to_line(myinfo);
	}

}
void addnewclinte()
{
	vector<infoaccount>vinfo;
	infoaccount myinfo;
	myinfo = readnewclint();
	adddatanewline(myfile, myinfo);
}
void addnewclintes()
{
	char addmore = 'Y';
	do
	{
		cout << "adding new clint:\n\n";
		addnewclinte();
		cout << "clint added successfully,do you want to add mor clintes?y/n?";
		cin >> addmore;
	} while (toupper(addmore) == 'Y');


}
void update_cliant_by_account_number(string account_number, vector<infoaccount>& vinfo)
{
	// åÐå ÇáÏÇáÉ ÊÓÊÞÈá ÝíßÊæÑ ãáíÇä
	infoaccount myinfo;
	char answer;

	if (find_clint_by_account_number(account_number, vinfo, myinfo))
	{
		PrintClientRecord(myinfo);
		cout << "\n\nAre you sure you want update this client? y/n ? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			for (infoaccount& c : vinfo)
			{
				if (c.account_number == account_number)
				{
					c = read_stract_infoaccount_to_update(account_number);
					break;

				}

			}
			saveclaintdatatofile(myfile, vinfo);
			// ÊÞæã åÐå ÇáÏÇáÉ ÈØÈÇÚå ãä ÌÏíÏ ÝÞØ ÇáãÚáæãÇÊ Çáí ÇÎÑ ÚäËÑ ÈíåÇ íÓÇæí false íÚäí ÇáÚäÕÑ Çáí Êã ÊÛíÑå ÝæÞ áÇ íäØÈÚ
			// ÈåÏåÇ ÓæÝ íÊã ÇÏÎÇá ÇáãáÝ ÈÇáÏÇáÉ ÊÍÊ
			// æãä Ëãå ÓæÝ ÊÎÒä Ýí ÇáÝíßÊæÑ ß ÚäÇÕÑ äÇÞÕÉ æÇÍÏ
			//refrish;


			cout << "\n\nClient update Successfully.";

		}

	}
	else
	{
		cout << "not found account number:" << account_number << endl;

	}
}
void delet_cliant_by_account_number(vector<infoaccount>& vinfo, string account_number)
{

	// åÐå ÇáÏÇáÉ ÊÓÊÞÈá ÝíßÊæÑ ãáíÇä
	infoaccount myinfo;
	char answer;

	if (find_clint_by_account_number(account_number, vinfo, myinfo))
	{
		PrintClientRecord(myinfo);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			mark_clint_for_delete_by_account_number(account_number, vinfo);
			//^ ÈÇáÊÇáí ÓæÝ ÊÓÞÈáå ÇáÏÇáÉ ÇáÓÝáíÉ >åÐå ÓæÝ ÊÑÌÚ Ýí ÇáÝíßÊæÑ  ÇáÓÊÑíßÌÑ ÇáãÓÊåÏÝ ãÊÛíÑ Ýíå ÇáÚäÕÑ ÇáÇÎíÑ

			saveclaintdatatofile(myfile, vinfo);
			// ÊÞæã åÐå ÇáÏÇáÉ ÈØÈÇÚå ãä ÌÏíÏ ÝÞØ ÇáãÚáæãÇÊ Çáí ÇÎÑ ÚäËÑ ÈíåÇ íÓÇæí false íÚäí ÇáÚäÕÑ Çáí Êã ÊÛíÑå ÝæÞ áÇ íäØÈÚ
			// ÈåÏåÇ ÓæÝ íÊã ÇÏÎÇá ÇáãáÝ ÈÇáÏÇáÉ ÊÍÊ
			// æãä Ëãå ÓæÝ ÊÎÒä Ýí ÇáÝíßÊæÑ ß ÚäÇÕÑ äÇÞÕÉ æÇÍÏ
			//refrish;
			vinfo = LoadCleintsDataFromFile(myfile);
			cout << "\n\nClient Deleted Successfully.";

		}

	}
	else
	{
		cout << "not found account number:" << account_number << endl;

	}
}
void  PrintClientRecord_choose1(infoaccount myinfo)
{
	cout << "| " << setw(15) << left << myinfo.account_number;
	cout << "| " << setw(10) << left << myinfo.bin_code_number;
	cout << "| " << setw(40) << left << myinfo.your_name;
	cout << "| " << setw(12) << left << myinfo.phone_number;
	cout << "| " << setw(12) << left << myinfo.account_balanc;




}
void PrintAllClientsData(vector <infoaccount> vinfo)
{
	cout << "\t\t\t\t\tclint(" << vinfo.size() << ") clint(s)\n\n\n\n";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << right << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (infoaccount s1 : vinfo)
	{
		PrintClientRecord_choose1(s1);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}
void showprintallclientsdata()
{
	system("cls");
	vector<infoaccount>vinfo;
	vinfo = LoadCleintsDataFromFile(myfile);
	PrintAllClientsData(vinfo);

}
void showadddatanewline()
{
	cin.ignore();
	addnewclintes();

}
void showdelet_cliant_by_account_number()
{
	cin.ignore();
	string account_number;
	vector<infoaccount>vinfo;

	vinfo = LoadCleintsDataFromFile(myfile);
	account_number = readstring();

	delet_cliant_by_account_number(vinfo, account_number);

}
void showupdate_cliant_by_account_number()
{
	cin.ignore();
	string account_number;
	vector<infoaccount>vinfo;
	vinfo = LoadCleintsDataFromFile(myfile);

	account_number = readstring();
	update_cliant_by_account_number(account_number, vinfo);

}
void showfind_clint_by_account_number()
{
	cin.ignore();
	infoaccount myinfo;
	vector<infoaccount>vinfo;
	vinfo = LoadCleintsDataFromFile(myfile);
	string account_number;

	account_number = readstring();
	if (find_clint_by_account_number(account_number, vinfo, myinfo))
	{
		PrintClientRecord(myinfo);

	}
	else
	{
		cout << endl;
		cout << "not found(" << account_number << ")";
	}
}
void showend()
{

	cout << "you are welcome in my system:-)" << endl;

}
enum enmanue
{
	showallclint = 1,
	addclint = 2,
	deletclint = 3,
	updetclint = 4,
	findclint = 5,
	transactions = 6,
	endsystem = 7


};
void gobacktomenue()
{
	system("pause>0");
	cout << "\n\npress any key to go back to mine manue..";
	system("pause>0");
	choose_item_from_menue();


}
short readmanue()
{
	int the_choose;
	cout << "choose what do you want to do ?[1 to 7]?";
	cin >> the_choose;
	return the_choose;
}
//******************************************************
vector<infoaccount> updet_balanc(string myfile,vector<infoaccount>vinfo)
{


	fstream sajjad;
	sajjad.open(myfile, ios::out);
	string dataline;
	if (sajjad.is_open())
	{
		for (infoaccount c : vinfo)
		{
			
				dataline = convert_record_to_line(c);
				sajjad << dataline << endl;
			
		}
		sajjad.close();
	}
	return vinfo;
}
bool deposit(vector<infoaccount>& vinfo, string account_number,double amount)
{

	// åÐå ÇáÏÇáÉ ÊÓÊÞÈá ÝíßÊæÑ ãáíÇä
	infoaccount myinfo;
	char answer;
	//double deposit_m;

	
	
		/*cout << "\n\nplease enter your deposit new the account?";
		cin >> deposit_m;*///


		cout << "\n\nAre you sure you want deposit in this client? y/n ? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			for (infoaccount &tr : vinfo)
			{
				if (tr.account_number == account_number)
				{
					tr.account_balanc = tr.account_balanc + amount;
					saveclaintdatatofile(myfile, vinfo);
					cout << "\n\n done Successfully.new balance is: " << tr.account_balanc;
					return true;
				}
				updet_balanc(myfile, vinfo);

			}
			
			return false;

		}

	
	
}
void chack_withdraw(infoaccount &withd,string account_number)
{
	double withdraw;
	if (withd.account_number == account_number)
	{
		do
		{
			cout << "\n\nplease enter your withdraw new the account?";
			cin >> withdraw;
			if (withd.account_balanc >= withdraw)
			{
				withd.account_balanc = withd.account_balanc - withdraw;

			}
			else
			{
				cout << "amount exceds the balance,you can withdraw up to: " << withd.account_balanc << endl;

			}


		} while (withd.account_balanc < withdraw);

	}

}
void withdraw_m(vector<infoaccount>& vinfo, string account_number)
{

	// åÐå ÇáÏÇáÉ ÊÓÊÞÈá ÝíßÊæÑ ãáíÇä
	infoaccount myinfo;
	char answer;
	double withdraw;

	if (find_clint_by_account_number(account_number, vinfo, myinfo))
	{
		PrintClientRecord(myinfo);
		
		cout << "\n\nAre you sure you want whithdraw in this client? y/n ? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			for (infoaccount& withd : vinfo)
			{
				
					
				chack_withdraw(withd, account_number);

				
				
				updet_balanc(myfile, vinfo);

			}

			vinfo = LoadCleintsDataFromFile(myfile);
			cout << "\n\nwithdraw Successfully.";

		}

	}
	else
	{
		cout << "you are welcome in sajjad bank:" << endl;

	}
}
void show_deposit()
{
	infoaccount myinfo;
	cin.ignore();
	string account_number;
	vector<infoaccount>vinfo;

	vinfo = LoadCleintsDataFromFile(myfile);
	account_number = readstring();
	while (!find_clint_by_account_number(account_number, vinfo, myinfo))
	{
		cout << "\n clint with [" << account_number << "] dose not exist.\n";
		account_number = readstring();
	}
	PrintClientRecord(myinfo);
	double amount = 0;
	cout << "\nplease enter deposit amount?";
	cin >> amount;
	deposit(vinfo, account_number,amount);
	

}
void show_whithdraw()
{
	

	cin.ignore();
	string account_number;
	vector<infoaccount>vinfo;
	infoaccount myinfo;
	vinfo = LoadCleintsDataFromFile(myfile);
	account_number = readstring();
	while (!find_clint_by_account_number(account_number, vinfo, myinfo))
	{
		cout << "\n clint with [" << account_number << "] dose not exist.\n";
		account_number = readstring();
	}
	
	PrintClientRecord(myinfo);
	double amount = 0;
	cout << "\nplease enter deposit amount?";
	cin >> amount;
	while (amount > myinfo.account_balanc)
	{
		cout << "amount exceeds the balanc,you can withdraw up to :" << myinfo.account_balanc << endl;
		cout << "\nplease enter deposit amount?";
		cin >> amount;
	}deposit(vinfo, account_number, amount*-1);

}
double total_balanc(vector<infoaccount>vinfo)
{
	double count = 0;
	for (infoaccount sumbalanc : vinfo)
	{
		count += sumbalanc.account_balanc;
	}
	return count;
}
void show_total_balanc()
{
	vector<infoaccount>vinfo;

	vinfo = LoadCleintsDataFromFile(myfile);
	PrintAllClientsData(vinfo);
	cout << "\n\n\t\t\t\ttotal_balanc=" << total_balanc(vinfo) << endl;
}
short readtran()
{
	int the_choose_tran;
	cout << "choose what do you want to do ?[1 to 4]?";
	cin >> the_choose_tran;
	return  the_choose_tran;
}
enum entransactions
{
	Deposit = 1,
	withdraw = 2,
	total_balances = 3,
	main_menue = 4
	

};
void gobacktotrans()
{
	cout << "\n\npress any key to go back to mine manue..";
	system("pause>0");
	choose_item_from_manue_tran();
	
}
void chack_item_from_menue_tran(entransactions trans)
{


	switch (trans)
	{
	case entransactions::Deposit:
		system("cls");
		show_deposit();
		gobacktotrans();
		break;
	case entransactions::withdraw :
		system("cls");
		show_whithdraw();
		gobacktotrans();
		break;
	case entransactions::total_balances:
		system("cls");
		show_total_balanc();
		gobacktotrans();
		break;

	case  entransactions::main_menue:
		system("cls");
		choose_item_from_menue();;
		gobacktotrans();
		break;
	
	}


}
void choose_item_from_manue_tran()
{


	system("cls");
	cout << "___________________________________________" << endl;
	cout << "\n\t\ttransactions menue screen\t\t\t" << endl;
	cout << "___________________________________________" << endl;
	cout << "\t[1] deposit" << endl;
	cout << "\t[2] withdraw" << endl;
	cout << "\t[3] total balances" << endl;
	cout << "\t[4] main menue" << endl;
	
	cout << "___________________________________________" << endl;
	chack_item_from_menue_tran((entransactions)readtran());




}
//********************************************
void chack_item_from_menue(enmanue manue)
{


	switch (manue)
	{
	case enmanue::showallclint:
		system("cls");
		showprintallclientsdata();
		gobacktomenue();
		break;
	case enmanue::addclint:
		system("cls");
		showadddatanewline();
		gobacktomenue();

		break;
	case enmanue::deletclint:
		system("cls");
		showdelet_cliant_by_account_number();
		gobacktomenue();
		break;

	case enmanue::updetclint:
		system("cls");
		showupdate_cliant_by_account_number();
		gobacktomenue();
		break;
	case enmanue::findclint:
		system("cls");
		showfind_clint_by_account_number();
		gobacktomenue();
		break;
	case enmanue::transactions:
		system("cls");
		choose_item_from_manue_tran();
		break;

	case enmanue::endsystem:
		system("cls");
		showend();
		break;
	}


}
void choose_item_from_menue()
{


	system("cls");
	cout << "___________________________________________" << endl;
	cout << "\n\t\tmain menue screen\t\t\t" << endl;
	cout << "___________________________________________" << endl;
	cout << "\t[1] show client list" << endl;
	cout << "\t[2] add new client" << endl;
	cout << "\t[3] Delete client" << endl;
	cout << "\t[4] Update client info" << endl;
	cout << "\t[5] finde clint" << endl;
	cout << "\t[6] transactions" << endl;
	cout << "\t[7] exit" << endl;
	cout << "___________________________________________" << endl;
	chack_item_from_menue((enmanue)readmanue());




}
int main()
{
	choose_item_from_menue();
	system("pause>0");
	return 0;
}

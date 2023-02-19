#include <iostream>
#include <cstring>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cmath>

using namespace std;

// GLOBAL VARIABLES
string name[30];
string address[30];
string phone[30];
bool room[30]; // To identify if room is checked-in or empty
double service[30]; // To calculate add-on bill (room service)
int stay[30]; // days for stay-in ( limit: 7 days )

int early[30]; // days before someone reserve ( assuming user are determining the time ) ( if 0 assume no reserve )
string earlyName[30]; // To identify person who reserved

string payName[10000]; //list of payment name
double pay[10000] = {0}; //list of payment
int count = 0;

// INPUT FUNCTIONS - To prevent any invalid input
double transferInput(string input, bool ignoreDot = false, bool space = false); //convert string to int/double since using int/double as cin can cause error
string stringInput(string, string); //prevent empty input
string stringLower(string); // convert uppercase string to lowercase string as the built-in fx can only accept a character

// MAIN FUNCTIONS
void displayMenu(); // main menu
void displayRoom(); // display all room ( if alloted would display "-" instead of room number )
void checkIn(); // option check-in ( 2 mode: normal, reserved check-in )
void records(); // option records ( display selected customer information )
void checkOut(); // option check-out ( display bill including room service bill )
void modification(); // option modify, modify selected customer's check-in ( 2 mode: change room, extend/shorten check-in )
void roomService(); // option service ( display foods and beverages, bills included in check-out )
void reservation(); // option reservation ( reserve any room, 2 mode: reserve, withdraw reserve )
void startUI(); // interface before going into main menu
void checkIncome(); // check hotel's income

// FUNCTIONS 
void calPrice(double &, int); // calculate the price of the bill ( price*days )
void calService(double &, double); // calculate service bill ( service bill + item cost )
void displayReceipt(double &, double &); // display all bills in check-out
void displayInformation(string, string, string, int, int); // display customer's information
void addIncome(double, string); //add bills to list of payment


int main(){
	//initialize variables
	for (int i = 1; i <= 30; i++){
		room[i-1] = false;
		service[i-1] = 5;
		stay[i-1] = 1;
		early[i-1] = 0;
	}
	
	startUI();
	
	return 0;
}

void startUI(){
	system("cls");
	
	cout<<"\n\n\n\n\n\t\t\t\tHotelManagement.cpp"<<endl;
	cout<<"\t\t\t     Press any key to continue"<<endl;
	
	getch();
		
	displayMenu();
}

void displayMenu(){
	string pseudo;
	int option;
	
	system("cls");
	
	cout<<"------------------------------[ Hotel Management ]------------------------------"<<endl;
	cout<<"\n\t\t\t     1. Check-in Room"<<endl;
	cout<<"\t\t\t     2. Check-out Room"<<endl;
	cout<<"\t\t\t     3. Modify Check-in"<<endl;
	cout<<"\t\t\t     4. Reserve Room"<<endl;
	cout<<"\t\t\t     5. Customer Records"<<endl;
	cout<<"\t\t\t     6. Room Service"<<endl;
	cout<<"\t\t\t     7. Hotel Income"<<endl;
	cout<<"\t\t\t     8. Exit"<<endl;
	cout<<"\t\t\t     Enter number of choice: ";
	do {
		cin.sync();
		getline(cin,pseudo);
		option = transferInput(pseudo,false,true);
		if ( option < 1 or option > 8){
			cout<<"\t\t\t   Invalid choice, enter 1-8 only: ";
		}
	} while ( option < 1 or option > 8);
	
	switch(option){
		case 1:
			checkIn();
			break;
		case 2:
			checkOut();
			break;
		case 3:
			modification();
			break;
		case 4:
			reservation();
			break;
		case 5:
			records();
			break;
		case 6:
			roomService();
			break;
		case 7:
			checkIncome();
		case 8:
			break;
	}
}

void displayRoom(){
	
	for (int i = 1; i <= 30; i++){
		if (room[i-1]){
			int n = i/10;
			if (n< 1) n = 1; else n = 2;
			if (n == 2) cout <<"[-----]";
			else cout<<"[----]";
		}else cout<<"[ R"<<i<<" ]";
		if (i == 10 or i == 20 or i == 30) cout<<endl; else if (i < 10) cout<<"  "; else cout<<" ";
	}
	
	cout<<"\nRegular room: [11-30]"<<endl;
	cout<<"High-class room: [1-10]"<<endl;
	
}

void checkIn(){
	string pseudo, keyName, keyAddress, keyPhone, pseudodays, response;
	int option, days;
	
	system("cls");
	
	cout<<"------------------------------[ Hotel Management ]------------------------------\n"<<endl;
	
	displayRoom();
	
	cout<<"\n(Reserved check-in) mode? (y/n) "<<endl; //if (y) then only check-in to those who reserved
	do {
		cin.sync();
		getline(cin,response);
		response = stringLower(response);
		if (response != "y" and response != "n") cout<<"Invalid input, (Reserved check-in) mode? (y/n)"<<endl;
		
	} while (response != "y" and response != "n");
	
	if (response == "n"){
		// NORMAL MODE
		system("cls");
	
		cout<<"------------------------------[ Hotel Management ]------------------------------\n"<<endl;
	
		displayRoom();
		
		cout<<"\nSelect a room (select other than 1-30 to cancel)"<<endl;
		cin.sync();
		getline(cin,pseudo);
		option = transferInput(pseudo);
		if ( option < 1 or option > 30){
			cout<<"\nInvalid choice, check-in canceled"<<endl;
			cout<<"Press any key to return"<<endl;
			getch();
			displayMenu();
		}
		else {
			if (room[option-1]){
				cout<<"Room is already alloted by another customer"<<endl;
			}
			else {
				cout<<"Enter the amount of days to check-in"<<endl;
				do {
					cin.sync();
					getline(cin,pseudodays);
					days = transferInput(pseudodays);
					if (days > 7) cout<<"Maximum check-in is 7 days, enter again: ";
					if (days < 1) days = 1;
				} while (days > 7);
			
				if (early[option-1] > days or early[option-1] == 0){
					keyName = stringInput(keyName,"Enter customer's name: ");
					keyAddress = stringInput(keyAddress, "Enter customer's address: ");
					keyPhone = stringInput(keyPhone, "Enter customer's phone number: ");
					stay[option-1] = days;
					name[option-1].assign(keyName);
					address[option-1].assign(keyAddress);
					phone[option-1].assign(keyPhone);
					room[option-1] = true;	
				
					cout<<"\nRoom successfully checked in"<<endl;
				}
				else {
					cout<<"Check-in are currently collided with early reservation, check-in canceled"<<endl;
				}
					
			}
			cout<<"Press any key to return"<<endl;
			getch();
			displayMenu();
		
		}	
	}
	else {
		//RESERVATION CHECK-IN MODE
		
		system("cls");

		cout<<"------------------------------[ Hotel Management ]------------------------------\n"<<endl;
	
		displayRoom();
		
		cout<<"\nReserved rooms: ";
		for (int i = 1; i <= 30; i++){
			if (early[i-1] > 0)
				cout<<i<<", ";
		}
		cout<<endl;
		
		cout<<"\nEnter number of reserved room ( Choose other than 1 to 30 to cancel )"<<endl;
		cin.sync();
		getline(cin,pseudo);
		option = transferInput(pseudo);
		if ( option < 1 or option > 30){
			cout<<"\nInvalid choice, reserved check-in canceled"<<endl;
			cout<<"Press any key to return"<<endl;
			getch();
			displayMenu();
		}
		else {
			if (room[option-1]){
				cout<<"Room "<<option<<" hasn't check-out yet. Please head to (check-out) option"<<endl;
			}
			else if (early[option-1] == 0){
				cout<<"There are no reservation on this room"<<endl;
			}
			else {
				cout<<"Customer: "<<earlyName[option-1]<<", confirm customer? (y/n)"<<endl;
				do {
					cin.sync();
					getline(cin,response);
					response = stringLower(response);
					if (response != "y" and response != "n") cout<<"Invalid input, confirm customer? (y/n)"<<endl;
				} while (response != "y" and response != "n");
				
				if (response == "n"){
					cout<<"\nReservation check-in canceled"<<endl;
					cout<<"Press any key to return"<<endl;
					getch();
					displayMenu();
					
				}
					
				cout<<"Enter the amount of days to check-in"<<endl;
				do {
					cin.sync();
					getline(cin,pseudodays);
					days = transferInput(pseudodays);
					if (days > 7) cout<<"Maximum check-in is 7 days, enter again: ";
					if (days < 1) days = 1;
				} while (days > 7);
			
				keyName = stringInput(keyName,"Enter customer's name: ");
				keyAddress = stringInput(keyAddress, "Enter customer's address: ");
				keyPhone = stringInput(keyPhone, "Enter customer's phone number: ");
				earlyName[option-1].clear();
				early[option-1] = 0;
				stay[option-1] = days;					
				name[option-1].assign(keyName);
				address[option-1].assign(keyAddress);
				phone[option-1].assign(keyPhone);
				room[option-1] = true;	
				
				cout<<"\nRoom successfully checked in"<<endl;
					
			}
			cout<<"Press any key to return"<<endl;
			getch();
			displayMenu();
			}
		}
		
}


void records(){
	string pseudo;
	int option;
	
	system("cls");
	
	cout<<"------------------------------[ Hotel Management ]------------------------------\n"<<endl;
	
	displayRoom();
	
	cout<<"\nAlloted rooms: ";
	for (int i = 1; i <= 30; i++){
		if (room[i-1])
			cout<<i<<", ";
	}
	cout<<endl;
	
	cin.sync();
	cout<<"\nEnter room number to check customer's record"<<endl;
	cout<<"Choose other than 1-30 to cancel"<<endl;
	getline(cin,pseudo);
	option = transferInput(pseudo);
	if ( option < 1 or option > 30){
		cout<<"\nInvalid choice, record display canceled"<<endl;
		cout<<"Press any key to return"<<endl;
		getch();
		displayMenu();
	}
	else {
		if (room[option-1]){
			displayInformation(name[option-1],phone[option-1], address[option-1], stay[option-1], option);
		}
		else {
			cout<<"\nRoom "<<option<<" is not alloted, no details available"<<endl;
		}
		
		cout<<"\nPress any key to return"<<endl;
		getch();
		displayMenu();
	}
}

void checkOut(){
	string pseudo,response;
	int option;
	double bill = 0;
	
	system("cls");
	
	cout<<"------------------------------[ Hotel Management ]------------------------------\n"<<endl;
	
	displayRoom();
	
	cout<<"\nAlloted rooms: ";
	for (int i = 1; i <= 30; i++){
		if (room[i-1])
			cout<<i<<", ";
	}
	cout<<endl;
	
	cout<<"\nSelect a room to check-out ( pick other than 1-30 to cancel )"<<endl;
	cin.sync();
	getline(cin,pseudo);
	option = transferInput(pseudo);
	if ( option < 1 or option > 30){
		cout<<"\nInvalid choice, check-out canceled"<<endl;
		cout<<"Press any key to return"<<endl;
		getch();
		displayMenu();
	}
	else {
		if (room[option-1]){
				
			displayInformation(name[option-1],phone[option-1], address[option-1], stay[option-1], option);
			
			cout<<"Confirm check-out? (y/n)"<<endl;
			do {
				cin.sync();
				getline(cin,response);
				response = stringLower(response);
				if (response != "y" and response != "n") cout<<"Invalid input, confirm check-out? (y/n)"<<endl;
			} while (response != "y" and response != "n");
			
			if(response == "n"){
				cout<<"\nCheck-out canceled"<<endl;
				cout<<"Press any key to return"<<endl;
				getch();
				return displayMenu();
			}
			
			cout<<"\nRoom Bill: RM";
			if (option >= 1 and option <= 10){
				bill = 750;
				// bill for high-class room
			}
			else {
				bill = 420;
				// bill for regular room
			}
			calPrice(bill,stay[option-1]);
			displayReceipt(bill, service[option-1]);
			addIncome(bill+service[option]-1, name[option-1]);
			
			room[option-1] = false; //Emptying room details
			name[option-1].clear();
			address[option-1].clear();
			phone[option-1].clear();
			service[option-1] = 5;
			
			if (early[option-1] > 0){
				early[option-1] = early[option-1] - stay[option-1];
			}
			
			stay[option-1] = 1;
		}
		else {
			cout<<"\nRoom "<<option<<" is not alloted, no details available"<<endl;
		}
		
		cout<<"\nPress any key to return"<<endl;
		getch();
		displayMenu();
	}
}

void modification(){
	string pseudo, pseudodays, response;
	int option, days;
	
	system("cls");
	
	cout<<"------------------------------[ Hotel Management ]------------------------------\n"<<endl;
	
	cout<<"\nAlloted rooms: ";
	for (int i = 1; i <= 30; i++){
		if (room[i-1])
			cout<<i<<", ";
	}
	cout<<endl;
	
	cout<<"\nSelect a room to modify check-in (select other than 1-30 to cancel)"<<endl;
	cin.sync();
	getline(cin,pseudo);
	option = transferInput(pseudo);
	if ( option < 1 or option > 30){
		cout<<"\nModification canceled"<<endl;
		cout<<"Press any key to return"<<endl;
		getch();
		displayMenu();
	}
	else {
		if (room[option-1]){
			cout<<"Customer: "<<name[option-1]<<", confirm customer? (y/n)"<<endl;
			do {
				cin.sync();
				getline(cin,response);
				response = stringLower(response);
				if (response != "y" and response != "n") cout<<"Invalid input, confirm customer? (y/n)"<<endl;
			} while (response != "y" and response != "n");
			
			if (response == "n" ){
				cout<<"\nModification canceled"<<endl;
				cout<<"Press any key to return"<<endl;
				getch();
				return displayMenu();
			}
			
			int selected = option;
			
			cout<<"\n1. Extend/Shorten Check-in"<<endl;
			cout<<"2. Change Room"<<endl;
			cout<<"3. Exit"<<endl;
			cout<<"Enter number of choice:";
			do {
				cin.sync();
				getline(cin,pseudo);
				option = transferInput(pseudo);
				if ( option < 1 or option > 3){
					cout<<"Invalid choice, enter 1-3 only: ";
				}
			} while ( option < 1 or option > 3);
			
			switch(option){
				case 1:
					//EXTEND/SHORTEN MODE
					cout<<"Enter the amount of days to extend/shorten"<<endl;
					cin.sync();
					getline(cin,pseudodays);
					days = transferInput(pseudodays);
					if (stay[selected-1] + days < 1){
						cout<<"\nInvalid input, modification canceled"<<endl;
					}
					else if (stay[selected-1] + days > 7){
						cout<<"\nCheck-in limit is 7 days, modification canceled"<<endl;
					}
					else if (early[selected-1] == 0 or early[selected-1] > stay[selected-1] + days){
						stay[selected-1] = stay[selected-1] + days;
						cout<<"\nModification succeed"<<endl;
					}
					else {
						cout<<"\nModification currently collided with early reservation, modification canceled"<<endl;
					}
					break;
				case 2:
					//CHANGE ROOM MODE
					cout<<"Select a room to switch with (select other than 1-30 to cancel)"<<endl;
					cin.sync();
					getline(cin,pseudo);
					option = transferInput(pseudo);
					if ( option < 1 or option > 30){
						cout<<"\nModification canceled"<<endl;
					}
					else {
						if (selected == option){
							cout<<"Selected room is the same room.."<<endl;	
						}
						else if (room[option-1]){
							cout<<"Room is already alloted by another customer"<<endl;
						}
						else {
							if (stay[selected-1] < early[option-1] or early[option-1] == 0){
								cout<<"\nRoom change succeed"<<endl;
								
								//transfering details to new room
								name[option-1].assign(name[selected-1]);
								address[option-1].assign(address[selected-1]);
								phone[option-1].assign(phone[selected-1]);
								service[option-1] = service[selected-1];
								room[option-1] = true;
								
								//clearing details from previous room
								name[selected-1].clear();
								address[selected-1].clear();
								phone[selected-1].clear();
								service[selected-1] = 5;
								room[selected-1] = false;
							}
							else {
								cout<<"\nRoom change currently collided with early reservation, modification canceled"<<endl;
							}
						}
					}
					break;
				case 3:
					//EXIT
					cout<<"Modification canceled"<<endl;
					break;
			}
			
			cout<<"Press any key to return"<<endl;
			getch();
			displayMenu();
			
		}
		else {
			cout<<"\nNo customer alloted this room"<<endl;
			cout<<"Press any key to return"<<endl;
			getch();
			displayMenu();
		}
	}
}

void reservation(){
	string pseudo, pseudodays, response;
	int option, days;
	
	system("cls");
	
	cout<<"------------------------------[ Hotel Management ]------------------------------\n"<<endl;
	
	displayRoom();
	
	cout<<"\n(Withdraw Reservation) mode? (y/n)"<<endl; // if (y) then any selected reservation will be withdrawn
	do {
		cin.sync();
		getline(cin,response);
		response = stringLower(response);
		if (response != "y" and response != "n") cout<<"Invalid input, (Withdraw Reservation) mode? (y/n)"<<endl;
	} while (response != "y" and response != "n");
	
	system("cls");
	
	cout<<"------------------------------[ Hotel Management ]------------------------------\n"<<endl;
	
	displayRoom();
		
	cout<<"\nSelect a room (select other than 1-30 to cancel)"<<endl;
	cin.sync();
	getline(cin,pseudo);
	option = transferInput(pseudo);
	if ( option < 1 or option > 30){
		cout<<"\nInvalid choice, reservation mode canceled"<<endl;
		cout<<"Press any key to return"<<endl;
		getch();
		displayMenu();
	}
	else {
		if (response == "n"){
			//RESERVATION MODE
			
			if (early[option-1] != 0){
				cout<<"Sorry, reservation limit per room is 1"<<endl;
				cout<<"Press any key to return"<<endl;
				getch();
				return displayMenu();
			}
			
			cout<<"Enter the amount of days before actual check-in ( 0 to cancel )"<<endl;
			cin.sync();
			getline(cin,pseudodays);
			days = transferInput(pseudodays);
		
			if (stay[option-1] > days){
				cout<<"Sorry, reservation collided with current customer"<<endl;
			}
			else if ( days < 1){
				cout<<"Invalid input, reservation mode canceled"<<endl;
			}
			else {
				earlyName[option-1] = stringInput(earlyName[option-1],"Enter customer's name for reservation");
				early[option-1] = days;
				cout<<"\nRoom reservation succeed"<<endl;
			}
		}
		else {
			//WITHDRAW RESERVATION MODE
			
			if (early[option-1] > 0){
				cout<<"Withdraw reservation of "<<earlyName[option-1]<<" on room "<<option<<"? (y/n)"<<endl;
				do {
					cin.sync();
					getline(cin,response);
					response = stringLower(response);
					if (response != "y" and response != "n") cout<<"withdraw reservation? (y/n)"<<endl;
				} while (response != "y" and response != "n");
				if (response == "y"){
					earlyName[option-1].clear();
					early[option-1] = 0;
					cout<<"\nReservation canceled"<<endl;
				}
				else cout<<"\nReservation withdrawal canceled"<<endl;
			}
			else cout<<"\nThere is currently no reservation for this room"<<endl;
		}
		cout<<"Press any key to return"<<endl;
		getch();
		displayMenu();
	}	
}

void roomService(){
	string pseudo;
	int option;
	double bill = 0;
	double discount = 0; //for high-class room purpose
	
	string food[20] = 
	{ //food
	"Fish n Chip","Crispy Chicken Chop",
	"French Fries","Omelette Rice","Chicken Porridge",
	"Ratatouille","Mee Curry",
	"Chicken Rice","Steak Burger","Miso Ramen",
	//beverage
	"Coca-cola","Fanta","Sprite","ABC","Apple Juice",
	"Orange Juice","Pineapple Juice","Green tea","Milk tea","Mineral water"
	};
	
	double cost[20] =
	{ //food
	15.25, 16.50, 8.00, 12.20, 11.50, 14.30, 12.20, 11.50, 14.00, 16.00,
	//beverage
	3.00, 3.00, 3.00, 5.00, 7.00, 7.00, 7.50, 6.50, 6.50, 1.00
	};
	
	system("cls");
	
	cout<<"------------------------------[ Hotel Management ]------------------------------\n"<<endl;
	
	cout<<"\nAlloted rooms: ";
	for (int i = 1; i <= 30; i++){
		if (room[i-1])
			cout<<i<<", ";
	}
	cout<<endl;
	
	cin.sync();
	cout<<"Which room required room service? ( enter other than 1 to 30 to cancel )"<<endl;
	getline(cin,pseudo);
	option = transferInput(pseudo);
	if (option < 1 or option > 30){
		cout<<"\nInvalid choice, room service canceled"<<endl;
		cout<<"Press any key to return"<<endl;
		getch();
		displayMenu();
	}
	else {
		if (room[option-1]){
			int deliver = option-1;
			
			if (option >= 1 and option <= 10)
				discount = .3;
			
			system("cls");
	
			cout<<"------------------------------[ Hotel Management ]------------------------------\n"<<endl;
			
			cout<<"[ Room Service ]"<<endl;
			
			for (int i = 0; i < 20; i++){
				if (i == 0) cout<<"\nMain courses"<<endl;
				if (i == 10) cout<<"\nBeverages"<<endl;
				cout<<i+1<<". "<<food[i]<<" - RM"<<cost[i]<<endl;
			}
			
			cout<<"\nHigh-class room receive 30% discount"<<endl;
			while (true){
				cin.sync();
				cout<<"Choose 1-20 to add into service ( choose other than 1-20 to end )"<<endl;
				getline(cin,pseudo);
				option = transferInput(pseudo);
				if (option < 1 or option > 20){
					if (bill == 0) cout<<"\nNo item selected, room service canceled"<<endl;
					else cout<<"\nTotal bill: RM"<<bill<<endl; cout<<"Items successfully added, bill will be included in check-out bill"<<endl;
					break;
				}
				else {
					cout<<"+"<<food[option-1]<<" - RM"<<cost[option-1]*(1-discount)<<endl;
					//calculate the bill ( bill + cost )
					calService(bill, cost[option-1]*(1-discount));
				}
			}
			//bill added to service's bill
			calService(service[deliver], bill);
			
		}
		else {
			cout<<"\nRoom "<<option<<" is not alloted, no details available"<<endl;
		}
		
		cout<<"\nPress any key to return"<<endl;
		getch();
		displayMenu();
	}
	
}

void checkIncome(){
	system("cls");
	double total = 0;
	
	cout<<"------------------------------[ Hotel Management ]------------------------------\n"<<endl;
	
	cout<<"[ Hotel Current Income ]\n"<<endl;
	
	for (int i = 0; i < 10000; i++){
		if (!payName[i].empty()) {
			cout<<i+1<<". "<<payName[i]<<" - RM"<<pay[i]<<endl;
		}
		total += pay[i];
	}
	
	cout<<"\nTotal Income: RM"<<total<<endl;
	
	cout<<"\nPress any key to return"<<endl;
	getch();
	displayMenu();
	
	
}

void calPrice(double &price, int days){
	price = price*days;
}

void calService(double &service, double price){
	service = service+price;
}

void addIncome(double bill, string name){
	payName[count] = name;
	pay[count] = bill;
	count++;
}

void displayReceipt(double &bill, double &service){
	cout<<bill<<endl;
	cout<<"Tourism Tax: 2% | RM"<<round(bill*.02*100)/100<<endl;
	cout<<"Service Bill: RM"<<service<<endl;
	cout<<"Service Tax: 5% | RM"<<round(service*.05*100)/100<<endl;
	bill =round(bill*1.02*100)/100;
	service = round(service*1.05*100)/100;
	cout<<"Total: RM"<<bill+service<<endl;
	cout<<"Room successfully checked out"<<endl;
}

void displayInformation(string name, string phone, string address, int duration, int roomNum){
	cout<<"\nName: "<<name<<endl;
	cout<<"Address: "<<address<<endl;
	cout<<"Phone number: "<<phone<<endl;
	cout<<"Alloted room for "<<duration<<" days"<<endl;
	cout<<"Room type: ";
	if (roomNum >= 1 and roomNum <= 10)
		cout<<"High-class"<<endl;
	else
		cout<<"Regular"<<endl;
}

double transferInput(string input, bool ignoreDot, bool space){
	// transfer string to double
	// if ignoreDot is true it would not include dot as an obstacle ( allowing decimal value )
	// if space is true it would go to mid
	do {
		cin.sync();
		char inputChar[input.length()];
		bool isValue = true;
		
		strcpy(inputChar,input.c_str());
		//turn string to chars
		
		//detect if each char is not a number, if isValue = false, will demand to input until no erros
		for (int i = 0; i < input.length(); i++){
			if (isdigit(inputChar[i]) == false){
				if ((inputChar[i] != '.' and inputChar[i] != '-') or (inputChar[i] == '.' and ignoreDot == false) or ( i != 0 and inputChar[i] == '-'))
					isValue = false;
			}
		}
		if (input.empty())
				isValue = false;
		
		if (isValue == false ){
			if (space){
				cout<<"\t\t\t     ";
			}
			cout<<"Please put number only: ";
			getline(cin,input);
		}
		else
			break;
	} while (true);
	return stod(input);
}

string stringInput(string input, string question){
	//if input is empty, will demand input until no empty
	while (true) {
		cout<<question<<endl;
		cin.sync();
		getline(cin,input);
		if (input.empty()){
			cout<<"Invalid input, input is empty. ";
			continue;
		}
		char inputChar[input.length()];
		strcpy(inputChar,input.c_str());
		bool containString = false;
		for (int i = 0; i < input.length(); i++){
			if (inputChar[i] != ' ')
				containString =  true;
		}
		if (containString)
			break;
		else
			cout<<"Invalid input, input is empty. ";
	}
	
	
	
	return input;
}

string stringLower(string input){
	//transfer uppercase string to lowercase string
	
	char inputChar[input.length()];
	strcpy(inputChar,input.c_str());
	string newInput, current;
	
	for (int i= 0; i < input.length(); i++){
		current = (char) tolower(inputChar[i]);
		newInput.append(current);
	}
	
	return newInput;
}
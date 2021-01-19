// CS Board Project
// Restaurant Management System

// Header Files
#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<process.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

// Functions

class table
{
	public:
		int table_ID;
		int customer_ID;
		int R_ID;  	// reservation ID
		char status;

		table()
		{
			table_ID = 0;
			customer_ID = 0;
			status = 'E';
			R_ID = NULL;
		}

		void show_table()
		{
			cout << "Table ID: " << table_ID;
			cout << "\nCustomer ID: " << customer_ID;
			cout << "\nStatus: " << status;
			cout << "\nReservation ID: " << R_ID;
		}
} t[9];

class customer
{
	private:
		int customer_ID;
		char name[25];   // customer name
		int nop;         // number of people
		long long contact;    // customer contact number
		char modeofpay[10]; // mode of payment

	public:
		void get_details()
		{
			cout << "Enter your name: ";
			gets(name);
			cout << "Enter number of people sitting: ";
			cin >> nop;
			cout << "Enter contact number: ";
			cin >> contact;
			cout << "Enter mode of payment: ";
			gets(modeofpay);
		}

		void show_details()
		{
			cout << "Customer name: " << name;
			cout << "\nNumber of people sitting: " << nop;
			cout << "\nCustomer contact number: " << contact;
			cout << "\nMode of payment: " << modeofpay;
		}

		void generate_customerID()
		{
			randomize();
			customer_ID = random(100) + 1;
		}

		int return_customer_ID()
		{
			return customer_ID;
		}
};

void reserve(int x)
{
	int z, check = 0;
	fstream f1;
	f1.open("table.dat", ios :: binary | ios :: app);

	randomize();
	do {
		z = random(9) + 1;
		if(t[z-1].table_ID == 0)
		{	t[z-1].table_ID = z;
			t[z-1].customer_ID = x;
			t[z-1].status = 'R';
			t[z-1].R_ID = random(100) + 1;
			check = 0;
			cout << "\n\nYour table number is: " << z;
			cout << "\nYour reservation ID is: " << t[z-1].R_ID;
		}
		else
			check = 1;
	} while(check == 1);
	f1.write((char *)&t[z-1], sizeof(t[z-1]));

	f1.close();
}

void walk_in(int x)
{
	int z, check = 0;
	fstream f1;
	f1.open("table.dat", ios :: binary | ios :: app);

	do {
		cout << "Enter the table number: ";
		cin >> z;

		if(t[z-1].table_ID == 0 && t[z-1].status == 'E')
		{	t[z-1].table_ID = z;
			t[z-1].customer_ID = x;
			t[z-1].status = 'T';
			t[z-1].R_ID = NULL;
			check = 0;

		}
		else
		{
			cout << "Sorry, chosen table is unavailable. Please chose another table.\n\n";
			getch();
			check = 1;
		}
	} while(check == 1);
	f1.write((char *)&t[z - 1], sizeof(t[z - 1]));

	f1.close();
}

void seating()
{
	clrscr();
	fstream f1;
	f1.open("customer.dat", ios :: binary | ios :: app);

	int x, y;
	customer c;
	c.get_details();
	c.generate_customerID();
	x = c.return_customer_ID();
	cout << "\n\nYour customer ID is: " << x;
	getch();

	f1.write((char *)&c, sizeof(c));

	clrscr();
	cout << "\n\n1. Reserve table\n2. Be seated right away\n\n\n";
	cout << "Enter choice: ";
	cin >> y;

	switch(y)
	{
		case 1:
			reserve(x);
			getch();
			break;
		case 2:
			walk_in(x);
			getch();
			break;
		default:
			cout << "Invalid choice.";
			getch();
			exit(0);
	}

	f1.close();
}

void show_customers()
{
	fstream file;
	file.open("customer.dat", ios :: binary | ios :: in);
	customer c;

	if(!file)
	{
		cout << "Error. File not created.";
		getch();
		exit(1);
	}

	while(file.read((char *)&c, sizeof(c)))
	{
		c.show_details();
		cout << "\n\n";
		getch();
	}
}

void show_tables()
{
	fstream file;
	file.open("table.dat", ios :: binary | ios :: in);
	table t;

	if(!file)
	{
		cout << "Error. File not created.";
		getch();
		exit(1);
	}

	while(file.read((char *)&t, sizeof(t)))
	{
		t.show_table();
		cout << "\n\n";
		getch();
	}
}

class menuitem
{
	public:
		char item[25];
		int price;

		void showname()
		{       cout << item;
		}

		void showprice()
		{	cout << price;
		}

} m[5];

void menu()
{
	clrscr();
	fstream file;
	file.open("menu.dat", ios::binary | ios::in | ios::app);

	menuitem m1;

	if(!file)
	{
		cout << "Error. File not created.";
		getch();
		exit(0);
	}

	strcpy(m[0].item, "Pizza");
	m[0].price = 100;
	file.write((char *)&m[0], sizeof(m));

	strcpy(m[1].item, "Fries");
	m[1].price = 500;
	file.write((char *)&m[1], sizeof(m));

	strcpy(m[2].item, "Pasta");
	m[2].price = 250;
	file.write((char *)&m[2], sizeof(m));

	strcpy(m[3].item, "Pepsi");
	m[3].price = 50;
	file.write((char *)&m[3], sizeof(m));

	strcpy(m[4].item, "Fanta");
	m[4].price = 60;
	file.write((char *)&m[4], sizeof(m));

	file.seekg(0);
	int p;
	cout << "\t\t\t\t***** MENU *****\n\n\n";
	cout << "Item Number\t\t\tItem Name\t\t\tItem Price\n\n";
	for(int i=0; i<5; i++)
	{
		p = file.tellg();
		cout <<"   " << i+1 << "\t\t\t\t  ";
		file.read((char *)&m1, sizeof(m1));
		m1.showname();
		cout << "\t\t\t\t  Rs ";
		m1.showprice();
		cout << endl;
		file.seekg(p+sizeof(m), ios :: beg);
	}
}

class bill
{
	public:
		int table_no;
		int customer_ID;
		char modeofpay[15]; // mode of payment
		int tc;               // total cost

};

void order()
{
	clrscr();
	fstream f1, f2;
	f1.open("Bill.dat", ios :: binary | ios :: app);
	f2.open("table.dat", ios :: binary | ios :: in);

	int cust_ID, inum;
	table t;
	bill b;
	int flag = 0;
	char y;

	cout << "Enter customer ID: ";
	cin >> cust_ID;

	do
	{       clrscr();
		while(f2.read((char*)&t, sizeof(t)))
		{       if(t.customer_ID == cust_ID)
			{       b.customer_ID = cust_ID;
				b.table_no = t.table_ID;
				flag = 1;
				break;
			}
			else
				flag = 0;
		}

		if(flag == 0)
		{
			cout << "\n\nInvalid customer ID. Press enter to try again.";
			getch();
		}

	} while(flag == 0);

	menu();
	do {
		int p = 0;
		cout << "Enter the number of item you would like to order: ";
		cin >> inum;
		p = sizeof(menuitem) * (inum - 1);


}

void customer()
{
	clrscr();
	//seating();
       //	getch();
       //	order();
       menu();
}

int main()
{
	clrscr();
	cout << "\t\t\t\t***** RESTAURANT *****\n\n\n";
	customer();
	//clrscr();
	//show_customers();
	//clrscr();
	//show_tables();

	getch();
	return 0;
}

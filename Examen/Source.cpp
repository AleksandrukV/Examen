#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

struct Date_of_receipt
{
	int day;
	int mouth;
	int year;
};

struct Expiration_date
{
	int day;
	int mouth;
	int year;
};

struct Sklad
{
	char name[20];
	char producer[20];
	int price;
	char tovar_groupe[20];
	Date_of_receipt date;
	Expiration_date ex_date;
};

Sklad InitSklad(Sklad sklad, FILE* f)
{
	fscanf(f, "%s", sklad.name);
	fscanf(f, "%s", sklad.producer);
	fscanf(f, "%i", &sklad.price);
	fscanf(f, "%s", sklad.tovar_groupe);
	fscanf(f, "%i", &sklad.date.day);
	fscanf(f, "%i", &sklad.date.mouth);
	fscanf(f, "%i", &sklad.date.year);
	fscanf(f, "%i", &sklad.ex_date.day);
	fscanf(f, "%i", &sklad.ex_date.mouth);
	fscanf(f, "%i", &sklad.ex_date.year);
	return sklad;
}

Sklad* CreateSklads(int size)
{
	Sklad* sklads = new Sklad[size];
	return sklads;
}

void Delete(Sklad* sklads)
{
	delete[] sklads;
}

Sklad* ReCreateSklads(Sklad* sklads, int size)
{
	Sklad* newsklads = CreateSklads(size);
	for (int i = 0; i < size - 1; i++)
	{
		newsklads[i] = sklads[i];
	}
	delete[] sklads;
	return newsklads;
}

Sklad* InitSklads(FILE* f, Sklad* sklads, int& size)
{
	char c = fgetc(f);
	int count = 0;
	while (c != EOF)
	{
		fseek(f, -1, SEEK_CUR);
		sklads = ReCreateSklads(sklads, ++size);
		sklads[count] = InitSklad(sklads[count], f);
		c = fgetc(f);
		count++;
	}
	return sklads;
}

Sklad InputSklad(Sklad sklad)
{
	cin.ignore();
	cout << "Enter name: ";
	cin.getline(sklad.name, 20);
	if (sklad.name[0] == NULL)
		strcpy(sklad.name, "0");
	cout << "Enter produser: ";
	cin.getline(sklad.producer, 20);
	if (sklad.producer[0] == NULL)
		strcpy(sklad.producer, "0");
	cout << "Enter price: ";
	cin >> sklad.price;
	cin.ignore();
	cout << "Enter tovar_groupe: ";
	cin.getline(sklad.tovar_groupe, 20);
	if (sklad.tovar_groupe[0] == NULL)
		strcpy(sklad.tovar_groupe, "0");
	cout << "Enter Date of receipt - day: ";
	cin >> sklad.date.day;
	cout << "Enter Date of receipt - mouth: ";
	cin >> sklad.date.mouth;
	cout << "Enter Date of receipt - year: ";
	cin >> sklad.date.year;
	cout << "Enter Expiration date - day: ";
	cin >> sklad.ex_date.day;
	cout << "Enter Expiration date - mouth: ";
	cin >> sklad.ex_date.mouth;
	cout << "Enter Expiration date - year: ";
	cin >> sklad.ex_date.year;
	cin.ignore();
	return sklad;
}

void AddSkladToFile(FILE* f, Sklad sklad)
{
	fprintf(f, "%s ", sklad.name);
	fprintf(f, "%s ", sklad.producer);
	fprintf(f, "%i ", sklad.price);
	fprintf(f, "%s ", sklad.tovar_groupe);
	fprintf(f, "%i ", sklad.date.day);
	fprintf(f, "%i ", sklad.date.mouth);
	fprintf(f, "%i ", sklad.date.year);
	fprintf(f, "%i ", sklad.ex_date.day);
	fprintf(f, "%i ", sklad.ex_date.mouth);
	fprintf(f, "%i", sklad.ex_date.year);
}

Sklad* AddTovar(FILE* f, Sklad* sklads, int& size)
{
	Sklad sklad;
	strcpy(sklad.name, "0");
	sklad = InputSklad(sklad);
	for (int i = 0; i < size; i++)
	{
		AddSkladToFile(f, sklads[i]);
		fprintf(f, "%c", '\n');
	}
	AddSkladToFile(f, sklad);
	sklads = ReCreateSklads(sklads, ++size);
	sklads[size - 1] = sklad;
	return sklads;
}

void PrintSklad(Sklad sklad)
{
	cout << "\tName - " << sklad.name << endl;
	cout << "\tProducer - " << sklad.producer << endl;
	cout << "\tPrice - " << sklad.price << endl;
	cout << "\tTovar groupe - " << sklad.tovar_groupe << endl;
	cout << "\tDate of receipt: day - " << sklad.date.day << endl;
	cout << "\tDate of receipt: mouth - " << sklad.date.mouth << endl;
	cout << "\tDate of receipt: year - " << sklad.date.year << endl;
	cout << "\tExpiration_date: day - " << sklad.ex_date.day << endl;
	cout << "\tExpiration_date: mouth - " << sklad.ex_date.mouth << endl;
	cout << "\tExpiration_date: year - " << sklad.ex_date.year << endl;
}

void PrintSklads(Sklad* sklads, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "Sklad " << i + 1 << "st" << endl;
		PrintSklad(sklads[i]);
	}
}

Sklad* DeleteSklad(FILE* f, Sklad* sklads, int& size)
{
	sklads = ReCreateSklads(sklads, size--);
	for (int i = 0; i < size; i++)
	{
		AddSkladToFile(f, sklads[i]);
		if (i < size - 1)
			fprintf(f, "%c", '\n');
	}
	return sklads;
}

int Search_For_Name(Sklad* sklads, int size)
{
	char str[20];
	str[0] = '1';
	while (str[0] != '0')
	{
		cout << "Enter search name:" << endl;
		cin.getline(str, 20);
		for (int i = 0; i < size; i++)
		{
			if (strcmp(sklads[i].name, str) == 0)
				return i;
		}
		if (str[0] != '0')
			cout << "No such name found.\n\tEnter 0 to exit." << endl;
	}
	return -1;
}

int Search_For_Producer(Sklad* sklads, int size)
{
	char str[20];
	str[0] = '1';
	while (str[0] != '0')
	{
		cout << "Enter search producer:" << endl;
		cin.getline(str, 20);
		for (int i = 0; i < size; i++)
		{
			if (strcmp(sklads[i].producer, str) == 0)
				return i;
		}
		if (str[0] != '0')
			cout << "No such prodecer found.\n\tEnter 0 to exit." << endl;
	}
	return -1;
}

int Search_For_Tovar_groupe(Sklad* sklads, int size)
{
	char str[20];
	str[0] = '1';
	while (str[0] != '0')
	{
		cout << "Enter search tovar groupe:" << endl;
		cin.getline(str, 20);
		for (int i = 0; i < size; i++)
		{
			if (strcmp(sklads[i].tovar_groupe, str) == 0)
				return i;
		}
		if (str[0] != '0')
			cout << "No such tovar groupe found.\n\tEnter 0 to exit." << endl;
	}
	return -1;
}

int Search_For_Price(Sklad* sklads, int size)
{
	int temp = -1;
	while (temp != 0)
	{
		cout << "Enter search price:" << endl;
		cin >> temp;
		for (int i = 0; i < size; i++)
		{
			if (sklads[i].price == temp)
				return i;
		}
		if (temp != 0)
			cout << "No such price found.\n\tEnter 0 to exit." << endl;
	}
	return -1;
}

int Search_For_Date_of_receipt(Sklad* sklads, int size)
{
	int temp = -1;
	int temp2 = -1;
	int temp3 = -1;
	while (temp != 0 && temp2 != 0 && temp3 != 0)
	{
		cout << "Enter search Date of receipt:" << endl;
		cout << "day: ";
		cin >> temp;
		cout << "mouth: ";
		cin >> temp2;
		cout << "year: ";
		cin >> temp3;
		for (int i = 0; i < size; i++)
		{
			if (sklads[i].date.day == temp && sklads[i].date.mouth == temp2 && sklads[i].date.year == temp3)
				return i;
		}
		if (temp != 0 && temp2 != 0 && temp3 != 0)
			cout << "No such Date of receipt found.\n\tEnter 0 to exit." << endl;
	}
	return -1;
}

int Search_For_Expiration_date(Sklad* sklads, int size)
{
	int temp = -1;
	int temp2 = -1;
	int temp3 = -1;
	while (temp != 0 && temp2 != 0 && temp3 != 0)
	{
		cout << "Enter search Expiration date:" << endl;
		cout << "day: ";
		cin >> temp;
		cout << "mouth: ";
		cin >> temp2;
		cout << "year: ";
		cin >> temp3;
		for (int i = 0; i < size; i++)
		{
			if (sklads[i].ex_date.day == temp && sklads[i].ex_date.mouth == temp2 && sklads[i].ex_date.year == temp3)
				return i;
		}
		if (temp != 0 && temp2 != 0 && temp3 != 0)
			cout << "No such Expiration date found.\n\tEnter 0 to exit." << endl;
	}
	return -1;
}

Sklad* Sort_by_Price(FILE* f, Sklad* sklads, int size)
{
	bool verify;
	for (int i = 1; i < size; i++)
	{
		verify = 0;
		for (int j = 0; j < size-i; j++)
		{
			if (sklads[j].price > sklads[j+1].price)
			{
				swap(sklads[j], sklads[j + 1]);
				verify = 1;
			}
		}
		if (verify == 0)
			break;
	}
	for (int i = 0; i < size; i++)
	{
		AddSkladToFile(f, sklads[i]);
		if (i<size-1)
			fprintf(f, "%c", '\n');
	}
	return sklads;
}

Sklad* Sort_by_tovar_groupe(FILE* f, Sklad* sklads, int size)
{
	bool verify;
	for (int i = 1; i < size; i++)
	{
		verify = 0;
		for (int j = 0; j < size - i; j++)
		{
			if (strcmp(sklads[j].tovar_groupe, sklads[j + 1].tovar_groupe)==1)
			{
				swap(sklads[j], sklads[j + 1]);
				verify = 1;
			}
		}
		if (verify == 0)
			break;
	}
	for (int i = 0; i < size; i++)
	{
		AddSkladToFile(f, sklads[i]);
		if (i < size - 1)
			fprintf(f, "%c", '\n');
	}
	return sklads;
}

int main()
{
	FILE* f = fopen("d:\\temp\\file.txt", "r");
	int size = 0;
	Sklad* sklads = CreateSklads(size);
	sklads = InitSklads(f, sklads, size);
	int menu;
	while (1)
	{
		cout << "Enter menu number:" << endl;
		cin >> menu;
		if (menu == 1)
		{
			FILE* f2 = fopen("d:\\temp\\file.txt", "w");
			sklads = AddTovar(f2, sklads, size);
			fclose(f2);
		}
		else if (menu == 2)
		{
			FILE* f2 = fopen("d:\\temp\\file.txt", "w");
			sklads = DeleteSklad(f2, sklads, size);
			fclose(f2);
		}
		else if (menu == 3)
		{
			int search_menu = 0;
			cout << "Enter search_menu number:\n1 - search by name\n2 - search by producer\n3 - search by price\n4 - search by product group\n5 - search by date of receipt\n6 - search by expiration date" << endl;
			cin >> search_menu;
			cin.ignore();
			int temp=-1;
			if (search_menu == 1)
			{
				temp = Search_For_Name(sklads, size);
				if (temp >= 0)
					PrintSklad(sklads[temp]);
			}
			else if (search_menu == 2)
			{
				temp = Search_For_Producer(sklads, size);
				if (temp >= 0)
					PrintSklad(sklads[temp]);
			}
			else if (search_menu == 3)
			{
				temp = Search_For_Price(sklads, size);
				if (temp >= 0)
					PrintSklad(sklads[temp]);
			}
			else if (search_menu == 4)
			{
				temp = Search_For_Tovar_groupe(sklads, size);
				if (temp >= 0)
					PrintSklad(sklads[temp]);
			}
			else if (search_menu ==5)
			{
				temp = Search_For_Date_of_receipt(sklads, size);
				if (temp >= 0)
					PrintSklad(sklads[temp]);
			}
			else if (search_menu == 6)
			{
				temp = Search_For_Expiration_date(sklads, size);
				if (temp >= 0)
					PrintSklad(sklads[temp]);
			}
		}
		else if (menu == 4)
		{
			int sort_menu = -1;
			cout << "Enter sort_menu:\n1 - sorting by price\n2 - sorting by tovar group" << endl;
			cin >> sort_menu;
			cin.ignore();
			if (sort_menu == 1)
			{
				FILE* f2 = fopen("d:\\temp\\file.txt", "w");
				sklads = Sort_by_Price(f2,sklads, size);
				fclose(f2);
			}
			if (sort_menu == 2)
			{
				FILE* f2 = fopen("d:\\temp\\file.txt", "w");
				sklads = Sort_by_tovar_groupe(f2, sklads, size);
				fclose(f2);
			}
		}
		else if (menu == 0)
			break;
	}

	PrintSklads(sklads, size);
	Delete(sklads);
	fclose(f);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// define clear console based on platform
void clear_console()
{
#ifdef _WIN32
	system("cls");
#elif __linux__
	system("clear");
#endif
}

// Car information data holder

// enum to spicify wich type of currency (supported by program)
enum Currency
{
	Peso,
	CanadianDollar,
	Balboa,
	Colon
};

// enum to spicify wich type of transmission the car use
enum TransmissionType
{
	Manual,
	Automatic,
};

// enum to spicify wich type of driving system the car use
enum DrivingSystemType
{
	TwoWheelDrive,
	FourWheelDrive
};

// enum to spicify wich type of driving system the car use
enum ConditionType
{
	BrandNew,
	Used,
	Both
};

// struct to hold search for car result contains 5 cars in array of struct Car
struct SearchResult
{
	struct Car *car[5];
};

// struct to hold Engine data
struct EngineData
{
	char *name;
};

// struct to hold Chassis data

struct ChassisData
{
	char *name;
};

// struct to hold Exterior data
struct ExteriorData
{
	char *name;
};

// struct to hold Steating data
struct SteatingAndTrimData
{
	char *name;
};

// struct to hold Dimension data
struct DimensionData
{
	float width, height, length;
};

// struct to hold FuelEconomy data
struct FuelEconomyData
{
	char *name;
};


/*
	struct to hold car data
*/
struct Car
{
	char *Model;
	char *Manufacturer;
	bool isColorUpgraded;
	char *Color;
	int Mileage;
	int price;
	bool isTransmissionUpgraded;
	enum TransmissionType Transmission;
	struct EngineData *Engine;
	struct ChassisData *Chassis;
	struct ExteriorData *Exterior;
	struct SteatingAndTrimData *SeatingAndTrim;
	bool Airbags;
	int AirbagsCount;
	struct FuelEconomyData *FuelEconomy;
	bool Hybrid;
	bool FullyElectrified;
	bool isAutomaticParkingAssistanceUpgraded;
	bool AutomaticParkingAssistance;
	bool NightVisionAssistance;
	bool isCruiseControl;
	bool CruiseControl;
	enum DrivingSystemType DrivingSystem;
	bool HillAssist;
	bool isTirePressureMonitoringSystemUpgreded;
	bool TirePressureMonitoringSystem;
	bool VoiceCommand;
	bool LaneChangeIndicator;
	bool ForwardCollisionWarningSensor;
	bool BlindSpotWarningSensors;
	bool SeatHeater;
	bool SteeringHeater;
	enum ConditionType Condition;
	char *countries[5];
};

/*
	struct to hold FinanceManager data
*/
struct FinanceManagerData
{
	char *FirstName, LastName;
	int PhoneNumber;
	int CellPhoneNumber;
	char *Address;
	char *DateOfEmployment;
	int YearsOfExperience;
};

/*
	struct to hold GeneralManager data
*/
struct GeneralManagerData
{

	int PhoneNumber;
	int CellPhoneNumber;
	char *Address;
	char *Email;
	char *DateOfEmployment;
	int YearsOfExperience;
};

/*
	struct to hold Branch data
*/
struct Branch
{
	// public information
	char *name;
	char *Address;
	char *PostalCode;
	char *PhoneNumber;
	char *FaxNumber;
	char *CustomerServiceEmail;
	char *NameOfTheGeneralManager;
	struct Car *cars[10];

	// confidential information
	struct GeneralManagerData *GeneralManager;
	struct FinaceManagerData *FinaceManager;
	int AvailableCars;
	char *AvailableCarsInformation;
};

/*
	struct to hold Dealership data
*/
struct Dealership
{
	char *name;
	struct Branch *Branches[3];
	int Sales;
};

/*
	struct to hold two vector data like min and max of value or x or y for position data type
*/
struct Vector2
{
	int min, max;
};

/*
	struct to hold Search data
*/
struct SearchModel
{
	char *CarModel;
	char *CarManufacturer;
	enum ConditionType CarCondition;
	struct Vector2 RangeOfMileage;
	struct Vector2 PriceRange;
	char *Color;
};

struct SearchModel *search;
struct Dealership dealership;
struct Dealership *dealershipPtr = &dealership;
int branch_index;
int car_index;
int peso = 18.01;
int canadianDollar = 1.35;
int balboa = 1;
int colon = 533.81;
float currentCurrency = 1;

/*
	Convert the program currency usd to branches currency
*/
void convert_price(enum Currency currency)
{
	switch (currency)
	{
	case 0:
		currentCurrency = peso;
		break;
	case 1:
		currentCurrency = canadianDollar;
		break;
	case 2:
		currentCurrency = balboa;
		break;
	case 3:
		currentCurrency = colon;
		break;
	default:
		currentCurrency = 1;
		break;
	}
}

/*
	Compare two char pointers return 0 if the two texts are similar
*/
int compare_string(char *first, char *second)
{
	while (*first == *second)
	{
		if (*first == '\0' || *second == '\0')
			break;

		first++;
		second++;
	}
	if (*first == '\0' && *second == '\0')
		return 0;
	else
		return -1;
}

/*
	Setbranch car list to null
*/
void create_branch_car_list(struct Branch *branch)
{
	branch->cars[0] = NULL;
	branch->cars[1] = NULL;
	branch->cars[2] = NULL;
	branch->cars[3] = NULL;
	branch->cars[4] = NULL;
	branch->cars[5] = NULL;
	branch->cars[6] = NULL;
	branch->cars[7] = NULL;
	branch->cars[8] = NULL;
	branch->cars[9] = NULL;
}

/*
	Allocate memory for car struct and initialize it with the given args
*/
struct Car *create_car(char *model, char *manufacturer, char *color, int price, enum TransmissionType transmission, enum ConditionType condition)
{
	struct Car *car = malloc(sizeof(struct Car));
	car->Model = model;
	car->Color = color;
	car->Manufacturer = manufacturer;
	car->price = price;
	car->Transmission = transmission;
	car->Condition = condition;
	return car;
}

/*
	Initialize branch data for Usa Washington
*/
struct Branch *create_usa_branch()
{
	struct Branch *branch = malloc(sizeof(struct Branch));

	// Allocate memory for branch
	create_branch_car_list(branch);

	// Set branch data
	branch->name = "USA - Washington DC";
	branch->Address = "13806 Hwy 99, Lynnwood, WA 98087, United States";
	branch->PhoneNumber = "+1 425-697-6969";
	branch->FaxNumber = "202-366-3244";
	branch->PostalCode = "98071";
	branch->CustomerServiceEmail = "usa.washington@support.com";
	branch->NameOfTheGeneralManager = "Muriel Bowser";

	// Set branch car list
	branch->cars[0] = create_car("bmw x1", "bmw", "Utah Orange Metallic", 43350, Automatic, BrandNew);
	branch->cars[1] = create_car("mercedes gle", "mercedes", "Black Metallic", 57700, Automatic, BrandNew);
	branch->cars[2] = create_car("ford raptor", "ford", "White", 65375, Automatic, BrandNew);
	branch->cars[3] = create_car("honda civic", "honda", "Cyan", 15950, Automatic, Used);
	branch->cars[4] = create_car("skoda octavia", "skoda", "Blue Metallic", 28270, Automatic, BrandNew);

	return branch;
}

/*
	Initialize branch data for Canada Ottawa
*/
struct Branch *create_canada_branch()
{
	struct Branch *branch = malloc(sizeof(struct Branch));

	// Allocate memory for branch
	create_branch_car_list(branch);

	// Set branch data
	branch->name = "Canada - Ottawa";
	branch->Address = "939 St. Laurent Blvd, Ottawa, ON K1K 3B1, Canada";
	branch->PhoneNumber = "+1 613-741-0741";
	branch->FaxNumber = "613-783-5958";
	branch->PostalCode = "K0A";
	branch->CustomerServiceEmail = "canada.ottawa@support.com";
	branch->NameOfTheGeneralManager = "Mark Sutcliffe";

	// Set branch car list
	branch->cars[0] = create_car("bmw x1", "bmw", "Utah Orange Metallic", 43350, Automatic, BrandNew);
	branch->cars[1] = create_car("mercedes gle", "mercedes", "Black Metallic", 57700, Automatic, BrandNew);
	branch->cars[2] = create_car("ford raptor", "ford", "White", 65375, Automatic, BrandNew);
	branch->cars[3] = create_car("honda civic", "honda", "Cyan", 15950, Automatic, Used);
	branch->cars[4] = create_car("skoda octavia", "skoda", "Blue Metallic", 28270, Automatic, BrandNew);

	return branch;
}

/*
	Initialize branch data for Mexico Mexico City
*/
struct Branch *create_mexico_branch()
{
	struct Branch *branch = malloc(sizeof(struct Branch));

	// Allocate memory for branch
	create_branch_car_list(branch);

	// Set branch data
	branch->name = "Mexico - Mexico City";
	branch->Address = "Vasco de Quiroga 2109, Santa Fe, Zedec Sta Fé, Álvaro Obregón, 01219 Ciudad de México, CDMX, Mexico";
	branch->PhoneNumber = "+52 55 5081 2300";
	branch->FaxNumber = "844-528-6611";
	branch->PostalCode = "00810";
	branch->CustomerServiceEmail = "mexico.mexicocity@support.com";
	branch->NameOfTheGeneralManager = "Claudia Sheinbaum";

	// Set branch car list
	branch->cars[0] = create_car("bmw x1", "bmw", "Utah Orange Metallic", 43350, Automatic, BrandNew);
	branch->cars[1] = create_car("mercedes gle", "mercedes", "Black Metallic", 57700, Automatic, BrandNew);
	branch->cars[2] = create_car("ford raptor", "ford", "White", 65375, Automatic, BrandNew);
	branch->cars[3] = create_car("honda civic", "honda", "Cyan", 15950, Automatic, Used);
	branch->cars[4] = create_car("skoda octavia", "skoda", "Blue Metallic", 28270, Automatic, BrandNew);

	return branch;
}

/*
	Initialize branch data for Panama Panama City
*/
struct Branch *create_panama_branch()
{
	struct Branch *branch = malloc(sizeof(struct Branch));

	// Allocate memory for branch
	create_branch_car_list(branch);


	// Set branch data
	branch->name = "Panama - Panama City";
	branch->Address = "Vía Ricardo J. Alfaro, Panamá, Panama";
	branch->PhoneNumber = "+507 392-9326";
	branch->FaxNumber = "507-5830";
	branch->PostalCode = "0801";
	branch->CustomerServiceEmail = "panama.panamacity@support.com";
	branch->NameOfTheGeneralManager = "Greg Brudnicki";

	// Set branch car list
	branch->cars[0] = create_car("bmw x1", "bmw", "Utah Orange Metallic", 43350, Automatic, BrandNew);
	branch->cars[1] = create_car("mercedes gle", "mercedes", "Black Metallic", 57700, Automatic, BrandNew);
	branch->cars[2] = create_car("ford raptor", "ford", "White", 65375, Automatic, BrandNew);
	branch->cars[3] = create_car("honda civic", "honda", "Cyan", 15950, Automatic, Used);
	branch->cars[4] = create_car("skoda octavia", "skoda", "Blue Metallic", 28270, Automatic, BrandNew);

	return branch;
}

/*
	Initialize branch data for Costa Rica San José
*/
struct Branch *create_costa_rica_branch()
{
	struct Branch *branch = malloc(sizeof(struct Branch));

	// Allocate memory for branch
	create_branch_car_list(branch);

	// Set branch data
	branch->name = "Costa Rica - San José";
	branch->Address = "Vía Ricardo J. Alfaro, Panamá, Panama";
	branch->PhoneNumber = "+507 392-9326";
	branch->FaxNumber = "339-581";
	branch->PostalCode = "94088";
	branch->CustomerServiceEmail = "costarica.sanjose@support.com";
	branch->NameOfTheGeneralManager = "Matt Mahan";

	// Set branch car list
	branch->cars[0] = create_car("bmw x1", "bmw", "Utah Orange Metallic", 43350, Automatic, BrandNew);
	branch->cars[1] = create_car("mercedes gle", "mercedes", "Black Metallic", 57700, Automatic, BrandNew);
	branch->cars[2] = create_car("ford raptor", "ford", "White", 65375, Automatic, BrandNew);
	branch->cars[3] = create_car("honda civic", "honda", "Cyan", 15950, Automatic, Used);
	branch->cars[4] = create_car("skoda octavia", "skoda", "Blue Metallic", 28270, Automatic, BrandNew);

	return branch;
}

void search_for_car()
{
	clear_console();

	printf("Search for car\n");
	printf("--------------------------------\n");
	printf("Enter car model: ");

#ifdef _WIN32
	char input[24];
	scanf("%s", input);
#elif __linux__
	char *input = malloc(sizeof(char) * (24 + 1));
	scanf("%s", input);
#endif

	for (int l = 0; l < sizeof(dealershipPtr->Branches) / sizeof(dealershipPtr->Branches[0]); l++)
	{
		struct Branch *branch = dealershipPtr->Branches[l];
		if (branch != NULL)
		{
			printf("\nCar matches in branch %s \n", branch->name);
			for (int i = 0; i < sizeof(branch->cars) / sizeof(branch->cars[0]); i++)
			{
				struct Car *car = branch->cars[i];
				if (car != NULL)
				{
					if (strcmp(car->Model, input) == 0)
						printf(" - Car Model: %s \n", car->Model);
				}
			}
		}
	}

	printf("--------------------------------\n");
	printf("0) Back\n");
	int action;
	scanf("%d", &action);
}

void print_branch_cars()
{
	clear_console();
	int input;

	for (int l = 0; l < sizeof(dealershipPtr->Branches) / sizeof(dealershipPtr->Branches[0]); l++)
	{
		struct Branch *branch = dealershipPtr->Branches[l];
		if (branch != NULL)
		{
			printf("  Branch %s Cars \n", branch->name);
			printf("--------------------------------\n");
			for (int i = 0; i < sizeof(branch->cars) / sizeof(branch->cars[0]); i++)
			{
				struct Car *car = branch->cars[i];
				if (car != NULL)
				{
					printf(" - Model: %s \n", car->Model);
					printf(" - Manufacturer: %s \n", car->Manufacturer);
					printf(" - Color: %s \n", car->Color);
					printf(" - Price: $%d \n", car->price);
					if (car->Transmission == 0)
					{
						printf(" - Transmission: Manual \n");
					}
					else
					{
						printf(" - Transmission: Automatic \n");
					}
					if (car->Condition == 0)
					{
						printf(" - Condition: Brand new \n");
					}
					else
					{
						printf(" - Condition: Used \n");
					}
					printf("--------------------------------\n");
				}
			}
		}
	}
	printf("\n0) Back\n");

	scanf("%d", &input);
}


// print branch data
void print_branches()
{
	clear_console();
	int input;

	printf("Branches \n");
	printf("--------------------------------\n");

	for (int i = 0; i < sizeof(dealershipPtr->Branches) / sizeof(dealershipPtr->Branches[0]); i++)
	{
		struct Branch *branch = dealershipPtr->Branches[i];
		// printf("Car pointer is: %p\n", (void *) car);
		if (branch != NULL)
		{
			printf("%d) Branch name: %s\n", i + 1, branch->name);
			printf("-- Branch address: %s\n", branch->Address);
			printf("-- Postal code: %s\n", branch->PostalCode);
			printf("-- Phone number: %s\n", branch->PhoneNumber);
			printf("-- Fax number: %s\n", branch->FaxNumber);
			printf("-- Customer service email: %s\n", branch->CustomerServiceEmail);
			printf("-- General manager: %s\n\n", branch->NameOfTheGeneralManager);
		}
	}

	printf("--------------------------------\n");
	printf("0) Exit\n");

	scanf("%d", &input);
}

void transfare_car()
{
}

void add_car()
{
	clear_console();

	printf("Enter car model\n");
	printf("--------------------------------\n");
	printf("Your input: ");

#ifdef _WIN32
	char input[24];
	scanf("%s", input);
#elif __linux__
	char *input = malloc(sizeof(char) * (24 + 1));
	scanf("%s", input);
#endif

	struct Branch *branch = dealershipPtr->Branches[branch_index];
	struct Car *car = branch->cars[car_index];

	if (car != NULL)
	{
		car->Model = strdup(input);
	}
	else
	{
		branch->cars[car_index] = create_car(strdup(input), "", "", 0, Automatic, BrandNew);
	}

	// printf("name :%s", input);

	// scanf("%s", &input);
}


/*
	Change car model name in selected branch and slot
*/
void change_car()
{
	clear_console();
	printf("Pick branch");
	printf("--------------------------------\n");
	for (int i = 0; i < sizeof(dealershipPtr->Branches) / sizeof(dealershipPtr->Branches[0]); i++)
	{
		struct Branch *branch = dealershipPtr->Branches[i];
		// printf("Car pointer is: %p\n", (void *) car);
		if (branch != NULL)
		{
			printf("%d) Branch name: %s\n", i + 1, branch->name);
		}
	}
	printf("--------------------------------\n");

	int input;
	printf("Your input: ");
	scanf("%d", &input);

	if (input >= 1 && input <= 3)
		branch_index = input - 1;

	clear_console();
	printf("Pick car slot");
	printf("--------------------------------\n");
	struct Branch *branch = dealershipPtr->Branches[branch_index];
	if (branch != NULL)
	{
		printf("\nCar matches in branch %s \n", branch->name);
		for (int i = 0; i < sizeof(branch->cars) / sizeof(branch->cars[0]); i++)
		{
			struct Car *car = branch->cars[i];
			if (car != NULL)
			{
				printf("%d) [%s] \n", i + 1, car->Model);
			}
			else
			{
				printf("%d) [empty] \n", i + 1);
			}
		}
	}
	printf("--------------------------------\n");

	input;
	printf("Your input: ");
	scanf("%d", &input);

	if (input >= 1 && input <= 10)
		car_index = input - 1;

	clear_console();
	printf("Pick action");
	printf("--------------------------------\n");
	printf("1) Add or Edit\n");
	// printf("2) Transfare\n");
	printf("--------------------------------\n");

	input;
	printf("Your input: ");
	scanf("%d", &input);

	if (input == 1)
		add_car();
	else
		transfare_car();
}

// Backend calls

// Add car to selected branch
void call_add_car(int slot, int branch, struct Car *car)
{
	dealershipPtr->Branches[branch]->cars[slot] = car;
}

// Remove car from selected branch
void call_remove_car(int slot, int branch, struct Car *car)
{
	dealershipPtr->Branches[branch]->cars[slot] = NULL;
}

// back end to update inventory once use buy a car and update sales
void call_sell_car(int slot, int branch)
{
	struct Car *car = dealershipPtr->Branches[branch]->cars[slot];
	struct Branch *branchRef = dealershipPtr->Branches[branch];

	if (strcmp(car->Manufacturer, "honda") == 0 && strcmp(branchRef->name, "Canada - Ottawa") == 0)
	{
		dealershipPtr->Sales += car->price * 0.98f * currentCurrency;
	}
	else if (strcmp(car->Manufacturer, "volvo") == 0 && strcmp(branchRef->name, "Mexico - Mexico City") == 0 && car->price > 60000)
	{
		dealershipPtr->Sales += car->price * 0.97f * currentCurrency;
	}else
	{
		dealershipPtr->Sales += car->price * 0.97f * currentCurrency;
	}

	dealershipPtr->Branches[branch]->cars[slot] = NULL;
}

bool inRange(int price, int mileage, struct SearchModel *search)
{
	return price > search->PriceRange.min && price < search->PriceRange.max || mileage > search->RangeOfMileage.min && mileage < search->RangeOfMileage.max;
}

// Search for the car based on use input
struct SearchResult *call_search_car(struct SearchModel *search)
{
	// search result counter and data holder
	int resultCount = 0;
	struct SearchResult *result = malloc(sizeof(struct SearchResult));

	for (int l = 0; l < sizeof(dealershipPtr->Branches) / sizeof(dealershipPtr->Branches[0]); l++)
	{
		if (resultCount > 4)
			break;

		struct Branch *branch = dealershipPtr->Branches[l];
		if (branch != NULL)
		{
			printf("\nCar matches in branch %s \n", branch->name);
			for (int i = 0; i < sizeof(branch->cars) / sizeof(branch->cars[0]); i++)
			{
				if (resultCount > 4)
					break;

				struct Car *car = branch->cars[i];
				if (car != NULL)
				{
					if (strcmp(car->Model, search->CarModel) == 0 || strcmp(car->Manufacturer, search->CarManufacturer) == 0 || car->Condition == search->CarCondition || inRange(car->price, car->Mileage, search))
					{
						result->car[resultCount] = car;
						resultCount++;
					}
				}
			}
		}
	}

	return result;
}

/*
	Transfare car from branch to another
	add transfer expenses to the sales
*/
void call_transfare_car(int slot, int branch, int to_slot, int to_branch)
{
	struct Car *car = dealershipPtr->Branches[branch]->cars[slot];
	dealershipPtr->Branches[branch]->cars[slot] = NULL;
	dealershipPtr->Branches[to_branch]->cars[to_slot] = car;
	dealershipPtr->Sales -= 1000 * currentCurrency;
}

// main menu
void main_menu()
{
	clear_console();

	printf("Welcome to %s store\n", dealershipPtr->name);
	printf("--------------------------------\n");
	printf("1) Add or change Car\n");
	printf("2) Search for car\n");
	printf("3) Print branches car data\n");
	printf("4) Print branches data\n");
	printf("\n0) Exit\n");
	printf("--------------------------------\n");

	int input;
	printf("Your input: ");
	scanf("%d", &input);

	switch (input)
	{
	case 0:
		exit(0);
	case 1:
		change_car();
		break;
	case 2:
		search_for_car();
		break;
	case 3:
		print_branch_cars();
		break;
	case 4:
		print_branches();
		break;
	default:
		return;
	}

	main_menu();
}

// Application entry point
int main()
{
	dealership.name = "Belal Elhawary";
	dealershipPtr->Branches[0] = create_usa_branch();
	dealershipPtr->Branches[1] = create_canada_branch();
	dealershipPtr->Branches[2] = create_mexico_branch();
	dealershipPtr->Branches[3] = create_panama_branch();
	dealershipPtr->Branches[4] = create_costa_rica_branch();
	main_menu();
	return 0;
}

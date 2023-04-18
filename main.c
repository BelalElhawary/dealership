#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

char *bool_to_string(bool value)
{
	if(value)
		return "Yes";
	else
		return "No";
}

// Car information data holder

// enum to spicify wich type of currency (supported by program)
typedef enum
{
	Peso,
	CanadianDollar,
	Balboa,
	Colon
} Currency;

// enum to spicify wich type of transmission the car use
typedef enum
{
	Manual,
	Automatic,
} TransmissionType;

// enum to spicify wich type of driving system the car use
typedef enum
{
	TwoWheelDrive,
	FourWheelDrive
} DrivingSystemType;

// enum to spicify wich type of driving system the car use
typedef enum
{
	BrandNew,
	Used,
	Both
} ConditionType;



// struct to hold Engine data
typedef struct 
{
	char *name;
} EngineData;

// struct to hold Chassis data

typedef struct
{
	char *name;
} ChassisData;

// struct to hold Exterior data
typedef struct
{
	char *name;
} ExteriorData;

// struct to hold Steating data
typedef struct
{
	char *name;
} SeatingAndTrimData;

// struct to hold Dimension data
typedef struct
{
	float width, height, length;
} DimensionData;

// struct to hold FuelEconomy data
typedef struct
{
	char *name;
} FuelEconomyData;

/*
	struct to hold car data
*/
typedef struct
{
	char *Model;
	char *Manufacturer;
	bool isColorUpgraded;
	char *Color;
	unsigned int Mileage;
	unsigned int price;
	bool isTransmissionUpgraded;
	TransmissionType Transmission;
	EngineData *Engine;
	ChassisData *Chassis;
	ExteriorData *Exterior;
	SeatingAndTrimData *SeatingAndTrim;
	bool Airbags;
	unsigned int AirbagsCount;
	FuelEconomyData *FuelEconomy;
	bool Hybrid;
	bool FullyElectrified;
	bool isAutomaticParkingAssistanceUpgraded;
	bool AutomaticParkingAssistance;
	bool NightVisionAssistance;
	bool isCruiseControl;
	bool CruiseControl;
	DrivingSystemType DrivingSystem;
	bool HillAssist;
	bool isTirePressureMonitoringSystemUpgreded;
	bool TirePressureMonitoringSystem;
	bool VoiceCommand;
	bool LaneChangeIndicator;
	bool ForwardCollisionWarningSensor;
	bool BlindSpotWarningSensors;
	bool SeatHeater;
	bool SteeringHeater;
	ConditionType Condition;
	char *countries[5];
} Car;

// struct to hold search for car result contains 5 cars in array of struct Car
typedef struct
{
	Car *car[5];
} SearchResult;

/*
	struct to hold FinanceManager data
*/
typedef struct
{
	char *FirstName, LastName;
	unsigned int PhoneNumber;
	unsigned int CellPhoneNumber;
	char *Address;
	char *DateOfEmployment;
	unsigned int YearsOfExperience;
} FinanceManagerData;

/*
	struct to hold GeneralManager data
*/
typedef struct
{

	unsigned int PhoneNumber;
	unsigned int CellPhoneNumber;
	char *Address;
	char *Email;
	char *DateOfEmployment;
	unsigned int YearsOfExperience;
} GeneralManagerData;

/*
	struct to hold Branch data
*/
typedef struct
{
	// public information
	char *name;
	char *Address;
	char *PostalCode;
	char *PhoneNumber;
	char *FaxNumber;
	char *CustomerServiceEmail;
	char *NameOfTheGeneralManager;
	Car *cars[10];

	// confidential information
	GeneralManagerData *GeneralManager;
	FinanceManagerData *FinaceManager;
	unsigned int AvailableCars;
	char *AvailableCarsInformation;
} Branch;

/*
	struct to hold Dealership data
*/
typedef struct
{
	char *name;
	Branch *Branches[5];
	unsigned int Sales;
} Dealership;

/*
	struct to hold two vector data like min and max of value or x or y for position data type
*/
typedef struct
{
	unsigned int min, max;
} Vector2;

/*
	struct to hold Search data
*/
typedef struct
{
	char *CarModel;
	char *CarManufacturer;
	ConditionType CarCondition;
	Vector2 *RangeOfMileage;
	Vector2 *PriceRange;
	char *Color;
} SearchModel;

char *error = NULL;
SearchModel *search;
Dealership *dealership;
unsigned int branch_index;
unsigned int car_index;
unsigned int peso = 18.01;
unsigned int canadianDollar = 1.35;
unsigned int balboa = 1;
unsigned int colon = 533.81;
float currentCurrency = 1;

/*
	Convert the program currency usd to branches currency
*/
void convert_price(Currency currency)
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
unsigned int compare_string(char *first, char *second)
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
void create_branch_car_list(Branch *branch)
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
Car *create_car(char *model, char *manufacturer, char *color, unsigned int price, TransmissionType transmission, ConditionType condition)
{
	Car *car = malloc(sizeof(Car));
	
	srand(12154842);
	car->Model = model;
	car->Color = color;
	car->isColorUpgraded = rand() & 1;
	car->Manufacturer = manufacturer;
	car->Mileage = 0;
	car->price = price;
	car->isTransmissionUpgraded = rand() & 1;
	car->Transmission = transmission;
	car->Engine = NULL;
	car->Chassis = NULL;
	car->Exterior = NULL;
	car->SeatingAndTrim = NULL;
	car->Airbags = rand() & 1;
	car->AirbagsCount = 6;
	car->FuelEconomy = NULL;
	car->Hybrid = rand() & 1;
	car->FullyElectrified = rand() & 1;
	car->isAutomaticParkingAssistanceUpgraded = rand() & 1;
	car->AutomaticParkingAssistance = rand() & 1;
	car->NightVisionAssistance = rand() & 1;
	car->isCruiseControl = rand() & 1;
	car->DrivingSystem = TwoWheelDrive;
	car->HillAssist = rand() & 1;
	car->isTirePressureMonitoringSystemUpgreded = rand() & 1;
	car->VoiceCommand = rand() & 1;
	car->LaneChangeIndicator = rand() & 1;
	car->ForwardCollisionWarningSensor = rand() & 1;
	car->BlindSpotWarningSensors = rand() & 1;
	car->SeatHeater = rand() & 1;
	car->SteeringHeater = rand() & 1;
	car->Condition = condition;
	
	return car;
}

/*
	Initialize branch data for Usa Washington
*/
Branch *create_usa_branch()
{
	Branch *branch = malloc(sizeof(Branch));

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
Branch *create_canada_branch()
{
	Branch *branch = malloc(sizeof(Branch));

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
Branch *create_mexico_branch()
{
	Branch *branch = malloc(sizeof(Branch));

	// Allocate memory for branch
	create_branch_car_list(branch);

	// Set branch data
	branch->name = "Mexico - Mexico City";
	branch->Address = "Vasco de Quiroga 2109, Santa Fe, Zedec Sta Fe, Alvaro Obregon, 01219 Ciudad de Mexico, CDMX, Mexico";
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
Branch *create_panama_branch()
{
	Branch *branch = malloc(sizeof(Branch));

	// Allocate memory for branch
	create_branch_car_list(branch);

	// Set branch data
	branch->name = "Panama - Panama City";
	branch->Address = "Via Ricardo J. Alfaro, Panama, Panama";
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
Branch *create_costa_rica_branch()
{
	Branch *branch = malloc(sizeof(Branch));

	// Allocate memory for branch
	create_branch_car_list(branch);

	// Set branch data
	branch->name = "Costa Rica - San Jose";
	branch->Address = "Via Ricardo J. Alfaro, Panama, Panama";
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

bool inRange(unsigned int price, unsigned int mileage, SearchModel *search)
{
	return price > search->PriceRange->min && price < search->PriceRange->max || mileage > search->RangeOfMileage->min && mileage < search->RangeOfMileage->max;
}

// Search for the car based on use input
SearchResult *call_search_car(SearchModel *search)
{
	// search result counter and data holder
	unsigned int resultCount = 0;
	SearchResult *result = malloc(sizeof(SearchResult));

	for (unsigned int l = 0; l < sizeof(dealership->Branches) / sizeof(dealership->Branches[0]); l++)
	{
		if (resultCount > 4)
			break;

		Branch *branch = dealership->Branches[l];
		if (branch != NULL)
		{
			printf("\nCar matches in branch %s \n", branch->name);
			for (unsigned int i = 0; i < sizeof(branch->cars) / sizeof(branch->cars[0]); i++)
			{
				if (resultCount > 4)
					break;

				Car *car = branch->cars[i];
				if (car != NULL)
				{
					if (strstr(car->Model, search->CarModel) != NULL || strcmp(car->Manufacturer, search->CarManufacturer) == 0 || car->Condition == search->CarCondition || inRange(car->price, car->Mileage, search))
					{
						result->car[resultCount] = car;
						resultCount++;
					}
					else
					{
						result->car[resultCount] = NULL;
					}
				}
			}
		}
	}

	free(search);
	return result;
}

void print_search_result(SearchResult *result)
{
	clear_console();

	printf("Search result\n");
	printf("--------------------------------\n");

	for (unsigned int l = 0; l < sizeof(result->car) / sizeof(result->car[0]); l++)
	{
		if (result->car != NULL)
		{
			printf("Model: %s\n", result->car[l]->Model);
			printf("Manufacturer: %s\n", result->car[l]->Manufacturer);
			printf("Price: %d\n", result->car[l]->price);
			printf("Mileage: %d\n", result->car[l]->Mileage);
		}
		printf("--------------------------------\n");
	}
	printf("0) Back\n");
	unsigned int action;
	scanf("%d", &action);
}

void search_for_car()
{
	clear_console();

	SearchModel *search = malloc(sizeof(SearchModel));

	printf("Search for car\n");
	printf("--------------------------------\n");
	printf("\nEnter car model: ");
	// Get user input string
	fflush(stdin);
	char input[24];
	fgets(input, 24, stdin);
	size_t ln = strlen(input) - 1;
	if (input[ln] == '\n')
	{
		input[ln] = '\0';
	}
	// Convert input string to lowercase
	for (unsigned int i = 0; i < strlen(input); i++)
	{
		input[i] = tolower(input[i]);
	}
	search->CarModel = input;

	printf("\nEnter car manufacturer: ");
	// Get user input string
	fflush(stdin);
	fgets(input, 24, stdin);
	ln = strlen(input) - 1;
	if (input[ln] == '\n')
	{
		input[ln] = '\0';
	}
	// Convert input string to lowercase
	for (unsigned int i = 0; i < strlen(input); i++)
	{
		input[i] = tolower(input[i]);
	}
	search->CarManufacturer = input;

	printf("\nEnter car price range: \n");
	// Get user input string
	fflush(stdin);
	unsigned int min, max;
	scanf("%d %d", &min, &max);
	Vector2 *price = malloc(sizeof(Vector2));
	price->min = min;
	price->max = max;
	search->PriceRange = price;

	printf("\nEnter car mileage range: \n");
	// Get user input string
	fflush(stdin);
	scanf("%d %d", &min, &max);
	Vector2 *mileage = malloc(sizeof(Vector2));
	price->min = min;
	price->max = max;
	search->RangeOfMileage = mileage;

	print_search_result(call_search_car(search));
}

void print_branch_cars()
{
	clear_console();
	unsigned int input;

	for (unsigned int l = 0; l < sizeof(dealership->Branches) / sizeof(dealership->Branches[0]); l++)
	{
		Branch *branch = dealership->Branches[l];
		if (branch != NULL)
		{
			printf("  Branch %s Cars \n", branch->name);
			printf("--------------------------------\n");
			for (unsigned int i = 0; i < sizeof(branch->cars) / sizeof(branch->cars[0]); i++)
			{
				Car *car = branch->cars[i];
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
	unsigned int input;

	printf("Branches \n");
	printf("--------------------------------\n");

	for (unsigned int i = 0; i < sizeof(dealership->Branches) / sizeof(dealership->Branches[0]); i++)
	{
		Branch *branch = dealership->Branches[i];
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

	fflush(stdin);
	char input[24];
	fgets(input, 24, stdin);
	size_t ln = strlen(input) - 1;
	if (input[ln] == '\n')
	{
		input[ln] = '\0';
	}

	Branch *branch = dealership->Branches[branch_index];
	Car *car = branch->cars[car_index];

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
	printf("Pick branch\n");
	printf("--------------------------------\n");
	for (unsigned int i = 0; i < sizeof(dealership->Branches) / sizeof(dealership->Branches[0]); i++)
	{
		Branch *branch = dealership->Branches[i];
		// printf("Car pointer is: %p\n", (void *) car);
		if (branch != NULL)
		{
			printf("%d) Branch name: %s\n", i + 1, branch->name);
		}
	}
	printf("--------------------------------\n");

	unsigned int input;
	printf("Your input: ");
	scanf("%d", &input);

	if (input >= 1 && input <= 5)
		branch_index = input - 1;

	clear_console();
	printf("Pick car slot");
	printf("--------------------------------\n");
	Branch *branch = dealership->Branches[branch_index];
	if (branch != NULL)
	{
		printf("\nCar matches in branch %s \n", branch->name);
		for (unsigned int i = 0; i < sizeof(branch->cars) / sizeof(branch->cars[0]); i++)
		{
			Car *car = branch->cars[i];
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
void call_add_car(unsigned int slot, unsigned int branch, Car *car)
{
	dealership->Branches[branch]->cars[slot] = car;
}

// Remove car from selected branch
void call_remove_car(unsigned int slot, unsigned int branch, Car *car)
{
	dealership->Branches[branch]->cars[slot] = NULL;
}

// back end to update inventory once use buy a car and update sales
void call_sell_car(unsigned int slot, unsigned int branchIndex)
{
	Branch *branch = dealership->Branches[branchIndex];
	Car *car = branch->cars[slot];

	if(branch == NULL)
		return;

	if(car == NULL)
		return;

	if (strcmp(car->Manufacturer, "honda") == 0 && strcmp(branch->name, "Canada - Ottawa") == 0)
	{
		dealership->Sales += car->price * 0.98;
	}
	else if (strcmp(car->Manufacturer, "volvo") == 0 && strcmp(branch->name, "Mexico - Mexico City") == 0 && car->price > 60000)
	{
		dealership->Sales += car->price * 0.97;
	}
	else
	{
		dealership->Sales += car->price;
	}

	dealership->Branches[branchIndex]->cars[slot] = NULL;
}

/*
	Transfare car from branch to another
	add transfer expenses to the sales
*/
void call_transfare_car(unsigned int slot, unsigned int branch, unsigned int to_slot, unsigned int to_branch)
{
	Car *car = dealership->Branches[branch]->cars[slot];
	dealership->Branches[branch]->cars[slot] = NULL;
	dealership->Branches[to_branch]->cars[to_slot] = car;
	dealership->Sales -= 1000;
}

void print_full_car_data()
{
	clear_console();

	printf("Print car data\n");
	printf("--------------------------------\n\n");
	printf("We have 5 branches with 10 cars in each\n");
	printf("Type branch number and submit then type car index and submit\n");
	unsigned int branchIndex, carIndex;
	scanf("%d%d", &branchIndex, &carIndex);

	branchIndex -= 1;
	carIndex -= 1;

	Branch *branch = dealership->Branches[branchIndex];
	if (branch == NULL || branchIndex > 4)
	{
		error = "Invalid branch index";
		return;
	}

	Car *car = branch->cars[carIndex];
	if (car == NULL || carIndex > 9)
	{
		error = "Invalid car index";
		return;
	}

	printf("\n Model: %s \n", car->Model);
	printf(" Manufacturer: %s \n", car->Manufacturer);
	
	printf(" Color: %s \n Color upgradable: %s\n", car->Color, bool_to_string(car->isColorUpgraded));
	printf(" Mileage: %d \n", car->Mileage);
	printf(" Price: $%d \n", car->price);

	if (car->Transmission == 0)
	{
		printf(" Transmission: Manual \n");
	}
	else
	{
		printf(" Transmission: Automatic \n");
	}

	if (car->Condition == 0)
	{
		printf(" Condition: Brand new \n");
	}
	else
	{
		printf(" Condition: Used \n");
	}

	if (car->DrivingSystem == 0)
	{
		printf(" DrivingSystem: Two wheels\n");
	}
	else
	{
		printf(" DrivingSystem: Four wheels\n");
	}
	
	printf(" Transmission Upgradable: %s \n", bool_to_string(car->isTransmissionUpgraded));
	printf(" Airbags: %s \n", bool_to_string(car->Airbags));
	printf(" Hybird: %s \n", bool_to_string(car->Hybrid));
	printf(" Fully electrified: %s \n", bool_to_string(car->FullyElectrified));
	printf(" Automatic parking assistance upgradable: %s \n", bool_to_string(car->isAutomaticParkingAssistanceUpgraded));
	printf(" Automatic parking assistance: %s \n", bool_to_string(car->AutomaticParkingAssistance));
	printf(" Night vision assistance: %s \n", bool_to_string(car->NightVisionAssistance));
	printf(" Curise control upgradable: %s \n", bool_to_string(car->isCruiseControl));
	printf(" Curise control: %s \n", bool_to_string(car->CruiseControl));
	printf(" Hill assist: %s \n", bool_to_string(car->HillAssist));
	printf(" isTirePressureMonitoringSystemUpgredable: %s \n", bool_to_string(car->isTirePressureMonitoringSystemUpgreded));
	printf(" Tire pressure monitoring system: %s \n", bool_to_string(car->TirePressureMonitoringSystem));
	printf(" Lane change indicator: %s \n", bool_to_string(car->LaneChangeIndicator));
	printf(" Blind spot warning sensors: %s \n", bool_to_string(car->BlindSpotWarningSensors));
	printf(" Seat heater: %s \n", bool_to_string(car->SeatHeater));
	printf(" Steering heater: %s \n", bool_to_string(car->SteeringHeater));

	printf("--------------------------------\n");

	unsigned int input;
	printf("0) Back\n");
	scanf("%d", &input);
}

void print_sell_car()
{
	clear_console();

	printf("Sell car\n");
	printf("--------------------------------\n\n");
	printf("We have 5 branches with 10 cars in each\n");
	printf("Type branch number and submit then type car index and submit\n");
	unsigned int branchIndex, carIndex;
	scanf("%d%d", &branchIndex, &carIndex);
	branchIndex -= 1;
	carIndex -= 1;

	Branch *branch = dealership->Branches[branchIndex];
	if (branch == NULL || branchIndex > 4)
	{
		error = "Invalid branch index";
		return;
	}

	Car *car = branch->cars[carIndex];
	if (car == NULL || carIndex > 9)
	{
		error = "Invalid car index";
		return;
	}

	call_sell_car(carIndex, branchIndex);
	printf("Done.\n");

	printf("--------------------------------\n");

	unsigned int input;
	printf("0) Back\n");
	scanf("%d", &input);
}

void print_transfare_car()
{
	clear_console();

	printf("Sell car\n");
	printf("--------------------------------\n\n");
	printf("We have 5 branches with 10 cars in each\n");
	printf("Type branch number and submit then type car index and submit\n");
	printf("First select the branch and car\n");
	unsigned int branchIndex, carIndex;
	scanf("%d%d", &branchIndex, &carIndex);
	branchIndex -= 1;
	carIndex -= 1;

	Branch *branch = dealership->Branches[branchIndex];
	if (branch == NULL || branchIndex > 4)
	{
		error = "Invalid branch index";
		return;
	}

	Car *car = branch->cars[carIndex];
	if (car == NULL || carIndex > 9)
	{
		error = "Invalid car index";
		return;
	}

	printf("Type branch number and submit then type car index and submit\n");
	printf("Then select where to transfare the car\n");
	unsigned int branchIndex2, carIndex2;
	scanf("%d%d", &branchIndex2, &carIndex2);
	branchIndex2 -= 1;
	carIndex2 -= 1;

	Branch *branch2 = dealership->Branches[branchIndex2];
	if (branch == NULL || branchIndex2 > 4)
	{
		error = "Invalid branch index";
		return;
	}

	Car *car2 = branch->cars[carIndex2];
	if (car == NULL || carIndex2 > 9)
	{
		error = "Invalid car index";
		return;
	}

	call_transfare_car(carIndex, branchIndex, carIndex2, branchIndex2);
	printf("Done.\n");

	printf("--------------------------------\n");

	unsigned int input;
	printf("0) Back\n");
	scanf("%d", &input);
}

// main menu
void main_menu()
{
	clear_console();

	printf("Welcome to %s  (store sales = $%d)\n", dealership->name, dealership->Sales);
	printf("--------------------------------\n");
	printf("1) Add or change Car\n");
	printf("2) Search for car\n");
	printf("3) Print branches car data\n");
	printf("4) Print branches data\n");
	printf("5) Sell a car\n");
	printf("6) Transfare a car\n");
	printf("7) Print full car data\n");
	printf("\n0) Exit\n");
	printf("--------------------------------\n");

	unsigned int input;
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
	case 5:
		print_sell_car();
		break;
	case 6:
		print_transfare_car();
		break;
	case 7:
		print_full_car_data();
		break;
	default:
		return;
	}

	main_menu();
}

// Application entry point
int main()
{
	dealership = malloc(sizeof(Dealership));
	dealership->name = "Belal Elhawary";
	dealership->Sales = 0;
	dealership->Branches[0] = create_usa_branch();
	dealership->Branches[1] = create_canada_branch();
	dealership->Branches[2] = create_mexico_branch();
	dealership->Branches[3] = create_panama_branch();
	dealership->Branches[4] = create_costa_rica_branch();
	main_menu();
	free(dealership);
	return 0;
}

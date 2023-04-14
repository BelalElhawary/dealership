#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// enum to spiceify wich type of transmission the car use
enum TransmissionType
{
	Manual,
	Automatic,
};

enum DrivingSystemType
{
	TwoWheelDrive,
	FourWheelDrive
};

enum ConditionType
{
	BrandNew,
	Used
};

struct EngineData
{
	char *name;
};

struct ChassisData
{
	char *name;
};

struct ExteriorData
{
	char *name;
};

struct SteatingAndTrimData
{
	char *name;
};

struct DimensionData
{
	float width, height, length;
};

struct FuelEconomyData
{
	char *name;
};

struct Car
{
	char *Model;
	char *Manufacturer;
	_Bool isColorUpgraded;
	char Color;
	int Mileage;
	int price;
	_Bool isTransmissionUpgraded;
	enum TransmissionType Transmission;
	struct EngineData *Engine;
	struct ChassisData *Chassis;
	struct ExteriorData *Exterior;
	struct SteatingAndTrimData *SeatingAndTrim;
	_Bool Airbags;
	int AirbagsCount;
	struct FuelEconomyData *FuelEconomy;
	_Bool Hybrid;
	_Bool FullyElectrified;
	_Bool isAutomaticParkingAssistanceUpgraded;
	_Bool AutomaticParkingAssistance;
	_Bool NightVisionAssistance;
	_Bool isCruiseControl;
	_Bool CruiseControl;
	enum DrivingSystemType DrivingSystem;
	_Bool HillAssist;
	_Bool isTirePressureMonitoringSystemUpgreded;
	_Bool TirePressureMonitoringSystem;
	_Bool VoiceCommand;
	_Bool LaneChangeIndicator;
	_Bool ForwardCollisionWarningSensor;
	_Bool BlindSpotWarningSensors;
	_Bool SeatHeater;
	_Bool SteeringHeater;
	enum ConditionType Condition;
	char *countries[5];
};

struct FinanceManagerData
{
	char *FirstName, LastName;
	int PhoneNumber;
	int CellPhoneNumber;
	char *Address;
	char *DateOfEmployment;
	int YearsOfExperience;
};

struct GeneralManagerData
{

	int PhoneNumber;
	int CellPhoneNumber;
	char *Address;
	char *Email;
	char *DateOfEmployment;
	int YearsOfExperience;
};

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

struct Dealership
{
	char *name;
	struct Branch *Branches[3];
};

struct Vector2
{
	int min, max;
};

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

struct Car *create_car(char *model)
{
	struct Car *car = malloc(sizeof(struct Car));
	car->Model = model;
	return car;
}

struct Branch *create_usa_branch()
{
	struct Branch *branch = malloc(sizeof(struct Branch));

	create_branch_car_list(branch);

	branch->name = "USA - Washington DC";
	branch->Address = "13806 Hwy 99, Lynnwood, WA 98087, United States";
	branch->PhoneNumber = "+1 425-697-6969";
	branch->FaxNumber = "202-366-3244";
	branch->PostalCode = "98071";
	branch->CustomerServiceEmail = "usa.washington@gmail.com";
	branch->NameOfTheGeneralManager = "Muriel Bowser";

	branch->cars[0] = create_car("BMW");

	return branch;
}

struct Branch *create_canada_branch()
{
	struct Branch *branch = malloc(sizeof(struct Branch));

	create_branch_car_list(branch);

	branch->name = "Canada - Ottawa";
	branch->Address = "939 St. Laurent Blvd, Ottawa, ON K1K 3B1, Canada";
	branch->PhoneNumber = "+1 613-741-0741";
	branch->FaxNumber = "613-783-5958";
	branch->PostalCode = "K0A";
	branch->CustomerServiceEmail = "canada.ottawa@gmail.com";
	branch->NameOfTheGeneralManager = "Mark Sutcliffe";

	branch->cars[0] = create_car("BMW");

	return branch;
}


struct Branch *create_mexico_branch()
{
	struct Branch *branch = malloc(sizeof(struct Branch));

	create_branch_car_list(branch);

	branch->name = "Mexico - Mexico City";
	branch->Address = "Vasco de Quiroga 2109, Santa Fe, Zedec Sta Fé, Álvaro Obregón, 01219 Ciudad de México, CDMX, Mexico";
	branch->PhoneNumber = "+52 55 5081 2300";
	branch->FaxNumber = "844-528-6611";
	branch->PostalCode = "00810";
	branch->CustomerServiceEmail = "mexico.mexicocity@gmail.com";
	branch->NameOfTheGeneralManager = "Claudia Sheinbaum";

	branch->cars[0] = create_car("BMW");

	return branch;
}


void search_for_car()
{
	clear_console();

	printf("Search for car\n");
	printf("--------------------------------\n");
	char input[10];
	printf("Enter car model: ");
	scanf("%s", input);

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
			printf("Branch %s Cars \n", branch->name);
			printf("--------------------------------\n");
			for (int i = 0; i < sizeof(branch->cars) / sizeof(branch->cars[0]); i++)
			{
				struct Car *car = branch->cars[i];
				if (car != NULL)
				{
					printf(" - Car Model: %s \n", car->Model);
				}
			}
			printf("--------------------------------\n\n");
		}
	}
	printf("0) Back\n");

	scanf("%d", &input);
}

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

void add_car()
{
	clear_console();

	printf("Enter car model\n");
	printf("--------------------------------\n");
	char input[24];
	printf("Your input: ");
	scanf("%s", input);
	struct Branch *branch = dealershipPtr->Branches[branch_index];
	struct Car *car = branch->cars[car_index];

	if(car != NULL)
	{
		car->Model = strdup(input);
	}
	else
	{
		branch->cars[car_index] = create_car(strdup(input));
	}

	//printf("name :%s", input);

	//scanf("%s", &input);
}

void transfare_car()
{

}

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
			}else{
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
	//printf("2) Transfare\n");
	printf("--------------------------------\n");

	input;
	printf("Your input: ");
	scanf("%d", &input);

	if(input == 1)
		add_car();
	else
		transfare_car();
}

void main_menu()
{
	clear_console();

	printf("Welcome to %s store\n", dealershipPtr->name);
	printf("--------------------------------\n");
	printf("1) Add or change Car\n");
	printf("2) Search for car\n");
	printf("3) Print branches car data\n");
	printf("4) Print branches data\n");
	printf("5) Print dealership data (underdevelopment)\n");
	printf("6) Sell or buy or transfare a car (underdevelopment)\n");
	printf("7) Info (underdevelopment)\n");
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
	case 6:
		change_car();
	default:
		return;
	}

	main_menu();
}


int main()
{
	dealership.name = "Belal Elhawary";
	dealershipPtr->Branches[0] = create_usa_branch();
	dealershipPtr->Branches[1] = create_canada_branch();
	dealershipPtr->Branches[2] = create_mexico_branch();
	main_menu();
	return 0;
}

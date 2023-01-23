#include <fstream>
#include "MealyMachine.h"
#include "MooreMachine.h"
#include "transitions.h"

using namespace std;

enum MachineType
{
	Moore,
	Mealy,
	Unknown,
};

MachineType GetMachineType(const string& typeName)
{
	if (typeName == "moore")
	{
		return MachineType::Moore;
	}
	else if (typeName == "mealy")
	{
		return MachineType::Mealy;
	}

	return MachineType::Unknown;
}

int main(int argc, char* argv[])
{
	if (argc > 3)
	{
		cerr << "invalid number if input parameters" << endl;
		return 1;
	}

	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);

	if (!inputFile.is_open())
	{
		cerr << "Cannot open file: " << argv[1] << endl;
		return 1;
	}

	if (!outputFile)
	{
		cerr << "Cannot create/open file: " << argv[2] << endl;
		return 1;
	}

	string inputAlphabetCharsCountStr;
	string outputAlphabetCharsCountStr;
	string statesCountStr;

	inputFile >> inputAlphabetCharsCountStr >> outputAlphabetCharsCountStr >> statesCountStr;

	auto inputAlphabetCharsCount = stoul(inputAlphabetCharsCountStr);
	auto outputAlphabetCharsCount = stoul(outputAlphabetCharsCountStr);
	auto statesCount = stoul(statesCountStr);

	string machineTypeName;
	inputFile >> machineTypeName;
	MachineType machineType = GetMachineType(machineTypeName);

	if (machineType == MachineType::Mealy)
	{
		auto mealyMachineData = ReadMealyMachineData(inputFile, inputAlphabetCharsCount, statesCount);
		auto mooreMachineData = TransitMealyToMoore(mealyMachineData);
		PrintMooreMachineData(mooreMachineData, outputFile);
	}
	else if (machineType == MachineType::Moore)
	{
		auto mooreMachineData = ReadMooreMachineData(inputFile, inputAlphabetCharsCount, statesCount);
		auto mealyMachineData = TransitMooreToMealy(mooreMachineData);
		PrintMealyMachineData(mealyMachineData, outputFile);
	}
	else
	{
		cerr << "Unknown machine type: " << machineTypeName << endl;
		return 1;
	}

	return 0;
}
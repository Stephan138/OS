#include "MealyMachine.h"
#include <string>
using namespace std;
using State = string;
using InputSignal = string;
using OutputSignal = string;

MealyTransition GetMealyTransition(const string& str)
{
	auto indexOfY = str.find("y");

	State state;
	state.append(str, 0, indexOfY);

	OutputSignal outputSignal;
	outputSignal.append(str, indexOfY);

	MealyTransition transition;
	transition.state = state;
	transition.outputSignal = outputSignal;
	return transition;
}

MealyMachineData ReadMealyMachineData(istream& stream, int inputAlphabetCharsCount, int statesCount)
{
	MealyMachineData mealyMachineData;

	for (int i = 1; i <= inputAlphabetCharsCount; i++)
	{
		for (int j = 0; j < statesCount; j++)
		{
			string transition;
			stream >> transition;

			InputSignal inputSignal = "x" + to_string(i);
			State currentState = transition[0] + to_string(j);

			mealyMachineData[inputSignal][currentState] = GetMealyTransition(transition);
		}
	}

	return mealyMachineData;
}

void PrintMealyMachineData(const MealyMachineData& mealyMachineData, ostream& stream)
{
	for (auto transitions : mealyMachineData)
	{
		for (auto transition : transitions.second)
		{
			stream << transition.second.state << transition.second.outputSignal << ' ';
		}
		stream << endl;
	}
}
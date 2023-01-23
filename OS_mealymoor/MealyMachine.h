#pragma once
#include <iostream>
#include <map>
#include <string>
using namespace std;
using State = string;
using InputSignal = string;
using OutputSignal = string;

using namespace std;

struct MealyTransition
{
	State state;
	OutputSignal outputSignal;
};

using MealyMachineData = map<InputSignal, map<State, MealyTransition>>;

MealyMachineData ReadMealyMachineData(istream& stream, int inputAlphabetCharsCount, int statesCount);
void PrintMealyMachineData(const MealyMachineData& mealyMachineData, ostream& stream);
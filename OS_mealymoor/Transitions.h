#pragma once
#include "MealyMachine.h"
#include "MooreMachine.h"

MooreMachineData TransitMealyToMoore(const MealyMachineData& mealyMachineData);
MealyMachineData TransitMooreToMealy(const MooreMachineData& mooreMachineData);
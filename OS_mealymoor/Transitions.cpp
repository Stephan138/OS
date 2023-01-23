#include "Transitions.h"
#include <set>

using namespace std;

const string NEW_STATE_NAME = "z";

bool operator<(const MealyTransition& transition1, const MealyTransition& transition2)
{
	return transition1.state < transition2.state ||
		transition1.state == transition2.state && transition1.outputSignal < transition2.outputSignal;
}

MooreMachineData TransitMealyToMoore(const MealyMachineData& mealyMachineData)
{
	std::set<MealyTransition> transitions;

	for (auto inputSignal : mealyMachineData)
	{
		for (auto startState : inputSignal.second)
		{
			transitions.insert(startState.second);
		}
	}

	map<State, State> newStatesMap;

	size_t i = 0;
	for (auto transition : transitions)
	{
		newStatesMap[transition.state] = NEW_STATE_NAME + to_string(i++);
	}

	MooreMachineData mooreMachineData;

	for (auto inputSignal : mealyMachineData)
	{
		for (auto startState : inputSignal.second)
		{
			State givenStartState = newStatesMap[startState.first];
			State givenNewState = newStatesMap[startState.second.state];

			mooreMachineData.graph[inputSignal.first][givenStartState] = givenNewState;
			mooreMachineData.outputSignals[givenNewState] = startState.second.outputSignal;
		}
	}

	return mooreMachineData;
}

MealyMachineData TransitMooreToMealy(const MooreMachineData& mooreMachineData)
{
	MealyMachineData mealyMachineData;

	for (auto inputSignal : mooreMachineData.graph)
	{
		for (auto startState : inputSignal.second)
		{
			State nextState = startState.second;
			OutputSignal outputSignal = mooreMachineData.outputSignals.at(nextState);

			mealyMachineData[inputSignal.first][startState.first] = MealyTransition{ nextState, outputSignal};
		}
	}

	return mealyMachineData;
}
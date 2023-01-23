#include <vector>
#include "MooreMachine.h"
#include <string>
using namespace std;
using State = string;
using InputSignal = string;
using OutputSignal = string;

MooreMachineData ReadMooreMachineData(istream& stream, int inputAlphabetCharsCount, int statesCount)
{
	vector<string> outputSignals(statesCount);

	for (size_t i = 0; i < outputSignals.size(); i++)
	{
		stream >> outputSignals[i];
	}

	MooreMachineData mooreMachineData;
	char stateSymbol;

	for (int i = 1; i <= inputAlphabetCharsCount; i++)
	{
		for (int j = 0; j < statesCount; j++)
		{
			State nextState;
			stream >> nextState;

			stateSymbol = nextState[0];

			InputSignal inputSignal = "x" + to_string(i);
			State currentState = stateSymbol + to_string(j);

			mooreMachineData.graph[inputSignal][currentState] = nextState;
		}
	}

	for (int i = 0; i < statesCount; i++)
	{
		mooreMachineData.outputSignals[stateSymbol + to_string(i)] = outputSignals[i];
	}

	return mooreMachineData;
}

void PrintMooreMachineData(const MooreMachineData& mooreMachineData, ostream& stream)
{
	for (auto outputSignal : mooreMachineData.outputSignals)
	{
		stream << outputSignal.second << ' ';
	}

	stream << endl;

	for (auto transitions : mooreMachineData.graph)
	{
		for (auto transition : transitions.second)
		{
			stream << transition.second << ' ';
		}
		stream << endl;
	}
}
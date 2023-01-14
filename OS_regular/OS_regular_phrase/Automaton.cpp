#include "Automaton.h"

CAutomaton::CAutomaton(NondeterministicAutomaton automaton)
	: m_automaton(automaton)
{
};

CAutomaton::NondeterministicAutomaton CAutomaton::GetAutomaton() const
{
	return m_automaton;
}

std::set<std::string> CAutomaton::GetActions() const
{
	return m_actions;
}
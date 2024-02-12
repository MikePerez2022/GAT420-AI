#pragma once
#include "iostream"

using namespace std;

// structure for a node in the decision tree
struct node_t
{
	// constructor

	node_t(string Info) :
		info{ Info }
	{}

	virtual node_t* execute() = 0;

	string info;
	node_t* trueNode{ nullptr };	// pointer to true branch
	node_t* falseNode{ nullptr };	// pointer to false branch
};

// enum defining different types of predicates (Less, Greater, Equal, Not_Equal)
enum ePredicate
{
	Less,
	Greater,
	Equal,
	UnEqual
};

// function to convert enum predicate to string representation
inline string getString(ePredicate predicate)
{
	switch (predicate)
	{
	case Less:
		return "<";
	case Greater:
		return ">";
	case Equal:
		return "==";
	case UnEqual:
		return "!=";
	default:
		break;
	}

	return "";
}

template <typename T>
struct decision_t : public node_t
{
	// constructor
	decision_t(const string& info, T& parameter, ePredicate predicate, const T& value) :
		node_t{ info },
		parameter{ parameter },
		predicate{ predicate },
		value{ value }
	{}

	node_t* execute()
	{
		bool result = false;
		switch (predicate)
		{
		case Less:
				result = (parameter < value);
				break;
		case Greater:
			result = (parameter > value);
			break;
		case Equal:
			result = (parameter == value);
			break;
		case UnEqual:
			result = (parameter != value);
			break;
		}

		cout << "descision: " << info << " : " << parameter << " " << getString(predicate) << " " << value << " (" << (result ? "true" : "false") << ")\n";

		// return true or false branch node based on result
		return (result) ? trueNode : falseNode;
	}

	T& parameter; // Reference to the parameter used for comparison
	T value; // Value for comparison
	ePredicate predicate; // Predicate used for comparison
};

struct action_t : public node_t
{
	// constructor
	//<constructor that takes in info string and calls parent class with info string>

	action_t(string Info) : node_t{ Info }
	{}

	virtual node_t* execute() override
	{
		cout << "action: " << info << endl;

		// action node is a leaf node (no children)
		return nullptr;
	}
};
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;
//bool for debugging code with cout statements in tracing the flow of the program from B to A 
const bool DEBUG = false;

//Set up functions for Boolean expressions
string getExpression();
string cleanWhiteSpace(string);
void errorReport(string,int, string);
bool isValid(string, int);
bool B(string, int&);
bool IT(string, int&);
bool OT(string, int&);
bool AT(string, int&);
bool IT_Tail(string, int&);
bool OT_Tail(string, int&);
bool AT_Tail(string, int&);
bool L(string, int&);
bool A(string, int&);


stack<char> BoolExpression;

int main()
{
	
	bool isValid = false;
	
	//propt user for input until they enter a valid expression
	//reset position if invalid
	while (!isValid)
	{
		int position = 0;
		string Ex = getExpression();
		Ex = cleanWhiteSpace(Ex);
		if (Ex != "False")
		{
			isValid = B(Ex, position);
		}
		if(isValid)
		{
			cout << "The final result of " << Ex << " is " << BoolExpression.top() << endl;
			BoolExpression.pop();
		}
	}
	system("pause");
}
//Get the boolean expression to evaluate
string getExpression()
{
	string Expression = "";
	cout << "Enter a boolean expression:" << endl;
	cout << "T = True, F = False, ~ = Not, V = Or, ^ = And, -> = Imply" << endl;
	getline(cin, Expression);
	
	return Expression;
}
//clean out whitespaces in the string since they are delimiters
string cleanWhiteSpace(string Ex)
{
	int ExLength = Ex.length();
	//Checks if there is a whitespace between an implication. if found then return error. else return cleaned string
	size_t found = Ex.find("- >");
	if (found !=string::npos)
	{
		errorReport(Ex, ++found, "<-!![ - > is an invalid boolean opperator!!]");
		Ex = "False";
		return Ex;
	}
	else
	{
		Ex.erase(remove_if(Ex.begin(), Ex.end(), isspace), Ex.end());
		return Ex;
	}
}
//Takes in the Expression entered, the position where the error occured and the fucntion it occured in and sumbits an error
//Based on where the incorrect expression occured.
void errorReport(string Ex, int position, string Function)
{
	Ex = Ex.insert(position, Function);
	cout << "Invalid Expression occured at character " << position << endl;
	cout << Ex << endl;
}
//Syntax B first checks to make sure last character is a period then checks if IT is true
bool B(string Ex, int &position)
{
	if (DEBUG)
	{
		cout << "B value = " << Ex[position] << endl;
	}
	if (Ex[Ex.length()-1] != '.')
	{
		errorReport(Ex, Ex.length(), "<-!![Expression must end in a period (.)]");
		return false;
	}
	else if (IT(Ex,position))
	{
		++position;
		return true;
	}
	else {
		return false;
	}
}

//Checks if OT is true sends the expression to check IT Tail or Imply Terms
bool IT(string Ex, int &position)
{
	if (DEBUG)
	{
		cout << "IT value = " << Ex[position] << endl;
	}
	if (OT(Ex, position))
	{
		if (IT_Tail(Ex, position))
		{
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//Checls for AT if true sends expression to OT Tail for or terms
bool OT(string Ex, int &position)
{
	if (DEBUG)
	{
		cout << "OT value = " << Ex[position] << endl;
	}
	if (AT(Ex, position))
	{
		if (OT_Tail(Ex, position))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

}

//Checks for L if true sends the expression to AT Tail for And Terms
bool AT(string Ex, int &position)
{
	if (DEBUG)
	{
		cout << "AT value = " << Ex[position] << endl;
	}
	if (L(Ex, position))
	{
		if (AT_Tail(Ex, position))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else 
	{
		return false;
	}
}

//Checks for Literals in the expression sends to A for ataoms
bool L(string Ex, int &position)
{
	if (DEBUG)
	{
		cout << "L value = " << Ex[position] << endl;
	}
	if (A(Ex, position))
	{
		return true;
	}
	else if (Ex[position] == '~')
	{
		//Find the inverse of the NOT Statement
		++position;
		if (Ex[position] == 'T')
		{
			Ex[position] = 'F';
		}
		else
		{
			Ex[position] = 'T';
		}
		L(Ex, position);
		return true;
	}
	else
	{
		return false;
	}
}

//Checks if expression is an atom and converts it accordingly
bool A(string Ex, int &position)
{
	if (DEBUG)
	{
		cout << "A value = " << Ex[position] << endl;
	}
	if (Ex[position] == 'T' || Ex[position] == 'F')
	{
		BoolExpression.push(Ex[position]);
		++position;
		return true;
	}
	else if (Ex[position] == '(')
	{
		++position;
		IT(Ex, position);
		return true;
	}
	else {
		errorReport(Ex, ++position, "<-!![Character is not a valid Atom.]!!");
		return false;
	}
}
//Check if there is an implied term in the expression
bool IT_Tail(string Ex, int &position)
{
	if (DEBUG)
	{
		cout << "IT Tail value = " << Ex[position] << endl;
	}
	if (Ex[position] == '-' && Ex[position + 1] == '>')
	{

		position+=2;
		if (OT(Ex, position))
		{
			if (IT_Tail(Ex, position))
			{
				//Evaluate the imply expression
				char rightEx = BoolExpression.top();
				BoolExpression.pop();
				char leftEx = BoolExpression.top();
				BoolExpression.pop();
				if (leftEx == 'F' || (leftEx == 'T' && rightEx == 'T'))
				{
					BoolExpression.push('T');
				}
				else
				{
					BoolExpression.push('F');
				}
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else if (Ex[position] == '.' || Ex[position] == ')')
	{
		return true;
	}
	else {
		return false;
	}
}

//Checks for or terms in the expression
bool OT_Tail(string Ex, int &position)
{
	if (DEBUG)
	{
		cout << "OT Tail value = " << Ex[position] << endl;
	}
	if (Ex[position] == 'V')
	{
		++position;

		if (AT(Ex, position))
		{
			if (OT_Tail(Ex, position))
			{
				//Evaluate or expression
				char rightEx = BoolExpression.top();
				BoolExpression.pop();
				char leftEx = BoolExpression.top();
				BoolExpression.pop();
				if (leftEx == 'F' && rightEx == 'F')
				{
					BoolExpression.push('F');
				}
				else
				{
					BoolExpression.push('T');
				}
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else if ((Ex[position] == '-' && Ex[position + 1] == '>') || Ex[position] == '.' || Ex[position] == ')')
	{
		return true;
	}
	else
	{ 
		return false; 
	}
}

//Checks for an and term in the expression
bool AT_Tail(string Ex, int &position)
{
	if (DEBUG)
	{
		cout << "AT Tail value = " << Ex[position] << endl;
	}
	if (Ex[position] == '^')
	{
		++position;
		if (L(Ex, position))
		{
			if (AT_Tail(Ex, position))
			{
				//Evaluate and term
				char rightEx = BoolExpression.top();
				BoolExpression.pop();
				char leftEx = BoolExpression.top();
				BoolExpression.pop();
				if (leftEx == 'T' && rightEx == 'T')
				{
					BoolExpression.push('T');
				}
				else
				{
					BoolExpression.push('F');
				}
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	//check for seperators 
	else if ((Ex[position] == '-' && Ex[position + 1] == '>') || Ex[position] == '.' || Ex[position] == ')' || Ex[position] == 'V')
	{
		return true;
	}
	else
	{
		errorReport(Ex, ++position, "<-!![Character is not a valid boolean opperation]!!");
		return false;
	}
}

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <cstdlib>

using namespace std;

int caller = 1;
int length;
vector <int> card;

string error(string error)
{
	if (error == "notNum") 			return "\n----------------------------\nError: Input must be numeric\n----------------------------\n";
	else if (error == "cardLength") return "\n----------------------\nError: Improper length\n----------------------\n";
	else if (error == "invalid") 	return "\n--------------------------\nError: Invalid card number\n--------------------------\n";
	else							return "\n---------------\nError: in error\n---------------\n";
}

int card_in()
{
	card.erase(card.begin(), card.end());
	string num;
	cout << "\nEnter card number: ";
	cin >> num;
	if ((num.length() == 16)
	||  (num.length() == 15))
	{
		length = num.length() - 1;
		int numIn;
		for (int i = 0; i <= length; i++)
		{
			stringstream numSS(num.substr(i, 1));
			while (!(numSS >> numIn))
			{
				numSS.clear();
				numSS.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << error("notNum");
				return caller = 1;
			}
			card.push_back(numIn);
		}
		return caller = 2;
	}
	else
	{
		cout << error("cardLength");
	}
	return caller = 1;
}

int card_val()
{
	vector <int> nums;
	for (int i = 0; i <= length; i++)
	{
		int newNum = card[i];
		if (i % 2 == 0)
		{
			newNum *= 2;
			if (newNum >= 10)
			{
				nums.push_back(newNum - 9);
			}
			else
			{
				nums.push_back(newNum);
			}
		}
		else
		{
			nums.push_back(newNum);
		}
	}
	int sumNum = 0;
	for (int i = 0; i <= length; i++)
	{
		sumNum += nums[i];
	}
	if (sumNum % 10 == 0)
	{
		cout << "\n> Valid: ";

		if (card[0] == 4)	// Visa starts with 4
		{
			if (((card[1] == 0) &&   (card[2] == 2) &&  (card[3] == 6))		// Visa Electron: 4026
			||  ((card[1] == 8) &&   (card[2] == 4) &&  (card[3] == 4))		// Visa Electron: 4844
			||  ((card[1] == 9) &&   (card[2] == 1) && ((card[3] == 3)		// Visa Electron: 4913
													||  (card[3] == 7)))	// Visa Electron: 4917
			||  ((card[2] == 0) && (((card[1] == 4) &&  (card[3] == 5))		// Visa Electron: 4405
								||  ((card[1] == 5) &&  (card[3] == 8))))	// Visa Electron: 4508
			||  ((card[1] == 1) &&   (card[2] == 7) &&  (card[3] == 5) && (card[4] == 0) && (card[5] == 0))) // Visa Electron: 417500
			{
				cout << "Visa Electron"
					 << endl;
			}
			else
			{
				cout << "Visa"
					 << endl;
			}
		}
		else if ((card[0] == 5) && ((card[1] >= 1) && (card[1] <= 5)))	// MasterCard starts with 51-55
		{
			cout << "MasterCard"
				 << endl;
		}
		else if ((card[0] == 3) && ((card[1] == 4) || (card[1] == 7)))	// American Express starts with 34 or 37
		{
			cout << "American Express"
				 << endl;
		}
		else if ((card[0] == 6) && ((card[1] == 5)											// Discover Card starts with 65
								|| ((card[1] == 0) &&  (card[2] == 1) &&  (card[3] == 1))	// Discover Card starts with 6011
								|| ((card[1] == 4) && ((card[2] >= 4)						// Discover Card starts with 644
													&& (card[2] <= 9)))						// 						  to 649
								|| ((card[1] == 2) &&  (card[2] == 2) && (((card[3] >  1)	// Discover Card starts with 6221**
																	   &&  (card[3] <  9))
																	  ||  ((card[3] == 1)      && (card[4] >  2))
																	  ||  ((card[3] == 9)      && (card[4] <  2))
																	  ||  ((card[3] == 1 || 9) && (card[4] == 2) && ((card[5] >= 6)
																												 || (card[5] <= 5)))))))
		{																					// 						  to 6229**
			cout << "Discover Card"
				 << endl;
		}
		else
		{
			cout << "Unknown Type"
				 << endl;
		}
	}
	else
	{
		cout << error("invalid");
	}
	return caller = 1;
}

int main()
{
	switch (caller)
	{
		case 1:
			card_in();
			main();
			break;
		case 2:
			card_val();
			main();
			break;
		default:
			return 0;
			break;
	}
	return 0;
}
#include <iostream>
#include <string>
#include <bitset>

using namespace std;

string shift(string str)
{
	const unsigned last = str.size() - 1;
	for (int i = last; i > 0; i--)
		str[i] = str[i - 1];

	str[0] = str[1];
	return str;
}

string bitAdder(string nA, string nB)
{
	char holder[nA.size()];
	string result = "";
	bool up = false;
	for (int i = nA.size() - 1; i >= 0; i--)
	{
		const bool nA_is_cero = nA[i] == '0';
		const bool nB_is_Cero = nB[i] == '0';
		const char bit = char(int(up) + int('0'));
		const char aBit = char(int(!up) + int('0'));
		if (nA_is_cero && nB_is_Cero)
		{
			holder[i] = bit;
			if (up)
				up = false;
		}
		else if (nA_is_cero != nB_is_Cero)
			holder[i] = aBit;
		else
		{
			holder[i] = bit;
			if (!up)
				up = true;
		}
	}
	for (int i = 0; i < nA.size(); i++)
		result.push_back(holder[i]);

	return result;
}

int main()
{
	bitset<4> complement;				   // complemento
	bitset<4> multiplying(string("0101")); // multiplicando
	bitset<4> multiplier(string("0011"));  // multiplicando
	bitset<4> one(string("1"));			   // uno

	complement = multiplying;
	complement.flip(); // turns all 0s to 1s and 1s to 0s

	//example vars MQA
	// convert bitset to str
	string M, Q, A, unit;
	M = multiplying.to_string<char, string::traits_type, string::allocator_type>();
	Q = multiplier.to_string<char, string::traits_type, string::allocator_type>();
	A = complement.to_string<char, string::traits_type, string::allocator_type>();
	unit = one.to_string<char, string::traits_type, string::allocator_type>();

	A = bitAdder(A, unit);

	int size = M.size();
	Q.push_back('0');

	for (int i = 0; i < size; i++)
		Q.insert(0, "0");
	for (int i = 0; i < size + 1; i++)
	{
		M.append("0");
		A.append("0");
	}

	cout << "input" << endl;
	cout << "M\t: " << M << endl;
	cout << "A\t: " << A << endl;
	cout << "Q\t: " << Q << endl;
	cout << "\nprocessing" << endl;

	for (int i = 0; i < size; i++)
	{
		const unsigned qSize = Q.size();
		const bool _isCero = Q[qSize - 2] == '0';
		const bool isCero = Q[qSize - 1] == '0';
		if (_isCero && isCero)
			Q = shift(Q);
		else if (!_isCero && isCero)
		{
			Q = bitAdder(Q, A);
			Q = shift(Q);
		}
		else if (_isCero && !isCero)
		{
			Q = bitAdder(Q, M);
			Q = shift(Q);
		}
		else if (!_isCero && !isCero)
			Q = shift(Q);
		cout << "\t  " << Q << endl;
	}
	cout << "\n\nanswer\t: ";
	for (int i = size; i < Q.size() - 1; i++)
		cout << Q[i];
	cout << endl;
}

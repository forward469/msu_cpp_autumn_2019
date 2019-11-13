#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "BigInteger.h"

using namespace std;

BigInteger::BigInteger()
{
	number = "0";
	sign = false;
}
//-------------------------------------------------------------
BigInteger::BigInteger(string s)
{
	if( isdigit(s[0]) ) 
	{
		setNumber(s);
		sign = false;
	}
	else
	{
		setNumber( s.substr(1) );
		sign = (s[0] == '-');
	}
}
//-------------------------------------------------------------
BigInteger::BigInteger(string s, bool sin)
{
	setNumber( s );
	setSign( sin );
}
//-------------------------------------------------------------
BigInteger::BigInteger(int n)
{
	stringstream ss;
	string s;
	ss << n;
	ss >> s;


	if( isdigit(s[0]) )
	{
		setNumber( s );
		setSign( false );
	}
	else
	{
		setNumber( s.substr(1) );
		setSign( s[0] == '-' );
	}
}
//-------------------------------------------------------------
void BigInteger::setNumber(string s)
{
	number = s;
}
//-------------------------------------------------------------
const string& BigInteger::getNumber() // Получение числа
{
	return number;
}
//-------------------------------------------------------------
void BigInteger::setSign(bool s)
{
	sign = s;
}
//-------------------------------------------------------------
const bool& BigInteger::getSign()
{
	return sign;
}
//-------------------------------------------------------------
BigInteger BigInteger::absolute()
{
	return BigInteger( getNumber() );
}
//-------------------------------------------------------------

void BigInteger::operator = (BigInteger b)
{
	setNumber( b.getNumber() );
	setSign( b.getSign() );
}
//-------------------------------------------------------------
bool BigInteger::operator == (const BigInteger &b)
{
	return equals((*this) , b);
}
//-------------------------------------------------------------
bool BigInteger::operator != (const BigInteger &b)
{
	return ! equals((*this) , b);
}
//-------------------------------------------------------------
bool BigInteger::operator > (const BigInteger &b)
{
	return greater((*this) , b);
}
//-------------------------------------------------------------
bool BigInteger::operator < (const BigInteger &b)
{
	return less((*this) , b);
}
//-------------------------------------------------------------
bool BigInteger::operator >= (const BigInteger &b)
{
	return equals((*this) , b)
		|| greater((*this), b);
}
//-------------------------------------------------------------
bool BigInteger::operator <= (const BigInteger &b)
{
	return equals((*this) , b) 
		|| less((*this) , b);
}
//-------------------------------------------------------------
BigInteger BigInteger::operator + (BigInteger &b)
{
	BigInteger addition;
	if( getSign() == b.getSign() )
	{
		addition.setNumber( add(getNumber(), b.getNumber() ) );
		addition.setSign( getSign() );
	}
	else
	{
		BigInteger tmp=b.absolute();
		if( absolute() > tmp )
		{
			addition.setNumber( subtract(getNumber(), b.getNumber() ) );
			addition.setSign( getSign() );
		}
		else
		{
			addition.setNumber( subtract(b.getNumber(), getNumber() ) );
			addition.setSign( b.getSign() );
		}
	}
	if(addition.getNumber() == "0")
		addition.setSign(false);

	return addition;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator - (BigInteger &b)
{
	b.setSign( ! b.getSign() ); // x - y = x + (-y)
	return (*this) + b;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator -() // Унарный минус
{
	(*this).setSign( ! (*this).getSign() );
	return (*this);
}
//-------------------------------------------------------------
BigInteger::operator string() // Перевод из BigInt в string
{
	string signedString = ( getSign() ) ? "-" : ""; 
	signedString += number;
	return signedString;
}
//-------------------------------------------------------------
// Равенство
bool BigInteger::equals(const BigInteger &n1, const BigInteger &n2)
{
	return n1.number == n2.number
		&& n1.number == n2.number;
}

//-------------------------------------------------------------
// Меньше
bool BigInteger::less(const BigInteger &n1, const BigInteger &n2)
{
	bool sign1 = n1.sign;
	bool sign2 = n2.sign;

	if(sign1 && ! sign2) 
		return true;

	else if(! sign1 && sign2)
		return false;

	else if(! sign1) 
	{
		if(n1.number.length() < n2.number.length() )
			return true;
		if(n1.number.length() > n2.number.length() )
			return false;
		return (n1.number < n2.number);
	}
	else 
	{
		if(n1.number.length() > n2.number.length())
			return true;
		if(n1.number.length() < n2.number.length())
			return false;
		return n1.number.compare( n2.number ) > 0; 
	}
}
//-------------------------------------------------------------
// Больше
bool BigInteger::greater(const BigInteger &n1, const BigInteger &n2)
{
	return ! equals(n1, n2) && ! less(n1, n2);
}

//-------------------------------------------------------------
// Суммирование
string BigInteger::add(string number1, string number2)
{
	string add = (number1.length() > number2.length()) ?  number1 : number2;
	char carry = '0';
	int differenceInLength = abs( (int) (number1.size() - number2.size()) );

	if(number1.size() > number2.size())
		number2.insert(0, differenceInLength, '0'); 

	else // if(number1.size() < number2.size())
		number1.insert(0, differenceInLength, '0');

	for(int i=number1.size()-1; i>=0; --i)
	{
		add[i] = ((carry-'0')+(number1[i]-'0')+(number2[i]-'0')) + '0';

		if(i != 0)
		{	
			if(add[i] > '9')
			{
				add[i] -= 10;
				carry = '1';
			}
			else
				carry = '0';
		}
	}
	if(add[0] > '9')
	{
		add[0]-= 10;
		add.insert(0,1,'1');
	}
	return add;
}

//-------------------------------------------------------------
// Вычитание
string BigInteger::subtract(string number1, string number2)
{
	string sub = (number1.length()>number2.length())? number1 : number2;
	int differenceInLength = abs( (int)(number1.size() - number2.size()) );

	if(number1.size() > number2.size())	
		number2.insert(0, differenceInLength, '0');

	else
		number1.insert(0, differenceInLength, '0');

	for(int i=number1.length()-1; i>=0; --i)
	{
		if(number1[i] < number2[i])
		{
			number1[i] += 10;
			number1[i-1]--;
		}
		sub[i] = ((number1[i]-'0')-(number2[i]-'0')) + '0';
	}

	while(sub[0]=='0' && sub.length()!=1)
		sub.erase(0,1);

	return sub;
}

//-------------------------------------------------------------
// Конвертирует long long в строку
string BigInteger::toString(long long n)
{
	stringstream ss;
	string temp;

	ss << n;
	ss >> temp;

	return temp;
}

//-------------------------------------------------------------
// Конвертирует строку в long long
long long BigInteger::toInt(string s)
{
	long long sum = 0;

	for(int i=0; i<s.length(); i++)
		sum = (sum*10) + (s[i] - '0');

	return sum;
}


int main()
{
	BigInteger big_A = 12345;
	BigInteger big_B("22412515132");

	cout << "BigInt: 12345 + (22412515132) = " <<(string)(big_A + big_B) << endl; // 22 412 527 477
	cout << "BigInt: (-12345) + (22412515132) = " << (string)(-big_A + big_B) << endl; // 22 412 502 787
	cout << "BigInt: 12345 > (22412515132) : " << (big_A > big_B) << endl; // False
	cout << "BigInt: 12345 < (22412515132) : " << (big_A < big_B) << endl; // True
	cout << "BigInt: 12345 >= (22412515132) : " << (big_A >= big_B) << endl; // False
	cout << "BigInt: 12345 <= (22412515132) : " << (big_A <= big_B) << endl; // True
	cout << "BigInt: 12345 == (22412515132) : " << (big_A == big_B) << endl; // False
	cout << "BigInt: 12345 != (22412515132) : " << (big_A != big_B) << endl; // True

	big_B = BigInteger(123);
	cout << "Copy: " << (string)big_B << endl;
	cout << "Copied == Inserted : " << (big_B == 123) << endl; // True
	return 0;
}
#include <string>
#define MAX 10000 // for strings

using namespace std;
//-------------------------------------------------------------
class BigInteger
{
private:
	string number;
	bool sign;
public:
	BigInteger(); // Пустой конструктор для создания "0"
	BigInteger(string s); // Строковый конструктор
	BigInteger(string s, bool sin);
	BigInteger(int n); // "int" конструктор
	void setNumber(string s);
	const string& getNumber(); // получение числа
	void setSign(bool s);
	const bool& getSign();
	BigInteger absolute(); // Возвращает значение по модулю
	void operator << (BigInteger b);
	void operator = (BigInteger b);
	bool operator == (BigInteger b);
	bool operator != (BigInteger b);
	bool operator > (BigInteger b);
	bool operator < (BigInteger b);
	bool operator >= (BigInteger b);
	bool operator <= (BigInteger b);
	BigInteger operator + (BigInteger b);
	BigInteger operator - (BigInteger b);
	BigInteger operator -(); // Унарный минус
	operator string(); // Переводит BigInt в строку
private:
	bool equals(BigInteger n1, BigInteger n2);
	bool less(BigInteger n1, BigInteger n2);
	bool greater(BigInteger n1, BigInteger n2);
	string add(string number1, string number2);
	string subtract(string number1, string number2);
	string toString(long long n);
	long long toInt(string s);
};


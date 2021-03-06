#include <string>



//-------------------------------------------------------------
class BigInteger
{
private:
	std::string number;
	bool sign;
public:
	BigInteger(); // Пустой конструктор для создания "0"
	BigInteger(std::string s); // Строковый конструктор
	BigInteger(std::string s, bool sin);
	BigInteger(int n); // "int" конструктор
	void setNumber(std::string s);
	const std::string& getNumber(); // получение числа
	void setSign(bool s);
	const bool& getSign();
	BigInteger absolute(); // Возвращает значение по модулю
	void operator << (const BigInteger &b);
	void operator = (BigInteger b);
	bool operator == (const BigInteger &b);
	bool operator != (const BigInteger &b);
	bool operator > (const BigInteger &b);
	bool operator < (const BigInteger &b);
	bool operator >= (const BigInteger &b);
	bool operator <= (const BigInteger &b);
	BigInteger operator + (BigInteger &b);
	BigInteger operator - (BigInteger &b);
	BigInteger operator -(); // Унарный минус
	operator std::string(); // Переводит BigInt в строку
private:
	bool equals(const BigInteger &n1, const BigInteger &n2);
	bool less(const BigInteger &n1, const BigInteger &n2);
	bool greater(const BigInteger &n1, const BigInteger &n2);
	std::string add(std::string number1, std::string number2);
	std::string subtract(std::string number1, std::string number2);
	std::string toString(long long n);
	long long toInt(std::string s);
};
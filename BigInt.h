#pragma once

#include <iostream>

class BigInt
{
	private:
		bool is_negative;
		unsigned long length;
		unsigned short* digits;

		// get a digit value or default (0)
		// util function for calculations where we could possibly go beyond our bounds
		constexpr unsigned short get_digit_or_default(int index) const { return index >= length ? 0 : digits[index]; }

	public:
		// cosntructor
		BigInt(long int value);
		BigInt(unsigned short* digits, unsigned short length, bool is_negative);

		// destructor
		~BigInt();

		// copy constructor
		BigInt(const BigInt& b);

		// assignment
		BigInt& operator=(const BigInt& b);

		// compares two BigInts
		// returns number > 0 if b is bigger
		// returns number < 0 if b is smaller
		// returns 0 if numbers are equals
		short cmp(const BigInt& b) const;

		// compares two BigInts absolute value (sign will be ignored)
		// returns number > 0 if b is bigger
		// returns number < 0 if b is smaller
		// returns 0 if numbers are equals
		short cmp_absolute(const BigInt& b) const;

		BigInt& operator += (const BigInt& b);
		BigInt& operator -= (const BigInt& b);
		BigInt& operator *= (const BigInt& b);
		BigInt& operator /= (const BigInt& b);

		// free insertion operator
		friend std::ostream& operator<<(std::ostream& os, const BigInt& b);

		// free equality operators
		friend bool operator==(const BigInt& b1, const BigInt& b2);
		friend bool operator!=(const BigInt& b1, const BigInt& b2);
		friend bool operator<=(const BigInt& b1, const BigInt& b2);
		friend bool operator>=(const BigInt& b1, const BigInt& b2);
		friend bool operator<(const BigInt& b1, const BigInt& b2);
		friend bool operator>(const BigInt& b1, const BigInt& b2);

		friend BigInt operator+(BigInt b1, const BigInt& b2);
		friend BigInt operator-(BigInt b1, const BigInt& b2);
		friend BigInt operator*(BigInt b1, const BigInt& b2);
		friend BigInt operator/(BigInt b1, const BigInt& b2);

		// friendly utils for calculations
		friend BigInt add(const BigInt& b1, const BigInt& b2);
		friend BigInt substract(const BigInt& b1, const BigInt& b2);
};


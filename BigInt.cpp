#include "BigInt.h"

#include <cstdlib>
#include <stack>
#include <new>
#include <ostream>
#include <cassert>

// -----------------------
// -- Internal Constants for CMP
// -----------------------

const int CMP_SECOND_PARAMETER_SMALLER = -1;
const int CMP_SECOND_PARAMETER_BIGGER = 1;
const int CMP_EQUAL = 0;

// -----------------------
// -- Internal Util functions
// -----------------------
static void decrease_size(unsigned short*& digits, int old_size, int new_size) {
	assert(old_size > new_size);

	unsigned short* tmp_array = new unsigned short[new_size] {};
	for (int i = 0; i < new_size; i++) {
		tmp_array[i] = digits[i];
	}
	delete[] digits;
	digits = tmp_array;
}

static void increase_size(unsigned short*& digits, int old_size, int new_size) {
	assert(new_size > old_size);

	unsigned short* tmp_array = new unsigned short[new_size] {};
	for (int i = 0; i < old_size; i++) {
		tmp_array[i] = digits[i];
	}
	delete[] digits;
	digits = tmp_array;
}

// -----------------------
// -- Util methods
// -----------------------
/// <summary>
/// Adds two BigInts and returns a new object
/// </summary>
BigInt add(const BigInt& b1, const BigInt& b2)
{
	int max_length_parameters = b1.length > b2.length ? b1.length : b2.length;
	unsigned short* destination_digits = new unsigned short[max_length_parameters] {};
	unsigned short current_length = max_length_parameters;

	for (int i = 0; i < current_length; i++) {
		// 1. calc sum
		unsigned short sum = b1.get_digit_or_default(i) + b2.get_digit_or_default(i);

		// 2. calc current
		unsigned short current = sum % 10;
		// use += instead of = because last iteration could have set carry on this position
		destination_digits[i] += current;

		// 3. calc carry
		unsigned short carry = sum / 10;
		// nothind to do in this iteration if there is no carry
		bool no_carry = carry == 0;
		if (no_carry)
			continue;

		// check size
		bool need_increase_size = i + 1 > (current_length - 1);
		if (need_increase_size) {
			increase_size(destination_digits, current_length, current_length + 1);
			current_length++;
		}

		// set carry value
		destination_digits[i + 1] = carry;
	}

	return BigInt(destination_digits, current_length, false);
}

/// <summary>
/// Subtracts two BigInts and returns a new object
/// </summary>
BigInt substract(const BigInt& b1, const BigInt& b2)
{
	int max_length_parameters = b1.length > b2.length ? b1.length : b2.length;
	unsigned short* destination_digits = new unsigned short[max_length_parameters] {};
	unsigned short current_length = max_length_parameters;

	unsigned short carry = 0;

	for (int i = 0; i < current_length; i++) {
		// 1. calc sum
		short diff = b1.get_digit_or_default(i) - b2.get_digit_or_default(i) - carry;
		bool is_diff_negative = diff < 0;

		// 2. calc current
		unsigned short current = is_diff_negative ? diff + 10 : diff;
		destination_digits[i] = current;

		// 3. calc carry 
		carry = is_diff_negative == true;
	}

	// 4. remove leading zeros
	// we could improve this algorithm by calculating the new size BEFORE shrinking the array
	// so we could shrink it in one statement
	for (int i = 1; i < current_length && current_length > 1; i++) {
		bool leading_zero = destination_digits[current_length - i] == 0;
		if (leading_zero) {
			decrease_size(destination_digits, current_length, current_length - i);
			current_length--;
			i--;
		}
		else {
			break;
		}
	}

	return BigInt(destination_digits, current_length, false);
}

// -----------------------
// -- Constructor, Destructor, Copy Constructor and Assignment Operator
// -----------------------

BigInt::BigInt(long int value) : is_negative(false), length(0)
{
	if (value < 0) {
		is_negative = true;
		value *= -1;
	}

	if (value == 0) {
		length = 1;
	}

	digits = new unsigned short[length] {};
	while (value > 0) {
		increase_size(digits, length, length + 1);
		unsigned short current_digit = value % 10;
		digits[length] = current_digit;
		value /= 10;
		length++;
	}
}

BigInt::BigInt(unsigned short* digits, unsigned short length, bool is_negative) : digits(digits), length(length), is_negative(is_negative)
{
}

// destructor
BigInt::~BigInt()
{
	delete[] digits;
}

// copy constructor
BigInt::BigInt(const BigInt& b) : digits(new unsigned short[b.length]), length(b.length), is_negative(b.is_negative)
{
	for (int i = 0; i < b.length; i++)
		digits[i] = b.digits[i];
}

// assignment operator
BigInt& BigInt::operator=(const BigInt& b)
{
	// check if we called ourself
	if (this == &b) {
		return *this;
	}

	if (length != b.length) {
		delete digits;
		digits = new unsigned short[b.length];
	}

	length = b.length;
	is_negative = b.is_negative;

	for (int i = 0; i < length; i++)
		digits[i] = b.digits[i];

	return *this;
}

// compares two BigInts and does not respect the sign
// returns number > 0 if b is bigger
// returns number < 0 if b is smaller
// returns 0 if numbers are equals
short BigInt::cmp_absolute(const BigInt& b) const
{
	if (length != b.length)
		return length > b.length ? CMP_SECOND_PARAMETER_SMALLER : CMP_SECOND_PARAMETER_BIGGER;

	for (int i = length-1; i >= 0; i--) {
		if (digits[i] == b.digits[i])
			continue;

		return digits[i] < b.digits[i] ? CMP_SECOND_PARAMETER_BIGGER : CMP_SECOND_PARAMETER_SMALLER;
	}

	return CMP_EQUAL;
}

// compares two BigInts
// returns number > 0 if b is bigger
// returns number < 0 if b is smaller
// returns 0 if numbers are equals
short BigInt::cmp(const BigInt& b) const
{
	// we are negative and b is not
	if (is_negative && !b.is_negative)
		return CMP_SECOND_PARAMETER_BIGGER;

	// we are positive and b is negative
	if (!is_negative && b.is_negative)
		return CMP_SECOND_PARAMETER_SMALLER;

	bool all_positive = !is_negative && !b.is_negative;
	if (all_positive) {
		bool any_length_bigger = length != b.length;
		if (any_length_bigger)
			return length < b.length ? CMP_SECOND_PARAMETER_BIGGER : CMP_SECOND_PARAMETER_SMALLER;
	}

	bool all_negative = is_negative && b.is_negative;
	if (all_negative) {
		bool any_length_bigger = length != b.length;
		if (any_length_bigger)
			return length < b.length ? CMP_SECOND_PARAMETER_SMALLER : CMP_SECOND_PARAMETER_BIGGER;
	}

	return cmp_absolute(b);
}


// -----------------------
// -- Operators
// -----------------------

BigInt& BigInt::operator+=(const BigInt& b)
{
	bool a_negativ = is_negative;
	bool b_negativ = b.is_negative;

	bool both_negative = a_negativ && b_negativ;
	bool both_positive = !a_negativ && !b_negativ;
	bool same_sign = both_negative || both_positive;

	if (same_sign) {
		// keep sign if both are the same sign and add
		BigInt sum = add(*this, b);
		is_negative = a_negativ;
		length = sum.length;

		delete digits;
		digits = new unsigned short[length];
		memcpy(digits, sum.digits, sizeof(unsigned short) * length);
	}

	bool one_negative = a_negativ != b_negativ;
	if (one_negative) {
		// if the signs are different, subtract the numbers and use the sign of the largest number
		bool is_a_larger = cmp_absolute(b) == CMP_SECOND_PARAMETER_SMALLER;
		bool sign_to_use = is_a_larger ? is_negative : b.is_negative;
		// let's use a new BigInt so we can change the sign
		BigInt b_copy_different_sign{ b };
		// let's change signs to positive for the simple substract
		b_copy_different_sign.is_negative = false;
		is_negative = false;
		BigInt sum = substract(
			is_a_larger ? *this : b_copy_different_sign,
			is_a_larger ? b_copy_different_sign : *this
		);
		length = sum.length;
		// use the sign we calculated earlier and take care of -0
		bool is_zero = sum.length == 1 && sum.digits[0] == 0;
		is_negative = is_zero ? false : sign_to_use;

		delete digits;
		digits = new unsigned short[length];
		memcpy(digits, sum.digits, sizeof(unsigned short) * length);
	}

	return *this;
}

BigInt& BigInt::operator -= (const BigInt& b)
{
	BigInt b_inverted{ b };
	b_inverted.is_negative = !b.is_negative;
	return *this += b_inverted;
}

BigInt& BigInt::operator*=(const BigInt& b)
{
	int current_length = length > b.length ? length : b.length;
	unsigned short* product_digits = new unsigned short[current_length] {};
	unsigned short current = 0;

	for (int i = 0; i < b.length; i++) {
		unsigned short carry = 0;
		unsigned short digit = 0;
		int j = i;
		while (j < length + i) {
			if (current_length < j + 1) {
				increase_size(product_digits, current_length, current_length + 1);
				current_length++;
			}
			// create current product, with carry and current digit
			unsigned short product = product_digits[j] + (b.digits[i] * digits[j - i]) + carry;
			// calc digit and carry
			digit = product % 10;
			carry = product / 10;
			product_digits[j] = digit;
			j++;
		}


		// last iterations carry
		if (carry > 0) {
			if (current_length < j + 1) {
				increase_size(product_digits, current_length, current_length + 1);
				current_length++;
			}
			digit = product_digits[j] + carry;
			carry = digit / 10;
			product_digits[j] = digit % 10;
		}
	}

	// 4. remove leading zeros
	// we could improve this algorithm by calculating the new size BEFORE shrinking the array
	// so we could shrink it in one statement
	for (int i = 1; i < current_length && current_length > 1; i++) {
		bool leading_zero = product_digits[current_length - i] == 0;
		if (leading_zero) {
			decrease_size(product_digits, current_length, current_length - i);
			current_length--;
			i--;
		}
		else {
			break;
		}
	}

	delete digits;
	digits = new unsigned short[current_length];
	length = current_length;
	bool is_zero = length == 1 && digits[0] == 0;
	is_negative = is_zero ? false : is_negative || b.is_negative;
	memcpy(digits, product_digits, sizeof(unsigned short) * current_length);

	return *this;
}

BigInt& BigInt::operator/=(const BigInt& b)
{
	BigInt dividor = BigInt{ b };
	BigInt rest = BigInt(*this);
	BigInt quotient = 0;

	assert(dividor != 0);

	if (dividor > (*this))
	{
		delete digits;
		digits = new unsigned short[1]{ 0 };
		length = 1;
		is_negative = false;
		return *this;
	}

	if (b < 0)
		dividor.is_negative = false;

	if (rest < 0)
		rest.is_negative = false;

	while (rest >= dividor) {
		quotient += 1;
		rest -= dividor;
	}

	delete digits;
	digits = new unsigned short[quotient.length]{};
	length = quotient.length;
	bool is_zero = length == 1 && digits[0] == 0;
	is_negative = is_zero ? false : is_negative || b.is_negative;
	memcpy(digits, quotient.digits, sizeof(unsigned short) * quotient.length);

	return *this;
}

std::ostream& operator<<(std::ostream& os, const BigInt& b)
{
	if (b.length == 0)
		return os << "0";

	if (b.is_negative)
		os << "-";

	for (int i = 0; i < b.length; i++)
		os << b.digits[b.length - i - 1];

	return os;
}

bool operator==(const BigInt& b1, const BigInt& b2)
{
	return b1.cmp(b2) == CMP_EQUAL;
}

bool operator!=(const BigInt& b1, const BigInt& b2)
{
	return !(b1 == b2);
}

bool operator<(const BigInt& b1, const BigInt& b2)
{
	return b1.cmp(b2) == CMP_SECOND_PARAMETER_BIGGER;
}

bool operator>(const BigInt& b1, const BigInt& b2)
{
	return b1.cmp(b2) == CMP_SECOND_PARAMETER_SMALLER;
}

bool operator<=(const BigInt& b1, const BigInt& b2)
{
	return b1 == b2 || b1 < b2;
}

bool operator>=(const BigInt& b1, const BigInt& b2)
{
	return b1 == b2 || b1 > b2;
}

BigInt operator+(BigInt b1, const BigInt& b2)
{
	return b1 += b2;
}

BigInt operator-(BigInt b1, const BigInt& b2)
{
	return b1 -= b2;
}

BigInt operator*(BigInt b1, const BigInt& b2)
{
	return b1 *= b2;
}

BigInt operator/(BigInt b1, const BigInt& b2)
{
	return b1 /= b2;
}


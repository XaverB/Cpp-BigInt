#include <iostream>
#include "BigInt.h"
#include <cassert>

using namespace std;

static void test_init(long int value) {
	BigInt b1 = BigInt(value);
	cout << "test_init(" << value << ") = " << b1 << endl;
}

static void test_init(unsigned short* digits, unsigned short length, bool is_negative) {
	BigInt b1 = BigInt(digits, length, is_negative);
	cout << "test_init(digits, " << length << ", " << is_negative << ") = " << b1 << endl;
}


static void test_init() {
	cout << "--- --- test_init --- ---" << endl;
	test_init(0);
	test_init(1);
	test_init(10);
	test_init(100);
	test_init(-0);
	test_init(-1);
	test_init(-10);
	test_init(-100);

	test_init(nullptr, 0, false);
	test_init(new unsigned short[] { 1 }, 1, false);
	test_init(new unsigned short[] { 0, 1 }, 2, false);
	test_init(new unsigned short[] { 0, 0, 1 }, 3, false);
	test_init(new unsigned short[] { 0 }, 1, true);
	test_init(new unsigned short[] { 1 }, 1, true);
	test_init(new unsigned short[] { 0, 1 }, 2, true);
	test_init(new unsigned short[] { 0, 0, 1 }, 3, true);
}

static void test_copy(BigInt source) {
	BigInt destination = BigInt(source);
	cout << "source: (" << source << ") destination: (" << destination << ")" << endl;
}

static void test_copy() {
	cout << "--- --- test_copy --- ---" << endl;
	test_copy(BigInt(0));
	test_copy(BigInt(1));
	test_copy(BigInt(10));
	test_copy(BigInt(-1));
	test_copy(BigInt(-10));
}

static void test_assignment(BigInt source) {
	BigInt destination = source;
	cout << "source: (" << source << ") destination: (" << destination << ")" << endl;
}

static void test_assignment() {
	cout << "--- --- test_assignment --- ---" << endl;
	test_assignment(BigInt(0));
	test_assignment(BigInt(1));
	test_assignment(BigInt(10));
	test_assignment(BigInt(-1));
	test_assignment(BigInt(-10));
}

static void test_cmp(BigInt b1, BigInt b2) {
	cout << "b1(" << b1 << ").cmp(" << b2 << ") = " << b1.cmp(b2) << endl;
}

static void test_cmp() {
	cout << "--- --- test_cmp --- ---" << endl;
	test_cmp(BigInt{ 0 }, BigInt{ 0 });
	test_cmp(BigInt{ 1 }, BigInt{ 1 });
	test_cmp(BigInt{ -1 }, BigInt{ -1 });
	test_cmp(BigInt{ -1 }, BigInt{ 1 });
	test_cmp(BigInt{ 1 }, BigInt{ -1 });
	test_cmp(BigInt{ 10 }, BigInt{ 1 });
	test_cmp(BigInt{ 1 }, BigInt{ 10 });
	test_cmp(BigInt{ 1 }, BigInt{ -10 });
	test_cmp(BigInt{ -10 }, BigInt{ 1 });
	test_cmp(BigInt{ -10 }, BigInt{ 0 });
	test_cmp(BigInt{ 0 }, BigInt{ -10 });
	test_cmp(BigInt{ -0 }, BigInt{ 0 });
	test_cmp(BigInt{ 101 }, BigInt{ 102 });
	test_cmp(BigInt{ 102 }, BigInt{ 101 });
	test_cmp(BigInt{ 100 }, BigInt{ 1000 });
	test_cmp(BigInt{ 1001 }, BigInt{ 1000 });
}

static void test_equality_operators(BigInt b1, BigInt b2) {
	cout << std::boolalpha;
	cout << b1 << " == " << b2 << " = " << (b1 == b2) << endl;
	cout << b1 << " != " << b2 << " = " << (b1 != b2) << endl;
	cout << b1 << " < " << b2 << " = " << (b1 < b2) << endl;
	cout << b1 << " > " << b2 << " = " << (b1 > b2) << endl;
	cout << b1 << " <= " << b2 << " = " << (b1 <= b2) << endl;
	cout << b1 << " >= " << b2 << " = " << (b1 >= b2) << endl;

}

static void test_equality_operators() {
	cout << "--- --- test_equality_operators --- ---" << endl;
	test_equality_operators(BigInt{ 0 }, BigInt{ 0 });
	test_equality_operators(BigInt{ 1 }, BigInt{ 1 });
	test_equality_operators(BigInt{ -1 }, BigInt{ -1 });
	test_equality_operators(BigInt{ -1 }, BigInt{ 1 });
	test_equality_operators(BigInt{ 1 }, BigInt{ -1 });
	test_equality_operators(BigInt{ 10 }, BigInt{ 1 });
	test_equality_operators(BigInt{ 1 }, BigInt{ 10 });
	test_equality_operators(BigInt{ 1 }, BigInt{ -10 });
	test_equality_operators(BigInt{ -10 }, BigInt{ 1 });
	test_equality_operators(BigInt{ -10 }, BigInt{ 0 });
	test_equality_operators(BigInt{ 0 }, BigInt{ -10 });
	test_equality_operators(BigInt{ -0 }, BigInt{ 0 });
	test_equality_operators(BigInt{ 101 }, BigInt{ 102 });
	test_equality_operators(BigInt{ 102 }, BigInt{ 101 });
	test_equality_operators(BigInt{ 100 }, BigInt{ 1000 });
	test_equality_operators(BigInt{ 1001 }, BigInt{ 1000 });
}

static void test_add(BigInt b1, BigInt b2) {
	cout << b1 << " + " << b2 << " = " << (b1 + b2) << endl;
	cout << b2 << " + " << b1 << " = " << (b2 + b1) << endl;
	//cout << b1 << " += " << b2 << " = ";
	/*b1 += b2;
	cout << b1 << endl;*/
}

static void test_add() {
	cout << "--- --- test_add --- ---" << endl;
	test_add(BigInt{ 0 }, BigInt{ 0 });
	test_add(BigInt{ 1 }, BigInt{ 1 });
	test_add(BigInt{ -1 }, BigInt{ -1 });
	test_add(BigInt{ -1 }, BigInt{ 1 });
	test_add(BigInt{ 1 }, BigInt{ -1 });
	test_add(BigInt{ 10 }, BigInt{ 1 });
	test_add(BigInt{ 1 }, BigInt{ 10 });
	test_add(BigInt{ 1 }, BigInt{ -10 });
	test_add(BigInt{ -10 }, BigInt{ 1 });
	test_add(BigInt{ -10 }, BigInt{ 0 });
	test_add(BigInt{ 0 }, BigInt{ -10 });
	test_add(BigInt{ -0 }, BigInt{ 0 });
	test_add(BigInt{ 101 }, BigInt{ 102 });
	test_add(BigInt{ 102 }, BigInt{ 101 });
	test_add(BigInt{ 100 }, BigInt{ 1000 });
	test_add(BigInt{ 1001 }, BigInt{ 1000 });
	test_add(BigInt{ 100 }, BigInt{ -9 });
	test_add(BigInt{ 100 }, BigInt{ -99 });
	test_add(BigInt{ -9 }, BigInt{ -1 });
}

static void test_sub(BigInt b1, BigInt b2) {
	cout << b1 << " - " << b2 << " = " << (b1 - b2) << endl;
	cout << b2 << " - " << b1 << " = " << (b2 - b1) << endl;
	cout << b1 << " -= " << b2 << " = ";
	b1 -= b2;
	cout << b1 << endl;
}

static void test_sub() {
	cout << "--- --- test_sub --- ---" << endl;
	test_sub(BigInt{ 0 }, BigInt{ 0 });
	test_sub(BigInt{ 1 }, BigInt{ 1 });
	test_sub(BigInt{ -1 }, BigInt{ -1 });
	test_sub(BigInt{ -1 }, BigInt{ 1 });
	test_sub(BigInt{ 1 }, BigInt{ -1 });
	test_sub(BigInt{ 10 }, BigInt{ 1 });
	test_sub(BigInt{ 1 }, BigInt{ 10 });
	test_sub(BigInt{ 1 }, BigInt{ -10 });
	test_sub(BigInt{ -10 }, BigInt{ 1 });
	test_sub(BigInt{ -10 }, BigInt{ 0 });
	test_sub(BigInt{ 0 }, BigInt{ -10 });
	test_sub(BigInt{ -0 }, BigInt{ 0 });
	test_sub(BigInt{ 101 }, BigInt{ 102 });
	test_sub(BigInt{ 102 }, BigInt{ 101 });
	test_sub(BigInt{ 100 }, BigInt{ 1000 });
	test_sub(BigInt{ 1001 }, BigInt{ 1000 });
	test_sub(BigInt{ 100 }, BigInt{ -9 });
	test_sub(BigInt{ 100 }, BigInt{ -99 });
	test_sub(BigInt{ -9 }, BigInt{ -1 });
	test_sub(BigInt{ 10 }, BigInt{ 1 });
	test_sub(BigInt{ 10 }, BigInt{ 9 });
	test_sub(BigInt{ 100 }, BigInt{ 99 });
	test_sub(BigInt{ 1000 }, BigInt{ 99 });
}

static void test_mult(BigInt b1, BigInt b2) {
	cout << b1 << " * " << b2 << " = " << (b1 * b2) << endl;
	cout << b2 << " * " << b1 << " = " << (b2 * b1) << endl;
	cout << b1 << " *= " << b2 << " = ";
	b1 *= b2;
	cout << b1 << endl;
}

static void test_mult() {
	cout << "--- --- test_mult --- ---" << endl;
	test_mult(BigInt{ 0 }, BigInt{ 0 });
	test_mult(BigInt{ 1 }, BigInt{ 1 });
	test_mult(BigInt{ -1 }, BigInt{ -1 });
	test_mult(BigInt{ -1 }, BigInt{ 1 });
	test_mult(BigInt{ 1 }, BigInt{ -1 });
	test_mult(BigInt{ 10 }, BigInt{ 1 });
	test_mult(BigInt{ 1 }, BigInt{ 10 });
	test_mult(BigInt{ 1 }, BigInt{ -10 });
	test_mult(BigInt{ -10 }, BigInt{ 1 });
	test_mult(BigInt{ -10 }, BigInt{ 0 });
	test_mult(BigInt{ 0 }, BigInt{ -10 });
	test_mult(BigInt{ -0 }, BigInt{ 0 });
	test_mult(BigInt{ 99 }, BigInt{ 99 });
	test_mult(BigInt{ 101 }, BigInt{ 102 });
	test_mult(BigInt{ 102 }, BigInt{ 101 });
	test_mult(BigInt{ 100 }, BigInt{ 1000 });
	test_mult(BigInt{ 1001 }, BigInt{ 1000 });
	test_mult(BigInt{ 100 }, BigInt{ -9 });
	test_mult(BigInt{ 100 }, BigInt{ -99 });
	test_mult(BigInt{ -9 }, BigInt{ -1 });
	test_mult(BigInt{ 10 }, BigInt{ 1 });
	test_mult(BigInt{ 10 }, BigInt{ 9 });
	test_mult(BigInt{ 100 }, BigInt{ 99 });
	test_mult(BigInt{ 1000 }, BigInt{ 99 });
}

static void test_div(BigInt b1, BigInt b2)
{
	cout << b1 << " / " << b2 << " = " << (b1 / b2) << endl;
	cout << b2 << " / " << b1 << " = " << (b2 / b1) << endl;
	cout << b1 << " /= " << b2 << " = ";
	b1 /= b2;
	cout << b1 << endl;
}

static void test_div()
{
	cout << "--- --- test_div --- ---" << endl;
	test_div(BigInt{ 4 }, BigInt{ 2 });
	test_div(BigInt{ -4 }, BigInt{ -2 });
	test_div(BigInt{ -4 }, BigInt{ 2 });
	test_div(BigInt{ 16 }, BigInt{ 4 });
	test_div(BigInt{ 15 }, BigInt{ 4 });
	test_div(BigInt{ 4 }, BigInt{ -2 });
	test_div(BigInt{ 3 }, BigInt{ 3 });
	test_div(BigInt{ 3 }, BigInt{ 2 });
	test_div(BigInt{ 1 }, BigInt{ 1 });
	test_div(BigInt{ -1 }, BigInt{ -1 });
	test_div(BigInt{ -1 }, BigInt{ 1 });
	test_div(BigInt{ 1 }, BigInt{ -1 });
	test_div(BigInt{ 10 }, BigInt{ 1 });
	test_div(BigInt{ 1 }, BigInt{ 10 });
	test_div(BigInt{ 1 }, BigInt{ -10 });
	test_div(BigInt{ -10 }, BigInt{ 1 });
	test_div(BigInt{ 99 }, BigInt{ 99 });
	test_div(BigInt{ 101 }, BigInt{ 102 });
	test_div(BigInt{ 102 }, BigInt{ 101 });
	test_div(BigInt{ 100 }, BigInt{ 1000 });
	test_div(BigInt{ 1001 }, BigInt{ 1000 });
	test_div(BigInt{ 100 }, BigInt{ -9 });
	test_div(BigInt{ 100 }, BigInt{ -99 });
	test_div(BigInt{ -9 }, BigInt{ -1 });
	test_div(BigInt{ 10 }, BigInt{ 1 });
	test_div(BigInt{ 10 }, BigInt{ 9 });
	test_div(BigInt{ 100 }, BigInt{ 99 });
	test_div(BigInt{ 1000 }, BigInt{ 99 });
}

static void test_random(int amount = 10)
{
	srand(time(NULL));

	cout << "--- --- test_random --- ---" << endl;
	for (int i = 0; i < amount; i++) {
		long random_1 = rand();
		long random_2 = rand();
		BigInt b1 = { random_1 };
		BigInt b2 = { random_2 };

		short cmp_result = (b1 + b2).cmp(random_1 + random_2);
		const short equal = 0;
		if (cmp_result != equal)
			cout << "ERROR " << b1 << " + " << " " << b2 << ": expected (" << random_1 + random_2 << "), actual: (" << b1 + b2 << ")" << endl;
		else
			cout << "PASSED " << b1 << " + " << " " << b2 << ": expected (" << random_1 + random_2 << "), actual: (" << b1 + b2 << ")" << endl;
		
		cmp_result = (b1 - b2).cmp(random_1 - random_2);
		if (cmp_result != 0)
			cout << "ERROR " << b1 << " - " << " " << b2 << ": expected (" << random_1 - random_2 << "), actual: (" << b1 - b2 << ")" << endl;
		else
			cout << "PASSED " << b1 << " - " << " " << b2 << ": expected (" << random_1 - random_2 << "), actual: (" << b1 - b2 << ")" << endl;

		// we need to cap our rnd values for mult or we would go beyond long limit
		long random_3 = random_1 % 10000;
		long random_4 = random_2 % 10000;
		long result = random_3 * random_4;
		BigInt b3{ random_3 };
		BigInt b4{ random_4 };
		cmp_result = (b3 * b4).cmp(result);
		if (cmp_result != 0)
			cout << "ERROR " << b3 << " * " << " " << b4 << ": expected (" << result << "), actual: (" << b3 * b4 << ")" << endl;
		else
			cout << "PASSED " << b3 << " * " << " " << b4 << ": expected (" << result << "), actual: (" << b3 * b4 << ")" << endl;

		// avoid zero division
		if (b2 == 0) {
			b2 += 1;
			random_2 += 1;
		}

		cmp_result = (b1 / b2).cmp(random_1 / random_2);
 		if(cmp_result != equal)
			cout << "ERROR " << b1 << " / " << " " << b2 << ": expected (" << random_1 / random_2 << "), actual: (" << b1 / b2 << ")" << endl;
		else
			cout << "PASSED " << b1 << " / " << " " << b2 << ": expected (" << random_1 / random_2 << "), actual: (" << b1 / b2 << ")" << endl;

	}
}

int main() {
	test_init();
	test_copy();
	test_assignment();
	test_cmp();
	test_equality_operators();
	test_add();
	test_sub();
	test_mult();
	test_div();
	test_random();

	return 0;
}

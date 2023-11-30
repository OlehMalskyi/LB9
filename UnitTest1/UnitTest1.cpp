#include "pch.h"
#include "CppUnitTest.h"
#include "../LB9.3/LB9.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestSort)
        {
            const int N = 3;
            Bday B[N] = { {1, 1, 2000}, {2, 2, 1999}, {3, 3, 2001} };
            Zodiac S[N] = { {"C", "B", "A"}, {"A", "C", "B"}, {"B", "A", "C"} };

            sort(S, B, N);

            Assert::AreEqual("B", S[0].zodiac_sign.c_str());
            Assert::AreEqual(2, B[0].day);

            Assert::AreEqual("A", S[1].zodiac_sign.c_str());
            Assert::AreEqual(1, B[1].day);

            Assert::AreEqual("C", S[2].zodiac_sign.c_str());
            Assert::AreEqual(3, B[2].day);
        }
	};
}

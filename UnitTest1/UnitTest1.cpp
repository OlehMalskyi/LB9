#include "pch.h"
#include "CppUnitTest.h"
#include "../LB9.1_B/LB9.1_B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(MaxAverageEvaluationTest)
        {
            const int N = 3;
            Students students[N] = {
                {"Student1", 3, KN, 90, 85, 95},
                {"Student2", 2, ITIS, 88, 92, 87},
                {"Student3", 4, KI, 75, 80, 78}
            };

            double result = max_average_evaluation(students, N);

            Assert::AreEqual(77.6667, result, 0.0001);
        }
	};
}

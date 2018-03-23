#include <cmath>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsProject
{		
	TEST_CLASS(UtilsTest)
	{
	public:
		
		/**
		 * Тестирование нахождения евклидова расстояния между двумя точками
		 * Кейс 1:
		 * Input: 1D point 1.0 and 1D point 1.0
		 * Distance: 0.0
		 * Кейс 2:
		 * Input: 1D point 1.0 and 1D point 2.0
		 * Distance: 0.0
		 * Кейс 3:
		 * Input: 1D point 0.0 and 1D point -1.0
		 * Distance: 0.0
		 */
		TEST_METHOD(TestEuclidDistanceBetweenPoints)
		{
			double point1 = 1.0;
			double point2 = 1.0;
			double expected = 0;
			float eps = 0.00001f;
			double result = distance(point1, point2);
			Assert::IsTrue(abs(expected - result) < eps);
			point1 = 1.0;
			point2 = 2.0;
			expected = 1.0;
			result = distance(point1, point2);
			Assert::IsTrue(abs(expected - result) < eps);
			point1 = 0.0;
			point2 = -1.0;
			result = distance(point1, point2);
			Assert::IsTrue(abs(expected - result) < eps);
		}

		TEST_METHOD(TestDistanceBetweenSequences)
		{
			// TODO: Your test code here
			Assert::AreEqual(1, 1);
		}
	};
}
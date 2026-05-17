#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "C:\Users\User\source\repos\Project21\Project21\Header.h"

int* massive;
int* arr;
int K = 20000;
int result[2];

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Prepare)
		{
			srand(1);
			arr = new int[K - 2];
			int randGap = abs(rand()) % (K - 3);
			for (int k = 0; k < K - 2; k++) {
				arr[k] = k + 1 + ((k >= randGap) ? 2 : 0);
			}
			for (long i = 0; i < K - 2; i++) {
				int coord1 = i;
				int coord2 = abs(rand()) % (K - 2);
				swap(&arr[coord1], &arr[coord2]);
			}
			LLN_by_throwing(arr, K, result);
		}
		
		TEST_METHOD(Throwing)
		{
			int r[2];
			LLN_by_throwing(arr, K, r);
			//Assert::AreEqual(result[1], r[1]);
			Assert::AreEqual(result[0], r[0]);
		}
		TEST_METHOD(Selection)
		{
			int r[2];
			LLN_by_selection(arr, K, r);
			Assert::AreEqual(result[1], r[1]);
			Assert::AreEqual(result[0], r[0]);
		}
		TEST_METHOD(Sort)
		{
			int r[2];
			LLN_by_sort(arr, K, r);
			//Assert::AreEqual(result[1], r[1]);
			Assert::AreEqual(result[0], r[0]);
		}
		TEST_METHOD(Sum)
		{
			int r[2];
			LLN_by_sum(arr, K, r);
			Assert::AreEqual(result[1], r[1]);
			Assert::AreEqual(result[0], r[0]);
		}
		
	};
}

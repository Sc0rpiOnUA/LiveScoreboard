#include "pch.h"
#include "CppUnitTest.h"
#include "../LiveScoreboard/Scoreboard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(Basic)
	{
	public:		
		TEST_METHOD(Ping)
		{
			Scoreboard scoreboard;
			Assert::AreEqual(scoreboard.Ping(), std::string("Pong"));
		}
	};
}

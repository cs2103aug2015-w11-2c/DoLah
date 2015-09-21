#include "stdafx.h"
#include "CppUnitTest.h"

#include "basic.h"

#include "CommandTokenizer.h"
#include "TokenizerLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest {
    TEST_CLASS(Tokenize) {
public:

    TEST_METHOD(vectorToStringTest) {
        std::vector<std::string> input = { "1", "2", "3", "4", "5" };
        std::string expected = (std::string) "{ 1, 2, 3, 4, 5 }";
        Assert::AreEqual(expected, TokenizerLibrary::vectorToString(input));
    }

    TEST_METHOD(explodeTest) {
        std::string input = "add #cs2103 #homework on Thursday";
        std::string expected = (std::string) "{ add, #cs2103, #homework, on, Thursday }";
        Assert::AreEqual(expected, TokenizerLibrary::vectorToString(TokenizerLibrary::explode(input)));
    }

    TEST_METHOD(isCommandCaseTest) {
        CommandTokenizer ct;
        std::string input = "ADD";
        bool expected = true;
        Assert::AreEqual(expected, ct.isCommand(input));
    }

    TEST_METHOD(isCommandWrongInputTest) {
        CommandTokenizer ct;
        std::string input = "dispray";
        bool expected = false;
        Assert::AreEqual(expected, ct.isCommand(input));
    }

    };
}
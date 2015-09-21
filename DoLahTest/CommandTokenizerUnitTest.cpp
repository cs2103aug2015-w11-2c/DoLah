#include "stdafx.h"
#include "CppUnitTest.h"

#include "basic.h"

#include "CommandTokenizer.h"
#include "TokenizerLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest {
    TEST_CLASS(Tokenize) {
public:
    std::vector<std::string> commandList = { "add", "dislay", "undo", "delete", "edit", "clear", "search", "sort" };

    TEST_METHOD(vectorToStringTest) {
        std::vector<std::string> input = { "1", "2", "3", "4", "5" };
        std::string expected = (std::string) "{ 1, 2, 3, 4, 5 }";
        Assert::AreEqual(expected, TokenizerLibrary::vectorToString(input));
    }

    TEST_METHOD(explodeTest) {
        std::string input = "add #cs2103 #homework on Thursday";
        std::string arg1 = " ";
        std::string expected = (std::string) "{ add, #cs2103, #homework, on, Thursday }";
        Assert::AreEqual(expected, TokenizerLibrary::vectorToString(TokenizerLibrary::explode(input, arg1)));
    }

    TEST_METHOD(isCommandCaseTest) {
        std::string input = "ADD";
        bool expected = true;
        Assert::AreEqual(expected, TokenizerLibrary::inArray(commandList, input));
    }

    TEST_METHOD(isCommandWrongInputTest) {
        std::string input = "dispray";
        bool expected = false;
        Assert::AreEqual(expected, TokenizerLibrary::inArray(commandList, input));
    }

    };
}
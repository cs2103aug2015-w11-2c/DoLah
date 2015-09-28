#include "stdafx.h"
#include "CppUnitTest.h"

#include "basic.h"

#include "CommandTokenizer.h"
#include "TokenizerLibrary.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest {
    TEST_CLASS(Tokenize) {
public:
    TEST_METHOD(findCommandTest) {
        CommandTokenizer ct;
        std::string input = "add #cs2103 #homework on Thursday";
        std::string expected = (std::string) "{ add }";

        StringToken* obj = ct.findCommand(TokenizerLibrary::explode(input, " "));
        Assert::AreEqual(expected, TokenizerLibrary::vectorToString(obj->getData()));
    }

    TEST_METHOD(findTagsTest) {
        CommandTokenizer ct;
        std::string input = "add #cs2103 #homework on Thursday";
        std::string expected = (std::string) "{ homework, cs2103 }";

        StringToken* obj = ct.findTags(TokenizerLibrary::explode(input, " "));
        Assert::AreEqual(expected, TokenizerLibrary::vectorToString(obj->getData()));
    }

    TEST_METHOD(findDescriptionTest) {
        CommandTokenizer ct;
        std::string input = "add #cs2103 #homework on Thursday";
        std::string expected = (std::string) "{ #cs2103 #homework on Thursday }";

        StringToken* obj = ct.findDescription(TokenizerLibrary::explode(input, " "));
        Assert::AreEqual(expected, TokenizerLibrary::vectorToString(obj->getData()));
    }

    TEST_METHOD(findDateTest) {
        CommandTokenizer ct;
        std::string input = "add #cs2103 #homework on 17th of March";
        std::string expected = (std::string) "{ 17-03-2016 }";
        

        DateTimeToken* obj = ct.findDate(TokenizerLibrary::explode(input, " "));
        Assert::AreEqual(expected, TokenizerLibrary::vectorToString(obj->getData()));
    }
    };
}


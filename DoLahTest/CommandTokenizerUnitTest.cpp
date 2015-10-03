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
        std::string input = "add #cs2103 #homework on 30th Sep";
        std::string expected = (std::string) "{ add }";

        std::string* obj = ct.findCommand(TokenizerLibrary::explode(input, " "));
        Assert::AreEqual(expected, TokenizerLibrary::vectorToString(obj->getStringVector()));
    }

    TEST_METHOD(findTagsTest) {
        CommandTokenizer ct;
        std::string input = "add #cs2103 #homework on 30th Sep";
        std::string expected = (std::string) "{ homework, cs2103 }";

        std::string* obj = ct.findTags(TokenizerLibrary::explode(input, " "));
        Assert::AreEqual(expected, TokenizerLibrary::vectorToString(obj->getStringVector()));
    }

    TEST_METHOD(findDescriptionTest) {
        CommandTokenizer ct;
        std::string input = "add #cs2103 #homework on 30th Sep";
        std::string expected = (std::string) "{ #cs2103 #homework on 30th Sep }";

        std::string* obj = ct.findDescription(TokenizerLibrary::explode(input, " "));
        Assert::AreEqual(expected, TokenizerLibrary::vectorToString(obj->getStringVector()));
    }

    //TEST_METHOD(findDateTest) {
    //    CommandTokenizer ct;
    //    std::string input = "add #cs2103 #homework on 17th of March";
    //    std::string expected = (std::string) "{ 17-03-2016 }";
    //    

    //    DateTimeToken* obj = ct.findDate(TokenizerLibrary::explode(input, " "));
    //    Assert::AreEqual(expected, TokenizerLibrary::vectorToString(obj->getData()));
    //}

    TEST_METHOD(tokenizeAddTest) {
        CommandTokenizer ct;
        std::string input = "add #cs2103 #homework on 30th Sep";
        std::vector<std::string> expected = { "{ add }", "{ #cs2103 #homework on Thursday }", "{ homework, cs2103 }" };

        std::vector<ITokenObject *> obj = ct.tokenizeAdd(TokenizerLibrary::explode(input, " "));
        Assert::AreEqual(expected.at(0), TokenizerLibrary::vectorToString(obj.at(0)->getStringVector()));
        Assert::AreEqual(expected.at(1), TokenizerLibrary::vectorToString(obj.at(1)->getStringVector()));
        Assert::AreEqual(expected.at(2), TokenizerLibrary::vectorToString(obj.at(2)->getStringVector()));
    }
    };
}


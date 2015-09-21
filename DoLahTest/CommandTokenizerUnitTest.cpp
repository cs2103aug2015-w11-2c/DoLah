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
        Assert::AreEqual((std::string) "{ 1, 2, 3, 4, 5 }", TokenizerLibrary::vectorToString({"1", "2", "3", "4", "5"}));
    }

    TEST_METHOD(explodeTest) {
        Assert::AreEqual((std::string) "{ 1, 2, 3, 4, 5 }", TokenizerLibrary::vectorToString(TokenizerLibrary::explode("1 2 3 4 5")));
    }

    };
}
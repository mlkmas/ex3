#include <functional>

#include "TestUtils.h"
#include "Queue.h"
#include "iostream"

#define AGREGATE_TEST_RESULT(res, cond) (res) = ((res) && (cond))

static bool isEven(int n)
{
    return (n % 2) == 0;
}

static void setFortyTwo(int& n)
{
    n = 42;
}

namespace QueueTests {

    bool testQueueMethods()
    {
        bool testResult = true;

        Queue<int> queue1;
        queue1.pushBack(1);
        queue1.pushBack(2);
        int front1 = queue1.front();
        AGREGATE_TEST_RESULT(testResult, front1 == 1);

        queue1.front() = 3;
        front1 = queue1.front();
        AGREGATE_TEST_RESULT(testResult, front1 == 3);

        queue1.popFront();
        front1 = queue1.front();
        AGREGATE_TEST_RESULT(testResult, front1 == 2);

        int size1 = queue1.size();
        AGREGATE_TEST_RESULT(testResult, size1 == 1);

        return testResult;
    }

    bool testModuleFunctions()
    {
        bool testResult = true;
        Queue<int> queue3;
        for (int i = 1; i <= 10; i++) {
            queue3.pushBack(i);
        }

        Queue<int> queue4 = filter(queue3, isEven);
        for (int i = 2; i <= 10; i+=2) {
            int front4 = queue4.front();
            AGREGATE_TEST_RESULT(testResult, front4 == i);
            queue4.popFront();
        }

        Queue<int> queue5;
        for (int i = 1; i <= 5; i++) {
            queue5.pushBack(i);
        }
        transform(queue5, setFortyTwo);
        for (Queue<int>::Iterator i = queue5.begin(); i != queue5.end(); ++i) {

            AGREGATE_TEST_RESULT(testResult,(*i == 42));
        }

        return testResult;
    }

    bool testExceptions()
    {
        bool testResult = true;

        bool exceptionThrown = false;
        Queue<int> queue6;
        try {
            queue6.front() = 5;
        }
        catch (Queue<int>::EmptyQueue& e) {
            exceptionThrown = true;
        }
        AGREGATE_TEST_RESULT(testResult, exceptionThrown);

        exceptionThrown = false;
        Queue<int>::Iterator endIterator = queue6.end();
        try {
            ++endIterator;
        }
        catch (Queue<int>::Iterator::InvalidOperation& e) {
            exceptionThrown = true;
        }
        AGREGATE_TEST_RESULT(testResult, exceptionThrown);

        return testResult;
    }

    bool testConstQueue()
    {
        bool testResult = true;

        Queue<int> queue5;
        for (int i = 1; i <= 5; i++) {
            queue5.pushBack(42);
        }
        const Queue<int> constQueue = queue5;
        for (Queue<int>::ConstIterator i = constQueue.begin(); i != constQueue.end(); ++i) {
            AGREGATE_TEST_RESULT(testResult, (*i == 42));
        }

        bool exceptionThrown = false;
        Queue<int>::ConstIterator endConstIterator = constQueue.end();
        try {
            ++endConstIterator;
        }
        catch (Queue<int>::ConstIterator::InvalidOperation& e) {
            exceptionThrown = true;
        }
        AGREGATE_TEST_RESULT(testResult, exceptionThrown);

        return testResult;
    }

}
#include <sstream>
#include "HealthPoints.h"

namespace HealthPointsTests {

    static bool checkHealthPointsValues(const HealthPoints& healthPoints, int current, int max)
    {
        std::ostringstream expected;
        expected << current << '(' << max << ')';
        std::ostringstream result;
        result << healthPoints;
        return (expected.str() == result.str());
    }

    bool testInitialization()
    {
        bool testResult = true;

        HealthPoints healthPoints1; /* has 100 points out of 100 */
        HealthPoints healthPoints2(150); /* has 150 points out of 150 */
        bool exceptionThrown = false;
        try {
            HealthPoints healthPoints3(-100);
        }
        catch (HealthPoints::InvalidArgument& e) {
            exceptionThrown = true;
        }

        testResult = testResult && exceptionThrown;
        testResult = testResult && checkHealthPointsValues(healthPoints1, 100, 100);
        return testResult;
    }

    bool testArithmaticOperators()
    {
        bool testResult = true;
        HealthPoints healthPoints1; /* has 100 points out of 100 */
        HealthPoints healthPoints2(150); /* has 150 points out of 150 */

        healthPoints1 -= 20; /* now has 80 points out of 100 */
        testResult = testResult && checkHealthPointsValues(healthPoints1, 80, 100);

        healthPoints1 += 100; /* now has 100 points out of 100 */
        testResult = testResult && checkHealthPointsValues(healthPoints1, 100, 100);

        healthPoints1 -= 150; /* now has 0 points out of 100 */
        testResult = testResult && checkHealthPointsValues(healthPoints1, 0, 100);

        healthPoints2 = healthPoints2 - 160; /* now has 0 points out of 150 */
        testResult = testResult && checkHealthPointsValues(healthPoints2, 0, 150);

        healthPoints2 = 160 + healthPoints1; /* now has 100 out of 100 */
        testResult = testResult && checkHealthPointsValues(healthPoints2, 100, 100);

        return testResult;

    }

    bool testComparisonOperators()
    {
        bool testResult = true;
        HealthPoints healthPoints1 = HealthPoints(100); /* has 100 points out of 100 */
        HealthPoints healthPoints2 = 100; /* has 100 points out of 100 */
        bool comparisonResult;

        comparisonResult = (healthPoints1 == healthPoints2); /* returns true */
        testResult = testResult && comparisonResult;

        healthPoints2 = HealthPoints(150); /* has 150 points out of 150 */
        comparisonResult = (healthPoints1 == healthPoints2); /* returns false */
        testResult = testResult && !comparisonResult;

        healthPoints2 -= 50; /* now has 100 points out of 150 */
        comparisonResult = (healthPoints1 == healthPoints2); /* returns true */

        comparisonResult = (healthPoints1 < healthPoints2); /* returns false */
        testResult = testResult && !comparisonResult;

        healthPoints1 -= 50; /* now has 50 points out of 100 */
        comparisonResult = (healthPoints1 < healthPoints2); /* returns true */

        return testResult;
    }

    bool testOutputOperator()
    {
        bool testResult = true;
        std::ostringstream stream;

        HealthPoints healthPoints1 = HealthPoints(100); /* has 100 points out of 100 */
        healthPoints1 -= 50; /* now has 50 points out of 100 */
        stream << healthPoints1; /* stream content is "50(100)" */
        testResult = testResult && (stream.str() == "50(100)");

        HealthPoints healthPoints2 = HealthPoints(150); /* has 1500 points out of 150 */
        healthPoints2 -= 50; /* now has 100 points out of 150 */
        stream << ", " << healthPoints2; /* stream content is "50(100), 100(150)" */
        testResult = testResult && (stream.str() == "50(100), 100(150)");

        return testResult;
    }

}
namespace HealthPointsTests {
    bool testInitialization();
    bool testArithmaticOperators();
    bool testComparisonOperators();
    bool testOutputOperator();
}

namespace QueueTests {
    bool testQueueMethods();
    bool testModuleFunctions();
    bool testExceptions();
    bool testConstQueue();
}

std::function<bool()> testsList[] = {
        HealthPointsTests::testInitialization,
        HealthPointsTests::testArithmaticOperators,
        HealthPointsTests::testComparisonOperators,
        HealthPointsTests::testOutputOperator,

        QueueTests::testQueueMethods,
        QueueTests::testModuleFunctions,
        QueueTests::testExceptions,
        QueueTests::testConstQueue
};

const int NUMBER_OF_TESTS = sizeof(testsList)/sizeof(std::function<bool()>);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        for (int i = 0; i < NUMBER_OF_TESTS; ++i) {
            runTest(testsList[i], "Test " + std::to_string(i + 1));
        }
    }
    else {
        int idx = -1;
        try {
            idx = std::stoi(argv[1]) - 1;
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: invalid argument: " << argv[1] << std::endl;
            return 1;
        }
        if (idx < 0 || idx > NUMBER_OF_TESTS - 1) {
            std::cerr << "Error: index out of range: " << argv[1] << std::endl;
            return 1;
        }
        runTest(testsList[idx], "Test " + std::to_string(idx + 1));
    }
    return 0;
}
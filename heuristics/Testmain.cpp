/*
 * Author:    Xuanliang Deng
 * Descr:     Main function for heuristic priority assignment policies
 * Date:      May 23 2021
 * Version:   1.0
 * History:   
 *            None
 */
#include "heuristics.h"
#include <gtest/gtest.h>

/* Declare the function(s) that you are testing */
std::vector<Task> calculate_prio_DkC(int m, std::vector<Task> task_set);
std::vector<Task> calculate_prio_DMPO(std::vector<Task> task_set);
std::vector<Task> calculate_prio_DCMPO(std::vector<Task> task_set);

/* Override operator '==' for comparison */
/*
bool operator==( const Task& test, const Task& answer ) 
{
    return std::make_tuple( test.period, test.WCET, test.deadline, test.response, test.priority, test.value ) == std::make_tuple( answer.period, answer.WCET, answer.deadline, answer.response, answer.priority, answer.value );
}
*/

/* DkC unit tests */
TEST(DkCTestSuite, DkC_1m8_test)
{
    std::vector<Task> test_case, test_answer;

    test_case = readTaskFile("UnitTests/DkC_1m8.txt");
    test_answer = readTaskFile("UnitTests/DkC_1m8_answer.txt");

    test_case = calculate_prio_DkC(8,test_case);

    for(int i = 0; i< test_case.size(); ++i)
    {
        EXPECT_EQ(test_case[i].period, test_answer[i].period) << "The period does not match!";
        EXPECT_EQ(test_case[i].priority, test_answer[i].priority) << "The priority does not match!";
        EXPECT_EQ(test_case[i].WCET, test_answer[i].WCET) << "The WCET does not match!";
        EXPECT_EQ(test_case[i].deadline, test_answer[i].deadline) << "The deadline does not match!";
        EXPECT_EQ(test_case[i].response, test_answer[i].response) << "The response does not match!";
        EXPECT_NEAR(test_case[i].value, test_answer[i].value, 1.0e-3) << "The value does not match!";
    }
}

TEST(DkCTestSuite, DkC_1m4_test)
{
    std::vector<Task> test_case, test_answer;

    test_case = readTaskFile("UnitTests/DkC_1m4.txt");
    test_answer = readTaskFile("UnitTests/DkC_1m4_answer.txt");

    test_case = calculate_prio_DkC(4,test_case);

    for(int i = 0; i< test_case.size(); ++i)
    {
        EXPECT_EQ(test_case[i].period, test_answer[i].period) << "The period does not match!";
        EXPECT_EQ(test_case[i].priority, test_answer[i].priority) << "The priority does not match!";
        EXPECT_EQ(test_case[i].WCET, test_answer[i].WCET) << "The WCET does not match!";
        EXPECT_EQ(test_case[i].deadline, test_answer[i].deadline) << "The deadline does not match!";
        EXPECT_EQ(test_case[i].response, test_answer[i].response) << "The response does not match!";
        EXPECT_NEAR(test_case[i].value, test_answer[i].value, 1.0e-3) << "The value does not match!";
    }
}

TEST(DkCTestSuite, DkC_1m1_test)
{
    std::vector<Task> test_case, test_answer;

    test_case = readTaskFile("UnitTests/DkC_1m1.txt");
    test_answer = readTaskFile("UnitTests/DkC_1m1_answer.txt");

    test_case = calculate_prio_DkC(1,test_case);

    for(int i = 0; i< test_case.size(); ++i)
    {
        EXPECT_EQ(test_case[i].period, test_answer[i].period) << "The period does not match!";
        EXPECT_EQ(test_case[i].priority, test_answer[i].priority) << "The priority does not match!";
        EXPECT_EQ(test_case[i].WCET, test_answer[i].WCET) << "The WCET does not match!";
        EXPECT_EQ(test_case[i].deadline, test_answer[i].deadline) << "The deadline does not match!";
        EXPECT_EQ(test_case[i].response, test_answer[i].response) << "The response does not match!";
        EXPECT_NEAR(test_case[i].value, test_answer[i].value, 1.0e-3) << "The value does not match!";
    }
}

TEST(DkCTestSuite, DkC_2m2_test)
{
    std::vector<Task> test_case, test_answer;

    test_case = readTaskFile("UnitTests/DkC_2m2.txt");
    test_answer = readTaskFile("UnitTests/DkC_2m2_answer.txt");

    test_case = calculate_prio_DkC(2,test_case);

    for(int i = 0; i< test_case.size(); ++i)
    {
        EXPECT_EQ(test_case[i].period, test_answer[i].period) << "The period does not match!";
        EXPECT_EQ(test_case[i].priority, test_answer[i].priority) << "The priority does not match!";
        EXPECT_EQ(test_case[i].WCET, test_answer[i].WCET) << "The WCET does not match!";
        EXPECT_EQ(test_case[i].deadline, test_answer[i].deadline) << "The deadline does not match!";
        EXPECT_EQ(test_case[i].response, test_answer[i].response) << "The response does not match!";
        EXPECT_NEAR(test_case[i].value, test_answer[i].value, 1.0e-3) << "The value does not match!";
    }
}

TEST(DMPOTestSuite, DMPO_1m8_test)
{
    std::vector<Task> test_case, test_answer;

    test_case = readTaskFile("UnitTests/DMPO_1m8.txt");
    test_answer = readTaskFile("UnitTests/DMPO_1m8_answer.txt");

    test_case = calculate_prio_DMPO(test_case);

    for(int i = 0; i< test_case.size(); ++i)
    {
        EXPECT_EQ(test_case[i].period, test_answer[i].period) << "The period does not match!";
        EXPECT_EQ(test_case[i].priority, test_answer[i].priority) << "The priority does not match!";
        EXPECT_EQ(test_case[i].WCET, test_answer[i].WCET) << "The WCET does not match!";
        EXPECT_EQ(test_case[i].deadline, test_answer[i].deadline) << "The deadline does not match!";
        EXPECT_EQ(test_case[i].response, test_answer[i].response) << "The response does not match!";
        EXPECT_NEAR(test_case[i].value, test_answer[i].value, 1.0e-3) << "The value does not match!";
    }
}

TEST(DMPOTestSuite, DMPO_2m8_test)
{
    std::vector<Task> test_case, test_answer;

    test_case = readTaskFile("UnitTests/DMPO_2m8.txt");
    test_answer = readTaskFile("UnitTests/DMPO_2m8_answer.txt");

    test_case = calculate_prio_DMPO(test_case);

    for(int i = 0; i< test_case.size(); ++i)
    {
        EXPECT_EQ(test_case[i].period, test_answer[i].period) << "The period does not match!";
        EXPECT_EQ(test_case[i].priority, test_answer[i].priority) << "The priority does not match!";
        EXPECT_EQ(test_case[i].WCET, test_answer[i].WCET) << "The WCET does not match!";
        EXPECT_EQ(test_case[i].deadline, test_answer[i].deadline) << "The deadline does not match!";
        EXPECT_EQ(test_case[i].response, test_answer[i].response) << "The response does not match!";
        EXPECT_NEAR(test_case[i].value, test_answer[i].value, 1.0e-3) << "The value does not match!";
    }
}

TEST(DCMPOTestSuite, DCMPO_1m8_test)
{
    std::vector<Task> test_case, test_answer;

    test_case = readTaskFile("UnitTests/DCMPO_1m8.txt");
    test_answer = readTaskFile("UnitTests/DCMPO_1m8_answer.txt");

    test_case = calculate_prio_DCMPO(test_case);

    for(int i = 0; i< test_case.size(); ++i)
    {
        EXPECT_EQ(test_case[i].period, test_answer[i].period) << "The period does not match!";
        EXPECT_EQ(test_case[i].priority, test_answer[i].priority) << "The priority does not match!";
        EXPECT_EQ(test_case[i].WCET, test_answer[i].WCET) << "The WCET does not match!";
        EXPECT_EQ(test_case[i].deadline, test_answer[i].deadline) << "The deadline does not match!";
        EXPECT_EQ(test_case[i].response, test_answer[i].response) << "The response does not match!";
        EXPECT_NEAR(test_case[i].value, test_answer[i].value, 1.0e-3) << "The value does not match!";
    }
}

/*
TEST(DCMPOTestSuite, DCMPO_1m8_test)
{
    std::vector<Task> test_case, test_answer;

    test_case = readTaskFile("UnitTests/DCMPO_1m8.txt");
    test_answer = readTaskFile("UnitTests/DCMPO_1m8_answer.txt");

    test_case = calculate_prio_DCMPO(test_case);

    for(int i = 0; i< test_case.size(); ++i)
    {
        EXPECT_EQ(test_case[i].period, test_answer[i].period) << "The period does not match!";
        EXPECT_EQ(test_case[i].priority, test_answer[i].priority) << "The priority does not match!";
        EXPECT_EQ(test_case[i].WCET, test_answer[i].WCET) << "The WCET does not match!";
        EXPECT_EQ(test_case[i].deadline, test_answer[i].deadline) << "The deadline does not match!";
        EXPECT_EQ(test_case[i].response, test_answer[i].response) << "The response does not match!";
        EXPECT_NEAR(test_case[i].value, test_answer[i].value, 1.0e-3) << "The value does not match!";
    }
}
*/

/*
TEST(DMPOTestSuite, DMPO_2m8_test)
{
    std::vector<Task> test_case, test_answer;

    test_case = readTaskFile("UnitTests/DkC_2m2.txt");
    test_answer = readTaskFile("UnitTests/DkC_2m2_answer.txt");

    test_case = calculate_prio_DkC(2,test_case);

    for(int i = 0; i< test_case.size(); ++i)
    {
        EXPECT_EQ(test_case[i].period, test_answer[i].period) << "The period does not match!";
        EXPECT_EQ(test_case[i].priority, test_answer[i].priority) << "The priority does not match!";
        EXPECT_EQ(test_case[i].WCET, test_answer[i].WCET) << "The WCET does not match!";
        EXPECT_EQ(test_case[i].deadline, test_answer[i].deadline) << "The deadline does not match!";
        EXPECT_EQ(test_case[i].response, test_answer[i].response) << "The response does not match!";
        EXPECT_NEAR(test_case[i].value, test_answer[i].value, 1.0e-3) << "The value does not match!";
    }
}
*/




int main(int argc, char **argv) 
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


/*
int main()
{
    int m = 8;

    std::vector<Task> task_set;
    std::string fileName = "UnitTests/DkC_1m8.txt";
    
    task_set = readTaskFile(fileName);
    task_set = calculate_prio_DkC(m, task_set);

    return 0;
}
*/


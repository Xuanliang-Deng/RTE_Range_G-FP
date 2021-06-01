#include "GSYY.h"
#include <gtest/gtest.h>

// m is the number of processors

TEST(GSYY4TaskSuite, four_task_case_1)
{
    int m = 2;
    std::vector<Task> test_case, test_answer;

    test_case = readTaskFile("tests/task_set_1.txt");
    test_answer = readTaskFile("tests/task_set_1_answer.txt");

    test_case = GSYY_unit_test(m, test_case);

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

TEST(GSYY4TaskSuite, four_task_case_2)
{
    int m = 3;
    std::vector<Task> test_case, test_answer;

    test_case = readTaskFile("tests/task_set_2.txt");
    test_answer = readTaskFile("tests/task_set_2_answer.txt");

    test_case = GSYY_unit_test(m, test_case);

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

TEST(GSYY2TaskSuite, two_task_case_1)
{
    int m = 4;
    std::vector<Task> test_case, test_answer;

    test_case = readTaskFile("tests/task_set_3.txt");
    test_answer = readTaskFile("tests/task_set_3_answer.txt");

    test_case = GSYY_unit_test(m, test_case);

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

TEST(GSYY3TaskSuite, three_task_case_1)
{
    int m = 2;
    std::vector<Task> test_case, test_answer;

    test_case = readTaskFile("tests/task_set_4.txt");
    test_answer = readTaskFile("tests/task_set_4_answer.txt");

    test_case = GSYY_unit_test(m, test_case);

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

TEST(GSYY3TaskSuite, three_task_case_2)
{
    int m = 2;
    std::vector<Task> test_case, test_answer;

    test_case = readTaskFile("tests/task_set_5.txt");
    test_answer = readTaskFile("tests/task_set_5_answer.txt");

    test_case = GSYY_unit_test(m, test_case);

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

int main(int argc, char **argv) 
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
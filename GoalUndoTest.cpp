/**
 * Unit Tests for GoalUndo class
 **/

#include <gtest/gtest.h>
#include "GoalUndo.h"

class GoalUndoTest : public ::testing::Test
{
    protected:
        GoalUndoTest(){}
        virtual ~GoalUndoTest(){}
        virtual void SetUp(){}
        virtual void TearDown(){}
};

TEST(GoalUndoTest, sanityCheck)
{
    ASSERT_TRUE(true);
}

TEST(GoalUndoTest, AddingSingleOperation)
{
    GoalUndo test;

    test.addOperation("SomeOp");

    ASSERT_EQ("SomeOp", test.getOperations());
}

TEST(GoalUndoTest, SameNameGetOp)
{
    GoalUndo test;
    //test
    test.addOperation("SomeOp");

    ASSERT_EQ("SomeOp", test.getOperations());
}

TEST(GoalUndoTest, SameNameGetGoal)
{
    GoalUndo test;
    test.addOperation("SomeOp");

    ASSERT_EQ("SomeOp", test.getGoal());
}

TEST(GoalUndoTest, GoalUndoSameNameOp)
{
    GoalUndo test;
    test.addOperation("SomeOp");

    ASSERT_EQ("SomeOp", test.getGoal());
    //getoperation
    ASSERT_EQ("SomeOp", test.getOperations());
}



TEST(GoalUndoTest, AddingMultipleOperation)
{
    GoalUndo test;
    for (int i = 0; i < 50; ++i)
    {
        test.addOperation("SomeOp");
    }
    for (int i = 0; i < 50; ++i)
    {
        test.undoOperation("SomeOp");
    }
    ASSERT_EQ("", test.getOperations());
}

TEST(GoalUndoTest, CheckingIfEmpty)
{
    GoalUndo test;
    ASSERT_EQ("", test.getGoal());
}

TEST(GoalUndoTest, CheckingIfItIsNotEmpty)
{
    GoalUndo test;
    test.addOperation("abc", "xyz");
    ASSERT_EQ("abc", test.getGoal());
}

TEST(GoalUndoTest, GoalUndoMultipleOp)
{
    GoalUndo test;
    test.addOperation("SomeOp", "a");
    for(int i=0; i<50; i++)
    {
        test.addOperation("a");
    }
    for(int i=0; i<47; i++)
    {
        //test.addOperation("a");
        test.undoOperation();
    }
    ASSERT_EQ("a a a a", test.getOperations());
}

TEST(GoalUndoTest, DeleteSimilarOp)
{
    GoalUndo test;
    test.addOperation("SomeOp", "Op1");
    test.addOperation("Op1");
    test.addOperation("Op2");

    ASSERT_EQ("Op1 Op1 Op2", test.getOperations());
}

TEST(GoalUndoTest, UnavailableOperation)
{
    GoalUndo test;
    test.undoOperation("Op1");
    ASSERT_EQ("", test.getOperations());
}


TEST(GoalUndoTest, GoalUndoOp)
{
    GoalUndo test;
    test.addOperation("SomeOp", "Op_1");
    for(int i=0; i<14; i++)
    {
        test.addOperation("Op_1");
    }

    for(int i=0; i<15; i++)
    {
        test.undoOperation();
    }

    ASSERT_EQ("", test.getGoal());
}

TEST(GoalUndoTest, AddGoalNoName)
{
    GoalUndo test;
    test.addOperation("", "");
    test.addOperation("");

    ASSERT_EQ("", test.getGoal());
}

TEST(GoalUndoTest, GoalUndoGetGoal)
{
    GoalUndo test;
    test.addOperation("SomeOp");

    ASSERT_EQ("SomeOp", test.getGoal());
}

TEST(GoalUndoTest, AddEmptyNameNoOp)
{
    GoalUndo test;
    test.addOperation("", "");
    test.addOperation("");

    ASSERT_EQ("", test.getOperations());
}

TEST(GoalUndoTest, EmptyOpNameGoal)
{
    GoalUndo test;
    test.addOperation("SomeOp", "");
    ASSERT_EQ("", test.getGoal());
}

TEST(GoalUndoTest, AddingAdjacentsEntries)
{
    GoalUndo test;
    test.addOperation("ComputerScience", "Software");
    test.addOperation("Gaming");
    test.addOperation("Compiler");
    test.addOperation("Management", "SAP");
    test.addOperation("Hadoop");
    test.addOperation("SoftSkills");
    test.addOperation("Commerce", "Accounts");
    test.addOperation("Economics");
    test.addOperation("Maths");

    ASSERT_EQ("Commerce", test.getGoal());
    ASSERT_EQ("Accounts Economics Maths", test.getOperations());
    test.undoGoal();

    ASSERT_EQ("Management", test.getGoal());
    ASSERT_EQ("SAP Hadoop SoftSkills", test.getOperations());
    test.undoGoal();

    ASSERT_EQ("ComputerScience", test.getGoal());
    ASSERT_EQ("Software Gaming Compiler", test.getOperations());

    test.undoGoal();
    ASSERT_EQ("", test.getGoal());
    test.undoGoal();
    ASSERT_EQ("", test.getGoal());
    ASSERT_EQ("", test.getOperations());
}

#include "iostream"
#include "ToDoList.h"
#include <gtest/gtest.h>

class test_ToDoList: public testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(test_ToDoList, test_DefaultConstructor)
{  
    ToDoList t;

    stringstream output; // output for storing ostream
  
    t.write(output);
    EXPECT_STREQ("", output.str().c_str()); // with empty string
}

TEST_F(test_ToDoList, test_addItem_single)
{
    ToDoList t;
    stringstream output; // output for storing ostream

    // test addItem()
    t.addItem("finish COMP 1633 assignment 1", 3);
    t.write(output);

    EXPECT_STREQ("3 finish COMP 1633 assignment 1\n", output.str().c_str()); 
}

TEST_F(test_ToDoList, test_addItem_multiple)
{
    ToDoList t;
    stringstream output; // output for storing ostream

    // test addItem()
    t.addItem("finish COMP 1633 assignment 1", 3);
    t.addItem("pay overdue MasterCard bill", 2);
    t.addItem("do laundry", 1);
    t.addItem("make dentist appointment", 3);

    // expected output
    char todo_list[1024] = "3 finish COMP 1633 assignment 1\n";
    strcat(todo_list, "3 make dentist appointment\n");
    strcat(todo_list, "2 pay overdue MasterCard bill\n");
    strcat(todo_list, "1 do laundry\n");

    t.write(output);
    EXPECT_STREQ(todo_list, output.str().c_str()); 
}

TEST_F(test_ToDoList, test_load)
{
    ToDoList t;
    stringstream outfile;

    // infile 
    stringstream infile;
    infile << "3 finish COMP 1633 assignment 1\n"
	   << "3 make dentist appointment\n"
	   << "2 pay overdue MasterCard bill\n"
	   << "1 do laundry\n";

    // test load()
    t.load(infile);

    // expected result
    char expect[1024] = "3 finish COMP 1633 assignment 1\n";
    strcat(expect, "3 make dentist appointment\n");
    strcat(expect, "2 pay overdue MasterCard bill\n");
    strcat(expect, "1 do laundry\n");

    // test load()
    t.write(outfile);
    EXPECT_STREQ(expect, outfile.str().c_str()); 
}

TEST_F(test_ToDoList, test_display_single)
{
    ToDoList t;
    stringstream output;

    // prepare infile 
    stringstream infile;
    infile << "2 pay overdue MasterCard bill\n";
    t.load(infile);

    // prepare expected result
    char expect[1024] = "Medium Priority:\n\n";
    strcat(expect, "1:      - pay overdue MasterCard bill\n\n");

    // test display()
    t.display(output);

    EXPECT_STREQ(expect, output.str().c_str()); 
}

TEST_F(test_ToDoList, test_display_multiple)
{
    ToDoList t;
    stringstream output;

    // prepare infile 
    stringstream infile;
    infile << "3 finish COMP 1633 assignment 1\n"
	   << "3 make dentist appointment\n"
	   << "2 pay overdue MasterCard bill\n"
	   << "1 do laundry\n";
    t.load(infile);

    // prepare expected result
    char expect[1024] = "High Priority:\n\n";
    strcat(expect, "1:      - finish COMP 1633 assignment 1\n");
    strcat(expect, "2:      - make dentist appointment\n");
    strcat(expect, "\nMedium Priority:\n\n");
    strcat(expect, "3:      - pay overdue MasterCard bill\n");
    strcat(expect, "\nLow Priority:\n\n");
    strcat(expect, "4:      - do laundry\n\n");

    // test display()
    t.display(output);

    EXPECT_STREQ(expect, output.str().c_str()); 
}

TEST_F(test_ToDoList, test_removeItem_multiple)
{
    ToDoList t;
    stringstream output;

    // prepare infile 
    stringstream infile;
    infile << "3 finish COMP 1633 assignment 1\n"
	   << "3 make dentist appointment\n"
	   << "2 pay overdue MasterCard bill\n"
	   << "1 do laundry\n";
    t.load(infile);

    // prepare expected result
    char expect[1024] = "High Priority:\n\n";
    strcat(expect, "1:      - finish COMP 1633 assignment 1\n");
    strcat(expect, "\nMedium Priority:\n\n");
    strcat(expect, "2:      - pay overdue MasterCard bill\n");
    strcat(expect, "\nLow Priority:\n\n");
    strcat(expect, "3:      - do laundry\n\n");

    // test removeItem(): delete second item "3 make dentist appointment"
    t.removeItem(2);

    t.display(output);
    EXPECT_STREQ(expect, output.str().c_str()); 
}

TEST_F(test_ToDoList, test_removeItem_singleton)
{
    ToDoList t;
    char empty[] = "empty priority list";
    stringstream output;

    // prepare infile 
    stringstream infile;
    infile << "2 pay overdue MasterCard bill\n";

    t.load(infile);

    // test removeItem()
    t.removeItem(1);

    t.display(output);
    EXPECT_STREQ(empty, output.str().c_str()); 
}

TEST_F(test_ToDoList, test_lookup_found)
{
    ToDoList t;
    char desc[DESCRIPTION_LENGTH+1];
    int priority;
    bool found;

    // prepare infile 
    stringstream infile;
    infile << "3 finish COMP 1633 assignment 1\n"
	   << "3 make dentist appointment\n"
	   << "2 pay overdue MasterCard bill\n"
	   << "1 do laundry\n";  
    t.load(infile);
  
    // test lookup()
    t.lookup(2, desc, priority, found);

    EXPECT_EQ(3, priority);    
    EXPECT_TRUE(strcmp ("make dentist appointment", desc) == 0); 
    EXPECT_TRUE(found); 
}

TEST_F(test_ToDoList, test_lookup_notFound)
{
    ToDoList t;
    char desc[DESCRIPTION_LENGTH+1];
    int priority;
    bool found;

    // prepare infile 
    stringstream infile;
    infile << "3 finish COMP 1633 assignment 1\n"
	   << "2 pay overdue MasterCard bill\n"
	   << "1 do laundry\n";  
    t.load(infile);
  
    // test lookup()
    t.lookup(4, desc, priority, found);

    EXPECT_FALSE(found); 
}

TEST_F(test_ToDoList, test_removeItem_random)
{
    ToDoList t;
    stringstream output;

    // prepare infile 
    stringstream infile;
    infile << "3 finish COMP 1633 assignment 1\n"
	   << "3 make dentist appointment\n"
	   << "2 pay overdue MasterCard bill\n"
	   << "2 call Dad\n"
	   << "1 make coffee\n";
    t.load(infile);

    // delete 4th
    char expect[1024] = "High Priority:\n\n";
    strcat(expect, "1:      - finish COMP 1633 assignment 1\n");
    strcat(expect, "2:      - make dentist appointment\n\n");
    strcat(expect, "Medium Priority:\n\n");
    strcat(expect, "3:      - pay overdue MasterCard bill\n\n");
    strcat(expect, "Low Priority:\n\n");
    strcat(expect, "4:      - make coffee\n\n"); // from 5th to 4th
    // test
    output.str(""); // reset output stream
    t.removeItem(4);
    t.display(output);
    EXPECT_STREQ(expect, output.str().c_str()); 

    // delete 3rd
    memset(expect, 0, sizeof(expect)); // reset expect output 
    strcat(expect, "High Priority:\n\n");
    strcat(expect, "1:      - finish COMP 1633 assignment 1\n");
    strcat(expect, "2:      - make dentist appointment\n\n");
    strcat(expect, "Low Priority:\n\n");  
    strcat(expect, "3:      - make coffee\n\n"); // from 4th to 3rd
    // test
    output.str(""); // reset output stream
    t.removeItem(3);
    t.display(output);
    EXPECT_STREQ(expect, output.str().c_str()); 

    // delete 2nd
    memset(expect, 0, sizeof(expect)); // reset expect output 
    strcat(expect, "High Priority:\n\n");
    strcat(expect, "1:      - finish COMP 1633 assignment 1\n\n");
    strcat(expect, "Low Priority:\n\n");  
    strcat(expect, "2:      - make coffee\n\n"); // from 3rd to 2nd
    // test
    output.str(""); // reset output stream
    t.removeItem(2);
    t.display(output);
    EXPECT_STREQ(expect, output.str().c_str()); 
}

TEST_F(test_ToDoList, test_removeItem_lastItem)
{
    ToDoList t;
    stringstream output;
    bool isRemoved;

    // prepare infile 
    stringstream infile;
    infile << "3 finish COMP 1633 assignment 1\n"
	   << "3 make dentist appointment\n"
	   << "3 take medicine\n"
	   << "2 pay overdue MasterCard bill\n"
	   << "2 call Dad\n"
	   << "2 meal prep\n"
	   << "1 do laundry\n"
	   << "1 lecture prep\n"
	   << "1 make coffee\n";
    t.load(infile);

    // delete 9th
    char expect[1024] = "High Priority:\n\n";
    strcat(expect, "1:      - finish COMP 1633 assignment 1\n");
    strcat(expect, "2:      - make dentist appointment\n");
    strcat(expect, "3:      - take medicine\n\n");
    strcat(expect, "Medium Priority:\n\n");
    strcat(expect, "4:      - pay overdue MasterCard bill\n");
    strcat(expect, "5:      - call Dad\n");
    strcat(expect, "6:      - meal prep\n\n");
    strcat(expect, "Low Priority:\n\n");
    strcat(expect, "7:      - do laundry\n");
    strcat(expect, "8:      - lecture prep\n\n");
    // test
    isRemoved = t.removeItem(9);
    t.display(output);
    EXPECT_STREQ(expect, output.str().c_str()); 
    EXPECT_TRUE(isRemoved);

    // delete 8th
    memset(expect, 0, sizeof(expect)); // reset expect output 
    strcat(expect, "High Priority:\n\n");
    strcat(expect, "1:      - finish COMP 1633 assignment 1\n");
    strcat(expect, "2:      - make dentist appointment\n");
    strcat(expect, "3:      - take medicine\n\n");
    strcat(expect, "Medium Priority:\n\n");
    strcat(expect, "4:      - pay overdue MasterCard bill\n");
    strcat(expect, "5:      - call Dad\n");
    strcat(expect, "6:      - meal prep\n\n");
    strcat(expect, "Low Priority:\n\n");
    strcat(expect, "7:      - do laundry\n\n");
    // test
    output.str(""); // reset output stream
    t.removeItem(8);
    t.display(output);
    EXPECT_STREQ(expect, output.str().c_str()); 
    EXPECT_TRUE(isRemoved);

    // delete 7th
    memset(expect, 0, sizeof(expect)); // reset expect output 
    strcat(expect, "High Priority:\n\n");
    strcat(expect, "1:      - finish COMP 1633 assignment 1\n");
    strcat(expect, "2:      - make dentist appointment\n");
    strcat(expect, "3:      - take medicine\n\n");
    strcat(expect, "Medium Priority:\n\n");
    strcat(expect, "4:      - pay overdue MasterCard bill\n");
    strcat(expect, "5:      - call Dad\n");
    strcat(expect, "6:      - meal prep\n\n");
    // test
    output.str(""); // reset output stream
    t.removeItem(7);
    t.display(output);
    EXPECT_STREQ(expect, output.str().c_str()); 
    EXPECT_TRUE(isRemoved);

    // delete 6th
    memset(expect, 0, sizeof(expect)); // reset expect output 
    strcat(expect, "High Priority:\n\n");
    strcat(expect, "1:      - finish COMP 1633 assignment 1\n");
    strcat(expect, "2:      - make dentist appointment\n");
    strcat(expect, "3:      - take medicine\n\n");
    strcat(expect, "Medium Priority:\n\n");
    strcat(expect, "4:      - pay overdue MasterCard bill\n");
    strcat(expect, "5:      - call Dad\n\n");
    // test
    output.str(""); // reset output stream
    t.removeItem(6);
    t.display(output);
    EXPECT_STREQ(expect, output.str().c_str()); 
    EXPECT_TRUE(isRemoved);

    // delete 5th
    memset(expect, 0, sizeof(expect)); // reset expect output 
    strcat(expect, "High Priority:\n\n");
    strcat(expect, "1:      - finish COMP 1633 assignment 1\n");
    strcat(expect, "2:      - make dentist appointment\n");
    strcat(expect, "3:      - take medicine\n\n");
    strcat(expect, "Medium Priority:\n\n");
    strcat(expect, "4:      - pay overdue MasterCard bill\n\n");
    // test
    output.str(""); // reset output stream
    t.removeItem(5);
    t.display(output);
    EXPECT_STREQ(expect, output.str().c_str()); 
    EXPECT_TRUE(isRemoved);

    // delete 4th
    memset(expect, 0, sizeof(expect)); // reset expect output 
    strcat(expect, "High Priority:\n\n");
    strcat(expect, "1:      - finish COMP 1633 assignment 1\n");
    strcat(expect, "2:      - make dentist appointment\n");
    strcat(expect, "3:      - take medicine\n\n");  
    // test
    output.str(""); // reset output stream
    t.removeItem(4);
    t.display(output);
    EXPECT_STREQ(expect, output.str().c_str()); 
    EXPECT_TRUE(isRemoved);

    // delete 3rd
    memset(expect, 0, sizeof(expect)); // reset expect output 
    strcat(expect, "High Priority:\n\n");
    strcat(expect, "1:      - finish COMP 1633 assignment 1\n");
    strcat(expect, "2:      - make dentist appointment\n\n");
    // test
    output.str(""); // reset output stream
    t.removeItem(3);
    t.display(output);
    EXPECT_STREQ(expect, output.str().c_str()); 
    EXPECT_TRUE(isRemoved);

    // delete 2rd
    memset(expect, 0, sizeof(expect)); // reset expect output 
    strcat(expect, "High Priority:\n\n");
    strcat(expect, "1:      - finish COMP 1633 assignment 1\n\n");
    // test
    output.str(""); // reset output stream
    t.removeItem(2);
    t.display(output);
    EXPECT_STREQ(expect, output.str().c_str()); 
    EXPECT_TRUE(isRemoved);

    // delete final
    memset(expect, 0, sizeof(expect)); // reset expect output 
    strcat(expect, "empty priority list");
    // test
    output.str(""); // reset output stream
    t.removeItem(1);
    t.display(output);
    EXPECT_STREQ("empty priority list", output.str().c_str()); 
    EXPECT_TRUE(isRemoved);
}

TEST_F(test_ToDoList, test_removeItem_3thru1) 
{
    ToDoList t;
    stringstream output;    

    // prepare infile
    stringstream infile;
    infile << "3 finish COMP 1633 assignment 1\n"
	   << "3 make dentist appointment\n"
	   << "3 pay overdue MasterCard bill\n";
    t.load(infile);

    // test removeItem()
    t.removeItem(1);
    t.removeItem(1);
    t.removeItem(1);
    t.display(output);
    EXPECT_STREQ("empty priority list", output.str().c_str()); 
}

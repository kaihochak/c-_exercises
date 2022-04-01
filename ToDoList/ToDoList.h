/*
              
Name:        Kai Ho Chak     
Date:        March 30, 2021       
              
*/

#ifndef TODOLIST_H
#define TODOLIST_H

/******************************************************************************
* ToDoList()
*    default constructor
*
* ~ToDoList()
*    deconstructor
*
* void load(istream &infile)
*    load an istream and read the todo list 
*    
* void write(ostream &outfile) const
*    write an given outfile the todo list
* 
* void display(ostream &out) const
*    display to the ostream the todo list from High to Low priority, if there is
*    number for items is also assignment accordingly    
*
* void addItem(const char desc[], int priority)
*    receive the given description and priority of the todo item
*    create a corresponding todo item and add to the todo list    
*
* bool removeItem(int pos)
*    receive the number of a todo item, then remove it from todo list 
*    return true if it is successful, otherwise false
*
* void lookup(int pos, char desc[], int &priority, bool &found) const
*    receive the number of a todo item, then look it up from todo list 
*    return the corresponding description and priority
*    also return true if such todo item is found, otherwise false
*
******************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

const int DESCRIPTION_LENGTH = 60;
const int DESCRIPTION_MIN = 1;

const int HIGH = 3;
const int MEDIUM = 2;
const int LOW = 1;
const int INVALID = 0;

const int NUM_PRIORITIES = HIGH;

class ToDoList
{
 public:
  ToDoList();
  ~ToDoList();

  void load(istream &infile);
  void write(ostream &outfile) const;
  void display(ostream &out) const;
  void addItem(const char desc[], int priority);
  bool removeItem(int pos);
  void lookup(int pos, char desc[], int &priority, bool &found) const;

 private:
  struct ToDoNode
  {
    ToDoNode *next;
    ToDoNode *prev;
    char desc[DESCRIPTION_LENGTH + 1];
  };

  typedef ToDoNode *ToDoNodePtr;

  bool getAt(int pos, ToDoNodePtr &item, int &priority) const;
  ToDoNodePtr createItem(const char desc[]) const;
  void link(ToDoNodePtr item, int priority);
  void unlink(ToDoNodePtr item);
  void displayPriority(int priority, int &position, ostream &out) const;

  ToDoNode head[NUM_PRIORITIES]; // dummy boundary HEAD node
  ToDoNode tail[NUM_PRIORITIES]; // dummy boundary TAIL node
};


#endif

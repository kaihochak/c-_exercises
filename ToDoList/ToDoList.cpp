/*
          
Title:    To Do List

Name:     Kai Ho Chak     
Date:     March 30, 2021       

              
*/

/******************************************************************************
* struct ToDoNode
*  {
*    ToDoNode *next;
*    ToDoNode *prev;
*    char desc[DESCRIPTION_LENGTH + 1];
*  };
*    a node of todo item, comprised of a next pointer that points to the next
*    todo item of the same priority if there is, and a prev pointer that points
*    to the previous todo item of the same priority if there is. desc is the 
*    description of the todo item.
*    
* typedef ToDoNode *ToDoNodePtr;
*    a pointer to the ToDoNode 
*    
* bool getAt(int pos, ToDoNodePtr &item, int &priority) const
*    searches the "to-do" list for a given position and returns a pointer to 
*    the node at this position and its priority
*    return true if such todo item is found, false otherwise.
* 
* ToDoNodePtr createItem(const char desc[]) const
*    creates a new item node (not yet linked in to the data structure)
*
* void link(ToDoNodePtr item, int priority)
*    links an existing item node into the data structure
*
* void unlink(ToDoNodePtr item)
*    unlinks an item node from the data structure (does not deallocate memory)
*
* void displayPriority(int priority, int &position, ostream &out) const
*    displays all items of a given priority to the given output stream
*
* ToDoNode head[NUM_PRIORITIES] 
* ToDoNode tail[NUM_PRIORITIES]
*    two parallel array of "dummy" boundary nodes, each element is the 
*    head/tail of the linked list of todo items in the differnt priority   
*    i.e. head[0] is the head of the low priority item list
*    i.e. tail[2] is the tail of the high priority item list
*
******************************************************************************/

#include "ToDoList.h"
#include <cstring>

/* 
  Private Methods
*/

bool ToDoList::getAt(int pos, ToDoNodePtr &item, int &priority) const
{
  bool canGet = false;
  ToDoNodePtr current = NULL;
  int count = 0;
  priority = HIGH;

  // make sure position is not zero
  if ( pos > 0 )
  {
    // traverse priority until no more node or get to the position
    while ( priority > INVALID && count < pos )
    {
      current = head[priority-1].next; // start from first of the priorty 

      while ( current != &tail[priority-1] && count < pos )
      {
        count++; // count if not dummy node

        if ( count < pos )   // traverse if not get to the target item
        {
          current = current->next;
        }
      }

      // stop updating the priority, if it's found 
      if ( count < pos )
      {
        priority--;
      } 
    }

    // prepare the node pointer and priority, if successfully get
    if ( count == pos )
    {
      item = current;
      canGet = true;
    } 
  }
  return canGet;
}

ToDoList::ToDoNodePtr ToDoList::createItem(const char desc[]) const
{
  ToDoNodePtr new_item = new ToDoNode; // create a node pointer and new node
  
  new_item->next = NULL; 
  new_item->prev = NULL;  
  strncpy (new_item->desc, desc, DESCRIPTION_LENGTH);
  
  return new_item;
}

void ToDoList::link(ToDoNodePtr item, int priority)
{   
  ToDoNodePtr last = tail[priority-1].prev; // last todo item of same priority

  last->next = item;  
  item->next = &tail[priority-1];
  tail[priority-1].prev = item;
  item->prev = last;

  return;
}

void ToDoList::unlink(ToDoNodePtr item)
{
  ToDoNodePtr pred = item->prev; // the node comes before the removed item
  ToDoNodePtr succ = item->next; // the node comes after the removed item

  // alter link to bypass the item to remove
  pred->next = succ;
  succ->prev = pred;

  return;
}

void ToDoList::displayPriority(int priority, int &position, ostream &out) const
{
  ToDoNodePtr current = head[priority-1].next;

  // traverse the linked list and print to outstream
  while ( current != &tail[priority-1] )
  {     
    out << position << ":      - " << current->desc << endl;
    current = current->next;
    position++;
  }

  return;
}

/* 
  Public Methods
*/

ToDoList::ToDoList()
{ 
  // point both dummy HEAD and TAIL to each other to initiate a empty list
  for ( int i = 0; i < 3; i++ )
  {
    head[i].next = &tail[i];  
    tail[i].next = NULL;
    tail[i].prev = &head[i];
    head[i].prev = NULL;
  }
}

ToDoList::~ToDoList()
{
  ToDoNodePtr current = NULL;
  ToDoNodePtr next = NULL;

  for ( int i = 0; i < 3; i++ )
  {
    current = head[i].next;
    // delete node until no more left
    while ( current != &tail[i] )
    {
      next = current->next;
      delete current;
      current = next;
    }

    // set dummy pointer to NULL
    head[i].next = NULL;
    head[i].prev = NULL;
    tail[i].next = NULL;
    tail[i].prev = NULL;
  }
}

void ToDoList::load(istream &infile)
{
  int priority;
  char space;
  char desc[DESCRIPTION_LENGTH+1];

  // read infile 
  infile >> priority;
  
  while ( !infile.eof() )
  {
    infile.get(space);
    infile.getline(desc, DESCRIPTION_LENGTH);

    // add new item
    addItem(desc, priority);

    // read another item
    infile >> priority;
  }
  
  return;
}

void ToDoList::write(ostream &outfile) const
{
  ToDoNodePtr current = NULL;

  // traverse array by priority level
  for ( int i = 2; i >= 0; i-- )
  {
    current = head[i].next;

    // traverse the linked list and write to the outfile
    while ( current != &tail[i] )
    {     
      outfile << i+1 << " " << current->desc << endl;
      current = current->next;
    }
  }

  return;
}

void ToDoList::display(ostream &out) const
{
  const char HIGH[] = "High Priority:\n\n";
  const char MED[] = "Medium Priority:\n\n";
  const char LOW[] = "Low Priority:\n\n";
  const char EMPTY[] = "empty priority list";
  bool isEmpty = true;
  int position = 1;

  // traverse array by priority level
  for ( int priority = 3; priority > 0; priority-- )
  {
    // display item by priorities
    if ( head[priority-1].next != &tail[priority-1] )
    {
      switch (priority) {
      case 3:
        out << HIGH;
        break;
      case 2:
        out << MED;
        break;
      case 1:
        out << LOW;
        break;
      default:
        break;
      }

      // displays all items of a given priority
      displayPriority(priority, position, out);
      isEmpty = false;
      out << endl;
    }
  }

  // print message if file is empty
  if ( isEmpty == true )
  {
    out << EMPTY;
  }

  return;
}

void ToDoList::addItem(const char desc[], int priority)
{
  ToDoNodePtr new_item = NULL;

  new_item = createItem(desc); // add a new to-do item
  link(new_item, priority); // link the item into the data structure

  return;
}

bool ToDoList::removeItem(int pos)
{
  bool isRemoved = false;
  ToDoNodePtr remove_item = NULL;
  int priority;

  // searches for the position and get its pointer and priority
  isRemoved = getAt(pos, remove_item, priority);

  // unlink the item from the data structure
  if ( isRemoved == true )
  {
    unlink(remove_item);
    delete remove_item;
    remove_item = NULL;
  }

  return isRemoved;
}

void ToDoList::lookup(int pos, char desc[], int &priority, bool &found) const
{
  ToDoNodePtr item = NULL;
  found = false;

  // searches for the position, then see if it's found
  // and get its pointer, description, and priority
  found = getAt(pos, item, priority);
  if ( found == true )
  {
    strncpy(desc, item->desc, DESCRIPTION_LENGTH+1);
  }
  return;
}

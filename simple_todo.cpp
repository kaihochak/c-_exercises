/*

simple todo

Name:          Kai Ho Chak
Due Date:      February 24, 2021

main() not implemented, use ioutil and test_todo

*/

#include <iostream>
#include <cstring>
#include "todo_list.h"
#include "ioutil.h"

const int MAXLEN = 30;

void load (istream &infile,
	   To_Do_Item_Ptr &head)
{
    int priority;
    char space;
    char desc[MAXLEN];
    To_Do_Item_Ptr new_item = NULL;
    To_Do_Item_Ptr current = head;
    
    // read infile 
    infile >> priority;
    
    while ( !infile.eof() )
    {
	infile.get(space);
	infile.getline(desc, MAXLEN);

	// create new item
	new_item = create_node (desc, priority);

	// for empty list
	if ( head == NULL )
	{
	    current = new_item;
	    head = current;
	}
	// for non-empty list
	else
	{
	    current->next = new_item;
	    current = current->next;
	}

	infile >> priority;
    }

    new_item = NULL;
    current = NULL;
    
    return;
} // load ends

void write (ostream &outfile,
	    To_Do_Item_Ptr head)
{
    To_Do_Item_Ptr current = head;

    // traverse the list and write to the outfile
    while ( current != NULL )
    {
	outfile << current->priority << " " << current->description << endl;
	current = current->next;
    }
    
    return;
}

To_Do_Item_Ptr create_node (const char desc[],
			    int priority)
{
    const int MAXLEN = 60;
    To_Do_Item_Ptr new_item = new To_Do_Item;
    
    // store priority, description, and set its pointer to NULL
    new_item->priority = priority;
    strncpy (new_item->description, desc, MAXLEN);
    new_item->next = NULL;
    
    return new_item;
} // create_node ends

void display_list (To_Do_Item_Ptr head,
		  ostream &out)
{
    const char HIGH[] = "High Priority:\n\n";
    const char MED[] = "Medium Priority:\n\n";
    const char LOW[] = "Low Priority:\n\n";
    To_Do_Item_Ptr current = head;
    int counter = 1;
    int priority = 0;
    
    while ( current != NULL )
    {
	// print headers for priority
	if ( priority != current->priority )
	{
	    out << endl;

	    switch ( current-> priority ) {
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

	    priority = current->priority;
	}

	out << counter << ":      - " << current->description << endl;
	current = current->next;
	counter++;
    }
        
    return;
} // display_list ends

void search(To_Do_Item_Ptr head,
	    int position,
	    To_Do_Item_Ptr &node,
	    bool &found)
{
    const char ERROR_NEG_NUM[] = "Please enter a positive list number.\n";
    const char NOT_FOUND[] = "Item is not found. Please enter again.\n";
    int counter = 1;
    To_Do_Item_Ptr current = head;
    found = false;

    // print error message if position is negative or zero
    if ( position <= 0 )
    {
	cout << ERROR_NEG_NUM;
    }
    else
    {
	// traverse the list, terminating based upon the requested position
	while ( current != NULL && counter < position)
	{
	    current = current->next;
	    counter++;
	}
	
	// return the corresponding pointer to the node if such position exists
	if ( current != NULL )
	{
	    found = true;
	    node = current;
	}
	// print error message if no such position
	else
	{
	    cout << NOT_FOUND;
	}
    }
    
    return;
    
} // search ends

void insert_item(To_Do_Item_Ptr &head,
		 To_Do_Item_Ptr node)
{
    To_Do_Item_Ptr succ = head;
    To_Do_Item_Ptr pred = NULL;

    // for empty list
    if ( head == NULL )
    {
	head = node;
    }
    // for singleton list
    else if ( succ->next == NULL )
    {
	if ( succ->priority >= node->priority )
	{
	    succ->next = node;
	}
	else
	{
	    node->next = succ;
	    head = node;
	}
    }
    // for other cases
    else
    {
	// traverse until pred reach the end of the priority sub-list 
	while ( succ != NULL && succ->priority >= node->priority )
	{
	    pred = succ;
	    succ = succ->next;
	}
   
	// insert
	pred->next = node;
	node->next = succ;
    }   
    return;
} // insert_item ends

void remove_item (To_Do_Item_Ptr &head,
		  To_Do_Item_Ptr &node)
{
    To_Do_Item_Ptr current = head;

    // for item to be removed as the first item
    if ( head == node )
    {
	head = node->next;
    }
    // for other cases
    else 
    {
	// traverse until the predecessor of the item to remove
	while ( current->next != node )
	{
	    current = current->next;
	}

	// alter link to bypass the item to remove
	current->next = node->next;
    }    
    return;
} // remove_item ends

void destroy_list (To_Do_Item_Ptr &head)
{
    To_Do_Item_Ptr current = head;
    To_Do_Item_Ptr next = NULL;    

    // delete node one by one until no more node exists
    while ( current != NULL )
    {
	next = current->next;
	delete current;
	current = next;
    }

    // set head back to NULL
    head = NULL;
	
    return;
} // destroy_list ends

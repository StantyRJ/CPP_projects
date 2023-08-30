#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

struct Node
{
    string name;
    Node* next;
};

struct Node* newNode(string newItem) {
   Node* node = new Node;
   node->name = newItem;
   node->next = NULL;
   return node;
};

void appendNode(Node* head, Node* newNode)
{
    Node* toAddTo = head;
    while(toAddTo->next != NULL)
    {
        toAddTo = toAddTo->next;
    }
    toAddTo->next = newNode;
}

void printInventory(Node* head)
{
    int slot = 1;
    Node* current = head;
    cout << endl;
    while(current != NULL)
    {
        cout << "[" << slot << "]" << " " << current->name << endl;
        slot ++;
        current = current->next;
    }
    cout << endl;
}

void switchItems(Node* head, int slot1, int slot2)
{
    Node* temp = head;
    Node* firstPos;
    Node* storeFirstNode;

    //find first node
    for(int pos1 = 1; pos1 < slot1-1; pos1++)
    {
        temp = temp->next;
    }
    
    firstPos = temp;

    if(slot1 <= 1)
        storeFirstNode = temp;
    else
        storeFirstNode = temp->next;
    
    cout << firstPos->name << endl;
    cout << storeFirstNode->name << endl;

    temp = head;
    Node* storeSecondNode;
    //find and change second node
    for(int pos2 = 1; pos2 < slot2-1; pos2++)
    {
        temp = temp->next;
    }
    if(slot2 <= 1)
        storeSecondNode = temp;
    else
        storeSecondNode = temp->next;

    cout << storeSecondNode->name << endl;

    //inject first selected node
    storeFirstNode->next = storeSecondNode->next;
    if (storeFirstNode->next)
        cout << storeFirstNode->next->name << endl;
    else
        cout << "NULL first name next"<< endl;
    firstPos->next = storeSecondNode;
    storeSecondNode->next = storeFirstNode;

    cout << head->name << endl;
    cout << head->next->name << endl;
    cout << head->next->next->name << endl;
    if (head->next->next->next == NULL)
        cout << "NULL\n";
    else
        cout << head->next->next->next->name << endl;

}

int menu()
{
    cout << "1) Current Inventory\n";
    cout << "2) Add Item To Inventory\n";
    cout << "3) Switch 2 Items In Inventory\n";
    cout << "4) Delete Item From Inventory\n";
    cout << "5) Exit Aplication\n";
    int answer;
    cin >> answer;
    return answer;
}

void action(int choice, bool& exit, Node* inventory, int* len)
{
    switch (choice)
    {
        case 1:
            printInventory(inventory);
        break;
        case 2:
        {
            string itemName;
            cout << "Enter Item Name: ";
            cin >> itemName;

            Node* newItem = newNode(itemName);
            appendNode(inventory,newItem);
            (*len)++;
            cout<< *len << endl;
        }
        break;
        case 3:
        {
            printInventory(inventory);
            int first,second;
            cout << "Select Item 1 to Switch [1-" << *len << "]: ";
            cin >> first;

            cout << "Select Item 2 to Switch [1-" << *len << "]: ";
            cin >> second; 

            if(first == second || first > *len || second > *len)
                cout << "Invalid input.";
            else
            {
                switchItems(inventory,first,second);
                //printInventory(inventory);
            }
                           

        }   
        break;
        case 5:
            exit = true;
        break;
    }
}

void freeInventory(Node* inventory)
{
    Node* current = inventory;
    Node* next;
    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

int main()
{
    bool exit = false;
    Node* inventory = newNode("Pickaxe");

    Node* newItem2 = newNode("Axe");
    appendNode(inventory,newItem2);

    Node* newItem3 = newNode("Bomb");
    appendNode(inventory,newItem3);

    Node* newItem4 = newNode("Boomerang");
    appendNode(inventory,newItem4);

    Node* newItem5 = newNode("Potion");
    appendNode(inventory,newItem5);

    int len = 5;

    while(!exit)
    {
        int choice = menu();
        action(choice, exit, inventory, &len);
    }

    freeInventory(inventory);
    return 0;
}

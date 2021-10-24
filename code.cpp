#include <bits/stdc++.h>
using namespace std;

void delete1(int r, int c);
void insert(int, int, int);
void search(int);
void update(int, int, int);
void print(bool type);
void save_file();

class node
{
public:
    int index;
    int data;
    node *next;
};
class linkedlist
{
    node *head;
    node *tail;

public:
    linkedlist() { head = NULL, tail = NULL; }
    friend void update(int, int, int);
    friend void print(bool type);
    friend void save_file();
    friend void insert(int, int, int);
    friend void delete1(int, int);
    friend void search(int);
};

linkedlist matrix[10];

void read_file()
{
    ifstream inputFile("M(10,5).csv", ios::in);
    string line;
    int col = 0, row = 0;
    while (getline(inputFile, line))
    {
        linkedlist tmp;
        char *str1 = &line[0];
        char *token1 = (char *)strtok(str1, ",");
        col = 0;
        while (col < 5)
        {
            if (token1[0] != '0')
                insert(row + 1, col + 1, atoi(token1));
            token1 = strtok(NULL, ",");
            col++;
        }
        row++;
    }
}

void insert(int row, int col, int value)
{
    node *newNode = new node;
    newNode->data = value;
    newNode->index = col - 1;
    newNode->next = NULL;
    if (matrix[row - 1].head == NULL)
        matrix[row - 1].head = newNode, matrix[row - 1].tail = matrix[row - 1].head;
    else
    {
        newNode->next = matrix[row - 1].head, matrix[row - 1].head = newNode;
    }
}

void delete1(int r, int c)
{
    if (matrix[r - 1].head->index == c - 1)
    {
        matrix[r - 1].head = matrix[r - 1].head->next;
        return;
    }

    node *current = matrix[r - 1].head;
    node *preview = NULL;
    while (current != NULL)
    {
        if (current->index == c - 1)
        {
            if (current->next != NULL)
                preview->next = current->next;
            else
                preview->next = NULL;
            current = preview;
            return;
        }
        preview = current;
        current = current->next;
    }
}

int main()
{
    read_file();
    int selection;
    cout << "insert new value : 0 \n"
         << "delete a value : 1\nsearch : 2 \n"
         << "update a element : 3 \nprint : 4\n" 
         << "save new data to a new file : 5\nexit : 6\n";
    cin >> selection;
    while(selection != 6)
    {
        if(selection == 0)
        {
            int row , col , value;
            cout <<"row : ";
            cin >> row;
            cout << "col : ";
            cin >> col;
            cout <<"value : ";
            cin >> value;
            insert(row , col , value);
        }
        else if(selection == 1)
        {
            int row , col;
            cout << "row : ";
            cin >> row;
            cout << "col : ";
            cin >> col;
            delete1(row , col);
        }
    }
}

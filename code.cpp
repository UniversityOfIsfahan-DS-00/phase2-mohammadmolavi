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

void search(int value)
{
    node *current;
    for (int i = 0; i < 10; i++)
    {
        current = matrix[i].head;
        int col = 0;
        while (current != NULL)
        {
            if (current->data == value)
            {
                cout << "There is this value in the list\n";
                return;
            }
            col++;
            current = current->next;
        }
    }
    cout << "This value is not in the list\n";
}

void update(int row, int col, int value)
{
    node *current = matrix[row - 1].head;
    for (int i = 0; i < col && current != NULL; i++)
    {
        if (current->index == col - 1)
        {
            current->data = value;
            return;
        }
        current = current->next;
    }
    insert(row, col, value);
}

void print(bool type)
{
    if (type == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                bool flag = false;
                node *current = matrix[i].head;
                while (current != NULL)
                {
                    if (current->index == j)
                    {
                        cout << current->data;
                        flag = true;
                        break;
                    }
                    current = current->next;
                }
                if (!flag)
                    cout << "0";
                if (j < 4)
                    cout << ",";
            }
            cout << endl;
        }
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            node *current = matrix[i].head;
            while (current != NULL)
            {
                cout << i + 1 << " " << current->index + 1 << " "
                     << current->data << endl;
                current = current->next;
            }
        }
    }
}

void save_file()
{
    ofstream outputFile("M(10,5).csv", ios::out);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            bool flag = false;
            node *current = matrix[i].head;
            while (current != NULL)
            {
                if (current->index == j)
                {
                    outputFile << current->data;
                    flag = true;
                    break;
                }
                current = current->next;
            }
            if (!flag)
                outputFile << "0";
            if (j < 4)
                outputFile << ",";
        }
        outputFile << endl;
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
    while (selection != 6)
    {
        if (selection == 0)
        {
            int row, col, value;
            cout << "row : ";
            cin >> row;
            cout << "col : ";
            cin >> col;
            cout << "value : ";
            cin >> value;
            insert(row, col, value);
        }
        else if (selection == 1)
        {
            int row, col;
            cout << "row : ";
            cin >> row;
            cout << "col : ";
            cin >> col;
            delete1(row, col);
        }
        else if (selection == 2)
        {
            cout << "value : ";
            int value;
            cin >> value;
            search(value);
        }
        else if (selection == 3)
        {
            int row, col, value;
            cout << "row : ";
            cin >> row;
            cout << "col : ";
            cin >> col;
            cout << "value : ";
            cin >> value;
            update(row, col, value);
        }
        else if (selection == 4)
        {
            bool type;
            cout << "print 2D matrix enter 0\n"
                 << "print compress mode enter 1\n";
            cin >> type;
            print(type);
        }
        else if (selection == 5)
            save_file();
        cout << "insert new value : 0 \n"
             << "delete a value : 1\nsearch : 2 \n"
             << "update a element : 3 \nprint : 4\n"
             << "save new data to a new file : 5\nexit : 6\n";
        cin >> selection;
    }
}

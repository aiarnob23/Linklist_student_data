#include <iostream>
#include<bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;

struct node
{
    int id;
    string name;
    float cgpa;
    node *link;
};

node *head = NULL;
node *tail = NULL;

void addStudentFromFile()
{
    int id;
    string name;
    float cgpa;
    ifstream file("student.txt");
    if (file.is_open())
    {
        while (file >> id >> name >> cgpa)
        {
            // Create a new node and add it to the list
            node *newnode = new node;
            newnode->id = id;
            newnode->name = name;
            newnode->cgpa = cgpa;
            newnode->link = NULL;

            if (head == NULL)
            {
                head = tail = newnode;
            }
            else
            {
                tail->link = newnode;
                tail = newnode;
            }
            file.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    else
    {
        cout << "No previous data found." << endl;
    }
    file.close();
}

void addNewStudent(int id, string name, float cgpa)
{
    // Check if same ID exists
    node *temp = head;
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            cout << "Same ID already exists!" << endl;
            return;
        }
        temp = temp->link;
    }

    // Memory allocation for new student
    node *newnode = new node;
    newnode->id = id;
    newnode->name = name;
    newnode->cgpa = cgpa;
    newnode->link = NULL;

    if (head == NULL)
    {
        head = tail = newnode;
    }
    else
    {
        tail->link = newnode;
        tail = newnode;
    }

    // Add data to the file
    ofstream file("student.txt", ios::out | ios::app);
    if (file.is_open())
    {
        file << newnode->id << " " << newnode->name << " " << newnode->cgpa<<endl;
        file.close();
        cout << "Student added successfully." << endl;
    }
    else
    {
        cout << "Error: Unable to write to the file." << endl;
    }
}

void displayStudentInfo()
{
    if (head == NULL)
    {
        cout << "No data found!" << endl;
    }
    else
    {
        node *temp = head;
        cout << "\nData:\n" << endl;
        while (temp != NULL)
        {
            cout << "ID: " << temp->id << "\tName: " << temp->name << "\tCGPA: " << temp->cgpa << endl;
            temp = temp->link;
        }
        cout << endl;
    }
}

void searchStudentbyId(int id)
{
    node *temp = head;
    bool found = false;
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            found = true;
            break;
        }
        temp = temp->link;
    }
    if (found)
    {
        cout << "Name: " << temp->name << "\tCGPA: " << temp->cgpa << endl;
    }
    else
    {
        cout << "Student Not Found!" << endl;
    }
}

int main()
{
    int choice, id;
    string name;
    float cgpa;

    // Checking if any data exists in the file
    addStudentFromFile();

    while (true)
    {
        cout << "\nEnter your choice: " << endl;
        cout << "1: Add student data" << endl;
        cout << "2: Display all data" << endl;
        cout << "3: Search student by ID" << endl;
        cout << "4: Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter student's name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter CGPA: ";
            cin >> cgpa;
            addNewStudent(id, name, cgpa);
            break;

        case 2:
            displayStudentInfo();
            break;

        case 3:
            cout << "Enter ID: ";
            cin >> id;
            searchStudentbyId(id);
            break;

        case 4:
            exit(0);

        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    }
}
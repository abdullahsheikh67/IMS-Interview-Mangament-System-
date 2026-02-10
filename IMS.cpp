#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ----------------------------------------------------
// Candidate Structure
// ----------------------------------------------------
struct Candidate {
    string name;
    string username;
    string password;
    string qualification;
    int experience;
    float cgpa;
    float priorityScore;
    string status;              // Waiting / Selected / Rejected
    Candidate* next;
};

// ----------------------------------------------------
// Priority Queue (Linked List)
// ----------------------------------------------------
class PriorityQueue {
private:
    Candidate* head;

    float calculatePriority(string qualification, int exp, float cgpa) {
        int q = 0;
        if (qualification == "PhD") q = 5;
        else if (qualification == "MS" || qualification == "MPhil") q = 4;
        else if (qualification == "BS") q = 3;
        else if (qualification == "Intermediate") q = 1;
        return q * 3 + exp * 2 + cgpa * 1.5;
    }

public:
    PriorityQueue() { head = NULL; }

    Candidate* getHead() { return head; }
    Candidate* getTop() { return head; }

    void insert(string name, string username, string password,
                string qualification, int exp, float cgpa) {

        Candidate* newNode = new Candidate;
        newNode->name = name;
        newNode->username = username;
        newNode->password = password;
        newNode->qualification = qualification;
        newNode->experience = exp;
        newNode->cgpa = cgpa;
        newNode->priorityScore = calculatePriority(qualification, exp, cgpa);
        newNode->status = "Waiting";
        newNode->next = NULL;

        if (!head || newNode->priorityScore > head->priorityScore) {
            newNode->next = head;
            head = newNode;
        } else {
            Candidate* temp = head;
            while (temp->next && temp->next->priorityScore >= newNode->priorityScore)
                temp = temp->next;
            newNode->next = temp->next;
            temp->next = newNode;
        }
        saveToFile();
    }

    void saveToFile() {
        ofstream file("candidates.txt");
        Candidate* temp = head;
        while (temp) {
            file << temp->name << ","
                 << temp->username << ","
                 << temp->password << ","
                 << temp->qualification << ","
                 << temp->experience << ","
                 << temp->cgpa << ","
                 << temp->priorityScore << ","
                 << temp->status << "\n";
            temp = temp->next;
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file("candidates.txt");
        if (!file.is_open()) return;

        while (file.good()) {
            Candidate* node = new Candidate;

            getline(file, node->name, ',');
            getline(file, node->username, ',');
            getline(file, node->password, ',');
            getline(file, node->qualification, ',');
            file >> node->experience; file.ignore();
            file >> node->cgpa; file.ignore();
            file >> node->priorityScore; file.ignore();
            getline(file, node->status);

            if (node->name == "") {
                delete node;
                break;
            }
            node->next = head;
            head = node;
        }
        file.close();
    }

    void display() {
        if (!head) {
            cout << "\nNo candidates in queue.\n";
            return;
        }
        cout << "\n--- Candidate Queue ---\n";
        Candidate* temp = head;
        while (temp) {
            cout << temp->name
                 << " | Score: " << temp->priorityScore
                 << " | Status: " << temp->status << endl;
            temp = temp->next;
        }
    }
};

// ----------------------------------------------------
PriorityQueue pq;

// ----------------------------------------------------
// Interviewer Authentication
// ----------------------------------------------------
bool interviewerLogin() {
    string id, pass;
    cout << "\n--- Interviewer Login ---\n";
    cout << "Interviewer ID: ";
    cin >> id;
    cout << "Password: ";
    cin >> pass;

    ifstream file("interviewers.txt");
    string fid, fpass;

    while (file.good()) {
        getline(file, fid, ',');
        getline(file, fpass);
        if (fid == id && fpass == pass) {
            cout << "Login successful.\n";
            return true;
        }
    }
    cout << "Invalid Interviewer ID or Password.\n";
    return false;
}

// ----------------------------------------------------
// Candidate Signup
// ----------------------------------------------------
void candidateSignup() {
    string name, qualification, username, password;
    int exp;
    float cgpa;

    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Create Username: ";
    cin >> username;

    cout << "Create Password: ";
    cin >> password;

    cout << "Qualification (PhD/MS/BS/Intermediate): ";
    cin >> qualification;

    cout << "Experience: ";
    cin >> exp;

    cout << "CGPA: ";
    cin >> cgpa;

    pq.insert(name, username, password, qualification, exp, cgpa);
    cout << "\nSignup successful.\n";
}

// ----------------------------------------------------
// Candidate Login
// ----------------------------------------------------
void candidateLogin() {
    string username, password;
    cout << "\n--- Candidate Login ---\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    Candidate* temp = pq.getHead();
    while (temp) {
        if (temp->username == username && temp->password == password) {
            cout << "\nApplication Status: ";
            if (temp->status == "Selected")
                cout << "You're SELECTED\n";
            else if (temp->status == "Rejected")
                cout << "Better Luck Next Time\n";
            else
                cout << "Waiting (Under Process)\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Invalid credentials.\n";
}

// ----------------------------------------------------
// Interviewer Portal
// ----------------------------------------------------
void interviewerPortal() {
    int choice;
    do {
        cout << "\n--- Interviewer Menu ---\n";
        cout << "1. View Next Candidate\n";
        cout << "2. Mark Selected\n";
        cout << "3. Mark Rejected\n";
        cout << "4. View Queue\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        Candidate* top = pq.getTop();

        switch (choice) {
        case 1:
            if (top)
                cout << "Next Candidate: " << top->name
                     << " | Score: " << top->priorityScore << endl;
            else
                cout << "No candidates.\n";
            break;

        case 2:
            if (top) {
                top->status = "Selected";
                pq.saveToFile();
                cout << "Candidate SELECTED.\n";
            }
            break;

        case 3:
            if (top) {
                top->status = "Rejected";
                pq.saveToFile();
                cout << "Candidate REJECTED.\n";
            }
            break;

        case 4:
            pq.display();
            break;
        }
    } while (choice != 0);
}

// ----------------------------------------------------
// Main Menu
// ----------------------------------------------------
void loginMenu() {
    int choice;
    do {
        cout << "\n--- Interview Management System ---\n";
        cout << "1. Candidate Signup\n";
        cout << "2. Candidate Login\n";
        cout << "3. Interviewer Login\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: candidateSignup(); break;
        case 2: candidateLogin(); break;
        case 3:
            if (interviewerLogin())
                interviewerPortal();
            break;
        }
    } while (choice != 0);
}

// ----------------------------------------------------
int main() {
    pq.loadFromFile();
    loginMenu();
    return 0;
}

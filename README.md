# IMS-Interview-Mangament-System-
The Interview Management System (IMS) is a console-based C++ application designed to automate and streamline the candidate selection process using a priority-based approach. The system manages candidate registrations, calculates their priority scores based on predefined criteria, and organizes them in a priority queue for interviewers.
The system is built using fundamental data structures, file handling, and object-oriented programming concepts in C++.

Core Functionality

1. Candidate Module

Candidates can sign up by entering:

Name

Username and password

Qualification

Experience

CGPA

The system automatically calculates a priority score using a weighted formula:

Qualification weight

Experience weight

CGPA weight

Candidates are inserted into a priority queue based on this score.

Candidates can log in to check their application status:

Waiting

Selected

Rejected

2. Interviewer Module

Interviewers log in using a secure ID and password.

After login, interviewers can:

View the next highest-priority candidate

Mark a candidate as selected

Mark a candidate as rejected

View the full candidate queue

3. Priority Queue System

Implemented using a linked list.

Candidates are sorted automatically according to their calculated priority score.

Highest-scoring candidate appears at the front of the queue.

4. File Handling

Candidate data is stored in candidates.txt.

Interviewer credentials are stored in interviewers.txt.

Data is loaded automatically when the program starts and saved after updates.

Key Concepts Used

Structures and classes

Linked lists

Priority queue logic

File handling (ifstream, ofstream)

Basic authentication system

Menu-driven console interface

Purpose of the Project

The main objective of this system is to:

Automate candidate ranking

Reduce manual shortlisting

Provide a simple interface for both candidates and interviewers

Demonstrate practical use of data structures and file management in C++

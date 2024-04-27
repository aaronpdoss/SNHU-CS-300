//*********************************************************
//Name: FinalProject
//Author: Aaron Doss
//Date: 4/20/24
//********************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <Windows.h>
#include <vector>

using namespace std;

struct Course{

    string courseId;
    string courseName;
    vector<string> preList;
};

class BinarySearchTree{

    private:

        struct Node{

            Course course;
            Node* right;
            Node* left;

            //default constructor
            Node(){

                left = nullptr;
                right = nullptr;
            }

            //initialize with course
            Node(Course oneCourse){

                course = oneCourse;
                left = nullptr;
                right = nullptr;

            }

        };

        Node*  root;
        void inOrder(Node* node);
        int size = 0;

    public:

        BinarySearchTree();
        void InOrder();
        void Insert(Course oneCourse);
        void Remove(string courseId);
        Course Search(string courseId);
        int Size();

};

//default constructor
BinarySearchTree::BinarySearchTree(){

    this->root = nullptr;

}

//move accross tree in order
void BinarySearchTree::InOrder(){

    inOrder(root);

}

//insert course
void BinarySearchTree::Insert(Course oneCourse){

    Node* currNode = root;

    if(root == NULL){

        root = new Node(oneCourse);

    }
    else
    {
        while(currNode != NULL){

            if(oneCourse.courseId < currNode->course.courseId){

                if(currNode->left == nullptr){

                    currNode->left = new Node(oneCourse);
                    currNode = NULL;

                }
                else
                {

                    currNode = currNode->left;

                }
            }
            else
            {
                if(currNode->right == nullptr){

                    currNode->right = new Node(oneCourse);
                    currNode = NULL;

                }
                else
                {

                    currNode = currNode->right;
                }
            }
        }
    }
    size++;
}

//remove course
void BinarySearchTree::Remove(string courseId){

    Node* par = NULL;
    Node* curr = root;

    while(curr != NULL){

        if (curr->course.courseId == courseId){

            if(curr->left == NULL && curr->right == NULL){

                if(par == NULL){

                    root = nullptr;

                }
                else if(par->left == curr){

                    par->left = NULL;

                }
                else
                {

                    par->right = NULL;

                }
               
            }
            else if(curr->right == NULL){

                if(par == NULL){

                    root = curr->left;

                }
                else if(par->left == curr){
                    par->left = curr->left;
                }
                else{
                    par->right = curr->left;
                }
            }
            else if(curr->left == NULL){
                if(par == NULL){
                    root = curr->right;
                }
                else if(par->left == curr){
                    par->left = curr->right;
                }
                else{
                    par->right = curr->right;
                }
            }
            else{
                Node* suc = curr->right;

                while(suc->left != NULL){

                    suc = suc->left;
                }

                Node successor = Node(suc->course);
                Remove(suc->course.courseId);
                curr->course = successor.course;
            }
            return;
        }
        else if(curr->course.courseId < courseId){
            par = curr;
            curr = curr->right;
        }
        else{
            par = curr;
            curr = curr->left;
        }
    }
    cout << "That value couldn't be found." << endl;
    return;
}

//search for a course
Course BinarySearchTree::Search(string courseId){

    Course oneCourse;

    Node* currNode = root;

    while(currNode != NULL){

        if(currNode->courseId == courseId){

            return currNode->course;
        }
        else if(courseId < currNode->course.courseId){

             currNode = currNode->left;
        }
        else{

            currNode = currNode->right;
        }
    }

    return oneCourse;
}

void BinarySearchTree::inOrder(Node* node){

    if(node == NULL){

        return;
    }
    inOrder(node->left);

    cout << node->course.courseId << ", " << node->course.courseName << endl;

    inOrder(node->right);
}

int BinarySearchTree::Size(){

    return size;

}

vector<string> Split(string lineFeed){

    char delim = ',';

    lineFeed += delim;
    vector<string> lineToken;
    string temp = "";

    for(int i = 0; i < lineFeed.length(); i++)
    {
        if(lineFeed[i]==delim)
        {
            lineToken.push_back(temp);
            temp = "";
            i++;
        }
        temp += lineFeed[i];
    }
    return lineToken;
}

void loadCourses(string csvPath, BinarySearchTree* courseList){

    ifstream file;
    string line;
    vector<string> stringToken;

    file.open(csvPath);

    if(!file.is_open()){
        cout << "Could not open file. Check file path." << endl;
        return;
    }

    while(!file.eof()){

        Course oneCourse;

        getline(file, line);
        stringToken = Split(line);

        if(stringToken.size() < 2){

            cout << "There was an Error. Skipping this line." <<endl;

        }
        else
        {
            oneCourse.courseId = stringToken.at(0);
            oneCourse.courseName = stringToken.at(1);

            for(unsigned int i = 2; i < stringToken.size(); i++){

                oneCourse.preList.push_back(stringToken.at(i));

            }

            courseList->Insert(oneCourse);
        }
    }

    file.close();
}

void displayCourse(Course oneCourse){

    cout << oneCourse.courseId << ", " << one.courseName << endl;
    cout << "Prerequisites: ";

    if(oneCourse.preList.empty()){
        cout << "none" << endl;
    }
    else{

        for(unsigned int i = 0; i < oneCourse.preList.size(); i++){

            cout << oneCourse.preList.at(i);

            if(oneCourse.preList.size() > 1 && i < oneCourse.preList.size()-1){

                cout << ", ";
            }
        }
    }

    cout << "\n";
}

void caseConversion(string &toConvert){

    for(unsigned int i = 0; i < toConver.length(); i++){

        if(isalpha(toConvert[i])){

            toConvert[i] = toupper(toConvert[i]);
        }
    }
}

int main(int argc, char* argv[]){

    string csvPath, oneCourseKey;

    switch(argc){

        case 2:
            csvPath = argv[1];
            break;
        case3:
            csvPath = argv[1];
            oneCourseKey = argv[2];
            break;
        default:
            csvPath = "FinalProjectTestInput.csv"
    }

    BinarySearchTree* courseList = new BinarySearchTree();

    Course course;
    bool correctInput;
    int choice = 0;

    while(choice != 9){
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display All Courses" << endl;
        cout << "  3. Find a Course" << endl;
        cout << "  4. Remove a Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";

        oneCourseKey = "";
        string anyKey = " ";
        choice = 0;

        try{

            cin >> choice;

            if((choice > 0 && choice < 5) || (choice == 9)){

                correctInput = true;
            }
            else{
                correctInput = false;
                throw 1;
            }

            switch(choice){
                case 1:

                    loadCourses(csvPath, courseList);
                    cout << courseList->Size() " courses read" << endl;

                    break;

                case 2:

                    courseList->InOrder();

                    cout << "\n Enter y to continue." << endl;

                    cin >> anyKey;

                    break;
                
                case 3:

                    cout << "\nWhat course are you looking for?" < endl;
                    cin >> oneCourseKey;

                    convertCase(oneCourseKey);

                    course = courseList->Search(oneCourseKey);

                    if(!course.courseId.empty()){
                        displayCourse(course);
                    }
                    else{
                        cout << "\nCourse ID " << oneCourseKey << " was not found." << endl;
            
                    }
                    break;
                
                case 4:
                    cout <<"What course are you looking to delete? " << endl;
                    cin >> oneCourseKey;

                    convertCase(oneCourseKey);
                    courseList->Remove(oneCourseKey);
                    break;

                case 9:

                    exit;
                    break;

                default:
                    throw 2;

            }
        }

        catch (int err){

            cout <<"\nCheck your input." << endl;
        }

        cin.clear();
        cin.ignore();

        system("cls");
    }

    cout << "Thanks for using this program!" << endl;

    return 0;
}
// C++ program to show the use of
// ostream::seekp() method using binary file

#include <bits/stdc++.h>

using namespace std;

class student {
    int rno;
    const char *name[20];

public:
    void getdata() {
        name[0] = "geek";
        rno = 11;
    }

    void putdata() {
        cout << rno << endl
             << name << endl;
    }

    // accepts the serial number
    // of record to be displayed
    void DisplayRecordAtPosition(int);
};

void student::DisplayRecordAtPosition(int n) {

    ofstream ofs;

    // opening the file in writing mode
    ofs.open("he.dat", ios::out | ios::binary);

    // displays the size of the object
    // sizeof object is 22
    // char[20]+int = 1*20 + 2 = 22
    cout << "size of record: "
         << sizeof(*this) << endl;

    // Using seekp() method to change position
    ofs.seekp((n - 1) * sizeof(student));

    // Writing in the new position
    ofs.write((char *) this, sizeof(student));

// Closing the output stream
    ofs.close();

    ifstream ifs;
    ifs.open("he.dat", ios::in | ios::binary);
    ifs.seekg((n - 1) * sizeof(student));
    ifs.read((char *) this, sizeof(student));
    putdata();
    ifs.close();
}

// Driver code
int main() {
    student s;
    int pos = 1;

    s.getdata();

    cout << "record no " << pos
         << " (position int file "
         << pos - 1 << ")\n";
    s.DisplayRecordAtPosition(pos);

    return 0;
}

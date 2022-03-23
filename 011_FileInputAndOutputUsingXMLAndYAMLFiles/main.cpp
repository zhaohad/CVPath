#include <opencv2/core/core.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

class MyData
{
public:
    MyData() : A(0), X(0), id() {}

    explicit MyData(int) : A(97), X(CV_PI), id("mydata1234") {}

    void write(FileStorage& fs) const {
        fs << "{" << "A" << A << "X" << X << "id" << id << "}";
    }

    void read(const FileNode& node) {
        A = (int) node["A"];
        X = (double) node["X"];
        id = (string) node["id"];
    }
public:
    int A;
    double X;
    string id;
};

void write(FileStorage& fs, const string&, const MyData& x) {
    x.write(fs);
}

void read(const FileNode& node, MyData& x, const MyData& default_value = MyData()) {
    if (node.empty()) {
        x = default_value;
    } else {
        x.read(node);
    }
}

ostream& operator<<(ostream& out, const MyData& m) {
    out << "{ id = " << m.id << ", ";
    out << "X = " << m.X << ", ";
    out << "A = " << m.A << "}";
    return out;
}

int main() {
    string fileName = "out.d";
    {
        Mat R = Mat_<uchar>::eye(3, 3);
        Mat T = Mat_<double>::zeros(3, 1);
        MyData m(1);

        // FileStorage fs(fileName, FileStorage::WRITE | FileStorage::FORMAT_JSON);
        // FileStorage fs(fileName, FileStorage::WRITE | FileStorage::FORMAT_XML);
        // FileStorage fs(fileName, FileStorage::WRITE | FileStorage::FORMAT_YAML);
        FileStorage fs(fileName, FileStorage::WRITE);

        fs << "iterationNr" << 100;
        fs << "strings" << "[";
        fs << "image1.jpg" << "Awesomeness" << "baboon.jpg" << "]";

        fs << "Mapping";
        fs << "{" << "One" << 1;
        fs << "Two" << 2 << "}";

        fs << "R" << R;
        fs << "T" << T;

        fs << "MyData" << m;
        fs.release();
        cout << "Write Done." << endl;
    }

    {
        cout << endl << "Reading: " << endl;
        FileStorage fs;
        fs.open(fileName, FileStorage::READ);

        int itNr;
        itNr = (int) fs["iterationNr"];
        cout << itNr << endl;
        if (!fs.isOpened()) {
            cerr << "Failed to open " << fileName << endl;
            return 1;
        }
        FileNode n = fs["strings"];
        if (n.type() != FileNode::SEQ) {
            cerr << "strings is not a sequence! FAIL" << endl;
            return 1;
        }

        FileNodeIterator it = n.begin();
        FileNodeIterator it_end = n.end();
        for (; it != it_end; ++it) {
            cout << (string) *it << endl;
        }
        n = fs["Mapping"];
        cout << "Two " << (int) (n["Two"]) << ";";
        cout << "One " << (int) (n["One"]) << endl << endl;

        MyData m;
        Mat R, T;
        fs["R"] >> R;
        fs["T"] >> T;
        fs["MyData"] >> m;

        cout << endl << "R = " << endl << R << endl;
        cout << "T = " << endl << T << endl << endl;
        cout << "MyData = " << endl << m << endl << endl;

        cout << "Attempt to read NonExisting (should initialize the data structure with its default).";
        fs["NonExisting"] >> m;
        cout << endl << "NonExisting = " << endl << m << endl;
        fs.release();
    }

    cout << endl;
    cout << "Tip: Open up " << fileName << " with a text editor to see the serialized data." << endl;
    return 0;
}

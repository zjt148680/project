#include "io.h"

using namespace std;


class IO_English {
public:
    static vector<string> _read_by_line(string filename) {
        vector<string> result;

        ifstream infile(filename); //打开文件
        if (!infile.is_open()) { //检查是否打开成功
            cout << "Failed to open file" << endl;
            return result;
        }
        string line;
        while (getline(infile, line)) { //逐行读取文件内容
            result.push_back(line);
        }
        infile.close(); //关闭文件
        return result;
    }

    static bool _write_by_line(string filename, vector<string> data) {
        ofstream outfile(filename, ofstream::trunc);//打开并清空
        //ofstream outfile(filename, ofstream::app);//打开不清空，换行的话就是输出一个"\n"或endl

        if (!outfile.is_open()) {
            return false;
        }

        for (int i = 0; i < data.size(); i++) {
            outfile << data[i] << endl;
        }
        outfile.close();
        return true;
    }

    static vector<vector<int>> _read_by_nums(string filename) {
        vector<vector<int>> result;

        ifstream infile(filename); //打开文件
        if (!infile.is_open()) { //检查是否打开成功
            cout << "Failed to open file" << endl;
            return result;
        }

        string line;
        int num;

        while (getline(infile, line)) {
            vector<int> a(0);

            istringstream iss(line); // 用istringstream将一行分解为数字字符串

            while (iss >> num) {
                a.push_back(num);
            }

            result.push_back(a);
        }

        infile.close();

        return result;
    }

    static bool _write_by_nums(std::string filename, std::vector<std::vector<int>> data) {
        ofstream outfile(filename, ofstream::trunc);//打开并清空

        if (!outfile.is_open()) {
            return false;
        }

        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data[i].size(); j++)
                outfile << data[i][j] << " ";
            outfile << endl;
        }
        outfile.close();
        return true;
    }

};

class IO_Chinese {
public:
    static vector<wstring> _read_by_line(string filename) {
        vector<wstring> result;

        wifstream winfile(filename, ios::binary); //打开文件
        winfile.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
        if (!winfile.is_open()) { //检查是否打开成功
            cout << "Failed to open file" << endl;
            return result;
        }
        wstring line;
        while (getline(winfile, line)) { //逐行读取文件内容
            result.push_back(line);
        }
        winfile.close(); //关闭文件
        return result;
    }

    static bool _write_by_line(string filename, vector<string> data) {
        ofstream outfile(filename, ofstream::trunc);//打开并清空
        //ofstream outfile(filename, ofstream::app);//打开不清空，换行的话就是输出一个"\n"或endl

        if (!outfile.is_open()) {
            return false;
        }

        for (int i = 0; i < data.size(); i++) {
            outfile << data[i] << endl;
        }
        outfile.close();
        return true;
    }

    static vector<vector<int>> _read_by_nums(string filename) {
        vector<vector<int>> result;

        ifstream infile(filename); //打开文件
        if (!infile.is_open()) { //检查是否打开成功
            cout << "Failed to open file" << endl;
            return result;
        }

        string line;
        int num;

        while (getline(infile, line)) {
            vector<int> a(0);

            istringstream iss(line); // 用istringstream将一行分解为数字字符串

            while (iss >> num) {
                a.push_back(num);
            }

            result.push_back(a);
        }

        infile.close();

        return result;
    }

    static bool _write_by_nums(std::string filename, std::vector<std::vector<int>> data) {
        ofstream outfile(filename, ofstream::trunc);//打开并清空

        if (!outfile.is_open()) {
            return false;
        }

        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data[i].size(); j++)
                outfile << data[i][j] << " ";
            outfile << endl;
        }
        outfile.close();
        return true;
    }

};








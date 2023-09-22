#include "io.h"

using namespace std;


class IO_English {
public:
    static vector<string> _read_by_line(string filename) {
        vector<string> result;

        ifstream infile(filename); //���ļ�
        if (!infile.is_open()) { //����Ƿ�򿪳ɹ�
            cout << "Failed to open file" << endl;
            return result;
        }
        string line;
        while (getline(infile, line)) { //���ж�ȡ�ļ�����
            result.push_back(line);
        }
        infile.close(); //�ر��ļ�
        return result;
    }

    static bool _write_by_line(string filename, vector<string> data) {
        ofstream outfile(filename, ofstream::trunc);//�򿪲����
        //ofstream outfile(filename, ofstream::app);//�򿪲���գ����еĻ��������һ��"\n"��endl

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

        ifstream infile(filename); //���ļ�
        if (!infile.is_open()) { //����Ƿ�򿪳ɹ�
            cout << "Failed to open file" << endl;
            return result;
        }

        string line;
        int num;

        while (getline(infile, line)) {
            vector<int> a(0);

            istringstream iss(line); // ��istringstream��һ�зֽ�Ϊ�����ַ���

            while (iss >> num) {
                a.push_back(num);
            }

            result.push_back(a);
        }

        infile.close();

        return result;
    }

    static bool _write_by_nums(std::string filename, std::vector<std::vector<int>> data) {
        ofstream outfile(filename, ofstream::trunc);//�򿪲����

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

        wifstream winfile(filename, ios::binary); //���ļ�
        winfile.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
        if (!winfile.is_open()) { //����Ƿ�򿪳ɹ�
            cout << "Failed to open file" << endl;
            return result;
        }
        wstring line;
        while (getline(winfile, line)) { //���ж�ȡ�ļ�����
            result.push_back(line);
        }
        winfile.close(); //�ر��ļ�
        return result;
    }

    static bool _write_by_line(string filename, vector<string> data) {
        ofstream outfile(filename, ofstream::trunc);//�򿪲����
        //ofstream outfile(filename, ofstream::app);//�򿪲���գ����еĻ��������һ��"\n"��endl

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

        ifstream infile(filename); //���ļ�
        if (!infile.is_open()) { //����Ƿ�򿪳ɹ�
            cout << "Failed to open file" << endl;
            return result;
        }

        string line;
        int num;

        while (getline(infile, line)) {
            vector<int> a(0);

            istringstream iss(line); // ��istringstream��һ�зֽ�Ϊ�����ַ���

            while (iss >> num) {
                a.push_back(num);
            }

            result.push_back(a);
        }

        infile.close();

        return result;
    }

    static bool _write_by_nums(std::string filename, std::vector<std::vector<int>> data) {
        ofstream outfile(filename, ofstream::trunc);//�򿪲����

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








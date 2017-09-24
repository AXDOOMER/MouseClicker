#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>

#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

const int SPEED = 50;

int main(int argc, char** argv) {
    cout << "Screen resolution:" << endl;
    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);
    cout << "width: " << screen_width << endl;
    cout << "height: " << screen_height << endl;
    cout << "========== mouse playback ==========" << endl;
    
    ifstream myfile;
    myfile.open ("clicks.log");
    Sleep(500);
    
    POINT loc;
    
    string line;
    while (getline(myfile, line)) {
        
        istringstream iss(line);
        vector<std::string> results((istream_iterator<string>(iss)),
        istream_iterator<string>());
        
        cout << "mouse_x: " << results.at(0) << '\t' 
             << "mouse_y: " << results.at(1) << '\t'
             << "click: " << results.at(2) << endl;
        
        // http://msdn.microsoft.com/en-us/library/ms646260(VS.85).aspx
    	INPUT Input = { 0 };
    	Input.type = INPUT_MOUSE;
        if (atoi(results.at(2).c_str()) == 1) {
            Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        } else {
            Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        }
        Input.mi.dwFlags |= MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        Input.mi.dx = atol(results.at(0).c_str()) * (65535.0f / screen_width);
        Input.mi.dy = atol(results.at(1).c_str()) * (65535.0f / screen_height);
        SendInput(1, &Input, sizeof(INPUT));
        
        Sleep(SPEED);
    }
    
    myfile.close();
    return 0;
}

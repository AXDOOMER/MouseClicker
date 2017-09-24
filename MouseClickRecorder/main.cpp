#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>

using namespace std;

const int PRECISION = 1000/50;

struct mousetic {
    int x;
    int y;
    bool left_click;
};

int main(int argc, char** argv) {
    cout << "Screen resolution:" << endl;
    cout << "width: " << GetSystemMetrics(SM_CXSCREEN) << endl;
    cout << "height: " << GetSystemMetrics(SM_CYSCREEN) << endl;
    cout << "========== mouse recorder ==========" << endl;
    
    ofstream myfile;
    myfile.open ("clicks.log");
    Sleep(500);
    
    POINT loc;
    vector<mousetic> com;
    
    while (true) {
        GetCursorPos(&loc);

        mousetic mpt;
        mpt.x = loc.x;
        mpt.y = loc.y;
        mpt.left_click = false;
        
        if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
        {
            mpt.left_click = true;
        }

        if (com.size() > 0 && mpt.x == com.back().x && 
            mpt.y == com.back().y && mpt.left_click == com.back().left_click) {
            Sleep(PRECISION);
            continue;
        }
        
        cout << "mouse_x: " << mpt.x << '\t' 
             << "mouse_y: " << mpt.y << '\t'
             << "click: " << mpt.left_click << endl;
    
        myfile << mpt.x << '\t' << mpt.y << '\t' << mpt.left_click << endl;
        
        com.push_back(mpt);
    }
    
    myfile.close();
    return 0;
}

#pragma once
using namespace std;

void gui(int command[]){
    // user interface logic
    cout << "Enter command to rotate " << endl;
    cout << "1 - rotating 90 degrees right, 2 - rotating 90 degrees left, 0 - without rotating ";
    cin >> command[0];

    cout << "Enter Gauss blur level " << endl;
    cout << "(if u dont need blur enter 0, else integer) ";
    cin >> command[1];
}
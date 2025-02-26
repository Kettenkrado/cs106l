#include <iostream>
#include <sstream>

using namespace std;

int main() {
    int x = 10;
    int& reference = x;
    cout << x << endl;
    reference = 20;
    cout << x << endl;
    
    return 0;
}
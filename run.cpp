// pinelang
#include "src/stdc++.h"
#include "src/vm.h"
using namespace std;
int main()
{

    ifstream fin("./code/main.pine");
    stringstream ss; ss << fin.rdbuf();
    vm::run(ss.str());
    return 0;
}

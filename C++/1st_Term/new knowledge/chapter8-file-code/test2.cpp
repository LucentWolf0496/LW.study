#include <fstream>
#include <iostream>
using namespace std;

int main(){
    ofstream fout1("D:\\Project-leaf\\LW.study\\C++\\chapter8-file-code\\test2-fellow1.cpp");
    ofstream fout2("D:\\Project-leaf\\LW.study\\C++\\chapter8-file-code\\test2-fellow2.cpp");
    fout1 << "#include <iostream>" << endl;
    fout1 << "#include <cmath>" << endl;
    fout1 << "using namespace std;" << endl;
    fout1 << endl;
    fout1 << "int main(){" << endl;
    fout1 << "    cout << sin(20.0/180*3.1415926) +" << endl;
    fout1 << "            cos(20.0/180*3.1415926) -" << endl;
    fout1 << "            cos(10.0/180*3.1415926) /" << endl;
    fout1 << "            tan(10.0/180*3.1415926)" << endl;
    fout1 << "         << endl;" << endl;
    fout1 << "    return 0;" << endl;
    fout1 << "}" << endl;
    fout2 << "#include <iostream>" << endl;
    fout2 << "using namespace std;" << endl;
    fout2 << endl;
    fout2 << "int main(){" << endl;
    fout2 << "    cout << \"LucentWolf-Projecting.ver\" << endl;" << endl;
    fout2 << "    return 0;" << endl;
    fout2 << "}" << endl;
    fout1.close();
    fout2.close();
}
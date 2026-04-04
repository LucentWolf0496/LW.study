// 关于文件流的处理
// 绝对路径:
// "c:\\tmp\\mydir\\some.txt"
// 相对路径：
// "\\tmp\\mydir\\some.txt"
//	当前盘符的根目录下的tmp\dir\some.txt
// "tmp\\mydir\\some.txt"
//	当前文件夹的tmp子文件夹里面的…..
// "..\\tmp\\mydir\\some.txt"
//	当前文件夹的父文件夹下面的tmp子文件夹里面的…..
// "..\\..\\tmp\\mydir\\some.txt"
//	当前文件夹的父文件夹的父文件夹下面的tmp子文件夹里面的…..

// #include <fstream>   // 包含头文件
// ofstream outFile("clients.dat", ios::out|ios::binary); //创建文件
// clients.dat”	要创建的文件的名字
// ios::out 		文件打开方式
// ios:out    	输出到文件, 删除原有内容
// ios::app  	输出到文件, 保留原有内容，总是在尾部添加（append简写）
// ios::binary 以二进制文件格式打开文件

// 文件名可以给出绝对路径，也可以给相对路径。没有交代路径信息，就是在当前文件夹下找文件
// 也可以先创建ofstream对象，再用 open函数打开
// ofstream fout;
// fout.open("test.out",ios::out|ios::binary);
// 判断打开是否成功：
// if（!fout）{ 
//     cout << “File open error!”<<endl;
// }

// 文件的读写指针
// 对于输入文件,有一个读指针;
// 对于输出文件,有一个写指针;
// 对于输入输出文件,有一个读写指针;
// 标识文件操作的当前位置, 该指针在哪里,读写操作就在哪里进行。

#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main(){
    ofstream fout("a1.out",ios::app); //以添加方式打开
    long location = fout.tellp();      //取得写指针的位置
    location = 10;
    fout.seekp(location); 	      // 将写指针移动到第10个字节处
    fout.seekp(location,ios::beg); //从头数location
    fout.seekp(location,ios::cur); //从当前位置数location
    fout.seekp(location,ios::end); //从尾部数location

    ifstream  fin("a1.in",ios::in|ios::ate); //打开文件，定位文件指针到文件尾
    long location2 = fin.tellg();   //取得读指针的位置
    location2 = 10L;
    fin.seekg(location2);  // 将读指针移动到第10个字节处
    fin.seekg(location2,ios::beg); //从头数location
    fin.seekg(location2,ios::cur); //从当前位置数location
    fin.seekg(location2,ios::end); //从尾部数location

    vector<int> v;  //v是一个可变长整型数组
	ifstream srcFile("in.txt",ios::in);
	ofstream destFile("out.txt",ios::out);
	int x;	
	while( srcFile >> x )
	          v.push_back(x); //往v末尾添加一个元素
	sort(v.begin(),v.end()); //排序
	for( int i = 0;i < v.size();i ++ )
	          destFile << v[i] << " ";
	destFile.close();// 显式关闭文件 ifstream fin(“test.dat”,ios::in);fin.close();
	srcFile.close();// ofstream fout(“test.dat”,ios::out);fout.close();
	return 0; 
}
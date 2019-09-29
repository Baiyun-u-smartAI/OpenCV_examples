#include "OpenCV_example.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

/*
static void help(char** av)
{
	cout << endl
		<< av[0] << " shows the usage of the OpenCV serialization functionality." << endl
		<< "usage: " << endl
		<< av[0] << " outputfile.yml.gz" << endl
		<< "The output file may be either XML (xml) or YAML (yml/yaml). You can even compress it by "
		<< "specifying this in its extension like xml.gz yaml.gz etc... " << endl
		<< "With FileStorage you can serialize objects in OpenCV by using the << and >> operators" << endl
		<< "For example: - create a class and have it serialized" << endl
		<< "             - use it to read and write matrices." << endl;
}
*/
// 定义自我数据结构，数据库的生成
// 对象的声明和实例化都在这里
class MyData
{
public:
	//声明构造函数
	MyData() : A(0), X(0), id()
	{}

	// 构造函数有一个输入值时，需开放(explicit)以避免隐性转换
	explicit MyData(int) : A(97), X(CV_PI), id("mydata1234")
	{}

	//
	void write(FileStorage& fs) const
	{
		fs << "{" << "A" << A << "X" << X << "id" << id << "}";
	}
	
	// 此类的输入
	void read(const FileNode& node)
	{
		A = (int)node["A"];
		X = (double)node["X"];
		id = (string)node["id"];
	}

// 数据成员
public:
	int A;
	double X;
	string id;
};

// 实际输出与输入函数
static void write(FileStorage& fs, const std::string&, const MyData& x)
{
	x.write(fs);
}
static void read(const FileNode& node, MyData& x,
	const MyData& default_value = MyData()){

	if (node.empty())
		x = default_value;
	else
		x.read(node);
}

// 将类显示到画面
static ostream& operator<<(ostream& out, const MyData& m)
{
	out << "{ id = " << m.id << ", ";
	out << "X = " << m.X << ", ";
	out << "A = " << m.A << "}";
	return out;
}

int run542()
{
	string filename = "outputfile.yml";

	// 写入
	{
		cout << endl << "写入开始: " << endl;
		Mat R = Mat_<uchar>::eye(3, 3),
			T = Mat_<double>::zeros(3, 1);
		MyData m(1);

		FileStorage fs(filename, FileStorage::WRITE);

		fs << "iterationNr" << 100;

		// 字符串开始
		fs << "strings" << "[";
		fs << "C:\\images\\lena.jpg" << "Awesomeness"
			<< "C:\\images\\baboon.jpg";
		// 字符串结束
		fs << "]";

		// 字符串匹配(mapping)
		fs << "Mapping";
		fs << "{" << "One" << 1;
		fs << "Two" << 2 << "}";

		// cv::Mat
		fs << "R" << R;
		fs << "T" << T;

		// 数据结构
		fs << "MyData" << m;

		// 释放fs内存
		fs.release();
		cout << "写入完成." << endl;
	}

	// 读取
	{
		cout << endl << "读取开始: " << endl;
		FileStorage fs;
		fs.open(filename, FileStorage::READ);

		int itNr;
		//fs["iterationNr"] >> itNr;
		itNr = (int)fs["iterationNr"];
		cout << itNr;
		if (!fs.isOpened())
		{
			cerr << "Failed to open " << filename << endl;
			return 1;
		}

		// 读字符串并取得结点
		FileNode n = fs["strings"];
		if (n.type() != FileNode::SEQ)
		{
			cerr << "错误,字符串不是循序的!" << endl;
			return 1;
		}

		// Go through the node
		FileNodeIterator it = n.begin(), it_end = n.end();
		for (; it != it_end; ++it)
			cout << (string)*it << endl;

		// Read mappings from a sequence
		n = fs["Mapping"];
		cout << "Two  " << (int)(n["Two"]) << "; ";
		cout << "One  " << (int)(n["One"]) << endl << endl;

		MyData m;
		Mat R, T;

		// Read cv::Mat
		fs["R"] >> R;
		fs["T"] >> T;
		// 读取自己的数据结构
		fs["MyData"] >> m;

		cout << endl
			<< "R = " << R << endl;
		cout << "T = " << T << endl << endl;
		cout << "MyData = " << endl << m << endl << endl;

		// 对不存在的结点显示基本特性
		cout << "尝试读取不存在的";
		fs["NonExisting"] >> m;
		cout << endl << "NonExisting = " << endl << m << endl;
	}

	cout << endl
		<< "提醒: 请用文字编辑器打开储存的文件 " << filename
		<< endl;

	getchar();

	return 0;
}

int(*run_file_input_output)()=run542;

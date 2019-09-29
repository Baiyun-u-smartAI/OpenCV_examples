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
// �����������ݽṹ�����ݿ������
// �����������ʵ������������
class MyData
{
public:
	//�������캯��
	MyData() : A(0), X(0), id()
	{}

	// ���캯����һ������ֵʱ���迪��(explicit)�Ա�������ת��
	explicit MyData(int) : A(97), X(CV_PI), id("mydata1234")
	{}

	//
	void write(FileStorage& fs) const
	{
		fs << "{" << "A" << A << "X" << X << "id" << id << "}";
	}
	
	// ���������
	void read(const FileNode& node)
	{
		A = (int)node["A"];
		X = (double)node["X"];
		id = (string)node["id"];
	}

// ���ݳ�Ա
public:
	int A;
	double X;
	string id;
};

// ʵ����������뺯��
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

// ������ʾ������
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

	// д��
	{
		cout << endl << "д�뿪ʼ: " << endl;
		Mat R = Mat_<uchar>::eye(3, 3),
			T = Mat_<double>::zeros(3, 1);
		MyData m(1);

		FileStorage fs(filename, FileStorage::WRITE);

		fs << "iterationNr" << 100;

		// �ַ�����ʼ
		fs << "strings" << "[";
		fs << "C:\\images\\lena.jpg" << "Awesomeness"
			<< "C:\\images\\baboon.jpg";
		// �ַ�������
		fs << "]";

		// �ַ���ƥ��(mapping)
		fs << "Mapping";
		fs << "{" << "One" << 1;
		fs << "Two" << 2 << "}";

		// cv::Mat
		fs << "R" << R;
		fs << "T" << T;

		// ���ݽṹ
		fs << "MyData" << m;

		// �ͷ�fs�ڴ�
		fs.release();
		cout << "д�����." << endl;
	}

	// ��ȡ
	{
		cout << endl << "��ȡ��ʼ: " << endl;
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

		// ���ַ�����ȡ�ý��
		FileNode n = fs["strings"];
		if (n.type() != FileNode::SEQ)
		{
			cerr << "����,�ַ�������ѭ���!" << endl;
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
		// ��ȡ�Լ������ݽṹ
		fs["MyData"] >> m;

		cout << endl
			<< "R = " << R << endl;
		cout << "T = " << T << endl << endl;
		cout << "MyData = " << endl << m << endl << endl;

		// �Բ����ڵĽ����ʾ��������
		cout << "���Զ�ȡ�����ڵ�";
		fs["NonExisting"] >> m;
		cout << endl << "NonExisting = " << endl << m << endl;
	}

	cout << endl
		<< "����: �������ֱ༭���򿪴�����ļ� " << filename
		<< endl;

	getchar();

	return 0;
}

int(*run_file_input_output)()=run542;

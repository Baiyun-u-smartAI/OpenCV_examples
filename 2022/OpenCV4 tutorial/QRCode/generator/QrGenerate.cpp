#include "QrCode.hpp"
#include <iostream>
#include <fstream>
using qrcodegen::QrCode;
using qrcodegen::QrSegment;
#include "ConvertToPNG.h" // 因为OpenCV不能直接识别svg矢量图
#include "InputParser.hpp"
int main(int argc, char** argv)
{
    InputParser input(argc, argv);
    if(input.cmdOptionExists("-h")){
        std::cout << "-i <string> : data for QR converting " << std::endl << "-o <filename> : filename without extension " <<std::endl;
    }
    const std::string &textFromInput = input.getCmdOption("-i");
    if (!textFromInput.empty()){
        const char *text = textFromInput.c_str(); // User-supplied text(二维码编码前数据)
        const QrCode::Ecc errCorLvl = QrCode::Ecc::MEDIUM;  // Error correction level

	    // Make and print the QR Code symbol
        const QrCode qr = QrCode::encodeSegments(QrSegment::makeSegments(text), errCorLvl, QrCode::MIN_VERSION, QrCode::MAX_VERSION, 7, true);// 生成二维码对象
	    
	    // const QrCode qr = QrCode::encodeText(text, errCorLvl); // 生成二维码对象
	
        std::ofstream svgfile;
        const std::string &OutName = input.getCmdOption("-o");
        std::string SVGFile, JPGFile;
        if (OutName.empty())
        {
            SVGFile = std::string("test.svg");
            JPGFile = std::string("test.jpg");
        }
        else
        {
            SVGFile = OutName+".svg";
            JPGFile = OutName+".jpg";
        }
        svgfile.open(SVGFile.c_str(), std::ios::out); //开始写入SVG

	    svgfile << qr.toSvgString(4) << std::endl; // 4是二维码的边界大小
        svgfile.close(); // 结束写入SVG文件
        ConvertToPNG(SVGFile.c_str(), 10, JPGFile.c_str()); // 10为svg图片放大倍数
    }
         
	
}
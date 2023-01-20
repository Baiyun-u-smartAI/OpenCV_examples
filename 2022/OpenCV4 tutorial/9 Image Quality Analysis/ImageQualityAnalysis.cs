using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using OpenCvSharp; //导入OpenCV4
namespace ImageQualityAnalysis
{
	class Program
	{
		static double calMEAN(Scalar result)
		{
			int i = 0;
			double sum = 0;
			// 计算总和

			for (int j = 0; j < 4; j++)
			{
				double val = result[j];
				if (0 == val || Double.IsInfinity(val))
				{
					break;
				}

				sum += val;
				i++;
			}

			return sum / i;
		}
		// 盲/无参考图像空间质量评估器 BRISQUE
		static double BRISQUE(Mat img)
		{
			// path to the trained model
			String model_path = "samples/brisque_model_live.yml";
			// path to range file
			String range_path = "samples/brisque_range_live.yml";
			// 静态计算方法
			Scalar result_static = OpenCvSharp.Quality.QualityBRISQUE.Compute(img, model_path, range_path);
			/* 另外一种动态计算的方法
			cv::Ptr<quality::QualityBase> ptr = quality::QualityBRISQUE::create(model_path, range_path);
			// computes BRISQUE score for img
			cv::Scalar result = ptr->compute(img);*/
			return calMEAN(result_static);
		}
		static void qualityCompute(String methodType, Mat img1, Mat img2)
		{
			// 算法结果和算法耗时
			double result;
			Stopwatch costTime = new Stopwatch();

			costTime.Start();

			/*if ("MSE" == methodType)
				result = MSE(img1, img2);
			else if ("PSNR" == methodType)
				result = PSNR(img1, img2);
			else if ("PSNR" == methodType)
				result = PSNR(img1, img2);
			else if ("GMSD" == methodType)
				result = GMSD(img1, img2);
			else if ("SSIM" == methodType)
				result = SSIM(img1, img2);
			else if ("BRISQUE" == methodType)*/
			result = BRISQUE(img2);
			costTime.Stop();
			Console.WriteLine("{0}_result is: {1}", methodType, result);
			Console.WriteLine("{0}_result is: {1}s", methodType, costTime.ElapsedMilliseconds / 1000.0);
		}
		static void Main(string[] args)
		{
			// 设置当前路径为程序运行路径
			DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
			string root = rootDir.Parent.Parent.FullName;
			System.IO.Directory.SetCurrentDirectory(root);

			Console.WriteLine("This is a test for Image Quality Analysis");
			Mat img2 = Cv2.ImRead("aaa.jpg");
			qualityCompute("BRISQUE", new Mat(), img2);
		}
	}
}

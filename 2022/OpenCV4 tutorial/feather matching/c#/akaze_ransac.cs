using System;
using System.Collections.Generic;
using System.IO;
using OpenCvSharp;

namespace split_merge
{
    class Program
    {

        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            Mat obj = Cv2.ImRead("box.png");

            //    GaussianBlur(object, blur_obj, Size(11, 11), 5);
            //    addWeighted(object, 2, blur_obj, -1, 0, object);
            Mat scene = Cv2.ImRead("box_in_scene.png");

            AKAZE akaze = AKAZE.Create(); // 创建描述符对象detector
            KeyPoint[] keyPoint_scene, keyPoint_object;
            Mat descriptors_scene = new Mat(), descriptors_object = new Mat();
            // 计算描述符
            akaze.DetectAndCompute(scene, new Mat(), out keyPoint_scene, descriptors_scene, false);
            akaze.DetectAndCompute(obj, new Mat(), out keyPoint_object, descriptors_object, false);

            if (descriptors_object.Empty() || descriptors_scene.Empty())
            {
                Console.WriteLine( "findSamePoint_akaze is no find Point!!!" );
                return ;
            }

            BFMatcher matcher = new BFMatcher(NormTypes.Hamming); // 暴力匹配对象matcher，用汉明距匹配
            IList<DMatch> matches = null, goodMatches = new List<DMatch>();  // 存放暴力匹配结果matches，存放筛选后的匹配结果goodMatches
            matches = matcher.Match(descriptors_object, descriptors_scene); // 特征点匹配
            if (matches.Count==0)
            {
                Console.WriteLine(" findSamePoint_AKAZE is no find matches!!!" );
                return ;
            }

            // 获取汉明距的最大值
            float maxdist = matches[0].Distance;
            foreach (var match in matches)
            {
                if (maxdist < match.Distance)
                {
                    maxdist = match.Distance;
                }
            }


            float thresh = 0.5f;  // 设置距离 // 可以调整精度
            foreach (var matche in matches)
            {
                if (matche.Distance < thresh * maxdist)
                {
                    goodMatches.Add(matche);
                }
            }

            if (goodMatches.Count < 2)
            {
                Console.WriteLine("findSamePoint_AKAZE is no find good Point!!!");
                return ;
            }

            //  画出匹配结果图result1
            Mat result1 = new Mat();
            Cv2.DrawMatches(obj, keyPoint_object, scene, keyPoint_scene, goodMatches, result1,
                Scalar.All(-1), Scalar.All(-1), new List<byte>(), DrawMatchesFlags.Default);

            Cv2.ImShow("AKAZE match", result1);
            Cv2.WaitKey();

            // RANSAC优化

            IList<DMatch> matches_ransac = new List<DMatch>();// 存放RANSAC优化后的结果
            IList<Point2d> objectPoints = new List<Point2d>(), scenePoints= new List<Point2d>();  // 定义保存匹配点对坐标
            // 保存从关键点中提取到的匹配点对的坐标
            foreach (var goodMatche in goodMatches)
            {
                objectPoints.Add(new Point2d(keyPoint_object[goodMatche.QueryIdx].Pt.X, keyPoint_object[goodMatche.QueryIdx].Pt.Y));
                scenePoints.Add(new Point2d(keyPoint_scene[goodMatche.TrainIdx].Pt.X,keyPoint_scene[goodMatche.TrainIdx].Pt.Y));
            }

            if (objectPoints.Count < 4 || scenePoints.Count < 4)
            { // 匹配点数过少
                return ;
            }

            if (objectPoints.Count + scenePoints.Count < 9)
            {  // 匹配点数过少
                return ;
            }


            Mat inliersMask = new Mat();// inliersMask代表findHomography运算的输入点有效性
            Mat H = Cv2.FindHomography(objectPoints, scenePoints, HomographyMethods.Ransac, 4, inliersMask);

            // 手动保留 RANSAC 过滤后的匹配点对
            for (int i = 0; i < inliersMask.Size().Height; i++)
            {
                if(inliersMask.At<bool>(1, i))
                {
                    matches_ransac.Add(goodMatches[i]);
                }
            }
            result1 = new Mat();
            Cv2.DrawMatches(obj, keyPoint_object, scene, keyPoint_scene, matches_ransac, result1,
                Scalar.All(-1), Scalar.All(-1), new List<byte>(), DrawMatchesFlags.NotDrawSinglePoints);

            Cv2.ImShow("AKAZE match ransac", result1);
            Cv2.WaitKey();

            // 在scene上绘制匹配区域
            IList<Point2f> points = new List<Point2f>{new Point2f(0, 0), new Point2f(obj.Cols - 1, 0),
                new Point2f(obj.Cols - 1, obj.Rows - 1), new Point2f(0, obj.Rows - 1) }; // 这是object图的四个点（按照顺时针、逆时针顺序）

            points = Cv2.PerspectiveTransform(points,  H);

            IList<IList<Point>> pts = new List<IList<Point>>(); // 存放多个多边形点的集合
            pts.Add( new List<Point>() ); // 添加第一条曲线
            foreach (var p in points)
            {
                pts[0].Add(new Point(p.X, p.Y)); // Point2f -> Point
            }
            // 绘制四边形
            Cv2.Polylines(scene, pts, true, new Scalar(255, 0, 0), 2);
            Cv2.ImShow("out", scene);
            Cv2.WaitKey();

        }
    }
}

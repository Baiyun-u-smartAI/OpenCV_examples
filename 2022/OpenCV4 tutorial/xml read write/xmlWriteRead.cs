using System;
using System.IO;
using System.Xml;//导入xml读写
using Microsoft.Extensions.FileSystemGlobbing;//导入文件glob
using Microsoft.Extensions.FileSystemGlobbing.Abstractions;//导入文件glob

namespace split_merge
{
    class Program
    {

        
        
        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            // todo 写数据
            XmlTextWriter writer = new XmlTextWriter("test.xml", System.Text.Encoding.UTF8);
            writer.Formatting = Formatting.Indented;
            writer.WriteStartDocument();
            writer.WriteStartElement("opencv_storage");
            writer.WriteStartElement("images");

            // todo glob查找固定格式的文件
            // Get a reference to the directory you want to search in
            var folder = new DirectoryInfo(@".\");

            // Create and configure the FileSystemGlobbing Matcher
            var matcher = new Matcher();
            matcher.AddInclude("*.jpg");
            matcher.AddInclude("*.jpeg");
            matcher.AddInclude("*.png");
            matcher.AddInclude("*.bmp");
           
            // Execute the matcher against the directory
            var result = matcher.Execute(new DirectoryInfoWrapper(folder));

            Console.WriteLine("Has matches: " + result.HasMatches);
            foreach (var file in result.Files)
            {
                writer.WriteElementString("path", file.Path);
            }

            writer.WriteEndDocument();

            writer.Close();

            // todo 读数据
            XmlDocument testDoc = new XmlDocument();
            testDoc.Load("test.xml");
            XmlNodeList xnl = testDoc.SelectNodes("/opencv_storage/images/path");
            foreach (XmlNode xn in xnl)
            {
                Console.WriteLine(xn.InnerText);
            }

        }
    }
}

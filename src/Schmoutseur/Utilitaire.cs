using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

static class Globals
{
    static public string fileDirectory = System.Reflection.Assembly.GetEntryAssembly().Location;
    static public string workingDirectory = GetWorkingDirectory();

    static string GetWorkingDirectory()
    {
        string str = "";
        string[] path = fileDirectory.Split('\\');

        for (int i = 0; i < path.Count() - 5; i++)
            str += path[i] + "\\";

        return str + "rc";
    }
}

static class Path
{
    static public string RelativeToAbsolute(string relative)
    {
        string[] split = Globals.workingDirectory.Split('\\');
        string fileName = split[split.Count() - 1];
        string path = fileName.Contains('.') ? Globals.workingDirectory.Replace("\\" + fileName, string.Empty) : Globals.workingDirectory;

        foreach (string str in relative.Split('/'))
        {
            if (str.Equals(".."))
                path = path.Remove(path.Length - path.Split('\\').Last().Length - 1);
            else
                path += "\\" + str;
        }

        return path;
    }

    static public string AbsoluteToRelative(string input)
    {
        string fileName = input.Split('\\').Last();
        string path = "", temp = input;
        string absolute = temp;
        string workingDir = Globals.workingDirectory;

        while (temp == absolute)
        {
            temp = absolute.Replace(workingDir + "\\", string.Empty);
            if (temp != absolute)
                path += temp.Replace('\\', '/');
            else
            {
                workingDir = workingDir.Remove(workingDir.Length - workingDir.Split('\\').Last().Length - 1);
                temp = absolute;
                path += "../";
            }
        }
        return path;
    }
}

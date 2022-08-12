using System;
using UnityEngine;
using System.IO;


#if UNITY_EDITOR
using UnityEditor;
using UnityEditor.Callbacks;
#endif

public class PostBuildUtil
{
#if UNITY_EDITOR
    [PostProcessBuild(0)]
    public static void OnPostprocessBuild(BuildTarget target, string pathToBuiltProject)
    {
        string path = pathToBuiltProject.Replace(".exe", "");

        if (target == BuildTarget.StandaloneWindows64)
        {
            string baseSourcePath = Application.dataPath + "/Plugins/x86_64/NexPlayer/";
            string baseTargetPath = path + "_Data/Plugins/";
#if UNITY_2017 || UNITY_2018
            string x64TargetPath = baseTargetPath;
#else
            string x64TargetPath = baseTargetPath + "x86_64/";
#endif
            string pluginsSubfolder = "/plugins/";

            if (!Directory.Exists(baseSourcePath))
            {
                baseSourcePath = Application.dataPath + "/NexPlayer/Plugins/x86_64/NexPlayer/";

                if(!Directory.Exists(baseSourcePath))
                    throw new Exception("OnPostprocessBuild: source path doesn't exist: " + baseSourcePath);
            }

            // manually copy files (skipping .meta), deleting the duplicates in /x86_64 (checking Plugins)
            string[] filePaths = Directory.GetFiles(baseSourcePath);
            foreach (string filePath in filePaths)
            {
                if (Path.GetExtension(filePath) != ".meta")
                {
                    string filename = Path.GetFileName(filePath);
                    if (File.Exists(x64TargetPath + filename))
                    {
                        File.Delete(x64TargetPath + filename); // delete existing dlls
                    }

                    if (!File.Exists(baseTargetPath + filename))
                    {
                        FileUtil.CopyFileOrDirectory(filePath, baseTargetPath + filename); // copy new dlls
                    }
                }
            }

            if (!Directory.Exists(baseTargetPath + pluginsSubfolder))
            {
                FileUtil.CopyFileOrDirectory(baseSourcePath + pluginsSubfolder, baseTargetPath + pluginsSubfolder); // copy the whole plugins subfolder
            }

            // delete duplicate files in /x86_64 (checking plugins subfolder)
            string[] pluginsFilePaths = Directory.GetFiles(baseSourcePath + pluginsSubfolder, "*.dll", SearchOption.AllDirectories);
            foreach (string filePath in pluginsFilePaths)
            {
                string filename = Path.GetFileName(filePath);
                if (File.Exists(x64TargetPath + filename))
                {
                    File.Delete(x64TargetPath + filename);
                }
            }

            // delete .meta files
            string[] pluginsmetaFilePaths = Directory.GetFiles(baseTargetPath + pluginsSubfolder, "*.meta", SearchOption.AllDirectories);
            foreach (string filePath in pluginsmetaFilePaths)
            {
                File.Delete(filePath);
            }
        }
    }
#endif

}

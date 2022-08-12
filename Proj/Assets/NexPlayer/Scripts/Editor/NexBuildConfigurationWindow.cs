using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using UnityEngine.Rendering;
using System;

public class NexBuildConfigurationWindow : EditorWindow
{
    public static void ShowWindow()
    {
        NexBuildConfigurationWindow window = GetWindow<NexBuildConfigurationWindow>("NexPlayer Build Configuration Helper");
        window.maxSize = window.minSize = new Vector2(400, 500);
    }

    private void OnEnable()
    {
        NexBuildConfigurationHelper.Configure();
    }

    private void OnGUI()
    {
        DrawBuildTarget();

        switch (NexBuildConfigurationHelper.CurrentBuildTarget)
        {
            case BuildTarget.StandaloneWindows64:
                DrawWindows64();
                break;

            case BuildTarget.StandaloneWindows:
                DrawWindows32();
                break;

            case BuildTarget.StandaloneOSX:
                DrawMacOSX();
                break;

            case BuildTarget.Android:
                DrawAndroid();
                break;

            case BuildTarget.iOS:
                DrawiOS();
                break;

            case BuildTarget.WebGL:
                DrawWebGL();
                break;

            default:
                DrawMessage("Platform not supported! Please select a supported platform", MessageType.Error);
                break;
        }
    }

    void DrawBuildTarget()
    {
        GUIStyle customStyle = new GUIStyle(GUI.skin.GetStyle("label"));
        customStyle.fontStyle = FontStyle.Bold;
        customStyle.fontSize = 13;
        customStyle.alignment = TextAnchor.MiddleLeft;

        EditorGUILayout.Space();
        EditorGUILayout.LabelField("Current build target: ", customStyle, GUILayout.Width(130));
        Rect lastRect = GUILayoutUtility.GetLastRect();
        Rect nextRect = new Rect(lastRect.xMax + 10, lastRect.yMin + 2, position.width - lastRect.width - 50, lastRect.height);
        DrawDropdown(nextRect, new GUIContent($"{NexBuildConfigurationHelper.CurrentBuildTarget}"));
        EditorGUILayout.Space();

    }
    void DrawWindows64()
    {
        DrawTitle("Graphic APIs");
        DrawMessage("NexPlayer for Windows supports all the GraphicAPIs that Unity supports", MessageType.Info);

        if (!NexBuildConfigurationHelper.AreRecomendedGraphicAPIsSet(BuildTarget.StandaloneWindows64))
        {
            DrawMessage("It's recommended to use Direct3D and Auto Graphics API", MessageType.Warning);

            if (GUILayout.Button("Set recommended Graphic APIs"))
            {
                NexBuildConfigurationHelper.SetGraphicAPIs(BuildTarget.StandaloneWindows64);
            }
        }
        else
        {
            DrawMessage("Graphic APIs are set as recommended for Windows OS", MessageType.None);
        }

    }
    void DrawWindows32()
    {
        DrawMessage("NexPlayer does not support 32bit Windows OS", MessageType.Error);
        if(GUILayout.Button("Change to 64bit Windows OS"))
        {
            EditorUserBuildSettings.SwitchActiveBuildTarget(BuildTargetGroup.Standalone, BuildTarget.StandaloneWindows64);
        }
    }
    void DrawAndroid()
    {
        DrawTitle("Graphic APIs");

#if UNITY_2021_2_OR_NEWER
        if (NexBuildConfigurationHelper.IsVulkan(BuildTarget.Android))
        {
            DrawMessage("NexPlayer for Android does not support Vulkan", MessageType.Error);
            if (GUILayout.Button("Set recommended Graphic APIs"))
            {
                PlayerSettings.SetUseDefaultGraphicsAPIs(BuildTarget.Android, false);
                GraphicsDeviceType[] AndroidGraphicAPIs = new GraphicsDeviceType[] { GraphicsDeviceType.OpenGLES3 };
                NexBuildConfigurationHelper.SetGraphicAPIsAndroid(BuildTarget.Android, AndroidGraphicAPIs);
            }
        }
        else if (NexBuildConfigurationHelper.AreRecomendedGraphicAPIsSet(BuildTarget.Android))
        {
            DrawMessage("It is recommended to use OpenGLES3", MessageType.Warning);

            if (GUILayout.Button("Set recommended Graphic APIs"))
            {
                PlayerSettings.SetUseDefaultGraphicsAPIs(BuildTarget.Android, false);
                GraphicsDeviceType[] AndroidGraphicAPIs = new GraphicsDeviceType[] { GraphicsDeviceType.OpenGLES3 };
                NexBuildConfigurationHelper.SetGraphicAPIsAndroid(BuildTarget.Android, AndroidGraphicAPIs);
            }
        }
        else
        {
            DrawMessage("Graphic APIs are set as recommended for Android", MessageType.None);
        }
#else
        
        if (NexBuildConfigurationHelper.IsVulkan(BuildTarget.Android))
        {
            DrawMessage("NexPlayer for Android does not support Vulkan", MessageType.Error);
            if (GUILayout.Button("Set recommended Graphic APIs"))
            {
                NexBuildConfigurationHelper.SetGraphicAPIs(BuildTarget.Android);
            }
        }
        else if (!NexBuildConfigurationHelper.AreRecomendedGraphicAPIsSet(BuildTarget.Android))
        {
            DrawMessage("It is recommended to use OpenGLES3 and Auto Graphics API", MessageType.Warning);

            if (GUILayout.Button("Set recommended Graphic APIs"))
            {
                NexBuildConfigurationHelper.SetGraphicAPIs(BuildTarget.Android);
            }
        }
        else
        {
            DrawMessage("Graphic APIs are set as recommended for Android", MessageType.None);
        }
#endif
        DrawTitle("Internet Access");

        if(PlayerSettings.Android.forceInternetPermission == false)
        {
            DrawMessage("Internet Access must be set to Required to make Http requests", MessageType.Warning);

            if (GUILayout.Button("Set Internet Access to Required"))
            {
                PlayerSettings.Android.forceInternetPermission = true;
            }
        }
        else
        {
            DrawMessage("Internet Access properly set", MessageType.None);
        }

        DrawTitle("Write Permission");

        if (PlayerSettings.Android.forceSDCardPermission == false)
        {
            DrawMessage("Write Permission must be set to External to allow content downloads", MessageType.Warning);

            if (GUILayout.Button("Set Write Permission to External"))
            {
                PlayerSettings.Android.forceSDCardPermission = true;
            }
        }
        else
        {
            DrawMessage("Write Permission properly set", MessageType.None);
        }
    }

    void DrawiOS()
    {
        DrawTitle("Graphic APIs");

        if (NexBuildConfigurationHelper.ISOpenGL(BuildTarget.iOS))
        {
            DrawMessage("NexPlayer for iOS does not support OpenGLES", MessageType.Error);
            if (GUILayout.Button("Set recommended Graphic APIs"))
            {
                NexBuildConfigurationHelper.SetGraphicAPIs(BuildTarget.iOS);
            }
        }
        else if (!NexBuildConfigurationHelper.AreRecomendedGraphicAPIsSet(BuildTarget.iOS))
        {
            DrawMessage("It is recommended to use Auto Graphics API", MessageType.Warning);

            if (GUILayout.Button("Set recommended Graphic APIs"))
            {
                NexBuildConfigurationHelper.SetGraphicAPIs(BuildTarget.iOS);
            }
        }
        else
        {
            DrawMessage("Graphic APIs are set as recommended for iOS", MessageType.None);
        }

        DrawTitle("Internet Access");

        if (PlayerSettings.iOS.allowHTTPDownload == false)
        {
            DrawMessage("Internet Access must be set to Required to make Http requests", MessageType.Warning);

            if (GUILayout.Button("Set Allaw Http Downloads to true"))
            {
                PlayerSettings.Android.forceInternetPermission = true;
            }
        }
        else
        {
            DrawMessage("Internet Access properly set", MessageType.None);
        }

        DrawTitle("SDK version");

        var version = Int32.Parse(PlayerSettings.iOS.targetOSVersionString.Split('.')[0]);
        
        if (version < 8)
        {
            DrawMessage("NexPlayer for iOS requieres a minimum SDK of 8.0 ", MessageType.Error);
            if (GUILayout.Button("Set the minimum iOS SDK version to 8.0"))
            {
#if UNITY_5_5_OR_NEWER
                PlayerSettings.iOS.targetOSVersionString = "8.0";
#else
			PlayerSettings.iOS.targetOSVersion = iOSTargetOSVersion.iOS_8_0;
#endif
            }
        }
        else
        {
            DrawMessage("Minimum SDK version properly set", MessageType.None);
        }
    }
    void DrawMacOSX()
    {
        DrawTitle("Graphic APIs");

        if (NexBuildConfigurationHelper.AreRecomendedGraphicAPIsSet(BuildTarget.StandaloneOSX))
        {
            DrawMessage("Graphic APIs are set as recommended for MacOSX", MessageType.None);
        }
        else if (NexBuildConfigurationHelper.ISOpenGL(BuildTarget.StandaloneOSX))
        {
            DrawMessage("NexPlayer for MacOSX does not support OpenGLCore", MessageType.Error);
            if (GUILayout.Button("Set recommended Graphic APIs"))
            {
                NexBuildConfigurationHelper.SetGraphicAPIs(BuildTarget.StandaloneOSX);
            }
        }
        else
        {
            DrawMessage("It is recommended to use Auto Graphics API", MessageType.Warning);

            if (GUILayout.Button("Set recommended Graphic APIs"))
            {
                NexBuildConfigurationHelper.SetGraphicAPIs(BuildTarget.StandaloneOSX);
            }
        }
    }
    void DrawWebGL()
    {
        DrawTitle("Template");

#if UNITY_2020 || UNITY_2021
        if (!PlayerSettings.WebGL.template.Contains("2020_21"))
        {
            DrawMessage("It is recommended to use the NexPlayer Template", MessageType.Warning);

            if (GUILayout.Button("Select NexPlayer Template"))
            {
                PlayerSettings.WebGL.template = "PROJECT:2020_21";
            }
        }
        else
        {
            DrawMessage("Using recommended WebGL Template", MessageType.None);
        }

        if (!PlayerSettings.WebGL.decompressionFallback)
        {
            DrawMessage("It is recommended to use Decompression Fallback", MessageType.Warning);

            if (GUILayout.Button("Activate Decompression Fallback"))
            {
                PlayerSettings.WebGL.decompressionFallback = true;
            }
        }
#else
        if (!PlayerSettings.WebGL.template.Contains("2018_19"))
        {
            DrawMessage("It is recommended to use the NexPlayer Template", MessageType.Warning);

            if (GUILayout.Button("Select NexPlayer Template"))
            {
                PlayerSettings.WebGL.template = "PROJECT:2018_19";
            }
        }
        else
        {
            DrawMessage("Using recommended WebGL Template", MessageType.None);
        }
#endif
    }


    void DrawMessage(string msg, MessageType type)
    {
        EditorGUILayout.HelpBox(msg, type);
    }
    void DrawTitle(string title)
    {
        GUIStyle customStyle = new GUIStyle(GUI.skin.GetStyle("label"));
        customStyle.fontStyle = FontStyle.Bold;
        customStyle.fontSize = 12;

        EditorGUILayout.Space();
        EditorGUILayout.LabelField(title, customStyle);
    }
    void DrawDropdown(Rect position, GUIContent label)
    {
        if (EditorGUI.DropdownButton(position, label, FocusType.Passive))
        {
            GenericMenu menu = new GenericMenu();
            menu.AddItem(new GUIContent(BuildTarget.StandaloneWindows64.ToString()), false, NexBuildConfigurationHelper.SetBuildTarget, BuildTarget.StandaloneWindows64);
            menu.AddItem(new GUIContent(BuildTarget.Android.ToString()), false, NexBuildConfigurationHelper.SetBuildTarget, BuildTarget.Android);
            menu.AddItem(new GUIContent(BuildTarget.StandaloneOSX.ToString()), false, NexBuildConfigurationHelper.SetBuildTarget, BuildTarget.StandaloneOSX);
            menu.AddItem(new GUIContent(BuildTarget.iOS.ToString()), false, NexBuildConfigurationHelper.SetBuildTarget, BuildTarget.iOS);
            menu.AddItem(new GUIContent(BuildTarget.WebGL.ToString()), false, NexBuildConfigurationHelper.SetBuildTarget, BuildTarget.WebGL);
            menu.DropDown(position);
        }
    }
}

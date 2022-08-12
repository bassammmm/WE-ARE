using UnityEngine;
#if UNITY_EDITOR_WIN || UNITY_EDITOR_OSX || UNITY_EDITOR_LINUX
using UnityEditor;
#endif

[System.Serializable]
[CreateAssetMenu(menuName = "NexPlayer/NexMaterials")]
public class NexMaterials : ScriptableObject
{
    public RenderTexture[] renderTextures;
    [Header("Materials")]
    public Material Default;
    public Material NexPlayer;
    public Material RenderTexture0;
    public Material RenderTexture1;
    public Material RenderTexture2;
    public Material RenderTexture3;
    public Material Transparent;
    public Material WorldSpaceTiling;
    public Material Mono;
    public Material Left;
    public Material Right;
    public Material Over;
    public Material Under;
    [Header("Meshes")]
    public Mesh screen;
    public Mesh sphere360;
    public Mesh quad;
    public Mesh cube;

    public void ResetReferences()
    {
#if UNITY_EDITOR_WIN || UNITY_EDITOR_OSX || UNITY_EDITOR_LINUX
        // RENDER TEXTURES
        renderTextures = new RenderTexture[4];
        string folder = "Assets/NexPlayer/Materials/RenderTextures/";
        for (int i = 0; i < renderTextures.Length; i++)
        {
            renderTextures[i] = AssetDatabase.LoadAssetAtPath<RenderTexture>(folder + "RenderTexture" + i + ".renderTexture");
        }
        // MATERIALS
        string matFolder = "Assets/NexPlayer/Materials/";
        NexPlayer = AssetDatabase.LoadAssetAtPath<Material>(matFolder + "NexPlayerUnity.mat");
        RenderTexture0 = AssetDatabase.LoadAssetAtPath<Material>(matFolder + "RenderTexture0.mat");
        RenderTexture1 = AssetDatabase.LoadAssetAtPath<Material>(matFolder + "RenderTexture1.mat");
        RenderTexture2 = AssetDatabase.LoadAssetAtPath<Material>(matFolder + "RenderTexture2.mat");
        RenderTexture3 = AssetDatabase.LoadAssetAtPath<Material>(matFolder + "RenderTexture3.mat");
        Transparent = AssetDatabase.LoadAssetAtPath<Material>(matFolder + "Transparent.mat");
        WorldSpaceTiling = AssetDatabase.LoadAssetAtPath<Material>(matFolder + "WorldSpaceTiling.mat");
        Mono = AssetDatabase.LoadAssetAtPath<Material>(matFolder + "MaterialMono.mat");
        Left = AssetDatabase.LoadAssetAtPath<Material>(matFolder + "MaterialLeft.mat");
        Right = AssetDatabase.LoadAssetAtPath<Material>(matFolder + "MaterialRight.mat");
        Over = AssetDatabase.LoadAssetAtPath<Material>(matFolder + "MaterialOver.mat");
        Under = AssetDatabase.LoadAssetAtPath<Material>(matFolder + "MaterialUnder.mat");
        // MESHES
        screen = AssetDatabase.LoadAssetAtPath<Mesh>("Assets/NexPlayer/NexPlayer360/Resources/CurvedMesh.dae");
        sphere360 = AssetDatabase.LoadAssetAtPath<Mesh>("Assets/NexPlayer/NexPlayer360/Resources/SpherePoints.dae");
        var quadPrimitive = GameObject.CreatePrimitive(PrimitiveType.Quad);
        quad = quadPrimitive.GetComponent<MeshFilter>().sharedMesh;
        var cubePrimitive = GameObject.CreatePrimitive(PrimitiveType.Cube);
        cube = cubePrimitive.GetComponent<MeshFilter>().sharedMesh;
        Default = cubePrimitive.GetComponent<MeshRenderer>().sharedMaterial;

        EditorUtility.SetDirty(this);

        DestroyImmediate(quadPrimitive);
        DestroyImmediate(cubePrimitive);
#endif
    }
}

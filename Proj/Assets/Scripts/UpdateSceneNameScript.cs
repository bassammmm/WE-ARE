using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UpdateSceneNameScript : MonoBehaviour
{

    public string sceneName;
    public GameObject OnLoadPhotonObject;

    OnLoadPunManagerScript OnLoadPunScript;
    
    private void OnEnable()
    {
        OnLoadPunScript = OnLoadPhotonObject.GetComponent<OnLoadPunManagerScript>();
    }


    public void onVrEnvButtonClick()
    {
        OnLoadPunScript.SceneName = sceneName;
    }
}

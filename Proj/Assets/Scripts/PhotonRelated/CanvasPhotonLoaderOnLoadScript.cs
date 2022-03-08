using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CanvasPhotonLoaderOnLoadScript : MonoBehaviour
{
    public GameObject OnLoadPhotonObject;
    OnLoadPunManagerScript OnLoadPunScript;
    public GameObject MyCanvas;
    public GameObject FriendsCanvas;
    CanvasManagerPublicScript canvasManager;
    bool IsPunConnected = false;


    // Update is called once per frame
    void Update()
    {
        IsPunConnected = OnLoadPunScript.CheckLobbyConnected();
        if (IsPunConnected)
        {
            ChangeCanvasCreateRoom();
        }
    }

    private void OnEnable()
    {

        canvasManager = GameObject.Find("CanvasManager").gameObject.GetComponent<CanvasManagerPublicScript>();
        OnLoadPunScript = OnLoadPhotonObject.GetComponent<OnLoadPunManagerScript>();
        if (OnLoadPunScript.CheckLobbyConnected())
        {
            
            ChangeCanvasCreateRoom();
        }
        else
        {
            OnLoadPunScript.ConnectToPun();
        }
    }

    void ChangeCanvasCreateRoom()
    {
        canvasManager.canvasChange(MyCanvas, FriendsCanvas);
    }

}

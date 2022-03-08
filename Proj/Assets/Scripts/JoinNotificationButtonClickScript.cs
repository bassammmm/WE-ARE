using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
public class JoinNotificationButtonClickScript : MonoBehaviour
{

    public TMP_Text userID;
    public TMP_Text roomID;
    CanvasManagerPublicScript canvasManager;

    private void OnEnable()
    {
        canvasManager = GameObject.Find("CanvasManager").gameObject.GetComponent<CanvasManagerPublicScript>();

    }


    public void OnJoinClick()
    {
        var RoomID = roomID.text;
        GameObject PunManager = GameObject.Find("OnLoadPUNManager");
        OnLoadPunManagerScript PunManagerScript = PunManager.GetComponent<OnLoadPunManagerScript>();
        PunManagerScript.RoomID = RoomID;

        GameObject CanvasNotification = gameObject.transform.parent.transform.parent.transform.parent.transform.parent.transform.parent.transform.parent.transform.parent.gameObject;
        GameObject CanvasClientLoader = PunManagerScript.ClientLoaderCanvas;
        canvasManager.canvasChange(CanvasNotification, CanvasClientLoader);


    }
}

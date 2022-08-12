using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using Firebase;
using Firebase.Auth;
using Firebase.Firestore;
using Firebase.Extensions;
using Firebase.Storage;
using Firebase.Database;
public class JoinNotificationButtonClickScript : MonoBehaviour
{

    public TMP_Text userID;
    public TMP_Text roomID;
    public TMP_Text sceneName;
    public TMP_Text notificationKey;


    CanvasManagerPublicScript canvasManager;
    DatabaseReference reference;
    private void OnEnable()
    {
        canvasManager = GameObject.Find("CanvasManager").gameObject.GetComponent<CanvasManagerPublicScript>();

    }


    public void OnJoinClick()
    {
        var RoomID = roomID.text;
        var SceneName = sceneName.text;
        string key = notificationKey.text;
        GameObject PunManager = GameObject.Find("OnLoadPUNManager");
        OnLoadPunManagerScript PunManagerScript = PunManager.GetComponent<OnLoadPunManagerScript>();
        PunManagerScript.RoomID = RoomID;
        PunManagerScript.SceneName = SceneName;


        var app_ = GameObject.Find("__app");
        PreLoadTestPhotonObjects preLoadTestPhotonObjects = app_.GetComponent<PreLoadTestPhotonObjects>();
        preLoadTestPhotonObjects.notificationKey = key;

        //deleteNotification(key);


        GameObject CanvasNotification = gameObject.transform.parent.transform.parent.transform.parent.transform.parent.transform.parent.transform.parent.transform.parent.gameObject;
        GameObject CanvasClientLoader = PunManagerScript.ClientLoaderCanvas;
        canvasManager.canvasChange(CanvasNotification, CanvasClientLoader);


    }

    
}

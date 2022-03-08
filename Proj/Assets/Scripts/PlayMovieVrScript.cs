using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using Firebase;
using Firebase.Database;
using Firebase.Auth;
using TMPro;
public class PlayMovieVrScript : MonoBehaviour
{
    public GameObject OnLoadPhotonObject;
    OnLoadPunManagerScript OnLoadPunScript;
    public GameObject OnLoadCreateRoomObject;
    public GameObject OnLoad2DGameObject;
    public TMP_Text roomName;
    
    OnLoadCanvasVrCreateRoomScript onLoadScript;
    OnlLoad2DRealtimeDatabaseManager onLoadRealtimeScript;
    

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        var obj = GameObject.Find("__app");
        var objScript = obj.GetComponent<PreLoadTestPhotonObjects>();
        if (!objScript.roomEntered)
        {
            if (OnLoadPunScript.CheckRoomConnected())
            {
                objScript.roomEntered = true;
                //SceneManager.LoadSceneAsync("CinemaVr");
            }
        }

    }

    private void OnEnable()
    {
        onLoadScript = OnLoadCreateRoomObject.GetComponent<OnLoadCanvasVrCreateRoomScript>();
        onLoadRealtimeScript = OnLoad2DGameObject.GetComponent<OnlLoad2DRealtimeDatabaseManager>();
        OnLoadPunScript = OnLoadPhotonObject.GetComponent<OnLoadPunManagerScript>();

    }

    public void OnPlayVrMovieButton()
    {

        var auth = FirebaseAuth.DefaultInstance;

        var myuserId = auth.CurrentUser.UserId;

        foreach (string userId in onLoadScript.usersInvited)
        {

            var RoomName = roomName.text.Trim();
            onLoadRealtimeScript.InviteRoomMethodCall(userId, RoomName, myuserId);

        }


        OnLoadPunScript.CreateRoom(roomName.text.Trim());
        OnLoadPunScript.SceneName = "CinemaVR";
        
    }




}

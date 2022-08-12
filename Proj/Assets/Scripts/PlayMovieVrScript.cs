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
    public GameObject OnLoadCreateRoomObject;
    public GameObject OnLoadRealtimeGameObject;
    public TMP_Text roomName;
    public GameObject ErrorMessage;

    OnLoadPunManagerScript OnLoadPunScript;
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
        onLoadRealtimeScript = OnLoadRealtimeGameObject.GetComponent<OnlLoad2DRealtimeDatabaseManager>();
        OnLoadPunScript = OnLoadPhotonObject.GetComponent<OnLoadPunManagerScript>();

    }

    public void OnPlayVrMovieButton()
    {
        var RoomName = roomName.text.Trim();



        if (RoomName.Length <= 2)
        {
            ErrorMessage.SetActive(true);
        }
        else
        {
            var auth = FirebaseAuth.DefaultInstance;

            var myuserId = auth.CurrentUser.UserId;

            var sceneName = OnLoadPunScript.SceneName;

            Debug.Log("Scene Name being sent to users : " + sceneName);

            foreach (string userId in onLoadScript.usersInvited)
            {

                RoomName = roomName.text.Trim();
                onLoadRealtimeScript.InviteRoomMethodCall(userId, RoomName, myuserId, sceneName);

            }


            OnLoadPunScript.CreateRoom(roomName.text.Trim());

        }


    }




}

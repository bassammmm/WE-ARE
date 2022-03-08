using Photon.Pun;
using Photon.Realtime;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using Firebase.Auth;
using Firebase;
//monobehaviour puncallbacks used because onconnectedtomaster is a function of that class
public class OnLoadPunManagerScript : MonoBehaviourPunCallbacks
{


    public string RoomID;
    public string SceneName;

    public GameObject ClientLoaderCanvas;
    // Start is called before the first frame update
    private void Start()
    {
        

    }


    public bool CheckPunConnected()
    {
        if (PhotonNetwork.IsConnected)
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    public bool CheckLobbyConnected()
    {
        if (PhotonNetwork.InLobby)
        {
            return true;
        }
        else
        {
            return false;
        }

    }


    public void ConnectToPun()
    {
        print("Connecting to server");

        var userID = FirebaseAuth.DefaultInstance.CurrentUser.UserId;
        PhotonNetwork.NickName = userID;
        // Just set the game version so that when you update the version, it doesn't cause errors
        PhotonNetwork.GameVersion = "0.0.0";
        PhotonNetwork.ConnectUsingSettings();
    }

    public override void OnConnectedToMaster()
    {
        print("Connected to server");
        print(PhotonNetwork.LocalPlayer.NickName);
        Debug.Log("Region : " + PhotonNetwork.CloudRegion);
        // You have to join the lobby to get room updates.
        PhotonNetwork.JoinLobby(); //no arg, lobby type as default
    }
    public override void OnDisconnected(DisconnectCause cause)
    {
        //press f12 to check where it is placed. 
        //base.OnDisconnected(cause);
        print("Disconnected to server\nReason: " + cause.ToString());
    }
    public override void OnJoinedLobby()
    {
        Debug.Log("Joined lobby");
        
    }















    public void CreateRoom(string roomName)
    {

        if (!PhotonNetwork.IsConnected)
            ConnectToPun();

        RoomOptions options = new RoomOptions();
        options.MaxPlayers = 4;
        options.IsVisible = true;
        Debug.Log("The input value of the room to be created is: " + roomName);
        PhotonNetwork.JoinOrCreateRoom(roomName, options, TypedLobby.Default);
    }
    public override void OnCreatedRoom()
    {
        Debug.Log("Created room successfully", this);
        
    }
    public override void OnCreateRoomFailed(short returnCode, string message)
    {
        Debug.Log("Room creation failed" + message, this);
    }

    public bool CheckRoomConnected()
    {
        if (PhotonNetwork.InRoom)
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    public void JoinRoom(string roomID)
    {
        Debug.Log("HErerere222 : "+roomID);

        PhotonNetwork.JoinRoom(roomID);
        Debug.Log("HErerere333");


    }

    public override void OnJoinedRoom()
    {
        Debug.Log("Room Connected");
        ConnectToScene();
    }

    public void ConnectToScene()
    {
        Debug.Log("Connecting to scene");
        PhotonNetwork.LoadLevel(SceneName);
        Debug.Log("Connected to scene");

    }









}












using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR;
using Firebase;
using Firebase.Auth;
using Firebase.Firestore;
using Firebase.Extensions;
using Firebase.Storage;
using UnityEngine.UI;
using UnityEngine.Assertions;
using Photon.Pun;
using TMPro;
using Photon.Realtime;
using ExitGames.Client.Photon;
using System.Threading.Tasks;
using UnityEngine.Video;


public class CinemaVRinitVrScript : MonoBehaviour
{
    public GameObject text;

    public GameObject PlayerMutablePrefab;
    public GameObject PlayerPrefab;

    string av_name;
    bool initiated = false;
    GameObject myPrefab;
    int ViewId;
    string Username;
    GameObject PlayerListNameObject;
    public long currentFrame;


    public const byte CREATE_PLAYERNAME_LIST = 3;
    public const byte SET_MOVIE_FRAME = 12;

    private void Awake()
    {

        //InitiatePrefabNetwork();

    }



    void Start()
    {
        
        StartCoroutine(SwitchToVR());
        
        setUserName();
        setPlayerAvatar();

        UpdatePlayerList();
        Debug.Log(PhotonNetwork.CurrentRoom.Name);
        VideoPlayer videoPlayer = GameObject.Find("VideoPlayer").GetComponent<VideoPlayer>();
        videoPlayer.Prepare();

    }


    private void Update()
    {
        
    }






    private void OnEnable()
    {
        PhotonNetwork.NetworkingClient.EventReceived += NetworkingClient_EventReceived;
    }

    private void OnDisable()
    {
        PhotonNetwork.NetworkingClient.EventReceived -= NetworkingClient_EventReceived;
    }


    private void NetworkingClient_EventReceived(EventData obj)
    {
        if (obj.Code == CREATE_PLAYERNAME_LIST)
        {
            PhotonPlayerList();

        }
        else if (obj.Code == SET_MOVIE_FRAME)
        {
            //Dosomething;
            object[] datas = (object[])obj.CustomData;
            long currFrame = (long)datas[0];
            Debug.Log(currFrame);
            Debug.Log("------------------------------------------------------------------------->>>>>>>>>>>>>>>> IN RPC");
            VideoPlayer videoPlayer = GameObject.Find("VideoPlayer").GetComponent<VideoPlayer>();
            videoPlayer.frame = currFrame;
            videoPlayer.Prepare();
            
        }
    }


    public void setMovieFrameRaiseEvent(long currFrame)
    {
        object[] datas = new object[] { currFrame };
        RaiseEventOptions raiseEventOptions = new RaiseEventOptions { Receivers = ReceiverGroup.All };
        PhotonNetwork.RaiseEvent(SET_MOVIE_FRAME, datas, raiseEventOptions, SendOptions.SendUnreliable);
    }




    void UpdatePlayerList()
    {
        object[] datas = new object[] { 0 };
        RaiseEventOptions raiseEventOptions = new RaiseEventOptions { Receivers = ReceiverGroup.All };
        PhotonNetwork.RaiseEvent(CREATE_PLAYERNAME_LIST, datas, raiseEventOptions, SendOptions.SendUnreliable);
    }



    void PhotonPlayerList()
    {
        var PlayerListParent = GameObject.Find("PlayerNames");
        foreach (Transform child in PlayerListParent.transform)
        {
            if(child.transform.tag== "PlayerMutablePrefab")
            {
                Destroy(child.gameObject);
            }
        }

        foreach (Player player in PhotonNetwork.PlayerListOthers)
        {
            var userID = player.NickName;

            getFireBaseUsernameAsync(userID);

        }
    }


    void getFireBaseUsernameAsync(string userID)
    {
        var firestore = FirebaseFirestore.DefaultInstance;
        firestore.Collection("users").Document(userID).GetSnapshotAsync().ContinueWithOnMainThread(task =>
        {
            Assert.IsNull(task.Exception);
            var characterData = task.Result.ConvertTo<CharacterStruct>();
            var userName = characterData.UserName;



            AddUserNameInPlayerList(userName,userID);

        });
    }


    void AddUserNameInPlayerList(string userNameSent,string userID)
    {
        //var playerlistparent = gameobject.find("playernames");
        //var prefabsinlist = gameobject.findgameobjectswithtag("playermutableprefab").length;
        //var x = 9.1;
        //var y = 4.5;
        //var z = 8;

        //for (int i = 0; i < prefabsinlist; i++)
        //{
        //    y = y - 0.5;
        //}

        //playerlistnameobject = instantiate(playermutableprefab, new vector3(playermutableprefab.transform.position.x, playermutableprefab.transform.position.y, playermutableprefab.transform.position.z), quaternion.identity, playerlistparent.transform);
        //playerlistnameobject.transform.position = new vector3((float)x, (float)y, (float)z);

        //gameobject username = playerlistnameobject.transform.getchild(1).transform.getchild(0).gameobject;
        //debug.log("player list : " + username);
        //debug.log("player list : " + username.getcomponent<textmeshprougui>().text);

        //username.getcomponent<textmeshprougui>().text = username;


        string usernamenetwork = userNameSent;
        var PlayerListParent = GameObject.Find("PlayerNames");
        var prefabsInList = GameObject.FindGameObjectsWithTag("PlayerMutablePrefab").Length;
        var x = 9.1;
        var y = 4.5;
        var z = 8;

        for (int i = 0; i < prefabsInList; i++)
        {
            y = y - 0.5;
        }

        PlayerListNameObject = Instantiate(PlayerMutablePrefab, new Vector3(PlayerMutablePrefab.transform.position.x, PlayerMutablePrefab.transform.position.y, PlayerMutablePrefab.transform.position.z), Quaternion.identity, PlayerListParent.transform);
        PlayerListNameObject.transform.position = new Vector3((float)x, (float)y, (float)z);


        GameObject userViewId = PlayerListNameObject.transform.GetChild(0).gameObject;
        userViewId.GetComponent<Text>().text = userID;

        GameObject userName = PlayerListNameObject.transform.GetChild(1).transform.GetChild(0).gameObject;
        userName.GetComponent<TextMeshProUGUI>().text = usernamenetwork;


    }





    void InitiatePrefabNetwork(string prefabName)
    {
        var obj = GameObject.Find("__app");
        var objScript = obj.GetComponent<PreLoadTestPhotonObjects>();
        if (!objScript.myNetworkPrefab)
        {

            var x = PhotonNetwork.Instantiate(prefabName, new Vector3((float)-0.982, (float)-0.2, (float)2.5), Quaternion.identity);
            Debug.Log(x.name);
            objScript.myNetworkPrefab = true;
            myPrefab = x;
            //x.transform.GetChild(1).transform.position = new Vector3(myPrefab.transform.GetChild(1).transform.position.x, (float)(myPrefab.transform.GetChild(1).transform.position.y - 1.56), myPrefab.transform.GetChild(1).transform.position.z);
            text.GetComponent<Text>().text = "Test : " + x.transform.GetChild(1).transform.position;
            ViewId = x.GetComponent<PhotonView>().ViewID;
        }

    }



    void setPlayerAvatar()
    {

        Debug.Log("Set Player Avatar");
        var auth = FirebaseAuth.DefaultInstance;
        var user = auth.CurrentUser;
        string userId = user.UserId;
        Debug.Log(user.UserId);
        var firestore = FirebaseFirestore.DefaultInstance;
        firestore.Collection("users").Document(userId).Collection("avatars").Document("avatarData").GetSnapshotAsync().ContinueWithOnMainThread(task =>
        {
            Assert.IsNull(task.Exception);
            var avatarData = task.Result.ConvertTo<AvatarStruct>();
            
            av_name = avatarData.AvatarName;



            InitiatePrefabNetwork(av_name);

            //GameObject avatarPrefab = Resources.Load<GameObject>(av_name);
            //Debug.Log(avatarPrefab);



            //var x = Instantiate(avatarPrefab, new Vector3(0, 1, 0), Quaternion.identity);
            //myPrefab.transform.GetChild(1).transform.position = new Vector3(myPrefab.transform.GetChild(1).transform.position.x, (float) (myPrefab.transform.GetChild(1).transform.position.y - 1.56), myPrefab.transform.GetChild(1).transform.position.z);

            //var x = PhotonNetwork.Instantiate(avatarPrefab.name, new Vector3(camera.transform.GetChild(0).position.x, camera.transform.GetChild(0).position.y, camera.transform.GetChild(0).position.z), Quaternion.identity);

            //x.transform.parent = camera.transform;
            //camera.transform.GetChild(1).position = new Vector3(camera.transform.GetChild(1).position.x, (float)(camera.transform.GetChild(1).position.y - 1.4), camera.transform.GetChild(1).position.z);

            //camera.transform.GetChild(1).GetChild(0).GetChild(0).GetChild(2).GetChild(0).GetChild(0).GetChild(1).GetChild(0).transform.parent = camera.transform.GetChild(0).transform;


        });


        

        
    }


    public void setUserName()
    {
        var auth = FirebaseAuth.DefaultInstance;
        var user = auth.CurrentUser;
        string userId = user.UserId;

        var firestore = FirebaseFirestore.DefaultInstance;
        firestore.Collection("users").Document(userId).GetSnapshotAsync().ContinueWithOnMainThread(task =>
        {
            Assert.IsNull(task.Exception);
            var characterData = task.Result.ConvertTo<CharacterStruct>();
            Username = characterData.UserName;

            //text.GetComponent<Text>().text = characterData.FirstName + ' ' + characterData.LastName;

        });
    }



    IEnumerator SwitchToVR()
    {
        // Device names are lowercase, as returned by `XRSettings.supportedDevices`.
        string desiredDevice = "cardboard"; // Or "cardboard".

        // Some VR Devices do not support reloading when already active, see
        // https://docs.unity3d.com/ScriptReference/XR.XRSettings.LoadDeviceByName.html
        if (System.String.Compare(XRSettings.loadedDeviceName, desiredDevice, true) != 0)
        {
            XRSettings.LoadDeviceByName(desiredDevice);

            // Must wait one frame after calling `XRSettings.LoadDeviceByName()`.
            yield return null;
        }

        // Now it's ok to enable VR mode.
        XRSettings.enabled = true;
    }

}


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

public class TicTacToeVrInitScript : MonoBehaviour
{

    public const byte UPDATE_PLAYER_SCALE = 5;
    public const byte UPDATE_PLAYER_NAME = 7;
    public string marker;
    public TMP_Text PlayerOne;
    public TMP_Text PlayerTwo;
    public GameObject GameManager;

    TicTacToeGameManager gameManagerScript;

    string av_name;
    bool initiated = false;
    int ViewId;
    string Username;
    GameObject PlayerListNameObject;


    void Start()
    {
        Debug.Log("PHOTON NETWORK PLAYERS : "+PhotonNetwork.PlayerList.Length);

        StartCoroutine(SwitchToVR());

        setUserName();
        setPlayerAvatar();

        Debug.Log(PhotonNetwork.CurrentRoom.Name);
    }








    private void OnEnable()
    {
        gameManagerScript = GameManager.GetComponent<TicTacToeGameManager>();
        PhotonNetwork.NetworkingClient.EventReceived += NetworkingClient_EventReceived;
    }

    private void OnDisable()
    {
        PhotonNetwork.NetworkingClient.EventReceived -= NetworkingClient_EventReceived;
    }

    private void NetworkingClient_EventReceived(EventData obj)
    {
        if (obj.Code == UPDATE_PLAYER_SCALE)
        {
            updatePlayerScale();

        }
        else if(obj.Code == UPDATE_PLAYER_NAME)
        {

            object[] datas = (object[])obj.CustomData;
            string userID = (string)datas[0];
            updatePlayerName(userID);
        }
    }


    void updatePlayerScale()
    {
        foreach (GameObject PlayerClone in GameObject.FindGameObjectsWithTag("Player"))
        {
            Debug.Log("Player Clone : "+PlayerClone);
            PlayerClone.transform.localScale = new Vector3(2, 2, 2);
            
        }
    }


    void updatePlayerName(string userID)
    {
        getFireBaseUsernameAsync(userID, PlayerTwo, "p2");
        gameManagerScript.playerTwoId = userID;
    }


    void ScalePlayers()
    {
        object[] datas = new object[] { 0 };
        RaiseEventOptions raiseEventOptions = new RaiseEventOptions { Receivers = ReceiverGroup.All };
        PhotonNetwork.RaiseEvent(UPDATE_PLAYER_SCALE, datas, raiseEventOptions, SendOptions.SendUnreliable);
    }


    void UpdatePlayerTwoName(string userID)
    {
        Debug.Log("here in update player raise event");
        object[] datas = new object[] { userID };
        RaiseEventOptions raiseEventOptions = new RaiseEventOptions { Receivers = ReceiverGroup.All };
        PhotonNetwork.RaiseEvent(UPDATE_PLAYER_NAME, datas, raiseEventOptions, SendOptions.SendUnreliable);
    }



    void InitiatePrefabNetwork(string prefabName)
    {
        var obj = GameObject.Find("__app");
        var objScript = obj.GetComponent<PreLoadTestPhotonObjects>();
        if (!objScript.myNetworkPrefab)
        {
            GameObject x;
            
            if (PhotonNetwork.PlayerList.Length > 1)
            {
                x = PhotonNetwork.Instantiate(prefabName, new Vector3((float)1.305, (float)2.852, (float)0.6472567), transform.rotation * Quaternion.Euler(0f, 270f, 0f));
                marker = "circle";

                UpdatePlayerTwoName(PhotonNetwork.NickName);

                getFireBaseUsernameAsync(PhotonNetwork.PlayerListOthers[0].NickName, PlayerOne, "p1");
                gameManagerScript.playerOneId = PhotonNetwork.PlayerListOthers[0].NickName;



            }
            else
            {
                x = PhotonNetwork.Instantiate(prefabName, new Vector3((float)-2.012, (float)2.852, (float)0.6472567), transform.rotation * Quaternion.Euler(0f, 90f, 0f));

                marker = "cross";

                getFireBaseUsernameAsync(PhotonNetwork.NickName,PlayerOne, "p1");
                gameManagerScript.playerOneId = PhotonNetwork.NickName;
            }
            Debug.Log(x.name);
            objScript.myNetworkPrefab = true;
           
            ViewId = x.GetComponent<PhotonView>().ViewID;

            ScalePlayers();
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





    void getFireBaseUsernameAsync(string userID, TMP_Text player, string usernameVariable)
    {
        var firestore = FirebaseFirestore.DefaultInstance;
        firestore.Collection("users").Document(userID).GetSnapshotAsync().ContinueWithOnMainThread(task =>
        {
            Assert.IsNull(task.Exception);
            var characterData = task.Result.ConvertTo<CharacterStruct>();
            var userName = characterData.UserName;

            player.GetComponent<TextMeshProUGUI>().text = userName + " -NotReady";
            if (usernameVariable == "p1")
            {
                gameManagerScript.playerOneUsername = userName;
            }
            else
            {
                gameManagerScript.playerTwoUsername = userName;
            }

        });
    }




}



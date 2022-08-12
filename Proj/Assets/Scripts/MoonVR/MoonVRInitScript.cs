
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


public class MoonVRInitScript : MonoBehaviour
{
    string av_name;
    bool initiated = false;
    GameObject myPrefab;
    int ViewId;
    string Username;
    GameObject PlayerListNameObject;




    void Start()
    {
        StartCoroutine(SwitchToVR());

        setUserName();
        setPlayerAvatar();

        Debug.Log(PhotonNetwork.CurrentRoom.Name);
    }





    void InitiatePrefabNetwork(string prefabName)
    {
        var obj = GameObject.Find("__app");
        var objScript = obj.GetComponent<PreLoadTestPhotonObjects>();
        if (!objScript.myNetworkPrefab)
        {

            GameObject x;

            if (PhotonNetwork.PlayerList.Length == 1)
            {


                x = PhotonNetwork.Instantiate(prefabName, new Vector3((float)9.047, (float)6.07, (float)18.708), transform.rotation * Quaternion.Euler(0f, 69.568f, 0f));

            } else if (PhotonNetwork.PlayerList.Length == 2)
            {
                x = PhotonNetwork.Instantiate(prefabName, new Vector3((float)8.85, (float)6.07, (float)20.621), transform.rotation * Quaternion.Euler(0f, 116.175f, 0f));

            } else if (PhotonNetwork.PlayerList.Length == 3)
            {
                x = PhotonNetwork.Instantiate(prefabName, new Vector3((float)10.367, (float)6.07, (float)21.893), transform.rotation * Quaternion.Euler(0f, 146.675f, 0f));

            } else
            {
                x = PhotonNetwork.Instantiate(prefabName, new Vector3((float)12.237, (float)6.07, (float)21.993), transform.rotation * Quaternion.Euler(0f, 184.723f, 0f));

            } 

            Debug.Log(x.name);
            objScript.myNetworkPrefab = true;
            myPrefab = x;
            //x.transform.GetChild(1).transform.position = new Vector3(myPrefab.transform.GetChild(1).transform.position.x, (float)(myPrefab.transform.GetChild(1).transform.position.y - 1.56), myPrefab.transform.GetChild(1).transform.position.z);
            //text.GetComponent<Text>().text = "Test : " + x.transform.GetChild(1).transform.position;
            //ViewId = x.GetComponent<PhotonView>().ViewID;
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





    














}

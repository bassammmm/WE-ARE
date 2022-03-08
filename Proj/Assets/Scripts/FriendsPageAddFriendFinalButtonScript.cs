using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Firebase;
using Firebase.Auth;
using Firebase.Firestore;
using Firebase.Extensions;
using Firebase.Storage;
using System;
using UnityEngine.UI;
using TMPro;

public class FriendsPageAddFriendFinalButtonScript : MonoBehaviour
{
    GameObject ContentFriendObject;
    FriendsPageLoaderScript loaderScript;
    OnlLoad2DRealtimeDatabaseManager realtimeManagerScript;

    private void OnEnable()
    {
        realtimeManagerScript = GameObject.Find("OnLoadRealtimeManager").GetComponent<OnlLoad2DRealtimeDatabaseManager>();


    }

    public void AddFriendClick()
    {
        ContentFriendObject = gameObject.transform.parent.parent.gameObject;

        GameObject addFriendBlock = gameObject.transform.parent.gameObject;
        string friendId = addFriendBlock.transform.Find("id").GetComponent<TMP_Text>().text;


        var auth = FirebaseAuth.DefaultInstance;
        string userId = auth.CurrentUser.UserId;

        //var data = new UserFriendStruct
        //{
        //    FriendUID = friendId
        //};

        //AddFriendData(data);


        realtimeManagerScript.SendFriendRequest(userId, friendId);





        foreach (Transform child in ContentFriendObject.transform)
        {
            GameObject.Destroy(child.gameObject);
        }


        loaderScript = new FriendsPageLoaderScript();
        loaderScript.GetFriendsData();
    }

    private void AddFriendData(UserFriendStruct data)
    {

        Debug.Log("Adding Friend");
        var auth = FirebaseAuth.DefaultInstance;
        string uid = auth.CurrentUser.UserId;
        var firestore = FirebaseFirestore.DefaultInstance;

        var task = firestore.Collection("users").Document(uid).Collection("friends").Document(data.FriendUID).SetAsync(data);
        if (task.Exception != null)
        {
            Debug.Log($"Firestore data upload error {task.Exception}");
        }
        else
        {
            Debug.Log("Firestore data uploaded successfully!");
        }
    }


}

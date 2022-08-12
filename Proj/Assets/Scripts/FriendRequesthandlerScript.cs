using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Firebase.Auth;
using Firebase.Firestore;
using TMPro;
using Firebase.Database;
using Firebase.Extensions;

public class FriendRequesthandlerScript : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }


    public void OnAcceptClick()
    {


        AddFriendFirestore();




        DeleteFriendReq();

        RefreshFriendList();


    }


    public void RefreshFriendList()
    {
        GameObject canvasFriends = GameObject.Find("Canvas (Friends)");
        FriendsPageLoaderScript friendsLoader = canvasFriends.GetComponent<FriendsPageLoaderScript>();
        friendsLoader.GetFriendsData();
    }


    public void OnRejectClick()
    {
        DeleteFriendReq();

    }


    public void AddFriendFirestore()
    {


        var auth = FirebaseAuth.DefaultInstance;
        string uid = auth.CurrentUser.UserId;
        var firestore = FirebaseFirestore.DefaultInstance;



        var friendId = gameObject.transform.parent.gameObject.transform.Find("id").GetComponent<TMP_Text>().text;

        var data = new UserFriendStruct
        {
            FriendUID = friendId
        };

        var data2 = new UserFriendStruct
        {
            FriendUID = uid
        };



        

        var task = firestore.Collection("users").Document(uid).Collection("friends").Document(data.FriendUID).SetAsync(data);
        if (task.Exception != null)
        {
            Debug.Log($"Firestore data upload error {task.Exception}");
        }
        else
        {
            Debug.Log("Firestore data uploaded successfully!");
        }

        var task2 = firestore.Collection("users").Document(friendId).Collection("friends").Document(data2.FriendUID).SetAsync(data2);
        if (task2.Exception != null)
        {
            Debug.Log($"Firestore data upload error {task.Exception}");
        }
        else
        {
            Debug.Log("Firestore data uploaded successfully!");
        }

    }


    public void DeleteFriendReq()
    {
        var friendId = gameObject.transform.parent.gameObject.transform.Find("id").GetComponent<TMP_Text>().text;
        var userId = FirebaseAuth.DefaultInstance.CurrentUser.UserId;
        DatabaseReference reference = FirebaseDatabase.DefaultInstance.RootReference;


        reference.Child("FriendRequest").Child(userId).GetValueAsync().ContinueWithOnMainThread(task =>
        {
            if (task.IsFaulted)
            {
                // Handle the error...
                Debug.LogWarning($"Error Reading Invites : {task.Exception}");
            }
            else if (task.IsCompleted)
            {
                DataSnapshot snapshot = task.Result;


                foreach (DataSnapshot childSnapshot in snapshot.Children)
                {
                    string recievedID = childSnapshot.Child("recievedID").Value.ToString();
                    string sentID = childSnapshot.Child("sentID").Value.ToString();
                    if (sentID == friendId)
                    {
                        reference.Child("FriendRequest").Child(userId).Child(childSnapshot.Key).SetValueAsync(null);
                    }
                    
                }



            }

        });
    }




}

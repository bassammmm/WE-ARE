using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Firebase;
using Firebase.Auth;
using Firebase.Database;
using Firebase.Firestore;
using Firebase.Extensions;

public class OnlLoad2DRealtimeDatabaseManager : MonoBehaviour
{

    public DatabaseReference reference;

    // Start is called before the first frame update
    void Start()
    {

        reference = FirebaseDatabase.DefaultInstance.RootReference;

    }

    // Update is called once per frame
    void Update()
    {

    }



    public void InviteRoomMethodCall(string userID, string roomID, string hostUserID)
    {
        StartCoroutine(InviteRoomMethod(userID, roomID, hostUserID));
    }

    public IEnumerator InviteRoomMethod(string userID, string roomID, string hostUserID)
    {
        InviteData inv_data = new InviteData(userID, roomID, hostUserID);
        string json = JsonUtility.ToJson(inv_data);
        string key = reference.Child("Invites").Child(userID).Push().Key;
        var AddInviteTask = reference.Child("Invites").Child(userID).Child(key).SetRawJsonValueAsync(json);

        yield return new WaitUntil(() => AddInviteTask.IsCompleted);
        if (AddInviteTask.Exception != null)
        {
            Debug.LogWarning($"Invite couldn't be sent to {userID} : {AddInviteTask.Exception}");
        }
        else
        {
            Debug.Log($"Invite sent to {userID}");
        }

    }

    
    public void SendFriendRequest(string userID, string friendID)
    {
        StartCoroutine(FriendReqMethod(userID, friendID));
    }


    public IEnumerator FriendReqMethod(string userID, string friendID)
    {
        FriendReq friendReq = new FriendReq(userID, friendID);
        string json = JsonUtility.ToJson(friendReq);
        string key = reference.Child("FriendRequest").Child(friendID).Push().Key;
        var AddFriendReqTask = reference.Child("FriendRequest").Child(friendID).Child(key).SetRawJsonValueAsync(json);

        yield return new WaitUntil(() => AddFriendReqTask.IsCompleted);


        if (AddFriendReqTask.Exception != null)
        {
            Debug.LogWarning($"Invite couldn't be sent to {userID} : {AddFriendReqTask.Exception}");
        }
        else
        {
            Debug.Log($"Invite sent to {friendID}");
        }


    }


}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Firebase.Firestore;


[FirestoreData]
public struct CharacterStruct
{
    [FirestoreProperty]
    public string FirstName { get; set; }

    [FirestoreProperty]
    public string LastName { get; set; }

    [FirestoreProperty]
    public string UserName { get; set; }

    

}


[FirestoreData]
public struct UserFriendStruct
{
    [FirestoreProperty]
    public string FriendUID { get; set; }


}



[FirestoreData]
public struct AvatarStruct
{
    [FirestoreProperty]
    public string AvatarName { get; set; }


}


public class InviteData
{
    public string userID;
    public string roomID;
    public string hostID;
    public string sceneName;


    public InviteData(string userID, string roomID, string hostID, string sceneName)
    {
        this.userID = userID;
        this.roomID = roomID;
        this.hostID = hostID;
        this.sceneName = sceneName;
    }
}

public class FriendReq
{
    public string sentID;
    public string recievedID;

    public FriendReq(string sentID, string recievedID)
    {
        this.sentID = sentID;
        this.recievedID = recievedID;
    }

}
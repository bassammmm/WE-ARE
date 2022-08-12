using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Firebase;
using Firebase.Auth;
using Firebase.Firestore;
using Firebase.Extensions;
using Firebase.Storage;
using Firebase.Database;
using TMPro;
using UnityEngine.Assertions;
using System.Threading.Tasks;
public class OnLoadNotificationsManagerScript : MonoBehaviour
{

    public GameObject ViewFriendsContent;
    public GameObject NotificationInvitePrefab;


    public GameObject NotificationFriendsContent;
    public GameObject NotificationFriendRequestPrefab;


    public GameObject Onload2dRealtimeManager;


    OnlLoad2DRealtimeDatabaseManager realTimeManagerScript;
    DatabaseReference reference;
    string firstName;
    string lastName;
    string userName;

    string firstNameReq;
    string lastNameReq;
    string userNameReq;
    bool enabled = false;

    // Start is called before the first frame update
    void OnEnable()
    {
        bool error = false;
        try
        {

            var user = FirebaseAuth.DefaultInstance.CurrentUser;

            var email = user.Email;
        }
        catch
        {

            error = true;
        }
        
        if (!error)
        {
            EnableMethodFunc();
        }

    }


    public void EnableMethodFunc()
    {
        if (!enabled)
        {
            realTimeManagerScript = Onload2dRealtimeManager.GetComponent<OnlLoad2DRealtimeDatabaseManager>();

            reference = realTimeManagerScript.reference;

            //StartCoroutine(UploadNotificationStart());

            var userId = FirebaseAuth.DefaultInstance.CurrentUser.UserId;
            reference = FirebaseDatabase.DefaultInstance.RootReference;

            reference.Child("Invites").Child(userId).ValueChanged += NotificationChangedHandler;

            reference.Child("FriendRequest").Child(userId).ValueChanged += FriendReqChangeHandler;
            enabled = true;
        }

    }

    // Update is called once per frame
    void Update()
    {
        
    }


    void FriendReqChangeHandler(object sender, ValueChangedEventArgs args)
    {



        if (args.DatabaseError != null)
        {
            Debug.LogError(args.DatabaseError.Message);
            return;
        }

        foreach (Transform child in NotificationFriendsContent.transform)
        {
            GameObject.Destroy(child.gameObject);
        }

        Debug.Log("here... HANDLER METHOD FRIEND REQ");
        var userId = FirebaseAuth.DefaultInstance.CurrentUser.UserId;
        reference = FirebaseDatabase.DefaultInstance.RootReference;


        reference.Child("FriendRequest").Child(userId).GetValueAsync().ContinueWithOnMainThread(async task =>
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
                    

                    await GetFriendsDataCallReq(sentID);


                    GameObject friendReqPrefab = Instantiate<GameObject>(NotificationFriendRequestPrefab);
                    friendReqPrefab.transform.SetParent(NotificationFriendsContent.transform, false);
                    friendReqPrefab.transform.Find("Text (TMP) ViewFriendName").GetComponent<TMP_Text>().text = firstNameReq + " " + lastNameReq + " (" + userNameReq + ")";
                    friendReqPrefab.transform.Find("id").GetComponent<TMP_Text>().text = sentID;



                }



            }

        });


    }



    void NotificationChangedHandler(object sender, ValueChangedEventArgs args)
    {
        if (args.DatabaseError != null)
        {
            Debug.LogError(args.DatabaseError.Message);
            return;
        }

        foreach (Transform child in ViewFriendsContent.transform)
        {
            GameObject.Destroy(child.gameObject);
        }

        
        ArrayList inv_data = new ArrayList();
        var userId = FirebaseAuth.DefaultInstance.CurrentUser.UserId;
        reference = FirebaseDatabase.DefaultInstance.RootReference;

        reference.Child("Invites").Child(userId).GetValueAsync().ContinueWithOnMainThread(async task =>
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


                    string notificationKey = childSnapshot.Key;

                    string roomID = childSnapshot.Child("roomID").Value.ToString();
                    string userID = childSnapshot.Child("userID").Value.ToString();
                    string hostID = childSnapshot.Child("hostID").Value.ToString();
                    string sceneName = childSnapshot.Child("sceneName").Value.ToString();
                    inv_data.Add(new InviteData(userID, roomID, hostID,sceneName));


                    await GetFriendsDataCall(hostID);


                    GameObject notificationPref = Instantiate<GameObject>(NotificationInvitePrefab);
                    notificationPref.transform.SetParent(ViewFriendsContent.transform, false);
                    notificationPref.transform.Find("Text (TMP) ViewFriendName").GetComponent<TMP_Text>().text = firstName + " " + lastName + " (" + userName + ")" + " || " + roomID;
                    notificationPref.transform.Find("id").GetComponent<TMP_Text>().text = hostID;
                    notificationPref.transform.Find("roomid").GetComponent<TMP_Text>().text = roomID;
                    notificationPref.transform.Find("sceneName").GetComponent<TMP_Text>().text = sceneName;
                    notificationPref.transform.Find("notificationkey").GetComponent<TMP_Text>().text = notificationKey;
                    


                }



            }

        });






    }








    public async Task GetFriendsDataCall(string Id)
    {
        var auth = FirebaseAuth.DefaultInstance;
        var user = auth.CurrentUser;
        string userId = user.UserId;

        var firestore = FirebaseFirestore.DefaultInstance;
        await firestore.Collection("users").Document(Id).GetSnapshotAsync().ContinueWith(task =>
        {
            Assert.IsNull(task.Exception);
            var characterData = task.Result.ConvertTo<CharacterStruct>();


            firstName = characterData.FirstName;
            lastName = characterData.LastName;
            userName = characterData.UserName;



        });


        return;
    }


    public async Task GetFriendsDataCallReq(string Id)
    {
        var auth = FirebaseAuth.DefaultInstance;
        var user = auth.CurrentUser;
        string userId = user.UserId;

        var firestore = FirebaseFirestore.DefaultInstance;
        await firestore.Collection("users").Document(Id).GetSnapshotAsync().ContinueWith(task =>
        {
            Assert.IsNull(task.Exception);
            var characterData = task.Result.ConvertTo<CharacterStruct>();


            firstNameReq = characterData.FirstName;
            lastNameReq = characterData.LastName;
            userNameReq = characterData.UserName;



        });


        return;
    }


}

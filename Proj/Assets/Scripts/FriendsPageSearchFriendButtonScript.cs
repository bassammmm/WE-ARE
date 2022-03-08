using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using Firebase;
using Firebase.Auth;
using Firebase.Firestore;
using Firebase.Extensions;
using Firebase.Storage;
using System;
using UnityEngine.UI;
using UnityEngine.Assertions;
using System.Threading.Tasks;
using Firebase.Database;

public class FriendsPageSearchFriendButtonScript : MonoBehaviour
{
    public GameObject searchInput;
    public GameObject FriendScrollObjectPrefab;
    public GameObject ContentFriendObject;


    bool FriendExist = false;
    Sprite mySprite;

    public void OnSearchFriendClick()
    {

        foreach (Transform child in ContentFriendObject.transform)
        {
            GameObject.Destroy(child.gameObject);
        }


        string searchName = searchInput.GetComponent<TMP_InputField>().text;


        SearchFirestoreFriends(searchName);



        
        
    }

    public void SearchFirestoreFriends(string username)
    {
        var user = FirebaseAuth.DefaultInstance.CurrentUser;
        string userId = user.UserId;

        var db = FirebaseFirestore.DefaultInstance;






        Debug.Log("searching");


        //Query userQuery = db.Collection("users").WhereEqualTo("UserName", username);

        Firebase.Firestore.Query userQuery = db.Collection("users").OrderBy("UserName").StartAt(username).EndAt(username+"\uf8ff");



        userQuery.GetSnapshotAsync().ContinueWithOnMainThread(async task => {
            QuerySnapshot userResultsSnapShots = task.Result;
            foreach (DocumentSnapshot documentSnapshot in userResultsSnapShots.Documents)
            {
                Debug.Log(String.Format("Document data for {0} document:", documentSnapshot.Id));
                CharacterStruct userStruct = documentSnapshot.ConvertTo<CharacterStruct>();

                Debug.Log(userStruct.FirstName);
                Debug.Log(userStruct.LastName);
                Debug.Log(userStruct.UserName);




                FriendExist = false;

                await CheckFriend(documentSnapshot.Id);


                Debug.Log("Valueeeeee : " + FriendExist);

                if (!FriendExist)
                {
                    if (userId != documentSnapshot.Id)
                    {
                        GameObject addFriend = Instantiate<GameObject>(FriendScrollObjectPrefab);
                        addFriend.transform.SetParent(ContentFriendObject.transform, false);

                        addFriend.transform.Find("Text (TMP) AddFriendName").GetComponent<TMP_Text>().text = userStruct.FirstName + " " + userStruct.LastName + " (" + userStruct.UserName + ")";
                        addFriend.transform.Find("id").GetComponent<TMP_Text>().text = documentSnapshot.Id;



                        StartCoroutine(getProfilePic(addFriend, documentSnapshot.Id));

                        // Newline to separate entries
                        Debug.Log("");
                    }
                }
            };
        });
        
    }

    public async Task CheckFriend(string Id)
    {
        var user = FirebaseAuth.DefaultInstance.CurrentUser;
        string userId = user.UserId;

        var db = FirebaseFirestore.DefaultInstance;


        Firebase.Firestore.Query userFriendAlready = db.Collection("users").Document(userId).Collection("friends").WhereEqualTo("FriendUID", Id);
        await userFriendAlready.GetSnapshotAsync().ContinueWith(task2 =>
        {
            if (task2.IsCompleted) { 
                Assert.IsNull(task2.Exception);
                QuerySnapshot userResultsSnapShots2 = task2.Result;
                int count = 0;
                foreach (DocumentSnapshot documentSnapshotfriend in userResultsSnapShots2.Documents)
                {

                    count = count + 1;
                };
                if (count > 0)
                {
                    FriendExist = true;
                    Debug.Log("Friend Already exists!");
                }
            };
        });




        //CHecking for friend request already sent????
        Debug.Log("Checking in requestss");

        DatabaseReference reference = FirebaseDatabase.DefaultInstance.RootReference.Child("FriendRequest");

        await reference.GetValueAsync().ContinueWithOnMainThread(task3 =>
        {
            if (task3.IsFaulted)
            {
                // Handle the error...
                Debug.LogWarning($"Error Reading Invites : {task3.Exception}");
            }
            else if (task3.IsCompleted)
            {
                DataSnapshot snapshot = task3.Result;


                foreach (DataSnapshot childSnapshot in snapshot.Children)
                {
                    
                    foreach (DataSnapshot grandChildSnapshot in childSnapshot.Children)
                    {

                        string recievedID = grandChildSnapshot.Child("recievedID").Value.ToString();
                        string sentID = grandChildSnapshot.Child("sentID").Value.ToString();
                        if (sentID==userId & recievedID== Id)
                        {
                            FriendExist = true;
                        }

                    }




                }



            }

        });









        return;
    }

    private IEnumerator getProfilePic(GameObject addFriend,string userId)
    {

        
        var storage = FirebaseStorage.DefaultInstance;

        var newMetaData = new MetadataChange();
        newMetaData.ContentType = "image/jpeg";
        StorageReference storageRef = storage.GetReferenceFromUrl("gs://fyp-proj2021.appspot.com/profilePics/");

        string picName = userId + "_profilePic.jpeg";

        StorageReference pictureRef = storageRef.Child(picName);



        const long maxAllowedSize = 5 * 1024 * 1024;
        var downloadTask = pictureRef.GetBytesAsync(maxAllowedSize).ContinueWithOnMainThread(task => {
            if (task.IsFaulted || task.IsCanceled)
            {
                Debug.LogException(task.Exception);
                // Uh-oh, an error occurred!
            }
            else
            {
                byte[] fileContents = task.Result;
                Debug.Log("Finished downloading!");
                Debug.Log("Profile Pic loaded!");
                Texture2D texture = new Texture2D(1, 1, TextureFormat.ARGB32, false);

                texture.LoadImage(fileContents);

                mySprite = Sprite.Create(texture, new Rect(0.0f, 0.0f, texture.width, texture.height), new Vector2(0.5f, 0.5f), 100.0f);
                addFriend.transform.Find("Image ProfilePicAddFriend").GetComponent<Image>().sprite = mySprite;
            }
        });

        yield return new WaitUntil(() => downloadTask.IsCompleted);


        yield return null;

    }

}

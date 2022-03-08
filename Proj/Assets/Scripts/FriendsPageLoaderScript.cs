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
using UnityEngine.Assertions;
using System.Threading.Tasks;

public class FriendsPageLoaderScript : MonoBehaviour
{
    public GameObject ViewFriendsContent;
    public GameObject FriendScrollObjectPrefab;
    string firstName;
    string lastName;
    string userName;





    Sprite mySprite;
    UserFriendStruct userStruct;
    




    void Start()
    {
        
        
    }


    private void OnEnable()
    {
        GetFriendsData();
    }


    public void GetFriendsData()
    {


        foreach (Transform child in ViewFriendsContent.transform)
        {
            GameObject.Destroy(child.gameObject);
        }
        var user = FirebaseAuth.DefaultInstance.CurrentUser;
        string userId = user.UserId;

        var db = FirebaseFirestore.DefaultInstance;


        Query userQuery = db.Collection("users").Document(userId).Collection("friends");
        userQuery.GetSnapshotAsync().ContinueWithOnMainThread(async task =>
        {
            QuerySnapshot userResultsSnapShots = task.Result;
            foreach (DocumentSnapshot documentSnapshot in userResultsSnapShots.Documents)
            {
                Debug.Log(String.Format("Document data for {0} document:", documentSnapshot.Id));
                UserFriendStruct userStruct = documentSnapshot.ConvertTo<UserFriendStruct>();

                await GetFriendsDataCall(documentSnapshot.Id);

                GameObject viewFriend = Instantiate<GameObject>(FriendScrollObjectPrefab);
                viewFriend.transform.SetParent(ViewFriendsContent.transform, false);

                viewFriend.transform.Find("Text (TMP) ViewFriendName").GetComponent<TMP_Text>().text = firstName + " " + lastName + " (" + userName + ")";
                viewFriend.transform.Find("id").GetComponent<TMP_Text>().text = documentSnapshot.Id;



                StartCoroutine(getProfilePic(viewFriend, documentSnapshot.Id));

                // Newline to separate entries
                Debug.Log("");


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





    private IEnumerator getProfilePic(GameObject addFriend, string userId)
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
                addFriend.transform.Find("Image ProfilePicViewFriend").GetComponent<Image>().sprite = mySprite;
            }
        });

        yield return new WaitUntil(() => downloadTask.IsCompleted);


        yield return null;

    }




}



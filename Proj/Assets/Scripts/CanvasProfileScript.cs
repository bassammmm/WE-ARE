using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Firebase;
using Firebase.Auth;
using Firebase.Firestore;
using Firebase.Extensions;
using Firebase.Storage;
using TMPro;
using UnityEngine.Assertions;
using UnityEngine.UI;
public class CanvasProfileScript : MonoBehaviour
{

    public GameObject username;
    public GameObject userprofile;
    public GameObject image;

    
    Sprite mySprite;



    // Start is called before the first frame update
    void Start()
    {
        image.GetComponent<ProfileAvatarImageLoader>().SetImage();
        var auth = FirebaseAuth.DefaultInstance;
        var user = auth.CurrentUser;
        string userId = user.UserId;
        
        var firestore = FirebaseFirestore.DefaultInstance;
        firestore.Collection("users").Document(userId).GetSnapshotAsync().ContinueWithOnMainThread(task =>
        {
            Assert.IsNull(task.Exception);
            var characterData = task.Result.ConvertTo<CharacterStruct>();
            Debug.Log(characterData.FirstName);

            username.GetComponent<TMP_Text>().text = characterData.FirstName + ' ' + characterData.LastName;
            


        });

        StartCoroutine(getProfilePic());

    }

    private IEnumerator getProfilePic()
    {

        var user = FirebaseAuth.DefaultInstance.CurrentUser;
        string userId = user.UserId;

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

                userprofile.GetComponent<Image>().sprite = mySprite;
            }
        });

        yield return new WaitUntil(() => downloadTask.IsCompleted);


        yield return null;

    }



    // Update is called once per frame
    void Update()
    {
        
    }



}

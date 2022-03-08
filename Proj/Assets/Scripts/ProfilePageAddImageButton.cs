using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Firebase;
using Firebase.Auth;
using Firebase.Firestore;
using Firebase.Storage;
using Firebase.Extensions;
using System.Threading.Tasks;
using TMPro;
using System.IO;

public class ProfilePageAddImageButton : MonoBehaviour
{

    public GameObject ImageUI;


    Texture2D texture;
    Sprite mySprite;
    string FilePath;
    string md5Hash;

    public void OnInsertPicClick()
    {
		StartCoroutine(PickImage(1024));
    }

    private IEnumerator PickImage(int maxSize)
	{

        yield return new WaitForEndOfFrame();
        NativeGallery.Permission permission = NativeGallery.GetImageFromGallery((path) =>
		{
			
            
            texture = NativeGallery.LoadImageAtPath(path, maxSize,true,false,false);
            mySprite = Sprite.Create(texture, new Rect(0.0f, 0.0f, texture.width, texture.height), new Vector2(0.5f, 0.5f), 100.0f);

            ImageUI.GetComponent<Image>().sprite = mySprite;

            FilePath = path;

            Debug.Log("File Path  :  " + path);
            if (path.Length>1)
            {
                UploadPic();
            }
        });

		
        

        

        
    }

    private void UploadPic()
    {
        var user = FirebaseAuth.DefaultInstance.CurrentUser;
        string userId = user.UserId;

        var storage = FirebaseStorage.DefaultInstance;

        var newMetaData = new MetadataChange();
        newMetaData.ContentType = "image/jpeg";
        StorageReference storageRef = storage.GetReferenceFromUrl("gs://fyp-proj2021.appspot.com/profilePics/");

        string picName = userId + "_profilePic.jpeg";

        StorageReference pictureRef = storageRef.Child(picName);



        // File located on disk
        string localFile = Uri.UriSchemeFile + "://" + FilePath;

        Debug.Log("LOCAL FILE  : " + localFile);


        // Upload the file to the path "images/rivers.jpg"
        pictureRef.PutFileAsync(localFile, newMetaData).ContinueWith((Task<StorageMetadata> task) => {
            if (task.IsFaulted || task.IsCanceled)
            {
                Debug.Log("PutFileAsync Error : " + task.Exception.ToString());

                // Uh-oh, an error occurred!
            }
            else
            {
                // Metadata contains file metadata such as size, content-type, and download URL.
                StorageMetadata metadata = task.Result;
                md5Hash = metadata.Md5Hash;
                Debug.Log("Finished uploading...");

                Debug.Log("md5 hash = " + md5Hash);

            }
        });
    }

}

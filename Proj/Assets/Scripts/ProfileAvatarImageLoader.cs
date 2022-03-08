using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Firebase;
using Firebase.Auth;
using Firebase.Firestore;
using Firebase.Extensions;
using Firebase.Storage;
using UnityEngine.Assertions;

public class ProfileAvatarImageLoader : MonoBehaviour
{


    public Image image;
    Image _image;
    public string[] ImageNames = { "m1", "m2", "m3", "m4", "m5", "fm1", "fm2", "fm3", "fm4", "fm5" };

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void SetImage()
    {
        var auth = FirebaseAuth.DefaultInstance;
        var user = auth.CurrentUser;
        string userId = user.UserId;

        var firestore = FirebaseFirestore.DefaultInstance;
        firestore.Collection("users").Document(userId).Collection("avatars").Document("avatarData").GetSnapshotAsync().ContinueWithOnMainThread(task =>
        {
            Assert.IsNull(task.Exception);
            var avatarData = task.Result.ConvertTo<AvatarStruct>();
            Debug.Log(avatarData.AvatarName);

            var img_name = avatarData.AvatarName;
            var tex = Resources.Load<Texture2D>("Avatars/PNGS/" + img_name);
            var sprite = Sprite.Create(tex, new Rect(0.0f, 0.0f, tex.width, tex.height), new Vector2(0.5f, 0.5f), 100.0f);
            image.sprite = sprite;


        });

    }


}

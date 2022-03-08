using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Firebase;
using Firebase.Auth;
using Firebase.Firestore;
using Firebase.Extensions;
using Firebase.Storage;
public class EditAvatarButtonsScript : MonoBehaviour
{
    // Start is called before the first frame update

    public Image image;
    Image _image;
    public string[] ImageNames = {"m1","m2","m3","m4","m5","fm1","fm2","fm3","fm4","fm5"};
    public GameObject Loader;
    EditAvatarLoaderScript loader;
    public GameObject profileAvatarImage;


    void Start()
    {
        loader = Loader.GetComponent<EditAvatarLoaderScript>();
    }
    public void OnDownClick()
    {
        loader.IncrementIndex();
        Debug.Log(loader.IndexImage);
        var img_name = ImageNames[loader.IndexImage];
        var tex = Resources.Load<Texture2D>("Avatars/PNGS/"+img_name);
        var sprite = Sprite.Create(tex, new Rect(0.0f, 0.0f, tex.width, tex.height), new Vector2(0.5f, 0.5f), 100.0f);
        image.sprite = sprite;
    }

    public void OnUpClick()
    {
        loader.DecrementIndex();
        Debug.Log(loader.IndexImage);
        var img_name = ImageNames[loader.IndexImage];
        var tex = Resources.Load<Texture2D>("Avatars/PNGS/" + img_name);
        var sprite = Sprite.Create(tex, new Rect(0.0f, 0.0f, tex.width, tex.height), new Vector2(0.5f, 0.5f), 100.0f);
        image.sprite = sprite;
    }


    public void ChooseAvatarClick()
    {
        var auth = FirebaseAuth.DefaultInstance;
        string userId = auth.CurrentUser.UserId;

        var data = new AvatarStruct
        {
            AvatarName = ImageNames[loader.IndexImage]
        };

        AddAvatarData(data);
        ChangeCanvasScript sc = gameObject.GetComponent<ChangeCanvasScript>();
        profileAvatarImage.GetComponent<ProfileAvatarImageLoader>().SetImage();
        sc.OnChangeClick();

    }


    void AddAvatarData(AvatarStruct data)
    {
        var auth = FirebaseAuth.DefaultInstance;
        string uid = auth.CurrentUser.UserId;
        var firestore = FirebaseFirestore.DefaultInstance;

        var task = firestore.Collection("users").Document(uid).Collection("avatars").Document("avatarData").SetAsync(data);
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

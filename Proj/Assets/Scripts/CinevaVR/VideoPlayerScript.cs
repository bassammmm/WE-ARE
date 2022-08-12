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
using UnityEngine.Video;
public class VideoPlayerScript : MonoBehaviour
{

    public VideoPlayer videoPlayer;
    // Start is called before the first frame update
    void Start()
    {



    }

    // Update is called once per frame
    void Update()
    {
        if (videoPlayer.frameCount > 0)
        {
            //Debug.Log(videoPlayer.frame + "/" + videoPlayer.frameCount);
        }
    }




}

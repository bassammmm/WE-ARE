using Photon.Pun;
using Photon.Realtime;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using Firebase.Auth;
using Firebase.Firestore;
using Firebase.Extensions;
using Firebase.Storage;
using Firebase.Database;
using UnityEngine.Video;

public class PreLoadTestPhotonObjects : MonoBehaviourPunCallbacks
{

    public bool myNetworkPrefab =false;
    public bool roomEntered = false;
    public string notificationKey;
    

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
        
    }



  

    public override void OnMasterClientSwitched(Player newMasterClient)
    {
        base.OnMasterClientSwitched(newMasterClient);
        



        ExitVRScript exitVrScript = GameObject.Find("exit").GetComponent<ExitVRScript>();

        exitVrScript.OnCinemaVrButtonClick();
        deleteNotification();
    }

    public override void OnPlayerLeftRoom(Player otherPlayer)
    {
        base.OnPlayerLeftRoom(otherPlayer);
        ExitVRScript exitVrScript = GameObject.Find("exit").GetComponent<ExitVRScript>();
        string sceneName = exitVrScript.SceneName;
        if (sceneName == "TicTacToe")
        {
            GameObject gameManager = GameObject.Find("GameManager");
            TicTacToeGameManager ticTacToeGameManager = gameManager.GetComponent<TicTacToeGameManager>();

            ticTacToeGameManager.clearTicTacToeBoard();
            ticTacToeGameManager.playerOneReady = false;
            ticTacToeGameManager.playerTwoReady = false;
            ticTacToeGameManager.GameOver = false;
            ticTacToeGameManager.AllowPlay = false;
            ticTacToeGameManager.WinnerBoard.SetActive(false);
            ticTacToeGameManager.setUserNotRead();
        }
        else if (sceneName== "CinemaVR")
        {
            VideoPlayer videoPlayer = GameObject.Find("VideoPlayer").GetComponent<VideoPlayer>();


            Debug.Log("--------------------------------------->>>> Video PLayer");
            videoPlayer.Pause();
            CinemaVRinitVrScript cinemaVRinitVrScript = GameObject.Find("ObjectOnLoad").GetComponent<CinemaVRinitVrScript>();
            cinemaVRinitVrScript.currentFrame = videoPlayer.frame;
            Debug.Log("----------------------------------------->>>>>");
            Debug.Log(cinemaVRinitVrScript.currentFrame);



        }
    }



    public override void OnPlayerEnteredRoom(Player newPlayer)
    {
        base.OnPlayerEnteredRoom(newPlayer);
        Debug.Log(newPlayer);
        Debug.Log("------------------------------------------------------------------->>>>>>>>>>> asdasdasd");

        StartCoroutine(waitcall());

    }

    IEnumerator waitcall()
    {
        yield return new WaitForSeconds(3);
        CinemaVRinitVrScript cinemaVRinitVrScript = GameObject.Find("ObjectOnLoad").GetComponent<CinemaVRinitVrScript>();

        cinemaVRinitVrScript.setMovieFrameRaiseEvent(cinemaVRinitVrScript.currentFrame + 10);
    }









    public void deleteNotification()
    {
        var userId = FirebaseAuth.DefaultInstance.CurrentUser.UserId;
        DatabaseReference reference = FirebaseDatabase.DefaultInstance.RootReference;

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


                    string nkey = childSnapshot.Key;
                    if (nkey == notificationKey)
                    {
                        reference.Child("Invites").Child(userId).Child(childSnapshot.Key).SetValueAsync(null);
                    }


                }


            }

        });


    }

}

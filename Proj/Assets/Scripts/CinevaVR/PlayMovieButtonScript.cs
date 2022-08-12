using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Video;
using Photon.Pun;
using Photon.Realtime;
using ExitGames.Client.Photon;

public class PlayMovieButtonScript : MonoBehaviour
{

    public VideoPlayer vidPlayer;
    public const byte PLAYVID_EVENT = 1;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnEnable()
    {
        PhotonNetwork.NetworkingClient.EventReceived += NetworkingClient_EventReceived;
    }

    private void OnDisable()
    {
        PhotonNetwork.NetworkingClient.EventReceived -= NetworkingClient_EventReceived;
    }


    private void NetworkingClient_EventReceived(EventData obj)
    {
        if (obj.Code == PLAYVID_EVENT)
        {
            vidPlayer.Play();
            CinemaVRinitVrScript cinemaVRinitVrScript = GameObject.Find("ObjectOnLoad").GetComponent<CinemaVRinitVrScript>();
            cinemaVRinitVrScript.currentFrame = vidPlayer.frame;
        }
    }





    public void PlayMovieClick()
    {
        vidPlayer.Play();
        object[] datas = new object[] { 0 };
        RaiseEventOptions raiseEventOptions = new RaiseEventOptions { Receivers = ReceiverGroup.All };
        PhotonNetwork.RaiseEvent(PLAYVID_EVENT, datas, raiseEventOptions, SendOptions.SendUnreliable);
    }


   


}

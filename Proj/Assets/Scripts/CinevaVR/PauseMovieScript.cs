using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Video;
using Photon.Pun;
using Photon.Realtime;
using ExitGames.Client.Photon;

public class PauseMovieScript : MonoBehaviour
{
    public VideoPlayer vidPlayer;
    public const byte PAUSEVID_EVENT = 2;
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
        if (obj.Code == PAUSEVID_EVENT)
        {
            vidPlayer.Pause();
        }
    }





    public void PauseMovieClick()
    {
        vidPlayer.Pause();
        object[] datas = new object[] { 0 };
        RaiseEventOptions raiseEventOptions = new RaiseEventOptions { Receivers = ReceiverGroup.All };
        PhotonNetwork.RaiseEvent(PAUSEVID_EVENT, datas, raiseEventOptions, SendOptions.SendUnreliable);
    }



}

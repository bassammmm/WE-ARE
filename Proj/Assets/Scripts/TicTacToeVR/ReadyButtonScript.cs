
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR;
using Firebase;
using Firebase.Auth;
using Firebase.Firestore;
using Firebase.Extensions;
using Firebase.Storage;
using UnityEngine.UI;
using UnityEngine.Assertions;
using Photon.Pun;
using TMPro;
using Photon.Realtime;
using ExitGames.Client.Photon;
using System.Threading.Tasks;

public class ReadyButtonScript : MonoBehaviour
{
    public GameObject GameManager;
    TicTacToeGameManager gameManagerScript;
    public TMP_Text ReadyButtonText;


    public const byte READY_PLAYER_EVENT = 8;

    private void OnEnable()
    {
        gameManagerScript = GameManager.GetComponent<TicTacToeGameManager>();
        PhotonNetwork.NetworkingClient.EventReceived += NetworkingClient_EventReceived;
    }

    private void OnDisable()
    {
        PhotonNetwork.NetworkingClient.EventReceived -= NetworkingClient_EventReceived;
    }


    private void NetworkingClient_EventReceived(EventData obj)
    {
        if (obj.Code == READY_PLAYER_EVENT)
        {
            
            object[] datas = (object[])obj.CustomData;
            string userID = (string)datas[0];
            gameManagerScript.ReadyButtonClick(userID);

        }
    }


    public void onReadyClick()
    {
        if (PhotonNetwork.PlayerListOthers.Length < 1)
        {
            Debug.Log("Waiting for player 1!");
        }
        else
        {
            Debug.Log("Setting Player One Ready-first button");
            object[] datas = new object[] { PhotonNetwork.NickName };
            RaiseEventOptions raiseEventOptions = new RaiseEventOptions { Receivers = ReceiverGroup.All };
            PhotonNetwork.RaiseEvent(READY_PLAYER_EVENT, datas, raiseEventOptions, SendOptions.SendUnreliable);
            //gameObject.SetActive(false);
            ReadyButtonText.GetComponent<TextMeshProUGUI>().text = "Waiting...";
        }

    }

}

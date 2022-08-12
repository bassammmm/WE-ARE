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


public class TileClickScript : MonoBehaviour
{
    TicTacToeGameManager gameManagerScript;
    TicTacToeVrInitScript tictactoeOnLoadScript;
    GameObject cross;
    GameObject circle;

    public const byte UPDATE_TILE_TOGGLE = 6;

    private void OnEnable()
    {
        gameManagerScript = GameObject.Find("GameManager").gameObject.GetComponent<TicTacToeGameManager>();
        tictactoeOnLoadScript = GameObject.Find("ObjectOnLoad").gameObject.GetComponent<TicTacToeVrInitScript>();
        cross = gameObject.transform.GetChild(0).gameObject;
        circle = gameObject.transform.GetChild(1).gameObject;

        PhotonNetwork.NetworkingClient.EventReceived += NetworkingClient_EventReceived;


    }

    private void OnDisable()
    {
        PhotonNetwork.NetworkingClient.EventReceived -= NetworkingClient_EventReceived;
    }

    private void NetworkingClient_EventReceived(EventData obj)
    {
        if (obj.Code == UPDATE_TILE_TOGGLE)
        {
            object[] datas = (object[])obj.CustomData;
            string name = (string)datas[0];
            string marker = (string)datas[1];
            toggleTile(name,marker);

        }
    }


    void toggleTile(string name,string marker)
    {

        GameObject tile = GameObject.Find(name).gameObject;
        cross = tile.transform.GetChild(0).gameObject;
        circle = tile.transform.GetChild(1).gameObject;

        if (marker == "cross")
        {
            cross.SetActive(!cross.activeSelf);
        }
        else
        {
            circle.SetActive(!circle.activeSelf);
        }
    }


    void ToggleTileClick(string name, string marker)
    {
        object[] datas = new object[] { name,marker };
        RaiseEventOptions raiseEventOptions = new RaiseEventOptions { Receivers = ReceiverGroup.All };
        PhotonNetwork.RaiseEvent(UPDATE_TILE_TOGGLE, datas, raiseEventOptions, SendOptions.SendUnreliable);
    }




    public void OnClick()
    {


        Debug.Log("Here ON Click");
        cross = gameObject.transform.GetChild(0).gameObject;
        circle = gameObject.transform.GetChild(1).gameObject;

        if (PhotonNetwork.NickName== gameManagerScript.PlayerTurnID)
        {
            if (!gameManagerScript.GameOver)
            {
                if (!cross.activeSelf && !circle.activeSelf)
                {
                    string marker = tictactoeOnLoadScript.marker;

                    string name = gameObject.name;

                    ToggleTileClick(name, marker);
                    gameManagerScript.ChangePlayerRaiseEvent(!gameManagerScript.PlayerOneTurn);

                }
                else
                {
                    Debug.Log("Tile already selected!");
                }

            }
            else
            {
                Debug.Log("Game Over!");
            }

        }
        else
        {
            Debug.Log("Not Your Turn!");
        }



    }
    



}

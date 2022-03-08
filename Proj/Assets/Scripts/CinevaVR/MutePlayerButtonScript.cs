using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Photon.Pun;
using Photon.Realtime;
using ExitGames.Client.Photon;
using Photon.Voice;
using Photon.Chat;
using Photon.Voice.PUN;
using Photon.Voice.Unity;

public class MutePlayerButtonScript : MonoBehaviour
{
    bool isPressed = false;
    Color oldColor;

    public const byte MUTE_EVENT = 4;

    void Start()
    {
        oldColor = gameObject.GetComponent<Renderer>().material.color;
       
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
        if (obj.Code == MUTE_EVENT)
        {

            object[] datas = (object[])obj.CustomData;
            string myID = (string)datas[0];
            string OtherID = (string)datas[1];
            bool toSend = (bool)datas[2];

            if (myID == PhotonNetwork.NickName)
            {
                foreach (GameObject PlayerClone in GameObject.FindGameObjectsWithTag("Player"))
                {
                    PhotonView playerView = PlayerClone.GetComponent<PhotonView>();
                    string playerID = playerView.Owner.NickName;
                    if (playerID == OtherID)
                    {
                        PlayerClone.GetComponent<PhotonVoiceView>().enabled = toSend;
                        PlayerClone.GetComponent<AudioSource>().enabled = toSend;
                        PlayerClone.GetComponent<Recorder>().enabled = toSend;
                        PlayerClone.GetComponent<Speaker>().enabled = toSend;

                    }
                }
            }else if (OtherID == PhotonNetwork.NickName)
            {
                foreach (GameObject PlayerClone in GameObject.FindGameObjectsWithTag("Player"))
                {
                    PhotonView playerView = PlayerClone.GetComponent<PhotonView>();
                    string playerID = playerView.Owner.NickName;
                    if (playerID == myID)
                    {
                        PlayerClone.GetComponent<PhotonVoiceView>().enabled = toSend;
                        PlayerClone.GetComponent<AudioSource>().enabled = toSend;
                        PlayerClone.GetComponent<Recorder>().enabled = toSend;
                        PlayerClone.GetComponent<Speaker>().enabled = toSend;

                    }
                }
            }

        }
    }

    void MutePlayer(string myID,string OtherID, bool toSend)
    {
        object[] datas = new object[] { myID, OtherID, toSend };
        RaiseEventOptions raiseEventOptions = new RaiseEventOptions { Receivers = ReceiverGroup.All };
        PhotonNetwork.RaiseEvent(MUTE_EVENT, datas, raiseEventOptions, SendOptions.SendUnreliable);
    }


    public void OnMuteClick()
    {
        ChangeColor();
        bool toSend = false;
        if (isPressed)
        {
            toSend = false;
        }
        else
        {
            toSend = true;
        }
        GameObject prefabParent = gameObject.transform.parent.gameObject;
        GameObject viewText = prefabParent.transform.GetChild(0).gameObject;
        string OtherUserIDNetwork = viewText.GetComponent<Text>().text;
        string MyIDNetwork = PhotonNetwork.NickName;
        MutePlayer(OtherUserIDNetwork, MyIDNetwork,toSend);
    }


    public void ChangeColor()
    {
        if (isPressed)
        {
            gameObject.GetComponent<Renderer>().material.color = oldColor;
            isPressed = false;
        }
        else
        {
            gameObject.GetComponent<Renderer>().material.color = new Color(255, 0, 0);
            isPressed = true;
        }

    }


}

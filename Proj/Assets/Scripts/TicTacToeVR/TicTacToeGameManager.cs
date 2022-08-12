
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

public class TicTacToeGameManager : MonoBehaviour
{
    public const byte CHANGE_PLAYER = 9;


    public GameObject PlayerOneInner;
    public GameObject PlayerTwoInner;
    public TMP_Text PlayerOneText;
    public TMP_Text PlayerTwoText;
    public TMP_Text ReadyButtonText;
    public TMP_Text WinnerText;
    public GameObject WinnerBoard;



    public string playerOneUsername;
    public string playerTwoUsername;

    public string playerOneId;
    public string playerTwoId;

    public bool playerOneReady=false;
    public bool playerTwoReady=false;

    public bool AllowPlay;
    public bool PlayerOneTurn;
    public string PlayerTurnID;
    public bool GameOver;
    public bool PlayerOneWon;
    public bool PlayerTwoWon;
    public bool Tie;

    


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
        if (obj.Code == CHANGE_PLAYER)
        {

            object[] datas = (object[])obj.CustomData;
            bool pone = (bool)datas[0];


            checkIfPlayerWon();

            if (!GameOver)
            {
                checkIfTie();
            }
            Debug.Log("Game Over ?      : " + GameOver);
            Debug.Log("Player One Won ? : " + PlayerOneWon);
            Debug.Log("Player Two Won ? : " + PlayerTwoWon);
            if (!GameOver)
            {
                ReadyButtonText.GetComponent<TextMeshProUGUI>().text = "In Progress";
                PlayerOneTurn = pone;
                if (pone)
                {
                    PlayerOneInner.SetActive(true);
                    PlayerTwoInner.SetActive(false);
                    PlayerTurnID = playerOneId;
                }
                else
                {
                    PlayerOneInner.SetActive(false);
                    PlayerTwoInner.SetActive(true);
                    PlayerTurnID = playerTwoId;
                }
            }
            else
            {
                
                if (PlayerOneWon)
                {
                    ReadyButtonText.GetComponent<TextMeshProUGUI>().text = "Play Again?";
                    PlayerOneText.GetComponent<TextMeshProUGUI>().text = playerOneUsername + " - WON";
                    PlayerTwoText.GetComponent<TextMeshProUGUI>().text = playerTwoUsername + " - LOST";
                    WinnerBoard.SetActive(true);
                    WinnerText.GetComponent<TextMeshProUGUI>().text = "Congratulations!!\n" + playerOneUsername + "\nWON!";
                }
                else if (PlayerTwoWon)
                {
                    ReadyButtonText.GetComponent<TextMeshProUGUI>().text = "Play Again?";
                    PlayerOneText.GetComponent<TextMeshProUGUI>().text = playerOneUsername + " - LOST";
                    PlayerTwoText.GetComponent<TextMeshProUGUI>().text = playerTwoUsername + " - WON";
                    WinnerBoard.SetActive(true);
                    WinnerText.GetComponent<TextMeshProUGUI>().text = "Congratulations!!\n" + playerTwoUsername + "\nWON!";
                }
                else
                {
                    ReadyButtonText.GetComponent<TextMeshProUGUI>().text = "Play Again?";
                    PlayerOneText.GetComponent<TextMeshProUGUI>().text = playerOneUsername + " - TIE";
                    PlayerTwoText.GetComponent<TextMeshProUGUI>().text = playerTwoUsername + " - TIE";
                    WinnerBoard.SetActive(true);
                    WinnerText.GetComponent<TextMeshProUGUI>().text = "It's a tie :()";
                }
                playerOneReady = false;
                playerTwoReady = false;
                AllowPlay = false;
                PlayerOneWon = false;
                PlayerTwoWon = false;
                PlayerOneTurn = false;
                PlayerTurnID = "";
                clearTicTacToeBoard();

            }
            
                


        }
    }


    public void setUserNotRead()
    {
        ReadyButtonText.GetComponent<TextMeshProUGUI>().text = "Ready";
        PlayerOneText.GetComponent<TextMeshProUGUI>().text = playerOneUsername + " -NotReady";
        PlayerTwoText.GetComponent<TextMeshProUGUI>().text = playerTwoUsername + " -NotReady"; ;

    }

    public void ChangePlayerRaiseEvent(bool pone)
    {

        object[] datas = new object[] { pone };
        RaiseEventOptions raiseEventOptions = new RaiseEventOptions { Receivers = ReceiverGroup.All };
        PhotonNetwork.RaiseEvent(CHANGE_PLAYER, datas, raiseEventOptions, SendOptions.SendUnreliable);

    }

    public void checkIfTie()
    {
        GameObject tile1 = GameObject.Find("tile1").gameObject;
        GameObject tile2 = GameObject.Find("tile2").gameObject;
        GameObject tile3 = GameObject.Find("tile3").gameObject;
        GameObject tile4 = GameObject.Find("tile4").gameObject;
        GameObject tile5 = GameObject.Find("tile5").gameObject;
        GameObject tile6 = GameObject.Find("tile6").gameObject;
        GameObject tile7 = GameObject.Find("tile7").gameObject;
        GameObject tile8 = GameObject.Find("tile8").gameObject;
        GameObject tile9 = GameObject.Find("tile9").gameObject;

        var count = 0;
        var t1x = tile1.transform.GetChild(0).gameObject.activeSelf;
        var t1o = tile1.transform.GetChild(1).gameObject.activeSelf;
        if (t1x || t1o)
        {
            count += 1;
        }

        var t2x = tile2.transform.GetChild(0).gameObject.activeSelf;
        var t2o = tile2.transform.GetChild(1).gameObject.activeSelf;
        if (t2x || t2o)
        {
            count += 1;
        }


        var t3x = tile3.transform.GetChild(0).gameObject.activeSelf;
        var t3o = tile3.transform.GetChild(1).gameObject.activeSelf;
        if (t3x || t3o)
        {
            count += 1;
        }

        var t4x = tile4.transform.GetChild(0).gameObject.activeSelf;
        var t4o = tile4.transform.GetChild(1).gameObject.activeSelf;
        if (t4x || t4o)
        {
            count += 1;
        }

        var t5x = tile5.transform.GetChild(0).gameObject.activeSelf;
        var t5o = tile5.transform.GetChild(1).gameObject.activeSelf;
        if (t5x || t5o)
        {
            count += 1;
        }


        var t6x = tile6.transform.GetChild(0).gameObject.activeSelf;
        var t6o = tile6.transform.GetChild(1).gameObject.activeSelf;
        if (t6x || t6o)
        {
            count += 1;
        }

        var t7x = tile7.transform.GetChild(0).gameObject.activeSelf;
        var t7o = tile7.transform.GetChild(1).gameObject.activeSelf;
        if (t7x || t7o)
        {
            count += 1;
        }

        var t8x = tile8.transform.GetChild(0).gameObject.activeSelf;
        var t8o = tile8.transform.GetChild(1).gameObject.activeSelf;
        if (t8x || t8o)
        {
            count += 1;
        }

        var t9x = tile9.transform.GetChild(0).gameObject.activeSelf;
        var t9o = tile9.transform.GetChild(1).gameObject.activeSelf;
        if (t9x || t9o)
        {
            count += 1;
        }
        if (count >= 9)
        {
            GameOver = true;
        }







    }

    public void clearTicTacToeBoard()
    {
        GameObject tile1 = GameObject.Find("tile1").gameObject;
        GameObject tile2 = GameObject.Find("tile2").gameObject;
        GameObject tile3 = GameObject.Find("tile3").gameObject;
        GameObject tile4 = GameObject.Find("tile4").gameObject;
        GameObject tile5 = GameObject.Find("tile5").gameObject;
        GameObject tile6 = GameObject.Find("tile6").gameObject;
        GameObject tile7 = GameObject.Find("tile7").gameObject;
        GameObject tile8 = GameObject.Find("tile8").gameObject;
        GameObject tile9 = GameObject.Find("tile9").gameObject;
        tile1.transform.GetChild(0).gameObject.SetActive(false);
        tile1.transform.GetChild(1).gameObject.SetActive(false);
        
        tile2.transform.GetChild(0).gameObject.SetActive(false);
        tile2.transform.GetChild(1).gameObject.SetActive(false);
        
        tile3.transform.GetChild(0).gameObject.SetActive(false);
        tile3.transform.GetChild(1).gameObject.SetActive(false);
        
        tile4.transform.GetChild(0).gameObject.SetActive(false);
        tile4.transform.GetChild(1).gameObject.SetActive(false);
        
        tile5.transform.GetChild(0).gameObject.SetActive(false);
        tile5.transform.GetChild(1).gameObject.SetActive(false);
        
        tile6.transform.GetChild(0).gameObject.SetActive(false);
        tile6.transform.GetChild(1).gameObject.SetActive(false);
        
        tile7.transform.GetChild(0).gameObject.SetActive(false);
        tile7.transform.GetChild(1).gameObject.SetActive(false);
        
        tile8.transform.GetChild(0).gameObject.SetActive(false);
        tile8.transform.GetChild(1).gameObject.SetActive(false);
        
        tile9.transform.GetChild(0).gameObject.SetActive(false);
        tile9.transform.GetChild(1).gameObject.SetActive(false);


    }
    public void checkIfPlayerWon()
    {
        GameObject tile1 = GameObject.Find("tile1").gameObject;
        GameObject tile2 = GameObject.Find("tile2").gameObject;
        GameObject tile3 = GameObject.Find("tile3").gameObject;
        GameObject tile4 = GameObject.Find("tile4").gameObject;
        GameObject tile5 = GameObject.Find("tile5").gameObject;
        GameObject tile6 = GameObject.Find("tile6").gameObject;
        GameObject tile7 = GameObject.Find("tile7").gameObject;
        GameObject tile8 = GameObject.Find("tile8").gameObject;
        GameObject tile9 = GameObject.Find("tile9").gameObject;

        //cross = gameObject.transform.GetChild(0).gameObject;
        //circle = gameObject.transform.GetChild(1).gameObject;
        if (PlayerOneTurn)
        {
            //Testing if player one won- testing for cross! 


            if (tile1.transform.GetChild(0).gameObject.activeSelf && tile4.transform.GetChild(0).gameObject.activeSelf && tile7.transform.GetChild(0).gameObject.activeSelf)
            {
                PlayerOneWon = true;
            }else if (tile1.transform.GetChild(0).gameObject.activeSelf && tile2.transform.GetChild(0).gameObject.activeSelf && tile3.transform.GetChild(0).gameObject.activeSelf)
            {
                PlayerOneWon = true;
            }else if (tile1.transform.GetChild(0).gameObject.activeSelf && tile5.transform.GetChild(0).gameObject.activeSelf && tile9.transform.GetChild(0).gameObject.activeSelf)
            {
                PlayerOneWon = true;
            }
            else if (tile4.transform.GetChild(0).gameObject.activeSelf && tile5.transform.GetChild(0).gameObject.activeSelf && tile6.transform.GetChild(0).gameObject.activeSelf)
            {
                PlayerOneWon = true;
            }else if (tile7.transform.GetChild(0).gameObject.activeSelf && tile8.transform.GetChild(0).gameObject.activeSelf && tile9.transform.GetChild(0).gameObject.activeSelf)
            {
                PlayerOneWon = true;
            }else if (tile2.transform.GetChild(0).gameObject.activeSelf && tile5.transform.GetChild(0).gameObject.activeSelf && tile8.transform.GetChild(0).gameObject.activeSelf)
            {
                PlayerOneWon = true;
            }else if (tile3.transform.GetChild(0).gameObject.activeSelf && tile6.transform.GetChild(0).gameObject.activeSelf && tile9.transform.GetChild(0).gameObject.activeSelf)
            {
                PlayerOneWon = true;
            }else if (tile3.transform.GetChild(0).gameObject.activeSelf && tile5.transform.GetChild(0).gameObject.activeSelf && tile7.transform.GetChild(0).gameObject.activeSelf)
            {
                PlayerOneWon = true;
            }
            if (PlayerOneWon)
            {
                GameOver = true;
            }

        }
        else
        {
            //Testing if player two won- testing for circle!
            if (tile1.transform.GetChild(1).gameObject.activeSelf && tile4.transform.GetChild(1).gameObject.activeSelf && tile7.transform.GetChild(1).gameObject.activeSelf)
            {
                PlayerTwoWon = true;
            }
            else if (tile1.transform.GetChild(1).gameObject.activeSelf && tile2.transform.GetChild(1).gameObject.activeSelf && tile3.transform.GetChild(1).gameObject.activeSelf)
            {
                PlayerTwoWon = true;
            }
            else if (tile1.transform.GetChild(1).gameObject.activeSelf && tile5.transform.GetChild(1).gameObject.activeSelf && tile9.transform.GetChild(1).gameObject.activeSelf)
            {
                PlayerTwoWon = true;
            }
            else if (tile4.transform.GetChild(1).gameObject.activeSelf && tile5.transform.GetChild(1).gameObject.activeSelf && tile6.transform.GetChild(1).gameObject.activeSelf)
            {
                PlayerTwoWon = true;
            }
            else if (tile7.transform.GetChild(1).gameObject.activeSelf && tile8.transform.GetChild(1).gameObject.activeSelf && tile9.transform.GetChild(1).gameObject.activeSelf)
            {
                PlayerTwoWon = true;
            }
            else if (tile2.transform.GetChild(1).gameObject.activeSelf && tile5.transform.GetChild(1).gameObject.activeSelf && tile8.transform.GetChild(1).gameObject.activeSelf)
            {
                PlayerTwoWon = true;
            }
            else if (tile3.transform.GetChild(1).gameObject.activeSelf && tile6.transform.GetChild(1).gameObject.activeSelf && tile9.transform.GetChild(1).gameObject.activeSelf)
            {
                PlayerTwoWon = true;
            }
            else if (tile3.transform.GetChild(1).gameObject.activeSelf && tile5.transform.GetChild(1).gameObject.activeSelf && tile7.transform.GetChild(1).gameObject.activeSelf)
            {
                PlayerTwoWon = true;
            }
            if (PlayerTwoWon)
            {
                GameOver = true;
            }



        }
    }



    public void checkIfBothStarted()
    {
        if (playerOneReady && playerTwoReady)
        {
            WinnerBoard.SetActive(false);
            Debug.Log("When both player ready then : ");
            AllowPlay = true;
            GameOver = false;
            Debug.Log("Game Over ? : "+GameOver);

            System.Random rnd = new System.Random();
            int num = rnd.Next(2);
            if (num == 0)
            {
                PlayerOneTurn = true;
            }
            else
            {
                PlayerOneTurn = false;
            }
            SetMarkerAroundPlayer();
        }
        else
        {
            AllowPlay = false;
        }
    }

    public void SetMarkerAroundPlayer()
    {
        ChangePlayerRaiseEvent(PlayerOneTurn);
    }

    public void SetPlayerOneReady()
    {
        GameOver = false;
        Debug.Log("Setting Player One Ready");
        playerOneReady = true;
        PlayerOneText.GetComponent<TextMeshProUGUI>().text = playerOneUsername + " - X";
        checkIfBothStarted();
    }


    public void SetPlayerTwoReady()
    {
        GameOver = false;
        playerTwoReady = true;
        PlayerTwoText.GetComponent<TextMeshProUGUI>().text = playerTwoUsername + " - O";
        checkIfBothStarted();
    }


    public void ReadyButtonClick(string userId)
    {
        Debug.Log("Setting Player One Ready-ready click");
        Debug.Log("User Id recieved : " + userId);
        Debug.Log("Player One Id : " + playerOneId);
        Debug.Log("Player Two Id : " + playerTwoId);

        if (userId == playerOneId)
        {
            SetPlayerOneReady();
        }
        else
        {
            SetPlayerTwoReady();
        }
    }

}

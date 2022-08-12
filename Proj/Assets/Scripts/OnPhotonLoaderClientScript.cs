using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class OnPhotonLoaderClientScript : MonoBehaviour
{
    public GameObject OnLoadPhotonObject;
    OnLoadPunManagerScript OnLoadPunScript;

    bool IsInRoom = false;
    bool IsInLobby = false;
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        if (OnLoadPunScript.CheckPunConnected())
        {
            if (OnLoadPunScript.CheckLobbyConnected())
            {
                Debug.Log("HErerere");

                OnLoadPunScript.JoinRoom(OnLoadPunScript.RoomID);

                

            }
        }


    }

    private void OnEnable()
    {
        OnLoadPunScript = OnLoadPhotonObject.GetComponent<OnLoadPunManagerScript>();


        if (OnLoadPunScript.CheckRoomConnected())
        {
            OnLoadPunScript.ConnectToScene();
        }
        else
        {
            OnLoadPunScript.ConnectToPun();
            

        }
    }


    


}

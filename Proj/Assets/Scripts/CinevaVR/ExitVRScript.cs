using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using Photon;
using Photon.Pun;

using UnityEngine.XR;
public class ExitVRScript : MonoBehaviourPunCallbacks
{
    public string SceneName;
    
    
    private void OnEnable()
    {
        

    }

    public void OnCinemaVrButtonClick()
    {

        RemoveNetworkPrefabVar();
        StartCoroutine(LeaveRoomClick());
        
    }

    public void RemoveNetworkPrefabVar()
    {

        var obj = GameObject.Find("__app");
        var objScript = obj.GetComponent<PreLoadTestPhotonObjects>();
        objScript.myNetworkPrefab = false;
    }

    IEnumerator LeaveRoomClick()
    {
        PhotonNetwork.LeaveRoom();
        while (PhotonNetwork.InRoom)
        {
            yield return null;
        }
        SceneManager.UnloadScene(SceneName);
        SceneManager.LoadScene("2DApp");

    }
}

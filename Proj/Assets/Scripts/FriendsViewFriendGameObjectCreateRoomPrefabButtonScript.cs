using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.UI;
public class FriendsViewFriendGameObjectCreateRoomPrefabButtonScript : MonoBehaviour
{
    public TMP_Text text;
    public TMP_Text userId;
    GameObject OnLoadObject;
    OnLoadCanvasVrCreateRoomScript onLoadScript;




    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void OnInviteClick()
    {
        OnLoadObject = gameObject.transform.parent.transform.parent.transform.parent.transform.parent.transform.parent.transform.parent.transform.parent.gameObject;
        OnLoadObject = OnLoadObject.transform.Find("OnLoadVrCreateRoom").gameObject; 
        Debug.Log(OnLoadObject.name);
        text.text = "Invited";
        gameObject.SetActive(false);
        onLoadScript = OnLoadObject.GetComponent<OnLoadCanvasVrCreateRoomScript>();
        onLoadScript.AddToUsersInvited(userId.text);



    }



}

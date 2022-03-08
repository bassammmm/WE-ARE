using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Collections;


public class OnLoadCanvasVrCreateRoomScript : MonoBehaviour
{
    public ArrayList usersInvited;
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
        usersInvited = new ArrayList(); // recommended 

    }



    public void AddToUsersInvited(string user_id)
    {
        usersInvited.Add(user_id);
        Debug.Log("Number of users invited : "+usersInvited.Count);
    }

}

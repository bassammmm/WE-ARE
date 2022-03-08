using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FriendsPageTabScript : MonoBehaviour
{

    public GameObject AddFriendPanel;
    public GameObject MyFriendsPanel;
    public GameObject NotificationsPanel;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }



    public void AddFriendTabClick()
    {
        AddFriendPanel.SetActive(true);
        MyFriendsPanel.SetActive(false);
        NotificationsPanel.SetActive(false);
    }


    public void MyFriendTabClick()
    {
        AddFriendPanel.SetActive(false);
        MyFriendsPanel.SetActive(true);
        NotificationsPanel.SetActive(false);

    }

    public void NotificationsTabClick()
    {
        AddFriendPanel.SetActive(false);
        MyFriendsPanel.SetActive(false);
        NotificationsPanel.SetActive(true);

    }

}

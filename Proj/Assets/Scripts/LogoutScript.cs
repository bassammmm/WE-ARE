using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Firebase.Auth;
public class LogoutScript : MonoBehaviour
{
 
    public void OnLogoutClick()
    {
        FirebaseAuth.DefaultInstance.SignOut();
    }
}

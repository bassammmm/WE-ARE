using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Firebase;
using Firebase.Auth;
using TMPro;


public class AuthManagerScript : MonoBehaviour
{
    public DependencyStatus dependancyStatus;
    public FirebaseAuth auth;
    public FirebaseUser user;


    private void Awake()
    {

        FirebaseApp.CheckAndFixDependenciesAsync().ContinueWith(task =>
        {
            dependancyStatus = task.Result;

            if (dependancyStatus == DependencyStatus.Available)
            {
                InitializeFirebase();
            }
            else
            {
                Debug.LogError("Could not resolve all Firebase Dependencies : " + dependancyStatus);
            }



        });
    }


    private void InitializeFirebase()
    {
        Debug.Log("Setting up Firebase Auth");
        auth = FirebaseAuth.DefaultInstance;
    }


}
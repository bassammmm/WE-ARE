using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using Firebase;
using Firebase.Auth;

public class LoginPageSignInScript : MonoBehaviour
{
    public GameObject username;
    public GameObject password;

    public GameObject ProfileCanvas;
    public GameObject RegisterCanvas;
    public GameObject LoginCanvas;

    public GameObject ErrorMessage;

    CanvasManagerPublicScript canvasManager;
    OnLoadNotificationsManagerScript OnLoadNotificationHandlerScript;

    private Coroutine _SignInUser;


    private void OnEnable()
    {
        canvasManager = GameObject.Find("CanvasManager").gameObject.GetComponent<CanvasManagerPublicScript>();
        OnLoadNotificationHandlerScript = GameObject.Find("OnLoadNotificationsManager").gameObject.GetComponent<OnLoadNotificationsManagerScript>();
    }



    public void OnButtonClick()
    {
        string usernameText = username.GetComponent<TMP_InputField>().text;
        string passwordText = password.GetComponent<TMP_InputField>().text;

        if(string.IsNullOrEmpty(usernameText)!=true && string.IsNullOrEmpty(passwordText) != true)
        {
            _SignInUser = StartCoroutine(SignInUser(usernameText,passwordText));
        }
        else
        {
            ErrorMessage.SetActive(true);
        }


    }

    IEnumerator SignInUser(string usernameText,string passwordText)
    {
        var auth = FirebaseAuth.DefaultInstance;
        
        var loginTask = auth.SignInWithEmailAndPasswordAsync(usernameText, passwordText);

        yield return new WaitUntil(() => loginTask.IsCompleted);


        if (loginTask.Exception!=null)
        {
            ErrorMessage.SetActive(true);
            Debug.Log($"An error occured while logging in ! {loginTask.Exception}");
        }
        else
        {
            Debug.Log("Login succeeded!");
            OnLoadNotificationHandlerScript.EnableMethodFunc();
            canvasManager.canvasChange(LoginCanvas, ProfileCanvas);

        }

        yield return null;
    }

}

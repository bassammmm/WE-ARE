using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using Firebase;
using Firebase.Auth;
using Firebase.Firestore;
public class RegisterPageRegisterScript : MonoBehaviour
{
    public GameObject fname;
    public GameObject lname;
    public GameObject uname;
    public GameObject email;
    public GameObject passw;
    public GameObject cpass;

    public GameObject RegisterCanvas;
    public GameObject LoginCanvas;

    public GameObject ErrorMessage;


    CanvasManagerPublicScript canvasManager;
    private Coroutine _RegistrationCoroutine;




    private void OnEnable()
    {
        canvasManager = GameObject.Find("CanvasManager").gameObject.GetComponent<CanvasManagerPublicScript>();

    }




    public void OnRegisterButtonClick()
    {
        string fnameText = fname.GetComponent<TMP_InputField>().text;
        string lnameText = lname.GetComponent<TMP_InputField>().text;
        string unameText = uname.GetComponent<TMP_InputField>().text;
        string emailText = email.GetComponent<TMP_InputField>().text;
        string passwordText = passw.GetComponent<TMP_InputField>().text;
        string cpassText = cpass.GetComponent<TMP_InputField>().text;

        var CharacterData = new CharacterStruct
        {
            FirstName = fnameText,
            LastName = lnameText,
            UserName = unameText
        };


        if (string.IsNullOrEmpty(emailText) != true && string.IsNullOrEmpty(passwordText) != true)
        {
            _RegistrationCoroutine = StartCoroutine(RegisterUser(emailText, passwordText,CharacterData));
            
        }
        else
        {
            ErrorMessage.SetActive(true);
            Debug.Log("Information is incomplete, please fill all the required fields.");
        }

    }

    private IEnumerator RegisterUser(string email, string password, CharacterStruct charaterData)
    {
        var auth = FirebaseAuth.DefaultInstance;
        var registerTask = auth.CreateUserWithEmailAndPasswordAsync(email, password);
        yield return new WaitUntil(() => registerTask.IsCompleted);

        if (registerTask.Exception != null)
        {
            ErrorMessage.SetActive(true);
            Debug.Log($"An error occured while registration! {registerTask.Exception}");
        }
        else
        {
            Debug.Log("Registration Succesful!");
            UploadUserData(charaterData);
            canvasManager.canvasChange(RegisterCanvas, LoginCanvas);

        }
        _RegistrationCoroutine = null;

    }


    private void UploadUserData(CharacterStruct charaterData)
    {
        var auth = FirebaseAuth.DefaultInstance;
        string uid = auth.CurrentUser.UserId;
        var firestore = FirebaseFirestore.DefaultInstance;
        var task = firestore.Collection("users").Document(uid).SetAsync(charaterData);
        if (task.Exception != null)
        {
            ErrorMessage.SetActive(true);
            Debug.Log($"Firestore data upload error {task.Exception}");
        }
        else
        {
            Debug.Log("Firestore data uploaded successfully!");
        }
    }

}

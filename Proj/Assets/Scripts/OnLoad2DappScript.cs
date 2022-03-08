using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR;
using Firebase;
using Firebase.Auth;
using Firebase.Firestore;
using Firebase.Extensions;
using Firebase.Storage;
public class OnLoad2DappScript : MonoBehaviour
{

    public GameObject LoginCanvas;
    public GameObject RegisterCanvas;
    public GameObject ProfileCanvas;
    public GameObject FriendsCanvas;
    public GameObject VRCanvas;
    public GameObject AvatarEditCanvas;
    public GameObject CreateRoomCanvas;
    public GameObject NotificationsCanvas;

    // Start is called before the first frame update
    void Start()
    {


        ConvertTo2DFunc();
        LoadCanvas();
    }


    public void LoadCanvas()
    {
        bool error = false;
        try
        {

            var user = FirebaseAuth.DefaultInstance.CurrentUser;
            
            var email = user.Email;
        }
        catch 
        {
            
            error = true;
        }


        
        if (!error)
        {
            
            
            LoginCanvas.SetActive(false);
            
            
            RegisterCanvas.SetActive(false);
            
            ProfileCanvas.SetActive(false);

            AvatarEditCanvas.SetActive(false);

            FriendsCanvas.SetActive(false);
            CreateRoomCanvas.SetActive(false);
            NotificationsCanvas.SetActive(false);


            VRCanvas.SetActive(true);
        }
        else
        {

            LoginCanvas.SetActive(true);


            RegisterCanvas.SetActive(false);

            ProfileCanvas.SetActive(false);

            AvatarEditCanvas.SetActive(false);

            FriendsCanvas.SetActive(false);

            CreateRoomCanvas.SetActive(false);
            NotificationsCanvas.SetActive(false);
            VRCanvas.SetActive(false);
        }



    }


    // Update is called once per frame
    void Update()
    {
        
    }

    public void ConvertTo2DFunc()
    {
        StartCoroutine(SwitchTo2D());
    }


    IEnumerator SwitchTo2D()
    {
        // Empty string loads the "None" device.
        XRSettings.LoadDeviceByName("");

        // Must wait one frame after calling `XRSettings.LoadDeviceByName()`.
        yield return null;

        // Not needed, since loading the None (`""`) device takes care of this.
        // XRSettings.enabled = false;

        // Restore 2D camera settings.
        ResetCameras();
    }

    // Resets camera transform and settings on all enabled eye cameras.
    void ResetCameras()
    {
        // Camera looping logic copied from GvrEditorEmulator.cs
        for (int i = 0; i < Camera.allCameras.Length; i++)
        {
            Camera cam = Camera.allCameras[i];
            if (cam.enabled && cam.stereoTargetEye != StereoTargetEyeMask.None)
            {

                // Reset local position.
                // Only required if you change the camera's local position while in 2D mode.
                cam.transform.localPosition = Vector3.zero;

                // Reset local rotation.
                // Only required if you change the camera's local rotation while in 2D mode.
                cam.transform.localRotation = Quaternion.identity;

                // No longer needed, see issue github.com/googlevr/gvr-unity-sdk/issues/628.
                // cam.ResetAspect();

                // No need to reset `fieldOfView`, since it's reset automatically.
            }
        }
    }
}

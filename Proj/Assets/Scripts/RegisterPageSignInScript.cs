using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RegisterPageSignInScript : MonoBehaviour
{

    public GameObject MyParentCanvas;
    public GameObject NextCanvas;

    CanvasManagerPublicScript canvasManager;


    private void OnEnable()
    {
        canvasManager = GameObject.Find("CanvasManager").gameObject.GetComponent<CanvasManagerPublicScript>();

    }

    public void OnSignInButtonClick()
    {
        canvasManager.canvasChange(MyParentCanvas, NextCanvas);
    }
}

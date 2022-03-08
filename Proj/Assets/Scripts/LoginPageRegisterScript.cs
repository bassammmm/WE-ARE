using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LoginPageRegisterScript : MonoBehaviour
{

    public GameObject MyParentCanvas;
    public GameObject NextCanvas;

    CanvasManagerPublicScript canvasManager;
    

    
        
    private void OnEnable()
    {
        canvasManager = GameObject.Find("CanvasManager").gameObject.GetComponent<CanvasManagerPublicScript>();

    }


    public void OnButtonClick()
    {

        canvasManager.canvasChange(MyParentCanvas, NextCanvas);
    }


}

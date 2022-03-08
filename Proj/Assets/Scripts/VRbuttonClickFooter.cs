using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VRbuttonClickFooter : MonoBehaviour
{
    public GameObject MyCanvas;
    public GameObject VRCanvas;
    CanvasManagerPublicScript canvasManager = new CanvasManagerPublicScript();
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    public void OnVrButtonClick()
    {
        canvasManager.canvasChange(MyCanvas, VRCanvas);
    }

}

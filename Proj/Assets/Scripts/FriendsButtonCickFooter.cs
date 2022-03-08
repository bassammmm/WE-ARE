using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FriendsButtonCickFooter : MonoBehaviour
{

    public GameObject MyCanvas;
    public GameObject FriendsCanvas;
    CanvasManagerPublicScript canvasManager = new CanvasManagerPublicScript();
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    public void OnFriendsClick()
    {
        canvasManager.canvasChange(MyCanvas, FriendsCanvas);
    }

}

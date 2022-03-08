using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ProfilePageFriendsButtonScript : MonoBehaviour
{

    public GameObject ProfileCanvas;
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



    public void OnFriendsButtonClick()
    {
        canvasManager.canvasChange(ProfileCanvas, FriendsCanvas);
    }

}

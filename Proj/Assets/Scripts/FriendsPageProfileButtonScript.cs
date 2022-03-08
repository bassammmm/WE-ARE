using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FriendsPageProfileButtonScript : MonoBehaviour
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



    public void OnProfileButtonClick()
    {
        canvasManager.canvasChange(FriendsCanvas, ProfileCanvas);
    }
}

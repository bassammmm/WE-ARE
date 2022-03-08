using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangeCanvasScript : MonoBehaviour
{
    // Start is called before the first frame update
    public GameObject MyCanvas;
    public GameObject FriendsCanvas;
    CanvasManagerPublicScript canvasManager;
    // Start is called before the first frame update


    private void OnEnable()
    {
        canvasManager = GameObject.Find("CanvasManager").gameObject.GetComponent<CanvasManagerPublicScript>();
    }
    public void OnChangeClick()
    {
        canvasManager.canvasChange(MyCanvas, FriendsCanvas);
    }
}

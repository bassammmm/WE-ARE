using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CinemaVrClickButtonScript : MonoBehaviour
{
    public GameObject MyCanvas;
    public GameObject FriendsCanvas;
    CanvasManagerPublicScript canvasManager;

    private void OnEnable()
    {
        canvasManager = GameObject.Find("CanvasManager").gameObject.GetComponent<CanvasManagerPublicScript>();

    }

    public void OnCinemaVrButtonClick()
    {
        //SceneManager.UnloadScene("2DApp");
        //SceneManager.LoadSceneAsync("CinemaVr");
        canvasManager.canvasChange(MyCanvas, FriendsCanvas);

    }


}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ExitVRScript : MonoBehaviour
{

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }


    public void OnCinemaVrButtonClick()
    {
        SceneManager.UnloadScene("CinemaVR");
        SceneManager.LoadScene("2DApp");
        
    }
}

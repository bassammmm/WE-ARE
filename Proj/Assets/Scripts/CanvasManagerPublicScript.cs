using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CanvasManagerPublicScript : MonoBehaviour
{





    private void Start()
    {


    }

    public void canvasChange(GameObject CanvasOne,GameObject CanvasTwo)
    {


        
        
        CanvasOne.SetActive(false);
        CanvasTwo.SetActive(true);

    }



}

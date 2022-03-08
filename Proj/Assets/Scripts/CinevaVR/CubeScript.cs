using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CubeScript : MonoBehaviour
{

    bool isPressed = false;
    public float rotSpeed;
    // Start is called before the first frame update
    public void Pressed()
    {
        isPressed = true;
    }
    public void Released()
    {
        isPressed = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (isPressed)
        {
            transform.Rotate(Vector3.up * rotSpeed * Time.deltaTime);
        }
    }
}

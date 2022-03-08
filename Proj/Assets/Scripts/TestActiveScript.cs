using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestActiveScript : MonoBehaviour
{

    public string name;
    // Start is called before the first frame update
    void Start()
    {
        Debug.Log(name + ": STARTTEDDD");
    }

    // Update is called once per frame
    void Update()
    {
        Debug.Log(name + ": Active");
    }
}

﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DontDestroyOnLoadScript : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        for (int i = 0; i < Object.FindObjectsOfType<DontDestroyOnLoadScript>().Length; i++)
        {
            if (Object.FindObjectsOfType<DontDestroyOnLoadScript>()[i] != this)
            {
                if (Object.FindObjectsOfType<DontDestroyOnLoadScript>()[i].name == gameObject.name)
                {
                    Destroy(gameObject);
                }
            }
        }
        DontDestroyOnLoad(gameObject);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}

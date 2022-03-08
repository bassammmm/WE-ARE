using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;

public class HeadScript : MonoBehaviour
{
    PhotonView view;
    void Start()
    {
        view = gameObject.GetComponent<PhotonView>();
    }


    void Update()
    {
        if (view.IsMine)
        {
            //Debug.Log(" Must change rotation man :/ ");
            //Debug.Log(" Camera : " + Camera.main.transform.rotation.ToString());
            transform.rotation = Camera.main.transform.rotation;
            //Debug.Log(" HEAD : " + transform.rotation.ToString());
        }


    }
}

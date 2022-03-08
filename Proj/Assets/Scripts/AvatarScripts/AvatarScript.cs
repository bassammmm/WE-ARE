using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
public class AvatarScript : MonoBehaviour
{

    public GameObject camera;
    public GameObject head;
    PhotonView view;
    // Start is called before the first frame update
    void Start()
    {
        view = gameObject.GetComponent<PhotonView>();
        if (!view.IsMine)
        {
            camera.GetComponent<Camera>().enabled = false;
            camera.GetComponent<AudioListener>().enabled = false;
            camera.GetComponent<GvrPointerPhysicsRaycaster>().enabled = false;
            camera.transform.Find("GvrReticlePointer").gameObject.SetActive(false);
        }
    }

    // Update is called once per frame
    void Update()
    {

        
    }


}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using Photon.Voice.Unity;

public class AudioAllowDisallow : MonoBehaviour
{
    public GameObject unMUTE;
    public GameObject mute;
    
    GameObject myAvatar;

    Speaker speaker;
    PhotonView myView;
    // Start is called before the first frame update


    private void OnEnable()
    {
        myAvatar = gameObject.transform.parent.gameObject;
        myView = myAvatar.GetComponent<PhotonView>();
        speaker = myAvatar.GetComponent<Speaker>();
    }

    public void onMuteClick()
    {
        if (myView.IsMine)
        {
            mute.SetActive(true);
            unMUTE.SetActive(false);
            speaker.enabled =false;
        }

    }

    public void onUnMuteClick()
    {
        if (myView.IsMine)
        {
            mute.SetActive(false);
            unMUTE.SetActive(true);
            speaker.enabled = true;
        }

    }

}

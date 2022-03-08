using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
public class ReactionsClickScript : MonoBehaviour
{



    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void ClapClick()
    {
        var Player = GameObject.FindGameObjectsWithTag("Player");

        foreach (var pl in Player)
        {
            var ViewPl = pl.GetComponent<PhotonView>();
            if (ViewPl.IsMine)
            {
                var AvatarPlayer = pl.gameObject.transform.GetChild(1);

                var AvatarPlayerScript = AvatarPlayer.GetComponent<AvatarReactionScript>();

                AvatarPlayerScript.Clap();
            }
        }
 
    }

    public void YellClick()
    {
        var Player = GameObject.FindGameObjectsWithTag("Player");

        foreach (var pl in Player)
        {
            var ViewPl = pl.GetComponent<PhotonView>();
            if (ViewPl.IsMine)
            {
                var AvatarPlayer = pl.gameObject.transform.GetChild(1);

                var AvatarPlayerScript = AvatarPlayer.GetComponent<AvatarReactionScript>();

                AvatarPlayerScript.Yell();
            }
        }
    }

    public void LaughClick()
    {
        var Player = GameObject.FindGameObjectsWithTag("Player");

        foreach (var pl in Player)
        {
            var ViewPl = pl.GetComponent<PhotonView>();
            if (ViewPl.IsMine)
            {
                var AvatarPlayer = pl.gameObject.transform.GetChild(1);

                var AvatarPlayerScript = AvatarPlayer.GetComponent<AvatarReactionScript>();

                AvatarPlayerScript.Laugh();
            }
        }
    }

    public void CheerClick()
    {
        var Player = GameObject.FindGameObjectsWithTag("Player");

        foreach (var pl in Player)
        {
            var ViewPl = pl.GetComponent<PhotonView>();
            if (ViewPl.IsMine)
            {
                var AvatarPlayer = pl.gameObject.transform.GetChild(1);

                var AvatarPlayerScript = AvatarPlayer.GetComponent<AvatarReactionScript>();

                AvatarPlayerScript.Cheer();
            }
        }
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
public class PlayerSeatMoveButton : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public float roundFloat(float num)
    {
        float dx = num;
        float snap = 0.5f;
        if (snap <= 1f)
            dx = Mathf.Floor(dx) + (Mathf.Round((dx - Mathf.Floor(dx)) * (1f / snap)) * snap);
        else
            dx = Mathf.Round(dx / snap) * snap;
        return dx;
    }

    public void MovePlayerLeft()
    {
        var Player = GameObject.FindGameObjectsWithTag("Player");

        foreach (var pl in Player)
        {
            var ViewPl = pl.GetComponent<PhotonView>();
            if (ViewPl.IsMine)
            {

                float xPost = (float)(pl.gameObject.transform.position.x - 0.5);
                if (xPost < -9.48)
                {
                    xPost= (float) 8.518;
                }
                bool posCorrect = false;
                int testCount = 0;
                while (!posCorrect & testCount < 36)
                {
                    bool Found = false;
                    foreach (var pll in Player)
                    {
                        if (pll != pl)
                        {

                            float testPLX = roundFloat(pll.gameObject.transform.position.x);
                            float testXpost = roundFloat(xPost);

                            if ( testPLX== testXpost)
                            {
                                Debug.Log("here after match");
                                xPost = (float)(xPost - 0.5);
                                if (xPost < -9.48)
                                {
                                    xPost = (float)8.518;
                                }
                                Found = true;
                                break;
                            }
                        }
                    }
                    if (Found)
                    {
                        posCorrect = false;
                    }
                    else
                    {
                        posCorrect = true;
                    }
                }
                float yPost = pl.gameObject.transform.position.y;
                float zPost = pl.gameObject.transform.position.z;


                pl.gameObject.transform.position = new Vector3(xPost, yPost, zPost);
            }
        }
    }


    public void MovePlayerRight()
    {
        var Player = GameObject.FindGameObjectsWithTag("Player");

        foreach (var pl in Player)
        {
            var ViewPl = pl.GetComponent<PhotonView>();
            if (ViewPl.IsMine)
            {

                float xPost = (float) (pl.gameObject.transform.position.x + 0.5);
                if (xPost >8.51)
                {
                    xPost = (float)-9.48;
                }
                bool posCorrect = false;
                int testCount = 0;
                while (!posCorrect & testCount<36)
                {
                    bool Found = false;
                    foreach (var pll in Player)
                    {
                        if (pll != pl)
                        {
                            float testPLX = roundFloat(pll.gameObject.transform.position.x);
                            float testXpost = roundFloat(xPost);

                            if (testPLX == testXpost)
                            {
                                Debug.Log("here after match");
                                xPost = (float)(xPost + 0.5);
                                if (xPost > 8.51)
                                {
                                    xPost = (float)-9.48;
                                }
                                Found = true;
                                break;
                            }
                        }
                    }
                    if (Found)
                    {
                        posCorrect = false;
                    }
                    else
                    {
                        posCorrect = true;
                    }
                }

                float yPost = pl.gameObject.transform.position.y;
                float zPost = pl.gameObject.transform.position.z;

                pl.gameObject.transform.position = new Vector3(xPost, yPost, zPost);


            }
        }
    }



}

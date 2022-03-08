using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
public class EditAvatarLoaderScript : MonoBehaviour
{

    public int IndexImage;

    // Start is called before the first frame update
    void Start()
    {
        
        IndexImage = 0;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void IncrementIndex()
    {
        if (IndexImage < 9)
        {
            IndexImage++;
        }
        
    }
    public void DecrementIndex()
    {
        if (IndexImage > 0)
        {
            IndexImage--;
        }
    }

}

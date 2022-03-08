using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AvatarReactionScript : MonoBehaviour
{

    Animator myAnimator;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnEnable()
    {
        myAnimator = gameObject.GetComponent<Animator>();
    }

    public void Clap()
    {
        myAnimator.SetTrigger("Clap");
    }

    public void Yell()
    {
        myAnimator.SetTrigger("Yell");
    }

    public void Laugh()
    {
        myAnimator.SetTrigger("Laugh");
    }

    public void Cheer()
    {
        myAnimator.SetTrigger("Cheer");
    }

}

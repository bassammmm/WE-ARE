using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DisableErrorMessage : MonoBehaviour
{


    public void onOkClick()
    {
        GameObject errorMessage = GameObject.Find("ErrorMessage");
        errorMessage.SetActive(false);
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameObjectUtil : MonoBehaviour
{
    public void ChangeActivateGameObject(GameObject gameObject)
    {
        gameObject.SetActive(!gameObject.activeSelf);
    }
}

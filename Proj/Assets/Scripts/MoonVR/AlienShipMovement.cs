using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
public class AlienShipMovement : MonoBehaviour
{
    // Start is called before the first frame update
    [SerializeField] private Vector3 target = new Vector3(1, 1, 1);
    [SerializeField] private Vector3 initial = new Vector3(1, 1, 1);
    [SerializeField] private float speed = 1;
    private void Update()
    {
        float diff = transform.position.x - target.x;
        // Moves the object to target position
        if (Math.Abs(diff)<10)
        {
            transform.position = initial;
        }

        transform.position = Vector3.MoveTowards(transform.position, target, Time.deltaTime * speed);
    }
}

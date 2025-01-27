﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR;
using Photon.Pun;
// Attach this controller to the main camera, or an appropriate
// ancestor thereof, such as the "player" game object.
public class PlayerMagicWindowScript : MonoBehaviour
{
    // Optional, allows user to drag left/right to rotate the world.
    private const float DRAG_RATE = .2f;
    float dragYawDegrees;
    PhotonView view;
    void Start()
    {
        view = gameObject.GetComponent<PhotonView>();
        // Make sure orientation sensor is enabled.
#if UNITY_ANDROID && !UNITY_EDITOR
 //code here
     Input.gyro.enabled = true;
#endif

    }

    void Update()
    {
#if UNITY_ANDROID && !UNITY_EDITOR
 //code here
     if (XRSettings.enabled)
        {
            // Unity takes care of updating camera transform in VR.
            return;
        }

        // android-developers.blogspot.com/2010/09/one-screen-turn-deserves-another.html
        // developer.android.com/guide/topics/sensors/sensors_overview.html#sensors-coords
        //
        //     y                                       x
        //     |  Gyro upright phone                   |  Gyro landscape left phone
        //     |                                       |
        //     |______ x                      y  ______|
        //     /                                       \
        //    /                                         \
        //   z                                           z
        //
        //
        //     y
        //     |  z   Unity
        //     | /
        //     |/_____ x
        //

        // Update `dragYawDegrees` based on user touch.
        CheckDrag();

        transform.localRotation =
            // Allow user to drag left/right to adjust direction they're facing.
            Quaternion.Euler(0f, -dragYawDegrees, 0f) *

            // Neutral position is phone held upright, not flat on a table.
            Quaternion.Euler(90f, 0f, 0f) *

            // Sensor reading, assuming default `Input.compensateSensors == true`.
            Input.gyro.attitude *

            // So image is not upside down.
            Quaternion.Euler(0f, 0f, 180f);

#endif

    }

    void CheckDrag()
    {
        if (Input.touchCount != 1)
        {
            return;
        }

        Touch touch = Input.GetTouch(0);
        if (touch.phase != TouchPhase.Moved)
        {
            return;
        }

        dragYawDegrees += touch.deltaPosition.x * DRAG_RATE;
    }
}
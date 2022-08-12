using System;
using UnityEngine;
using NexPlayerAPI;

public abstract class NexPlayerCommand : MonoBehaviour
{
    public abstract void Execute(NexPlayerBehaviour nexPlayer, Action action);
}


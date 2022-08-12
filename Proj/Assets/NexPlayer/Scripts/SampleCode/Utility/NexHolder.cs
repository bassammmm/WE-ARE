using UnityEngine;
using NexPlayerSample;

public class NexHolder : MonoBehaviour
{
    public string nexStoreURL;
    public NexPlayer player;
    public OfflineStreaming offDload;

    public void RunThisVideo()
    {
        player.StreamDownloadController.PlayOffline(nexStoreURL);
        offDload.CloseButtonMenu();
    }
}

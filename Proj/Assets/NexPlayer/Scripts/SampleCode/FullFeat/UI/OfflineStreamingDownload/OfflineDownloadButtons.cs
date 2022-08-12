using System.Collections;
using UnityEngine;
using UnityEngine.Android;

namespace NexPlayerSample
{
    public class OfflineDownloadButtons : MonoBehaviour
    {
        [SerializeField] NexPlayer player;
        public GameObject downloadingPanel;
        public GameObject offlineList;
        public GameObject progressBar;
        public GameObject downloadButton;
        public OfflineStreaming downloadContent;
        static bool downloaded;
        [SerializeField] NexUIController UI;

        public void FindReferences(NexPlayer NxP, GameObject downloading, GameObject offList, GameObject bar, OfflineStreaming content, GameObject button, NexUIController ui)
        {
            player = NxP;
            downloadingPanel = downloading;
            offlineList = offList;
            progressBar = bar;
            downloadButton = button;
            downloadContent = content;
            downloaded = false;
            UI = ui;
        }

        private void Start()
        {
            //DisableButtons();
        }

        public void EnableOfflineList()
        {
            if (offlineList.activeInHierarchy)
            {
                offlineList.SetActive(false);
                //downloadButton.SetActive(true);
            }
            else
            {
                UI.HideAllPanels();
                offlineList.SetActive(true);
                downloadContent.SetDownloadPanels();
                //downloadButton.SetActive(false);
                downloadingPanel.SetActive(false);
            }
        }

        public void EnableDownloading()
        {
            if (downloadingPanel.activeInHierarchy)
            {
                downloadingPanel.SetActive(false);
                //downloadButton.SetActive(true);
            }
            else
            {
                UI.HideAllPanels();
                downloadingPanel.SetActive(true);
                //downloadButton.SetActive(false);
                offlineList.SetActive(false);
            }
        }

        public void HandleDownloadDone()
        {
            StartCoroutine(DownloadDone());
        }

        IEnumerator DownloadDone()
        {
            yield return null;
            downloaded = true;
            EnableDownloading();
            EnableOfflineList();
        }

        public void DownloadVideo()
        {
            if (Application.internetReachability != NetworkReachability.ReachableViaCarrierDataNetwork 
                && Application.internetReachability != NetworkReachability.ReachableViaLocalAreaNetwork)
            {
                player.SetPlayerStatus("Download Failed");
                Debug.Log("Download Failed. No internet access.");
                return;
            }

            if(Application.platform == RuntimePlatform.Android)
            {
                if (!CanDownloadStream())
                {
                    player.SetPlayerStatus("Download Failed");
                    Debug.Log("Android Download Failed. No write permissions.");
                    return;
                }
            }

            progressBar.SetActive(!downloaded);
            downloadingPanel.transform.GetChild(1).gameObject.SetActive(downloaded);

            if (player.playType == 0)
            {
                if (player.URL.Contains("mp4"))
                {
                    if (!downloaded)
                        OfflineDownload();
                }
                else
                {
                    if (!downloaded)
                        player.StreamDownloadController.StreamOfflineSaver();
                }

                EnableDownloading();
            }
        }

        private bool CanDownloadStream()
        {
            bool hasWritePermission = true;

            //Check for external storage permissions
            if (Application.platform == RuntimePlatform.Android)
            {
                hasWritePermission = Permission.HasUserAuthorizedPermission(Permission.ExternalStorageWrite);
            }

            return hasWritePermission;
        }


        public void DisableButtons()
        {
            if (Application.platform == RuntimePlatform.WindowsEditor || Application.platform == RuntimePlatform.WindowsPlayer)
            {
                if (player != null && !player.URL.Contains(".mp4"))
                    gameObject.SetActive(false);
            }

            if (player.playType != 0)
            {
                downloadButton.SetActive(false);
            }
        }

        public void OfflineDownload()
        {
            player.downloadingContent = true;
        }
    }
}

using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using NexPlayerAPI;

namespace NexPlayerSample
{
    public class PlaybackSettings : MonoBehaviour
    {
        public InputField url;
        //public Dropdown asset_dropdown;
        //public Dropdown subtitleAsset_dropdown;
        public InputField subtitleUrl;
        public InputField keyServerUrl;
        public Dropdown renderMode_dropdown;
        //public Dropdown playMode_dropdown;

        public AdditionalValueManager drmHeaderManager;
        public AdditionalValueManager httpHeaderManager;

        public Toggle autoPlayToggle;
        public Toggle loopPlayToggle;
        public Toggle mutePlayToggle;
        public Toggle thumbnailToggle;
        public Toggle drmCacheToggle;

        private string[] assetArray;
        private string[] subtitleAssetArray;
        // Start is called before the first frame update
        void Start()
        {
            //playMode_dropdown.value = 0;
            //playMode_dropdown.onValueChanged.AddListener(delegate
            //{
            //    ChangePlayMode(playMode_dropdown);
            //});

            url.gameObject.SetActive(true);
            //asset_dropdown.gameObject.SetActive(false);
            //subtitleAsset_dropdown.gameObject.SetActive(false);

            assetArray = StreamingAssetFileHelper.GetAssetVideoFiles();
            if (assetArray != null)
            {
                List<string> assetList = new List<string>(assetArray);
                //asset_dropdown.AddOptions(assetList);
            }
            else
            {
                Debug.Log("There is no streamingasset video files");
            }

            subtitleAssetArray = StreamingAssetFileHelper.GetAssetSubtitleFiles();
            if (subtitleAssetArray != null)
            {
                List<string> subtitleAssetList = new List<string>(subtitleAssetArray);
                //subtitleAsset_dropdown.AddOptions(subtitleAssetList);
            }
            else
            {
                Debug.Log("There is no streamingasset subtitle files");
            }
        }

        // Update is called once per frame
        void Update()
        {

        }

        public void ChangePlayMode(Dropdown mode)
        {
            Debug.Log("play mode value : " + mode.value);
            switch (mode.value)
            {
                //Streaming Play
                case 0:
                    url.gameObject.SetActive(true);
                    //asset_dropdown.gameObject.SetActive(false);
                    //subtitleAsset_dropdown.gameObject.SetActive(false);
                    break;

                //Asset Play
                case 1:
                    url.gameObject.SetActive(false);
                    //asset_dropdown.gameObject.SetActive(true);
                    //subtitleAsset_dropdown.gameObject.SetActive(true);
                    break;

                //Local Play
                case 2:

                    break;

                default:
                    Debug.Log("Not support mode");
                    break;
            }
        }

        public void TogglePlaybackScene()
        {
            int renderModeIndex = renderMode_dropdown.value;

            switch (renderModeIndex)
            {
                case 0:
                    UnityEngine.SceneManagement.SceneManager.LoadScene("NexPlayer_RawImage_Sample");
                    break;

                case 1:
                    UnityEngine.SceneManagement.SceneManager.LoadScene("NexPlayer_MaterialOverride_Sample");
                    break;

                case 2:
                    UnityEngine.SceneManagement.SceneManager.LoadScene("NexPlayer_RenderTexture_Sample");
                    break;
            }

            NexPlayer.sharedURL = url.text;
            NexPlayer.sharedSubtitleURL = subtitleUrl.text;

            //if (playModeIndex == 0)
            //{
            //    NexPlayer.sharedURL = url.text;
            //    NexPlayer.sharedSubtitleURL = subtitleUrl.text;
            //}
            //else if (playModeIndex == 1)
            //{
            //    //NexPlayer.sharedURL = assetArray[asset_dropdown.value];
            //    //NexPlayer.sharedSubtitleURL = subtitleAssetArray[subtitleAsset_dropdown.value];
            //}

        //NexPlayer.sharedPlayType = playModeIndex;
        NexPlayer.sharedPlayType = 0;
        NexPlayer.sharedKeyServerURL = keyServerUrl.text;

            Dictionary<string, string> drmHeaderDic = drmHeaderManager.GetAdditionalDRMHeaders();
            Dictionary<string, string> httpHeaderDic = httpHeaderManager.GetAdditionalHTTPHeaders();

        NexPlayer.sharedAutoPlay = autoPlayToggle.isOn;
        NexPlayer.sharedLoopPlay = loopPlayToggle.isOn;
        NexPlayer.sharedMutePlay = mutePlayToggle.isOn;
        NexPlayer.sharedThumbnail = thumbnailToggle.isOn;
        NexPlayer.sharedDrmCache = drmCacheToggle.isOn;
    }

        public void Cancel()
        {
            UnityEngine.SceneManagement.SceneManager.LoadScene("MainMenu");
        }
    }
}
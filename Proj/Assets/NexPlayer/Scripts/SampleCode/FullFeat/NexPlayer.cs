using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Events;
using UnityEngine.SceneManagement;
using NexPlayerAPI;
using NexUtility;
using Alticast;

#if UNITY_EDITOR
using UnityEditor;
#endif

namespace NexPlayerSample
{
    public partial class NexPlayer : NexPlayerBehaviour
    {
        #region CONTROLLERS
        /// <summary>
        /// Control max screen functionality
        /// </summary>
        public NexPlayerStreamDownloadController StreamDownloadController { private set; get; }
        #endregion

        #region VARIABLES

        [Tooltip("play type with source(0 : streaming, 1: asset, 2 : local)")]
        [SerializeField]
        [Range(0, 2)]
        public int playType = 0;
        [SerializeField]
        public int assetFileIndex = 0;
        [SerializeField]
        public string streamingSubtitleUri = default; //"http://webs.nexstreaming.com/hls/i/subtitle/sample.smi";
        [SerializeField]
        public string assetSubtitleUri = default;
        [SerializeField]
        public string localSubtitleUri = default;
        [SerializeField]
        public int subtitleFileIndex = 0;

        [Tooltip("Subtitle URL is used to load subtitle")]
        [SerializeField]
        public string subtitleURL = null;

        [SerializeField]
        public bool thumbnail;

        [HideInInspector]
        public string licenseFilePath = "licenseFile.xml";
        // Inspector Events
        [SerializeField]
        public NexPlayerCommand asyncInitEvent;
        [SerializeField]
        public UnityEvent initCompleteEvent = new UnityEvent();

        [SerializeField]
        public UnityEvent readyToPlayEvent = new UnityEvent();

        [SerializeField]
        public UnityEvent startToPlayEvent = new UnityEvent();

        [SerializeField]
        public UnityEvent endOfPlayEvent = new UnityEvent();

        public string savedCaption = null;
        public int savedStartCaptionTime = 0;
        public int savedEndCaptionTime = 0;

        private int lastTimeStamp = 0;

        [NonSerialized]
        public VideoCanvasHelper videoCanvasHelper;

        private NexPlayerStatus playerStatus = NexPlayerStatus.NEXPLAYER_STATUS_NONE;

        private bool isRotate = false;

        private bool isFirstVideo = true;

        [NonSerialized]
        public bool is360scene = false;

        //private bool windowsFirstFrame = true;

        //int httpCounter = 0;

        //3rd party
        [Obsolete]
        private AlticastWVDRM alticastWVDrm;

#endregion

#region BOOL FLAGS
        public bool allowSeek = false;
        private bool bOnSubtitle = true;
        private bool bApplicationPaused = false;
        private bool bApplicationLostFocus = false;
        private bool bFirstPause = true;
#endregion BOOL FLAGS

#region NEXPLAYER PREFS

        [Tooltip("This value is buffering time such as initial buffering time and rebuffering duration in millisecond")]
        public uint bufferingTime;
        [Tooltip("This value is max-caption-length")]
        public uint maxCaptionLength;

        [Tooltip("Enable the player to set a lower resolution")]
        public bool enableTrackDown;
        [Tooltip("The minimun frames percentage that must be rendered. If less frames are rendered, the player will be set to a lower resolution. Recommended value is 70.")]
        [Range(0, 100)]
        public int minRenderedFramesPercentage = 70;

        [Tooltip("If this value is set to True, App works on RunInBackground")]
        public bool runInBackground;

        [Tooltip("This string value is for TimedMetadata Custom Tags")]
        public string customTags;
        [Tooltip("The buffer that controls the maximum length of the external subtitles")]
        public uint BufferSubtitles;
#endregion

#region SHARED VARIABLES 
        public static string sharedURL = null;
        public static string sharedSubtitleURL = null;
        public static int sharedPlayType = 0;
        public static NexSubtitleElement subtitleElement;
        public static Dictionary<string, string> sharedHttpHeaders = null;
        private static bool useSharedAutoPlay = false;
        private static bool _sharedAutoPlay;
        private static bool useSharedLoopPlay = false;
        private static bool _sharedLoopPlay;
        private static bool useSharedMutePlay = false;
        private static bool _sharedMutePlay;
        private static bool useSharedThumbnail = false;
        private static bool _sharedThumbnail;
        public static uint sharedBufferingTime = 0;
        public static bool sharedLowLatencyEnable = false;
        public static bool sharedAutoLowLatencyEnable = false;
        public static uint sharedLowLatencyValue = 0;
        public static bool sharedAbr = false;
        public static bool sharedRunInBackground = false;
        public static string sharedCustomTags = null;
        public static bool sharedSyncEnable = false;
        public static uint sharedDelay = 0;
        public static uint sharedSpeedUpSync = 0;
        public static uint sharedJumpSync = 0;
        public static List<string> sharedMultiURLPaths = null;
        public static uint sharedVolume = 0;

        public static bool sharedAutoPlay
        {
            get
            {
                return _sharedAutoPlay;
            }
            set
            {
                _sharedAutoPlay = value;
                useSharedAutoPlay = true;
            }
        }

        public static bool sharedLoopPlay
        {
            get
            {
                return _sharedLoopPlay;
            }
            set
            {
                _sharedLoopPlay = value;
                useSharedLoopPlay = true;
            }
        }
        public static bool sharedMutePlay
        {
            get
            {
                return _sharedMutePlay;
            }
            set
            {
                _sharedMutePlay = value;
                useSharedMutePlay = true;
            }
        }
        public static bool sharedThumbnail
        {
            get
            {
                return _sharedThumbnail;
            }
            set
            {
                _sharedThumbnail = value;
                useSharedThumbnail = true;
            }
        }
#endregion SHARED VARIABLES

#region MONO BEHAVIOUR
        protected override void OnEnable()
        {
            //Called in HandleEnable
            //base.OnEnable();

            if (asyncInitEvent != null)
            {
                asyncInitEvent.Execute(this, () =>
                {
                    HandleEnable();
                });
            }
            else
            {
                HandleEnable();
            }
        }

        private void HandleEnable()
        {
            base.OnEnable();
            EnableUIComponent(true);
        }

        protected override void Start()
        {
            base.Start();

            EnableUIComponent(true);

            Log("NexPlayer Unity Start");

#if UNITY_IOS && !UNITY_EDITOR_OSX
           if (renderTextureRenderer != null)
               renderTextureRenderer.GetComponent<MeshRenderer>().enabled = true;
           else if (rawImage != null)
               rawImage.GetComponent<RawImage>().enabled = true;
           else if (renderTarget != null)
                renderTarget.enabled = true;
#endif
        }

        protected override void OnDisable()
        {
            if(IsPlayerCreated())
            {
                Stop(); // This probably is not necessary. To be tested. 
            }

            //Calling after Stop to preserve untested functionality
            base.OnDisable();

            subtitleURL = null;
            EnableUIComponent(false);
        }

        protected override void OnApplicationFocus(bool focus)
        {
            base.OnApplicationFocus(focus);

            Log($"OnApplicationFocus({focus}) called");

            if (IsPlayerCreated())
            {
                //Refresh Player in LiveStream
                if (GetTotalTime() == -1 && GetCurrentTime() > GetTotalTime())
                {
                    if (focus)
                    {
                        if (Application.platform == RuntimePlatform.WindowsEditor || Application.platform == RuntimePlatform.WindowsPlayer)
                        {
                            OpenContentAsync(URL, subtitleURL);
                        }
                        else
                        {
                            StartPlayBack();
                        }
                    }
                }

                if (!runInBackground)
                {
                    //Go to Background
                    if (!focus)
                    {
                        // Save current player status                    
                        if (bApplicationPaused == false && playerStatus == NexPlayerStatus.NEXPLAYER_STATUS_NONE)
                        {
                            //Cache the player status
                            playerStatus = GetPlayerStatus();
                        }

                        bApplicationLostFocus = true;

                        if (GetPlayerStatus() > NexPlayerStatus.NEXPLAYER_STATUS_STOP)
                        {
                            Pause();

                            if (StreamDownloadController.bDownloading)
                            {
                                Stop();
                                StreamDownloadController.bDownloading = false;
                            }

                            SetPlayPauseImage(false);
                        }
                    }
                    //Return to Foreground
                    else
                    {
                        if (bApplicationLostFocus)
                        {
                            //Read the cached player status
                            if (playerStatus == NexPlayerStatus.NEXPLAYER_STATUS_PLAY)
                            {
                                Resume();
                                SetPlayPauseImage(true);
                            }

                            if (bApplicationPaused == false)
                            {
                                playerStatus = NexPlayerStatus.NEXPLAYER_STATUS_NONE;
                            }

                            bApplicationLostFocus = false;
                        }
                    }
                }
            }
        }

        protected override void OnApplicationPause(bool pauseStatus)
        {
            base.OnApplicationPause(pauseStatus);

            Log("OnApplicationPause(" + pauseStatus + ")");

            //Check if is LiveStreaming
            if (IsPlayerCreated())
            {
                if (GetTotalTime() > -1 && !Application.runInBackground)
                {
                    //Go to Background
                    if (pauseStatus)
                    {
                        // Save current player status
                        playerStatus = GetPlayerStatus();
                        bApplicationPaused = true;
                        if (playerStatus > NexPlayerStatus.NEXPLAYER_STATUS_STOP)
                        {
                            Pause();
                        }
                    }
                    //Return to Foreground
                    else
                    {
                        if (bApplicationPaused)
                        {
                            if (GetPlayerStatus() == NexPlayerStatus.NEXPLAYER_STATUS_PLAY)
                            {
                                Resume();
                            }
                            playerStatus = NexPlayerStatus.NEXPLAYER_STATUS_NONE;
                            bApplicationPaused = false;
                        }
                    }
                }
            }
        }

        
#endregion

#region NP BEHAVIOUR

        protected override void Init()
        {
            base.Init();

            Log("NexPlayer Unity Init");
            PrintVersionInfo();

#region Run in background
            Application.runInBackground = runInBackground;
            Debug.Log($"Application Run In Background {Application.runInBackground}");
#endregion

#region Video Canvas Helper 1
            videoCanvasHelper = new VideoCanvasHelper(this);
#endregion

#region Windows Editor Condition
            if (Application.platform == RuntimePlatform.WindowsEditor)
            {
                if (GetRenderMode() == NexRenderMode.RawImage && rawImage != null)
                {
                    screenSize = videoCanvasHelper.GetRendererSize();
                }
            }
#endregion

            // Forces device to never sleep
            Screen.sleepTimeout = SleepTimeout.NeverSleep;
        }

        protected override void InitControllers()
        {
            base.InitControllers();

            MultistreamController = gameObject.AddComponent<NexPlayerMultistreamController>();
            MultistreamController.Init(this);

            MultistreamController.numberOfStreams = numberOfStreams;
            MultistreamController.multiURLPaths = multiURLPaths;
            MultistreamController.multiKeyServerURL = multiKeyServerURL;
            MultistreamController.multiSubTexts = multiSubTexts;
            MultistreamController.multiRawImages = multiRawImages;
            MultistreamController.multiRenderTextures = multiRenderTextures;

            StreamDownloadController = new NexPlayerStreamDownloadController(this);
        }

        public override void Release()
        {
            if (IsPlayerCreated())
            {
                Stop();
            }

            //Calling after Stop to preserve untested functionality
            base.Release();
        }

        protected override string GetSubtitleURL()
        {
            string subtitle = null;
            if (subtitleURL != null && !string.IsNullOrEmpty(subtitleURL))
            {
                subtitle = NexUtil.GetFullUri(playType, subtitleURL);
            }
            return subtitle;
        }

        protected override void SetPreInitConfiguration()
        {
            //Check Player Values from other scene
            //Do before calling base to force initialize these values
            CheckSharedValues();

            base.SetPreInitConfiguration();

#region Render
            ChangeRenderMode((int)startingRenderMode);
            originalRendererSize = videoCanvasHelper.GetRendererSize();
            Log("originalRenderSize : " + originalRendererSize.x + " x " + originalRendererSize.y);
#endregion

            if (IsPlayerCreated())
            {
                //Basic Properties
                //Set LogLevel for debugging(Protocol, NexALFactory)
                SetLogLevelForDebugging();

                // Multi-Stream sync disables autoplay to enable it later
                SetAutoPlay(autoPlay);

                // Advanced properties
                SetFirstFrame(!autoPlay && thumbnail);
                SetOnSubtitle(bOnSubtitle);

                SetCaptionText(string.Empty);

                if (Application.platform == RuntimePlatform.Android ||
                    Application.platform == RuntimePlatform.IPhonePlayer ||
                    Application.platform == RuntimePlatform.WindowsEditor ||
                    Application.platform == RuntimePlatform.WindowsPlayer)
                {
                    //The following values are not set for Multistreaming
                    if (MultistreamController != null && MultistreamController.IsMultiStream())
                    {
                        return;
                    }

                    //Set Buffering Time
                    if (bufferingTime > 0)
                    {
                        Log($"set buffering time: {bufferingTime}(sec)");
                        SetPlayerProperty(NexPlayerProperty.INITIAL_BUFFERING_DURATION, (int)bufferingTime);
                        SetPlayerProperty(NexPlayerProperty.RE_BUFFERING_DURATION, (int)bufferingTime);
                    }

                    // Set the TrackDown so the frames percentage rendered is not less than playerPrefs.maxRenderedFramesPercentage 
                    EnableTrackDown(enableTrackDown, minRenderedFramesPercentage);

                    //Set ABR Enabled
                    Log($"ABR enabled: {supportABR}");
                    if (supportABR)
                    {
                        SetPlayerProperty(NexPlayerProperty.SUPPORT_ABR, 1);
                    }
                    else
                    {
                        SetPlayerProperty(NexPlayerProperty.SUPPORT_ABR, 0);
                    }

                    //Max caption length
                    if (maxCaptionLength > 0)
                    {
                        SetPlayerProperty(NexPlayerProperty.MAX_CAPTION_LENGTH, (int)maxCaptionLength);
                    }
                    else
                    {
                        SetPlayerProperty(NexPlayerProperty.MAX_CAPTION_LENGTH, 10000);
                    }

                    //Set Custom Tags for TimedMetadata
                    if (!String.IsNullOrEmpty(customTags))
                    {
                        Log($"Set Custom Tags : {customTags}");
                        SetCustomTags(customTags);
                    }

                    if (Application.platform == RuntimePlatform.Android ||
                        Application.platform == RuntimePlatform.WindowsEditor)
                    {
                        ChangeSubtitleBufferLength((int)BufferSubtitles);
                    }
                }
            }
        }

        //GetContentType is overriden because this class uses playType instead of contentType
        protected override NexContentType GetContentType()
        {
            if(!Enum.IsDefined(typeof(NexContentType), playType))
            {
                Debug.LogError($"Invalid play type {playType}. Default to Streaming.");
                contentType = NexContentType.STREAMING; // apply the value to contentType as well
                return contentType;
            }
            else
            {
                contentType = (NexContentType)playType; // apply the value to contentType as well
                return contentType;
            }
        }

#endregion

#region EVENT MANAGERS
        protected override void EventTextureChanged()
        {
            base.EventTextureChanged();

            if (currentRendererSize != Vector2.zero)
            {
                SetPlayerOutputPosition(ratio, videoCanvasHelper.GetRendererSize());
            }

            if (this.thumbnail != false)
            {
                ShowFirstFrame(this.thumbnail);
            }
        }

        protected override void EventOnTime()
        {
            base.EventOnTime();

            SetCurrentTime();
            SetTotalTime();

            //Update Content Statistic Info(every 60fps) and player should be finished wrap up initialization
            if (IsPlayerCreated() && GetPlayerStatus() > NexPlayerStatus.NEXPLAYER_STATUS_CLOSE)
            {
                // CONTENT INFO     
                UpdateContentInfo();

                // STATISTIC INFO  
                UpdateContentStatisticInfo();

                //Monitor change of the renderer size
                MonitorRendererSizeChange();
            }
        }

        protected override void EventTrackChanged()
        {
            base.EventTrackChanged();
            SetVideoSize();
        }

        protected override void EventInitComplete()
        {
            base.EventInitComplete();

            UpdateContentInfo();

            SetPlayerStatus("Opened");

            if (multiURLPaths.Count > 1)
            {
                if (Application.platform == RuntimePlatform.WindowsEditor || Application.platform == RuntimePlatform.WindowsPlayer)
                {
                    MultistreamController.MultiStreamSetHTTPHeaders();
                }
            }

            initCompleteEvent.Invoke();
        }

        protected override void EventPlaybackStarted()
        {
            base.EventPlaybackStarted();

            SetPlayerStatus("Playing");

            if (!MultistreamController.IsMultiStream())
            {
                readyToPlayEvent.Invoke();
                startToPlayEvent.Invoke();
            }

            UpdateCaption();
            CheckVolume();
        }

        protected override void EventPlaybackPaused()
        {
            base.EventPlaybackPaused();

            SetPlayerStatus("Pause");

            if (bFirstPause)
            {
                bFirstPause = false;
                if (!autoPlay)
                {
                    readyToPlayEvent.Invoke();
                }
            }
        }

        protected override void EventEndOfContent()
        {
            base.EventEndOfContent();

            endOfPlayEvent.Invoke();
        }

        protected override void EventBufferingStarted(int percent)
        {
            base.EventBufferingStarted(percent);

            EventBuffering(percent);
        }

        protected override void EventBuffering(int percent)
        {
            base.EventBuffering(percent);

#if UNITY_STANDALONE && UNITY_EDITOR
            SetPlayerStatus("Buffering");// : " + percent + "%");
#else
            SetPlayerStatus("Buffering: " + percent + "%");
#endif
        }

        protected override void EventBufferingEnded()
        {
            base.EventBufferingEnded();

            var status = GetPlayerStatus();
            switch(status)
            {
                case NexPlayerStatus.NEXPLAYER_STATUS_PAUSE:
                    SetPlayerStatus("Pause");
                    break;
                case NexPlayerStatus.NEXPLAYER_STATUS_PLAY:
                default:
                    SetPlayerStatus("Playing");
                    break;
            }
        }

        protected override void EventStopped()
        {
            base.EventStopped();

            SetPlayerStatus("Stop");
            ResetPlayerUI();
        }

        protected override void EventClosed()
        {
            base.EventClosed();

            ResetPlayerUI();
        }

        protected override void EventSeeked()
        {
            base.EventSeeked();

            SetIsSeeking(false);

            var status = GetPlayerStatus();
            switch (status)
            {
                case NexPlayerStatus.NEXPLAYER_STATUS_PAUSE:
                    //Force update the time
                    lastTimeStamp = 0;
                    SetCurrentTime();
                    SetPlayerStatus("Pause");
                    break;
                case NexPlayerStatus.NEXPLAYER_STATUS_PLAY:
                    SetPlayerStatus("Playing");
                    break;
            }
        }

        protected override void EventTextRender()
        {
            base.EventTextRender();

            HandleEventTextRender();
        }

        protected override void EventLoading()
        {
            base.EventLoading();

            SetPlayerStatus("Loading");
        }

        protected override void EventTimedMetadataRender()
        {
            base.EventTimedMetadataRender();

            NexTimedMetadata updateTimedMetadata = GetTimedMetadata();
            Log($"Metadata Title : {updateTimedMetadata.Title}");
            Log($"Metadata Album : {updateTimedMetadata.Album}");
            Log($"Metadata Artist : {updateTimedMetadata.Artist}");
            Log($"Metadata Track : {updateTimedMetadata.TrackNumber}");
            Log($"Metadata Year : {updateTimedMetadata.Year}");
            Log($"Metadata Genre : {updateTimedMetadata.Genre}");
            Log($"Metadata PrivateFrame : {updateTimedMetadata.PrivateFrame}");
            Log($"Metadata Text : {updateTimedMetadata.Text}");
            Log($"Metadata Encapsulated Object : {updateTimedMetadata.EncapsulatedObject}");
        }

#endregion

#region ERROR MANAGERS

        protected override void Error(NexErrorCode error)
        {
            base.Error(error);

            if (!bLicensingError)
            {
                Log("player init result : " + error.ToString("X"));
            }
        }

        protected override void ErrorTimeLocked()
        {
            base.ErrorTimeLocked();
            Release();
            gameObject.SetActive(false);
            expiredMessage.SetActive(true);
        }

        protected override void ErrorNotActivateAppID()
        {
            base.ErrorNotActivateAppID();

            bLicensingError = true;
        }

        [Obsolete("Use Pause() instead")]
        public void pausePlayer()
        {
            Pause();
        }

        [Obsolete("Use Resume() instead")]
        public void ResumePlayer()
        {
            Resume();
        }

        #endregion

        #region EXTENSIONS

        public void ToggleRotate()
        {
            Log("ToggleRotate() called");

            //only support in rawImage
            if (this.gameObject.activeSelf == true)
            {
                if (GetRenderMode() == NexRenderMode.RawImage && rawImage != null)
                {
                    if (isRotate)
                    {
                        rawImage.rectTransform.localRotation = Quaternion.Euler(Vector3.zero);
                        rawImage.rectTransform.sizeDelta = new Vector2(0.0f, 0.0f);
                        isRotate = false;
                    }
                    else
                    {
                        rawImage.rectTransform.localRotation = Quaternion.Euler(new Vector3(0, 0, -90));
                        rawImage.rectTransform.sizeDelta = new Vector2(screenSize.y - screenSize.x, screenSize.x - screenSize.y);
                        isRotate = true;
                    }
                }
            }
        }

        public void ToggleQuit()
        {
#if UNITY_IOS && (UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX)
            Release();
#endif
            SceneManager.LoadScene(0);
        }

        public void ToggleCaption(bool bToggle)
        {
            Log($"ToggleCaption({bToggle}) called");
            if (this.gameObject.activeSelf == false)
                return;

            if (IsPlayerCreated())
            {
                Log("Toggle Caption : " + bToggle);

                SetOnSubtitle(bToggle);
                OnOffSubtitle(bToggle);
                
                if (bToggle == false)
                {
                    SetCaptionText(string.Empty);
                }
            }
            else
            {
                SetCaptionToggle();
            }

            if (bToggle)
            {
                if (savedCaption != null && IsPlayerCreated())
                {
                    int currentTime = GetCurrentTime();
                    if (savedStartCaptionTime <= currentTime && savedEndCaptionTime >= currentTime)
                    {
                        SetCaptionText(savedCaption);
                    }
                }

                SetCaptionImageColor(Color.white);
            }
            else
            {
                SetCaptionImageColor(Color.gray);
            }
#if UNITY_EDITOR_WIN && UNITY_STANDALONE_WIN
            SetCC(bToggle);
#endif
        }

        private void SetVideoSize()
        {
            Log("SetVideoSize() called");

            if (IsPlayerCreated())
            {
                int height = GetVideoHeight();
                int width = GetVideoWidth();
                SetVideoSizeText($"{width}x{height}");
            }
        }

        public void Seek()
        {
            Log("Seek() called");

            if (this.gameObject.activeSelf == false)
            {
                return;
            }

            if (IsPlayerCreated() && seekBar != null)
            {
                if (allowSeek)
                {
                    int threshold = 1000;
                    if (GetPlayerStatus() > NexPlayerStatus.NEXPLAYER_STATUS_STOP)
                    {
                        int valueTemp = (int)(GetSeekBarValue() * (float)GetTotalTime());

                        bool isUpdateBigEnough = Math.Abs(valueTemp - GetCurrentTime()) > threshold;

                        //Fixed issue seek to current time.                    
                        if (isUpdateBigEnough && valueTemp != GetCurrentTime())
                        {
                            Seek(valueTemp);
                            SetIsSeeking(true);
                            SetCaptionText(string.Empty);
                        }

                        allowSeek = false;
                    }
                    else
                    {
                        //Seek Bar is fixed when player is stop status/close.
                        SetSeekBar(0.0f, 0.0f);
                        allowSeek = false;
                    }
                }
            }
        }

        public void PlayNextVideo()
        {
            if (isFirstVideo)
            {
                ChangeVideoTo("new URL");
            }
            else
            {
                ChangeVideoTo(URL);
            }
        }

        public void ChangeVideoTo(string url)
        {
            isFirstVideo = !isFirstVideo;
            OpenContentAsync(url, subtitleURL);

            Debug.Log("Called ChangeVideo");
        }

        public void CheckSharedValues ()
        {
            if (!string.IsNullOrEmpty(sharedURL))
            {
                Log("playType :" + playType);
                playType = sharedPlayType;
                URL = sharedURL;
            }

            if (!string.IsNullOrEmpty(sharedSubtitleURL))
            {
                subtitleURL = sharedSubtitleURL;
            }

            if (sharedHttpHeaders != null)
            {
                additionalHttpHeaders = sharedHttpHeaders;
            }
            if (useSharedAutoPlay)
            {
                autoPlay = sharedAutoPlay;
            }
            if (useSharedLoopPlay)
            {
                loopPlay = sharedLoopPlay;
            }
            if (useSharedMutePlay)
            {
                mutePlay = sharedMutePlay;
            }
            if (useSharedThumbnail)
            {
                thumbnail = sharedThumbnail;
            }
            if (sharedVolume > 0)
            {
                volume = sharedVolume;
            }
            if (sharedBufferingTime > 0)
            {
                bufferingTime = sharedBufferingTime;
            }
            if (sharedAbr)
            {
                supportABR = sharedAbr;
            }
            if (sharedRunInBackground)
            {
                runInBackground = sharedRunInBackground;
            }
            if (sharedCustomTags != null)
            {
                customTags = sharedCustomTags;
            }
            if (sharedSyncEnable)
            {
                SynchronizationEnable = sharedSyncEnable;
            }
            if (sharedDelay > 0)
            {
                DelayTime = sharedDelay;
            }
            if (sharedSpeedUpSync > 0)
            {
                SpeedUpSyncTime = sharedSpeedUpSync;
            }
            if (sharedJumpSync > 0)
            {
                JumpSyncTime = sharedJumpSync;
            }
            if (sharedMultiURLPaths != null)
            {
                multiURLPaths = sharedMultiURLPaths;
            }

        }
#endregion
    }
}
mergeInto(LibraryManager.library, {

  Hello: function () {
    test();
  },

  ThreeJSTest: function () {
      simplethreeJS();
  },

  UnregisterNativeTextureId: function (nativeTextureId) // this needs to be called every time we create a new texture, in order to avoid memory accumulation
  {
    GLctx.deleteTexture(GL.textures[nativeTextureId]);
   // var tex = GL.textures[nativeTextureId];

    //tex.name = 0;
    GL.textures[nativeTextureId] = null;
  },

  UpdateWebGLTexture: function (textureId, textureWidth, textureHeight) {
    var tex = updateTexture(GL.textures[textureId], GL.currentContext, textureWidth, textureHeight); // do something to the texture
    printTextureArrayInformation(GL.textures);
  },

  UpdateTextureFromUnity: function (textureId, textureWidth, textureHeight) {
    var tex = updateVideoTexture(GL.textures[textureId], GL.currentContext, textureWidth, textureHeight); // do something to the texture
    printTextureArrayInformation(GL.textures);
  },

  NEXPLAYERUnity_SetWebGLKey: function (nexPlayerKey) {
    setWebGLKey(UTF8ToString(nexPlayerKey));
  },

  NEXPLAYERUnity_Init: function (url, serverKey) {
    setUpContext(GL);
  },

  NEXPLAYERUnity_Open: function (url) {
    setUpNexPlayer(UTF8ToString(url));
  },

  NEXPLAYERUnity_Start: function (milliseconds) {
    start(milliseconds);
  },

  NEXPLAYERUnity_Resume: function () {
    resume();
  },

  NEXPLAYERUnity_Pause: function () {
    pause();
  },

  NEXPLAYERUnity_Stop : function () {
    stopPlayer();
  },

  NEXPLAYERUnity_Seek: function (milliseconds) {
    seek(milliseconds);
  },

  NexPlayerUnity_ReleasePlayer: function () {
    releasePlayer(GL.textures);
  },

  NEXPLAYERUnity_NativeGetVersionMajor: function (){
   return NativeGetVersionMajor();
  },

  NEXPLAYERUnity_NativeGetVersionMinor: function (){
   return NativeGetVersionMinor();
  },

  NEXPLAYERUnity_NativeGetVersionPatch: function (){
   return NativeGetVersionPatch();
  },

  NEXPLAYERUnity_GetVideoDuration: function () {
    return getVideoDuration();
  },

  NEXPLAYERUnity_GetCurrentTime: function () {
    return getCurrentLiveTime();
  },

  NexPlayerUnity_SetVolume: function (value) {
    setVolume(value);
  },

  NEXPLAYERUnity_SetTrack: function (trackID) {
    setCurrentTrack(trackID);
  },

  NexPlayerUnity_SetAutoPlayback: function (autoPlayback) {
    setAutoPlayback(autoPlayback);
  },

  NEXPLAYERUnity_Close: function () {
    closePlayer();
  },

  NEXPLAYERUnity_GetPlayerStatus : function() {
    return getPlayerStatus();
  },

  NEXPLAYERUnity_GetContentInfoInt : function (info_index) {
    return getContentInfo(info_index);
  },

  NEXPLAYERUnity_QueueIsEmpty: function () {
    return isEventQueueEmpty();
  },

  NEXPLAYERUnity_AsyncCmdType: function () {
    return getEventAsyncCMDType();
  },

  NEXPLAYERUnity_AsyncCmdValue: function() {
    return getEventAsyncCMDValue();
  },

  NEXPLAYERUnity_AsyncCmdResult: function () {
    return getEventAsyncCMDResult();
  },

  NEXPLAYERUnity_SetAudioStream : function (id) {

  },

  NEXPLAYERUnity_SetCaptionStream : function (id) {

  },

  CopyPasteReader: function(gObj, vName)
  {
      var gameObjectName = UTF8ToString(gObj);
      var voidName = UTF8ToString(vName);
      if (typeof navigator.clipboard.readText === 'function') {
        navigator.clipboard.readText().then(function(data) {
          unityInstance.SendMessage(gameObjectName, voidName, data);
        }, function() {
          unityInstance.SendMessage(gameObjectName, voidName, "no text aviable in clipboard");
        })
      }
  }, // demo
});
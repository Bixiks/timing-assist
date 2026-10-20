#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/GJGameLevel.hpp>
#include <Geode/modify/EnhancedGameObject.hpp>
#include <Geode/modify/EffectGameObject.hpp>
#include <Geode/modify/RingObject.hpp>
#include <Geode/modify/GameObject.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <deque>
#include <type_traits>
#include <utility>
#include <vector>
#include <chrono>
#include <cstring>
#include <set>
#include <string>

using namespace geode::prelude;

#define TA_LIGHT_FIELDS(X) \
    X(m_wasTeleported) \
    X(m_fixGravityBug) \
    X(m_reverseSync) \
    X(m_yVelocityBeforeSlope) \
    X(m_dashX) \
    X(m_dashY) \
    X(m_dashAngle) \
    X(m_dashStartTime) \
    X(m_dashRing) \
    X(m_slopeStartTime) \
    X(m_justPlacedStreak) \
    X(m_maybeLastGroundObject) \
    X(m_lastCollisionBottom) \
    X(m_lastCollisionTop) \
    X(m_lastCollisionLeft) \
    X(m_lastCollisionRight) \
    X(m_unk50C) \
    X(m_unk510) \
    X(m_currentSlope2) \
    X(m_preLastGroundObject) \
    X(m_slopeAngle) \
    X(m_slopeSlidingMaybeRotated) \
    X(m_quickCheckpointMode) \
    X(m_collidedObject) \
    X(m_lastGroundObject) \
    X(m_collidingWithLeft) \
    X(m_collidingWithRight) \
    X(m_maybeSavedPlayerFrame) \
    X(m_scaleXRelated2) \
    X(m_groundYVelocity) \
    X(m_yVelocityRelated) \
    X(m_scaleXRelated3) \
    X(m_scaleXRelated4) \
    X(m_scaleXRelated5) \
    X(m_isCollidingWithSlope) \
    X(m_isBallRotating) \
    X(m_unk669) \
    X(m_currentPotentialSlope) \
    X(m_currentSlope) \
    X(unk_584) \
    X(m_collidingWithSlopeId) \
    X(m_slopeFlipGravityRelated) \
    X(m_slopeAngleRadians) \
    X(m_rotateObjectsRelated) \
    X(m_potentialSlopeMap) \
    X(m_rotationSpeed) \
    X(m_rotateSpeed) \
    X(m_isRotating) \
    X(m_isBallRotating2) \
    X(m_speedMultiplier) \
    X(m_yStart) \
    X(m_gravity) \
    X(m_unk648) \
    X(m_gameModeChangedTime) \
    X(m_padRingRelated) \
    X(m_maybeReducedEffects) \
    X(m_maybeIsFalling) \
    X(m_maybeCanRunIntoBlocks) \
    X(m_isOnGround3) \
    X(m_lastCheckpointTime) \
    X(m_lastJumpTime) \
    X(m_lastFlipTime) \
    X(m_lastSpiderFlipTime) \
    X(m_unkBool5) \
    X(m_accelerationOrSpeed) \
    X(m_snapDistance) \
    X(m_ringJumpRelated) \
    X(m_objectSnappedTo) \
    X(m_maybeSpriteRelated) \
    X(m_slopeRotation) \
    X(m_currentSlopeYVelocity) \
    X(m_unk3d0) \
    X(m_blackOrbRelated) \
    X(m_unk3e0) \
    X(m_unk3e1) \
    X(m_isAccelerating) \
    X(m_isCurrentSlopeTop) \
    X(m_collidedTopMinY) \
    X(m_collidedBottomMaxY) \
    X(m_collidedLeftMaxX) \
    X(m_collidedRightMinX) \
    X(m_maybeIsColliding) \
    X(m_jumpBuffered) \
    X(m_stateRingJump) \
    X(m_wasJumpBuffered) \
    X(m_wasRobotJump) \
    X(m_stateJumpBuffered) \
    X(m_stateRingJump2) \
    X(m_touchedRing) \
    X(m_touchedCustomRing) \
    X(m_touchedGravityPortal) \
    X(m_maybeTouchedBreakableBlock) \
    X(m_jumpRelatedAC2) \
    X(m_touchedPad) \
    X(m_yVelocity) \
    X(m_fallSpeed) \
    X(m_isOnSlope) \
    X(m_wasOnSlope) \
    X(m_slopeVelocity) \
    X(m_maybeUpsideDownSlope) \
    X(m_isShip) \
    X(m_isBird) \
    X(m_isBall) \
    X(m_isDart) \
    X(m_isRobot) \
    X(m_isSpider) \
    X(m_isUpsideDown) \
    X(m_isOnGround) \
    X(m_isGoingLeft) \
    X(m_isSideways) \
    X(m_isSwing) \
    X(m_reverseRelated) \
    X(m_maybeReverseSpeed) \
    X(m_maybeReverseAcceleration) \
    X(m_xVelocityRelated2) \
    X(m_groundObjectMaterial) \
    X(m_vehicleSize) \
    X(m_playerSpeed) \
    X(m_shipRotation) \
    X(m_lastPortalPos) \
    X(m_unkUnused3) \
    X(m_isOnGround2) \
    X(m_lastLandTime) \
    X(m_platformerVelocityRelated) \
    X(m_maybeIsBoosted) \
    X(m_scaleXRelatedTime) \
    X(m_decreaseBoostSlide) \
    X(m_unkA29) \
    X(m_isLocked) \
    X(m_controlsDisabled) \
    X(m_lastGroundedPos) \
    X(m_lastActivatedPortal) \
    X(m_hasEverJumped) \
    X(m_hasEverHitRing) \
    X(m_isSecondPlayer) \
    X(m_unkA99) \
    X(m_totalTime) \
    X(m_isBeingSpawnedByDualPortal) \
    X(m_unkAngle1) \
    X(m_yVelocityRelated3) \
    X(m_followRelated) \
    X(m_unk838) \
    X(m_stateOnGround) \
    X(m_stateUnk) \
    X(m_stateNoStickX) \
    X(m_stateNoStickY) \
    X(m_stateUnk2) \
    X(m_stateBoostX) \
    X(m_stateBoostY) \
    X(m_maybeStateForce2) \
    X(m_stateScale) \
    X(m_platformerXVelocity) \
    X(m_holdingRight) \
    X(m_holdingLeft) \
    X(m_leftPressedFirst) \
    X(m_scaleXRelated) \
    X(m_maybeHasStopped) \
    X(m_xVelocityRelated) \
    X(m_maybeGoingCorrectSlopeDirection) \
    X(m_isSliding) \
    X(m_maybeSlopeForce) \
    X(m_isOnIce) \
    X(m_physDeltaRelated) \
    X(m_isOnGround4) \
    X(m_maybeSlidingTime) \
    X(m_maybeSlidingStartTime) \
    X(m_changedDirectionsTime) \
    X(m_slopeEndTime) \
    X(m_isMoving) \
    X(m_platformerMovingLeft) \
    X(m_platformerMovingRight) \
    X(m_isSlidingRight) \
    X(m_maybeChangedDirectionAngle) \
    X(m_unkUnused2) \
    X(m_isPlatformer) \
    X(m_stateNoAutoJump) \
    X(m_stateDartSlide) \
    X(m_stateHitHead) \
    X(m_stateFlipGravity) \
    X(m_gravityMod) \
    X(m_stateForce) \
    X(m_stateForceVector) \
    X(m_affectedByForces) \
    X(m_lastMovedTime) \
    X(m_playerSpeedAC) \
    X(m_fixRobotJump) \
    X(m_holdingButtons) \
    X(m_inputsLocked) \
    X(m_gv0123) \
    X(m_unkUnused) \
    X(m_isOutOfBounds) \
    X(m_fallStartY) \
    X(m_disablePlayerSqueeze) \
    X(m_ignoreDamage) \
    X(m_enable22Changes) \
    X(m_enableImpulseFix) \
    X(m_width) \
    X(m_height) \
    X(m_contentSize) \
    X(m_position) \
    X(m_positionX) \
    X(m_positionY) \
    X(m_lastPosition)

#define TA_HEAVY_FIELDS(X) \
    X(m_jumpPadRelated) \
    X(m_ringRelatedSet) \
    X(m_touchedRings)


#define TA_BGL_SCALARS(X) \
    X(m_playbackMode) \
    X(m_lowDetailMode) \
    X(m_extraLDM) \
    X(m_ignoreDamage) \
    X(m_enable22Changes) \
    X(m_allowStaticRotate) \
    X(m_fixNegativeScale) \
    X(m_startingFromBeginning) \
    X(m_visibleObjectsCount) \
    X(m_visibleObjectsIndex) \
    X(m_visibleObjects2Count) \
    X(m_visibleObjects2Index) \
    X(m_unked0) \
    X(m_disabledObjectsCount) \
    X(m_unked8) \
    X(m_areaObjectsCount) \
    X(m_processedAreaObjectsCount) \
    X(m_unkee4) \
    X(m_disabledObjectsIndex) \
    X(m_unkeec) \
    X(m_areaObjectsIndex) \
    X(m_processedAreaObjectsIndex) \
    X(m_lastUsedLinkedID) \
    X(m_increasedLayerCapacity) \
    X(m_enterEasingValuesIndex) \
    X(m_dualTouchTrigger) \
    X(m_clicks) \
    X(m_attempts) \
    X(m_jumping) \
    X(m_leftSectionIndex) \
    X(m_rightSectionIndex) \
    X(m_bottomSectionIndex) \
    X(m_topSectionIndex) \
    X(m_isEditor) \
    X(m_blending) \
    X(m_isPlatformer) \
    X(m_particleCount) \
    X(m_customParticleCount) \
    X(m_particleSystemLimit) \
    X(m_activeGradients) \
    X(m_objectsDeactivated) \
    X(m_areaObjectsUpdated) \
    X(m_useReplay) \
    X(m_unk3189) \
    X(m_solidCollisionObjectsCount) \
    X(m_solidCollisionObjectsIndex) \
    X(m_hazardCollisionObjectsCount) \
    X(m_hazardCollisionObjectsIndex) \
    X(m_isPracticeMode) \
    X(m_practiceMusicSync) \
    X(m_loadingProgress) \
    X(m_unk31f8) \
    X(m_cameraFlip) \
    X(m_cameraWidthOffset) \
    X(m_cameraHeightOffset) \
    X(m_updateGroundShadows) \
    X(m_levelLength) \
    X(m_resetActiveObjects) \
    X(m_skipArtReload) \
    X(m_isTestMode) \
    X(m_freezeStartCamera) \
    X(m_unk322a) \
    X(m_cameraUnzoomedHeightOffset) \
    X(m_targetCameraHeightOffset) \
    X(m_calculateTargetHeightOffset) \
    X(m_staticCameraShake) \
    X(m_skipCameraShake) \
    X(m_playerDied) \
    X(m_extraDelta) \
    X(m_started) \
    X(m_unk3251) \
    X(m_cameraWidth) \
    X(m_cameraHeight) \
    X(m_cameraUnzoomedX) \
    X(m_halfCameraWidth) \
    X(m_activeObjectsCount) \
    X(m_activeObjectsIndex) \
    X(m_resumeTimer) \
    X(m_recordInputs) \
    X(m_unk32a1) \
    X(m_unk32a2) \
    X(m_unk32a3) \
    X(m_unk32a4) \
    X(m_unk32d0) \
    X(m_unk32d4) \
    X(m_randomSeed) \
    X(m_unk32e0) \
    X(m_replayRandSeed) \
    X(m_unk32ec) \
    X(m_currentStep) \
    X(m_unk3370) \
    X(m_queuedRecordedButtonsSize) \
    X(m_savedAttempts) \
    X(m_portalIndicators) \
    X(m_orbIndicators) \
    X(m_unk3380) \
    X(m_hideGround) \
    X(m_keepGroupParents) \
    X(m_keyframeGroup) \
    X(m_timePlayed) \
    X(m_tickIndex) \
    X(m_clickIndex) \
    X(m_levelEndAnimationStarted) \
    X(m_points) \
    X(m_calcNonEffectObjectsSize) \
    X(m_calcCollisionBlockObjectsSize) \
    X(m_calcCollisionBlockObjects2Size) \
    X(m_sectionXFactor) \
    X(m_sectionYFactor) \
    X(m_maxGameplayY) \
    X(m_songTriggerInterval) \
    X(m_showAudioVisualizer) \
    X(m_areaMovedCount) \
    X(m_areaScaledCount) \
    X(m_areaRotatedCount) \
    X(m_areaColorCount) \
    X(m_areaMovedCountTotal) \
    X(m_areaScaledCountTotal) \
    X(m_areaRotatedCountTotal) \
    X(m_areaColorCountTotal) \
    X(m_movedCount) \
    X(m_scaledCount) \
    X(m_rotatedCount) \
    X(m_followedCount) \
    X(m_areaMovedCountDisplay) \
    X(m_areaScaledCountDisplay) \
    X(m_areaRotatedCountDisplay) \
    X(m_areaColorCountDisplay) \
    X(m_areaMovedCountTotalDisplay) \
    X(m_areaScaledCountTotalDisplay) \
    X(m_areaRotatedCountTotalDisplay) \
    X(m_areaColorCountTotalDisplay) \
    X(m_movedCountDisplay) \
    X(m_scaledCountDisplay) \
    X(m_rotatedCountDisplay) \
    X(m_followedCountDisplay) \
    X(m_loadingStartPosition) \
    X(m_processingAudioTriggers) \
    X(m_audioPaused) \
    X(m_startOptimization) \
    X(m_isDebugDrawEnabled) \
    X(m_disablePlayerHitbox) \
    X(m_hitboxesOnDeath) \
    X(m_timestamp) \
    X(m_isBetweenSteps) \
    X(m_clickBetweenSteps) \
    X(m_clickOnSteps)
#define TA_PL_SCALARS(X) \
    X(m_unk36c8) \
    X(m_unk36cc) \
    X(m_unk36cd) \
    X(m_unk36ce) \
    X(m_unk36cf) \
    X(m_damageVerified) \
    X(m_passedIntegrity) \
    X(m_objectsCreated) \
    X(m_unk3768) \
    X(m_platformerRestart) \
    X(m_unk376d) \
    X(m_isIgnoreDamageEnabled) \
    X(m_unk3778) \
    X(m_unk377c) \
    X(m_unk3780) \
    X(m_unk3784) \
    X(m_unk3788) \
    X(m_unk378c) \
    X(m_endChecked) \
    X(m_endXPosition) \
    X(m_unk37b0) \
    X(m_unk37b1) \
    X(m_enterEffectPosition) \
    X(m_isSilent) \
    X(m_unk37cc) \
    X(m_unk37e0) \
    X(m_pulseRodIndex) \
    X(m_maxObjectX) \
    X(m_decimalPercentage) \
    X(m_hintShown) \
    X(m_progressWidth) \
    X(m_progressHeight) \
    X(m_totalGravityEffects) \
    X(m_activeGravityEffects) \
    X(m_gravityEffectIndex) \
    X(m_doNot) \
    X(m_unk383c) \
    X(m_skipAudioStep) \
    X(m_jumps) \
    X(m_hasJumped) \
    X(m_uncommittedJumps) \
    X(m_showLeaderboardPercentage) \
    X(m_hasCompletedLevel) \
    X(m_inResetDelay) \
    X(m_lastAttemptPercent) \
    X(m_endLayerStars) \
    X(m_orbs) \
    X(m_diamonds) \
    X(m_secretKey) \
    X(m_recordingStopped) \
    X(m_unk38b0) \
    X(m_unk38b8) \
    X(m_unk38c0) \
    X(m_unk38c8) \
    X(m_unk38cc) \
    X(m_unk38d0) \
    X(m_attemptTime) \
    X(m_bestAttemptTime) \
    X(m_pauseTime) \
    X(m_currentTime) \
    X(m_pauseDelta) \
    X(m_unk3900) \
    X(m_glitterEnabled) \
    X(m_bgEffectDisabled) \
    X(m_unk3906) \
    X(m_isPaused) \
    X(m_disableGravityEffect) \
    X(m_unk3918) \
    X(m_unk3920) \
    X(m_nextColorKey) \
    X(m_tryPlaceCheckpoint) \
    X(m_musicPrepared) \
    X(m_endPosition)
#define TA_GS_SCALARS(X) \
    X(m_cameraZoom) \
    X(m_targetCameraZoom) \
    X(m_cameraOffset) \
    X(m_unkPoint1) \
    X(m_unkPoint2) \
    X(m_unkPoint3) \
    X(m_cameraDeltaPosition) \
    X(m_unkPoint5) \
    X(m_unkPoint6) \
    X(m_unkPoint7) \
    X(m_unkPoint8) \
    X(m_unkPoint9) \
    X(m_unkPoint10) \
    X(m_unkPoint11) \
    X(m_unkPoint12) \
    X(m_unkPoint13) \
    X(m_unkPoint14) \
    X(m_unkPoint15) \
    X(m_unkPoint16) \
    X(m_unkPoint17) \
    X(m_unkPoint18) \
    X(m_unkPoint19) \
    X(m_unkPoint20) \
    X(m_unkPoint21) \
    X(m_unkPoint22) \
    X(m_unkPoint23) \
    X(m_unkPoint24) \
    X(m_unkPoint25) \
    X(m_unkPoint26) \
    X(m_unkPoint27) \
    X(m_unkPoint28) \
    X(m_unkPoint29) \
    X(m_unkBool1) \
    X(m_unkInt1) \
    X(m_unkBool2) \
    X(m_unkInt2) \
    X(m_unkBool3) \
    X(m_unkPoint30) \
    X(m_middleGroundOffsetY) \
    X(m_unkInt3) \
    X(m_unkInt4) \
    X(m_unkBool4) \
    X(m_unkBool5) \
    X(m_cameraPadding) \
    X(m_cameraEasing) \
    X(m_unkInt5) \
    X(m_unkInt6) \
    X(m_unkInt7) \
    X(m_unkInt8) \
    X(m_unkInt9) \
    X(m_unkInt10) \
    X(m_lastModeHeight) \
    X(m_lastCameraZoom) \
    X(m_unkUint1) \
    X(m_portalY) \
    X(m_unkBool6) \
    X(m_gravityRelated) \
    X(m_unkInt12) \
    X(m_unkInt13) \
    X(m_unkInt14) \
    X(m_unkInt15) \
    X(m_unkBool7) \
    X(m_isFreeMode) \
    X(m_disableCameraGridSnap) \
    X(m_backgroundSpeedX) \
    X(m_backgroundSpeedY) \
    X(m_middlegroundSpeedX) \
    X(m_middlegroundSpeedY) \
    X(m_cameraAngle) \
    X(m_targetCameraAngle) \
    X(m_playerStreakBlend) \
    X(m_timeWarp) \
    X(m_queuedTimeWarp) \
    X(m_timeWarpRelated) \
    X(m_currentChannel) \
    X(m_rotateChannel) \
    X(m_totalTime) \
    X(m_levelTime) \
    X(m_unkDouble3) \
    X(m_commandIndex) \
    X(m_unkUint3) \
    X(m_currentProgress) \
    X(m_unkUint4) \
    X(m_unkUint5) \
    X(m_unkUint6) \
    X(m_unkUint7) \
    X(m_lastActivatedPortal1) \
    X(m_lastActivatedPortal2) \
    X(m_cameraPosition) \
    X(m_isFlipped) \
    X(m_levelFlipProgress) \
    X(m_inSecondHalfOfFlipAnimation) \
    X(m_isFlipping) \
    X(m_isDualMode) \
    X(m_dualAnimationProgress) \
    X(m_cameraEdgeValue0) \
    X(m_cameraEdgeValue1) \
    X(m_cameraEdgeValue2) \
    X(m_cameraEdgeValue3) \
    X(m_unkUint10) \
    X(m_unkUint11) \
    X(m_unkUint12) \
    X(m_cameraStepDiff) \
    X(m_backgroundWidth) \
    X(m_timeModRelated) \
    X(m_timeModRelated2) \
    X(m_unkUint13) \
    X(m_unkPoint32) \
    X(m_cameraLastPosition) \
    X(m_unkBool20) \
    X(m_unkBool21) \
    X(m_audioOnDeath) \
    X(m_respawnTime) \
    X(m_noDeathSFX) \
    X(m_cameraShakeEnabled) \
    X(m_cameraShakeDuration) \
    X(m_cameraShakeStrength) \
    X(m_cameraShakeInterval) \
    X(m_lastShakeTime) \
    X(m_unkPoint34) \
    X(m_dualRelated) \
    X(m_unkBool27) \
    X(m_instantExitStaticCameraX) \
    X(m_instantExitStaticCameraY) \
    X(m_unkUint17) \
    X(m_unkBool30) \
    X(m_background) \
    X(m_ground) \
    X(m_middleground) \
    X(m_unlinkDualGravity) \
    X(m_points) \
    X(m_hasObtainedPoints) \
    X(m_pauseCounter) \
    X(m_pauseBufferTimer)
#define TA_BGL_SIZES(X) \
    X(m_activeSfxTriggers) \
    X(m_unk8a0) \
    X(m_spawnRemapTriggers) \
    X(m_uiObjectPositions) \
    X(m_unkdd8) \
    X(m_disabledObjects) \
    X(m_unke08) \
    X(m_areaObjects) \
    X(m_processedAreaObjects) \
    X(m_visibilityGroups) \
    X(m_visibleObjects) \
    X(m_visibleObjects2) \
    X(m_groups) \
    X(m_staticGroups) \
    X(m_optimizedGroups) \
    X(m_targetGroups) \
    X(m_labelObjects) \
    X(m_timeLabelObjects) \
    X(m_destroyObjectValues) \
    X(m_enterEasingValues) \
    X(m_enterEasingIndices) \
    X(m_particleCountToParticleString) \
    X(m_customParticlesUIDs) \
    X(m_solidCollisionObjects) \
    X(m_hazardCollisionObjects) \
    X(m_sequenceTriggers) \
    X(m_activeObjects) \
    X(m_queuedButtons) \
    X(m_queuedRecordedButtons) \
    X(m_unk3330) \
    X(m_queuedReplayButtons) \
    X(m_unk3390) \
    X(m_unk3340) \
    X(m_unk3358) \
    X(m_unk3388) \
    X(m_unk33a0) \
    X(m_savePositionObjects) \
    X(m_savePositionValues) \
    X(m_sections) \
    X(m_nonEffectObjects) \
    X(m_collisionBlockSections) \
    X(m_calcNonEffectObjects) \
    X(m_calcCollisionBlockObjects) \
    X(m_calcCollisionBlockObjects2) \
    X(m_sectionSizes) \
    X(m_nonEffectObjectsSizes) \
    X(m_collisionBlockSectionSizes) \
    X(m_nonEffectObjectsFlags) \
    X(m_stickyGroups)
#define TA_PL_SIZES(X) \
    X(m_objectStrings) \
    X(m_dynamicSaveObjects) \
    X(m_activeSaveObjects1) \
    X(m_activeSaveObjects2) \
    X(m_dynamicSaveObjects2) \
    X(m_blendingColors) \
    X(m_keyColors) \
    X(m_keyOpacities)
#define TA_GS_SIZES(X) \
    X(m_spawnChannelRelated0) \
    X(m_spawnChannelRelated1) \
    X(m_tweenActions) \
    X(m_gameObjectPhysics) \
    X(m_unkVecFloat1) \
    X(m_activatedObjectIDs) \
    X(m_stateObjects) \
    X(m_unkMapPairGJGameEventIntVectorEventTriggerInstance) \
    X(m_unkMapPairGJGameEventIntInt) \
    X(m_enterEffectInstanceVectors) \
    X(m_exitEffectInstanceVectors) \
    X(m_enterChannelMap) \
    X(m_exitChannelMap) \
    X(m_moveEffectInstances) \
    X(m_rotateEffectInstances) \
    X(m_scaleEffectInstances) \
    X(m_fadeEffectInstances) \
    X(m_tintEffectInstances) \
    X(m_unsortedAreaEffects) \
    X(m_advanceFollowInstances) \
    X(m_dynamicMoveActions) \
    X(m_dynamicRotateActions) \
    X(m_unkUMap8) \
    X(m_proximityVolumeRelated) \
    X(m_songChannelStates) \
    X(m_songTriggerStateVectors) \
    X(m_sfxTriggerStates)
namespace {

using Clock = std::chrono::steady_clock;

constexpr int kModeCount = 8;
constexpr int kLandMargin = 2;
constexpr int kWindowMargin = 4;
constexpr int kAfterRelease = 6;
constexpr int kAfterPress = 6;
constexpr int kRescue = 4;
constexpr int kNoTick = -1000000;
constexpr int kRing = 16;
constexpr float kClearCap = 40.f;
constexpr float kShiftPenalty = 1.5f;
constexpr float kRiskClear = 1.5f;
constexpr float kRiskClearLand = 0.5f;
constexpr int kLandCap = 360;
constexpr int kTopBranch = 5;
constexpr int kStartGrace = 30;
constexpr float kRiskGain = 3.f;
constexpr float kMaxSnap = 24.f;
constexpr float kSmoothTime = 0.025f;
constexpr double kTicksPerSecond = 240.0;

enum class Mode { Cube, Ship, Ball, Ufo, Wave, Robot, Spider, Swing };

enum class LandPhase { WaitStart, WaitLeave, WaitFirstLand, WaitRejump, WaitLand, Done };

template <class T>
using Plain = std::remove_cvref_t<T>;

struct Snapshot {
#define TA_DECLARE(f) Plain<decltype(std::declval<PlayerObject&>().f)> f{};
    TA_LIGHT_FIELDS(TA_DECLARE)
    TA_HEAVY_FIELDS(TA_DECLARE)
#undef TA_DECLARE
    std::vector<CCObject*> touching;
    CCPoint nodePosition;
    CCSize nodeContentSize;
    float nodeRotation = 0.f;
    float nodeScaleX = 1.f;
    float nodeScaleY = 1.f;
    bool isDead = false;
    bool isDashing = false;
    bool shouldTryPlacingCheckpoint = false;
    bool canPlaceCheckpoint = false;
    bool checkpointTimeout = false;
    bool touchingRing = false;
    bool hasHeavy = false;
    int tick = kNoTick;
};

struct Queued {
    int tick;
    bool down;
    bool isPlayer1;
    bool main;
    int origin;
};

struct Channel {
    std::deque<Queued> queue;
    bool held = false;
    int pressTick = 0;
    int releaseTick = kNoTick;
    int shift = 0;
    int firePressTick = 0;
    Mode mode = Mode::Cube;
    bool adjusting = false;
    bool adjustIsPlayer1 = true;
    int adjustStart = 0;
    int adjustDeadline = 0;
};

struct Config {
    bool enabled = true;
    int maxDelay = 8;
    int holdMaxDelay = 3;
    int lead = 2;
    int leadModes = 1;
    int lookahead = 120;
    bool keepHold = true;
    bool releaseAssist = true;
    bool indicator = false;
    bool debug = false;
    bool smart = false;
    int smartWindow = 4;
    bool adjust = false;
    int adjustMax = 29;
    double budgetMs = 5.0;
    int planAhead = 1;
};

struct SimEvent {
    int tick;
    bool down;
};

struct SimRecord {
    std::vector<CCPoint> path[2];
    bool died = false;
    int diedIndex = 0;
    CCRect outer;
    CCRect inner;
    float rotation = 0.f;
};

struct SimPlan {
    std::vector<SimEvent> events;
    int length = 0;
    int watchFrom = -1;
    int captureAt = -1;
    bool noOffset = false;
    bool branchAtLanding = false;
    bool branchAtEnd = false;
    Snapshot* branchOut = nullptr;
    bool trackClearance = false;
    SimRecord* record = nullptr;
};

struct SimResult {
    int death = -1;
    int unknownAt = -1;
    float clearance = kClearCap;
    bool resolved = false;
    bool landed = false;
    bool aborted = false;
    bool captured = false;
    bool branchSaved = false;
    CCPoint capturePos;
    GameObject* landObject = nullptr;
    float landY = 0.f;
};

struct Outcome {
    bool ok = false;
    bool aborted = false;
    bool idleDeath = false;
    bool resolved = false;
    bool haveLanding = false;
    GameObject* landObject = nullptr;
    float landY = 0.f;
    float clearance = 0.f;
    int survivors = 0;
};

struct Choice {
    int tick = 0;
    bool found = true;
    bool firstOk = true;
};

struct Probe {
    bool active = false;
    int compareAt = 0;
    PlayerObject* player = nullptr;
    CCPoint predicted[3];
    bool valid[3] = { false, false, false };
};

struct Smooth {
    bool active = false;
    PlayerObject* player = nullptr;
    CCPoint offset;
    float rotation = 0.f;
    CCPoint basePosition;
    float baseRotation = 0.f;
};

struct Targets {
    PlayerObject* players[2] = { nullptr, nullptr };
    int count = 0;
    int channel = 0;
};

struct EvalContext {
    PlayLayer* pl = nullptr;
    Targets const* targets = nullptr;
    Snapshot const* sources[2] = { nullptr, nullptr };
    std::vector<SimEvent> pending;
    Mode mode = Mode::Cube;
    Config const* cfg = nullptr;
    int futureFrom = 0;
    bool wantProbe = false;
    bool noOffset = false;
    bool thorough = false;
    int depth = 0;
};

struct State {
    PlayLayer* layer = nullptr;
    PlayerObject* fakes[2] = { nullptr, nullptr };
    std::set<std::string> simTouched;
    std::set<std::string> simTouchedLogged;
    bool saveCalled = false;
    bool saveBlocked = false;
    int savePercent = 0;
    bool saveChk = false;
    PlayLayer* diagOwner = nullptr;
    int bestBefore = 0;
    int bestAfter = 0;
    int diedAt = 0;
    bool diedPlatformer = false;
    bool diedMoved = false;
    bool diagDeath = false;
    bool deathVerified = false;
    bool deathIntegrity = false;
    bool deathTestMode = false;
    bool deathPractice = false;
    CCLabelBMFont* label = nullptr;
    CCLabelBMFont* diagLabel = nullptr;
    CCDrawNode* liveDraw = nullptr;
    CCDrawNode* decisionDraw = nullptr;
    Channel channels[2];
    std::array<double, kModeCount> hold{};
    std::array<double, kModeCount> gap{};
    std::array<std::array<Snapshot, kRing>, 2> ring;
    Snapshot live[2];
    Smooth smooth[2];
    int updates = 0;
    int attemptStart = 0;
    int lastAnyInput = kNoTick;
    int inputOffset = 0;
    std::array<int, 3> votes{};
    float stepDt = 0.25f;
    bool ready = false;
    bool inQueue = false;
    bool inCommands = false;
    bool dispatching = false;
    bool simulating = false;
    bool catchingUp = false;
    bool simDied = false;
    bool simUnknown = false;
    bool trackClearance = false;
    float simClearance = kClearCap;
    bool captured = false;
    CCPoint capturePos;
    bool runCaptured = false;
    CCPoint runCapturePos;
    std::array<std::array<Snapshot, 2>, kTopBranch + 1> branches;
    bool budgetActive = false;
    bool budgetHit = false;
    Clock::time_point budgetEnd;
    bool changedThisAttempt = false;
    bool smartOn = false;
    bool debugOn = false;
    bool orbSim = true;
    Probe probe;
    int mismatch = 0;
    bool untrusted = false;
};

State g;

int msToTicks(int64_t ms) {
    return std::max(0, static_cast<int>(std::lround(static_cast<double>(ms) * kTicksPerSecond / 1000.0)));
}

int ticksToMs(int ticks) {
    return static_cast<int>(std::lround(ticks * 1000.0 / kTicksPerSecond));
}

Config readConfig() {
    auto mod = Mod::get();
    Config c;
    c.enabled = mod->getSettingValue<bool>("enabled");
    c.maxDelay = msToTicks(mod->getSettingValue<int64_t>("max-delay"));
    c.holdMaxDelay = msToTicks(mod->getSettingValue<int64_t>("hold-max-delay"));
    c.lead = msToTicks(mod->getSettingValue<int64_t>("input-lead"));
    auto leadModes = mod->getSettingValue<std::string>("lead-modes");
    c.leadModes = leadModes == "Wave only" ? 0 : leadModes == "All gamemodes" ? 2 : 1;
    c.lookahead = std::max(24, msToTicks(mod->getSettingValue<int64_t>("lookahead")));
    c.keepHold = mod->getSettingValue<bool>("keep-hold");
    c.releaseAssist = mod->getSettingValue<bool>("release-assist");
    c.indicator = mod->getSettingValue<bool>("indicator");
    c.debug = mod->getSettingValue<bool>("debug-overlay");
    c.smart = mod->getSettingValue<bool>("smart-predict");
    c.smartWindow = std::clamp(msToTicks(mod->getSettingValue<int64_t>("smart-window")), 1, kRing - 2);
    c.adjust = mod->getSettingValue<bool>("wave-adjust");
    c.adjustMax = std::max(1, msToTicks(mod->getSettingValue<int64_t>("adjust-max")));
    c.budgetMs = static_cast<double>(std::clamp<int64_t>(mod->getSettingValue<int64_t>("think-time"), 1, 30));
    c.planAhead = static_cast<int>(std::clamp<int64_t>(mod->getSettingValue<int64_t>("plan-ahead"), 1, 4));
    return c;
}

void save(Snapshot& s, PlayerObject* p, bool heavy);

void noteTouched(char const* where, char const* name) {
    std::string key = fmt::format("{}.{}", where, name);
    g.simTouched.insert(key);
    if (g.simTouchedLogged.insert(key).second) log::warn("check changed {}, put it back", key);
}

template <class T>
bool sameBytes(T const& a, T const& b) {
    return std::memcmp(&a, &b, sizeof(T)) == 0;
}

struct GameGuard {
    PlayLayer* pl = nullptr;
#define TA_D(f) Plain<decltype(std::declval<PlayLayer&>().f)> bgl_##f{};
    TA_BGL_SCALARS(TA_D)
#undef TA_D
#define TA_D(f) Plain<decltype(std::declval<PlayLayer&>().f)> pl_##f{};
    TA_PL_SCALARS(TA_D)
#undef TA_D
#define TA_D(f) Plain<decltype(std::declval<GJGameState&>().f)> gs_##f{};
    TA_GS_SCALARS(TA_D)
#undef TA_D
#define TA_D(f) size_t bglsz_##f = 0;
    TA_BGL_SIZES(TA_D)
#undef TA_D
#define TA_D(f) size_t plsz_##f = 0;
    TA_PL_SIZES(TA_D)
#undef TA_D
#define TA_D(f) size_t gssz_##f = 0;
    TA_GS_SIZES(TA_D)
#undef TA_D
    gd::map<std::pair<int, int>, int> activated;
    gd::unordered_map<int, GameObjectPhysics> physics;
    gd::unordered_map<int, GJValueTween> tweens;
    gd::vector<GameObject*> solids;
    gd::vector<GameObject*> hazards;
    int idCounter = 0;
    PlayerObject* players[2] = { nullptr, nullptr };
    Snapshot playerState[2];

    void capture(PlayLayer* layer) {
        pl = layer;
        if (!pl) return;
        auto& gs = pl->m_gameState;
#define TA_C(f) bgl_##f = pl->f;
        TA_BGL_SCALARS(TA_C)
#undef TA_C
#define TA_C(f) pl_##f = pl->f;
        TA_PL_SCALARS(TA_C)
#undef TA_C
#define TA_C(f) gs_##f = gs.f;
        TA_GS_SCALARS(TA_C)
#undef TA_C
#define TA_C(f) bglsz_##f = pl->f.size();
        TA_BGL_SIZES(TA_C)
#undef TA_C
#define TA_C(f) plsz_##f = pl->f.size();
        TA_PL_SIZES(TA_C)
#undef TA_C
#define TA_C(f) gssz_##f = gs.f.size();
        TA_GS_SIZES(TA_C)
#undef TA_C
        activated = gs.m_activatedObjectIDs;
        physics = gs.m_gameObjectPhysics;
        tweens = gs.m_tweenActions;
        solids = pl->m_solidCollisionObjects;
        hazards = pl->m_hazardCollisionObjects;
        idCounter = *reinterpret_cast<int*>(geode::base::get() + 0x6ba158);
        players[0] = pl->m_player1;
        players[1] = pl->m_player2;
        for (int i = 0; i < 2; i++) {
            if (players[i]) save(playerState[i], players[i], false);
        }
    }

    void restore() {
        if (!pl) return;
        auto& gs = pl->m_gameState;
#define TA_R(f) if (!sameBytes(bgl_##f, pl->f)) { noteTouched("layer", #f); pl->f = bgl_##f; }
        TA_BGL_SCALARS(TA_R)
#undef TA_R
#define TA_R(f) if (!sameBytes(pl_##f, pl->f)) { noteTouched("play", #f); pl->f = pl_##f; }
        TA_PL_SCALARS(TA_R)
#undef TA_R
#define TA_R(f) if (!sameBytes(gs_##f, gs.f)) { noteTouched("state", #f); gs.f = gs_##f; }
        TA_GS_SCALARS(TA_R)
#undef TA_R
#define TA_R(f) if (bglsz_##f != pl->f.size()) noteTouched("layer-list", #f);
        TA_BGL_SIZES(TA_R)
#undef TA_R
#define TA_R(f) if (plsz_##f != pl->f.size()) noteTouched("play-list", #f);
        TA_PL_SIZES(TA_R)
#undef TA_R
#define TA_R(f) if (gssz_##f != gs.f.size()) noteTouched("state-list", #f);
        TA_GS_SIZES(TA_R)
#undef TA_R
        if (gs.m_activatedObjectIDs != activated) {
            noteTouched("state", "m_activatedObjectIDs");
            gs.m_activatedObjectIDs = activated;
        }
        if (gs.m_gameObjectPhysics.size() != physics.size()) noteTouched("state", "m_gameObjectPhysics");
        gs.m_gameObjectPhysics = physics;
        if (gs.m_tweenActions.size() != tweens.size()) noteTouched("state", "m_tweenActions");
        gs.m_tweenActions = tweens;
        pl->m_solidCollisionObjects = solids;
        pl->m_hazardCollisionObjects = hazards;
        int nowCounter = *reinterpret_cast<int*>(geode::base::get() + 0x6ba158);
        if (nowCounter != idCounter) noteTouched("game", "uniqueIDCounter");
        for (int i = 0; i < 2; i++) {
            auto p = players[i];
            if (!p || (i == 0 ? pl->m_player1 : pl->m_player2) != p) continue;
            auto& st = playerState[i];
#define TA_R(f) if (!sameBytes(st.f, Plain<decltype(p->f)>(p->f))) { noteTouched("player", #f); p->f = st.f; }
            TA_LIGHT_FIELDS(TA_R)
#undef TA_R
        }
        pl = nullptr;
    }
};

struct Budget {
    explicit Budget(double ms) {
        if (g.layer && g.ready) guard.capture(g.layer);
        g.budgetActive = true;
        g.budgetHit = false;
        g.budgetEnd = Clock::now() + std::chrono::microseconds(static_cast<int64_t>(ms * 1000.0));
    }
    ~Budget() {
        guard.restore();
        g.budgetActive = false;
        g.budgetHit = false;
    }
    Budget(Budget const&) = delete;
    Budget& operator=(Budget const&) = delete;
    GameGuard guard;
};

bool outOfTime() {
    if (!g.budgetActive) return false;
    if (g.budgetHit) return true;
    if (Clock::now() > g.budgetEnd) g.budgetHit = true;
    return g.budgetHit;
}

Mode modeOf(bool ship, bool bird, bool ball, bool dart, bool robot, bool spider, bool swing) {
    if (ship) return Mode::Ship;
    if (bird) return Mode::Ufo;
    if (ball) return Mode::Ball;
    if (dart) return Mode::Wave;
    if (robot) return Mode::Robot;
    if (spider) return Mode::Spider;
    if (swing) return Mode::Swing;
    return Mode::Cube;
}

Mode modeOf(PlayerObject* p) {
    return modeOf(p->m_isShip, p->m_isBird, p->m_isBall, p->m_isDart, p->m_isRobot, p->m_isSpider, p->m_isSwing);
}

Mode modeOf(Snapshot const& s) {
    return modeOf(s.m_isShip, s.m_isBird, s.m_isBall, s.m_isDart, s.m_isRobot, s.m_isSpider, s.m_isSwing);
}

char const* modeName(Mode m) {
    switch (m) {
        case Mode::Ship: return "ship";
        case Mode::Ball: return "ball";
        case Mode::Ufo: return "ufo";
        case Mode::Wave: return "wave";
        case Mode::Robot: return "robot";
        case Mode::Spider: return "spider";
        case Mode::Swing: return "swing";
        default: return "cube";
    }
}

bool isHoldMode(Mode m) {
    return m == Mode::Ship || m == Mode::Wave;
}

bool isLandMode(Mode m) {
    return m == Mode::Cube || m == Mode::Ball || m == Mode::Robot;
}

bool releaseMatters(Mode m) {
    return m == Mode::Ship || m == Mode::Wave || m == Mode::Robot;
}

int idx(Mode m) {
    return static_cast<int>(m);
}

int holdTicks(Mode m) {
    return std::clamp(static_cast<int>(std::lround(g.hold[idx(m)])), 2, 90);
}

int gapTicks(Mode m) {
    return std::clamp(static_cast<int>(std::lround(g.gap[idx(m)])), 3, 120);
}

int maxDelayFor(Config const& cfg, Mode m) {
    return isHoldMode(m) ? std::min(cfg.maxDelay, cfg.holdMaxDelay) : cfg.maxDelay;
}

int leadFor(Config const& cfg, Mode m) {
    if (cfg.lead <= 0) return 0;
    if (cfg.leadModes == 2) return cfg.lead;
    if (m == Mode::Wave) return cfg.lead;
    if (m == Mode::Ship && cfg.leadModes == 1) return cfg.lead;
    return 0;
}

std::vector<int> spreadAround(int center, int lo, int hi, std::initializer_list<int> base) {
    std::vector<int> out;
    for (int v = center - 2; v <= center + 2; v++) {
        if (v >= lo && v <= hi) out.push_back(v);
    }
    for (int v : base) {
        if (v >= lo && v <= hi && std::find(out.begin(), out.end(), v) == out.end()) out.push_back(v);
    }
    if (out.empty()) out.push_back(std::clamp(center, lo, hi));
    std::stable_sort(out.begin(), out.end(), [center](int a, int b) {
        return std::abs(a - center) < std::abs(b - center);
    });
    return out;
}

std::vector<int> holdOptions(Mode m) {
    int typical = holdTicks(m);
    if (m == Mode::Robot) {
        auto out = spreadAround(typical, 2, 40, { 4, 12, 24 });
        if (out.size() > 6) out.resize(6);
        return out;
    }
    int lo = std::max(2, typical / 2);
    int hi = std::clamp(typical * 5 / 2, 8, 50);
    return spreadAround(typical, lo, hi, { 2, 3, 4, 6, 8, 11, 15, 20, 27, 36, 48 });
}

std::vector<int> nextPressOptions(Mode m, int minGap) {
    int typical = gapTicks(m);
    int lo = std::max(minGap, typical / 2);
    int hi = std::clamp(typical * 5 / 2, lo + 4, 60);
    auto out = spreadAround(typical, lo, hi, { 3, 5, 8, 12, 17, 24, 34, 46, 60 });
    out.push_back(-1);
    return out;
}

void learn(double& value, int sample) {
    value = std::clamp(value * 0.75 + sample * 0.25, 2.0, 120.0);
}

bool keepInSim(GameObjectType t) {
    return t == GameObjectType::Solid
        || t == GameObjectType::Hazard
        || t == GameObjectType::AnimatedHazard
        || t == GameObjectType::Slope;
}

bool isSimSpecial(GameObjectType t) {
    switch (t) {
        case GameObjectType::YellowJumpPad:
        case GameObjectType::PinkJumpPad:
        case GameObjectType::GravityPad:
        case GameObjectType::RedJumpPad:
        case GameObjectType::SpiderPad:
        case GameObjectType::YellowJumpRing:
        case GameObjectType::PinkJumpRing:
        case GameObjectType::GravityRing:
        case GameObjectType::GreenRing:
        case GameObjectType::DropRing:
        case GameObjectType::RedJumpRing:
        case GameObjectType::DashRing:
        case GameObjectType::GravityDashRing:
        case GameObjectType::SpiderOrb:
            return true;
        default:
            return false;
    }
}

bool simulatedSpecial(GameObject* obj) {
    return g.orbSim && obj && isSimSpecial(obj->m_objectType);
}

bool isCollectibleId(int id) {
    return id == 1329 || id == 1275 || id == 1587 || id == 1589 || id == 1598
        || id == 1614 || id == 3601 || (id >= 4401 && id <= 4539);
}

bool isSpeedPortal(int id) {
    return id == 200 || id == 201 || id == 202 || id == 203 || id == 1334;
}

bool isInteractive(GameObject* obj) {
    if (isSpeedPortal(obj->m_objectID)) return true;
    if (obj->m_isTrigger) return false;
    switch (obj->m_objectType) {
        case GameObjectType::InverseGravityPortal:
        case GameObjectType::NormalGravityPortal:
        case GameObjectType::ShipPortal:
        case GameObjectType::CubePortal:
        case GameObjectType::YellowJumpPad:
        case GameObjectType::PinkJumpPad:
        case GameObjectType::GravityPad:
        case GameObjectType::YellowJumpRing:
        case GameObjectType::PinkJumpRing:
        case GameObjectType::GravityRing:
        case GameObjectType::InverseMirrorPortal:
        case GameObjectType::NormalMirrorPortal:
        case GameObjectType::BallPortal:
        case GameObjectType::RegularSizePortal:
        case GameObjectType::MiniSizePortal:
        case GameObjectType::UfoPortal:
        case GameObjectType::Breakable:
        case GameObjectType::DualPortal:
        case GameObjectType::SoloPortal:
        case GameObjectType::WavePortal:
        case GameObjectType::RobotPortal:
        case GameObjectType::TeleportPortal:
        case GameObjectType::GreenRing:
        case GameObjectType::DropRing:
        case GameObjectType::SpiderPortal:
        case GameObjectType::RedJumpPad:
        case GameObjectType::RedJumpRing:
        case GameObjectType::CustomRing:
        case GameObjectType::DashRing:
        case GameObjectType::GravityDashRing:
        case GameObjectType::SwingPortal:
        case GameObjectType::GravityTogglePortal:
        case GameObjectType::SpiderOrb:
        case GameObjectType::SpiderPad:
        case GameObjectType::TeleportOrb:
            return true;
        default:
            return false;
    }
}

float rectGap(CCRect const& a, CCRect const& b) {
    float dx = std::max({ 0.f, a.getMinX() - b.getMaxX(), b.getMinX() - a.getMaxX() });
    float dy = std::max({ 0.f, a.getMinY() - b.getMaxY(), b.getMinY() - a.getMaxY() });
    return std::sqrt(dx * dx + dy * dy);
}

float normalizeAngle(float a) {
    while (a > 180.f) a -= 360.f;
    while (a < -180.f) a += 360.f;
    return a;
}

void clearLogs(PlayerObject* p) {
    p->m_collisionLogTop->removeAllObjects();
    p->m_collisionLogBottom->removeAllObjects();
    p->m_collisionLogLeft->removeAllObjects();
    p->m_collisionLogRight->removeAllObjects();
}

bool touchingRing(PlayerObject* p) {
    return p && p->m_touchingRings && p->m_touchingRings->count() > 0;
}

void save(Snapshot& s, PlayerObject* p, bool heavy) {
#define TA_SAVE(f) s.f = p->f;
    TA_LIGHT_FIELDS(TA_SAVE)
    if (heavy) {
        TA_HEAVY_FIELDS(TA_SAVE)
    }
#undef TA_SAVE
    s.hasHeavy = heavy;
    s.touching.clear();
    if (heavy && p->m_touchingRings) {
        for (unsigned int i = 0; i < p->m_touchingRings->count(); i++) {
            s.touching.push_back(p->m_touchingRings->objectAtIndex(i));
        }
    }
    s.nodePosition = p->getPosition();
    s.nodeContentSize = p->getContentSize();
    s.nodeRotation = p->getRotation();
    s.nodeScaleX = p->getScaleX();
    s.nodeScaleY = p->getScaleY();
    s.isDead = p->m_isDead;
    s.isDashing = p->m_isDashing;
    s.shouldTryPlacingCheckpoint = p->m_shouldTryPlacingCheckpoint;
    s.canPlaceCheckpoint = p->m_canPlaceCheckpoint;
    s.checkpointTimeout = p->m_checkpointTimeout;
    s.touchingRing = touchingRing(p);
}

void load(PlayerObject* p, Snapshot const& s, bool forSim) {
    p->setContentSize(s.nodeContentSize);
    p->setScaleX(s.nodeScaleX);
    p->setScaleY(s.nodeScaleY);
    p->setRotation(s.nodeRotation);
    p->setPosition(s.nodePosition);
#define TA_LOAD(f) p->f = s.f;
    TA_LIGHT_FIELDS(TA_LOAD)
    if (s.hasHeavy) {
        TA_HEAVY_FIELDS(TA_LOAD)
    }
#undef TA_LOAD
    p->m_touchingRings->removeAllObjects();
    if (forSim) {
        p->m_isDead = false;
        p->m_isDashing = false;
        p->m_shouldTryPlacingCheckpoint = false;
        p->m_canPlaceCheckpoint = false;
        p->m_checkpointTimeout = false;
        if (g.orbSim) {
            for (auto obj : s.touching) p->m_touchingRings->addObject(obj);
        }
    }
    else {
        p->m_isDead = s.isDead;
        p->m_isDashing = s.isDashing;
        p->m_shouldTryPlacingCheckpoint = s.shouldTryPlacingCheckpoint;
        p->m_canPlaceCheckpoint = s.canPlaceCheckpoint;
        p->m_checkpointTimeout = s.checkpointTimeout;
    }
    clearLogs(p);
    p->m_isObjectRectDirty = true;
    p->m_isOrientedBoxDirty = true;
}

int ringSlot(int tick) {
    return ((tick % kRing) + kRing) % kRing;
}

int playerIndex(PlayLayer* pl, PlayerObject* p) {
    return p == pl->m_player2 ? 1 : 0;
}

void clearRing() {
    for (auto& r : g.ring) {
        for (auto& s : r) s.tick = kNoTick;
    }
}

Targets targetsFor(PlayLayer* pl, bool isPlayer1) {
    Targets t;
    bool twoPlayer = pl->m_levelSettings && pl->m_levelSettings->m_twoPlayerMode;
    bool dual = pl->m_gameState.m_isDualMode;
    t.channel = (twoPlayer && !isPlayer1) ? 1 : 0;
    if (dual && !twoPlayer && pl->m_player2) {
        t.players[0] = pl->m_player1;
        t.players[1] = pl->m_player2;
        t.count = 2;
    }
    else if (dual && twoPlayer && !isPlayer1 && pl->m_player2) {
        t.players[0] = pl->m_player2;
        t.count = 1;
    }
    else {
        t.players[0] = pl->m_player1;
        t.count = 1;
    }
    return t;
}

bool layerReady(PlayLayer* pl) {
    return pl && g.ready && g.layer == pl && g.fakes[0] && g.fakes[1];
}

bool inStartGrace() {
    return g.updates - g.attemptStart < kStartGrace;
}

bool canAssist(PlayLayer* pl, Targets const& t) {
    if (!layerReady(pl) || g.untrusted || inStartGrace()) return false;
    if (pl->m_playerDied || pl->m_levelEndAnimationStarted || pl->m_hasCompletedLevel || pl->m_isPaused) return false;
    for (int i = 0; i < t.count; i++) {
        auto p = t.players[i];
        if (!p || p->m_isDead || p->m_isDashing || p->m_isLocked) return false;
        if (touchingRing(p)) return false;
    }
    return true;
}

void captureLive(Targets const& t) {
    for (int i = 0; i < t.count; i++) save(g.live[i], t.players[i], true);
}

SimResult runSim(PlayLayer* pl, int count, Snapshot const* const* sources, SimPlan const& plan) {
    if (outOfTime()) {
        SimResult aborted;
        aborted.aborted = true;
        return aborted;
    }
    PlayerObject* fakes[2] = { g.fakes[0], g.fakes[1] };
    for (int i = 0; i < count; i++) load(fakes[i], *sources[i], true);

    GameObject* blocks[2] = { pl->m_player1CollisionBlock, pl->m_player2CollisionBlock };
    CCPoint blockPos[2];
    double blockX[2] = { 0.0, 0.0 };
    double blockY[2] = { 0.0, 0.0 };
    for (int i = 0; i < 2; i++) {
        if (!blocks[i]) continue;
        blockPos[i] = blocks[i]->getPosition();
        blockX[i] = blocks[i]->m_positionX;
        blockY[i] = blocks[i]->m_positionY;
    }

    int offset = plan.noOffset ? 0 : g.inputOffset;
    std::vector<SimEvent> events = plan.events;
    for (auto& e : events) e.tick = std::max(0, e.tick + offset);
    std::stable_sort(events.begin(), events.end(), [](SimEvent const& a, SimEvent const& b) {
        return a.tick < b.tick;
    });

    float dt = g.stepDt > 0.f ? g.stepDt : 0.25f;
    SimResult result;
    int end = plan.length;
    size_t next = 0;
    LandPhase phase = plan.watchFrom >= 0 ? LandPhase::WaitStart : LandPhase::Done;
    int groundedFor = 0;
    auto record = plan.record;
    if (record) {
        for (int i = 0; i < count; i++) {
            record->path[i].clear();
            record->path[i].push_back(fakes[i]->getPosition());
        }
        record->died = false;
    }

    g.simulating = true;
    g.simDied = false;
    g.simUnknown = false;
    g.trackClearance = plan.trackClearance;
    g.simClearance = kClearCap;
    g.captured = false;

    for (int tick = 0; tick < end; tick++) {
        if ((tick & 15) == 15 && outOfTime()) {
            result.aborted = true;
            break;
        }
        if (phase == LandPhase::WaitStart && tick >= plan.watchFrom) {
            phase = fakes[0]->m_isOnGround ? LandPhase::WaitLeave : LandPhase::WaitFirstLand;
        }

        while (next < events.size() && events[next].tick <= tick) {
            for (int i = 0; i < count; i++) {
                if (events[next].down) fakes[i]->pushButton(PlayerButton::Jump);
                else fakes[i]->releaseButton(PlayerButton::Jump);
            }
            next++;
        }

        int diedIndex = -1;
        for (int i = 0; i < count; i++) {
            auto f = fakes[i];
            clearLogs(f);
            f->update(dt);
            pl->checkCollisions(f, dt, false);
            if (f->m_isDead) g.simDied = true;
            if (g.simDied) {
                diedIndex = i;
                break;
            }
            if (g.simUnknown) break;
            f->updateRotation(dt);
            if (record) record->path[i].push_back(f->getPosition());
        }

        if (g.simDied) {
            result.death = tick;
            if (record && diedIndex >= 0) {
                auto f = fakes[diedIndex];
                f->m_isObjectRectDirty = true;
                record->died = true;
                record->diedIndex = diedIndex;
                record->outer = f->GameObject::getObjectRect();
                record->inner = f->GameObject::getObjectRect(0.3f, 0.3f);
                record->rotation = f->getRotation();
                record->path[diedIndex].push_back(f->getPosition());
            }
            break;
        }
        if (g.simUnknown) {
            result.unknownAt = tick;
            break;
        }

        if (tick == plan.captureAt) {
            g.capturePos = fakes[0]->getPosition();
            g.captured = true;
            result.captured = true;
            result.capturePos = g.capturePos;
        }

        bool grounded = fakes[0]->m_isOnGround;
        switch (phase) {
            case LandPhase::WaitLeave:
                if (!grounded) phase = LandPhase::WaitLand;
                break;
            case LandPhase::WaitFirstLand:
                if (grounded) {
                    phase = LandPhase::WaitRejump;
                    groundedFor = 0;
                }
                break;
            case LandPhase::WaitRejump:
                if (!grounded) {
                    phase = LandPhase::WaitLand;
                }
                else if (++groundedFor > 3) {
                    phase = LandPhase::Done;
                    end = std::min(end, tick + 1 + (plan.branchAtLanding ? 0 : kLandMargin));
                    result.landed = true;
                    result.landObject = fakes[0]->m_lastGroundObject;
                    result.landY = fakes[0]->getPositionY();
                    if (plan.branchAtLanding && plan.branchOut) {
                        for (int i = 0; i < count; i++) save(plan.branchOut[i], fakes[i], true);
                        result.branchSaved = true;
                    }
                }
                break;
            case LandPhase::WaitLand:
                if (grounded) {
                    phase = LandPhase::Done;
                    end = std::min(end, tick + 1 + (plan.branchAtLanding ? 0 : kLandMargin));
                    result.landed = true;
                    result.landObject = fakes[0]->m_lastGroundObject;
                    result.landY = fakes[0]->getPositionY();
                    if (plan.branchAtLanding && plan.branchOut) {
                        for (int i = 0; i < count; i++) save(plan.branchOut[i], fakes[i], true);
                        result.branchSaved = true;
                    }
                }
                break;
            default:
                break;
        }
    }

    if (plan.branchAtEnd && plan.branchOut && !result.branchSaved && result.death < 0 && result.unknownAt < 0 && !result.aborted) {
        for (int i = 0; i < count; i++) save(plan.branchOut[i], fakes[i], true);
        result.branchSaved = true;
    }
    result.clearance = g.simClearance;
    if (result.death >= 0) result.resolved = true;
    else if (result.aborted || result.unknownAt >= 0) result.resolved = false;
    else if (plan.watchFrom >= 0) result.resolved = result.landed;
    else result.resolved = true;
    g.simulating = false;
    g.trackClearance = false;

    for (int i = 0; i < 2; i++) {
        if (!blocks[i]) continue;
        blocks[i]->setPosition(blockPos[i]);
        blocks[i]->m_positionX = blockX[i];
        blocks[i]->m_positionY = blockY[i];
    }

    return result;
}

void armProbe(EvalContext const& c, SimPlan const& base, int rel, CCPoint predicted) {
    g.probe.active = true;
    g.probe.compareAt = g.updates + 2 + base.captureAt;
    g.probe.player = c.targets->players[0];
    g.probe.predicted[1] = predicted;
    g.probe.valid[1] = true;
    for (int s = 0; s < 3; s += 2) {
        int delta = s - 1;
        g.probe.valid[s] = false;
        SimPlan alt = base;
        alt.record = nullptr;
        alt.trackClearance = false;
        alt.watchFrom = -1;
        alt.length = base.captureAt + 1;
        bool moved = false;
        for (auto& e : alt.events) {
            if (e.down && e.tick == rel) {
                if (e.tick + delta < 0) break;
                e.tick += delta;
                moved = true;
                break;
            }
        }
        if (!moved) continue;
        auto r = runSim(c.pl, c.targets->count, c.sources, alt);
        if (r.death < 0 && r.unknownAt < 0 && g.captured) {
            g.probe.predicted[s] = g.capturePos;
            g.probe.valid[s] = true;
        }
    }
}

bool isHolding(Snapshot const& s) {
    auto it = s.m_holdingButtons.find(static_cast<int>(PlayerButton::Jump));
    return it != s.m_holdingButtons.end() && it->second;
}

bool canContinue(EvalContext const& c, Snapshot* from, int depth, bool thorough) {
    if (depth <= 0) return true;
    Snapshot const* src[2] = { &from[0], &from[1] };
    Snapshot* out = g.branches[std::clamp(depth - 1, 0, kTopBranch - 1)].data();
    int count = c.targets->count;
    Mode m = modeOf(from[0]);
    int h = holdTicks(m);

    auto attempt = [&](SimPlan& p) {
        p.noOffset = c.noOffset;
        p.branchOut = out;
        auto r = runSim(c.pl, count, src, p);
        if (r.aborted) return true;
        if (r.death >= 0) return false;
        if (depth == 1 || !r.branchSaved) return true;
        return canContinue(c, out, depth - 1, false);
    };

    if (isLandMode(m)) {
        SimPlan idle;
        idle.length = 48;
        idle.watchFrom = 0;
        idle.branchAtLanding = true;
        if (attempt(idle)) return true;

        static constexpr int quick[] = { 0, 4, 9, 16, 26 };
        static constexpr int dense[] = { 0, 2, 4, 6, 9, 12, 16, 21, 27, 34 };
        auto tryJump = [&](int k) {
            SimPlan p;
            p.events.push_back({ k, true });
            p.events.push_back({ k + h, false });
            p.length = k + std::max(c.cfg->lookahead, kLandCap);
            p.watchFrom = k;
            p.branchAtLanding = true;
            return attempt(p);
        };
        if (thorough) {
            for (int k : dense) {
                if (tryJump(k)) return true;
            }
        }
        else {
            for (int k : quick) {
                if (tryJump(k)) return true;
            }
        }
        return false;
    }

    if (isHoldMode(m)) {
        bool holding = isHolding(from[0]);
        int window = std::clamp(std::max(h, gapTicks(m)) + kAfterPress, 8, 40);
        static constexpr int quick[] = { 0, 3, 6, 10, 15 };
        static constexpr int dense[] = { 0, 1, 2, 3, 4, 6, 8, 10, 13, 17 };
        auto tryToggle = [&](int k) {
            SimPlan p;
            p.events.push_back({ k, !holding });
            p.length = k + window;
            p.branchAtEnd = true;
            return attempt(p);
        };
        SimPlan keep;
        keep.length = window;
        keep.branchAtEnd = true;
        if (attempt(keep)) return true;
        if (thorough) {
            for (int k : dense) {
                if (tryToggle(k)) return true;
            }
        }
        else {
            for (int k : quick) {
                if (tryToggle(k)) return true;
            }
        }
        return false;
    }

    int quiet = m == Mode::Spider ? 14 : 24;
    SimPlan none;
    none.length = quiet;
    none.branchAtEnd = true;
    if (attempt(none)) return true;
    static constexpr int quick[] = { 0, 4, 8, 14 };
    static constexpr int dense[] = { 0, 2, 4, 6, 8, 11, 14, 18 };
    auto tryTap = [&](int k) {
        SimPlan p;
        p.events.push_back({ k, true });
        p.events.push_back({ k + 3, false });
        p.length = k + 16;
        p.branchAtEnd = true;
        return attempt(p);
    };
    if (thorough) {
        for (int k : dense) {
            if (tryTap(k)) return true;
        }
    }
    else {
        for (int k : quick) {
            if (tryTap(k)) return true;
        }
    }
    return false;
}

bool considerRun(EvalContext const& c, SimPlan& plan, bool score, Outcome& best, int idleUntil) {
    plan.length = std::max(plan.length, c.futureFrom + kWindowMargin);
    plan.trackClearance = score;
    plan.noOffset = c.noOffset;
    auto r = runSim(c.pl, c.targets->count, c.sources, plan);
    g.runCaptured = r.captured;
    g.runCapturePos = r.capturePos;
    if (r.aborted) {
        best.aborted = true;
        if (!best.ok) {
            best.ok = true;
            best.clearance = kClearCap;
        }
        return true;
    }
    if (r.death >= 0 && r.death < idleUntil) best.idleDeath = true;
    bool ok = r.death < 0 && (r.unknownAt < 0 || r.unknownAt >= c.futureFrom);
    if (!ok) return false;
    if (plan.branchOut && r.branchSaved && !canContinue(c, plan.branchOut, c.depth, c.thorough)) return false;
    float clear = std::min(r.clearance, kClearCap);
    if (!best.ok || clear > best.clearance) {
        best.ok = true;
        best.clearance = clear;
    }
    if (r.resolved) best.resolved = true;
    if (r.landed && !best.haveLanding) {
        best.haveLanding = true;
        best.landObject = r.landObject;
        best.landY = r.landY;
    }
    best.survivors++;
    return !score || best.survivors >= 3;
}

SimPlan basePlan(EvalContext const& c) {
    SimPlan p;
    p.events = c.pending;
    if (c.depth > 0) {
        p.branchOut = g.branches[kTopBranch].data();
        if (!isLandMode(c.mode)) p.branchAtEnd = true;
    }
    return p;
}

int depthFor(Config const& cfg, Mode m) {
    return isLandMode(m) ? cfg.planAhead : cfg.planAhead - 1;
}

void runPressPlan(EvalContext const& c, SimPlan& p, int rel, int releaseAt, bool score, Outcome& best, bool& probeDone, bool& stop) {
    bool probe = c.wantProbe && !probeDone && rel == std::max(rel, c.futureFrom) && releaseAt - rel >= 4;
    if (probe) p.captureAt = rel + std::min(6, releaseAt - rel - 2);
    int before = best.survivors;
    stop = considerRun(c, p, score, best, rel);
    if (probe && best.survivors > before && g.runCaptured) {
        CCPoint predicted = g.runCapturePos;
        probeDone = true;
        armProbe(c, p, rel, predicted);
    }
}

Outcome evalPress(EvalContext const& c, int rel, bool score) {
    Mode m = c.mode;
    int anchor = std::max(rel, c.futureFrom);
    Outcome best;
    bool probeDone = false;
    bool stop = false;

    if (isHoldMode(m) || m == Mode::Robot) {
        for (int h : holdOptions(m)) {
            SimPlan p = basePlan(c);
            p.events.push_back({ rel, true });
            p.events.push_back({ anchor + h, false });
            if (m == Mode::Robot) {
                p.length = anchor + std::max(c.cfg->lookahead, kLandCap);
                p.watchFrom = rel;
                p.branchAtLanding = true;
            }
            else {
                p.length = anchor + std::min(c.cfg->lookahead, h + kAfterRelease);
            }
            runPressPlan(c, p, rel, anchor + h, score, best, probeDone, stop);
            if (stop || best.idleDeath) break;
        }
        return best;
    }

    if (isLandMode(m)) {
        int h = holdTicks(m);
        int cap = std::max(c.cfg->lookahead, kLandCap);
        SimPlan p = basePlan(c);
        p.events.push_back({ rel, true });
        p.events.push_back({ anchor + h, false });
        p.length = anchor + cap;
        p.watchFrom = rel;
        p.branchAtLanding = true;
        runPressPlan(c, p, rel, anchor + h, score, best, probeDone, stop);
        return best;
    }

    int tap = std::min(holdTicks(m), 5);
    int quiet = m == Mode::Spider ? 14 : 28;
    for (int gp : nextPressOptions(m, tap + 2)) {
        SimPlan p = basePlan(c);
        p.events.push_back({ rel, true });
        p.events.push_back({ anchor + tap, false });
        if (gp > 0) {
            p.events.push_back({ anchor + gp, true });
            p.events.push_back({ anchor + gp + 2, false });
            p.length = anchor + std::min(c.cfg->lookahead, gp + kAfterPress + 4);
        }
        else {
            p.length = anchor + std::min(c.cfg->lookahead, quiet);
        }
        runPressPlan(c, p, rel, anchor + tap, score, best, probeDone, stop);
        if (stop || best.idleDeath) break;
    }
    return best;
}

Outcome evalRelease(EvalContext const& c, int rel, bool score) {
    Mode m = c.mode;
    int anchor = std::max(rel, c.futureFrom);
    Outcome best;

    if (m == Mode::Robot || !isHoldMode(m)) {
        SimPlan p = basePlan(c);
        p.events.push_back({ rel, false });
        p.length = anchor + std::max(c.cfg->lookahead, kLandCap);
        p.watchFrom = rel;
        p.branchAtLanding = true;
        considerRun(c, p, score, best, rel);
        return best;
    }

    for (int gp : nextPressOptions(m, 2)) {
        SimPlan p = basePlan(c);
        p.events.push_back({ rel, false });
        if (gp > 0) {
            p.events.push_back({ anchor + gp, true });
            p.length = anchor + std::min(c.cfg->lookahead, gp + kAfterPress);
        }
        else {
            p.length = anchor + std::min(c.cfg->lookahead, 10);
        }
        if (considerRun(c, p, score, best, rel) || best.idleDeath) break;
    }
    return best;
}

std::vector<SimEvent> pendingEvents(Channel const& ch, int now) {
    std::vector<SimEvent> out;
    out.reserve(ch.queue.size() + 2);
    for (auto const& q : ch.queue) out.push_back({ std::max(0, q.tick - now), q.down });
    return out;
}

int lastQueuedTick(Channel const& ch, int now) {
    return ch.queue.empty() ? now : std::max(now, ch.queue.back().tick);
}

EvalContext liveContext(PlayLayer* pl, Targets const& t, Channel const& ch, int now, Config const& cfg) {
    captureLive(t);
    EvalContext c;
    c.pl = pl;
    c.targets = &t;
    c.sources[0] = &g.live[0];
    c.sources[1] = &g.live[1];
    c.pending = pendingEvents(ch, now);
    c.mode = modeOf(t.players[0]);
    c.cfg = &cfg;
    c.depth = depthFor(cfg, c.mode);
    c.futureFrom = 0;
    return c;
}

bool sameLanding(Outcome const& a, Outcome const& b) {
    if (!a.haveLanding || !b.haveLanding) return false;
    if (a.landObject || b.landObject) return a.landObject == b.landObject;
    return std::abs(a.landY - b.landY) < 2.f;
}

template <class Eval>
Choice chooseTick(int now, int preferred, int lo, int hi, bool landMode, Eval&& eval) {
    Choice choice;
    choice.tick = preferred;
    auto first = eval(preferred - now, true);
    choice.firstOk = first.ok;
    float riskLine = landMode ? kRiskClearLand : kRiskClear;
    if (first.ok && (first.aborted || first.clearance >= riskLine || !first.resolved)) return choice;

    auto search = [&](int a, int b, auto&& accept, int& outTick) {
        bool found = false;
        float bestScore = -1e9f;
        int span = std::max(preferred - a, b - preferred);
        bool stopSide[2] = { false, false };
        for (int d = 1; d <= span && !outOfTime(); d++) {
            for (int side = 0; side < 2; side++) {
                if (stopSide[side]) continue;
                int t = side == 0 ? preferred + d : preferred - d;
                if (t < a || t > b) continue;
                auto o = eval(t - now, true);
                if (o.aborted) break;
                if (o.idleDeath && side == 0) stopSide[0] = true;
                if (!accept(o)) continue;
                float score = o.clearance + static_cast<float>(o.survivors) + (o.resolved ? 5.f : 0.f) - kShiftPenalty * d;
                if (!found || score > bestScore) {
                    found = true;
                    bestScore = score;
                    outTick = t;
                }
            }
            if (found && landMode) break;
        }
        return found;
    };

    int picked = preferred;
    if (first.ok) {
        auto safer = [&](Outcome const& o) {
            if (!o.ok || !o.resolved || o.clearance < first.clearance + kRiskGain) return false;
            if (first.haveLanding && !sameLanding(first, o)) return false;
            return true;
        };
        if (search(lo, hi, safer, picked)) choice.tick = picked;
        return choice;
    }

    auto alive = [](Outcome const& o) { return o.ok; };
    if (search(lo, hi, alive, picked) || search(hi + 1, hi + kRescue, alive, picked)) {
        choice.tick = picked;
        return choice;
    }
    choice.found = false;
    return choice;
}

Choice choosePress(PlayLayer* pl, Targets const& t, Channel const& ch, int now, Config const& cfg) {
    auto c = liveContext(pl, t, ch, now, cfg);
    c.wantProbe = true;
    c.thorough = true;
    int base = lastQueuedTick(ch, now);
    int preferred = base + leadFor(cfg, c.mode);
    int hi = preferred + maxDelayFor(cfg, c.mode);
    bool nearest = isLandMode(c.mode);
    return chooseTick(now, preferred, base, hi, nearest, [&](int rel, bool score) {
        auto o = evalPress(c, rel, score);
        c.wantProbe = false;
        c.thorough = false;
        return o;
    });
}

Choice chooseRelease(PlayLayer* pl, Targets const& t, Channel const& ch, int now, int target, Config const& cfg) {
    Mode m = modeOf(t.players[0]);
    if (!cfg.releaseAssist || !releaseMatters(m)) return Choice{ target, true, true };
    auto c = liveContext(pl, t, ch, now, cfg);
    c.thorough = true;
    int lo = std::max(lastQueuedTick(ch, now), ch.firePressTick + 1);
    lo = std::min(lo, target);
    int hi = target + maxDelayFor(cfg, m);
    return chooseTick(now, target, lo, hi, m == Mode::Robot, [&](int rel, bool score) {
        auto o = evalRelease(c, rel, score);
        c.thorough = false;
        return o;
    });
}

int pickLateTicks(PlayLayer* pl, Targets const& t, Channel const& ch, int now, bool press, Config const& cfg) {
    if (!cfg.smart || !g.smartOn || !ch.queue.empty()) return 0;
    EvalContext c;
    c.pl = pl;
    c.targets = &t;
    c.mode = modeOf(t.players[0]);
    c.cfg = &cfg;
    c.depth = depthFor(cfg, c.mode);
    c.noOffset = true;
    CCPoint current = t.players[0]->getPosition();

    for (int j = 1; j <= cfg.smartWindow && !outOfTime(); j++) {
        int u = now - j;
        if (u < g.lastAnyInput) break;
        bool usable = true;
        for (int i = 0; i < t.count && usable; i++) {
            auto p = t.players[i];
            auto const& snap = g.ring[playerIndex(pl, p)][ringSlot(u)];
            if (snap.tick != u || snap.isDead || snap.isDashing || snap.touchingRing
                || modeOf(snap) != modeOf(p)
                || snap.m_isUpsideDown != p->m_isUpsideDown
                || snap.m_vehicleSize != p->m_vehicleSize
                || snap.m_playerSpeed != p->m_playerSpeed
                || snap.m_isGoingLeft != p->m_isGoingLeft
                || snap.m_isSideways != p->m_isSideways) {
                usable = false;
            }
            c.sources[i] = &snap;
        }
        if (!usable) break;

        SimPlan reach;
        reach.events.push_back({ 0, press });
        reach.length = j;
        reach.captureAt = j - 1;
        reach.noOffset = true;
        runSim(pl, t.count, c.sources, reach);
        if (!g.captured || ccpDistance(g.capturePos, current) > kMaxSnap) break;

        c.futureFrom = j;
        auto o = press ? evalPress(c, 0, false) : evalRelease(c, 0, false);
        if (o.aborted) break;
        if (o.ok) return j;
    }
    return 0;
}

void applySmooth(Smooth& s) {
    auto p = s.player;
    if (!p || !p->m_mainLayer || !p->getParent()) return;
    auto parent = p->getParent();
    CCPoint cur = p->getPosition();
    CCPoint a = p->convertToNodeSpace(parent->convertToWorldSpace(cur));
    CCPoint b = p->convertToNodeSpace(parent->convertToWorldSpace(cur + s.offset));
    p->m_mainLayer->setPosition(s.basePosition + (b - a));
    float sign = p->getScaleX() * p->getScaleY() < 0.f ? -1.f : 1.f;
    p->m_mainLayer->setRotation(s.baseRotation + s.rotation * sign);
}

void endSmooth(Smooth& s) {
    if (s.active && s.player && s.player->m_mainLayer) {
        s.player->m_mainLayer->setPosition(s.basePosition);
        s.player->m_mainLayer->setRotation(s.baseRotation);
    }
    s = Smooth();
}

void endAllSmooth(bool restore) {
    for (auto& s : g.smooth) {
        if (restore) endSmooth(s);
        else s = Smooth();
    }
}

void tickSmooth(float dt) {
    float keep = std::exp(-std::max(dt, 0.f) / kSmoothTime);
    for (auto& s : g.smooth) {
        if (!s.active) continue;
        s.offset = s.offset * keep;
        s.rotation *= keep;
        if (ccpLength(s.offset) < 0.25f && std::abs(s.rotation) < 0.5f) {
            endSmooth(s);
            continue;
        }
        applySmooth(s);
    }
}

void applyLate(PlayLayer* pl, Targets const& t, int j, bool down, bool isPlayer1) {
    int u = g.updates - j;
    CCPoint oldPos[2];
    float oldRot[2] = { 0.f, 0.f };
    for (int i = 0; i < t.count; i++) {
        oldPos[i] = t.players[i]->getPosition();
        oldRot[i] = t.players[i]->getRotation();
        load(t.players[i], g.ring[playerIndex(pl, t.players[i])][ringSlot(u)], false);
    }

    g.dispatching = true;
    pl->handleButton(down, static_cast<int>(PlayerButton::Jump), isPlayer1);
    g.dispatching = false;

    float dt = g.stepDt > 0.f ? g.stepDt : 0.25f;
    g.catchingUp = true;
    for (int n = 0; n < j; n++) {
        for (int i = 0; i < t.count; i++) {
            auto p = t.players[i];
            if (p->m_isDead) continue;
            clearLogs(p);
            p->update(dt);
            pl->checkCollisions(p, dt, false);
            if (!p->m_isDead) p->updateRotation(dt);
        }
    }
    g.catchingUp = false;
    g.lastAnyInput = g.updates;

    for (int i = 0; i < t.count; i++) {
        auto p = t.players[i];
        if (!p->m_mainLayer || p->m_isDead) continue;
        auto& s = g.smooth[playerIndex(pl, p)];
        if (!s.active) {
            s.basePosition = p->m_mainLayer->getPosition();
            s.baseRotation = p->m_mainLayer->getRotation();
        }
        s.active = true;
        s.player = p;
        s.offset = s.offset + (oldPos[i] - p->getPosition());
        s.rotation = normalizeAngle(s.rotation + normalizeAngle(oldRot[i] - p->getRotation()));
        applySmooth(s);
    }
}

void takeSnapshots(PlayLayer* pl) {
    int slot = ringSlot(g.updates);
    save(g.ring[0][slot], pl->m_player1, false);
    g.ring[0][slot].tick = g.updates;
    if (pl->m_player2 && pl->m_gameState.m_isDualMode) {
        save(g.ring[1][slot], pl->m_player2, false);
        g.ring[1][slot].tick = g.updates;
    }
}

ccColor4F rgba(float r, float gr, float b, float a) {
    return ccc4f(r, gr, b, a);
}

void drawRotatedRect(CCDrawNode* node, CCRect const& rect, float rotation, ccColor4F fill, ccColor4F line, float width) {
    CCPoint center = ccp(rect.getMidX(), rect.getMidY());
    CCPoint corners[4] = {
        ccp(rect.getMinX(), rect.getMaxY()),
        ccp(rect.getMaxX(), rect.getMaxY()),
        ccp(rect.getMaxX(), rect.getMinY()),
        ccp(rect.getMinX(), rect.getMinY())
    };
    float angle = CC_DEGREES_TO_RADIANS(-rotation);
    float cs = std::cos(angle);
    float sn = std::sin(angle);
    for (auto& v : corners) {
        float x = v.x - center.x;
        float y = v.y - center.y;
        v = ccp(center.x + x * cs - y * sn, center.y + x * sn + y * cs);
    }
    node->drawPolygon(corners, 4, fill, width, line);
}

void drawRecord(CCDrawNode* node, SimRecord const& rec, int count, ccColor4F color) {
    for (int i = 0; i < count; i++) {
        auto const& path = rec.path[i];
        for (size_t k = 1; k < path.size(); k++) {
            node->drawSegment(path[k - 1], path[k], 0.6f, color);
        }
    }
    if (rec.died) {
        drawRotatedRect(node, rec.outer, rec.rotation, rgba(1.f, 0.f, 0.f, 0.15f), rgba(1.f, 0.1f, 0.1f, 0.9f), 0.5f);
        drawRotatedRect(node, rec.inner, 0.f, rgba(0.f, 0.3f, 1.f, 0.15f), rgba(0.1f, 0.4f, 1.f, 0.9f), 0.4f);
    }
}

void showIndicator(std::string const& text) {
    if (!g.label || !g.ready) return;
    g.label->setString(text.c_str());
    g.label->stopAllActions();
    g.label->setOpacity(220);
    g.label->runAction(CCSequence::create(CCDelayTime::create(0.8f), CCFadeOut::create(0.4f), nullptr));
}

void drawDecision(PlayLayer* pl, Targets const& t, Channel const& ch, int now, Config const& cfg, int userTick, int chosenTick, bool press) {
    if (!g.decisionDraw) return;
    Budget budget(cfg.budgetMs);
    auto c = liveContext(pl, t, ch, now, cfg);
    Mode m = c.mode;
    int h = holdTicks(m);
    auto plan = [&](int tick, SimRecord* rec) {
        SimPlan p = basePlan(c);
        int rel = tick - now;
        if (press) {
            p.events.push_back({ rel, true });
            p.events.push_back({ rel + h, false });
        }
        else {
            p.events.push_back({ rel, false });
        }
        p.length = rel + std::max(cfg.lookahead, 120);
        p.record = rec;
        return p;
    };
    SimRecord original;
    SimRecord chosen;
    runSim(pl, t.count, c.sources, plan(userTick, &original));
    runSim(pl, t.count, c.sources, plan(chosenTick, &chosen));
    g.decisionDraw->clear();
    drawRecord(g.decisionDraw, original, t.count, rgba(1.f, 0.45f, 0.2f, 0.85f));
    drawRecord(g.decisionDraw, chosen, t.count, rgba(1.f, 0.95f, 0.2f, 0.95f));
    g.decisionDraw->stopAllActions();
    g.decisionDraw->setVisible(true);
    g.decisionDraw->runAction(CCSequence::create(CCDelayTime::create(1.2f), CCHide::create(), nullptr));
}

void drawLiveProjection(PlayLayer* pl) {
    if (!g.liveDraw) return;
    g.liveDraw->clear();
    if (!g.debugOn || g.untrusted || inStartGrace()) return;
    auto p1 = pl->m_player1;
    if (!p1 || p1->m_isDead || pl->m_playerDied || pl->m_levelEndAnimationStarted) return;

    auto cfg = readConfig();
    Budget budget(cfg.budgetMs);
    auto t = targetsFor(pl, true);
    captureLive(t);
    Snapshot const* sources[2] = { &g.live[0], &g.live[1] };
    int length = std::max(cfg.lookahead, 120);

    auto it = p1->m_holdingButtons.find(static_cast<int>(PlayerButton::Jump));
    bool holding = it != p1->m_holdingButtons.end() && it->second;

    SimRecord holdRec;
    SimPlan holdPlan;
    if (!holding) holdPlan.events.push_back({ 0, true });
    holdPlan.length = length;
    holdPlan.record = &holdRec;
    runSim(pl, t.count, sources, holdPlan);

    SimRecord freeRec;
    SimPlan freePlan;
    if (holding) freePlan.events.push_back({ 0, false });
    freePlan.length = length;
    freePlan.record = &freeRec;
    runSim(pl, t.count, sources, freePlan);

    drawRecord(g.liveDraw, holdRec, t.count, rgba(0.25f, 0.95f, 0.45f, 0.9f));
    drawRecord(g.liveDraw, freeRec, t.count, rgba(0.25f, 0.85f, 1.f, 0.9f));
}

void resetChannels() {
    for (auto& ch : g.channels) ch = Channel();
}

void sendButton(GJBaseGameLayer* layer, bool down, bool isPlayer1) {
    g.dispatching = true;
    layer->handleButton(down, static_cast<int>(PlayerButton::Jump), isPlayer1);
    g.dispatching = false;
}

void dispatch(GJBaseGameLayer* layer, Channel& ch, Queued const& q) {
    if (q.down && q.main && ch.held && q.origin == ch.pressTick) {
        ch.shift = std::max(0, g.updates - ch.pressTick);
        ch.firePressTick = g.updates;
    }
    sendButton(layer, q.down, q.isPlayer1);
}

void showDiag(PlayLayer* pl, bool completed) {
    if (!g.diagLabel || g.diagOwner != pl) return;
    std::vector<std::string> names(g.simTouched.begin(), g.simTouched.end());
    std::string touched;
    for (size_t i = 0; i < names.size(); i++) {
        if (i > 0) touched += (i % 3 == 0) ? ",\n  " : ", ";
        touched += names[i];
    }
    if (touched.empty()) touched = "nothing";
    bool verified = completed ? pl->m_damageVerified : g.deathVerified;
    bool integrity = completed ? pl->m_passedIntegrity : g.deathIntegrity;
    bool testMode = completed ? pl->m_isTestMode : g.deathTestMode;
    bool practice = completed ? pl->m_isPracticeMode : g.deathPractice;
    bool platformer = completed ? pl->m_isPlatformer : g.diedPlatformer;
    int bestNow = pl->m_level ? pl->m_level->m_normalPercent.value() : 0;
    std::string save;
    if (!g.saveCalled) save = "save not called";
    else if (g.saveBlocked) save = fmt::format("save {}% blocked by safe mode", g.savePercent);
    else save = fmt::format("save {}% chk {}", g.savePercent, g.saveChk ? 1 : 0);
    std::string text = fmt::format(
        "mod {} | died at {}% | best before {}% now {}%\n{}\nverified {} integrity {} test {} practice {} platformer {}\nsafe mode {} moved input {}\nchanged: {}",
        layerReady(pl) ? "on" : "off", g.diedAt, g.bestBefore, bestNow, save,
        verified ? 1 : 0, integrity ? 1 : 0, testMode ? 1 : 0, practice ? 1 : 0, platformer ? 1 : 0,
        Mod::get()->getSettingValue<bool>("safe-mode") ? "on" : "off", g.diedMoved ? "yes" : "no", touched);
    log::info("save check: {}", text);
    g.diagLabel->stopAllActions();
    g.diagLabel->setString(text.c_str());
    g.diagLabel->setOpacity(230);
    g.diagLabel->runAction(CCSequence::create(CCDelayTime::create(8.f), CCFadeOut::create(0.5f), nullptr));
}

void report(Config const& cfg, bool changed, std::string const& text) {
    if (changed) g.changedThisAttempt = true;
    if ((cfg.debug || (cfg.indicator && changed)) && !text.empty()) showIndicator(text);
}

void processAdjust(GJBaseGameLayer* layer, PlayLayer* pl) {
    for (auto& ch : g.channels) {
        if (!ch.adjusting) continue;
        auto cfg = readConfig();
        auto t = targetsFor(pl, ch.adjustIsPlayer1);
        bool release = !t.players[0] || !canAssist(pl, t) || g.updates >= ch.adjustDeadline || modeOf(t.players[0]) != Mode::Wave;
        if (!release) {
            Budget budget(cfg.budgetMs);
            auto c = liveContext(pl, t, ch, g.updates, cfg);
            auto o = evalRelease(c, 0, true);
            release = o.ok && !o.aborted && o.clearance >= kRiskClear;
        }
        if (!release) continue;
        ch.adjusting = false;
        sendButton(layer, false, ch.adjustIsPlayer1);
        report(cfg, true, fmt::format("wave adjust +{}ms", ticksToMs(g.updates - ch.adjustStart)));
    }
}

void firePending(GJBaseGameLayer* layer, PlayLayer* pl) {
    for (auto& ch : g.channels) {
        while (!ch.queue.empty()) {
            Queued q = ch.queue.front();
            bool due = q.tick <= g.updates;
            if (!due && q.down) {
                auto t = targetsFor(pl, q.isPlayer1);
                for (int i = 0; i < t.count; i++) {
                    if (touchingRing(t.players[i])) due = true;
                }
            }
            if (!due) break;
            ch.queue.pop_front();
            dispatch(layer, ch, q);
        }
    }
}

void flushAll(GJBaseGameLayer* layer) {
    for (auto& ch : g.channels) {
        while (!ch.queue.empty()) {
            Queued q = ch.queue.front();
            ch.queue.pop_front();
            dispatch(layer, ch, q);
        }
        if (ch.adjusting) {
            ch.adjusting = false;
            sendButton(layer, false, ch.adjustIsPlayer1);
        }
        ch.shift = 0;
        ch.held = false;
    }
}

void checkProbe(PlayerObject* real) {
    if (!g.probe.active || g.updates != g.probe.compareAt) return;
    g.probe.active = false;
    if (real != g.probe.player) return;
    auto pos = real->getPosition();
    float dist[3] = { 1e9f, 1e9f, 1e9f };
    int bestIndex = 1;
    for (int i = 0; i < 3; i++) {
        if (!g.probe.valid[i]) continue;
        auto const& p = g.probe.predicted[i];
        dist[i] = std::abs(pos.x - p.x) + std::abs(pos.y - p.y);
        if (dist[i] < dist[bestIndex]) bestIndex = i;
    }
    float best = dist[bestIndex];

    if (best < 0.75f && (bestIndex == 1 || dist[1] > 1.5f)) {
        g.votes[bestIndex]++;
        int total = g.votes[0] + g.votes[1] + g.votes[2];
        if (total >= 6) {
            int shift = 0;
            if (g.votes[0] >= 5) shift = -1;
            if (g.votes[2] >= 5) shift = 1;
            if (shift != 0) {
                g.inputOffset = std::clamp(g.inputOffset + shift, -2, 2);
                log::info("timing calibrated, input offset is now {}", g.inputOffset);
                Mod::get()->setSavedValue<int64_t>("input-offset", g.inputOffset);
            }
            g.votes = {};
        }
    }

    if (best > 1.5f) {
        g.mismatch += 2;
        log::debug("prediction off by {:.2f} units", best);
    }
    else if (g.mismatch > 0) {
        g.mismatch--;
    }
    if (g.mismatch >= 6 && !g.untrusted) {
        g.untrusted = true;
        log::warn("predictions don't match the game here, pausing the assist until the next attempt");
        showIndicator("assist paused");
    }
}

bool shouldBlockProgress() {
    return g.changedThisAttempt && Mod::get()->getSettingValue<bool>("safe-mode");
}

}

$on_mod(Loaded) {
    g.hold.fill(20.0);
    g.gap.fill(30.0);
    g.hold[static_cast<int>(Mode::Wave)] = 10.0;
    g.gap[static_cast<int>(Mode::Wave)] = 10.0;
    auto mod = Mod::get();
    g.inputOffset = static_cast<int>(std::clamp<int64_t>(mod->getSavedValue<int64_t>("input-offset", 0), -2, 2));
    g.smartOn = mod->getSettingValue<bool>("smart-predict");
    g.debugOn = mod->getSettingValue<bool>("debug-overlay");
    g.orbSim = mod->getSettingValue<bool>("simulate-orbs");
    listenForSettingChanges<bool>("smart-predict", [](bool value) {
        g.smartOn = value;
        clearRing();
    });
    listenForSettingChanges<bool>("debug-overlay", [](bool value) {
        g.debugOn = value;
        if (g.liveDraw && !value) g.liveDraw->clear();
    });
    listenForSettingChanges<bool>("simulate-orbs", [](bool value) {
        g.orbSim = value;
    });
}

class $modify(TABaseLayer, GJBaseGameLayer) {
    static void onModify(auto& self) {
        (void)self.setHookPriority("GJBaseGameLayer::handleButton", Priority::VeryEarly);
    }

    void processQueuedButtons(float dt, bool clearInputQueue) {
        bool prev = g.inQueue;
        g.inQueue = true;
        GJBaseGameLayer::processQueuedButtons(dt, clearInputQueue);
        g.inQueue = prev;
    }

    void processCommands(float dt, bool isHalfTick, bool isLastTick) {
        auto pl = PlayLayer::get();
        if (!layerReady(pl) || static_cast<GJBaseGameLayer*>(pl) != this) {
            GJBaseGameLayer::processCommands(dt, isHalfTick, isLastTick);
            return;
        }
        processAdjust(this, pl);
        firePending(this, pl);
        bool prev = g.inCommands;
        g.inCommands = true;
        GJBaseGameLayer::processCommands(dt, isHalfTick, isLastTick);
        g.inCommands = prev;
    }

    void handleButton(bool down, int button, bool isPlayer1) {
        auto pl = PlayLayer::get();
        if (g.dispatching || !(g.inQueue || g.inCommands) || g.simulating || g.catchingUp
            || button != static_cast<int>(PlayerButton::Jump)
            || !layerReady(pl) || static_cast<GJBaseGameLayer*>(pl) != this) {
            if (!g.simulating && !g.catchingUp) g.lastAnyInput = g.updates;
            GJBaseGameLayer::handleButton(down, button, isPlayer1);
            return;
        }

        auto targets = targetsFor(pl, isPlayer1);
        if (!targets.players[0]) {
            g.lastAnyInput = g.updates;
            GJBaseGameLayer::handleButton(down, button, isPlayer1);
            return;
        }
        auto cfg = readConfig();
        auto& ch = g.channels[targets.channel];
        int now = g.updates;
        g.probe.active = false;

        auto send = [&](int tick, bool main) {
            if (ch.queue.empty() && tick <= now) {
                if (down && main) {
                    ch.shift = 0;
                    ch.firePressTick = now;
                }
                g.lastAnyInput = now;
                GJBaseGameLayer::handleButton(down, button, isPlayer1);
            }
            else {
                ch.queue.push_back({ std::max(tick, now), down, isPlayer1, main, ch.pressTick });
            }
        };

        if (down) {
            if (ch.adjusting) {
                ch.adjusting = false;
                ch.held = true;
                ch.pressTick = now;
                ch.shift = 0;
                report(cfg, true, "wave adjust: kept holding");
                return;
            }
            if (ch.held) {
                send(lastQueuedTick(ch, now), false);
                return;
            }
            Mode m = modeOf(targets.players[0]);
            if (ch.releaseTick != kNoTick && ch.mode == m) {
                int sample = now - ch.releaseTick;
                if (sample > 0 && sample < 240) learn(g.gap[idx(m)], sample);
            }
            ch.held = true;
            ch.mode = m;
            ch.pressTick = now;

            int natural = lastQueuedTick(ch, now);
            Choice choice{ natural, true, true };
            bool assist = cfg.enabled && canAssist(pl, targets);
            int preferred = natural;
            int late = 0;
            {
                Budget budget(cfg.budgetMs);
                if (assist) {
                    preferred = natural + leadFor(cfg, m);
                    choice = choosePress(pl, targets, ch, now, cfg);
                }
                if (assist && !choice.found && natural == now) {
                    late = pickLateTicks(pl, targets, ch, now, true, cfg);
                }
            }

            if (late > 0) {
                applyLate(pl, targets, late, true, isPlayer1);
                ch.shift = 0;
                ch.firePressTick = now - late;
                report(cfg, true, fmt::format("{} late fix -{}ms", modeName(m), ticksToMs(late)));
                return;
            }

            bool moved = choice.tick != preferred;
            if (moved) g.probe.active = false;
            if (assist && cfg.debug && moved) drawDecision(pl, targets, ch, now, cfg, preferred, choice.tick, true);
            ch.shift = std::max(0, choice.tick - now);
            ch.firePressTick = choice.tick;
            if (assist) {
                std::string text;
                if (moved) text = fmt::format("{} press {:+}ms", modeName(m), ticksToMs(choice.tick - preferred));
                else if (!choice.found) text = fmt::format("{} press: no safe tick", modeName(m));
                else if (cfg.debug) text = fmt::format("{} press ok", modeName(m));
                report(cfg, moved, text);
            }
            send(choice.tick, true);
            return;
        }

        if (!ch.held) {
            send(lastQueuedTick(ch, now), false);
            return;
        }
        ch.held = false;
        int sample = now - ch.pressTick;
        if (sample > 0 && sample < 240) learn(g.hold[idx(ch.mode)], sample);
        ch.releaseTick = now;

        int natural = lastQueuedTick(ch, now);
        int target = natural;
        if (cfg.enabled && cfg.keepHold) target = std::max(target, now + ch.shift);
        Choice choice{ target, true, true };
        bool assist = cfg.enabled && canAssist(pl, targets);
        Mode m = modeOf(targets.players[0]);
        int late = 0;
        {
            Budget budget(cfg.budgetMs);
            if (assist) choice = chooseRelease(pl, targets, ch, now, target, cfg);
            if (assist && !choice.found && target == now && natural == now) {
                late = pickLateTicks(pl, targets, ch, now, false, cfg);
            }
        }
        if (late > 0) {
            applyLate(pl, targets, late, false, isPlayer1);
            ch.shift = 0;
            report(cfg, true, fmt::format("{} late release -{}ms", modeName(m), ticksToMs(late)));
            return;
        }

        bool earlierFix = choice.found && choice.tick <= target;
        if (assist && cfg.adjust && m == Mode::Wave && !choice.firstOk && !earlierFix && natural == now && ch.queue.empty()) {
            ch.adjusting = true;
            ch.adjustIsPlayer1 = isPlayer1;
            ch.adjustStart = now;
            ch.adjustDeadline = now + cfg.adjustMax;
            ch.shift = 0;
            report(cfg, true, "wave adjust: holding");
            return;
        }

        bool moved = choice.tick != target;
        if (assist && cfg.debug && moved) drawDecision(pl, targets, ch, now, cfg, target, choice.tick, false);
        if (assist && releaseMatters(m)) {
            std::string text;
            if (moved) text = fmt::format("{} release {:+}ms", modeName(m), ticksToMs(choice.tick - target));
            else if (!choice.found) text = fmt::format("{} release: no safe tick", modeName(m));
            else if (cfg.debug) text = fmt::format("{} release ok", modeName(m));
            report(cfg, moved, text);
        }
        send(choice.tick, true);
        ch.shift = 0;
    }

    void collisionCheckObjects(PlayerObject* player, gd::vector<GameObject*>* objects, int objectCount, float dt) {
        if (!g.simulating || !objects || !player) {
            GJBaseGameLayer::collisionCheckObjects(player, objects, objectCount, dt);
            return;
        }

        std::vector<GameObject*> off;
        off.reserve(32);
        CCRect body = player->getObjectRect();
        CCRect reach = body;
        reach.origin.x -= 6.f;
        reach.origin.y -= 6.f;
        reach.size.width += 12.f;
        reach.size.height += 12.f;
        bool goingLeft = player->m_isGoingLeft;

        int n = std::min(objectCount, static_cast<int>(objects->size()));
        for (int i = 0; i < n; i++) {
            auto obj = (*objects)[i];
            if (!obj) continue;
            if (obj == m_anticheatSpike) {
                if (!obj->m_isDisabled && !obj->m_isDisabled2) {
                    obj->m_isDisabled = true;
                    obj->m_isDisabled2 = true;
                    off.push_back(obj);
                }
                continue;
            }
            if (simulatedSpecial(obj)) continue;
            if (keepInSim(obj->m_objectType) && !isCollectibleId(obj->m_objectID)) {
                if (!g.trackClearance || obj->m_isDisabled || obj->m_isDisabled2) continue;
                auto type = obj->m_objectType;
                CCRect const& r = obj->getObjectRect();
                if (type == GameObjectType::Hazard || type == GameObjectType::AnimatedHazard) {
                    g.simClearance = std::min(g.simClearance, rectGap(body, r));
                }
                else if (type == GameObjectType::Solid && r.getMinY() < body.getMaxY() - 1.f && r.getMaxY() > body.getMinY() + 1.f) {
                    float ahead = goingLeft ? body.getMinX() - r.getMaxX() : r.getMinX() - body.getMaxX();
                    if (ahead >= -1.f) g.simClearance = std::min(g.simClearance, std::max(0.f, ahead));
                }
                continue;
            }
            if (obj->m_isDisabled || obj->m_isDisabled2) continue;
            if (isInteractive(obj) && reach.intersectsRect(obj->getObjectRect())) g.simUnknown = true;
            obj->m_isDisabled = true;
            obj->m_isDisabled2 = true;
            off.push_back(obj);
        }

        GJBaseGameLayer::collisionCheckObjects(player, objects, objectCount, dt);

        for (auto obj : off) {
            obj->m_isDisabled = false;
            obj->m_isDisabled2 = false;
        }
    }

    void playerTouchedRing(PlayerObject* player, RingObject* object) {
        if (g.simulating && !simulatedSpecial(object)) return;
        GJBaseGameLayer::playerTouchedRing(player, object);
    }

    void playerTouchedTrigger(PlayerObject* player, EffectGameObject* object) {
        if (g.simulating) return;
        GJBaseGameLayer::playerTouchedTrigger(player, object);
    }

    bool canBeActivatedByPlayer(PlayerObject* player, EffectGameObject* object) {
        if (g.simulating && !simulatedSpecial(object)) return false;
        return GJBaseGameLayer::canBeActivatedByPlayer(player, object);
    }

    void gameEventTriggered(GJGameEvent event, int material, int playerID) {
        if (g.simulating) return;
        GJBaseGameLayer::gameEventTriggered(event, material, playerID);
    }

    void activateSFXTrigger(SFXTriggerGameObject* object) {
        if (g.simulating) return;
        GJBaseGameLayer::activateSFXTrigger(object);
    }

    void activateSongEditTrigger(SongTriggerGameObject* object) {
        if (g.simulating) return;
        GJBaseGameLayer::activateSongEditTrigger(object);
    }

    void bumpPlayer(PlayerObject* player, EffectGameObject* object) {
        if (g.simulating && !simulatedSpecial(object)) {
            g.simUnknown = true;
            return;
        }
        GJBaseGameLayer::bumpPlayer(player, object);
    }

    void teleportPlayer(TeleportPortalObject* object, PlayerObject* player) {
        if (g.simulating) {
            g.simUnknown = true;
            return;
        }
        GJBaseGameLayer::teleportPlayer(object, player);
    }
};

class $modify(TAPlayLayer, PlayLayer) {
    static void onModify(auto& self) {
        (void)self.setHookPriority("PlayLayer::destroyPlayer", Priority::First);
    }

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        g.ready = false;
        g.layer = nullptr;
        g.fakes[0] = nullptr;
        g.fakes[1] = nullptr;
        g.label = nullptr;
        g.diagLabel = nullptr;
        g.diagOwner = nullptr;
        g.liveDraw = nullptr;
        g.decisionDraw = nullptr;
        g.simulating = false;
        g.catchingUp = false;
        g.changedThisAttempt = false;
        g.probe.active = false;
        g.mismatch = 0;
        g.untrusted = false;
        g.lastAnyInput = g.updates;
        g.votes = {};
        endAllSmooth(false);
        clearRing();
        resetChannels();
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        if (Mod::get()->getSettingValue<bool>("enabled")) m_clickBetweenSteps = false;
        return true;
    }

    void setupHasCompleted() {
        PlayLayer::setupHasCompleted();
        g.attemptStart = g.updates;
        g.diagOwner = this;
        g.diagDeath = false;
        g.saveCalled = false;
        g.saveBlocked = false;
        g.simTouched.clear();
        g.diagLabel = nullptr;
        if (Mod::get()->getSettingValue<bool>("debug-overlay")) {
            auto diag = CCLabelBMFont::create("", "bigFont.fnt");
            diag->setAnchorPoint({ 0.f, 0.f });
            diag->setScale(0.28f);
            diag->setPosition({ 6.f, 22.f });
            diag->setOpacity(0);
            this->addChild(diag, 1000);
            g.diagLabel = diag;
        }
        if (!Mod::get()->getSettingValue<bool>("enabled")) return;

        int* idCounter = reinterpret_cast<int*>(geode::base::get() + 0x6ba158);
        int savedCounter = *idCounter;
        int savedCreated = m_objectsCreated;
        bool savedIntegrity = m_passedIntegrity;

        auto holder = CCLayer::create();
        holder->setVisible(false);
        m_objectLayer->addChild(holder);

        for (int i = 0; i < 2; i++) {
            auto fake = PlayerObject::create(1, 1, this, holder, true);
            fake->setVisible(false);
            holder->addChild(fake);
            fake->m_uniqueID = -90001 - i;
            g.fakes[i] = fake;
        }

        *idCounter = savedCounter;
        m_objectsCreated = savedCreated;
        m_passedIntegrity = savedIntegrity;

        if (Mod::get()->getSettingValue<bool>("debug-overlay")) {
            ccBlendFunc blend = { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };
            auto liveDraw = CCDrawNode::create();
            liveDraw->setBlendFunc(blend);
            m_objectLayer->addChild(liveDraw, 1000);
            g.liveDraw = liveDraw;

            auto decisionDraw = CCDrawNode::create();
            decisionDraw->setBlendFunc(blend);
            decisionDraw->setVisible(false);
            m_objectLayer->addChild(decisionDraw, 1001);
            g.decisionDraw = decisionDraw;
        }

        auto mod = Mod::get();
        g.label = nullptr;
        if (mod->getSettingValue<bool>("indicator") || mod->getSettingValue<bool>("debug-overlay")) {
            auto label = CCLabelBMFont::create("", "bigFont.fnt");
            label->setAnchorPoint({ 0.f, 0.f });
            label->setScale(0.35f);
            label->setPosition({ 6.f, 6.f });
            label->setOpacity(0);
            this->addChild(label, 1000);
            g.label = label;
        }

        g.smartOn = mod->getSettingValue<bool>("smart-predict");
        g.debugOn = mod->getSettingValue<bool>("debug-overlay");
        g.orbSim = mod->getSettingValue<bool>("simulate-orbs");
        g.layer = this;
        g.ready = true;
        g.lastAnyInput = g.updates;
        clearRing();
        resetChannels();
    }

    void postUpdate(float dt) {
        PlayLayer::postUpdate(dt);
        if (!layerReady(this)) return;
        tickSmooth(dt);
        if (g.debugOn && !g.simulating) drawLiveProjection(this);
    }

    void resetLevel() {
        bool ready = layerReady(this);
        if (g.diagDeath) showDiag(this, false);
        g.diagDeath = false;
        g.saveCalled = false;
        g.saveBlocked = false;
        g.simTouched.clear();
        if (ready) flushAll(this);
        endAllSmooth(ready);
        PlayLayer::resetLevel();
        g.attemptStart = g.updates;
        g.changedThisAttempt = false;
        g.probe.active = false;
        g.mismatch = 0;
        g.untrusted = false;
        g.lastAnyInput = g.updates;
        clearRing();
        if (ready && g.liveDraw) g.liveDraw->clear();
        if (ready && g.decisionDraw) g.decisionDraw->clear();
    }

    void pauseGame(bool unfocused) {
        if (layerReady(this)) flushAll(this);
        g.probe.active = false;
        g.lastAnyInput = g.updates;
        clearRing();
        PlayLayer::pauseGame(unfocused);
    }

    void onQuit() {
        g.ready = false;
        g.probe.active = false;
        g.layer = nullptr;
        g.fakes[0] = nullptr;
        g.fakes[1] = nullptr;
        g.label = nullptr;
        g.diagLabel = nullptr;
        g.diagOwner = nullptr;
        g.liveDraw = nullptr;
        g.decisionDraw = nullptr;
        endAllSmooth(false);
        clearRing();
        resetChannels();
        PlayLayer::onQuit();
    }

    void destroyPlayer(PlayerObject* player, GameObject* object) {
        bool fake = player && (player == g.fakes[0] || player == g.fakes[1]);
        if (object && object == m_anticheatSpike && !fake) {
            PlayLayer::destroyPlayer(player, object);
            return;
        }
        if (object && object == m_anticheatSpike && fake) return;
        if (g.simulating || (layerReady(this) && fake)) {
            g.simDied = true;
            return;
        }
        bool track = g.diagOwner == this && !g.diagDeath && !m_playerDied;
        if (track) {
            g.bestBefore = m_level ? m_level->m_normalPercent.value() : 0;
            g.diedAt = getCurrentPercentInt();
            g.diedMoved = g.changedThisAttempt;
        }
        PlayLayer::destroyPlayer(player, object);
        if (track && m_playerDied) {
            g.diagDeath = true;
            g.deathVerified = m_damageVerified;
            g.deathIntegrity = m_passedIntegrity;
            g.deathTestMode = m_isTestMode;
            g.deathPractice = m_isPracticeMode;
            g.diedPlatformer = m_isPlatformer;
        }
    }

    void updateVerifyDamage() {
        if (g.simulating) return;
        PlayLayer::updateVerifyDamage();
    }

    void playGravityEffect(bool flip) {
        if (g.simulating) return;
        PlayLayer::playGravityEffect(flip);
    }

    void playEndAnimationToPos(CCPoint position) {
        if (g.simulating) {
            g.simUnknown = true;
            return;
        }
        PlayLayer::playEndAnimationToPos(position);
    }

    void levelComplete() {
        bool block = shouldBlockProgress();
        bool testMode = m_isTestMode;
        g.bestBefore = m_level ? m_level->m_normalPercent.value() : 0;
        if (block) m_isTestMode = true;
        PlayLayer::levelComplete();
        m_isTestMode = testMode;
        g.diedAt = 100;
        g.diedMoved = g.changedThisAttempt;
        showDiag(this, true);
    }

    void showNewBest(bool newReward, int orbs, int diamonds, bool demonKey, bool noRetry, bool noTitle) {
        if (shouldBlockProgress()) return;
        PlayLayer::showNewBest(newReward, orbs, diamonds, demonKey, noRetry, noTitle);
    }
};

class $modify(TAPlayerObject, PlayerObject) {
    void update(float dt) {
        if (!g.simulating && !g.catchingUp) {
            auto pl = PlayLayer::get();
            if (pl && this == pl->m_player1) {
                if (dt > 0.f) g.stepDt = dt;
                if (g.smartOn && layerReady(pl) && !m_isDead) takeSnapshots(pl);
                g.updates++;
                if (g.probe.active && layerReady(pl)) checkProbe(this);
            }
        }
        PlayerObject::update(dt);
    }

    void incrementJumps() {
        if (g.simulating) return;
        PlayerObject::incrementJumps();
    }

    void ringJump(RingObject* object, bool skipCheck) {
        if (g.simulating && !simulatedSpecial(object)) {
            g.simUnknown = true;
            return;
        }
        PlayerObject::ringJump(object, skipCheck);
    }

    void playSpiderDashEffect(CCPoint from, CCPoint to) {
        if (g.simulating) return;
        PlayerObject::playSpiderDashEffect(from, to);
    }

    void spawnCircle() {
        if (g.simulating) return;
        PlayerObject::spawnCircle();
    }

    void spawnDualCircle() {
        if (g.simulating) return;
        PlayerObject::spawnDualCircle();
    }

    void spawnPortalCircle(ccColor3B color, float startRadius) {
        if (g.simulating) return;
        PlayerObject::spawnPortalCircle(color, startRadius);
    }

    void playBumpEffect(int objectType, GameObject* object) {
        if (g.simulating) return;
        PlayerObject::playBumpEffect(objectType, object);
    }

    void tryPlaceCheckpoint() {
        if (g.simulating) return;
        PlayerObject::tryPlaceCheckpoint();
    }
};

class $modify(TAEnhancedObject, EnhancedGameObject) {
    void activatedByPlayer(PlayerObject* player) {
        if (g.simulating) return;
        EnhancedGameObject::activatedByPlayer(player);
    }

    void powerOnObject(int state) {
        if (g.simulating) return;
        EnhancedGameObject::powerOnObject(state);
    }

    void triggerActivated(float xPosition) {
        if (g.simulating) return;
        EnhancedGameObject::triggerActivated(xPosition);
    }
};

class $modify(TAEffectObject, EffectGameObject) {
    void triggerActivated(float xPosition) {
        if (g.simulating) return;
        EffectGameObject::triggerActivated(xPosition);
    }
};

class $modify(TARingObject, RingObject) {
    void powerOnObject(int state) {
        if (g.simulating) return;
        RingObject::powerOnObject(state);
    }

    void triggerActivated(float xPosition) {
        if (g.simulating) return;
        RingObject::triggerActivated(xPosition);
    }

    void spawnCircle() {
        if (g.simulating) return;
        RingObject::spawnCircle();
    }
};

class $modify(TAGameObject, GameObject) {
    void playShineEffect() {
        if (g.simulating) return;
        GameObject::playShineEffect();
    }
};

class $modify(TAGameLevel, GJGameLevel) {
    void savePercentage(int percent, bool isPracticeMode, int clicks, int attempts, bool isChkValid) {
        bool block = PlayLayer::get() && shouldBlockProgress();
        if (PlayLayer::get() && !isPracticeMode) {
            g.saveCalled = true;
            g.saveBlocked = block;
            g.savePercent = percent;
            g.saveChk = isChkValid;
        }
        if (block) return;
        GJGameLevel::savePercentage(percent, isPracticeMode, clicks, attempts, isChkValid);
    }
};

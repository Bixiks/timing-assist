#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/GJGameLevel.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <deque>
#include <type_traits>
#include <utility>
#include <vector>

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

namespace {

constexpr int kModeCount = 8;
constexpr int kLandMargin = 2;
constexpr int kWindowMargin = 4;
constexpr int kNoTick = -1000000;
constexpr int kRing = 16;
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
};

struct Config {
    bool enabled = true;
    int maxDelay = 8;
    int lookahead = 120;
    bool keepHold = true;
    bool releaseAssist = true;
    bool indicator = false;
    bool smart = false;
    int smartWindow = 6;
};

struct SimEvent {
    int tick;
    bool down;
};

struct SimPlan {
    std::vector<SimEvent> events;
    int length = 0;
    int watchFrom = -1;
    int probeAt = -1;
};

struct SimResult {
    int death = -1;
    int unknownAt = -1;
};

struct Pick {
    int tick = 0;
    bool found = true;
};

struct Probe {
    bool active = false;
    int compareAt = 0;
    PlayerObject* player = nullptr;
    CCPoint predicted[3];
};

struct Targets {
    PlayerObject* players[2] = { nullptr, nullptr };
    int count = 0;
    int channel = 0;
};

struct State {
    PlayLayer* layer = nullptr;
    PlayerObject* fakes[2] = { nullptr, nullptr };
    CCLabelBMFont* label = nullptr;
    Channel channels[2];
    std::array<double, kModeCount> hold{};
    std::array<double, kModeCount> gap{};
    std::array<std::array<Snapshot, kRing>, 2> ring;
    Snapshot live[2];
    int updates = 0;
    int lastAnyInput = kNoTick;
    float stepDt = 0.25f;
    bool ready = false;
    bool inQueue = false;
    bool inCommands = false;
    bool dispatching = false;
    bool simulating = false;
    bool catchingUp = false;
    bool simDied = false;
    bool simUnknown = false;
    bool changedThisAttempt = false;
    bool smartOn = false;
    Probe probe;
    CCPoint probeCapture[3];
    int probeCaptured = 0;
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
    c.lookahead = std::max(24, msToTicks(mod->getSettingValue<int64_t>("lookahead")));
    c.keepHold = mod->getSettingValue<bool>("keep-hold");
    c.releaseAssist = mod->getSettingValue<bool>("release-assist");
    c.indicator = mod->getSettingValue<bool>("indicator");
    c.smart = mod->getSettingValue<bool>("smart-predict");
    c.smartWindow = std::clamp(msToTicks(mod->getSettingValue<int64_t>("smart-window")), 1, kRing - 2);
    return c;
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
    return std::clamp(static_cast<int>(std::lround(g.gap[idx(m)])), 4, 120);
}

void learn(double& value, int sample) {
    value = std::clamp(value * 0.8 + sample * 0.2, 2.0, 120.0);
}

bool keepInSim(GameObjectType t) {
    return t == GameObjectType::Solid
        || t == GameObjectType::Hazard
        || t == GameObjectType::AnimatedHazard
        || t == GameObjectType::Slope;
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
    if (forSim) {
        p->m_isDead = false;
        p->m_isDashing = false;
        p->m_shouldTryPlacingCheckpoint = false;
        p->m_canPlaceCheckpoint = false;
        p->m_checkpointTimeout = false;
    }
    else {
        p->m_isDead = s.isDead;
        p->m_isDashing = s.isDashing;
        p->m_shouldTryPlacingCheckpoint = s.shouldTryPlacingCheckpoint;
        p->m_canPlaceCheckpoint = s.canPlaceCheckpoint;
        p->m_checkpointTimeout = s.checkpointTimeout;
    }
    p->m_touchingRings->removeAllObjects();
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

bool canAssist(PlayLayer* pl, Targets const& t) {
    if (!layerReady(pl) || g.untrusted) return false;
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

    float dt = g.stepDt > 0.f ? g.stepDt : 0.25f;
    SimResult result;
    int end = plan.length;
    size_t next = 0;
    LandPhase phase = plan.watchFrom >= 0 ? LandPhase::WaitStart : LandPhase::Done;
    int groundedFor = 0;

    g.simulating = true;
    g.simDied = false;
    g.simUnknown = false;
    g.probeCaptured = 0;

    for (int tick = 0; tick < end; tick++) {
        if (phase == LandPhase::WaitStart && tick >= plan.watchFrom) {
            phase = fakes[0]->m_isOnGround ? LandPhase::WaitLeave : LandPhase::WaitFirstLand;
        }

        while (next < plan.events.size() && plan.events[next].tick <= tick) {
            for (int i = 0; i < count; i++) {
                if (plan.events[next].down) fakes[i]->pushButton(PlayerButton::Jump);
                else fakes[i]->releaseButton(PlayerButton::Jump);
            }
            next++;
        }

        for (int i = 0; i < count; i++) {
            auto f = fakes[i];
            clearLogs(f);
            f->update(dt);
            pl->checkCollisions(f, dt, false);
            if (f->m_isDead) g.simDied = true;
            if (g.simDied || g.simUnknown) break;
            f->updateRotation(dt);
        }

        if (g.simDied) {
            result.death = tick;
            break;
        }
        if (g.simUnknown) {
            result.unknownAt = tick;
            break;
        }

        if (plan.probeAt > 0 && tick >= plan.probeAt - 1 && tick <= plan.probeAt + 1) {
            g.probeCapture[tick - plan.probeAt + 1] = fakes[0]->getPosition();
            g.probeCaptured++;
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
                    end = std::min(end, tick + 1 + kLandMargin);
                }
                break;
            case LandPhase::WaitLand:
                if (grounded) {
                    phase = LandPhase::Done;
                    end = std::min(end, tick + 1 + kLandMargin);
                }
                break;
            default:
                break;
        }
    }

    g.simulating = false;

    for (int i = 0; i < 2; i++) {
        if (!blocks[i]) continue;
        blocks[i]->setPosition(blockPos[i]);
        blocks[i]->m_positionX = blockX[i];
        blocks[i]->m_positionY = blockY[i];
    }

    return result;
}

void setPressWindow(SimPlan& plan, Mode m, int pressAt, int futureFrom, Config const& cfg) {
    int hold = holdTicks(m);
    int gap = gapTicks(m);
    if (isHoldMode(m)) {
        plan.length = futureFrom + std::min(cfg.lookahead, hold + kWindowMargin);
    }
    else if (isLandMode(m)) {
        plan.length = futureFrom + cfg.lookahead;
        plan.watchFrom = pressAt;
    }
    else {
        plan.length = futureFrom + std::min(cfg.lookahead, std::max(12, hold + gap) + kWindowMargin);
    }
}

void setReleaseWindow(SimPlan& plan, Mode m, int releaseAt, int futureFrom, Config const& cfg) {
    if (isLandMode(m)) {
        plan.length = futureFrom + cfg.lookahead;
        plan.watchFrom = releaseAt;
    }
    else {
        plan.length = futureFrom + std::min(cfg.lookahead, gapTicks(m) + kWindowMargin);
    }
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

Pick pickPressTick(PlayLayer* pl, Targets const& t, Channel const& ch, int now, Config const& cfg) {
    int base = lastQueuedTick(ch, now);
    Mode m = modeOf(t.players[0]);
    int hold = holdTicks(m);
    auto pending = pendingEvents(ch, now);
    captureLive(t);
    Snapshot const* sources[2] = { &g.live[0], &g.live[1] };

    for (int k = 0; k <= cfg.maxDelay; k++) {
        int rel = base - now + k;
        SimPlan plan;
        plan.events = pending;
        plan.events.push_back({ rel, true });
        plan.events.push_back({ rel + hold, false });
        setPressWindow(plan, m, rel, rel, cfg);
        if (k == 0 && rel == 0) {
            plan.probeAt = std::clamp(hold - 1, 2, 6);
        }

        auto r = runSim(pl, t.count, sources, plan);
        if (r.death < 0) {
            if (k == 0 && rel == 0 && g.probeCaptured == 3) {
                g.probe.active = true;
                g.probe.compareAt = now + 2 + plan.probeAt;
                g.probe.player = t.players[0];
                for (int i = 0; i < 3; i++) g.probe.predicted[i] = g.probeCapture[i];
            }
            return { base + k, true };
        }
        if (r.death < rel) break;
    }
    return { base, false };
}

Pick pickReleaseTick(PlayLayer* pl, Targets const& t, Channel const& ch, int now, int target, Config const& cfg) {
    Mode m = modeOf(t.players[0]);
    if (!cfg.releaseAssist || !releaseMatters(m)) return { target, true };

    int minTick = std::max(lastQueuedTick(ch, now), ch.firePressTick + 1);
    auto pending = pendingEvents(ch, now);
    captureLive(t);
    Snapshot const* sources[2] = { &g.live[0], &g.live[1] };

    auto safe = [&](int tick) {
        int rel = tick - now;
        SimPlan plan;
        plan.events = pending;
        plan.events.push_back({ rel, false });
        setReleaseWindow(plan, m, rel, rel, cfg);
        return runSim(pl, t.count, sources, plan).death < 0;
    };

    if (safe(target)) return { target, true };
    for (int d = 1; d <= cfg.maxDelay; d++) {
        if (safe(target + d)) return { target + d, true };
        if (target - d >= minTick && safe(target - d)) return { target - d, true };
    }
    return { target, false };
}

int pickLateTicks(PlayLayer* pl, Targets const& t, Channel const& ch, int now, bool press, Config const& cfg) {
    if (!cfg.smart || !g.smartOn || !ch.queue.empty()) return 0;
    Mode m = modeOf(t.players[0]);
    int hold = holdTicks(m);
    Snapshot const* sources[2] = { nullptr, nullptr };

    for (int j = 1; j <= cfg.smartWindow; j++) {
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
            sources[i] = &snap;
        }
        if (!usable) break;

        SimPlan plan;
        if (press) {
            plan.events.push_back({ 0, true });
            plan.events.push_back({ j + hold, false });
            setPressWindow(plan, m, 0, j, cfg);
        }
        else {
            plan.events.push_back({ 0, false });
            setReleaseWindow(plan, m, 0, j, cfg);
        }
        plan.length = std::max(plan.length, j + kWindowMargin);

        auto r = runSim(pl, t.count, sources, plan);
        if (r.death < 0 && (r.unknownAt < 0 || r.unknownAt >= j)) return j;
    }
    return 0;
}

void applyLate(PlayLayer* pl, Targets const& t, int j, bool down, bool isPlayer1) {
    int u = g.updates - j;
    for (int i = 0; i < t.count; i++) {
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

void showIndicator(std::string const& text) {
    if (!g.label || !g.ready) return;
    g.label->setString(text.c_str());
    g.label->stopAllActions();
    g.label->setOpacity(210);
    g.label->runAction(CCSequence::create(CCDelayTime::create(0.6f), CCFadeOut::create(0.4f), nullptr));
}

void resetChannels() {
    for (auto& ch : g.channels) ch = Channel();
}

void dispatch(GJBaseGameLayer* layer, Channel& ch, Queued const& q) {
    if (q.down && q.main && ch.held && q.origin == ch.pressTick) {
        ch.shift = std::max(0, g.updates - ch.pressTick);
        ch.firePressTick = g.updates;
    }
    g.dispatching = true;
    layer->handleButton(q.down, static_cast<int>(PlayerButton::Jump), q.isPlayer1);
    g.dispatching = false;
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
        ch.shift = 0;
        ch.held = false;
    }
}

void checkProbe(PlayerObject* real) {
    if (!g.probe.active || g.updates != g.probe.compareAt) return;
    g.probe.active = false;
    if (real != g.probe.player) return;
    auto pos = real->getPosition();
    float best = 1e9f;
    for (auto const& p : g.probe.predicted) {
        best = std::min(best, std::abs(pos.x - p.x) + std::abs(pos.y - p.y));
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

void markChanged(Config const& cfg, std::string const& text) {
    g.changedThisAttempt = true;
    if (cfg.indicator && !text.empty()) showIndicator(text);
}

}

$on_mod(Loaded) {
    g.hold.fill(20.0);
    g.gap.fill(30.0);
    g.smartOn = Mod::get()->getSettingValue<bool>("smart-predict");
    listenForSettingChanges<bool>("smart-predict", [](bool value) {
        g.smartOn = value;
        clearRing();
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
            Pick pick{ natural, true };
            bool assist = cfg.enabled && canAssist(pl, targets);
            if (assist) pick = pickPressTick(pl, targets, ch, now, cfg);

            if (assist && !pick.found && natural == now) {
                int late = pickLateTicks(pl, targets, ch, now, true, cfg);
                if (late > 0) {
                    applyLate(pl, targets, late, true, isPlayer1);
                    ch.shift = 0;
                    ch.firePressTick = now - late;
                    markChanged(cfg, fmt::format("late fix -{}ms", ticksToMs(late)));
                    return;
                }
            }

            ch.shift = std::max(0, pick.tick - now);
            ch.firePressTick = pick.tick;
            if (pick.tick > natural) {
                markChanged(cfg, fmt::format("press +{}ms", ticksToMs(pick.tick - now)));
            }
            send(pick.tick, true);
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
        Pick pick{ target, true };
        bool assist = cfg.enabled && canAssist(pl, targets);
        if (assist) pick = pickReleaseTick(pl, targets, ch, now, target, cfg);

        if (assist && !pick.found && target == now && natural == now) {
            int late = pickLateTicks(pl, targets, ch, now, false, cfg);
            if (late > 0) {
                applyLate(pl, targets, late, false, isPlayer1);
                ch.shift = 0;
                markChanged(cfg, fmt::format("late release -{}ms", ticksToMs(late)));
                return;
            }
        }

        if (pick.tick != now) {
            markChanged(cfg, pick.tick != target ? fmt::format("release {:+}ms", ticksToMs(pick.tick - now)) : std::string());
        }
        send(pick.tick, true);
        ch.shift = 0;
    }

    void collisionCheckObjects(PlayerObject* player, gd::vector<GameObject*>* objects, int objectCount, float dt) {
        if (!g.simulating || !objects || !player) {
            GJBaseGameLayer::collisionCheckObjects(player, objects, objectCount, dt);
            return;
        }

        std::vector<GameObject*> off;
        off.reserve(32);
        CCRect reach = player->getObjectRect();
        reach.origin.x -= 6.f;
        reach.origin.y -= 6.f;
        reach.size.width += 12.f;
        reach.size.height += 12.f;

        int n = std::min(objectCount, static_cast<int>(objects->size()));
        for (int i = 0; i < n; i++) {
            auto obj = (*objects)[i];
            if (!obj) continue;
            if (keepInSim(obj->m_objectType) && !isCollectibleId(obj->m_objectID)) continue;
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
        if (g.simulating) return;
        GJBaseGameLayer::playerTouchedRing(player, object);
    }

    void playerTouchedTrigger(PlayerObject* player, EffectGameObject* object) {
        if (g.simulating) return;
        GJBaseGameLayer::playerTouchedTrigger(player, object);
    }

    bool canBeActivatedByPlayer(PlayerObject* player, EffectGameObject* object) {
        if (g.simulating) return false;
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
        if (g.simulating) {
            g.simUnknown = true;
            return;
        }
        GJBaseGameLayer::bumpPlayer(player, object);
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
        g.simulating = false;
        g.catchingUp = false;
        g.changedThisAttempt = false;
        g.probe.active = false;
        g.mismatch = 0;
        g.untrusted = false;
        g.lastAnyInput = g.updates;
        clearRing();
        resetChannels();
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        if (Mod::get()->getSettingValue<bool>("enabled")) m_clickBetweenSteps = false;
        return true;
    }

    void setupHasCompleted() {
        PlayLayer::setupHasCompleted();

        auto holder = CCLayer::create();
        holder->setVisible(false);
        m_objectLayer->addChild(holder);

        for (int i = 0; i < 2; i++) {
            auto fake = PlayerObject::create(1, 1, this, holder, true);
            fake->setVisible(false);
            holder->addChild(fake);
            g.fakes[i] = fake;
        }

        g.label = nullptr;
        if (Mod::get()->getSettingValue<bool>("indicator")) {
            auto label = CCLabelBMFont::create("", "bigFont.fnt");
            label->setAnchorPoint({ 0.f, 0.f });
            label->setScale(0.35f);
            label->setPosition({ 6.f, 6.f });
            label->setOpacity(0);
            this->addChild(label, 1000);
            g.label = label;
        }

        g.smartOn = Mod::get()->getSettingValue<bool>("smart-predict");
        g.layer = this;
        g.ready = true;
        g.lastAnyInput = g.updates;
        clearRing();
        resetChannels();
    }

    void resetLevel() {
        if (layerReady(this)) flushAll(this);
        PlayLayer::resetLevel();
        g.changedThisAttempt = false;
        g.probe.active = false;
        g.mismatch = 0;
        g.untrusted = false;
        g.lastAnyInput = g.updates;
        clearRing();
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
        clearRing();
        resetChannels();
        PlayLayer::onQuit();
    }

    void destroyPlayer(PlayerObject* player, GameObject* object) {
        if (g.simulating || (layerReady(this) && player && (player == g.fakes[0] || player == g.fakes[1]))) {
            g.simDied = true;
            return;
        }
        PlayLayer::destroyPlayer(player, object);
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
        if (block) m_isTestMode = true;
        PlayLayer::levelComplete();
        m_isTestMode = testMode;
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
        if (g.simulating) {
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

class $modify(TAGameLevel, GJGameLevel) {
    void savePercentage(int percent, bool isPracticeMode, int clicks, int attempts, bool isChkValid) {
        if (PlayLayer::get() && shouldBlockProgress()) return;
        GJGameLevel::savePercentage(percent, isPracticeMode, clicks, attempts, isChkValid);
    }
};

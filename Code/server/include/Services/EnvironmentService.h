#pragma once

#include <Events/PacketEvent.h>
#include <Structs/TimeModel.h>

struct World;
struct UpdateEvent;
struct PlayerJoinEvent;

class EnvironmentService
{
public:
    EnvironmentService(World &aWorld, entt::dispatcher &aDispatcher);

    // we use these types for SOL
    // this is done this way because SOL
    // provides direct support for these
    using TTime = std::pair<int, int>;
    using TDate = std::tuple<int, int, int>;

    bool SetTime(int aHour, int aMinutes, float aScale) noexcept;

    // returns hours, minutes
    TTime GetTime() const noexcept;

    // returns dd/mm/yy
    TDate GetDate() const noexcept;

    float GetTimeScale() const noexcept { return m_timeModel.TimeScale; }

private:
    void OnUpdate(const UpdateEvent &) noexcept; 
    void OnPlayerJoin(const PlayerJoinEvent&) noexcept;

    TimeModel m_timeModel;
    uint64_t m_lastTick = 0;

    entt::scoped_connection m_updateConnection;
    entt::scoped_connection m_joinConnection;
    World &m_world;
};

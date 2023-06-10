#include "Room.h"

void Room::addUser(const LoggedUser& user)
{
    std::lock_guard<std::mutex> users_lock(user_mutex);
	m_users.push_back(user);
}

void Room::removeUser(const LoggedUser& user)
{
    std::lock_guard<std::mutex> users_lock(user_mutex);
    auto it = std::find_if(m_users.begin(), m_users.end(),
        [&](const LoggedUser& u) { return u.getUsername() == user.getUsername(); });

    if (it != m_users.end())
    {
        if (user.getUsername() == m_admin.getUsername()); // Notify players to leave the server
        m_users.erase(it);
    }
}

const std::vector<LoggedUser>& Room::getAllUsers() const
{
    return m_users;
}

const unsigned int Room::getRoomState() const
{
    return m_metadata.isActive;
}

void Room::startGame()
{
    m_metadata.isActive = true;
}

RoomData Room::getRoomData() const
{
    return m_metadata;
}

bool Room::isUserInRoom(const LoggedUser& user) const
{
    for (const auto& currentUser : m_users)
    {
        if (currentUser.getUsername() == user.getUsername())
        {
            return true;
        }
    }
    return false;
}

LoggedUser Room::getAdmin() const
{
    return m_admin;
}

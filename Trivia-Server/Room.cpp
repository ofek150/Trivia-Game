#include "Room.h"

Room::Room(const RoomData& metadata) : m_metadata(metadata) {}

void Room::addUser(const LoggedUser& user)
{
	m_users.push_back(user);
}

void Room::removeUser(const LoggedUser& user)
{
    auto it = std::find_if(m_users.begin(), m_users.end(),
        [&](const LoggedUser& u) { return u.getUsername() == user.getUsername(); });

    if (it != m_users.end())
    {
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

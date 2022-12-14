#include "epoller.h"

Epoller::Epoller(int MaxEvent) : m_events(MaxEvent)
{
    m_EpollFd = epoll_create(512);
    assert(m_EpollFd >= 0 && m_events.size() > 0);
}

Epoller::~Epoller()
{
    close(m_EpollFd);
}

bool Epoller::AddFd(int fd, uint32_t events)
{
    if (fd < 0)
    {
        return false;
    }
    epoll_event ev = {0};
    ev.data.fd = fd;
    ev.events = events;
    return 0 == epoll_ctl(m_EpollFd, EPOLL_CTL_ADD, fd, &ev);
}

bool Epoller::ModFd(int fd, uint32_t events)
{
    if (fd < 0)
    {
        return false;
    }
    epoll_event ev = {0};
    ev.data.fd = fd;
    ev.events = events;
    return 0 == epoll_ctl(m_EpollFd, EPOLL_CTL_MOD, fd, &ev);
}

bool Epoller::DelFd(int fd)
{
    if (fd < 0)
    {
        return false;
    }
    epoll_event ev = {0};
    return 0 == epoll_ctl(m_EpollFd, EPOLL_CTL_DEL, fd, &ev);
}

int Epoller::Wait(int timeoutms)
{
    return epoll_wait(m_EpollFd, &m_events[0], static_cast<int>(m_events.size()), timeoutms);
}

int Epoller::GetEventFd(size_t i) const
{
    assert(i < m_events.size() && i >= 0);
    return m_events[i].data.fd;
}

uint32_t Epoller::GetEvents(size_t i) const
{
    assert(i < m_events.size() && i >= 0);
    return m_events[i].events;
}
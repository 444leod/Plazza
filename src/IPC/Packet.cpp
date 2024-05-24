/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Packet
*/

#include "Packet.hpp"
#include <iostream>

void plz::Packet::append(const void *data, std::size_t size)
{
    auto pos = this->_data.end();
    const auto *begin = reinterpret_cast<const std::byte *>(data);
    const auto *end = begin + size;
    this->_data.insert(pos, begin, end);
    this->_size = this->_data.size();
}

const void *plz::Packet::raw() const
{
    return reinterpret_cast<const void *>(this->_data.data());
}

bool plz::Packet::_checkSize(std::size_t size)
{
    if (this->_pos + size <= this->_size)
        return true;
    this->_fail = true;
    return false;
}

plz::Packet& plz::Packet::operator<<(bool data)
{
    *this << static_cast<std::uint8_t>(data);
    return *this;
}

plz::Packet& plz::Packet::operator<<(char data)
{
    *this << static_cast<std::uint8_t>(data);
    return *this;
}

plz::Packet& plz::Packet::operator<<(uint8_t data)
{
    this->append(&data, sizeof(data));
    return *this;
}

plz::Packet& plz::Packet::operator<<(int data)
{
    this->append(&data, sizeof(data));
    return *this;
}

plz::Packet& plz::Packet::operator<<(std::uint32_t data)
{
    this->append(&data, sizeof(data));
    return *this;
}

plz::Packet& plz::Packet::operator<<(int64_t data)
{
    this->append(&data, sizeof(data));
    return *this;
}

plz::Packet& plz::Packet::operator<<(std::size_t data)
{
    this->append(&data, sizeof(data));
    return *this;
}

plz::Packet& plz::Packet::operator<<(const char *data)
{
    std::size_t len = std::strlen(data);
    *this << len;
    this->append(data, len);
    return *this;
}

plz::Packet& plz::Packet::operator<<(const std::string& data)
{
    *this << data.c_str();
    return *this;
}

plz::Packet& plz::Packet::operator>>(bool& data)
{
    if (!this->_checkSize(sizeof(data)))
        return *this;
    std::memcpy(&data, &(this->_data[this->_pos]), sizeof(data));
    this->_pos += sizeof(data);
    return *this;
}

plz::Packet& plz::Packet::operator>>(char& data)
{
    if (!this->_checkSize(sizeof(data)))
        return *this;
    std::memcpy(&data, &(this->_data[this->_pos]), sizeof(data));
    this->_pos += sizeof(data);
    return *this;
}

plz::Packet& plz::Packet::operator>>(int& data)
{
    if (!this->_checkSize(sizeof(data)))
        return *this;
    std::memcpy(&data, &(this->_data[this->_pos]), sizeof(data));
    this->_pos += sizeof(data);
    return *this;
}

plz::Packet& plz::Packet::operator>>(std::uint32_t& data)
{
    if (!this->_checkSize(sizeof(data)))
        return *this;
    std::memcpy(&data, &(this->_data[this->_pos]), sizeof(data));
    this->_pos += sizeof(data);
    return *this;
}

plz::Packet& plz::Packet::operator>>(int64_t& data)
{
    if (!this->_checkSize(sizeof(data)))
        return *this;
    std::memcpy(&data, &(this->_data[this->_pos]), sizeof(data));
    this->_pos += sizeof(data);
    return *this;
}

plz::Packet& plz::Packet::operator>>(std::size_t& data)
{
    if (!this->_checkSize(sizeof(data)))
        return *this;
    std::memcpy(&data, &(this->_data[this->_pos]), sizeof(data));
    this->_pos += sizeof(data);
    return *this;
}

plz::Packet& plz::Packet::operator>>(char *data)
{
    std::size_t len = 0;
    if (!this->_checkSize(sizeof(data)))
        return *this;
    *this >> len;
    if (!this->_checkSize(sizeof(data))) {
        return *this;
    }
    std::memcpy(data, &(this->_data[this->_pos]), len);
    this->_pos += len;
    return *this;
}

plz::Packet& plz::Packet::operator>>(std::string& data)
{
    std::size_t len = 0;

    if (!this->_checkSize(sizeof(data)))
        return *this;
    *this >> len;
    if (!this->_checkSize(sizeof(data)))
        return *this;
    for (std::size_t i = 0; i < len; i++) {
        char c;
        *this >> c;
        data += c;
    }
    return *this;
}
